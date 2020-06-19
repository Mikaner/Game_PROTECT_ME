#include "Module.h"
#include "Module_adventurer.h"
#include "Id.h"
#define physical_weapon 0
#define magical_weapon 1
#define location_room 0
#define location_adventurer 1
#define normal_power 1
#define boss_power 5

void Module_adventurer_construct(Module_adventurer* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, location_adventurer, physical_weapon, 1, normal_power);
}