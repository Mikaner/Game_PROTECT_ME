#include "Module.h"
#include "Id.h"
#ifndef CLASS_MODULE_BOSS
#define CLASS_MODULE_BOSS

typedef struct module_boss
{
    Module module;
}Module_boss;

void Module_boss_construct(Module_boss* const p_this, Id* p_id);
#endif