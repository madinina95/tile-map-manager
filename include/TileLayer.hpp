//
// Created by lionheart on 21/03/2020.
//

#ifndef MAPMANAGER_TILELAYER_HPP
#define MAPMANAGER_TILELAYER_HPP


#include <string>
#include <vector>
#include <memory>
#include <TmxLayer.h>
#include <Tmx.h>
#include <SFML/Graphics/Texture.hpp>

#include "Tile.hpp"
#include "PropertyTile.hpp"
#include "AnimatedTile.hpp"


class TileMap;

class TileLayer : public sf::Drawable, public sf::Transformable {
public:
    TileLayer(const Tmx::TileLayer &tmxLayer, const TileMap &map);

    ~TileLayer();

    int getWidth() const;

    int getHeight() const;

    std::string getName() const;

    bool isVisible() const;

    float getOpacity() const;

    int getZOrder() const;

    void buildTiles();

    void update(const sf::Time &dt);

    void setVisibleArea(const sf::IntRect &visibleArea);

    void setVisible(bool visible);

    bool isAnimated();


protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:

    const Tmx::TileLayer &m_tmxTileLayer;

    int m_width;
    int m_height;
    std::string m_name;
    bool m_isVisible;
    float m_opacity;
    int m_zOrder;
    sf::IntRect m_visibleArea;
    bool m_isAnimated;

    const TileMap &m_parent;

    std::vector<std::unique_ptr<Tile>> m_tiles;


};


#endif //MAPMANAGER_TILELAYER_HPP
