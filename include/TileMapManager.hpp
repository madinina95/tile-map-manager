//
// Created by lionheart on 20/03/2020.
//

#ifndef MAPMANAGER_TILEMAPMANAGER_HPP
#define MAPMANAGER_TILEMAPMANAGER_HPP


#include <string>
#include <memory>
#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>
#include <Tmx.h>
#include "TileMap.hpp"

class TileMapManager : public sf::Drawable, public sf::Transformable{

public:
    TileMapManager();

    ~TileMapManager();

    void loadTileMap(const std::string& tmxFile);

    void clearTileMap();

    void update(sf::Time &dt);

    void setVisibleArea(sf::IntRect &visibleArea);

    std::string &getCurrentMap();

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:

    std::unique_ptr<TileMap> m_map;
    std::string m_cuurentMap;
};


#endif //MAPMANAGER_TILEMAPMANAGER_HPP
