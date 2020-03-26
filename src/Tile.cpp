//
// Created by lionheart on 21/03/2020.
//

#include "../include/Tile.hpp"

Tile::Tile(const int &tileId, const sf::Vector2i &position, const Tileset &tileset) :
        m_tileId(tileId),
        m_position(position),
        m_tileSet(tileset),
        m_vertices(sf::Quads, 4),
        m_isVisible(true){

    applyTexture(
            m_position.x,
            m_position.y,
            m_tileSet.m_spacing,
            m_tileSet.m_tilesetSize.x,
            m_tileSet.m_tileSize,
            m_tileId
    );

}

Tile::~Tile() {

}

void Tile::applyTexture(int x, int y, int spacing, int tilesetWidth, sf::Vector2i tileSize, int tileId) {


    // Get the position of the tile in the tileset
    int tu = tileId % (tilesetWidth / (tileSize.x + spacing));
    int tv = tileId / (tilesetWidth / (tileSize.x + spacing));

    sf::Vertex *quad = &m_vertices[0];

    // Get the position of the tile in the window
    quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
    quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
    quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
    quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);


    // Get the position of the texture in tileset
    quad[0].texCoords = sf::Vector2f(tu * (tileSize.x + spacing), tv * (tileSize.y + spacing));
    quad[1].texCoords = sf::Vector2f((tu + 1) * (tileSize.x + spacing) - spacing, tv * (tileSize.y + spacing));
    quad[2].texCoords = sf::Vector2f((tu + 1) * (tileSize.x + spacing) - spacing,
                                     (tv + 1) * (tileSize.y + spacing) - spacing);
    quad[3].texCoords = sf::Vector2f(tu * (tileSize.x + spacing), (tv + 1) * (tileSize.y + spacing) - spacing);

}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // on applique la transformation
    states.transform *= getTransform();
    // on applique la texture du tileset
    states.texture = m_tileSet.m_texture.get();
    // et on dessine enfin le tableau de vertex
    target.draw(m_vertices, states);

}

sf::Vector2i Tile::getWorldPosition() {
    return sf::Vector2i(m_vertices[0].position.x, m_vertices[0].position.y);
}

void Tile::update(sf::Time dt) {
    // Do nothing

}

bool Tile::isAnimated() {
    return false;
}

bool Tile::isVisible() {
    return m_isVisible;
}

void Tile::setIsVisible(bool isVisible) {
    m_isVisible = isVisible;
}
