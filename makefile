make_buttle: test_buttle_main.c
	gcc -o buttle test_buttle_main.c id.c module.c module_adventurer.c module_boss.c module_skeleton.c room.c stage.c 
make_main: protect_me_main.c
	gcc -o main protect_me_main.c id.c module.c module_adventurer.c module_boss.c module_skeleton.c room.c stage.c
