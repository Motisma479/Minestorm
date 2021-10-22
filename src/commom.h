#pragma once


#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT    800

#define PLAYER_ANGULAR_SPEED 360
#define ANGULAR_FRICTION  200
//#define ENEMY_CAPACITY 10
#define BULLET_CAPACITY 64
#define ENEMY_COUNT 20


/*
DestRect : Magnetic Mine
Rectangle rect = { texture->width/2.0f,texture->width /4.0f,texture->width/4.0f,texture->height/2.0f};
DestRect : Floating Mine
Rectangle rect = { texture->width,texture->width /4.0f,texture->width/4.0f,texture->height/2.0f};
*/