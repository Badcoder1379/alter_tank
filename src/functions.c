#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <time.h>
#include <SDL2_gfxPrimitives.h>
#include "structs.c"
#include "functions.h"
bool click_m = false;
bool click_q = false;
double distance(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

void tank_set_place(Map* map1,Tank* tank1){
    int a=rand()%(map1->max_x-map1->map_x)+map1->map_x;
    tank1->x=a;
    int b=rand()%(map1->max_y-map1->map_y)+map1->map_y;
    tank1->y=b;
}
void creat_bullet(Tank* tank1 , Bullet* bullet_set){
    int i;
    for (i = 0; i < 5; ++i) {
        if (bullet_set[i].life==false)break;
        if(i==4)return;
    }


    bullet_set[i].life=true;
    bullet_set[i].x=tank1->x + (tank1->width_of_tank/2 + bullet_set[0].radius+1)*cos(tank1->angle) ;
    bullet_set[i].y=tank1->y +(tank1->width_of_tank/2 + bullet_set[0].radius+1)*sin(tank1->angle) ;
    bullet_set[i].angle=tank1->angle;
    bullet_set[i].time=0;
}
void physic_check(Map* map1,Tank* tank1){
        for (int j = 0; j < map1->num; j++) {
            if(map1->wall_set[j].rc==false){
                //row
                if(tank1->x>=map1->wall_set[j].x1 &&
                        tank1->x<=map1->wall_set[j].x2 &&
                       fabs(tank1->y-map1->wall_set[j].y1)<=(tank1->width_of_tank/2+2)){
                    if(tank1->y>map1->wall_set[j].y1)tank1->y+=tank1->step;
                    if(tank1->y<map1->wall_set[j].y1)tank1->y-=tank1->step;
                }
            }
            if(map1->wall_set[j].rc==true){
                //colomn
                if(tank1->y>=map1->wall_set[j].y1 &&
                   tank1->y<=map1->wall_set[j].y2 &&
                   fabs(tank1->x-map1->wall_set[j].x1)<=(tank1->width_of_tank/2+2)){
                    if(tank1->x>map1->wall_set[j].x1)tank1->x+=tank1->step;
                    if(tank1->x<map1->wall_set[j].x1)tank1->x-=tank1->step;                }
            }


        }

}

void move_tank(Tank* tank1) {


        const Uint8 *keyState = SDL_GetKeyboardState(NULL);

        if (keyState[SDL_SCANCODE_UP]){
                tank1->y += tank1->step*sin(tank1->angle);
                tank1->x += tank1->step*cos(tank1->angle);
            }
            if(keyState[SDL_SCANCODE_DOWN]){
                tank1->y -= tank1->step*sin(tank1->angle);
                tank1->x -= tank1->step*cos(tank1->angle);
            }
            if(keyState[SDL_SCANCODE_LEFT]){
                tank1->angle -= tank1->handling;
            }
            if(keyState[SDL_SCANCODE_RIGHT]){
                tank1->angle += tank1->handling;
            }


    }
void move_second_tank(Tank* tank2) {


    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_E]){
        tank2->y += tank2->step*sin(tank2->angle);
        tank2->x += tank2->step*cos(tank2->angle);
    }
    if(keyState[SDL_SCANCODE_D]){
        tank2->y -= tank2->step*sin(tank2->angle);
        tank2->x -= tank2->step*cos(tank2->angle);
    }
    if(keyState[SDL_SCANCODE_S]){
        tank2->angle -= tank2->handling;
    }
    if(keyState[SDL_SCANCODE_F]){
        tank2->angle += tank2->handling;
    }
}
void bullet_move(Bullet* bullet_set){
        for (int i = 0; i < 5; i++) {
            if(bullet_set[i].life==true){
                bullet_set[i].y += bullet_set[i].speed*sin(bullet_set[i].angle);
                bullet_set[i].x += bullet_set[i].speed*cos(bullet_set[i].angle);
                bullet_set[i].time++;
                if(bullet_set[i].time > bullet_set[i].old)bullet_set[i].life=false;
            }
        }
    }
bool handle_event(){
    SDL_Event e;
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT)
            return 0;
        return 1;
    }
