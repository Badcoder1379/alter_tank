//
// Created by asus on 24/12/2018.
//\

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "structs.c"
#include "functions.h"
#include "view.h"
#include <time.h>


#ifdef main
#undef main
#endif

int main(int argc, char *argv[]) {

    Tank *tank1 = malloc(sizeof(Tank));
    tank1_def(tank1);

    Tank *tank2 = malloc(sizeof(Tank));
    tank2_def(tank2);

    Bullet *bullet_set = malloc(10*sizeof(Bullet));
    bullet_def(bullet_set);

    Bullet *bullet_set2 = malloc(10*sizeof(Bullet));
    bullet_def(bullet_set2);

    Map* map1=malloc(sizeof(Map));
    map_def(map1);
    load_map(map1);

   tank_set_place(map1,tank1);
    tank_set_place(map1,tank2);


    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("ALTER_tank", 10, 10, 800, 600, SDL_WINDOW_MAXIMIZED);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    const double FPS = 90;
    int t=0;
    int *time=&t;
    bool al=false;
    bool* aloane=&al;

    while (handle_event()  ) {
        int start_ticks = SDL_GetTicks();
        move_tank(bullet_set,tank1);
        move_second_tank(bullet_set2,tank2);
        bullet_reflection(map1,bullet_set);
        bullet_reflection(map1,bullet_set2);
        bullet_move(bullet_set);
        bullet_move(bullet_set2);
        physic_check(map1,tank1);
        physic_check(map1,tank2);
        SDL_SetRenderDrawColor(renderer, map1->main_color.red, map1->main_color.green, map1->main_color.blue,map1->main_color.a);
        SDL_RenderClear(renderer);
        draw_map(renderer,map1);
        view_tank(renderer, tank1);
        view_tank(renderer, tank2);
        view_bullet(renderer,bullet_set);
        view_bullet(renderer,bullet_set2);
        SDL_RenderPresent(renderer);

        int state = logic(tank1,tank2,bullet_set,bullet_set2);
        if(state>0){t=0; logic_handle(&t,&al,state,map1,tank1,tank2,bullet_set,bullet_set2); }

        t++;
        if(t >200 && al==true){
            if(tank1->life==true){state=2;}else{state=1;}
            new_game(time,aloane,state,map1,tank1,tank2,bullet_set,bullet_set2);
        }
                    while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


