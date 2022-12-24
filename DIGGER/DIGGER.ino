#include <Gamebuino-Meta.h>
#include "DIGGER.h"
#include "Sprites.h"
#include "Levels.h"
#include "Locale.h"
#include "Sounds.h"
#include "Font.h"

byte world[WORLD_W][WORLD_H];

// cursor
int cursor_x, cursor_y;
int camera_x, camera_y;
bool scroll_xp, scroll_xm, scroll_yp, scroll_ym = false;
int display_width = gb.display.width();
int display_height = gb.display.height();

int score = 0;
int scorehard;
int highscore[7];
char scorename[7][9 + 1];
int countdown = 5000;
byte diams_need, diamonds;
byte level = 0;
byte lives = 0;
bool dead = false;
byte gamestate = MENU;
int codepos = 0;
int worldpos = 0;
byte dir = DIGGER_I;
byte ldir = DIGGER_I;
byte digger_step = 0;
byte idle_step = 0;
bool countdown_step = false;
bool countdown_toggle = false;
byte idle_sprite = 0;
byte timer = 0;
unsigned long starttime = 0;

bool sfx_diamond = false;
bool sfx_rock = false;
bool sfx_step = false;
bool gfx_inverse = false;

bool digger_in_idle = true;
byte zufall_x = 0;
byte zufall_y = 0;
byte idle = 0;

//Statuszeile
bool clr_flag = true;
ColorIndex zbg = KCB_ROT;   //Statuszeile Hintergrund
String zs = String(score);  //Score
bool zs_flag = true;
String zc = String(countdown);  //Counter
String zd = String(diamonds);   //Diamanten ist/soll
bool zd_flag = true;
String zr = String(level + 1);  //Raum
bool zr_flag = true;
String zl = String(lives);  //Leben
bool zl_flag = true;

//16 colors index palettes
const Color PALETTE[] = {
  // custom color   idx systemColorName  KC-Color
  (Color)0x0000,  //0 INDEX_BLACK      KCF/B_SCHWARZ
  (Color)0x0836,  //1 INDEX_DARKBLUE   KCF_BLAU
  (Color)0xc8f7,  //2 INDEX_PURPLE     KCF_PURPUR
  (Color)0x6078,  //3 INDEX_GREEN      KCF_VIOLETT
  (Color)0xcc23,  //4 INDEX_BROWN      KCF_ORANGE
  (Color)0x235a,  //5 INDEX_DARKGRAY   KCF_BLAUGRUEN
  (Color)0x8f08,  //6 INDEX_GRAY       KCF_GELBGRUEN
  (Color)0xf79f,  //7 INDEX_WHITE      KCF_WEISS     #ffffff Text Farbe
  (Color)0xc863,  //8 INDEX_RED        KCF_ROT
  (Color)0x9000,  //9 INDEX_ORANGE     KCB_ROT       #920205 Hintergrund Farbe (im Menü tranzparent)
  (Color)0xe74b,  //a INDEX_YELLOW     KCF_GELB
  (Color)0x2e8a,  //b INDEX_LIGHTGREEN KCF_GRUEN
  (Color)0x7bf0,  //c INDEX_LIGHTBLUE  KCB_WEISS
  (Color)0x0011,  //d INDEX_BLUE       KCB_BLAU      #04028f
  (Color)0xc88f,  //e INDEX_MAGENTA    KCF_PURPURROT
  (Color)0x2f38   //f INDEX_BEIGE      KCF_TUERKIS
};
const Color PALETTE_HIGHSCORE[] = {
  // custom color   idx systemColorName  KC-ColorName
  (Color)0x0000,  //0 INDEX_BLACK      KCF/B_SCHWARZ
  (Color)0x0836,  //1 INDEX_DARKBLUE   KCF_BLAU
  (Color)0xc8f7,  //2 INDEX_PURPLE     KCF_PURPUR
  (Color)0x6078,  //3 INDEX_GREEN      KCF_VIOLETT
  (Color)0xcc23,  //4 INDEX_BROWN      KCF_ORANGE
  (Color)0x235a,  //5 INDEX_DARKGRAY   KCF_BLAUGRUEN
  (Color)0x8f08,  //6 INDEX_GRAY       KCF_GELBGRUEN
  (Color)0xe74b,  //7 INDEX_WHITE      KCF_GELB      #E7E95D Text Farbe
  (Color)0xc863,  //8 INDEX_RED        KCF_ROT
  (Color)0x044C,  //9 INDEX_ORANGE     KCB_TUERKIS   #028965 Hintergrund Farbe
  (Color)0xe74b,  //a INDEX_YELLOW     KCF_GELB
  (Color)0x2e8a,  //b INDEX_LIGHTGREEN KCF_GRUEN
  (Color)0x7bf0,  //c INDEX_LIGHTBLUE  KCB_WEISS
  (Color)0x0011,  //d INDEX_BLUE       KCB_BLAU
  (Color)0xc88f,  //e INDEX_MAGENTA    KCF_PURPURROT
  (Color)0x2f38   //f INDEX_BEIGE      KCF_TUERKIS
};

