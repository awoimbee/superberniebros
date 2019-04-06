//
// Created by Eli Winkelman on 6/4/17.
//

#include <SFML/Graphics.hpp>
#include "../Tiles/Tiles.h"
#include "../Player/Player.h"
#include "../BadGuys/BadGuy.h"
#include "../Entities/Entity.h"
#include "../MoneyBagsBro/MoneyBagsBro.h"
#include "../MoneyBag/MoneyBag.h"
#include "../Level/Level.h"
#ifndef SUPERBERNIEBROS_GAME_H
#define SUPERBERNIEBROS_GAME_H
using namespace std;
class Game {
public:
    int currentLevel = 2;
    bool won = false;
    std::vector<Level> levels;
    double g;
    Text moneyCounter;
    Text shermanAntiTrustAct;
    int shermanAntiTrustActCounter = 0;
    float money = 0;
    Game(double gravity, const Texture &tileTexture, const Texture &badGuyTexture, const Texture &playerTexture, const Texture &coinTexture, const Texture &shermanAntiTrustActTexture, const Font &font,
         vector<vector<vector<vector<int>>>> levelTileArrayArray, vector<vector<vector<int>>> levelMonsterArrayArray,
         vector<vector<vector<int>>> levelMoneyBagsBroArrayArray, vector<vector<vector<int>>> levelBossArray, vector<vector<vector<int>>> levelCoinArrayArray, vector<vector<vector<int>>> levelShermanAntiTrustActArrayArray);
    void checkCoinCollection();
    void checkPowerUpCollection();
};

#endif //SUPERBERNIEBROS_GAME_H
