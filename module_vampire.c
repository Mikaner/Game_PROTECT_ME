#include <stdlib.h>
#include "Module.h"
#include "Module_vampire.h"
#include "Id.h"


void Module_vampire_construct(Module_vampire* const p_this, Id* p_id){
    Module_construct((Module*)p_this, p_id, num_of_vampire, location_room, physical_weapon, 2, normal_power);
    ((Module*)p_this)->max_hitpoint = rand()%200+1;
    ((Module*)p_this)->hitpoint = rand()%200+1;
    ((Module*)p_this)->power = rand()%50+1;
    ((Module*)p_this)->physical_resistance = rand()%16+1;
    ((Module*)p_this)->magic_resistance = rand()%16-4;
}