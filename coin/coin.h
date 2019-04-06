//
// Created by Eli Winkelman on 6/8/17.
//
#include "../Entities/Entity.h"
#include <SFML/Graphics.hpp>
#ifndef SUPERBERNIEBROS_COIN_H
#define SUPERBERNIEBROS_COIN_H


class Coin
{
public:
    int vel[2] = {0, 0};
    int frame = 0, row = 0;
    Sprite sprite;
    void updateTextureRect(int frameCounter) {
        if (frameCounter >= 60){
            frame = (frame+1)%5;
        }
        sprite.setTextureRect(IntRect(117*frame,200*row,117,200));
    };
    void onCollisionWithTilesY() {

            sprite.move(0, -vel[1]);
            vel[1] = 0;

    };

    void onCollisionWithTilesX() {

            sprite.move(-vel[0], 0);
            vel[0] = -vel[0];

    }
    //Coin(int, int, const Texture& texture);
};




#endif //SUPERBERNIEBROS_COIN_H
