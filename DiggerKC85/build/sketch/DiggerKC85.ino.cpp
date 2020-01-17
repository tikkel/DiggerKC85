#include <Arduino.h>
#line 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
#include <Gamebuino-Meta.h>
#include "DiggerKC85.h"
#include "Sprites.h"
#include "Level.h"
#include "Menu.h"
#include "Sounds.h"

byte world[WORLD_W][WORLD_H];

//generate Multilang-Array for pause menu
const MultiLang* Pausemenu_easy[MENULENGTH]  = {
  lang_resume,
  lang_new,
  lang_levelup,
  lang_leveldown,
  lang_toggle_easy,
  lang_score
};
const MultiLang* Pausemenu_hard[MENULENGTH]  = {
  lang_resume,
  lang_new,
  lang_levelup,
  lang_leveldown,
  lang_toggle_hard,
  lang_score
};

// cursor
int cursor_x, cursor_y;
int camera_x, camera_y;
bool scroll_xp, scroll_xm, scroll_yp, scroll_ym = false;
int display_width = gb.display.width();
int display_height = gb.display.height();

int score = 0;
int scoreeasy;
int scorehard;
int highscore[7] = { 0, 0, 0, 0, 0, 0, 0, };
char scorename[7][9+1] = { "         ", "         ", "         ", "         ", "         ", "         ", "         ", };
int countdown = 5000;
byte diams_need, diamonds;
byte curlevel = 0;
byte maxlevel = 0;
byte maxhard = 0;
byte curhard = 0;
byte maxeasy = 0;
byte cureasy = 0;
byte lives = LIVES;
byte liveseasy = LIVES;
byte liveshard = LIVES;
bool dead = false;
bool gamemode = EASY;
bool temp_gamemode;
byte gamestate = PAUSED;
int  codepos = 0;
int  worldpos = 0;
byte dir = DIGGER_I;
byte ldir = DIGGER_I;
byte digger_step = 0;
byte idle_step = 0;
bool countdown_step = false;
bool countdown_toggle = false;
byte idle_sprite = 0;
byte timer = 0;
unsigned long starttime=0;

bool sfx_diamond = false;
bool sfx_rock    = false;
bool sfx_step    = false;
bool gfx_inverse = false;

bool digger_in_idle = true;
byte zufall_x = 0;
byte zufall_y = 0;
byte idle = 0;

//Statuszeile
ColorIndex zfg, zbg; //foreground- and backgroundcolor
String zs = String(score);
String zc = String(countdown);
String zd = String(diamonds);
String zr = String(curlevel + 1);
String zl = String(lives);
String hs = String(score);

//16 colors index palette
const Color PALETTE[] = {
  (Color)0x0000, //0 INDEX_BLACK      KCF/B_SCHWARZ
  (Color)0x0836, //1 INDEX_DARKBLUE   KCF_BLAU
  (Color)0xc8f7, //2 INDEX_PURPLE     KCF_PURPUR
  (Color)0x6078, //3 INDEX_GREEN      KCF_VIOLETT
  (Color)0xcc23, //4 INDEX_BROWN      KCF_ORANGE    gb.gui.menu-Akzent?
  (Color)0x235a, //5 INDEX_DARKGRAY   KCF_BLAUGRUEN gb.gui.menu-Hintergrund?
  (Color)0x8f08, //6 INDEX_GRAY       KCF_GELBGRUEN
  (Color)0xf79f, //7 INDEX_WHITE      KCF_WEISS     gb.gui.menu-Vordergrund?
  (Color)0xc863, //8 INDEX_RED        KCF_ROT
  (Color)0x9000, //9 INDEX_ORANGE     KCB_ROT
  (Color)0xe74b, //a INDEX_YELLOW     KCF_GELB
  (Color)0x2e8a, //b INDEX_LIGHTGREEN KCF_GRUEN
  (Color)0x7bf0, //c INDEX_LIGHTBLUE  KCB_WEISS
  (Color)0x0011, //d INDEX_BLUE       KCB_BLAU
  (Color)0xc88f, //e INDEX_MAGENTA    KCF_PURPURROT
  (Color)0x2f38  //f INDEX_BEIGE      KCF_TUERKIS
};

#line 106 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void setup();
#line 125 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void loop();
#line 217 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void initGame();
#line 222 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void newGame();
#line 236 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void initWorld(byte _level);
#line 267 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
byte getBits(byte _level, byte bits);
#line 278 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void setTile( byte sprite);
#line 295 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void nextLevel();
#line 308 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void viewScore();
#line 331 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void loadScore();
#line 343 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void saveScore();
#line 380 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void loadGame();
#line 398 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void saveGame();
#line 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Monster.ino"
void monster_die(byte x, byte y);
#line 43 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Monster.ino"
void moveMonster(byte x, byte y, byte sprite);
#line 79 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Monster.ino"
void sIND(byte x, byte y, byte sprite);
#line 83 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Monster.ino"
byte getNewDirection(byte x, byte y);
#line 137 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Monster.ino"
bool testMove(byte x, byte y, byte monster);
#line 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Physics.ino"
void updatePhysics();
#line 27 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Physics.ino"
void falling(byte x, byte y, byte sprite);
#line 65 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Physics.ino"
void moveRock(char xoff, char yoff);
#line 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Player.ino"
void movePlayer(int8_t xoff, int8_t yoff);
#line 8 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Player.ino"
void handlePlayer(int8_t xoff, int8_t yoff);
#line 36 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Player.ino"
void die();
#line 46 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Player.ino"
void updateCursor();
#line 5 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Render.ino"
void drawWorld();
#line 7 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Sounds.ino"
void Fill_TonBuffer(int ton_low, int ton_high, int rate);
#line 106 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
void setup(){
  //SerialUSB.begin(9600);
  gb.begin();
  gb.display.setPalette(PALETTE);
  gb.setFrameRate(36);
  Fill_TonBuffer(TON_LOW, TON_HIGH, TON_RATE);

  SerialUSB.printf( "lives: %i\n", lives );
  gamemode = HARD;
    loadGame();
    saveGame();
  gamemode = EASY;
    loadGame();
    saveGame();
  SerialUSB.printf( "lives: %i\n", lives );
  
  initGame();
}

