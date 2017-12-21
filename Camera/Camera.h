//
// Created by Andre Driemeyer on 18/12/2017.
//

#ifndef UNTITLED_CAMERA_H
#define UNTITLED_CAMERA_H


#include <allegro5/haptic.h>

class Camera {

    public:
        Camera(float zoom, int x, int y, ALLEGRO_DISPLAY* screen);

        float zoom;
        int x;
        int y;
        ALLEGRO_DISPLAY* sreen;

};


#endif //UNTITLED_CAMERA_H
