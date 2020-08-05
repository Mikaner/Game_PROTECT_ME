#include "Module.h"
#include "Module_skeleton.h"
#include "Id.h"

void Module_skeleton_construct(Module_skeleton* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_skeleton, location_room, physical_weapon, 2, normal_power+8);
    ((Module*)p_this)->max_hitpoint = 80;
    ((Module*)p_this)->hitpoint = 80;
}