void setup() {
  gb.begin();
  gb.display.setPalette(PALETTE);
  gb.setFrameRate(36);
  Fill_TonBuffer(TON_LOW, TON_HIGH, TON_RATE);
  initScore();
}

void loop() {
  while (!gb.update())
    ;  //update the gb.display

  switch (gamestate) {
    case MENU:
      gb.lights.clear();
      //Menügrafik
      viewMenu();
      //Tasten abfragen

      //(A)Play
      if (gb.buttons.released(BUTTON_A)) {
        if (lives != 0) {  //resume
          initStatus();
          gamestate = RUNNING;
        } else {  //load last game stand
          oldGame();
          initWorld(level);
          initStatus();
          gamestate = RUNNING;
        }
      }

      //(B)Score
      if (gb.buttons.released(BUTTON_B)) {
        loadScore();
        gamestate = SCORE;
      }
      break;

      //Look at the Rooms
      //if (gb.buttons.pressed(BUTTON_MENU)) {
      //
      //}
      //break;

    case SCORE:
      if (gb.buttons.released(BUTTON_B))
        gamestate = MENU;
      viewScore();
      if (gb.frameCount % 10)
        gb.lights.drawImage(0, 0, ledsprite_highscore);
      break;

    case RUNNING:
      //pause the game if menu is pressed
      if (gb.buttons.released(BUTTON_B))
        gamestate = MENU;

      //GAME-LOOP
      updateCursor();   //Player  ( digger action )
      updatePhysics();  //Physics ( falling() rocks & diamonds, moveMonster() )
      drawWorld();      //Render  ( scrolling screen, draw tiles )

      if (lives < 1) {
        saveScore();
        gamestate = SCORE;
      }

      //for debugging: show some stats
      if (gb.frameCount % 10 == 0) {
        SerialUSB.printf("CPU load: %i %% \n", gb.getCpuLoad());
        //SerialUSB.printf( "RAM free: %i bytes \n", gb.getFreeRam() );
      }

      break;
    default:
      break;
  }
}

void oldGame() {
  loadGame();
  dead = false;
}

void initStatus() {
  zr_flag = true;
  zl_flag = true;
  zd_flag = true;
  zs_flag = true;
  clr_flag = true;
}

//decoder of compressed level data
void initWorld(byte _level) {
  gb.lights.clear();
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
  saveGame();
}

//helper for decompressor, returns number of bits of an compressed level starting at (bit-) position "codepos"
byte getBits(byte _level, byte bits) {
  //uses global var codepos for bitoffset
  const byte *pos = levels[_level] + codepos / 8;
  int w = pgm_read_byte(pos) * 256 + pgm_read_byte(pos + 1);
  w >>= (16 - (codepos % 8) - bits);  //shift bits to right
  w = (w & ((1 << bits) - 1));        //mask desired bits
  codepos += bits;
  return (byte)w;
}

// set Tile to worldmap. Note: codes in level data have slightly different meanings than in world map.
void setTile(byte sprite) {
  byte x = worldpos % WORLD_W;
  byte y = worldpos / WORLD_W;
  switch (sprite) {
    case MONSTER_RT: world[x][y] = MONSTER_R | TYPE_RT | RENDERSTATE; break;
    case MONSTER_LT: world[x][y] = MONSTER_L | TYPE_LT | RENDERSTATE; break;
    case MONSTER_D: world[x][y] = MONSTER_D | TYPE_UD | RENDERSTATE; break;
    case MONSTER_U: world[x][y] = MONSTER_U | TYPE_UD | RENDERSTATE; break;
    case MONSTER_L: world[x][y] = MONSTER_L | TYPE_LR | RENDERSTATE; break;
    case MONSTER_R: world[x][y] = MONSTER_R | TYPE_LR | RENDERSTATE; break;
    default: world[x][y] = sprite | RENDERSTATE; break;
  }
  if (sprite == PLAYER) {
    cursor_x = x;
    cursor_y = y;
  }
}

void nextLevel() {
  if (level < NUM_LEVELS)
    level++;
  initStatus();
  initWorld(level);
}

