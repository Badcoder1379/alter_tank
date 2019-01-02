#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <time.h>
#include "structs.c"
#include "view.h"


void view_tank(SDL_Renderer* renderer,Tank* tank1){
Color color1;
color1=tank1->color;
    if(tank1->life==true) {
        filledCircleRGBA(renderer,
                         tank1->x,
                         tank1->y,
                         tank1->width_of_tank / 2,
                         0, 0, 0, 255
        );

        filledCircleRGBA(renderer,
                         tank1->x,
                         tank1->y,
                         tank1->width_of_tank / 2 - 5,
                         color1.red, color1.green, color1.blue, color1.a
        );
        thickLineRGBA(renderer,
                      tank1->x - cos(tank1->angle) * tank1->tool_loole / 3,
                      tank1->y - sin(tank1->angle) * tank1->tool_loole / 3,
                      tank1->x + cos(tank1->angle) * tank1->tool_loole * 3 / 4,
                      tank1->y + sin(tank1->angle) * tank1->tool_loole * 3 / 4,
                      tank1->width_of_tank / 4,
                      0, 0, 0, 255
        );

        thickLineRGBA(renderer,
                      tank1->x - cos(tank1->angle) * (tank1->tool_loole / 3 - 2),
                      tank1->y - sin(tank1->angle) * (tank1->tool_loole / 3 - 2),
                      tank1->x + cos(tank1->angle) * (tank1->tool_loole - 2) * 3 / 4,
                      tank1->y + sin(tank1->angle) * (tank1->tool_loole - 2) * 3 / 4,
                      tank1->width_of_tank / 4 - 5,
                      255, 255, 255, 255
        );
    }
}
void view_bullet(SDL_Renderer* renderer,Bullet* bullet_set){
int i;
    for (i = 0; i < 10; i++) {
        if(bullet_set[i].life==true){
            filledCircleRGBA(renderer,
                    bullet_set[i].x,
                    bullet_set[i].y,
                    bullet_set[i].radius,
                    0,0,0,255
                    );
        }
    }

}
void draw_map(SDL_Renderer *renderer, Map *map1) {
    SDL_Rect fillRect1 = {map1->map_x,map1->map_y,map1->max_x-map1->map_x,map1->max_y-map1->map_y};
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&fillRect1);
    for (int i = 0; i < map1->num; i++) {
        if(map1->wall_set[i].display==true) {
            int a,b,c,d;
            if(map1->wall_set[i].rc==true){
                a=0;b=-3;c=0;d=3;
            }
            else{
                a=-3;b=0;c=3;d=0;
            }
            thickLineRGBA(renderer,
                          map1->wall_set[i].x1+a,
                          map1->wall_set[i].y1+b,
                          map1->wall_set[i].x2+c,
                          map1->wall_set[i].y2+d,
                          map1->wall_width,
                          170, 51, 255, 255
            );
        }
    }
}


