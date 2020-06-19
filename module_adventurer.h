#include "Module.h"
#include "Id.h"
#ifndef CLASS_MODULE_ADVENTURER
#define CLASS_MODULE_ADVENTURER

typedef struct module_adventurer
{
    Module module;
    int posision;
}Module_adventurer;

void Module_adventurer_construct(Module_adventurer* const p_this, Id* p_id);

void Module_physical_adventurer_construct(Module_adventurer* const p_this, Id* p_id);
void Module_magical_adventurer_construct(Module_adventurer* const p_this, Id* p_id);

void Module_adventurer_set_posision(Module_adventurer* const p_this, int posision);
int Module_adventurer_get_posision(Module_adventurer* const p_this);
#endif