void loop() {
    while (!gb.update());
    
    switch (gamestate) {
      case PAUSED:
        gb.lights.clear();
        switch ( gb.gui.menu(lang_title, gamemode ? Pausemenu_hard : Pausemenu_easy, MENULENGTH) ) {
          case -1: //nothing selected
            break;
          case 0: //resume game
            if (lives != 0)
              gamestate = RUNNING;
            break;
          case 1: //new game
            newGame();
            initWorld(curlevel);
            break;
          case 2: //lvlup
            //SerialUSB.printf( "lives: %i\n", lives );
            if (curlevel < maxlevel)
              curlevel++;
            initWorld(curlevel);
            saveGame();
            dead = false;
            gamestate = RUNNING;
            break;
          case 3: //lvldown
            if (curlevel > 0)
              curlevel--;
            initWorld(curlevel);
            saveGame();
            dead = false;
            gamestate = RUNNING;
            break;
          case 4: //gamemode
            gamemode = !gamemode;
            gb.save.set(0, gamemode);
            curlevel = (gamemode == EASY) ? cureasy : curhard;
            maxlevel = (gamemode == EASY) ? maxeasy : maxhard;
            lives    = (gamemode == EASY) ? liveseasy : liveshard;
            score    = (gamemode == EASY) ? scoreeasy : scorehard;
            dead = false;
            initWorld(curlevel);
            break;
          case 5: //highscore
            loadScore();
            gamestate = SCORE;
            break;
        };
        break;

      case SCORE:
        if (gb.buttons.released(BUTTON_A))
          gamestate = PAUSED;
        if (lives <1 || lives>LIVES) //update the highscore if 
          saveScore();
        viewScore();
        if (gb.frameCount % 10)
          gb.lights.drawImage(0, 0, ledsprite_highscore);
        
        //for debugging: show some stats
        /*
        if ( gb.frameCount % 10 == 0 ) {
          SerialUSB.printf( "CPU load: %i %% \n", gb.getCpuLoad() );
          SerialUSB.printf( "RAM free: %i bytes \n", gb.getFreeRam() );
        }
        */
        break;
 
      case RUNNING:
        //pause the game if menu is pressed
        if (gb.buttons.pressed(BUTTON_MENU))
          gamestate = PAUSED;
        updateCursor();   //Player  ( digger action )
        updatePhysics();  //Physics ( falling() rocks & diamonds, moveMonster() )
        drawWorld();      //Render  ( scrolling screen, draw tiles )
        if (lives <1 || lives>LIVES) {
          loadScore();
          gamestate=SCORE;
        }

        //for debugging: show some stats
        if ( gb.frameCount % 10 == 0 ) {
          SerialUSB.printf( "CPU load: %i %% \n", gb.getCpuLoad() );
          //SerialUSB.printf( "RAM free: %i bytes \n", gb.getFreeRam() );
        }
        
        break;
    }

}

void initGame() {
  loadGame();
  initWorld(curlevel);
}

void newGame() {
  score = 0;
  curlevel = 0;
  lives = LIVES;
  maxeasy = 0;
  cureasy = 0;
  maxhard = 0;
  curhard = 0;
  gamestate = RUNNING;
  dead = false;
  saveGame();
}

//decoder of compressed level data
void initWorld(byte _level) {
  gb.lights.clear();
  zfg = gamemode ? INDEX_WHITE : INDEX_WHITE; //KCF_WEISS : KCF_WEISS
  zbg = gamemode ? INDEX_ORANGE : INDEX_BLACK; //KCB_ROT : KCB_SCHWARZ
  countdown = 5000;
  countdown_step = false;
  countdown_toggle = false;
  diamonds = 0;
  codepos = 0;
  worldpos = 0;
  diams_need = getBits(_level, 8);
  while (worldpos < WORLD_H * WORLD_W) {
    if (getBits(_level, 1)) {
      byte r = getBits(_level, BITREF);
      byte c = getBits(_level, BITCOUNT) + MINMATCH;

      for (byte i = 0; i < c; i++) {
        if (worldpos < WORLD_W * WORLD_H) {
          int refpos = worldpos - r;
          setTile(world[refpos % WORLD_W][refpos / WORLD_W]);
          worldpos++;
        }
      }
    } else {
      setTile(getBits(_level, CODELENGTH));
      worldpos++;
    }
  }
}

