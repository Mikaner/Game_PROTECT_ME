#include "Module.h"
#include "Module_goblin.h"
#include "Id.h"


void Module_goblin_construct(Module_goblin* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_goblin, location_room, physical_weapon, 1, (int)(normal_power/3)+1);
    ((Module*)p_this)->max_hitpoint = 165;
    ((Module*)p_this)->hitpoint = 165;
}