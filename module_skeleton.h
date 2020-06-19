#include "Module.h"
#include "Id.h"
#ifndef CLASS_MODULE_SKELETON
#define CLASS_MODULE_SKELETON

typedef struct module_skeleton
{
    Module module;
}Module_skeleton;

void Module_skeleton_construct(Module_skeleton* const p_this, Id* p_id);
#endif