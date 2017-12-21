//
// Created by Andre Driemeyer on 20/12/2017.
//

#include "TileBlock.h"
#include "../game_constants.h"


const float FREQUENCY = 3;
const float BLOCK_FREQUENCY = BLOCK_SIZE/FREQUENCY;



TileBlock::TileBlock(int tile_block_x, int tile_block_y, siv::PerlinNoise* perlin, BitmapPair* grass,
                         BitmapPair* ocean,BitmapPair* tree, Camera* camera){
    this->tile_block_x = tile_block_x;
    this->tile_block_y = tile_block_y;
    this->ocean = ocean;
    this->grass = grass;
    this->perlin = perlin;
    this->camera = camera;
    this->tree = tree;

    this->tile_block_map[std::make_tuple(tile_block_x,tile_block_y)] = this;

    this->generate_block();

}

void TileBlock::generate_block() {
    for(int i=0; i<BLOCK_SIZE; i++){
        std::vector<Tile*> temp_tile_vec;
        std::vector<Tree*> temp_tree_vec;
        for(int j=0; j<BLOCK_SIZE;j++){

            double noise =  this->perlin->noise( (i / BLOCK_FREQUENCY) + (this->tile_block_x *FREQUENCY), (j / BLOCK_FREQUENCY) + (this->tile_block_y *FREQUENCY));
            if (noise> -0.1 ) // arbitrary threshold
                temp_tile_vec.push_back(new Tile((i + (BLOCK_SIZE * this->tile_block_x))*TILE_SIZE,
                                            (j + (BLOCK_SIZE * this->tile_block_y))*TILE_SIZE, this->grass, this->camera));
            else
                temp_tile_vec.push_back(new Tile((i + (BLOCK_SIZE * this->tile_block_x))*TILE_SIZE,
                                            (j + (BLOCK_SIZE * this->tile_block_y))*TILE_SIZE, this->ocean, this->camera));


            if (noise > 0.3 ){ //arbitrary threshold
                temp_tree_vec.push_back(new Tree((i + (BLOCK_SIZE * this->tile_block_x))*TILE_SIZE,
                                                 (j + (BLOCK_SIZE * this->tile_block_y))*TILE_SIZE, this->tree, this->camera));
            } else
                temp_tree_vec.push_back(NULL);
        }
        this->block.push_back(temp_tile_vec);
        this->trees.push_back(temp_tree_vec);

    }

}

void TileBlock::draw() {
    for(int i=0; i<BLOCK_SIZE; i++){
        for(int j=0; j<BLOCK_SIZE;j++){
            this->block[i][j]->draw();
        }
    }

}

void TileBlock::draw_trees() {

    for(int j=0; j<BLOCK_SIZE;j++){
        for(int i=(int) BLOCK_SIZE-1; i>=0; i--){
            if(this->trees[i][j])
                this->trees[i][j]->draw();
        }
    }

}
