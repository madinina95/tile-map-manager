//
// Created by lionheart on 21/03/2020.
//

#include "../include/Tileset.hpp"

Tileset::Tileset(int id, const std::string &path, const sf::Vector2i &tileSize, const sf::Vector2i &tilesetSize,
                 const int &spacing) :
        m_id(id),
        m_path(path),
        m_tileSize(tileSize),
        m_tilesetSize(tilesetSize),
        m_spacing(spacing),
        m_texture(new sf::Texture()){

    m_texture->loadFromFile(m_path);

}

Tileset::~Tileset() {

}
