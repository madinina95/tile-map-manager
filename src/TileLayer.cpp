//
// Created by lionheart on 21/03/2020.
//

#include "../include/TileMap.hpp"
#include "../include/TileLayer.hpp"

TileLayer::TileLayer(const Tmx::TileLayer &tmxLayer, const TileMap &map) :
        m_tmxTileLayer(tmxLayer),
        m_isAnimated(false),
        m_parent(map),
        m_tiles() {

    m_width = tmxLayer.GetWidth();
    m_height = tmxLayer.GetHeight();
    m_name = tmxLayer.GetName();
    m_isVisible = tmxLayer.IsVisible();
    m_opacity = tmxLayer.GetOpacity();
    m_zOrder = tmxLayer.GetZOrder();

}

TileLayer::~TileLayer() {

}

int TileLayer::getWidth() const {
    return m_width;
}

int TileLayer::getHeight() const {
    return m_height;
}

std::string TileLayer::getName() const {
    return m_name;
}

bool TileLayer::isVisible() const {
    return m_isVisible;
}

float TileLayer::getOpacity() const {
    return m_opacity;
}

int TileLayer::getZOrder() const {
    return m_zOrder;
}

void TileLayer::buildTiles() {

    // Reserve in memory the number of tile
    m_tiles.resize(m_tmxTileLayer.mapGetMap()->GetHeight() * m_tmxTileLayer.mapGetMap()->GetWidth());

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            sf::Vector2i position(x, y);
            int tileIndexTilset = m_tmxTileLayer.GetTileTilesetIndex(x, y);
            if (tileIndexTilset != -1) { // Nothing to draw in this tile for this layer
                int tileId = m_tmxTileLayer.GetTile(x, y).id;
                // the tile add properties
                const Tmx::Tile *tile = m_tmxTileLayer.mapGetMap()->GetTileset(tileIndexTilset)->GetTile(tileId);
                if (tile != nullptr) {
                    if (tile->IsAnimated()) {
                        m_isAnimated = true;
                        m_tiles[x + y * m_width] =
                                std::unique_ptr<Tile>(new AnimatedTile(
                                        tileId,
                                        *m_tmxTileLayer.mapGetMap()->GetTileset(tileIndexTilset)->GetTile(tileId),
                                        position,
                                        m_parent.getTileSet(tileIndexTilset))
                                );
                    } else {
                        m_tiles[x + y * m_width] =
                                std::unique_ptr<Tile>(new PropertyTile(
                                        tileId,
                                        *m_tmxTileLayer.mapGetMap()->GetTileset(tileIndexTilset)->GetTile(tileId),
                                        position,
                                        m_parent.getTileSet(tileIndexTilset))
                                );
                    }
                } else {
                    m_tiles[x + y * m_width] = std::make_unique<Tile>(
                            tileId,
                            position,
                            m_parent.getTileSet(tileIndexTilset)
                    );
                }
            } else {
                m_tiles[x + y * m_width] = nullptr;
            }
        }
    }
}

void TileLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    states.transform *= getTransform();

    for (int j = 0; j < m_height; ++j) {
        for (int i = 0; i < m_width; ++i) {
            if (m_tiles[i + j * m_width] != nullptr) {
                if (m_visibleArea.contains(m_tiles[i + j * m_width]->getWorldPosition().x,
                                         m_tiles[i + j * m_width]->getWorldPosition().y)) {
                    target.draw(*m_tiles[i + j * m_width], states);
                }
            }
        }
    }
}

void TileLayer::update(const sf::Time &dt) {
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            if (m_tiles[x + y * m_width] != nullptr &&
                m_tiles[x + y * m_width]->isAnimated()) {
                if (m_visibleArea.contains(m_tiles[x + y * m_width]->getWorldPosition().x,
                                         m_tiles[x + y * m_width]->getWorldPosition().y)) {
                    m_tiles[x + y * m_width]->update(dt);
                }
            }
        }
    }
}

void TileLayer::setVisibleArea(const sf::IntRect &visibleArea) {
    m_visibleArea = visibleArea;
}

bool TileLayer::isAnimated() {
    return m_isAnimated;
}
