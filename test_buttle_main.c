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
/*
Module* set_skeleton(Id* identification){
    Module_skeleton skeleton;
    Module_skeleton_construct(&skeleton, identification);
    Module* m = (Module*)&skeleton;
    return m;
}
*/

void set_up(Id* identification, Stage* stage){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Module* skeleton = Stage_get_module(stage, i, j);
            Module_skeleton_construct((Module_skeleton*)skeleton, identification);
            Stage_set_module(stage, *skeleton, i, j);
        }
    }
}

int battle_in_room(Stage* stage, Rooms* room, Module_adventurer* adventurer_group,  int room_pointer, int adventurer_pointer, long int length){
    printf("Buttle in Room %d\n", room_pointer+1);
    long int max_adventurer = length;
    printf("max_adventurer: %ld\n", max_adventurer);
    int pointer = adventurer_pointer;
    Module* front = Stage_get_module(stage, room_pointer, 0);
    Module* middle = Stage_get_module(stage, room_pointer, 1);
    Module* back = Stage_get_module(stage, room_pointer, 2);
    while(Rooms_get_flag(room)==0 && pointer < max_adventurer){
        if(Module_get_hitpoint(front)>0){
            if(Module_get_hitpoint((Module*)&adventurer_group[pointer])>0){
                Module_be_attacked(front, (Module*)&adventurer_group[pointer]);
            }else{
                pointer++;
                if(pointer>=max_adventurer) break;
            }
            if(Module_get_hitpoint(front)>0){
                Module_be_attacked((Module*)&adventurer_group[pointer], front);
            }else{
                for (int i = pointer; i < max_adventurer; i++)
                {
                    Module_adventurer_set_posision(&adventurer_group[i], 2);
                }
            }
        }
        if(Module_get_hitpoint(middle)>0){
            if(Module_get_hitpoint(front)<=0){
                if(Module_get_hitpoint((Module*)&adventurer_group[pointer])>0){
                    Module_be_attacked(middle, (Module*)&adventurer_group[pointer]);
                }else{
                    pointer++;
                    if(pointer>=max_adventurer) break;
                }
            }
            if(Module_get_hitpoint(middle)>0 && 3-Module_adventurer_get_posision(&adventurer_group[pointer])<=Module_get_range(middle)){
                Module_be_attacked((Module*)&adventurer_group[pointer], middle);
            }
            
            if(Module_get_hitpoint(middle)<=0){
                for (int i = pointer; i < max_adventurer; i++)
                {
                    Module_adventurer_set_posision(&adventurer_group[i], 3);
                }
            }
        }
        if(Module_get_hitpoint(back)>0){
            if(Module_get_hitpoint(front)<=0&&Module_get_hitpoint(middle)<=0){
                if(Module_get_hitpoint((Module*)&adventurer_group[pointer])>0){
                    Module_be_attacked(back, (Module*)&adventurer_group[pointer]);
                }else{
                    pointer++;
                    if(pointer>=max_adventurer) break;
                }
            }
            if(Module_get_hitpoint(back)>0 && 4-Module_adventurer_get_posision(&adventurer_group[pointer])<=Module_get_range(back))
                Module_be_attacked((Module*)&adventurer_group[pointer], back);
        }else{
            Rooms_set_flag(room);
        }
    }
    printf("Front's HP: %d\n",Module_get_hitpoint(front));
    printf("Middle's HP: %d\n",Module_get_hitpoint(middle));
    printf("Back's HP: %d\n",Module_get_hitpoint(back));
    for(int i = 0; i<max_adventurer; i++){
        printf("Adventurer HP: %d\n", Module_get_hitpoint((Module*)(&adventurer_group[i])));
    }
    return pointer;
}

int battle(Stage* stage, Id* identification, long int length){
    printf("in battle\n");
    int max_room_num = 6;
    int adventurer_pointer = 0;
    int room_pointer = 0;
    Module_adventurer adventurer_group[length];
    for (int i = 0; i < length; i++)
    {
        Module_adventurer advent = {0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0};
        Module_adventurer_construct(&advent, identification);
        adventurer_group[i] = advent;
    }

    printf("Success to set adventurer\n");
    printf("Length :%ld\n", (sizeof adventurer_group)/ (sizeof( Module_adventurer)));
    long int max_adventurer = ((sizeof adventurer_group)/(sizeof( Module_adventurer)));
    
    while(room_pointer<max_room_num){
        Rooms* room = Stage_get_room(stage, room_pointer);
        adventurer_pointer = battle_in_room(stage, room, adventurer_group, room_pointer, adventurer_pointer, max_adventurer);
        if(adventurer_pointer<max_adventurer){
            room_pointer++;
        }else{
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

    long int adventurer_length = -1;
    while(adventurer_length<0){
        printf("How many adventurer will be came ? > ");
        scanf("%ld",&adventurer_length);
        if(adventurer_length<0){
            printf("Please input non-negative integer.\n");
        }
    }

    int cleared_room = battle(&stage, &identification, adventurer_length);
    printf("Cleared Room : %d\n",cleared_room);
    printf("Success to battle\n");
    if(cleared_room>=6){
        printf("The dungeon has fallen.\n");
    }else{
        printf("Success to protected the dungeon!\n");
    }
    
    return 0;
}