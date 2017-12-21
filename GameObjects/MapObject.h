//
// Created by Andre Driemeyer on 18/12/2017.
//

#ifndef UNTITLED_MAPOBJECT_H
#define UNTITLED_MAPOBJECT_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "../Camera/Camera.h"
#include "../BitmapPair.h"


class MapObject {




public:
    float x, y;
    BitmapPair*  image;
    float w,h;
    Camera* camera;

    //Functions
    MapObject(float x, float y, BitmapPair *image, Camera *camera);
    int draw();
};


#endif //UNTITLED_MAPOBJECT_H
