#include <stdio.h>
#include "Id.h"
#include "Module.h"
int main(){
    Module m;
    Module_init_construct(&m);
    printf("%p\n",&m);
    printf("%p\n",&(m.id));
    
}