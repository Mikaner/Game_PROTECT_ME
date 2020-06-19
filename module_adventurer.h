#include "Module.h"
#include "Id.h"
#ifndef CLASS_MODULE_ADVENTURER
#define CLASS_MODULE_ADVENTURER

typedef struct module_adventurer
{
    Module module;
}Module_adventurer;

void Module_adventurer_construct(Module_adventurer* const p_this, Id* p_id);
#endif