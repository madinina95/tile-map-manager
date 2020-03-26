//
// Created by lionheart on 24/03/2020.
//

#ifndef MAPMANAGER_TILEANIMATION_HPP
#define MAPMANAGER_TILEANIMATION_HPP


#include <Tmx.h>

class TileAnimation {
public:
    TileAnimation(const std::vector<Tmx::AnimationFrame> &frames);

    ~TileAnimation();

    const Tmx::AnimationFrame &getFrame(int frame);

private:
    std::vector<Tmx::AnimationFrame> m_frames;

};


#endif //MAPMANAGER_TILEANIMATION_HPP
