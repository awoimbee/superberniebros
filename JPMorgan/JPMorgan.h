//
// Created by Eli Winkelman on 6/13/17.
//
#include <stdlib.h>
#include "../Entities/Entity.h"
#ifndef SUPERBERNIEBROS_JPMORGAN_H
#define SUPERBERNIEBROS_JPMORGAN_H



class Boss : public Entity {

    void die() {
        //cause fall off screen
        collides = false;
    }
    void setVelocity(int gameCounter) {
        srand(time(NULL));
        if(collides) {
            isThrowingMoney = false;
            int cycleCounter = gameCounter % 240;

            if (cycleCounter == 60 || cycleCounter == 180) {
                vel[1] = -15;
            }
            if (cycleCounter <= 5 && cycleCounter >= 0) {
                vel[0] = -15;
            }
            else if (cycleCounter <= 65 && cycleCounter >= 60) {
                vel[0] = 15;
            }
            else {
                vel[0] = rand() %31 -15;
            }
            if (gameCounter % 10 == 0 && ((cycleCounter > 5 && cycleCounter < 60) || cycleCounter > 65)) {
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

};


#endif //SUPERBERNIEBROS_JPMORGAN_H
