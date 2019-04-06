//
// Created by Eli Winkelman on 6/7/17.
//
#include <SFML/Graphics.hpp>
#include "../Tiles/Tiles.h"
#include "../ShermanAntiTrustActPowerup/ShermanAntiTrustPowerUp.h"
#include "../Player/Player.h"
#include "../BadGuys/BadGuy.h"
#include "../Entities/Entity.h"
#include "../coin/coin.h"
#include "../MoneyBagsBro/MoneyBagsBro.h"
#include "../MoneyBag/MoneyBag.h"
#include "../JPMorgan/JPMorgan.h"
#ifndef SUPERBERNIEBROS_LEVEL_H
#define SUPERBERNIEBROS_LEVEL_H


class Level {
public:

    std::vector<sf::Sprite> tiles;
    Player player;
    sf::View view;
    std::vector<Entity*> entities;
    std::vector<Coin*> coins;
    std::vector<ShermanAntiTrustPowerUp*> powerUps;
    double g, terminalVel;
    int secondCounter = 0;
    Level(double, double, std::vector<std::vector<std::vector<int>>> levelArray, std::vector<std::vector<int>> monsterLevelArray, std::vector<std::vector<int>>, std::vector<std::vector<int>> levelBossArray, std::vector<std::vector<int>> coinArray, std::vector<std::vector<int>> shermanAntiTrustActArray, const Texture &texture, const Texture &badGuyTexture, const Texture &playerTexture, const Texture &coinTexture, const Texture &shermanAntiTrustTexture);
    void Physics(const Texture &moneyBagTexture, const Texture &chickenNugget, int level);
    void newMoneyBag(int x, int y, int dir);
    void Restart(std::vector<std::vector<int>> monsterLevelArray, std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::vector<std::vector<int>> coinArray, const Texture &badGuyTexture, const Texture &playerTexture, const Texture &coinTexture);
    void activateMonsters();
    void HandleKeypresses(sf::Keyboard keyboard);
};


#endif //SUPERBERNIEBROS_LEVEL_H
