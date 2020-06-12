#include "Module.h"
#ifndef CLASS_ROOM_H
#define CLASS_ROOM_H

typedef struct rooms {
    Module room[3];
    int flag;
}Rooms;

void Rooms_construct(Rooms* const p_this);

void Rooms_set_module(Rooms* const p_this, Module module, int posision);
void Rooms_set_flag(Rooms* const p_this);
int Rooms_get_flag(Rooms* const p_this);

#endif