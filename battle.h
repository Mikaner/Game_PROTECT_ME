#include "Id.h"
#include "Stage.h"
#include "Module_adventurer.h"
#ifndef CLASS_BATTLE_H
#define CLASS_BATTLE_H

int battle_in_room(Stage* stage, Rooms* room, Module_adventurer* adventurer_group,  int room_pointer, int adventurer_pointer, long int length);
int battle(Stage* stage, Id* identification, long int length);

#endif