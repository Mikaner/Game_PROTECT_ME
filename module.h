#include "Id.h"
#ifndef CLASS_MODULE_H
#define CLASS_MODULE_H

typedef struct module{
    int id;
    int location;
    int level;
    int levelup_base_cost;
    int hitpoint;
    int max_hitpoint;
    int weapon;
    int power;
    int range;
    int physical_resistance;
    int magic_resistance;
    int physical_buff;
    int magical_buff;
}Module;

void Module_init_construct( Module* const p_this);
void Module_construct(Module* const p_this, Id* p_id, int location, int weapon, int range, int power);

int Module_get_id(Module* const p_this);
int Module_get_hitpoint(Module* const p_this);
int Module_get_weapon(Module* const p_this);
int Module_get_attack_power(Module* const p_this);
int Module_get_range(Module* const p_this);
int Module_get_physical_resistance(Module* const p_this);
int Module_get_magic_resistance(Module* const p_this);
int Module_get_physical_buff(Module* const p_this);
int Module_get_magic_buff(Module* const p_this);

void Module_be_attacked(Module* const p_this,int weapon, int power);

#endif