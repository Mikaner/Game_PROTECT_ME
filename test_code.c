#include <stdio.h>
#include <string.h>
#include "Id.h"
#include "Module.h"
#include "Module_adventurer.h"

int main(){
    Id identification;
    Id_construct(&identification);
    Module m;
    Module_init_construct(&m);
    printf("%p\n",&m);
    printf("%p\n",&(m.id));
    
    Module_adventurer* group[500];
    for(int i=0; i<500; i++){
        Module_adventurer advent = {0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0};
        Module_adventurer_construct(&advent,&identification);
        group[i] = &advent;
    }
    for(int i=0; i<3; i++){
        printf("%p\n", &group[i]);
        printf("%ld\n", (sizeof group[i]));
        printf("pointer %p\n", &*group[i]);
    }
    printf("length %ld\n", ((sizeof group)/(sizeof(struct Module_adventurer*))));
    char* s = "Module";
    printf(" %*s%*s \n",8+(int)strlen(s)/2,s,8-(int)strlen(s)/2,"");
}