#include "Room.h"
#include "Module.h"


void Rooms_construct(Rooms* const p_this){
    for(int i=0; i<3; i++){
        Module_init_construct(&(p_this->room[i]));
    }
    p_this->flag = 0;
}

void Rooms_set_module(Rooms* const p_this, Module module, int posision){
    p_this->room[posision] = module;
}

void Rooms_set_flag(Rooms* const p_this){
    p_this->flag = 1;
}

int Rooms_get_flag(Rooms* const p_this){
    return p_this->flag;
}