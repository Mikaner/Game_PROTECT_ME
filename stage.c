#include "Stage.h"
#include "Room.h"
#include "Module.h"

void Stage_construct( Stage* const p_this, int stage_number, int stage_cost){
    p_this->stage_number=stage_number;
    p_this->cost=stage_cost;
    for(int i=0; i<6; i++){
        Rooms_construct(&(p_this->rooms[i]));
    }
}

void Stage_set_module(Stage* const p_this, Module module, int room_num, int posision){
    Rooms_set_module(&(p_this->rooms[room_num]), module, posision);
}

int Stage_get_module(Stage* const p_this, int room_num, int posision){
    Rooms* room = &(p_this->rooms[room_num]);
    Module mod = room->room[posision];
    return Module_get_id(&mod);
}

int Stage_get_last_room_flag(Stage* const p_this){
    return Rooms_get_flag(&(p_this->rooms[5]));
}