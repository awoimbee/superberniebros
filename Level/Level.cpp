//
// Created by Eli Winkelman on 6/7/17.
//
#include "../coin/coin.h"
#include "Level.h"
//
// Created by Eli Winkelman on 6/4/17.
//

#include "Level.h"

//Level class constructor, builds the level
Level::Level(double gravity, double terminalVelocity, std::vector<std::vector<std::vector<int>>> levelArray, std::vector<std::vector<int>> levelBankerArray, std::vector<std::vector<int>> levelMoneyBagsBroArray, std::vector<std::vector<int>> levelBossArray, std::vector<std::vector<int>> levelCoinArray, std::vector<std::vector<int>> levelShermanAntiTrustActVector, const Texture &texture, const Texture &badGuyTexture, const Texture &playerTexture, const Texture &coinTexture, const Texture &shermanAntiTrustActTexture) {
    terminalVel = terminalVelocity;
    player.init(playerTexture);
    view.reset(FloatRect(0, 0, 2000, 1000));
    int xpos = 0, ypos = 0;
    for (int i = 0; i < levelArray.size(); i++) {
        for (int j = 0; j < levelArray[i].size(); j++) {
            if (!levelArray[i][j].empty()) {
                Tile tile(xpos, ypos, levelArray[i][j][0], levelArray[i][j][1], texture);
                tiles.push_back(tile.tile);
            }
            ypos += 72;
        }
        xpos += 72;
        ypos = 0;
    }

    for (int i = 0; i < levelBankerArray.size(); i++) {
        entities.push_back(new Banker());
        entities[i] -> setPosition(levelBankerArray[i][0], levelBankerArray[i][1]);
        entities[i] -> setVelocity(-2, 0);
        entities[i] -> setTexture(badGuyTexture);
        entities[i] -> setScale(2, 1.4);
    }

    for (int j = 0; j < levelMoneyBagsBroArray.size(); j++) {
        entities.push_back(new MoneyBagsBro());
        entities[j+levelBankerArray.size()] -> setPosition(levelMoneyBagsBroArray[j][0], levelMoneyBagsBroArray[j][1]);
        entities[j+levelBankerArray.size()] -> setVelocity(1, 0);
        entities[j+levelBankerArray.size()] -> setScale(.5, .5);
    }
    for (int i = 0; i < levelBossArray.size(); i++) {
        entities.push_back(new Boss());
        entities[i+levelBankerArray.size()+levelMoneyBagsBroArray.size()] -> setPosition(levelBossArray[i][0], levelBossArray[i][1]);
    }
   for (int i = 0; i < levelCoinArray.size(); i++) {
       coins.push_back(new Coin());
       coins[i] -> sprite.setPosition(levelCoinArray[i][0], levelCoinArray[i][1]);
       coins[i] -> sprite.setTexture(coinTexture);
       coins[i] -> sprite.setScale(.5, .5);
   }
    for (int i = 0; i < levelShermanAntiTrustActVector.size(); i++) {
        powerUps.push_back(new ShermanAntiTrustPowerUp());
        powerUps[i] -> sprite.setPosition(levelShermanAntiTrustActVector[i][0], levelShermanAntiTrustActVector[i][1]);
        powerUps[i] -> sprite.setTexture(shermanAntiTrustActTexture);
        powerUps[i] -> sprite.setScale(.5, .5);
        powerUps[i] -> sprite.setTextureRect(IntRect(0, 0, 200, 200));
    }
    g = gravity;
};

