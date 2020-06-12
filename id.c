#include "id.h"

void Id_construct(Id* const p_this){
    p_this->id = 0;
}

int Id_get_id(Id* const p_this){
    int tmp = p_this->id;
    p_this->id++;
    return tmp;
}