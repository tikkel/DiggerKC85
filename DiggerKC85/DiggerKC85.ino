#include <Gamebuino-Meta.h>
#include "DiggerKC85.h"
#include "Sprites.h"
#include "Level.h"
#include "Menu.h"
#include "Sounds.h"
#include "Charset.h"

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
bool gamemode = HARD; //EASY|HARD
bool temp_gamemode;
byte gamestate = MENU;
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
bool  clr_flag = true;
ColorIndex zfg, zbg; //foreground- and backgroundcolor
String zs      = String(score);        //Score
bool   zs_flag = true;
String zc = String(countdown);         //Counter
String zd      = String(diamonds);     //Diamanten ist/soll
bool   zd_flag = true;
String zr      = String(curlevel + 1); //Raum
bool   zr_flag = true;
String zl      = String(lives);        //Leben
bool   zl_flag = true;
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
      case MENU:
        gb.lights.clear();
        //Menügrafik
        viewMenu();
        //Tasten abfragen
        //(A)Play
        if (gb.buttons.released(BUTTON_A)) {
          newGame();
          initWorld(curlevel);          
          gamestate = RUNNING;
        }
        //(B)Score
        if (gb.buttons.released(BUTTON_B)) {
          loadScore();
          gamestate = SCORE;
        }
        break;
        
      case SCORE:   
        if (gb.buttons.released(BUTTON_A))
          gamestate = MENU;
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
          gamestate = MENU;          
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
  dead = false;
  saveGame();
}

//decoder of compressed level data
void initWorld(byte _level) {
  zr_flag = true;
  zl_flag = true;
  zd_flag = true;
  zs_flag = true;
  clr_flag = true;
  gb.lights.clear();
  zfg = gamemode ? INDEX_BEIGE : INDEX_BEIGE; //KCF_TUERKIS : KCF_TUERKIS
  zbg = gamemode ? INDEX_ORANGE : INDEX_ORANGE; //KCB_ROT : KCB_SCHWARZ
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

void viewMenu() {
  gb.display.setFontSize(1);
  gb.display.fill(INDEX_ORANGE);    //KCB_ROT
  gb.display.setColor(INDEX_BEIGE); //KCF_TUERKIS
  gb.display.setCursor(0,0);
  
  const char *screen[]={ //Sonderzeichen oktal codiert
    "\234\235\235\235\235\235\235\235\235\235\235\235\235\235\235\235\235\235\235\236",
    "\237\240\241\241\241\241\241\241\241\241\241\241\241\241\241\241\241\241\242\237",
    "\237\243                \251\237",
    "\237\243 \200\201\202\203\204\205\206\207\210\211\212\213\214\215 \251\237",
    "\237\243 \216\217\220\221\222\223\224\225\226\227\230\231\232\233 \251\237",
    "\237\243 \252\253\254\255\256\257\260\261\262\263\264\265\266\267 \251\237",
    "\237\243 ALEXANDER LANG \251\237",
    "\237\243  STEFAN DAHLKE \251\237",
    //"\237\243    MARTIN GUTH \251\237",
    "\237\243 HUMBOLDT-      \251\237",
    "\237\243    -UNIVERSITY \251\237",
    "\237\243 A:Play         \251\237",
    "\237\243 B:Highscore    \251\237",
    "\237\243 \136:Rooms  @ 1988\251\237",
    "\237\243          BERLIN\251\237",
    "\237\274\275\275\275\275\275\275\275\275\275\275\275\275\275\275\275\275\276\237",
    "\270\271\271\271\271\271\271\271\271\271\271\271\271\271\271\271\271\271\272\273",
  };
  
  for ( int ze = 0; ze < 16; ze++ )
    for ( int sp = 0; sp < 20; sp++ ) {
      charSet.setFrame( int(screen[ze][sp]) - 32 );
      gb.display.drawImage( sp*8, ze*8, charSet );
    }
}

void viewScore() {
  char cstr[2];
  
  gb.display.fill( INDEX_ORANGE );
  
  hs = gb.language.get( lang_highscore );
  strcpy(cstr, hs.c_str());
  for ( int sp = 0; sp < hs.length(); sp++ ) {
    charSet.setFrame( int(cstr[sp]) - 32 );
    gb.display.drawImage( 8+sp*8, TOPBAR_H, charSet );
  }
  
  hs = String( "\135\135\135\135\135\135\135\135\135\135\135" );
  strcpy(cstr, hs.c_str());
  for ( int sp = 0; sp < hs.length(); sp++ ) {
    charSet.setFrame( int(cstr[sp]) - 32 );
    gb.display.drawImage( 8+sp*8, TOPBAR_H+8, charSet );
  }
  
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
