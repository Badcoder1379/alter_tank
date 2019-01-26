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
                a=0;b=-1;c=0;d=1;
            }
            else{
                a=-1;b=0;c=1;d=0;
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


void show_menu(SDL_Renderer *renderer,int i){
    Color color1,color2;
    color1.red=200;
    color1.blue=200;
    color1.green=200;
    color2.red=180;
    color2.blue=0;
    color2.green=0;
    int x=165;
    int y=80;
    int width =15;
    int lenth =100;
    int distance =7;
    thickLineRGBA(renderer,x,y,x+lenth,y,width,color1.red,color1.green,color1.blue,255);
    if(i%4==0){stringRGBA(renderer,(x*2+lenth)/(2) -20,y-3,"Resume",color2.red,color2.green,color2.blue,255);}
    else{stringRGBA(renderer,(x*2+lenth)/(2) -20,y-3,"Resume",0,0,0,255);}
    y+=distance+width;
    thickLineRGBA(renderer,x,y,x+lenth,y,width,color1.red,color1.green,color1.blue,255);
    if(i%4==1){stringRGBA(renderer,(x*2+lenth)/(2) -29,y-3,"New game",color2.red,color2.green,color2.blue,255);}
    else{stringRGBA(renderer,(x*2+lenth)/(2) -29,y-3,"New game",0,0,0,255);}
    y+=distance+width;
    thickLineRGBA(renderer,x,y,x+lenth,y,width,color1.red,color1.green,color1.blue,255);
    if(i%4==2){stringRGBA(renderer,(x*2+lenth)/(2) -26,y-3,"Setting",color2.red,color2.green,color2.blue,255);}
    else{stringRGBA(renderer,(x*2+lenth)/(2) -26,y-3,"Setting",0,0,0,255);}
    y+=distance+width;
    thickLineRGBA(renderer,x,y,x+lenth,y,width,color1.red,color1.green,color1.blue,255);
    if(i%4==3){stringRGBA(renderer,(x*2+lenth)/(2) -18,y-3,"Exit",color2.red,color2.green,color2.blue,255);}
    else{stringRGBA(renderer,(x*2+lenth)/(2) -15,y-3,"Exit",0,0,0,255);}
    y+=distance+width;
    stringRGBA(renderer,(x*2+lenth)/(2) -42,y-3,"Press space",0,0,0,255);

    SDL_RenderSetScale(renderer,3.5,3.5);

}

void show_score(SDL_Renderer *renderer,STATE *state1){
    int i;
    int fx=1450;
    int fy=50;
    int r=20;
    int dis=20;
    for(i=0;i<state1->win_score-state1->sc2;i++){
        filledCircleRGBA(renderer,fx,fy,r,0,0,0,255);
        filledCircleRGBA(renderer,fx,fy,r-2,200,0,0,255);
        fy+=dis+2*r;
    }
    fy=50;
    fx-=60;
    for(i=0;i<state1->win_score-state1->sc1;i++){
        filledCircleRGBA(renderer,fx,fy,r,0,0,0,255);
        filledCircleRGBA(renderer,fx,fy,r-2,0,0,200,255);
        fy+=dis+2*r;
    }

}