int logic(Tank* tank1,Tank* tank2,Bullet* bullet_set, Bullet* bullet_set2){
        for (int i = 0; i<5 ; i++) {
            if(bullet_set[i].life==true &&
            distance(tank1->x,tank1->y,bullet_set[i].x,bullet_set[i].y)
            <bullet_set[0].radius + tank1->width_of_tank/2 -2){bullet_set[i].life=false;return 1; }

            if(bullet_set2[i].life==true &&
            distance(tank1->x,tank1->y,bullet_set2[i].x,bullet_set2[i].y)
            <bullet_set[0].radius + tank1->width_of_tank/2 -2){bullet_set2[i].life=false;return 1;}

            if(bullet_set[i].life==true &&
            distance(tank2->x,tank2->y,bullet_set[i].x,bullet_set[i].y)
            <bullet_set[0].radius + tank2->width_of_tank/2 -2){bullet_set[i].life=false; return 2;}

            if(bullet_set2[i].life==true &&
            distance(tank2->x,tank2->y,bullet_set2[i].x,bullet_set2[i].y)
            <bullet_set[0].radius + tank2->width_of_tank/2 -2){bullet_set2[i].life=false;return 2;}
        }
    return 0;
    }
void load_map(Map *map1) {
    srand(time(NULL));
    int r=rand() % 3;
    r++;


    int i;
    FILE * fptr;
    switch (r){
        case 1:
            fptr = fopen("map1.txt","r");
            break;
        case 2:
            fptr = fopen("map2.txt","r");
            break;
        case 3:
            fptr = fopen("map3.txt","r");
            break;
    }

    fscanf(fptr,"%d",&map1->num);
    int max_x=0,max_y=0;
    for(i=0;i<map1->num;i++){
        fscanf(fptr,"%d%d%d%d",
               &map1->wall_set[i].x1,
               &map1->wall_set[i].y1,
               &map1->wall_set[i].x2,
               &map1->wall_set[i].y2
               );
        map1->wall_set[i].display=true;


        if(map1->wall_set[i].x1==map1->wall_set[i].x2)
        {map1->wall_set[i].rc = true;}
        else
        {map1->wall_set[i].rc = false;}

        map1->wall_set[i].x1=map1->wall_set[i].x1*map1->map_size + map1->map_x;
        map1->wall_set[i].x2=map1->wall_set[i].x2*map1->map_size + map1->map_x;
        map1->wall_set[i].y1=map1->wall_set[i].y1*map1->map_size + map1->map_y;
        map1->wall_set[i].y2=map1->wall_set[i].y2*map1->map_size + map1->map_y;


        if(map1->wall_set[i].x1 > max_x)max_x=map1->wall_set[i].x1;
        if(map1->wall_set[i].x2 > max_x)max_x=map1->wall_set[i].x2;
        if(map1->wall_set[i].y1 > max_y)max_y=map1->wall_set[i].y1;
        if(map1->wall_set[i].y2 > max_y)max_y=map1->wall_set[i].y2;

        map1->num+=2;
        if(map1->wall_set[i].rc==true){
             i++;
             map1->wall_set[i].x1=map1->wall_set[i-1].x1-map1->wall_width/2-2;
             map1->wall_set[i].x2=map1->wall_set[i-1].x1+map1->wall_width/2+2;
             map1->wall_set[i].y1=map1->wall_set[i-1].y1+map1->wall_width/2;
             map1->wall_set[i].y2=map1->wall_set[i-1].y1+map1->wall_width/2;
             map1->wall_set[i].display=false;
             map1->wall_set[i].rc=false;
             i++;
             map1->wall_set[i].x1=map1->wall_set[i-2].x2-map1->wall_width/2-2;
             map1->wall_set[i].x2=map1->wall_set[i-2].x2+map1->wall_width/2+2;
             map1->wall_set[i].y1=map1->wall_set[i-2].y2-map1->wall_width/2;
             map1->wall_set[i].y2=map1->wall_set[i-2].y2-map1->wall_width/2;
             map1->wall_set[i].display=false;
            map1->wall_set[i].rc=false;

        }
        else{
             i++;
             map1->wall_set[i].y1=map1->wall_set[i-1].y1-map1->wall_width/2-2;
             map1->wall_set[i].y2=map1->wall_set[i-1].y1+map1->wall_width/2+2;
             map1->wall_set[i].x1=map1->wall_set[i-1].x1+map1->wall_width/2;
             map1->wall_set[i].x2=map1->wall_set[i-1].x1+map1->wall_width/2;
             map1->wall_set[i].display=false;
             map1->wall_set[i].rc=true;

            i++;
             map1->wall_set[i].y1=map1->wall_set[i-2].y2-map1->wall_width/2-2;
             map1->wall_set[i].y2=map1->wall_set[i-2].y2+map1->wall_width/2+2;
             map1->wall_set[i].x1=map1->wall_set[i-2].x2-map1->wall_width/2;
             map1->wall_set[i].x2=map1->wall_set[i-2].x2-map1->wall_width/2;
             map1->wall_set[i].display=false;
             map1->wall_set[i].rc=true;

        }

    }

    map1->max_x=max_x;
    map1->max_y=max_y;
}
void bullet_reflection(Map* map1,Bullet* bullet_set){

    // part1
    for (int i = 0; i <10 ; i++) {
        if (bullet_set[i].life==true){
            for (int j = 0; j < map1->num; j++) {
                if(map1->wall_set[j].rc==false && map1->wall_set[j].display==false){
                    //row
                    if(bullet_set[i].x>=map1->wall_set[j].x1 &&
                        bullet_set[i].x<=map1->wall_set[j].x2 &&
                        fabs(bullet_set[i].y-map1->wall_set[j].y1)<=(bullet_set[0].radius+1)){
                            bullet_set[i].angle*=(-1);
                            while (bullet_set[i].x>=map1->wall_set[j].x1 &&
                                   bullet_set[i].x<=map1->wall_set[j].x2 &&
                                   fabs(bullet_set[i].y-map1->wall_set[j].y1)<=(bullet_set[0].radius+1)){
                                bullet_set[i].y += bullet_set[i].speed*sin(bullet_set[i].angle);
                                bullet_set[i].x += bullet_set[i].speed*cos(bullet_set[i].angle);
                                bullet_set[i].time++;
                            }
                    }
                }
                if(map1->wall_set[j].rc==true && map1->wall_set[j].display==false){
                    //colomn
                    if(bullet_set[i].y>=map1->wall_set[j].y1 &&
                       bullet_set[i].y<=map1->wall_set[j].y2 &&
                       fabs(bullet_set[i].x - map1->wall_set[j].x1)<=(bullet_set[0].radius+1)){
                        bullet_set[i].angle=3.1415 -bullet_set[i].angle;
                        while(bullet_set[i].y>=map1->wall_set[j].y1 &&
                              bullet_set[i].y<=map1->wall_set[j].y2 &&
                              fabs(bullet_set[i].x - map1->wall_set[j].x1)<=(bullet_set[0].radius+1)){
                            bullet_set[i].y += bullet_set[i].speed*sin(bullet_set[i].angle);
                            bullet_set[i].x += bullet_set[i].speed*cos(bullet_set[i].angle);
                            bullet_set[i].time++;
                        }
                    }
                }


            }
        }
    }
//part2
    for (int i = 0; i <10 ; i++) {
        if (bullet_set[i].life == true) {
            for (int j = 0; j < map1->num; j++) {
                if (map1->wall_set[j].rc == false && map1->wall_set[j].display == true) {
                    //row
                    if (bullet_set[i].x >= map1->wall_set[j].x1 &&
                        bullet_set[i].x <= map1->wall_set[j].x2 &&
                        fabs(bullet_set[i].y - map1->wall_set[j].y1) <= (bullet_set[0].radius + 1)) {
                        bullet_set[i].angle *= (-1);
                        while (bullet_set[i].x >= map1->wall_set[j].x1 &&
                               bullet_set[i].x <= map1->wall_set[j].x2 &&
                               fabs(bullet_set[i].y - map1->wall_set[j].y1) <= (bullet_set[0].radius + 1)) {
                            bullet_set[i].y += bullet_set[i].speed * sin(bullet_set[i].angle);
                            bullet_set[i].x += bullet_set[i].speed * cos(bullet_set[i].angle);
                            bullet_set[i].time++;
                        }
                    }
                }
                if (map1->wall_set[j].rc == true && map1->wall_set[j].display == true) {
                    //colomn
                    if (bullet_set[i].y >= map1->wall_set[j].y1 &&
                        bullet_set[i].y <= map1->wall_set[j].y2 &&
                        fabs(bullet_set[i].x - map1->wall_set[j].x1) <= (bullet_set[0].radius + 1)) {
                        bullet_set[i].angle = 3.1415 - bullet_set[i].angle;
                        while (bullet_set[i].y >= map1->wall_set[j].y1 &&
                               bullet_set[i].y <= map1->wall_set[j].y2 &&
                               fabs(bullet_set[i].x - map1->wall_set[j].x1) <= (bullet_set[0].radius + 1)) {
                            bullet_set[i].y += bullet_set[i].speed * sin(bullet_set[i].angle);
                            bullet_set[i].x += bullet_set[i].speed * cos(bullet_set[i].angle);
                            bullet_set[i].time++;
                        }
                    }
                }


            }
        }
    }
//end
}
void tank1_def(Tank* tank1){
    tank1->angle = rand() % 628;
    tank1->handling = 0.12;
    tank1->step = 4;
    tank1->lenth_of_tank =16;
    tank1->width_of_tank =40;
    tank1->tool_loole = 26;
    tank1->color.red=180;tank1->color.green=0;tank1->color.blue=0;tank1->color.a=255;
    tank1->life=true;
};
void tank2_def(Tank* tank2){
    tank2->angle = rand() % 628;
    tank2->handling = 0.12;
    tank2->step = 4;
    tank2->lenth_of_tank =16;
    tank2->width_of_tank =40;
    tank2->tool_loole = 26;
    tank2->color.red=0;tank2->color.green=0;tank2->color.blue=180;tank2->color.a=255;
    tank2->life=true;
};
void bullet_def(Bullet* bullet_set){
    for(int i=0;i<5;i++){
        bullet_set[i].life = false;
        bullet_set[i].radius=5;
        bullet_set[i].old=300;
        bullet_set[i].speed = 5;
    }
}
void map_def(Map* map1){
    map1->map_x=30;
    map1->map_y=30;
    map1->map_size=80;
    map1->wall_width =2;
    map1->main_color.red=190;map1->main_color.green=198;map1->main_color.blue=198;map1->main_color.a=1;
    map1->first_color=map1->main_color;

}
void new_game(int a,STATE *state1,Map* map1,Tank* tank1,Tank* tank2, Bullet* bullet_set,Bullet* bullet_set2){
    int start_ticks = SDL_GetTicks();
    while (SDL_GetTicks() - start_ticks < 1000);
    if(a!=3){
        map1->main_color = (a==2)?tank1->color : tank2->color;
        if(a==2)state1->sc1++;
        if(a==1)state1->sc2++;
    }
    if(state1->sc1==state1->win_score || state1->sc2==state1->win_score)state1->win=true;
    if(a==3)map1->main_color=map1->first_color;
    for (int i = 0; i < 5; i++) {
        bullet_set[i].life=false;
        bullet_set2[i].life=false;
    }
    load_map(map1);
    tank_set_place(map1,tank1);
    tank_set_place(map1,tank2);
    tank1->life=true;
    tank2->life=true;
    state1->tank1=true;
    state1->tank2=true;
    state1->timelast=0;
}
void fire_tank1(Bullet* bullet_set,Tank* tank1){
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if(keyState[SDL_SCANCODE_M]){
        if(click_m==false) {
            creat_bullet(tank1, bullet_set);
            click_m = true;
        }
    } else{click_m=false;}
}
void fire_second_tank1(Bullet* bullet_set2,Tank* tank2){
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if(keyState[SDL_SCANCODE_Q]){
        if(click_q==false) {
            creat_bullet(tank2, bullet_set2);
            click_q = true;
        }
    } else{click_q=false;}
}
void state_def(STATE *state1){
    state1->sc1=0;
    state1->sc2=0;
    state1->tank1=true;
    state1->tank2=true;
    state1->timelast=0;
    state1->time=200;
    state1->win =false;
    state1->win_score=2;
}
void logic_handle(STATE *state1,Map* map1,Tank* tank1,Tank* tank2, Bullet* bullet_set,Bullet* bullet_set2) {
    int a = logic(tank1, tank2, bullet_set, bullet_set2);
    if (a > 0) {
        if (a == 1) {
            state1->tank1 = false;
            tank1->life = false;
            tank1->x = 2000;
            tank1->y = 2000;
            state1->timelast=0;
        }
        if (a == 2) {
            state1->tank2 = false;
            tank2->life = false;
            tank2->x = 2000;
            tank2->y = 2000;
            state1->timelast=0;

        }
    }

    if (state1->tank1 == false || state1->tank2 == false)state1->timelast++;

    if(state1->timelast>state1->time){
        int a=0;
        if(state1->tank1==false)a+=1;
        if(state1->tank2==false)a+=2;
        new_game(a,state1,map1,tank1,tank2,bullet_set,bullet_set2);
    }
}

int save(STATE *state1,Map* map1,Tank* tank1,Tank* tank2, Bullet* bullet_set,Bullet* bullet_set2){
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_ESCAPE]){

        // saving

        return 1;
    }
    return 0;
}