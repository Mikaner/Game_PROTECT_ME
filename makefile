make_main: protect_me_main.c
	gcc -o main -pthread protect_me_main.c id.c module.c module_adventurer.c module_boss.c module_skeleton.c room.c stage.c battle.c
make_battle: test_battle_main.c
	gcc -o battle test_battle_main.c id.c module.c module_adventurer.c module_boss.c module_skeleton.c room.c stage.c 
