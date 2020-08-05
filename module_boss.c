#include "Module.h"
#include "Module_boss.h"
#include "Id.h"

void Module_boss_construct(Module_boss* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_boss, location_room, magical_weapon, 3, boss_power);
    ((Module*)p_this)->max_hitpoint = 255;
    ((Module*)p_this)->hitpoint = 255;
    ((Module*)p_this)->physical_resistance = 8;
    ((Module*)p_this)->magic_resistance = 4;
}