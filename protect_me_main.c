#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <windows.h>
#include "Id.h"
#include "Stage.h"
#include "Module.h"
#include "Module_adventurer.h"
#include "Module_boss.h"
#include "Module_skeleton.h"
#include "Module_zombie.h"
#include "Module_witch.h"
#include "Module_goblin.h"
#include "Module_mummy.h"
#include "Module_vampire.h"
#include "battle.h"
#define ESC 27
#define max_module_type 7

Id identification;
Stage stage;
pthread_mutex_t mutex;
int time_up_flag = 0;
int boss_is_available = 1;

char* get_module_name(int module_num);
int intro();
void do_battle(void);

char* get_module_name(int module_num){
    switch (module_num)
    {
    case 0:
        return "No Name";
        break;
    case 1:
        return "Adventurer";
        break;
    case 2:
        return "Boss";
        break;
    case 3:
        return "Skeleton";
        break;
    case 4:
        return "Zombie";
        break;
    case 5:
        return "Witch";
        break;
    case 6:
        return "Goblins";
        break;
    case 7:
        return "MummyMan";
        break;
    case 8:
        return "Vampire";
        break;
    default:
        return "No Module";
        break;
    }
}
void print_game_clear(){
    printf("         ■\n");
    printf("  ■■■■■  ■                      ■■  ■■\n");
    printf(" ■■   ■  ■                      ■■  ■■\n");
    printf("■■       ■    ■■■■   ■■■   ■ ■■ ■■  ■■\n");
    printf("■        ■   ■■  ■  ■   ■  ■■   ■■  ■■\n");
    printf("■        ■   ■   ■■     ■  ■■   ■   ■\n");
    printf("■        ■   ■■■■■■ ■■■■■  ■    ■   ■\n");
    printf("■■       ■   ■      ■   ■  ■    ■   ■\n");
    printf(" ■■   ■  ■   ■■     ■  ■■  ■\n");
    printf("  ■■■■   ■    ■■■■  ■■■■■  ■    ■■  ■■\n");
}

void print_game_over(){
    printf("  ■■■■■\n");
    printf(" ■■   ■\n");
    printf("■■         ■■■   ■■■■  ■■    ■■■■       ■■■■  ■■   ■  ■■■■  ■ ■■\n");
    printf("■         ■   ■  ■■  ■■  ■  ■■  ■      ■■  ■■  ■   ■ ■■  ■  ■■\n");
    printf("■    ■■■      ■  ■   ■   ■  ■   ■■     ■    ■  ■  ■  ■   ■■ ■■\n");
    printf("■      ■  ■■■■■  ■   ■   ■  ■■■■■■     ■    ■  ■■ ■  ■■■■■■ ■\n");
    printf("■■     ■  ■   ■  ■   ■   ■  ■          ■    ■   ■ ■  ■      ■\n");
    printf(" ■■   ■■  ■  ■■  ■   ■   ■  ■■         ■■  ■■   ■■   ■■     ■\n");
    printf("  ■■■■■   ■■■■■  ■   ■   ■   ■■■■       ■■■■     ■    ■■■■  ■    ■  ■  ■\n");
}

int intro(){
    int input_stage_num;
    int sum_stage=1;
    int co=0;
    printf("**CAUTHION : If you executed this game by Shift-jis or anything which is not utf-8, please change character code to utf-8.**\n\n-------------------\n");
    printf("Welcome to this world. \n\n");
    //printf("説明がほしいか？\n");
    printf("Do you want some description?\n");
    //printf("君は選ばれたんだ。選ばれるのは好きだろ？喜びたまえ。\n\n");
    printf("You are decided. You like to be chosen, don't you? Prease be glad.\n");

    //printf("説明は以上だ。\n");
    printf("The description is done.\n");
    //printf("さあさあ、君のステージを選択したまえ！\n");
    printf("Come on, come on. Choose stage number!\n\n");
    //printf("まあ今は1つしかないんだがな！\n");
    printf("Well, this game has only one stage now.\n");
    for(int i=0; i<sum_stage; i++){
        printf("%d) stage1\n", i+1);
    }
    printf("\n");
    do{
        if (co>1 && co<=4){
            //printf("なんだ？1を入れなければ進まないぞ？\n");
            printf("What? Not proceed if you don't input 1.\n");
        }else if (co>4){
            //printf("ああ、やめたいのか。仕方ないな...\n");
            printf("I understand. You do NOT want to play this game. OK...\n");
            Sleep(250);
            Sleep(250);
            printf(".");
            Sleep(250);
            printf(".");
            Sleep(250);
            printf(".\n");
            Sleep(250);
            //printf("じゃあな。\n");
            printf("Good bye.\n\n");
            print_game_over();
            exit(0);
        }
        printf("input --> ");
        scanf("%d", &input_stage_num);
        co++;
    }while(input_stage_num!=1);

    printf("%d\n", input_stage_num);

    return input_stage_num-1;
}

