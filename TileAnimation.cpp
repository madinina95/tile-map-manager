//
// Created by lionheart on 24/03/2020.
//

#include "TileAnimation.hpp"

TileAnimation::TileAnimation(const std::vector<Tmx::AnimationFrame> &frames) : m_frames(frames) {

}

TileAnimation::~TileAnimation() {

}

const Tmx::AnimationFrame &TileAnimation::getFrame(int frame) {
    return m_frames[frame];
}