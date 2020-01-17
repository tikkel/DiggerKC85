#define SPRITE_W 16
#define SPRITE_H 16
#define NUM_SPRITES 33
#define NUM_LEDMATRIX 10

//sprites
#define EMPTY 0
#define WALL 1
#define ROCK 2
#define SOIL 3
#define DIAMOND 4
#define DIAMOND1 13
#define DIAMOND2 14
#define DIAMOND3 15
#define CHANGER 5
#define DOOR 6
#define MONSTER_D 7
#define MONSTER_L 8
#define MONSTER_U 9
#define MONSTER_R 10
#define PLAYER 11
#define DEATH 12

#define DIGGER_L 1
#define DIGGER_U 2
#define DIGGER_I 3
#define DIGGER_D 4
#define DIGGER_R 5

#define MONSTER_RT 12
#define MONSTER_LT 13

#define NUM_LEVELS 152

#define WORLD_W 20
#define WORLD_H 14

//8bit Operatoren
#define PHYSICSTATE 16 //0x10, 0001 0000  physic-state
#define RENDERSTATE 32  //0x20, 0010 0000  render-state

#define SPRITEMASK 15   //0x0F, 0000 1111
#define STATEMASK 240   //0xF0, 1111 0000
#define TYPEMASK 192    //0xC0, 1100 0000

//types of monsters
#define TYPE_UD 0
#define TYPE_LR 64
#define TYPE_RT 128
#define TYPE_LT 192

//gamestates
#define MENULENGTH 6
#define PAUSED 1
#define RUNNING 0
#define GAMEOVER 2
#define SCORE 3
#define EASY false
#define HARD true
#define LIVES 20

//decryption
#define BITREF 6
#define BITCOUNT 3
#define MINMATCH 3
#define CODELENGTH 4
