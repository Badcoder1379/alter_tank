#ifndef PROJECT_FUNCS_H
#define PROJECT_FUNCS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
bool handle_event();
void tank_set_place(Map* map1,Tank* tank1);
void bullet_move(Bullet* bullet_set);
void move_tank(Tank* tank1);
void move_second_tank(Tank* tank1);
void load_map(Map *map1);
void bullet_reflection(Map* map1,Bullet* bullet_set);
void physic_check(Map* map1,Tank* tank1);
int logic(Tank* tank1,Tank* tank2,Bullet* bullet_set, Bullet* bullet_set2);
void logic_handle(STATE *state1,Map* map1,Tank* tank1,Tank* tank2, Bullet* bullet_set,Bullet* bullet_set2);
void tank1_def(Tank* tank1);
void tank2_def(Tank* tank1);
void bullet_def(Bullet* bullet_set);
void map_def(Map* map1);
void new_game(int a,STATE *state1,Map* map1,Tank* tank1,Tank* tank2, Bullet* bullet_set,Bullet* bullet_set2);
void fire_tank1(Bullet* bullet_set,Tank* tank1);
void fire_second_tank1(Bullet* bullet_set2,Tank* tank2);
void state_def(STATE *state1);
int save(STATE *state1,Map* map1,Tank* tank1,Tank* tank2, Bullet* bullet_set,Bullet* bullet_set2);
#endif //PROJECT_FUNCS_H