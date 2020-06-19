#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Id.h"
#include "Module.h"
#include "Stage.h"
#define ESC 27

int intro(){
    int input_stage_num;
    int sum_stage=1;
    int co=0;
    printf("Welcome to this world.\n");
    printf("説明がほしいか？\n");
    printf("君は選ばれたんだ。選ばれるのは好きだろ？喜びたまえ。\n\n");

    printf("これ以上の説明はない。\n");
    printf("さあ、君のステージを選択したまえ。\n");
    printf("まあ今は1つしかないんだがな！\n");
    while(sum_stage!=0){
        printf("stage1\n");
        sum_stage--;
    }
    printf("\n");
    do{
        if (co>1){
            printf("なんだ？1を入れなければ進まないぞ？\n");
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

void init_timer(){
    double start_time = clock()/CLOCKS_PER_SEC;
}

void show_room_status(char *name){
    printf("|%*s%*s|",8+strlen(name)/2,name,8-strlen(name)/2,"");
}

void show_route(char* a, char* c){
    printf(" %*s%*s ",8+strlen(a)/2,a,8-strlen(a)/2,"");
    printf("  %*s%*s  ",8+strlen("|")/2,"|",8-strlen("|")/2,"");
    printf(" %*s%*s ",8+strlen(c)/2,c,8-strlen(c)/2,"");
    printf("\n");
}

void show_room(int room_num1, int room_num2, int room_num3){
    if(room_num1!=0){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf(" ");

    if(room_num2!=0){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf(" ");
    if(room_num3!=0){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf("\n");
    
    for(int i=0; i<3;i++){
        if(room_num1!=0){
            show_room_status("No module");
        }else{
            printf("                  ");
        }
        printf(" ");

        if(room_num2!=0){
            show_room_status("No module");
        }else{
            printf("                  ");
        }
        printf(" ");
        if(room_num3!=0){
            show_room_status("No module");
        }else{
            printf("                  ");
        }
        printf("\n");
    }
    if(room_num1!=0){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf(" ");

    if(room_num2!=0){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf(" ");
    if(room_num3!=0){
        printf("------------------");
    }else{
        printf("                  ");
    }
    printf("\n");
}

void show_entrance_room(){
    char* s = "entrance";
    printf("                   ");
    printf(" %*s%*s ",8+strlen(s)/2,s,8-strlen(s)/2,"");
    printf("\n");
    show_route("  ","  ");
    show_room(0,1,0);
}
void show_before_core_room(){
    char* s = "to core room";
    show_room(0,1,0);
    show_route("  ","  ");
    printf("                   ");
    printf(" %*s%*s ",8+strlen(s)/2,s,8-strlen(s)/2,"");
    printf("\n\n");
}

void show_dungeon(){
    show_entrance_room();

    show_route("               /","\\               ");
    
    show_room(1,1,1);

    show_route("               \\","/               ");

    show_room(0,1,0);
    show_route("  ","  ");
    show_before_core_room();
}

void show_commands(){
    printf("0) Exit this game.\n");
    printf("1-6) Choose the room.\n");
    //printf("27) Exit this game.\n");
    //printf("Else) No action.\n");
    printf("Else) Show all dungeon status.\n");
}

int main(){
    Id identification;
    Stage stage;
    int stage_num = intro();
    int stage_cost = get_stage_cost(stage_num);
    int input_num;
    init_game(&identification, &stage, stage_num, stage_cost);
    init_timer();
    printf("Success to make stage.\n\n");

    show_dungeon();
    while(input_num!=ESC){
        show_commands();
        printf("--> ");
        scanf("%d",&input_num);
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
            show_room(input_num,0,0);
            break;
        default:
            show_dungeon();
            break;
        }
        printf("\n");
    }
    return 0;
}