#include <stdio.h>
#include <stdlib.h>
#include "Module.h"
#include "Module_adventurer.h"
#include "Id.h"

void Module_adventurer_construct(Module_adventurer* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_adventurer, location_adventurer, physical_weapon, 1, normal_power);
    int hp = rand()%100+1;
    p_this->position = 0;
    ((Module*)p_this)->power = rand()%50+1;
    ((Module*)p_this)->max_hitpoint = hp;
    ((Module*)p_this)->hitpoint = hp;
    ((Module*)p_this)->magic_resistance = rand()%5;
    ((Module*)p_this)->physical_resistance = rand()%4+1;
}

void Module_physical_adventurer_construct(Module_adventurer* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_adventurer, location_adventurer, physical_weapon, 1, normal_power);
    p_this->position = 0;
    ((Module*)p_this)->power = normal_power+12;
    ((Module*)p_this)->physical_resistance = 8;
}

void Module_magical_adventurer_construct(Module_adventurer* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_adventurer, location_adventurer, magical_weapon, 1, normal_power);
    p_this->position = 0;
    ((Module*)p_this)->power = normal_power+12;
    ((Module*)p_this)->physical_resistance = 4;
    ((Module*)p_this)->magic_resistance = 6;
}

void Module_adventurer_set_position(Module_adventurer* const p_this, int position){
    p_this->position = position;
}

int Module_adventurer_get_position(Module_adventurer* const p_this){
    return p_this->position;
}