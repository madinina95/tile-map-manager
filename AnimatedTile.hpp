//
// Created by lionheart on 22/03/2020.
//

#ifndef MAPMANAGER_ANIMATEDTILE_HPP
#define MAPMANAGER_ANIMATEDTILE_HPP


#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "Tile.hpp"
#include "PropertyTile.hpp"
#include "TileAnimation.hpp"

class AnimatedTile : public PropertyTile {
public:
    AnimatedTile(const int &tileId, const Tmx::Tile &tmxTile, const sf::Vector2i &position, const Tileset &tileset);

    ~AnimatedTile();

    void update(sf::Time dt) override ;

    bool isAnimated() override;

private:
    void setFrame(int currentFrame);

private:
    const Tmx::Tile &m_tmxTile;
    int m_frameCount;
    int m_totalDuration;
    sf::Time m_frameDuration;
    sf::Time m_elapsed;
    int m_currentFrame;
    std::shared_ptr<TileAnimation> m_animation;
};


#endif //MAPMANAGER_ANIMATEDTILE_HPP
