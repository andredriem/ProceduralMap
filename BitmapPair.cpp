//
// Created by Andre Driemeyer on 18/12/2017.
//

#include "BitmapPair.h"

BitmapPair::BitmapPair(ALLEGRO_BITMAP *bitmap, Camera* camera) {
    this->original = bitmap;
    this->bitmap = al_clone_bitmap(bitmap);
    this->camera = camera;
    this->bitmap_pair_list.push_back(this);

}

void BitmapPair::update() {

    ALLEGRO_BITMAP* current = al_get_target_bitmap();



    ALLEGRO_BITMAP* temp = al_create_bitmap(int(al_get_bitmap_width(this->original)*camera->zoom),
                                            int(al_get_bitmap_height(this->original)*camera->zoom));

    al_set_target_bitmap(temp);

    al_clear_to_color(al_map_rgba(0,0,0,0));

    al_draw_scaled_bitmap(this->original, //Source image
                          0,0, //Image center
                          al_get_bitmap_width(this->original),al_get_bitmap_height(this->original), //Image original dimensions
                          0,0, //New center
                          int(al_get_bitmap_width(this->original)*camera->zoom), int(al_get_bitmap_height(this->original)*camera->zoom), //new dimensions
                          0); // Flags


    al_destroy_bitmap(this->bitmap);
    this->bitmap = temp;

    al_set_target_bitmap(current);

}

BitmapPair::~BitmapPair() {
    al_destroy_bitmap(this->original);
    al_destroy_bitmap(this->bitmap);

}
