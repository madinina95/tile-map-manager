//
// Created by lionheart on 20/03/2020.
//

#include <memory>
#include "../include/TileMap.hpp"

TileMap::TileMap() : m_drawTo(-1), m_drawFrom(-1) {

}

TileMap::~TileMap() {

}


void TileMap::loadMap(std::string fileName) {

    std::unique_ptr<Tmx::Map> map = std::make_unique<Tmx::Map>();
    map->ParseFile(fileName);

    // generate tileset Map to load texture
    generateTilesetList(*map);

    // instanciate unique_ptr tile layers

    m_width = map->GetWidth();
    m_height = map->GetHeight();
    m_tileWidth = map->GetTileWidth();
    m_tileHeight = map->GetTileHeight();

    m_nbTilesets = map->GetNumTilesets();
    m_nbLayers = map->GetNumLayers();

    m_tileLayers.resize(m_nbLayers);

    buildLayer(*map);

}

void TileMap::generateTilesetList(Tmx::Map &map) {

    for (int i = 0; i < map.GetTilesets().size(); ++i) {
        const sf::Vector2i tileSize(map.GetTilesets()[i]->GetTileWidth(), map.GetTilesets()[i]->GetTileHeight());
        const sf::Vector2i tilesetSize(map.GetTilesets()[i]->GetImage()->GetWidth(),
                                       map.GetTilesets()[i]->GetImage()->GetHeight());

        // TODO variabilise the path
        std::string root = "../map/tilesets/";

        const std::string path = root.append(map.GetTilesets()[i]->GetImage()->GetSource());
        const int spacing = map.GetTilesets()[i]->GetSpacing();

        loadTileset(i, path, tileSize, tilesetSize, spacing);

    }
}

void TileMap::buildLayer(const Tmx::Map &tmxMap) {

    for (int i = 0; i < m_nbLayers; ++i) {
        m_tileLayers[i] = std::make_unique<TileLayer>(*(tmxMap.GetTileLayer(i)), *this);
        m_tileLayers[i]->buildTiles();
    }
}

int TileMap::getWidth() const {
    return m_width;
}

int TileMap::getHeight() const {
    return m_height;
}

int TileMap::getTileWidth() const {
    return m_tileWidth;
}

int TileMap::getTileHeight() const {
    return m_tileHeight;
}

int TileMap::getNbTilesets() const {
    return m_nbTilesets;
}

int TileMap::getNbLayers() const {
    return m_nbLayers;
}

void TileMap::loadTileset(const int &id, const std::string &path, const sf::Vector2i &tileSize,
                          const sf::Vector2i &tilesetSize,
                          const int &spacing) {
    std::unique_ptr<Tileset> ptr(new Tileset(id, path, tileSize, tilesetSize, spacing));
    m_tilesetsMap.emplace(id, std::move(ptr));
}

Tileset &TileMap::getTileSet(const int &id) const {
    return *m_tilesetsMap.at(id);
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    states.transform *= getTransform();

    if (m_drawTo != 1) {
        for (int i = 0; i <= m_drawTo; ++i) {
            if (m_tileLayers[i]->isVisible()) {
                m_tileLayers[i]->setVisibleArea(m_visibleArea);
                target.draw(*m_tileLayers[i], states);
            }
        }
    }

    if (m_drawFrom != 1) {
        for (int i = m_drawFrom; i < m_tileLayers.size(); ++i) {
            if (m_tileLayers[i]->isVisible()) {
                m_tileLayers[i]->setVisibleArea(m_visibleArea);
                target.draw(*m_tileLayers[i], states);
            }
        }
    }

}

void TileMap::update(sf::Time &dt) {

    for (const auto &tileLayer : m_tileLayers) {
        if (tileLayer->isVisible() && tileLayer->isAnimated()) {
            tileLayer->update(dt);
        }
    }

}

void TileMap::setVisibleArea(sf::IntRect &visibleArea) {
    m_visibleArea = visibleArea;
}

void TileMap::setDrawFrom(const int &index) {
    m_drawFrom = index;
}

void TileMap::setDrawTo(const int &index) {
    m_drawTo = index;
}

TileLayer &TileMap::getLayer(const std::string &name) {

    for (const auto &layer : m_tileLayers) {
        if(layer->getName() == name) {
            return *layer;
        }
    }
}
