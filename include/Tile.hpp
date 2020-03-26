//
// Created by lionheart on 21/03/2020.
//

#ifndef MAPMANAGER_TILE_HPP
#define MAPMANAGER_TILE_HPP


#include <Tmx.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

#include "Tileset.hpp"

class Tile : public sf::Drawable, public sf::Transformable {
public:
    Tile(const int &tileId, const sf::Vector2i &position, const Tileset &tileset);

    virtual ~Tile();

    sf::Vector2i getWorldPosition();

    virtual void update(sf::Time dt);

    virtual bool isAnimated();

    bool isVisible();

    void setIsVisible(bool isVisible);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void applyTexture(int x, int y, int spacing, int tilesetWidth, sf::Vector2i tileSize, int tileId);

protected:
    const int m_tileId;
    const sf::Vector2i m_position;
    const Tileset &m_tileSet;
    sf::VertexArray m_vertices;
    bool m_isVisible;
private:


};


#endif //MAPMANAGER_TILE_HPP