//helper for decompressor, returns number of bits of an compressed level starting at (bit-) position "codepos" 
byte getBits(byte _level, byte bits) {
  //uses global var codepos for bitoffset
  const byte *pos = levels[_level] + codepos / 8;
  int w = pgm_read_byte(pos) * 256 + pgm_read_byte(pos + 1);
  w >>= (16 - (codepos % 8) - bits); //shift bits to right
  w = ( w & ((1 << bits) - 1)); //mask desired bits
  codepos += bits;
  return (byte)w;
}

// set Tile to worldmap. Note: codes in level data have slightly different meanings than in world map.
void setTile( byte sprite) {
  byte x = worldpos % WORLD_W;
  byte y = worldpos / WORLD_W;
  switch (sprite) {
    case MONSTER_RT: world[x][y] = MONSTER_R | TYPE_RT | RENDERSTATE; break;
    case MONSTER_LT: world[x][y] = MONSTER_L | TYPE_LT | RENDERSTATE; break;
    case MONSTER_D:  world[x][y] = MONSTER_D | TYPE_UD | RENDERSTATE; break;
    case MONSTER_U:  world[x][y] = MONSTER_U | TYPE_UD | RENDERSTATE; break;
    case MONSTER_L:  world[x][y] = MONSTER_L | TYPE_LR | RENDERSTATE; break;
    case MONSTER_R:  world[x][y] = MONSTER_R | TYPE_LR | RENDERSTATE; break;
    default: world[x][y] = sprite | RENDERSTATE; break;
  }
  if (sprite == PLAYER) {
    cursor_x =  x;
    cursor_y = y;
  }
}
void nextLevel() {
  if (curlevel < NUM_LEVELS-3) {
    (gamemode == EASY) ? cureasy++ : curhard++;
    maxeasy = max(maxeasy, cureasy);
    maxhard = max(maxhard, curhard);
    curlevel++;
    if (maxlevel < curlevel)
      maxlevel++;
  }
  initWorld(curlevel);
  saveGame();
}

void viewScore() {
  gb.display.fill(LIGHTGREEN);
  gb.display.setFontSize(2);
  gb.display.setColor(YELLOW);
  gb.display.setCursor(72, 0);
  gb.display.print( gamemode ? lang_score_hard : lang_score_easy );
  gb.display.setCursor(8, 12); //4,6
  gb.display.print( lang_highscore );
  gb.display.fillRect(8 , 24, 88, 6);
    for (byte i = 0; i < 7; i++) {
      gb.display.setCursor(16, 36 + (i * 12));
      //score
      hs = String( highscore[i] );
      while (hs.length() < 5)
        hs = String( "0" + hs );
      gb.display.print( hs );
      //space
      gb.display.print( "  " );
      //name
      gb.display.print( scorename[i] );
    }
}

void loadScore() {
  byte offset;
  if ( gamemode )
    offset = 9; //blocks 9-22 hard highscore
  else
    offset = 23; //blocks 23-37 easy highscore
  for (byte i = 0; i < 7; i++) {
    highscore[i] = gb.save.get(i + offset);
    gb.save.get(i + offset + 7, scorename[i], 9+1);
  }
}

void saveScore() {
  //prüfe Zeile 0-6
  for (byte j = 0; j < 7; j++) {
    //ist der Highscore größer als die aktuelle Zeile?
    if (score > highscore[j]) {
      
      //Zeilen unterhalb, nach unten kopieren
      for (byte z = 5; z>=j && z<6; z--) {
        //SerialUSB.printf( "z:%u j:%u\n", z, j );
        highscore[z+1] = highscore[z];
        strcpy(scorename[z+1], scorename[z]);
      }
      
      //setze neuen scorename
      char temp_scorename[1][9+1];
      strcpy(temp_scorename[1], scorename[j+1]); //workaround
      gb.getDefaultName( scorename[j] );       //funktioniert nicht richtig, überschreibt [j+1] mit "n"
      strcpy(scorename[j+1], temp_scorename[1]); //workaround
      gb.gui.keyboard( lang_name, scorename[j], 9 );
      
      //setze neuen highscore
      highscore[j] = score;
      score = 0;
      saveGame();
      byte offset;
      if ( gamemode )
        offset = 9; //blocks 9-22 hard highscore
      else
        offset = 23; //blocks 23-37 easy highscore
      for (byte i = 0; i < 7; i++) {
        gb.save.set(i + offset, highscore[i]);
        gb.save.set(i + offset + 7, scorename[i]);
      }
    }
  }
}

void loadGame(){
  gamemode  = gb.save.get(0);
  cureasy   = gb.save.get(1);
  maxeasy   = gb.save.get(2);
  curhard   = gb.save.get(3);
  maxhard   = gb.save.get(4);
  liveseasy = gb.save.get(5);
  liveshard = gb.save.get(6);
  scoreeasy = gb.save.get(7);
  scorehard = gb.save.get(8);
  maxeasy  = max(maxeasy, cureasy);
  maxhard  = max(maxhard, curhard);
  curlevel = (gamemode == EASY) ? cureasy : curhard;
  maxlevel = (gamemode == EASY) ? maxeasy : maxhard;
  lives    = (gamemode == EASY) ? liveseasy : liveshard;
  score    = (gamemode == EASY) ? scoreeasy : scorehard;
}

