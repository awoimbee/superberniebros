//
// Created by Eli Winkelman on 6/4/17.
//

//This is the entity abstract class, it should hold things that all entities have in common

#include <SFML/Graphics.hpp>

#ifndef SUPERBERNIEBROS_ENTITY_H
#define SUPERBERNIEBROS_ENTITY_H

using namespace sf;


class Entity {
public:
    //entity velocity vector
        int lives = 0;
        float vel[2] = {0, 0};
    //true if entity should collide with stuff (set to false to fall off screen for death or something)
        bool collides = true,
    activated = false,
    isThrowingMoney = false,
    hasGravity = true;
    //Run on death of entity
    virtual void die() {

    };
    virtual void init() {

    };

    virtual void setTexture(const Texture& texture) {
        sprite.setTexture(texture);
    }
    virtual void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }
    virtual void setVelocity(float xvel, float yvel) {
        vel[0] = xvel;
        vel[1] = yvel;
    }
    virtual void setScale(float xscale, float yscale) {
        sprite.setScale(xscale, yscale);
    }
     //most (but not all) entities need to update their texture rect for movement animations
    virtual void updateTextureRect(int) {

    };
    virtual void onCollisionWithTilesY() {

    };
    virtual void onCollisionWithTilesX() {

    };
    virtual void onCollisionWithBankerY() {

    }
    virtual void onCollisionWithBankerX() {

    }
    virtual void onCollisionWithX(Entity entity) {

    };
    virtual void onCollisionWithY(Entity entity) {

    }
    virtual void setVelocity(int gameSecondCounter) {

    }
    //All entities have some sprite
    Sprite sprite;
    /*//Check x and y collisions for entities separately (for different actions)
        virtual bool checkXCollisions() = 0;
        virtual bool checkYCollisions() = 0;
    //What to do in different types of collisions

        virtual void onCollisionWithBanker() = 0;
        virtual void onCollisionWithMoneyBagBro() = 0;


    //initiation function to set position, textures, etc.

    //function to move the entity on every loop run
        virtual void move() = 0;

        */
};


#endif //SUPERBERNIEBROS_ENTITY_H
