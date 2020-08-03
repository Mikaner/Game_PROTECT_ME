#include <stdio.h>
#include <windows.h>
#include "Id.h"
#include "Module.h"
#include "Module_adventurer.h"
#include "Room.h"
#include "Stage.h"


int battle_in_room(Stage* stage, Rooms* room, Module_adventurer* adventurer_group,  int room_pointer, int adventurer_pointer, long int length){
    printf("------ Buttle in Room %d ------\n", room_pointer+1);
    long int max_adventurer = length;
    printf("max_adventurer: %ld\n", max_adventurer);
    int pointer = adventurer_pointer;
    Module* front = Stage_get_module(stage, room_pointer, 0);
    Module* middle = Stage_get_module(stage, room_pointer, 1);
    Module* back = Stage_get_module(stage, room_pointer, 2);
    int co = 0;
    /*printf("Front's HP: %d\n",Module_get_hitpoint(front));
    printf("Middle's HP: %d\n",Module_get_hitpoint(middle));
    printf("Back's HP: %d\n",Module_get_hitpoint(back));
    for(int i = 0; i<max_adventurer; i++){
        printf("Adventurer HP: %d\n", Module_get_hitpoint((Module*)(&adventurer_group[i])));
        Module_adventurer_set_position(&adventurer_group[i], 0);
    }*/
    // Battle
    while(Rooms_get_flag(room)==0 && pointer < max_adventurer){
        /*printf("turn %d\n",++co);
        printf("Adventurer Pointer: %d\n",pointer);
        printf("Adventurer HP: %d\n", Module_get_hitpoint((Module*)&adventurer_group[pointer]));
        printf("Adventurer Position: %d\n", Module_adventurer_get_position(&adventurer_group[pointer]));
        printf("Front HP : %d\n", Module_get_hitpoint(front));
        printf("Middle HP : %d\n", Module_get_hitpoint(middle));
        printf("Back HP : %d\n\n", Module_get_hitpoint(back));*/
        // Move module pointer
        while(Module_get_hitpoint((Module*)&adventurer_group[pointer])<=0){
            printf("Pointer %d HP: %d\n",pointer,Module_get_hitpoint((Module*)&adventurer_group[pointer]));
            pointer++;
            if(pointer>=max_adventurer) break;
        }
        if(pointer>=max_adventurer) break;
        // Buttle adventurer vs front
        if(Module_get_hitpoint(front)>0){
            // Check adventurer hp
            if(Module_get_hitpoint((Module*)&adventurer_group[pointer])>0){
                // Adventurer attack to front
                Module_be_attacked(front, (Module*)&adventurer_group[pointer]);
            }else{
                // Incriment adventurer pointer
                while(Module_get_hitpoint((Module*)&adventurer_group[pointer])<=0){
                    printf("Adventurer %d HP: %d\n",pointer+1,Module_get_hitpoint((Module*)&adventurer_group[pointer]));
                    pointer++;
                    if(pointer>=max_adventurer) break;
                }
                if(pointer>=max_adventurer) break;
            }
            // Check front hp
            if(Module_get_hitpoint(front)>0){
                // Front attack to adventurer <-- need to check
                //printf("%d\n",Module_get_hitpoint((Module*)&adventurer_group[pointer]));
                Module_be_attacked((Module*)&adventurer_group[pointer], front);
            }
        }
        if(Module_get_hitpoint(front)<=0){
            // Move adventurer position
            for (int i = pointer; i < max_adventurer; i++) {
                Module_adventurer_set_position(&adventurer_group[i], 2);
            }
        }
        // Buttle adventurer vs middle
        if(Module_get_hitpoint(middle)>0){
            // Check front hp -- for adventurer to attack middle.
            if(Module_get_hitpoint(front)<=0){
                // Check adventurer hp
                if(Module_get_hitpoint((Module*)&adventurer_group[pointer])>0){
                    // Adventurer attack to middle
                    Module_be_attacked(middle, (Module*)&adventurer_group[pointer]);
                }else{
                    // Move adventurer pointer
                    while(Module_get_hitpoint((Module*)&adventurer_group[pointer])<=0){
                        printf("Pointer %d HP: %d\n",pointer,Module_get_hitpoint((Module*)&adventurer_group[pointer]));
                        pointer++;
                        if(pointer>=max_adventurer) break;
                    }
                    if(pointer>=max_adventurer) break;
                }
            }
            // Check to be adventurer in middle's range <-- need to check
            // Need to add checker for adventurer hp
            if(Module_get_hitpoint(middle)>0 && 3-Module_adventurer_get_position(&adventurer_group[pointer])<=Module_get_range(middle)){
                // Middle attack to adventurer <-- need to check
                Module_be_attacked((Module*)&adventurer_group[pointer], middle);
            }
        }
        // Check middle hp
        if(Module_get_hitpoint(middle)<=0 && Module_get_hitpoint(front)<=0){
            // Move adventurer position after defeating middle.
            for (int i = pointer; i < max_adventurer; i++)
            {
                Module_adventurer_set_position(&adventurer_group[i], 3);
            }
        }
        // Chack back hp
        if(Module_get_hitpoint(back)>0){
            // Check adventurer hp
            if(Module_get_hitpoint((Module*)&adventurer_group[pointer])>0){
                // Check front hp and middle hp -- for adventurer to attack back.
                if(Module_get_hitpoint(front)<=0&&Module_get_hitpoint(middle)<=0){
                    // Adventurer attack to back
                    Module_be_attacked(back, (Module*)&adventurer_group[pointer]); 
                }
            }else{
                while(Module_get_hitpoint((Module*)&adventurer_group[pointer])<=0){
                    printf("Pointer %d HP: %d\n",pointer,Module_get_hitpoint((Module*)&adventurer_group[pointer]));
                    pointer++;
                    if(pointer>=max_adventurer) break;
                }
                if(pointer>=max_adventurer) break;
            }
               
            // Check to be adventurer in back's range <-- need to check
            if(4-Module_adventurer_get_position(&adventurer_group[pointer])<=Module_get_range(back))
                // Front attack to adventurer <-- need to check
                Module_be_attacked((Module*)&adventurer_group[pointer], back);
        }
        // The room is falled if there is no module.
        if(Module_get_hitpoint(front)<=0 && Module_get_hitpoint(middle)<=0 && Module_get_hitpoint(back)<=0){
            // The room falled
            Rooms_set_flag(room);
        }
    }
    printf("Front's HP: %d\n",Module_get_hitpoint(front));
    printf("Middle's HP: %d\n",Module_get_hitpoint(middle));
    printf("Back's HP: %d\n",Module_get_hitpoint(back));
    /*for(int i = 0; i<max_adventurer; i++){
        printf("Adventurer HP: %d\n", Module_get_hitpoint((Module*)(&adventurer_group[i])));
        Module_adventurer_set_position(&adventurer_group[i], 0);
    }*/
    Sleep(500);
    return pointer;
}

