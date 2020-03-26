//
// Created by lionheart on 22/03/2020.
//

#ifndef MAPMANAGER_PROPERTYTILE_HPP
#define MAPMANAGER_PROPERTYTILE_HPP


#include "Tile.hpp"

class PropertyTile : public Tile {

public:
    PropertyTile(const int &tileId, const Tmx::Tile &tmxTile, const sf::Vector2i &position, const Tileset &tileset);

    virtual ~PropertyTile();

    virtual void update(sf::Time dt) override ;

    bool isAnimated() override;

private:
    void fillProperties();
private:
    const Tmx::Tile &m_tmxTile;
    std::unordered_map<std::string, std::string> m_properties;

};


#endif //MAPMANAGER_PROPERTYTILE_HPP
