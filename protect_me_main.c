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
#include "battle.h"
#define ESC 27
#define num_of_adventurer 1
#define num_of_boss 2
#define num_of_skeleton 3
#define max_module_type 2

Id identification;
Stage stage;
pthread_mutex_t mutex;

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
    default:
        return "No Module";
        break;
    }
}
void print_game_clear(){
    printf("  ■■■■                                                                                            ■            ■\n");
    printf("■      ■                                                                                            ■            ■\n");
    printf("■            ■      ■      ■■■■      ■■■■      ■■■        ■■■        ■■■          ■            ■\n");
    printf("  ■          ■      ■    ■■          ■■          ■■  ■■    ■■          ■■              ■            ■\n");
    printf("    ■■      ■      ■    ■            ■            ■      ■    ■■          ■■              ■            ■\n");
    printf("      ■■    ■      ■    ■            ■            ■■■■■      ■■■        ■■■          ■            ■\n");
    printf("        ■    ■    ■■    ■            ■            ■                  ■■          ■■                        \n");
    printf("■    ■■    ■    ■■      ■    ■      ■    ■    ■■    ■    ■    ■■    ■    ■■        ■            ■\n");
    printf("  ■■■        ■■■■      ■■■■      ■■■■      ■■■■    ■■■■      ■■■■          ■            ■\n\n");
}

void print_game_over(){

}

int intro(){
    int input_stage_num;
    int sum_stage=1;
    int co=0;
    printf("Welcome to this world.\n");
    printf("説明がほしいか？\n");
    //printf("Do you want some description?\n");
    printf("君は選ばれたんだ。選ばれるのは好きだろ？喜びたまえ。\n\n");
    //printf("You are decided");

    printf("これ以上の説明はない。\n");
    printf("さあ、君のステージを選択したまえ。\n");
    printf("まあ今は1つしかないんだがな！\n");
    while(sum_stage!=0){
        printf("stage1\n");
        sum_stage--;
    }
    printf("\n");
    do{
        if (co>1 && co<=5){
            printf("なんだ？1を入れなければ進まないぞ？\n");
        }else if (co>5){
            printf("ああ、やめたいのか。仕方ないな...\n");
            printf("じゃあな。\n");
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
    printf("%d millis have passed.\n", millis);

    do_battle();
    exit(0);
}

void show_room_status(char *name){
    printf("|%*s%*s|",8+(int)strlen(name)/2,name,8-(int)strlen(name)/2,"");
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
            show_room_status(module_name);
        }else{
            printf("                  ");
        }
        printf(" ");

        if(room_num2!=-1){
            module_name = get_module_name(Module_get_num(Stage_get_module(stage, room_num2,i)));
            show_room_status(module_name);
        }else{
            printf("                  ");
        }
        printf(" ");
        if(room_num3!=-1){
            module_name = get_module_name(Module_get_num(Stage_get_module(stage, room_num3,i)));
            show_room_status(module_name);
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
    char* s = "entrance";
    printf("                   ");
    printf(" %*s%*s ",8+(int)strlen(s)/2,s,8-(int)strlen(s)/2,"");
    printf("\n");
    show_route("  ","  ");
    show_room(stage,-1,0,-1);
}
void show_before_core_room(Stage* stage){
    char* s = "to core room";
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
    printf("0) Exit this game.\n");
    printf("1-6) Choose the number of room.\n");
    printf("Else) Show all dungeon status.\n");
}

void show_module_commands(){
    printf("Please input module number.\n");
    printf("0) Exit this game.\n");
    printf("1) Set Boss.\n");
    printf("2) Set Skeleton.\n");
    printf("Else) Back.\n");
}

void set_module_to_room(Id* identificaton, Stage* stage, int room_num, int module_type, int module_position){
    Rooms* room = Stage_get_room(stage, room_num);
    Module mdl = {0,-1,0,0,0,0,0,0,0,0,0,0,0,0};
    printf("type is :%d\n",module_type);
    switch (module_type)
    {
    case num_of_boss:
        Module_boss_construct((Module_boss*)&mdl, identificaton);
        Rooms_set_module(room, mdl, module_position);
        break;
    case num_of_skeleton:
        Module_skeleton_construct((Module_skeleton*)&mdl, identificaton);
        Rooms_set_module(room, mdl, module_position);
    default:
        printf("404 Module not found.\n");
        break;
    }
}

int main(){
    pthread_t pthread;
    //unsigned int max_count = 60*10;
    unsigned int time_limit = 2;

    int stage_num = intro();
    int stage_cost = get_stage_cost(stage_num);
    int input_num=-1;
    init_game(&identification, &stage, stage_num, stage_cost);
    pthread_create( &pthread, NULL, &timer, &time_limit);
    printf("Success to make stage.\n\n");

    show_dungeon(&stage);
    while(input_num!=0){
        show_commands();
        printf("--> ");
        scanf("%d",&input_num);
        printf("\n");
        if(input_num>=0 && input_num<100){
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
            while (input_module_type<0 || input_module_type>2)
            {
                show_module_commands();
                printf(">>> ");
                scanf("%d",&input_module_type);
                printf("\n");
                if(input_module_type==0) exit(0);
                if(input_module_type<1){
                    printf("That module is not signed up.\n");
                    continue;
                }else if(input_module_type > max_module_type){
                    break;
                }
                int input_module_position=0;
                while(input_module_position<1 || input_module_position>3){
                    printf("Please input this module position.\n");
                    printf("0) Exit this game.\n");
                    printf("1-3) Set position.\n");
                    printf("Else) Back.\n");
                    printf(">>> ");
                    scanf("%d",&input_module_position);
                    printf("\n");
                    if(input_module_position==0) exit(0);
                    set_module_to_room(&identification,&stage,input_num-1,input_module_type+1, input_module_position-1);
                }
            }
            show_dungeon(&stage);
            break;
        case -200:
        default:
            show_dungeon(&stage);
            break;
        }
        }else{
            show_dungeon(&stage);
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

    long int adventurer_length = 20;

    int cleared_room = battle(&stage, &identification, adventurer_length);
    printf("Cleared Room : %d\n",cleared_room);
    printf("Success to battle\n");
    if(cleared_room>=6){
        printf("The dungeon has fallen.\n");
    }else{
        printf("Success to protected the dungeon!\n");
        print_game_clear();
    }
}
