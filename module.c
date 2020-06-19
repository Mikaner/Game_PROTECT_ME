#include <stdio.h>
#include "Module.h"
#include "Id.h"

void Module_init_construct(Module* const p_this){
    p_this->id = 0;
    p_this->level = 0;
    p_this->levelup_base_cost = 0;
    p_this->hitpoint = 0;
    p_this->max_hitpoint = 0;
    p_this->location = 0;
    p_this->weapon = 0;
    p_this->range = 0;
    p_this->power = 0;
    p_this->physical_resistance = 0;
    p_this->magic_resistance = 0;
    p_this->physical_buff = 0;
    p_this->magical_buff = 0;
}

void Module_construct(Module* const p_this, Id* p_id,
                      int location, int weapon, int range, int power){
    p_this->id = Id_get_id(p_id);
    p_this->level = 1;
    p_this->levelup_base_cost = 5;
    p_this->hitpoint = 10;
    p_this->max_hitpoint = 10;
    p_this->location = location;
    p_this->weapon = weapon;
    p_this->range = range;
    p_this->power = power;
    p_this->physical_resistance = 0;
    p_this->magic_resistance = 0;
    p_this->physical_buff = 0;
    p_this->magical_buff = 0;
}

int Module_get_id(Module* const p_this){
    return p_this->id;
}
int Module_get_hitpoint(Module* const p_this){
    return p_this->hitpoint;
}
int Module_get_weapon(Module* const p_this){
    return p_this->weapon;
}
int Module_get_attack_power(Module* const p_this){
    return p_this->power;
}
int Module_get_range(Module* const p_this){
    return p_this->range;
}
int Module_get_physical_resistance(Module* const p_this){
    return p_this->physical_resistance;
}
int Module_get_magic_resistance(Module* const p_this){
    return p_this->magic_resistance;
}
int Module_get_physical_buff(Module* const p_this){
    return p_this->physical_buff;
}
int Module_get_magic_buff(Module* const p_this){
    return p_this->magical_buff;
}

void Module_be_attacked(Module* const p_this, Module* enemy){
    int weapon = Module_get_weapon(enemy);
    int power = Module_get_attack_power(enemy);
    if (weapon==0){
        p_this->hitpoint -= (power-p_this->physical_resistance);
    }else{
        p_this->hitpoint -= (power-p_this->magic_resistance);
    }
}