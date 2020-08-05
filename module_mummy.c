#include <stdlib.h>
#include "Module.h"
#include "Module_mummy.h"
#include "Id.h"


void Module_mummy_construct(Module_mummy* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_mummy, location_room, physical_weapon, 1, normal_power);
    ((Module*)p_this)->max_hitpoint = 100;
    ((Module*)p_this)->hitpoint = 100;
    ((Module*)p_this)->physical_resistance = rand()%8+1;
    ((Module*)p_this)->magic_resistance = rand()%9-4;
}