int get_stage_cost(int input_stage){
    if(input_stage==0){
        return 20;
    }else{
        printf("There is not to be assigned stage in this game.\n");
        return 0;
    }
}

void init_game(Id* identification, Stage* stage, int stage_num, int stage_cost){
    Id_construct(identification);
    Stage_construct(stage, stage_num, stage_cost);
}

void *timer(void *seconds){
    //double start_time = clock()/CLOCKS_PER_SEC;
    int millis = (*(int*)seconds) * 1000;
    Sleep(millis);
    printf("\n%d millis have passed.\n", millis);
    time_up_flag = 1;


    do_battle();
    exit(0);
}

void show_room_status(char *name, int position){
    printf("|%d: %*s%*s|",position,6+(int)strlen(name)/2,name,7-(int)strlen(name)/2,"");
}

void show_route(char* a, char* c){
    printf(" %*s%*s ",8+(int)strlen(a)/2,a,8-(int)strlen(a)/2,"");
    printf("  %*s%*s  ",8+(int)strlen("|")/2,"|",8-(int)strlen("|")/2,"");
    printf(" %*s%*s ",8+(int)strlen(c)/2,c,8-(int)strlen(c)/2,"");
    printf("\n");
}

void show_room(Stage* stage, int room_num1, int room_num2, int room_num3){
    char* module_name;
    if(room_num1!=-1){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf(" ");

    if(room_num2!=-1){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf(" ");
    if(room_num3!=-1){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf("\n");

    if(room_num1!=-1){
        printf("|---- room %d ----|",room_num1+1);
    }else{
        printf("                  ");
    }
    printf(" ");

    if(room_num2!=-1){
        printf("|---- room %d ----|",room_num2+1);
    }else{
        printf("                  ");
    }
    printf(" ");
    if(room_num3!=-1){
        printf("|---- room %d ----|",room_num3+1);
    }else{
        printf("                  ");
    }
    printf("\n");
    
    for(int i=0; i<3;i++){
        if(room_num1!=-1){
            module_name = get_module_name(Module_get_num(Stage_get_module(stage, room_num1,i)));
            show_room_status(module_name, i+1);
        }else{
            printf("                  ");
        }
        printf(" ");

        if(room_num2!=-1){
            module_name = get_module_name(Module_get_num(Stage_get_module(stage, room_num2,i)));
            show_room_status(module_name, i+1);
        }else{
            printf("                  ");
        }
        printf(" ");
        if(room_num3!=-1){
            module_name = get_module_name(Module_get_num(Stage_get_module(stage, room_num3,i)));
            show_room_status(module_name, i+1);
        }else{
            printf("                  ");
        }
        printf("\n");
    }
    if(room_num1!=-1){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf(" ");

    if(room_num2!=-1){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf(" ");
    if(room_num3!=-1){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf("\n");
}

void show_entrance_room(Stage* stage){
    char* s = "Entrance";
    printf("                   ");
    printf(" %*s%*s ",8+(int)strlen(s)/2,s,8-(int)strlen(s)/2,"");
    printf("\n");
    show_route("  ","  ");
    show_room(stage,-1,0,-1);
}
void show_before_core_room(Stage* stage){
    char* s = "Core room";
    show_room(stage,-1,5,-1);
    show_route("  ","  ");
    printf("                   ");
    printf(" %*s%*s ",8+(int)strlen(s)/2,s,8-(int)strlen(s)/2,"");
    printf("\n\n");
}

void show_dungeon(Stage* stage){
    show_entrance_room(stage);

    show_route("               /","\\               ");
    
    show_room(stage,1,2,3);

    show_route("               \\","/               ");

    show_room(stage,-1,4,-1);
    show_route("  ","  ");
    show_before_core_room(stage);
}

void show_commands(){
    printf("Please input to choose choices numbers.\n");
    printf("0) Show all dungeon status.\n");
    printf("1) Choose room 1.\n");
    printf("2) Choose room 2.\n");
    printf("3) Choose room 3.\n");
    printf("4) Choose room 4.\n");
    printf("5) Choose room 5.\n");
    printf("6) Choose room 6.\n");
    printf("Else) Exit this game.\n");
}

void show_module_commands(){
    printf("Please input module number.\n");
    printf("0) Back to previous choices.\n");
    printf("1) Set Boss.\n");
    printf("2) Set Skeleton.\n");
    printf("3) Set Zombie.\n");
    printf("4) Set Witch.\n");
    printf("5) Set Goblins.\n");
    printf("6) Set Mummy man.\n");
    printf("7) Set Vampire.\n");
}

void show_position_commands(){
    printf("Please input position number of selected module.\n");
    printf("0) Back to previous choices.\n");
    printf("1) Set position 1.\n");
    printf("2) Set position 2.\n");
    printf("3) Set position 3.\n");
}

void set_module_to_room(Id* mdl_id, Stage* stage, int room_num, int module_type, int module_position){
    Rooms* room = Stage_get_room(stage, room_num);
    Module mdl = {0,-1,0,0,0,0,0,0,0,0,0,0,0,0};
    printf("type is :%d\n",module_type);
    switch (module_type)
    {
    case num_of_boss:
        Module_boss_construct((Module_boss*)&mdl, mdl_id);
        Rooms_set_module(room, mdl, module_position);
        break;
    case num_of_skeleton:
        Module_skeleton_construct((Module_skeleton*)&mdl, mdl_id);
        Rooms_set_module(room, mdl, module_position);
        break;
    case num_of_zombie:
        Module_zombie_construct((Module_zombie*)&mdl, mdl_id);
        Rooms_set_module(room, mdl, module_position);
        break;
    case num_of_witch:
        Module_witch_construct((Module_witch*)&mdl, mdl_id);
        Rooms_set_module(room, mdl, module_position);
        break;
    case num_of_goblin:
        Module_goblin_construct((Module_goblin*)&mdl, mdl_id);
        Rooms_set_module(room, mdl, module_position);
        break;
    case num_of_mummy:
        Module_mummy_construct((Module_mummy*)&mdl, mdl_id);
        Rooms_set_module(room, mdl, module_position);
        break;
    case num_of_vampire:
        Module_vampire_construct((Module_vampire*)&mdl, mdl_id);
        Rooms_set_module(room, mdl, module_position);
        break;
    default:
        printf("404 Module not found.\n");
        break;
    }
}

int main(){
    pthread_t pthread;
    //unsigned int max_count = 60*10;
    unsigned int time_limit = 60;

    int stage_num = intro();
    int stage_cost = get_stage_cost(stage_num);
    int input_num=-1;
    init_game(&identification, &stage, stage_num, stage_cost);
    pthread_create( &pthread, NULL, &timer, &time_limit);
    printf("Success to make stage.\n\n");

    show_dungeon(&stage);
    while(input_num!=0 && time_up_flag==0){
        input_num = 0;
        show_commands();
        printf("--> ");
        scanf("%d",&input_num);
        printf("\n");
        if(time_up_flag==1) break;
        switch (input_num)
        {
        case 0:
            exit(0);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            show_room(&stage,input_num-1,-1,-1);
            int input_module_type=-1;
            while ((input_module_type<0 || input_module_type>max_module_type) && time_up_flag==0)
            {
                show_module_commands();
                printf(">>> ");
                scanf("%d",&input_module_type);
                printf("\n");
                if(time_up_flag==1) break;
                if(input_module_type==0) break;

                if(input_module_type >= 1 || input_module_type <= max_module_type){
                    int input_module_position=0;
                    while((input_module_position<1 || input_module_position>3) && time_up_flag==0){
                        show_position_commands();
                        printf(">>> ");
                        scanf("%d",&input_module_position);
                        printf("\n");
                        if(time_up_flag==1) break;
                        if(input_module_position==0) break;
                        set_module_to_room(&identification,&stage,input_num-1,input_module_type+1, input_module_position-1);
                    }
                }else{
                    printf("That module is not signed up.\n");
                }
            }
            show_dungeon(&stage);
            break;
        case -200:
        default:
            show_dungeon(&stage);
            break;
        }
        printf("\n");
    }

    return 0;
}

void do_battle(void){
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int id_num = Stage_get_module_id(&stage, i,j);
            printf("%d",id_num);
        }
    }
    printf("\n");

    long int adventurer_length = 200;

    int cleared_room = battle(&stage, &identification, adventurer_length);
    printf("Cleared Room : %d\n",cleared_room);
    printf("Success to battle\n");
    if(cleared_room>=6){
        printf("The dungeon has fallen.\n\n");
        print_game_over();
    }else{
        printf("Success to protected the dungeon!\n\n");
        print_game_clear();
    }
}
