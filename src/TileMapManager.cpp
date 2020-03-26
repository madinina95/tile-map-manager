//
// Created by lionheart on 20/03/2020.
//

#include "../include/TileMapManager.hpp"

TileMapManager::TileMapManager() : m_map(new TileMap()) {}

TileMapManager::~TileMapManager() {

}

void TileMapManager::loadTileMap(const std::string& tmxFile) {

    m_cuurentMap = tmxFile;
    m_map->loadMap(tmxFile);

}

void TileMapManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    states.transform *= getTransform();
    target.draw(*m_map);

}

void TileMapManager::update(sf::Time &dt) {
    m_map->update(dt);

}

void TileMapManager::setVisibleArea(sf::IntRect &visibleArea) {
    m_map->setVisibleArea(visibleArea);
}

void TileMapManager::clearTileMap() {

    m_map = std::make_unique<TileMap>();

}

std::string &TileMapManager::getCurrentMap() {
    return m_cuurentMap;
}
