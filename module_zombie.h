#include "Module.h"
#include "Id.h"
#ifndef CLASS_MODULE_ZOMBIE
#define CLASS_MODULE_ZOMBIE

typedef struct module_zombie
{
    Module module;
}Module_zombie;

void Module_zombie_construct(Module_zombie* const p_this, Id* p_id);
#endif