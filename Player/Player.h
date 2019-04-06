//
// Created by Eli Winkelman on 6/4/17.
//
#include <SFML/Graphics.hpp>
#ifndef SUPERBERNIEBROS_PLAYER_H
#define SUPERBERNIEBROS_PLAYER_H

using namespace sf;

class Player {

public:
    Sprite playerSprite;
    float vel[2] = {0, 0};
    bool canjump = false;
    int killCountdown = 0;
    int frame = 1, row = 0;
    int frameCounter = 0;
    bool collides = true;

    void init(const Texture &spriteSheet);

    void updateTextureRect();
};


#endif //SUPERBERNIEBROS_PLAYER_H
