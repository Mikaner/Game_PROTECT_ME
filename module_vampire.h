#include "Module.h"
#include "Id.h"
#ifndef CLASS_MODULE_VAMPIRE
#define CLASS_MODULE_VAMPIRE

typedef struct module_vampire
{
    Module module;
}Module_vampire;

void Module_vampire_construct(Module_vampire* const p_this, Id* p_id);
#endif