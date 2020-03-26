//
// Created by lionheart on 21/03/2020.
//

#ifndef MAPMANAGER_TILESET_HPP
#define MAPMANAGER_TILESET_HPP


#include <string>
#include <memory>
/* SFML */
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>

class Tileset {
public:
    Tileset(int id,const std::string &path, const sf::Vector2i &tileSize, const sf::Vector2i &tilesetSize, const int &spacing );

    ~Tileset();

public:
    std::string m_path;
    const sf::Vector2i m_tileSize;
    const sf::Vector2i m_tilesetSize;
    const int m_spacing;
    std::unique_ptr<sf::Texture> m_texture;
    int m_id;

};


#endif //MAPMANAGER_TILESET_HPP