void saveGame() {
  (gamemode == EASY) ? cureasy=curlevel : curhard=curlevel;
  (gamemode == EASY) ? maxeasy=maxlevel : maxhard=maxlevel;
  (gamemode == EASY) ? liveseasy=lives : liveshard=lives;
  (gamemode == EASY) ? scoreeasy=score : scorehard=score;
  gb.save.set(0, gamemode);
  gb.save.set(1, cureasy);
  gb.save.set(2, maxeasy);
  gb.save.set(3, curhard);
  gb.save.set(4, maxhard);
  gb.save.set(5, liveseasy);
  gb.save.set(6, liveshard);
  gb.save.set(7, scoreeasy);
  gb.save.set(8, scorehard);
}

#line 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Monster.ino"
void monster_die(byte x, byte y) {
  if (   world[x - 1][y - 1] == PLAYER
         || world[x - 1][y] == PLAYER
         || world[x - 1][y + 1] == PLAYER
         || world[x][y - 1] == PLAYER
         || world[x][y + 1] == PLAYER
         || world[x + 1][y - 1] == PLAYER
         || world[x + 1][y] == PLAYER
         || world[x + 1][y + 1] == PLAYER
     ) die();
  if (gamemode == EASY) {
    world[x][y] = DIAMOND | RENDERSTATE;
    sIND(x - 1, y + 1, DIAMOND);
    sIND(x  , y + 1, DIAMOND);
    sIND(x + 1, y + 1, DIAMOND);
    sIND(x - 1, y - 1, DIAMOND);
    sIND(x - 1, y  , DIAMOND);
    sIND(x  , y - 1, DIAMOND);
    sIND(x + 1, y - 1, DIAMOND);
    sIND(x + 1, y  , DIAMOND);
    sfx_rock = true;
    gb.lights.fill(WHITE);
    gb.tft.invertDisplay( true );
    gfx_inverse = true;
  } else {
    world[x][y] = EMPTY | RENDERSTATE;
    sIND(x - 1, y + 1, EMPTY);
    sIND(x  , y + 1, EMPTY);
    sIND(x + 1, y + 1, EMPTY);
    sIND(x - 1, y - 1, EMPTY);
    sIND(x - 1, y  , EMPTY);
    sIND(x  , y - 1, EMPTY);
    sIND(x + 1, y - 1, EMPTY);
    sIND(x + 1, y  , EMPTY);
    sfx_rock = true;
    gb.lights.fill(WHITE);
    gb.tft.invertDisplay( true );
    gfx_inverse = true;
  }

}

