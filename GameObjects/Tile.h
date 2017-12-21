//
// Created by Andre Driemeyer on 18/12/2017.
//

#ifndef UNTITLED_TILE_H
#define UNTITLED_TILE_H


#include "MapObject.h"

class Tile: public MapObject {
public:
    Tile(float x, float y, BitmapPair *image, Camera *camera);


};


#endif //UNTITLED_TILE_H
