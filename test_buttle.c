#include <stdio.h>
#include "Id.h"
#include "Module.h"
#include "Module_skeleton.h"
#include "Module_boss.h"
#include "Module_adventurer.h"
#include "Room.h"
#include "Stage.h"

void init_game(Id* identification, Stage* stage){
    Id_construct(identification);
    Stage_construct(stage, 0, 20);
}

Module* set_skeleton(Id* identification){
    Module_skeleton skeleton;
    Module_skeleton_construct(&skeleton, identification);
    Module* m = (Module*)&skeleton;
    return m;
}

void set_up(Id* identification, Stage* stage){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Module* mod;
            mod = set_skeleton(identification);
            Stage_set_module(stage, *mod, i, j);
        }
    }
}

int main(){
    Id identification;
    Stage stage;
    init_game(&identification, &stage);
    set_up(&identification, &stage);
    printf("Success to set Module in stage\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int id_num = Stage_get_module(&stage, i,j);
            printf("%d",id_num);
        }
    }
    
    return 0;
}