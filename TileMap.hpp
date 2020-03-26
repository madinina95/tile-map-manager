//
// Created by lionheart on 20/03/2020.
//

#ifndef MAPMANAGER_TILEMAP_HPP
#define MAPMANAGER_TILEMAP_HPP

#include <Tmx.h>
#include <SFML/Graphics/Texture.hpp>
#include "TileLayer.hpp"
#include "Tileset.hpp"

class TileMap : public sf::Drawable, public sf::Transformable{
public:
    TileMap();

    ~TileMap();

    void loadMap(std::string fileName);

    int getWidth() const;


    int getHeight() const;


    int getTileWidth() const;


    int getTileHeight() const;

    int getNbTilesets() const;

    int getNbLayers() const;

    Tileset &getTileSet(const int &id) const;

    virtual void update(sf::Time &dt);

    void setVisibleArea(sf::IntRect &visibleArea);


protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


private:
    void generateTilesetList(Tmx::Map &map);

    void buildLayer(const Tmx::Map &tmxMap);

    void loadTileset(const int &id,const std::string &path, const sf::Vector2i &tileSize, const sf::Vector2i &tilesetSize,
                     const int &spacing);

private:
    std::vector<std::unique_ptr<TileLayer>> m_tileLayers;

    int m_width;
    int m_height;
    int m_tileWidth;
    int m_tileHeight;
    int m_nbLayers;
    int m_nbTilesets;
    // La map contenant les ressources
    std::unordered_map<int, std::unique_ptr<Tileset>> m_tilesetsMap;

    sf::IntRect m_visibleArea;


};


#endif //MAPMANAGER_TILEMAP_HPP
