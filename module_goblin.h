#include "Module.h"
#include "Id.h"
#ifndef CLASS_MODULE_GOBLIN
#define CLASS_MODULE_GOBLIN

typedef struct module_goblin
{
    Module module;
}Module_goblin;

void Module_goblin_construct(Module_goblin* const p_this, Id* p_id);
#endif