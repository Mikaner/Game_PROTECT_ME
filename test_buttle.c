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

Module* set_adventurer(Id* identification){
    Module_adventurer adventurer;
    Module_adventurer_construct(&adventurer, identification);
    Module* m = (Module*)&adventurer;
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

int battle_in_room(Stage* stage, Rooms* room, Module** adventurer_group, int room_pointer){
    printf("in battle_in_room\n");
    int max_adventurer = sizeof adventurer_group / sizeof adventurer_group[0];
    int pointer = 0;
    Module* front = Stage_get_module(stage, room_pointer, 0);
    Module* middle = Stage_get_module(stage, room_pointer, 1);
    Module* back = Stage_get_module(stage, room_pointer, 2);
    while(Rooms_get_flag(room)==0 && pointer < max_adventurer){
        printf("Hi\n");
        if(Module_get_hitpoint(front)>0){
            if(Module_get_hitpoint(adventurer_group[pointer])>0){
                Module_be_attacked(front, adventurer_group[pointer]);
            }else{
                pointer++;
            }
            if(Module_get_hitpoint(front)>0)
                Module_be_attacked(adventurer_group[pointer], front);
            else{
                for (int i = pointer; i < max_adventurer; i++)
                {
                    Module_adventurer_set_posision((Module_adventurer*)adventurer_group[i], 2);
                }
            }
        }
        if(Module_get_hitpoint(middle)>0){
            printf("What's up?\n");
            if(Module_get_hitpoint(front)<=0){
                if(Module_get_hitpoint(adventurer_group[pointer])>0)
                    Module_be_attacked(middle, adventurer_group[pointer]);
                else
                    pointer++;
            }
            printf("Probably there is one error in here\n");
            if(Module_get_hitpoint(middle)>0 && 3-Module_adventurer_get_posision((Module_adventurer*)adventurer_group[pointer])<=Module_get_range(middle)){
                printf("Probably there is one error in here\n");
                Module_be_attacked(adventurer_group[pointer], middle);
            }
            printf("Probably there is one error in here\n");
            
            if(Module_get_hitpoint(middle)<=0){
                for (int i = pointer; i < max_adventurer; i++)
                {
                    Module_adventurer_set_posision((Module_adventurer*)adventurer_group[i], 3);
                }
            }
        }
        if(Module_get_hitpoint(back)>0){
            if(Module_get_hitpoint(front)<=0&&Module_get_hitpoint(middle)<=0){
                if(Module_get_hitpoint(adventurer_group[pointer])>0)
                    Module_be_attacked(back, adventurer_group[pointer]);
                else
                    pointer++;
            }
            if(Module_get_hitpoint(back)>0 && 4-Module_adventurer_get_posision((Module_adventurer*)adventurer_group[pointer])<=Module_get_range(back))
                Module_be_attacked(adventurer_group[pointer], back);
        }else{
            Rooms_set_flag(room);
        }
        printf("Hello?\n");
    }
    return pointer;
}

int battle(Stage* stage, Module** adventurer_group){
    printf("in battle\n");
    int max_room_num = 6;
    int adventurer_pointer = 0;
    int room_pointer = 0;
    int max_adventurer = sizeof adventurer_group / sizeof adventurer_group[0];
    while(room_pointer<max_room_num){
        Rooms* room = Stage_get_room(stage, room_pointer);
        adventurer_pointer = battle_in_room(stage, room, adventurer_group, room_pointer);
        if(adventurer_pointer<max_adventurer){
            printf("Hello\n");
            room_pointer++;
        }else{
            printf("hi\n");
            break;
        }
    }
    return room_pointer;
}

int main(){
    Id identification;
    Stage stage;
    init_game(&identification, &stage);
    set_up(&identification, &stage);
    printf("Success to set module to room in stage\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int id_num = Stage_get_module_id(&stage, i,j);
            printf("%d",id_num);
        }
    }
    printf("\n");

    Module* adventurer_group[2000];
    for (int i = 0; i < 2000; i++)
    {
        adventurer_group[i] = set_adventurer(&identification);
    }

    printf("Success to set adventurer\n");

    int cleared_room = battle(&stage, adventurer_group);
    printf("%d\n",cleared_room);
    printf("Success to battle\n");
    
    return 0;
}