int battle(Stage* stage, Id* identification, long int length){
    printf("in battle\n");
    int max_room_num = 6;
    int adventurer_pointer = 0;
    int room_pointer = 0;
    int ad1_pointer = 0;
    int ad2_pointer = 0;
    int ad3_pointer = 0;
    Module_adventurer adventurer_group[length];
    for (int i = 0; i < length; i++)
    {
        Module_adventurer advent = {0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0};
        Module_adventurer_construct(&advent, identification);
        adventurer_group[i] = advent;
    }

    printf("Success to set adventurer\n");
    printf("Length :%ld\n\n", (sizeof adventurer_group)/ (sizeof( Module_adventurer)));
    long int max_adventurer = ((sizeof adventurer_group)/(sizeof( Module_adventurer)));
    
    while(room_pointer<max_room_num){
        if (room_pointer==1){
            int room1_pointer = 1;
            int room2_pointer = 2;
            int room3_pointer = 3;
            //int num_of_arriving_adventurer = max_adventurer-adventurer_pointer;
            /*Module_adventurer ad_group1[(num_of_arriving_adventurer)/3 + 1*((num_of_arriving_adventurer)%3==1 || num_of_arriving_adventurer%3==2)];
            Module_adventurer ad_group2[(num_of_arriving_adventurer)/3 + 1*((num_of_arriving_adventurer)%3==2)];
            Module_adventurer ad_group3[(num_of_arriving_adventurer)/3];*/
            Module_adventurer ad_group1[(max_adventurer)/3 + 1*((max_adventurer)%3==1 || max_adventurer%3==2)];
            Module_adventurer ad_group2[(max_adventurer)/3 + 1*((max_adventurer)%3==2)];
            Module_adventurer ad_group3[(max_adventurer)/3];
            int flg1=0,flg2=0,flg3=0;
            int count = 0;
            //for(int i = 0; i<num_of_arriving_adventurer; i++){
            for(int i = 0; i<max_adventurer; i++){
                switch(i%3){
                case 0:
                    ad_group1[count] = adventurer_group[i+adventurer_pointer];
                    flg1=1;
                    break;
                case 1:
                    ad_group2[count] = adventurer_group[i+adventurer_pointer];
                    flg2=1;
                    break;
                case 2:
                    ad_group3[count] = adventurer_group[i+adventurer_pointer];
                    flg3=1;
                    break;
                }
                if(flg1 && flg2 && flg3){
                    flg1=0;
                    flg2=0;
                    flg3=0;
                    count++;
                }
            }
            count = 0;
            //for(int i = 0; i<num_of_arriving_adventurer; i++){
            for(int i = 0; i<max_adventurer; i++){
                switch(i%3){
                case 0:
                    flg1=1;
                    break;
                case 1:
                    flg2=1;
                    break;
                case 2:
                    flg3=1;
                    break;
                }
                if(flg1 && flg2 && flg3){
                    flg1=0;
                    flg2=0;
                    flg3=0;
                    count++;
                }
            }
            Rooms* room1 = Stage_get_room(stage, room1_pointer);
            Rooms* room2 = Stage_get_room(stage, room2_pointer);
            Rooms* room3 = Stage_get_room(stage, room3_pointer);
            printf("ad1\n");
            //ad1_pointer = battle_in_room(stage, room1, ad_group1, room1_pointer, ad1_pointer,
            //                             (num_of_arriving_adventurer)/3 + 1*((num_of_arriving_adventurer)%3==1 || num_of_arriving_adventurer%3==2));
            ad1_pointer = battle_in_room(stage, room1, ad_group1, room1_pointer, ad1_pointer,
                                         (max_adventurer)/3 + 1*((max_adventurer)%3==1 || max_adventurer%3==2));
            printf("ad2\n");
            //ad2_pointer = battle_in_room(stage, room2, ad_group2, room2_pointer, ad2_pointer,
            //                             (num_of_arriving_adventurer)/3 + 1*((num_of_arriving_adventurer)%3==2));
            ad2_pointer = battle_in_room(stage, room2, ad_group2, room2_pointer, ad2_pointer,
                                         (max_adventurer)/3 + 1*((max_adventurer)%3==2));
            printf("ad3\n");
            //ad3_pointer = battle_in_room(stage, room3, ad_group3, room3_pointer, ad3_pointer, (num_of_arriving_adventurer)/3);
            ad3_pointer = battle_in_room(stage, room3, ad_group3, room3_pointer, ad3_pointer, (max_adventurer)/3);
            count = 0;
            //for(int i = 0; i<num_of_arriving_adventurer; i++){
            for(int i = 0; i<max_adventurer; i++){
                switch(i%3){
                case 0:
                    adventurer_group[i+adventurer_pointer] = ad_group1[count];
                    flg1=1;
                    break;
                case 1:
                    adventurer_group[i+adventurer_pointer] = ad_group2[count];
                    flg2=1;
                    break;
                case 2:
                    adventurer_group[i+adventurer_pointer] = ad_group3[count];
                    flg3=1;
                    break;
                }
                if(flg1 && flg2 && flg3){
                    flg1=0;
                    flg2=0;
                    flg3=0;
                    count++;
                }
            }
            //if(ad1_pointer<(num_of_arriving_adventurer)/3 + 1*((num_of_arriving_adventurer)%3==1 || num_of_arriving_adventurer%3==2) || 
            //   ad2_pointer<(num_of_arriving_adventurer)/3 + 1*((num_of_arriving_adventurer)%3==2) ||
            //   ad3_pointer<(num_of_arriving_adventurer)/3)
            if(ad1_pointer<(max_adventurer)/3 + 1*((max_adventurer)%3==1 || max_adventurer%3==2) || 
               ad2_pointer<(max_adventurer)/3 + 1*((max_adventurer)%3==2) ||
               ad3_pointer<(max_adventurer)/3)
            {
                room_pointer = room_pointer+3;
                printf("room pointer : %d\n\n",room_pointer);
            }else{
                printf("Max Pointer1: %d, Max Pointer2: %d, Max Pointer3: %d\n",
                //        (num_of_arriving_adventurer)/3 + 1*((num_of_arriving_adventurer)%3==1 || num_of_arriving_adventurer%3==2),
                //        (num_of_arriving_adventurer)/3 + 1*((num_of_arriving_adventurer)%3==2),
                //        (num_of_arriving_adventurer)/3);
                        (max_adventurer)/3 + 1*((max_adventurer)%3==1 || max_adventurer%3==2),
                        (max_adventurer)/3 + 1*((max_adventurer)%3==2),
                        (max_adventurer)/3);
                printf("Ad1 Pointer : %d, Ad2 Pointer : %d, Ad3 Pointer : %d\n",ad1_pointer,ad2_pointer,ad3_pointer);
                break;
            }
        }else{
            Rooms* room = Stage_get_room(stage, room_pointer);
            adventurer_pointer = battle_in_room(stage, room, adventurer_group, room_pointer, adventurer_pointer, max_adventurer);
            if(adventurer_pointer<max_adventurer){
                room_pointer++;
                printf("room pointer : %d\n\n",room_pointer);
                adventurer_pointer = 0;
            }else{
                break;
            }
        }
        
    }
    return room_pointer;
}