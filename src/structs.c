#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int red;
    int green;
    int blue;
    int a;
}Color;

typedef struct{
    double x;
    double y;
    double angle;
    double handling ;
    int step ;
    double lenth_of_tank ;
    double width_of_tank ;
    double tool_loole ;
    Color color;
    bool life;
    bool laser;
}Tank;

typedef struct {
double x;
double y;
double angle;
double speed;
bool life ;
double time;
double radius;
double old;
}Bullet;

typedef struct {
    bool rc; // true : row , false : colomn
    int x1;
    int y1;
    int x2;
    int y2;
    bool display;
}Wall;


typedef struct {
    int num;
    Wall wall_set[400] ;
    int max_x;
    int max_y;
    int map_x;
    int map_y;
    int map_size;
    int wall_width;
    Color main_color;
    Color first_color;
}Map;


typedef struct {
    bool tank1;
    bool tank2;
    int timelast;
    int time;
    int sc1;
    int sc2;
    bool win;
    int win_score;
}STATE;
