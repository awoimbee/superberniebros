//
// Created by Eli Winkelman on 6/4/17.
//

#include "Player.h"
void Player::updateTextureRect() {

    if (frameCounter >= 60) {
        frame = frame < 4 ? frame + 1 : 1;
    }
    if (vel[0] < 0) {
        row = 0;
    }
    if (vel[0] > 0) {
        row = 1;
    }
    if (!canjump) {
        frame = 2;
    }
    if (vel[0] == 0) {
        frame = 0;
    }
    playerSprite.setTextureRect(IntRect(20 * frame, 25 * row, 20, 25));
}

void Player::init(const Texture &spriteSheet) {

    playerSprite.setTexture(spriteSheet);
    playerSprite.setPosition(100, 300);
    playerSprite.setTextureRect(IntRect(20 * frame, 25 * row, 20, 25));
    playerSprite.scale(3.5, 2.8);

}