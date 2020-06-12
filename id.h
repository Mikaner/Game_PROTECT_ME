#ifndef CLASS_ID_H
#define CLASS_ID_H

typedef struct id{
    int id;
}Id;

void Id_construct(Id* const p_this);
int Id_get_id(Id* const p_this);

#endif