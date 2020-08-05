#include "Module.h"
#include "Module_witch.h"
#include "Id.h"


void Module_witch_construct(Module_witch* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_witch, location_room, magical_weapon, 3, normal_power-2);
    ((Module*)p_this)->max_hitpoint = 80;
    ((Module*)p_this)->hitpoint = 80;
    ((Module*)p_this)->physical_resistance = 4;
    ((Module*)p_this)->magic_resistance = 16;
}