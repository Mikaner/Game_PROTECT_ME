#include "Module.h"
#include "Module_zombie.h"
#include "Id.h"


void Module_zombie_construct(Module_zombie* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_zombie, location_room, physical_weapon, 1, normal_power);
    ((Module*)p_this)->max_hitpoint = 120;
    ((Module*)p_this)->hitpoint = 120;
    ((Module*)p_this)->physical_resistance = 4;
}