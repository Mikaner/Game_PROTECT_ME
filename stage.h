#include "Module.h"
#include "Room.h"
#ifndef CLASS_STAGE_H
#define CLASS_STAGE_H

typedef struct stage{
    int stage_number;
    Rooms rooms[6];
    int cost;
}Stage;

void Stage_construct(Stage* const p_this, int stage_number, int stage_cost);

void Stage_set_module(Stage* const p_this, Module module, int room_num, int posision);

int Stage_get_module(Stage* const p_this, int room_num, int posision);

int Stage_get_last_room_flag(Stage* const p_this);

#endif