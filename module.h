#include "Id.h"
#ifndef CLASS_MODULE_H
#define CLASS_MODULE_H
#define num_of_adventurer 1
#define num_of_boss 2
#define num_of_skeleton 3
#define num_of_zombie 4
#define num_of_witch 5
#define num_of_goblin 6
#define num_of_mummy 7
#define num_of_vampire 8
#define physical_weapon 0
#define magical_weapon 1
#define location_room 0
#define location_adventurer 1
#define normal_power 16
#define boss_power 64

typedef struct module{
    int id;
    int module_num;
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
void Module_construct(Module* const p_this, Id* p_id, int module_num, int location, int weapon, int range, int power);

int Module_get_id(Module* const p_this);
int Module_get_num(Module* const p_this);
int Module_get_hitpoint(Module* const p_this);
int Module_get_max_hitpoint(Module* const p_this);
int Module_get_weapon(Module* const p_this);
int Module_get_attack_power(Module* const p_this);
int Module_get_range(Module* const p_this);
int Module_get_physical_resistance(Module* const p_this);
int Module_get_magic_resistance(Module* const p_this);
int Module_get_physical_buff(Module* const p_this);
int Module_get_magic_buff(Module* const p_this);

void Module_be_attacked(Module* const p_this, Module* enemy);

#endif