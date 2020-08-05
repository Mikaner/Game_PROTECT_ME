#include "Module.h"
#include "Id.h"
#ifndef CLASS_MODULE_MUMMY
#define CLASS_MODULE_MUMMY

typedef struct module_mummy
{
    Module module;
}Module_mummy;

void Module_mummy_construct(Module_mummy* const p_this, Id* p_id);
#endif