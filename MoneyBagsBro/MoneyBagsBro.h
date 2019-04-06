//
// Created by Eli Winkelman on 6/5/17.
//
#include "../Entities/Entity.h"
#ifndef SUPERBERNIEBROS_MONEYBAGSBRO_H
#define SUPERBERNIEBROS_MONEYBAGSBRO_H


class MoneyBagsBro : public Entity {

public:

    void die() {
        //cause fall off screen
        collides = false;
    }
    void setVelocity(int gameCounter) {
        if(collides) {
            isThrowingMoney = false;
            int cycleCounter = gameCounter % 120;

            if (cycleCounter == 0 || cycleCounter == 60) {
                vel[1] = -15;
            }
            if (cycleCounter <= 5 && cycleCounter >= 0) {
                vel[0] = -5;
            }
            else if (cycleCounter <= 65 && cycleCounter >= 60) {
                vel[0] = 5;
            }
            else {
                vel[0] = 0;
            }
            if (gameCounter % 15 == 0 && ((cycleCounter > 5 && cycleCounter < 60) || cycleCounter > 65)) {
                isThrowingMoney = true;
            }
            else {
                isThrowingMoney = false;
            }

        }

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
    void onCollisionWithX(Entity entity) {

    }
    void onCollisionWithY(Entity entity) {

    }
    void updateTextureRect(int counter) {

    }
    //updates the sprite for walking animation

};


#endif //SUPERBERNIEBROS_MONEYBAGSBRO_H
