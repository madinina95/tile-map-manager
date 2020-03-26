//
// Created by lionheart on 20/03/2020.
//

#ifndef MAPMANAGER_GAME_HPP
#define MAPMANAGER_GAME_HPP


#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "TileMapManager.hpp"

class Game {

public:
    Game();

    ~Game();

    void run();

private:
    void processEvents(sf::Event &event);

    void update(sf::Time dt);

    void render();

private:

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::Time m_timeSinceLastUpdate;
    sf::Time m_timePerFrame;
    TileMapManager m_tileMapManager;
    sf::View m_view;
};


#endif //MAPMANAGER_GAME_HPP
