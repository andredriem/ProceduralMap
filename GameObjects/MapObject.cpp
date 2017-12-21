//
// Created by Andre Driemeyer on 18/12/2017.
//

#include <allegro5/allegro.h>
#include "MapObject.h"
#include "../game_constants.h"

MapObject::MapObject(float x, float y, BitmapPair *image, Camera *camera) {
    this->x = x;
    this->y = y;
    this->image = image;
    this->camera = camera;
}

int MapObject::draw() {

    al_draw_bitmap(this->image->bitmap,
                   ((this->x - this->camera->x)*this->camera->zoom ) + SCREEN_W/2,
                   ((this->y - this->camera->y)*this->camera->zoom ) + SCREEN_H/2,
                   0);

    return 1;
}
