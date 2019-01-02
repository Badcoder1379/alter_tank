//
// Created by asus on 24/12/2018.
//

#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>


void view_tank(SDL_Renderer* renderer, Tank* tank1);
void view_bullet(SDL_Renderer* renderer,Bullet* bullet_set);
void draw_map(SDL_Renderer *renderer, Map *map1);


#endif //PROJECT_VIEW_H
