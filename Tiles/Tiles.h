//
// Created by Eli Winkelman on 6/4/17.
//
#include <SFML/Graphics.hpp>
#ifndef SUPERBERNIEBROS_TILES_H
#define SUPERBERNIEBROS_TILES_H
using namespace sf;
class Tile {
public:
    Texture texture;
    Sprite tile;
    Tile(int, int, int, int, const Texture &);
};


#endif //SUPERBERNIEBROS_TILES_H
