make_main: protect_me_main.c
	gcc -o protect_me -pthread protect_me_main.c id.c module.c module_adventurer.c module_boss.c module_skeleton.c module_zombie.c module_witch.c module_goblin.c module_mummy.c module_vampire.c room.c stage.c battle.c
make_battle: test_battle_main.c
	gcc -o battle test_battle_main.c id.c module.c module_adventurer.c module_boss.c module_skeleton.c module_zombie.c module_witch.c module_goblin.c module_mummy.c module_vampire.c room.c stage.c 