void moveMonster(byte x, byte y, byte sprite) {

  if ( (gb.frameCount % (gamemode ? 4 : 8) == 0) && ((world[x][y] & RENDERSTATE) == 0) ) {
    
    //straight forward preferred, if not: search new direction
    if (sprite == MONSTER_D) {
      switch (world[x][y + 1] & SPRITEMASK) {
        case EMPTY: world[x][y + 1] = world[x][y] | RENDERSTATE; world[x][y] = EMPTY | RENDERSTATE; break;
        case PLAYER: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }
    else if ((sprite == MONSTER_U)) {
      switch (world[x][y - 1] & SPRITEMASK ) {
        case EMPTY: world[x][y - 1] = (world[x][y] | RENDERSTATE); world[x][y] = EMPTY | RENDERSTATE; break;
        case PLAYER: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }
    else if ((sprite == MONSTER_L)) {
      switch (world[x - 1][y] & SPRITEMASK ) {
        case EMPTY: world[x - 1][y] = (world[x][y] | RENDERSTATE); world[x][y] = EMPTY | RENDERSTATE; break;
        case PLAYER: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }
    else if ((sprite == MONSTER_R)) {
      switch (world[x + 1][y] & SPRITEMASK ) {
        case EMPTY: world[x + 1][y] = (world[x][y] | RENDERSTATE); world[x][y] = EMPTY | RENDERSTATE; break;
        case PLAYER: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }

  }
}
void sIND(byte x, byte y, byte sprite) { //setIfNotWorldBorder
  if (x > 0 && x < WORLD_W - 1 && y > 0 && y < WORLD_H - 1)   world[x][y] = sprite | RENDERSTATE;
}

byte getNewDirection(byte x, byte y) {
  byte type = world[x][y] & TYPEMASK;
  byte sprite = world[x][y] & SPRITEMASK;
  switch (type) {
    case TYPE_UD:
      if (sprite == MONSTER_D) {
        if ( (world[x][y - 1] & SPRITEMASK) == EMPTY )
          sprite = MONSTER_U;
      }
      else {
        if ( (world[x][y + 1] & SPRITEMASK) == EMPTY )
          sprite = MONSTER_D;
      }
      break;
    case TYPE_LR:
      if (sprite == MONSTER_R) {
        if ( (world[x - 1][y] & SPRITEMASK) == EMPTY )
          sprite = MONSTER_L;
      }
      else {
        if ( (world[x + 1][y] & SPRITEMASK) == EMPTY )
          sprite = MONSTER_R;
      }
      break;
    case TYPE_RT:
      //rechts [ *>]
      sprite++; if (sprite > MONSTER_R) sprite = MONSTER_D;
        if (testMove(x, y, sprite))
          break;
      //links [<*<]
      sprite--; sprite--; if (sprite < MONSTER_D) sprite = MONSTER_R; 
        if (testMove(x, y, sprite))
          break;
      //umkehr [>* ]
      sprite--; if (sprite < MONSTER_D) sprite = MONSTER_R;
        if (testMove(x, y, sprite))
          break;
    case TYPE_LT:
      //rechts [<* ]
      sprite--; if (sprite < MONSTER_D) sprite = MONSTER_R;
        if (testMove(x, y, sprite))
          break;
      //links [>*>]
      sprite++; sprite++; if (sprite > MONSTER_R) sprite = MONSTER_D;
        if (testMove(x, y, sprite))
          break;
      //umkehr [>* ]
      sprite++; if (sprite > MONSTER_R) sprite = MONSTER_D;
        if (testMove(x, y, sprite))
          break;
  }
  return sprite + type;
}

bool testMove(byte x, byte y, byte monster) {
  switch (monster) {
    case MONSTER_U:
      if (world[x][y - 1] == PLAYER) die();
      return (world[x][y - 1] == EMPTY) ? true : false; break;
    case MONSTER_L:
      if (world[x - 1][y] == PLAYER) die();
      return (world[x - 1][y] == EMPTY) ? true : false; break;
    case MONSTER_D:
      if (world[x][y + 1] == PLAYER) die();
      return (world[x][y + 1] == EMPTY) ? true : false; break;
    case MONSTER_R:
      if (world[x + 1][y] == PLAYER) die();
      return (world[x + 1][y] == EMPTY) ? true : false; break;
    default:
      return true; break;
  }
}

#line 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Physics.ino"
void updatePhysics() {
  //Skip borders in Check (x,y=1)
  if (gb.frameCount % (gamemode ? 4 : 5) == 0) {
    for (byte y = 1; y < WORLD_H - 1; y++) {
      for (byte x = 1; x < WORLD_W - 1; x++) {
        //byte sprite = world[x][y] & ~PHYSICSTATE & ~TYPEMASK;
        byte sprite = world[x][y] & ~STATEMASK;
        switch (sprite) {
          case ROCK: falling(x, y, ROCK); break;               //rock
          case DIAMOND: falling(x, y, DIAMOND); break;         //diam
          case MONSTER_D: moveMonster(x, y, MONSTER_D); break; //mon_down
          case MONSTER_U: moveMonster(x, y, MONSTER_U); break; //mon_up
          case MONSTER_L: moveMonster(x, y, MONSTER_L); break;
          case MONSTER_R: moveMonster(x, y, MONSTER_R); break;
          default: break;
        }
      }
    }
    for (byte y = 1; y < WORLD_H - 1; y++) {
      for (byte x = 1; x < WORLD_W - 1; x++) {
        world[x][y] &= ~PHYSICSTATE;
      }
    }
  }
}

void falling(byte x, byte y, byte sprite) {
  if ( (world[x][y] & PHYSICSTATE) > 0 ) {
    switch (world[x][y + 1] & SPRITEMASK) {
      case PLAYER: die(); sfx_rock = true; break;
      case MONSTER_D: monster_die(x, y + 1);return; break;
      case MONSTER_U: monster_die(x, y + 1);return; break;
      case MONSTER_L: monster_die(x, y + 1);return; break;
      case MONSTER_R: monster_die(x, y + 1);return; break;
      case EMPTY: break;
      default: sfx_rock = true; break;
    }
  }
  else {
      //gerade runterfallen
      if (world[x][y + 1] == EMPTY) {
        world[x][y + 1] = sprite | PHYSICSTATE| RENDERSTATE;
        world[x][y] = EMPTY | RENDERSTATE;
        return;
      }
      if (world[x][y + 1] == ROCK || world[x][y + 1] == DIAMOND) {
        //rechts runterfallen
        if (world[x + 1][y + 1] == EMPTY && world[x + 1][y] == EMPTY) {
          world[x + 1][y + 1] = sprite | PHYSICSTATE | RENDERSTATE;
          world[x][y] = EMPTY | RENDERSTATE;
        //links runterfallen
        } else if (world[x - 1][y + 1] == EMPTY && world[x - 1][y] == EMPTY) {
          world[x - 1][y + 1] = sprite | PHYSICSTATE | RENDERSTATE;
          world[x][y] = EMPTY | RENDERSTATE;
        }
        return;
      }
      if ((sprite == ROCK) && (world[x][y + 1] == CHANGER) && (world[x][y + 2] == EMPTY)) {
        world[x][y] = EMPTY | RENDERSTATE;
        world[x][y + 2] = DIAMOND | PHYSICSTATE | RENDERSTATE;
      }
  }
}

void moveRock(char xoff, char yoff) {
  if (yoff != 0) {
    return;
  }
  if (gb.buttons.repeat(BUTTON_RIGHT, 8) && world[cursor_x + 2][cursor_y] == EMPTY ) {
    world[cursor_x + 2][cursor_y] = ROCK | RENDERSTATE;
    movePlayer(1, 0);
    sfx_step = true;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 8) && world[cursor_x - 2][cursor_y] == EMPTY ) {
    world[cursor_x - 2][cursor_y] = ROCK | RENDERSTATE;
    movePlayer(-1, 0);
    sfx_step = true;
  }
}

#line 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Player.ino"
void movePlayer(int8_t xoff, int8_t yoff) {
  world[cursor_x][cursor_y] = EMPTY | PHYSICSTATE | RENDERSTATE;
  cursor_x = cursor_x + xoff;
  cursor_y = cursor_y + yoff;
  world[cursor_x][cursor_y] = PLAYER;
}

void handlePlayer(int8_t xoff, int8_t yoff) {
  ldir = dir;
  //dir = 8 + xoff * 2 + yoff;
  dir = DIGGER_I + xoff * 2 + yoff;
  if (dir != ldir) digger_step = 0;
  timer = 4;
  byte target = world[cursor_x + xoff][cursor_y + yoff];
  target &= ~PHYSICSTATE;
  switch ( target ) {
    case EMPTY: movePlayer(xoff, yoff); sfx_step = true; break;
    case WALL: break;
    case ROCK: moveRock(xoff, yoff); break;
    case SOIL: movePlayer(xoff, yoff); sfx_step = true; break;
    case DIAMOND: movePlayer(xoff, yoff); diamonds++; sfx_diamond = true; score += 3; break;
    case CHANGER: break;
    case DOOR:
      if (diams_need <= diamonds) {
        movePlayer(xoff, yoff);
        sfx_diamond = true;
        score += 100;
        nextLevel();

      }
      break;
    default: die();
  }
}

void die() {
  byte x = cursor_x; 
  byte y = cursor_y;
  world[x][y] = DEATH | RENDERSTATE;
  dead = true;
  sfx_rock = true;
  lives--;
  saveGame();
}

void updateCursor() {
  if (gfx_inverse) {
      gb.tft.invertDisplay( false );
      gfx_inverse = false;
    }
  if ( gb.buttons.released(BUTTON_A) && !dead ) {
    sfx_rock = true;
    die();
  }
  else if ( gb.buttons.released(BUTTON_A) && dead ) {
    sfx_diamond = true;
    initWorld(curlevel);
    dead = false;
  }
  else if (!dead) {
  
    if (!sfx_diamond && !sfx_rock) {
      if (diamonds >= diams_need )
        gb.lights.drawImage(0, 0, ledsprite_collected);
      else
        gb.lights.clear();
    }
  
    if (countdown_step)
      countdown--;
    countdown_step ^= 1;
    if (countdown == 0)
      die();
  
    if (gb.buttons.repeat(BUTTON_RIGHT, 4)) {
      handlePlayer(1, 0);
    }
    if (gb.buttons.repeat(BUTTON_LEFT, 4)) {
      handlePlayer(-1, 0);
    }
    if (gb.buttons.repeat(BUTTON_DOWN, 4)) {
      handlePlayer(0, 1);
    }
    if (gb.buttons.repeat(BUTTON_UP, 4)) {
      handlePlayer(0, -1);
    }

  }

  // S O F T - S C R O L L I N G
  //Zielposition der Kamera um Digger (cursor) zu Zentrieren
  int camera_x_target = cursor_x * SPRITE_W - display_width / 2 + SPRITE_W / 2;
  int camera_y_target = cursor_y * SPRITE_H - display_height / 2 + SPRITE_H / 2;
  
  // nach rechts scrollen
  if (camera_x < camera_x_target - SPRITE_W * 2) { //scrolling ON
    scroll_xp = true;
    scroll_xm = false;
  }
  else if (camera_x == camera_x_target) //scrollOff, wenn zentriert
    scroll_xp = false;
  if (scroll_xp) {
    camera_x = camera_x + 2; //scrolle 2 pixel
    if (camera_x > WORLD_W * SPRITE_W - display_width) { 
      camera_x = WORLD_W * SPRITE_W - display_width;
      scroll_xp = false;
    }
  }
  // nach links scrollen
  if (camera_x > camera_x_target + SPRITE_W * 2) { //scrolling ON
    scroll_xm = true;
    scroll_xp = false;
  }
  else if (camera_x == camera_x_target) //scrollOff, wenn zentriert
    scroll_xm = false;
  if (scroll_xm) {
    camera_x = camera_x - 2; //scrolle 2 pixel
    if (camera_x < 0) {
      camera_x = 0;
      scroll_xm = false;
    }
  }

  // nach unten scrollen
  if (camera_y < camera_y_target - SPRITE_H * 2) { //scrolling ON
    scroll_yp = true;
    scroll_ym = false;
  }
  else if (camera_y == camera_y_target) //scrolling OFF, wenn zentriert
    scroll_yp = false;
  if (scroll_yp) {
    camera_y = camera_y + 2; //scrolle 2 pixel
    if (camera_y > WORLD_H * SPRITE_H - display_height) {
      camera_y = WORLD_H * SPRITE_H - display_height;
      scroll_yp = false;
    }
  }
  // nach oben scrollen
  if (camera_y > camera_y_target + SPRITE_H * 2) { //scrolling ON
    scroll_ym = true;
    scroll_yp = false;
  }
  else if (camera_y == camera_y_target) //scrolling OFF, wenn zentriert
    scroll_ym = false;
  if (scroll_ym) {
    camera_y = camera_y - 2; //scrolle 2 pixel
    if (camera_y < -12) { //12 ist gleich die Menüzeilenhöhe
      camera_y = -12;
      scroll_ym = false;
    }
  }

}

#line 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Render.ino"
byte diamond_step = 7;
byte digger_l_steps[6] = { 18, 19, 20, 19, 18, 17 };
byte digger_r_steps[6] = { 27, 28, 29, 28, 27, 26 };

void drawWorld() {

  //diamond-animation
  if (diamond_step > 6) {
    diamond_step = 0; }
  else {
    diamond_step++; }
  //SerialUSB.printf( "diamant_animation: %i\n", DIAMOND1 + diamond_step/2 );

  for (byte y = 0; y < WORLD_H; y++) {
    int y_screen = y * SPRITE_H - camera_y; //coordinates on the screen depending on the camera position
    
    for (byte x = 0; x < WORLD_W; x++) {
      int x_screen = x * SPRITE_W - camera_x; //coordinates on the screen depending on the camera position
      
      byte sprite = world[x][y];
      sprite &= SPRITEMASK;

      idle = world[zufall_x][zufall_y];

      //diamond-animation
      if (sprite == DIAMOND) {
        sprite = DIAMOND1 + diamond_step/2;
        world[x][y] = DIAMOND | RENDERSTATE;}

      //digger-animation
      if (sprite == PLAYER) {
        world[x][y] = PLAYER | RENDERSTATE;
        switch (dir) {
          case DIGGER_L:
            digger_in_idle = false;
            sprite = digger_l_steps[digger_step/2]; //18,19,20,19,18,17, jedes Sprite wird x2 ausgelesen
            digger_step++;
            if (digger_step > 11) //12 Animationsschritte, 0-11
              digger_step = 0;
            //SerialUSB.printf( "sprite_l: %i\n", sprite );
            break;
          case DIGGER_U:
            digger_in_idle = false;
            sprite = 21 + digger_step/4; //21,22, jedes Sprite wird x4 ausgelesen
            digger_step++;
            if (digger_step > 7) //8 Animationsschritte, 0-7
              digger_step = 0;
            //SerialUSB.printf( "sprite_u: %i\n", sprite );
            break;
          case DIGGER_I:
            zufall_x++;
            if ( zufall_x > WORLD_W ) {
              zufall_x = 0;
              zufall_y++;
              if ( zufall_y > WORLD_H ) {
                zufall_y = 0;
                zufall_x = 0;
              }
            }
            if ( (!digger_in_idle) && (idle == ROCK) ) {
              //ROCK --> blinzeln
              digger_in_idle = true;
              idle_sprite = 30;
            }
            else if ( (!digger_in_idle) && (idle == DIAMOND) ) {
              //DIAMOND --> stampfen
              digger_in_idle = true;
              idle_sprite = 32;
            }
            else if ( digger_in_idle ) {
              //ein paar takte warten und wieder freigeben
              idle_step++;
              if ( (idle_step > 5) && (idle_sprite == 30) )
                idle_sprite = 31;
              sprite = idle_sprite;
              if ( idle_step > 11 ) {
                idle_step = 0;
                digger_in_idle = false;
                sprite = 23; //22
                if ( idle_sprite == 32 )
                  sfx_step = true;
              }
            }
            else {
              sprite = 23;
            }
            break;
          case DIGGER_D:
            digger_in_idle = false;
            sprite = 24 + digger_step/4; //24,25, jedes Sprite wird x4 ausgelesen
            digger_step++;
            if (digger_step > 7) //8 Animationsschritte, 0-7
              digger_step = 0;
            //SerialUSB.printf( "sprite_d: %i\n", sprite );
            break;
          case DIGGER_R:
            digger_in_idle = false;
            sprite = digger_r_steps[digger_step/2]; //27,28,29,28,27,26, jedes Sprite wird x2 ausgelesen
            digger_step++;
            if (digger_step > 11) //12 Animationsschritte, 0-11
              digger_step = 0;
            //SerialUSB.printf( "sprite_r: %i\n", sprite );
            break;
        }
      }

      
      
      // don't draw sprites which are out of the screen
      //full refresh
      if ( !(x_screen < -SPRITE_W-1 || x_screen > display_width-1 || y_screen < 1 || y_screen > display_height-1) ) {
      //partial refresh
      //if ( !(x_screen < -SPRITE_W-1 || x_screen > display_width-1 || y_screen < 1 || y_screen > display_height-1) && (world[x][y] & RENDERSTATE)==RENDERSTATE ) {
      //no refresh
      //if ( (world[x][y] & RENDERSTATE) == RENDERSTATE ) {
        spritesheet.setFrame(sprite);
        gb.display.drawImage(x_screen, y_screen, spritesheet);
      }

      world[x][y] &= ~RENDERSTATE;

    }
  }

  // LED_FX and sound_FX
  if (gb.frameCount % 4 == 0) {
    if (sfx_diamond) {
      gb.sound.play( ton_buffer[TON_DIAMANT], ton_laenge[TON_DIAMANT] );
      gb.lights.drawImage(0, 0, ledsprite_collect);
    }
    else if ( sfx_rock ) {
      gb.sound.play( ton_buffer[TON_STEIN], ton_laenge[TON_STEIN] );
      gb.lights.drawImage(0, 0, ledsprite_falled);
    }
    else if ( sfx_step )
      gb.sound.play( ton_buffer[TON_SCHRITT], ton_laenge[TON_SCHRITT] );
    else if ( dead )
      gb.lights.drawImage(0, 0, ledsprite_highscore);
    sfx_diamond = false;
    sfx_rock = false;
    sfx_step = false;
  }

  // nach losgelassener Richtungstaste, wieder auf wartend (idle) zurückstellen (timer default: nach 2 frames)
  if (timer == 0)
    dir = DIGGER_I;
  timer--;

  //
  // statuszeile:_rr_ll*_cccc_dd*00_
  //
  //extern const byte font3x3[]; //a really tiny font
  //extern const byte font3x5[]; //a small but efficient font (default)
  //extern const byte font5x7[]; //a large, comfy font

  //gb.display.setFont(font5x7);
  gb.display.setFontSize(2);
  gb.display.setTextWrap( false );
  gb.display.cursorY = 0;

  // raum
  gb.display.cursorX = 0;
  gb.display.setColor(zfg, zbg);
  zr = String(curlevel + 1);
  while (zr.length() < 2)
    zr = String("0" + zr + " ");
  gb.display.print(zr);

  // leben
  gb.display.cursorX = 20;
  gb.display.setColor(zfg, zbg);
  zl = String(lives);
  while (zl.length() < 2)
    zl = String("0" + zl);
  gb.display.print(zl);
  gb.display.cursorX = 34;
  gb.display.setColor(INDEX_RED, zbg); //KCF_ROT
  gb.display.print(F("\03 "));         //HERZ

  // countdown
  gb.display.cursorX = 46;
  gb.display.setColor(zfg, zbg);
  zc = String(countdown);
  while (zc.length() < 4)
    zc = String("0" + zc);
  if ( (gb.frameCount % 15 == 0) && (countdown < 1000) )
    countdown_toggle ? countdown_toggle = false : countdown_toggle = true; 
  countdown_toggle ? gb.display.print("     ") : gb.display.print(zc + " ");

  // diamanten
  gb.display.cursorX = 82;
  zd = String(diamonds);
  while (zd.length() < 2)
    zd = String("0" + zd);
  gb.display.print(zd);
  gb.display.cursorX = 96;
  gb.display.setColor(INDEX_YELLOW, zbg); //KCF_GELB
  gb.display.print(F("\04"));             //DIAMANT
  gb.display.cursorX = 102;
  gb.display.setColor(zfg, zbg);
  gb.display.print(diams_need);
  gb.display.print(" ");

  // score
  gb.display.cursorX = 122;
  zs = String(score);
  while (zs.length() < 5)
    zs = String("0" + zs);
  gb.display.print(zs);

}

#line 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Sounds.ino"
/* digger sound effects
   forked from original "XDigger" sound.c
   found at http://zenway.ru/page/xdigger
   XDigger  Copyright (C) 1988-99 Alexander Lang
*/

void Fill_TonBuffer(int ton_low, int ton_high, int rate) {

  int i, j, k, n;
  unsigned char augenblicklicherpeak;
  
  // TON_SCHRITT
  augenblicklicherpeak=ton_low;
  for (i=0,j=2; j>0; j--) {
    for(k=0; k<0x40; k++) {
      for (n=0; n <= ( rate / KC_CTC_FREQ_VT256 <<0 ); n++)
        ton_buffer[TON_SCHRITT][ ( rate * i / KC_CTC_FREQ_VT256 <<0 ) + n ] = augenblicklicherpeak;
      i++;
    }
    augenblicklicherpeak = ton_low + ton_high - augenblicklicherpeak;
  }
  ton_laenge[TON_SCHRITT] = (rate * (i-1) / KC_CTC_FREQ_VT256 <<0) + n-1;
  //SerialUSB.printf( "ton_laenge_schritt: %i bytes\n", ton_laenge[TON_SCHRITT]);
  
  // TON_STEIN
  augenblicklicherpeak=ton_low;
  for (i=0,j=0x0ff; ; j++) {
    if (j > 256) j = 1;
    if (j == 0x12) break; //j^TC-Reihe: 255,256,1...18 (^0x14 loops)
    for(k=0;k<j;k++){
      for (n = 0; n <= ( rate / KC_CTC_FREQ_VT16 <<0 ); n++)
        ton_buffer[TON_STEIN][ ( rate * i / KC_CTC_FREQ_VT16 <<0 ) + n ] = augenblicklicherpeak;
      i++;
    }
    augenblicklicherpeak = ton_low + ton_high - augenblicklicherpeak;
  }
  ton_laenge[TON_STEIN] = (rate * (i-1) / KC_CTC_FREQ_VT16 <<0) + n-1;
  //SerialUSB.printf( "ton_laenge_stein: %i bytes\n", ton_laenge[TON_STEIN]);
  
  // TON_DIAMANT
  augenblicklicherpeak=ton_low;
  for (i=0,j=0x40; j>0; j--) {
    for(k=0;k<j;k++) {
      for (n = 0; n <= ( rate / KC_CTC_FREQ_VT16 <<0 ); n++)
        ton_buffer[TON_DIAMANT][ ( rate * i / KC_CTC_FREQ_VT16 <<0 ) + n ] = augenblicklicherpeak;
      i++;
    }
    augenblicklicherpeak = ton_low + ton_high - augenblicklicherpeak;
  }
  ton_laenge[TON_DIAMANT] = (rate * (i-1) / KC_CTC_FREQ_VT16 <<0) + n-1;
  //SerialUSB.printf( "ton_laenge_diamant: %i bytes\n", ton_laenge[TON_DIAMANT]);
  
}