void Level::Restart(std::vector<std::vector<int>> levelBankerArray, std::vector<std::vector<int>> levelMoneyBagsBroArray, std::vector<std::vector<int>> levelBossArray, std::vector<std::vector<int>> levelCoinArray, const Texture &badGuyTexture, const Texture &playerTexture, const Texture &coinTexture) {
    entities.clear();
    player.playerSprite.setPosition(100,300);
    player.collides = true;
    player.vel[1] = 0;
    player.vel[0] = 0;
    player.frameCounter = 0;
    view.reset(FloatRect(0, 0, 2000, 1000));
    int xpos = 0, ypos = 0;

    for (int i = 0; i < levelBankerArray.size(); i++) {
        entities.push_back(new Banker());
        entities[i] -> setPosition(levelBankerArray[i][0], levelBankerArray[i][1]);
        entities[i] -> setVelocity(-2, 0);
        entities[i] -> setTexture(badGuyTexture);
        entities[i] -> setScale(2, 1.4);
    }

    for (int j = 0; j < levelMoneyBagsBroArray.size(); j++) {
        entities.push_back(new MoneyBagsBro());
        entities[j+levelBankerArray.size()] -> setPosition(levelMoneyBagsBroArray[j][0], levelMoneyBagsBroArray[j][1]);
        entities[j+levelBankerArray.size()] -> setVelocity(1, 0);
        entities[j+levelBankerArray.size()] -> setScale(.5, .5);
    }


    for (int i = 0; i < levelBossArray.size(); i++) {
        entities.push_back(new Boss());
        entities[i+levelBankerArray.size()+levelMoneyBagsBroArray.size()] -> setPosition(levelBossArray[i][0], levelBossArray[i][1]);
    }
    for (int i = 0; i < levelCoinArray.size(); i++) {
        coins.push_back(new Coin());
        coins[i] -> sprite.setPosition(levelCoinArray[i][0], levelCoinArray[i][1]);
        coins[i] -> sprite.setTexture(coinTexture);
        coins[i] -> sprite.setScale(.5, .5);
    }


};
void Level::activateMonsters() {

    for (int i = 0; i < entities.size(); i++) {
        if (entities[i] -> sprite.getPosition().x < view.getCenter().x + 1010) {
            entities[i] -> activated = true;
        }
    }

}

