//
// Created by Andre Driemeyer on 18/12/2017.
//

#ifndef UNTITLED_BITMAPPAIR_H
#define UNTITLED_BITMAPPAIR_H

#include <allegro5/allegro.h>
#include <vector>
#include "Camera/Camera.h"


class BitmapPair {


public:
    ALLEGRO_BITMAP* bitmap;
    static std::vector<BitmapPair*> bitmap_pair_list;

    BitmapPair(ALLEGRO_BITMAP* bitmap, Camera* camera);
    void update();

    virtual ~BitmapPair();

private:
    Camera* camera;
    ALLEGRO_BITMAP* original;

};


#endif //UNTITLED_BITMAPPAIR_H
