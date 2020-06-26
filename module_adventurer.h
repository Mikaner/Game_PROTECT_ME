#include "Module.h"
#include "Id.h"
#ifndef CLASS_MODULE_ADVENTURER
#define CLASS_MODULE_ADVENTURER

typedef struct module_adventurer
{
    Module module;
    int position;
}Module_adventurer;

void Module_adventurer_construct(Module_adventurer* const p_this, Id* p_id);

void Module_physical_adventurer_construct(Module_adventurer* const p_this, Id* p_id);
void Module_magical_adventurer_construct(Module_adventurer* const p_this, Id* p_id);

void Module_adventurer_set_position(Module_adventurer* const p_this, int position);
int Module_adventurer_get_position(Module_adventurer* const p_this);
#endif