void Level::Physics(const Texture &moneyBagTexture, const Texture &chickenNugget, int level) {
    //Player Physics
    player.updateTextureRect();

    //gravity and terminal velocity
    if (player.vel[1] < terminalVel) {
        player.vel[1] += g;
    } else {
        player.vel[1] = terminalVel;
    }

    //move in y direction
    player.playerSprite.move(0, player.vel[1]);

    //set jumping to false by default
    player.canjump = false;
    //jump off monster
    if (player.killCountdown < 0) {
        player.canjump = true;
        player.killCountdown--;
    }
    //check y collisions
    if (player.collides) {
        //check tile collisions
        for (int i = 0; i < tiles.size(); i++) {
            if (player.playerSprite.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
                player.playerSprite.move(0, -player.vel[1]);
                player.vel[1] = 0;
                if (player.vel[1] <= 0) {
                    player.canjump = true;
                }

            }
        }
        //check entity collisions
        for (int i = 0; i < entities.size(); i++) {
            if (player.playerSprite.getGlobalBounds().intersects(entities[i] -> sprite.getGlobalBounds())) {

                    if (player.vel[1] > 0) {
                        entities[i]->die();
                        player.canjump = true;
                        player.killCountdown = 4;
                        player.collides = true;
                        player.vel[1] = -10;
                        player.playerSprite.move(0, player.vel[1]);
                    } else if (player.vel[1] < 0) {
                        player.collides = false;
                        entities[i]->collides = true;
                        player.playerSprite.move(0, -1);
                        player.vel[0] = -player.vel[0];
                    }

            }
        }
    }

    player.playerSprite.move(player.vel[0], 0);
    if (player.playerSprite.getPosition().x < 0 ) {
        player.playerSprite.move(-player.vel[0], 0);
    }

    if (player.collides) {
        for (int i = 0; i < tiles.size(); i++) {
            if (player.playerSprite.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
                player.playerSprite.move(-player.vel[0], 0);
                player.vel[0] = -player.vel[0];
            }
        }
        for (int i = 0; i < entities.size(); i++) {
            if (player.playerSprite.getGlobalBounds().intersects(entities[i] -> sprite.getGlobalBounds())) {

                    player.collides = false;
                    entities[i] -> collides = true;
                    player.playerSprite.move(0, -1);
                    player.vel[0] = -player.vel[0];


            }
        }
    }
    if (player.vel[0] == 0) {
        player.playerSprite.move(1, 0);
        for (int i = 0; i < tiles.size(); i++) {
            if (player.playerSprite.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
                player.playerSprite.move(-player.vel[0], 0);
                player.vel[0] = -player.vel[0];
            }
        }
        for (int i = 0; i < entities.size(); i++) {
            if (player.playerSprite.getGlobalBounds().intersects(entities[i] -> sprite.getGlobalBounds())) {

                    player.collides = false;
                    entities[i] -> collides = true;
                    player.playerSprite.move(0, -1);
                    player.vel[0] = -player.vel[0];


            }
        }
        player.playerSprite.move(-2, 0);
        for (int i = 0; i < tiles.size(); i++) {
            if (player.playerSprite.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
                player.playerSprite.move(-player.vel[0], 0);
                player.vel[0] = -player.vel[0];
            }
        }
        for (int i = 0; i < entities.size(); i++) {
            if (player.playerSprite.getGlobalBounds().intersects(entities[i] -> sprite.getGlobalBounds())) {

                    player.collides = false;
                    entities[i] -> collides = true;
                    player.playerSprite.move(0, -2);
                    player.vel[0] = -player.vel[0];

            }
        }
        player.playerSprite.move(1, 0);
    }
    //Monster Physics

    for (int j = 0; j < entities.size(); j++) {
        //set velocities for monsters in loops
        if (entities[j] -> activated) {
            entities[j] -> setVelocity(secondCounter);

            if (entities[j] -> isThrowingMoney && player.frameCounter % 60 == 0){

                newMoneyBag(entities[j] -> sprite.getPosition().x, entities[j] -> sprite.getPosition().y, -1);
                if (level == 3) {
                    entities[entities.size()-1] -> setTexture(chickenNugget);
                }
                else {
                    entities[entities.size()-1] -> setTexture(moneyBagTexture);
                    entities[entities.size()-1] -> setScale(.25, .25);
                }
                entities[entities.size()-1] -> setVelocity(-5, -20);
                entities[j] -> isThrowingMoney = false;

            }
            //gravity
            if (entities[j] -> hasGravity) {
                entities[j] -> vel[1] += g;
            }

            //move in the y direction
            entities[j] -> sprite.move(0, entities[j] -> vel[1]);

            //check collisions with tiles
            for (int i = 0; i < tiles.size(); i++) {
                if (entities[j] -> sprite.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
                    entities[j] -> onCollisionWithTilesY();
                }
            }
            //check collisions with other entities
            for (int i = 0; i < entities.size(); i++) {
                if (entities[j] -> sprite.getGlobalBounds().intersects(entities[i] -> sprite.getGlobalBounds()) && i != j) {
                    entities[j] -> onCollisionWithY(*entities[i]);
                }
            }

            //move in the x direction

            entities[j] -> sprite.move(entities[j] -> vel[0], 0);
            //Check tile collisions
            for (int i = 0; i < tiles.size(); i++) {
                if (entities[j] -> sprite.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
                    entities[j] -> onCollisionWithTilesX();
                }
            }
            for (int i = 0; i < entities.size(); i++) {
                if (entities[j] -> sprite.getGlobalBounds().intersects(entities[i] -> sprite.getGlobalBounds()) && j != i) {
                    entities[j] -> onCollisionWithX(*entities[i]);
                }
            }
        }
    }
}

void Level::HandleKeypresses(Keyboard keyboard) {
    //handles all key presses in the game (player, menu, etc.)
    if (keyboard.isKeyPressed(Keyboard::Left)) {
        player.vel[0] = -5;
    }
    if (keyboard.isKeyPressed(Keyboard::Right)) {
        player.vel[0] = 5;
    }
    if (keyboard.isKeyPressed(Keyboard::Up)) {
        if (player.canjump) {
            player.vel[1] = -20;
        }
    }
    if (keyboard.isKeyPressed(Keyboard::LShift)) {
        player.vel[0] = player.vel[0] * 2;
    }
    if ((!keyboard.isKeyPressed(Keyboard::Right) && !keyboard.isKeyPressed(Keyboard::Left)) ||
        (keyboard.isKeyPressed(Keyboard::Right) && keyboard.isKeyPressed(Keyboard::Left))) {
        player.vel[0] = 0;
    }

}
void Level::newMoneyBag(int x, int y, int dir) {
    entities.push_back(new MoneyBag());
    entities[entities.size()-1] -> setPosition(x, y);
}