void viewMenu() {
  gb.display.setPalette(PALETTE);
  gb.display.setFontSize(1);
  gb.display.fill(INDEX_BLUE);       //KCB_BLAU
  gb.display.setColor(INDEX_WHITE);  //KCF_WEISS
  gb.display.setCursor(0, 0);

  const char *screen[] = {
    //Sonderzeichen oktal codiert
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

  for (int ze = 0; ze < 16; ze++)
    for (int sp = 0; sp < 20; sp++) {
      charSet.setFrame(int(screen[ze][sp]) - 32);
      charSet.setTransparentColor(KCB_ROT);  //Schrift-Transparenz aktivieren, Index 9 (KCB_ROT) ist gleich Transparenz
      gb.display.drawImage(sp * 8, ze * 8, charSet);
    }
}

void viewScore() {
  char cstr[11];
  String hs = String(score);

  gb.display.setPalette(PALETTE_HIGHSCORE);
  gb.display.fill(KCB_TUERKIS);

  //"HIGHSCORE :"
  hs = gb.language.get(lang_highscore);
  strcpy(cstr, hs.c_str());
  for (int sp = 0; sp < hs.length(); sp++) {
    charSet.setFrame(int(cstr[sp]) - 32);
    gb.display.drawImage(8 + sp * 8, TOPBAR_H, charSet);
  }

  //"___________"
  hs = String("\135\135\135\135\135\135\135\135\135\135\135");
  strcpy(cstr, hs.c_str());
  for (int sp = 0; sp < hs.length(); sp++) {
    charSet.setFrame(int(cstr[sp]) - 32);
    gb.display.drawImage(8 + sp * 8, TOPBAR_H + 8, charSet);
  }

  //list
  for (byte i = 0; i < 7; i++) {

    //score "x5char"
    hs = String(highscore[i]);
    while (hs.length() < 5)
      hs = String("0" + hs);
    strcpy(cstr, hs.c_str());
    for (int sp = 0; sp < 5; sp++) {
      charSet.setFrame(int(cstr[sp]) - 32);
      gb.display.drawImage(2 * 8 + sp * 8, 36 + (i * 12), charSet);
    }

    //name "x2space + x9char"
    hs = ("  " + String(scorename[i]));
    while (hs.length() < 11)
      hs = String(hs + " ");
    strcpy(cstr, hs.c_str());
    for (int sp = 0; sp < 11; sp++) {
      charSet.setFrame(int(cstr[sp]) - 32);
      gb.display.drawImage(7 * 8 + sp * 8, 36 + (i * 12), charSet);
    }
  }
}

void loadScore() {
  byte offset = 3;  //blocks 3-9 for highscore
  for (byte i = 0; i < 7; i++) {
    highscore[i] = gb.save.get(i + offset);
    gb.save.get(i + offset + 7, scorename[i], 9 + 1);
  }
}

void saveScore() {
  //prüfe Zeile 0-6
  for (byte j = 0; j < 7; j++) {
    //ist der Highscore größer als die aktuelle Zeile?
    if (score > highscore[j]) {

      //Zeilen unterhalb, nach unten kopieren
      for (byte z = 5; z >= j && z < 6; z--) {
        highscore[z + 1] = highscore[z];
        strcpy(scorename[z + 1], scorename[z]);
      }

      //Eingabe neuen scorename
      char defaultUser[12 + 1];
      gb.getDefaultName(defaultUser);  //hole 12stelligen Benutzernamen aus loader.bin
      for (byte i = 0; i < 9; i++) {   //einkürzen auf 9stellig
        scorename[j][i] = defaultUser[i];
      }
      gb.gui.keyboard(lang_name, scorename[j], 9);

      //Speicher neuen Highscore
      highscore[j] = score;
      score = 0;
      saveGame();
      byte offset = 3;  //blocks 3-9: score, 10-16: name
      for (byte i = 0; i < 7; i++) {
        gb.save.set(i + offset, highscore[i]);
        gb.save.set(i + offset + 7, scorename[i]);
      }
    }
  }
}

void initScore() {
  byte offset = 3;  //blocks 3-9 for highscore
  char initname[7][9 + 1] = {
    "---------",
    "Digger   ",
    "(c) 1988 ",
    "by A.Lang",
    "---------",
    "         ",
    "         ",
  };
  for (byte i = 0; i < 7; i++) {
    highscore[i] = gb.save.get(i + offset);
    gb.save.get(i + offset + 7, scorename[i], 9 + 1);
    if ((highscore[i] == 0) && (String(scorename[i]) == ""))
      gb.save.set(i + offset + 7, initname[i]);
  }
}

void loadGame() {
  level = gb.save.get(0);
  lives = gb.save.get(1);
  score = gb.save.get(2);

  if (lives == 0)
    lives = LIVES;

  SerialUSB.printf("LOADED level:%i lives:%i score:%i\n", level, lives, score);
}

void saveGame() {
  gb.save.set(0, level);
  gb.save.set(1, lives);
  gb.save.set(2, score);

  SerialUSB.printf("SAVED  level:%i lives:%i score:%i\n", level, lives, score);
}
