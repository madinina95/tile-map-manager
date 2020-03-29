//
// Created by lionheart on 20/03/2020.
//

#include "../include/Game.hpp"

Game::Game() : m_timeSinceLastUpdate(sf::Time::Zero),
               m_timePerFrame(sf::seconds(0)) {

    m_window.create(sf::VideoMode(800, 600), "Tile Map Manager");
    m_timePerFrame =  sf::seconds(1.f / 60.f);
    m_window.setFramerateLimit(60);

    m_tileMapManager.loadTileMap(std::string("../map/example.tmx"));

    m_view.setCenter(sf::Vector2f(400.f, 300.f));
    m_view.setSize(sf::Vector2f(800.f, 600.f));

    m_window.setView(m_view);
    sf::IntRect visibleArea;
    visibleArea.top = m_view.getCenter().y - 50 - m_view.getSize().y / 2;
    visibleArea.left = m_view.getCenter().x - 50 - m_view.getSize().x / 2;
    visibleArea.height = m_view.getSize().y + 50;
    visibleArea.width = m_view.getSize().x + 50;
    m_tileMapManager.setVisibleArea(visibleArea);

}

Game::~Game() {

}

void Game::run() {
    while (m_window.isOpen()) {
        sf::Event event;
        bool repaint = false;
        processEvents(event);
        sf::Time elapsedTime = m_clock.restart();
        m_timeSinceLastUpdate += elapsedTime;
        while (m_timeSinceLastUpdate > m_timePerFrame) {
            m_timeSinceLastUpdate -= m_timePerFrame;
            update(m_timePerFrame);
            repaint = true;
        }
        if (repaint) {
            render();
        }
    }
}

void Game::processEvents(sf::Event &event) {
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::Right) {
                m_view.move(5, 0);
                updateVisibleArea();
                m_tileMapManager.getLayer(std::string("grass")).setVisible(true);
                m_window.setView(m_view);
            }
            if(event.key.code == sf::Keyboard::Left) {
                m_view.move(-5, 0);
                updateVisibleArea();
                m_tileMapManager.getLayer(std::string("grass")).setVisible(false);
                m_window.setView(m_view);
            }
            if(event.key.code == sf::Keyboard::Up) {
                m_view.move(0, -5);
                updateVisibleArea();
                m_window.setView(m_view);
            }
            if(event.key.code == sf::Keyboard::Down) {
                m_view.move(0, 5);
                updateVisibleArea();
                m_window.setView(m_view);
            }
        }
    }
}

void Game::update(sf::Time dt) {
    m_tileMapManager.update(dt);
}

void Game::render() {
    m_window.clear();
    m_tileMapManager.drawTo(2);
    m_window.draw(m_tileMapManager);
    // draw the player if you want
    // apply other layers
    m_tileMapManager.drawFrom(3);
    m_window.draw(m_tileMapManager);
    m_window.display();
}

void Game::updateVisibleArea() {
    // la vue change alors on la set
    sf::IntRect visibleArea;
    visibleArea.top = m_view.getCenter().y - 50 - m_view.getSize().y / 2;
    visibleArea.left = m_view.getCenter().x - 50 - m_view.getSize().x / 2;
    visibleArea.height = m_view.getSize().y + 50;
    visibleArea.width = m_view.getSize().x + 50;

    m_tileMapManager.setVisibleArea(visibleArea);
}
