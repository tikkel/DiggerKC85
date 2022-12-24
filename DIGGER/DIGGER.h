#define SPRITE_W 16
#define SPRITE_H 16
#define TOPBAR_H 16
#define NUM_SPRITES 33
#define NUM_LEDMATRIX 10

#define CHAR_W 8
#define CHAR_H 8
#define NUM_CHARS 184

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
#define PHYSICSTATE 16  //0x10, 0001 0000  physic-state
#define RENDERSTATE 32  //0x20, 0010 0000  render-state

#define SPRITEMASK 15  //0x0F, 0000 1111
#define STATEMASK 240  //0xF0, 1111 0000
#define TYPEMASK 192   //0xC0, 1100 0000

//types of monsters
#define TYPE_UD 0
#define TYPE_LR 64
#define TYPE_RT 128
#define TYPE_LT 192

//gamestates
#define MENULENGTH 6
#define MENU 1
#define RUNNING 0
#define GAMEOVER 2
#define SCORE 3

#define LIVES 20

//decryption
#define BITREF 6
#define BITCOUNT 3
#define MINMATCH 3
#define CODELENGTH 4

//KC85-Farben         rgb565     rgb888
#define KCF_SCHWARZ   0x0000 //"#030205"
#define KCF_BLAU      0x0836 //"#0A05B6"
#define KCF_ROT       0xc863 //"#CA0F19"
#define KCF_PURPUR    0xc8f7 //"#CA1CBB"
#define KCF_GRUEN     0x2e8a //"#2ED157"
#define KCF_TUERKIS   0x2f38 //"#2DE7C0"
#define KCF_GELB      0xe74b //"#E7E95D"
#define KCF_WEISS     0xf79f //"#F3F0F9"
#define KCF_VIOLETT   0x6078 //"#670FC7"
#define KCF_ORANGE    0xcc23 //"#CD871B"
#define KCF_PURPURROT 0xc88f //"#CF1178"
#define KCF_GRUENBLAU 0x26f3 //"#27DD9A"
#define KCF_BLAUGRUEN 0x235a //"#276BD3"
#define KCF_GELBGRUEN 0x8f08 //"#8FE041"

#define KCB_SCHWARZ   0x0000 //"#030205"
#define KCB_BLAU      0x0011 //"#04028F"
#define KCB_ROT       INDEX_ORANGE //0x9000 //"#920205" PALETTE[] Hintergrund Statuszeile
#define KCB_PURPUR    0x8010 //"#870280"
#define KCB_GRUEN     0x03e2 //"#027E13"
#define KCB_TUERKIS   INDEX_ORANGE //0x044c //"#028965" PALETTE_HIGHSCORE[] Hintergrund Higscore
#define KCB_GELB      0x7be0 //"#7A7F04"
#define KCB_WEISS     0x7bf0 //"#7D7C80"
