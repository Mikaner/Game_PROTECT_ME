#include <stdio.h>
#include "Module.h"
#include "Module_adventurer.h"
#include "Id.h"
#define num_of_adventurer 1
#define num_of_boss 2
#define num_of_skeleton 3
#define physical_weapon 0
#define magical_weapon 1
#define location_room 0
#define location_adventurer 1
#define normal_power 1
#define boss_power 5

void Module_adventurer_construct(Module_adventurer* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_adventurer, location_adventurer, physical_weapon, 1, normal_power);
    p_this->position = 0;
}

void Module_physical_adventurer_construct(Module_adventurer* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_adventurer, location_adventurer, physical_weapon, 1, normal_power);
    p_this->position = 0;
}

void Module_magical_adventurer_construct(Module_adventurer* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_adventurer, location_adventurer, magical_weapon, 1, normal_power);
    p_this->position = 0;
}

void Module_adventurer_set_position(Module_adventurer* const p_this, int position){
    p_this->position = position;
}

int Module_adventurer_get_position(Module_adventurer* const p_this){
    return p_this->position;
}