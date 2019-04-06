//
// Created by Eli Winkelman on 6/4/17.
//
#include <SFML/Graphics.hpp>
#include "../Entities/Entity.h"

#ifndef SUPERBERNIEBROS_BADGUY_H
#define SUPERBERNIEBROS_BADGUY_H

using namespace sf;

class Banker : public Entity {

public:

    int frame = 0, row = 2;

    void die() {
        //cause fall off screen
        collides = false;
    }

    void setScale() {
        sprite.setScale(2.11, 1.411);
    };
    void onCollisionWithTilesY() {
        if (collides) {
            sprite.move(0, -vel[1]);
            vel[1] = 0;
        }
    };

    void onCollisionWithTilesX() {
        if (collides) {
            sprite.move(-vel[0], 0);
            vel[0] = -vel[0];
        }
    }
    void onCollisionWithBankerY() {
        sprite.move(0, -vel[1]);
        vel[1] = 0;
    }
    void onCollisionWithBankerX() {
        sprite.move(-vel[0], 0);
        vel[0] = - vel[0];
    }
    void onCollisionWithX(Entity entity) {
        if(typeid(entity) == typeid(Banker)) {
            onCollisionWithBankerX();
        }
    }
    void onCollisionWithY(Entity entity) {
        if(typeid(entity) == typeid(Banker)) {
            onCollisionWithBankerY();
        }
    }
    //updates the sprite for walking animation
    void updateTextureRect(int frameCounter) {
        //change the frame every second for the animation
        if (frameCounter >= 60) {
            frame = (frame + 1) % 4;
        }
        if (vel[0] < 0) {
            row = 1;
        }
        if (vel[0] > 0) {
            row = 2;
        }
        if (!collides) {
            frame = 0;
        }
        sprite.setTextureRect(IntRect(34 * frame, 51 * row, 34, 51));
    }
};



#endif //SUPERBERNIEBROS_BADGUY_H
