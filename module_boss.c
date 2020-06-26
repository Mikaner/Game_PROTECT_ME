#include "Module.h"
#include "Module_boss.h"
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

void Module_boss_construct(Module_boss* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_boss, location_room, magical_weapon, 3, boss_power);
    ((Module*)p_this)->max_hitpoint = 40;
    ((Module*)p_this)->hitpoint = 40;
    ((Module*)p_this)->magic_resistance = 1;
}