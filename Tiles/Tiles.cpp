//
// Created by Eli Winkelman on 6/4/17.
//

#include "Tiles.h"
Tile::Tile(int x, int y, int textureFrame, int textureRow, const Texture &texture) {

    tile.setTexture(texture);
    //current tiles are 72 x 72, ours might be a different size, this will need to be changed
    tile.setTextureRect(IntRect(72 * textureFrame, 72 * textureRow, 72, 72));

    tile.setPosition(x, y);
}