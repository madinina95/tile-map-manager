//
// Created by lionheart on 22/03/2020.
//

#include "../include/AnimatedTile.hpp"

AnimatedTile::AnimatedTile(const int &tileId, const Tmx::Tile &tmxTile, const sf::Vector2i &position,
                           const Tileset &tileset) : PropertyTile(tileId, tmxTile, position, tileset),
                                                     m_tmxTile(tmxTile) {


    m_frameCount = m_tmxTile.GetFrameCount();
    m_totalDuration = m_tmxTile.GetTotalDuration();

    m_animation = std::make_shared<TileAnimation>(m_tmxTile.GetFrames());
    m_currentFrame = 0;

    m_elapsed = sf::Time::Zero;
    m_frameDuration = sf::seconds(0.15);

}

AnimatedTile::~AnimatedTile() {

}

void AnimatedTile::update(sf::Time dt) {
    m_elapsed += dt;
    if (m_elapsed > m_frameDuration) {
        m_elapsed -= m_frameDuration;
        ++m_currentFrame;
        if (m_currentFrame + 1 > m_frameCount) {
            m_currentFrame = 0;
        }
    }
    setFrame(m_currentFrame);
}

void AnimatedTile::setFrame(int currentFrame) {

    Tmx::AnimationFrame frame = m_animation->getFrame(currentFrame);
    m_frameDuration = sf::milliseconds(frame.GetDuration());

    Tile::applyTexture(m_position.x,
                       m_position.y,
                       m_tileSet.m_spacing,
                       m_tileSet.m_tilesetSize.x,
                       m_tileSet.m_tileSize,
                       frame.GetTileID()
    );
}

bool AnimatedTile::isAnimated() {
    return true;
}
