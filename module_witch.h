#include "Module.h"
#include "Id.h"
#ifndef CLASS_MODULE_WITCH
#define CLASS_MODULE_WITCH

typedef struct module_witch
{
    Module module;
}Module_witch;

void Module_witch_construct(Module_witch* const p_this, Id* p_id);
#endif