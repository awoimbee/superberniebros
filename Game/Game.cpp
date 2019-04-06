//
// Created by Eli Winkelman on 6/4/17.
//

#include "Game.h"
#include <iomanip> // setprecision
#include <sstream> // stringstream
using namespace std;
//Game class constructor, builds the game

Game::Game(double gravity, const Texture &tileTexture, const Texture &badGuyTexture, const Texture &playerTexture, const Texture &coinTexture, const Texture &shermanAntiTrustActTexture, const Font &font,
           vector<vector<vector<vector<int>>>> levelTileArrayArray, vector<vector<vector<int>>> levelMonsterArrayArray,
           vector<vector<vector<int>>> levelMoneyBagsBroArrayArray, vector<vector<vector<int>>> levelBossArray, vector<vector<vector<int>>> levelCoinArrayArray, vector<vector<vector<int>>> levelShermanAntiTrustActArrayArray) {
    g = gravity;
    moneyCounter.setFont(font);
    moneyCounter.setString("$" + to_string(0));
    moneyCounter.setColor(Color::Black);
    moneyCounter.setCharacterSize(100);
    moneyCounter.setPosition(10, 10);
    shermanAntiTrustAct.setFont(font);
    shermanAntiTrustAct.setString("SHERMAN ANTITRUST ACT!!");
    shermanAntiTrustAct.setColor(Color::Black);
    shermanAntiTrustAct.setCharacterSize(100);
    for (int i = 0; i < levelTileArrayArray.size(); i++) {
        levels.push_back(
                Level(.75, 16, levelTileArrayArray[i], levelMonsterArrayArray[i], levelMoneyBagsBroArrayArray[i], levelBossArray[i], levelCoinArrayArray[i], levelShermanAntiTrustActArrayArray[i],
                      tileTexture, badGuyTexture, playerTexture, coinTexture, shermanAntiTrustActTexture));
    }
}
void Game::checkCoinCollection() {

    for(int j = 0; j < levels[currentLevel].coins.size(); j++) {
        if (levels[currentLevel].player.playerSprite.getGlobalBounds().intersects(levels[currentLevel].coins[j] -> sprite.getGlobalBounds())) {
            money += 2.7;

            stringstream stream;
            stream << fixed << setprecision(2) << money;
            string s = stream.str();
            moneyCounter.setString("$" + s);
            levels[currentLevel].coins.erase(levels[currentLevel].coins.begin() + j);
            j--;
        }
    }

}
void Game::checkPowerUpCollection() {
    for(int j = 0; j < levels[currentLevel].powerUps.size(); j++) {
        if (levels[currentLevel].player.playerSprite.getGlobalBounds().intersects(levels[currentLevel].powerUps[j] -> sprite.getGlobalBounds())) {
            for(int i = 0; i < levels[currentLevel].entities.size(); i++) {
                if (levels[currentLevel].entities[i] -> sprite.getPosition().x > levels[currentLevel].view.getCenter().x-1000 && levels[currentLevel].entities[i] -> sprite.getPosition().x < levels[currentLevel].view.getCenter().x+1000) {
                    levels[currentLevel].entities[i] -> die();
                }
            }
            shermanAntiTrustActCounter = 20;
            shermanAntiTrustAct.setPosition(levels[currentLevel].view.getCenter().x-500, 20);
            levels[currentLevel].powerUps.erase(levels[currentLevel].powerUps.begin() + j);
            j--;
        }
    }
}
