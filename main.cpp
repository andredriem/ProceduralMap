#include <stdio.h>
#include <vector>
#include <allegro5/allegro.h>
#include <iostream>
#include "GameObjects/MapObject.h"
#include "game_constants.h"
#include "PerlinNoise.hpp"
#include <allegro5/allegro_native_dialog.h>
#include "GameObjects/TileBlock.h"




std::vector<BitmapPair*>  BitmapPair::bitmap_pair_list;
std::map<std::tuple<int,int>,TileBlock*> TileBlock::tile_block_map;


int main(int argc, char **argv){
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *main_character_bitmap = NULL;
    ALLEGRO_BITMAP* grass_bitmap = NULL;
    ALLEGRO_BITMAP* ocean_bitmap = NULL;


    srand((unsigned int) time(0));
    siv::PerlinNoise* perlin = new siv::PerlinNoise((uint32_t) rand());
    bool redraw = true;
    Camera* camera = new Camera(1,(BLOCK_SIZE/2)*TILE_SIZE,(BLOCK_SIZE/2)*TILE_SIZE, display);

    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }


    if(!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }

    main_character_bitmap = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);

    al_set_target_bitmap(main_character_bitmap);
    al_clear_to_color(al_map_rgb(255,0,0));
    al_set_target_bitmap(al_get_backbuffer(display));

    BitmapPair* main_character_pair = new BitmapPair(main_character_bitmap,camera);
    grass_bitmap = al_load_bitmap("assets/grass.png");

    BitmapPair* green_tile_pair = new BitmapPair(grass_bitmap, camera);
    ocean_bitmap = al_load_bitmap("assets/water.png");
    BitmapPair* blue_tile_pair = new BitmapPair(ocean_bitmap, camera);
    BitmapPair* tree = new BitmapPair(al_load_bitmap("assets/tree.png"),camera);


    MapObject* main_character= new MapObject(camera->x,camera->y,main_character_pair,camera);

    TileBlock* main_tile_block = new TileBlock(0,0,perlin,green_tile_pair,blue_tile_pair,tree, camera);


    event_queue = al_create_event_queue();
    if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    if(!al_install_mouse()){
        fprintf(stderr, "failed to detect some kind of mouse input!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    if(!al_install_keyboard()){
        fprintf(stderr, "failed to detect some kind of keyboard input!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }



    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();

    al_start_timer(timer);


    std::map<std::tuple<int,int>,TileBlock*>::iterator map_iterator;


    while(1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
            if(ev.mouse.dz > 0){
                camera->zoom *= 2;
            }
            else if(ev.mouse.dz < 0) {
                camera->zoom /= 2;
            }

            if(camera->zoom < MIN_ZOOM)
                camera->zoom = MIN_ZOOM;

            if(camera->zoom > MAX_ZOOM)
                camera->zoom = MAX_ZOOM;

            if(ev.mouse.dz != 0){
                for(int i = 0;BitmapPair::bitmap_pair_list.size() > i; i++){
                    BitmapPair::bitmap_pair_list[i]->update();
                }

            }

        }

        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    camera->y -= TILE_SIZE;
                    main_character->y = camera->y;
                    break;
                case ALLEGRO_KEY_DOWN:
                    camera->y += TILE_SIZE;
                    main_character->y = camera->y;
                    break;
                case ALLEGRO_KEY_LEFT:
                    camera->x -= TILE_SIZE;
                    main_character->x = camera->x;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    camera->x += TILE_SIZE;
                    main_character->x = camera->x;
                    break;
                default:
                    break;
            }

            int temp_x = camera->x / TILE_SIZE;
            int temp_y = camera->y / TILE_SIZE;
            if(temp_x<0)
                temp_x -= BLOCK_SIZE;
            if(temp_y<0)
                temp_y -= BLOCK_SIZE;

            int block_coordinate_x = int(temp_x / BLOCK_SIZE);
            int block_coordinate_y = int(temp_y / BLOCK_SIZE);


            if(TileBlock::tile_block_map.find(std::make_tuple(block_coordinate_x,block_coordinate_y)) == TileBlock::tile_block_map.end()){
                new TileBlock(block_coordinate_x,block_coordinate_y,perlin,green_tile_pair,blue_tile_pair,tree,camera);
            }


        }


        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0,0,0));

            for(map_iterator = TileBlock::tile_block_map.begin(); map_iterator != TileBlock::tile_block_map.end(); map_iterator++){
                map_iterator->second->draw();
            }

            main_character->draw();

            for(map_iterator = TileBlock::tile_block_map.begin(); map_iterator != TileBlock::tile_block_map.end(); map_iterator++){
                map_iterator->second->draw_trees();
            }

            al_flip_display();


        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    //There are some allegro that must be deleted manually in those objects. (I think)
    delete green_tile_pair;
    delete blue_tile_pair;
    delete main_character_pair;


    return 0;
}