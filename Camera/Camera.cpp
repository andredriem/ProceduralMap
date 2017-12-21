//
// Created by Andre Driemeyer on 18/12/2017.
//

#include "Camera.h"

Camera::Camera(float zoom, int x, int y, ALLEGRO_DISPLAY* screen) {
    this->x = x;
    this->y = y;
    this->zoom = zoom;
    this->sreen = screen;
}
