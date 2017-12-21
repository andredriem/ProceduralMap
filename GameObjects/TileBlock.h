//
// Created by Andre Driemeyer on 20/12/2017.
//

#ifndef UNTITLED_TILEBLOCK_H
#define UNTITLED_TILEBLOCK_H

#include <map>
#include <tuple>
#include <vector>
#include "Tile.h"
#include "../PerlinNoise.hpp"
#include "Tree.h"


class TileBlock {

public:
    static std::map<std::tuple<int,int>,TileBlock*> tile_block_map;
    static int global_x_min;
    static int global_y_min;
    static int global_x_max;
    static int global_y_max;


    TileBlock(int tile_block_x, int tile_block_y, siv::PerlinNoise* perlin, BitmapPair* grass,
              BitmapPair* ocean, BitmapPair* tree, Camera* camera);
    void draw();
    void draw_trees();

    int tile_block_x;
    int tile_block_y;
    std::vector<std::vector<Tile*>> block;
    BitmapPair* ocean;
    BitmapPair* grass;
    BitmapPair* tree;
    siv::PerlinNoise* perlin;
    Camera* camera;
    std::vector<std::vector<Tree*>> trees;

private:
    void generate_block();

};


#endif //UNTITLED_TILEBLOCK_H
