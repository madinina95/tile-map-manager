//
// Created by lionheart on 22/03/2020.
//

#include "../include/PropertyTile.hpp"

PropertyTile::PropertyTile(const int &tileId, const Tmx::Tile &tmxTile, const sf::Vector2i &position,
                           const Tileset &tileset) : Tile(tileId,position, tileset),
                           m_tmxTile(tmxTile){

    fillProperties();

}

PropertyTile::~PropertyTile() {

}

void PropertyTile::fillProperties() {

    for (const auto &property : m_tmxTile.GetProperties().GetList()) {
        m_properties.emplace(property.first,property.second);
    }
}

void PropertyTile::update(sf::Time dt) {
    Tile::update(dt);
}

bool PropertyTile::isAnimated() {
    return false;
}
