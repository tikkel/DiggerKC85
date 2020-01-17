# 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino"
# 2 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino" 2
# 3 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino" 2
# 4 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino" 2
# 5 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino" 2
# 6 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino" 2
# 7 "/home/makko/Arduino/DiggerKC85/DiggerKC85/DiggerKC85.ino" 2

byte world[20][14];

//generate Multilang-Array for pause menu
const MultiLang* Pausemenu_easy[6] = {
  lang_resume,
  lang_new,
  lang_levelup,
  lang_leveldown,
  lang_toggle_easy,
  lang_score
};
const MultiLang* Pausemenu_hard[6] = {
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
byte lives = 20;
byte liveseasy = 20;
byte liveshard = 20;
bool dead = false;
bool gamemode = false;
bool temp_gamemode;
byte gamestate = 1;
int codepos = 0;
int worldpos = 0;
byte dir = 3;
byte ldir = 3;
byte digger_step = 0;
byte idle_step = 0;
bool countdown_step = false;
bool countdown_toggle = false;
byte idle_sprite = 0;
byte timer = 0;
unsigned long starttime=0;

bool sfx_diamond = false;
bool sfx_rock = false;
bool sfx_step = false;
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
  (Color)0x2f38 //f INDEX_BEIGE      KCF_TUERKIS
};

void setup(){
  //SerialUSB.begin(9600);
  gb.begin();
  gb.display.setPalette(PALETTE);
  gb.setFrameRate(36);
  Fill_TonBuffer(0x00, 0xff, 44100 /*default 44100Hz, META Samplefreq.*/);

  SerialUSB.printf( "lives: %i\n", lives );
  gamemode = true;
    loadGame();
    saveGame();
  gamemode = false;
    loadGame();
    saveGame();
  SerialUSB.printf( "lives: %i\n", lives );

  initGame();
}

void loop() {
    while (!gb.update());

    switch (gamestate) {
      case 1:
        gb.lights.clear();
        switch ( gb.gui.menu(lang_title, gamemode ? Pausemenu_hard : Pausemenu_easy, 6) ) {
          case -1: //nothing selected
            break;
          case 0: //resume game
            if (lives != 0)
              gamestate = 0;
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
            gamestate = 0;
            break;
          case 3: //lvldown
            if (curlevel > 0)
              curlevel--;
            initWorld(curlevel);
            saveGame();
            dead = false;
            gamestate = 0;
            break;
          case 4: //gamemode
            gamemode = !gamemode;
            gb.save.set(0, gamemode);
            curlevel = (gamemode == false) ? cureasy : curhard;
            maxlevel = (gamemode == false) ? maxeasy : maxhard;
            lives = (gamemode == false) ? liveseasy : liveshard;
            score = (gamemode == false) ? scoreeasy : scorehard;
            dead = false;
            initWorld(curlevel);
            break;
          case 5: //highscore
            loadScore();
            gamestate = 3;
            break;
        };
        break;

      case 3:
        if (gb.buttons.released(BUTTON_A))
          gamestate = 1;
        if (lives <1 || lives>20) //update the highscore if 
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

      case 0:
        //pause the game if menu is pressed
        if (gb.buttons.pressed(BUTTON_MENU))
          gamestate = 1;
        updateCursor(); //Player  ( digger action )
        updatePhysics(); //Physics ( falling() rocks & diamonds, moveMonster() )
        drawWorld(); //Render  ( scrolling screen, draw tiles )
        if (lives <1 || lives>20) {
          loadScore();
          gamestate=3;
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
  lives = 20;
  maxeasy = 0;
  cureasy = 0;
  maxhard = 0;
  curhard = 0;
  gamestate = 0;
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
  while (worldpos < 14 * 20) {
    if (getBits(_level, 1)) {
      byte r = getBits(_level, 6);
      byte c = getBits(_level, 3) + 3;

      for (byte i = 0; i < c; i++) {
        if (worldpos < 20 * 14) {
          int refpos = worldpos - r;
          setTile(world[refpos % 20][refpos / 20]);
          worldpos++;
        }
      }
    } else {
      setTile(getBits(_level, 4));
      worldpos++;
    }
  }
}

//helper for decompressor, returns number of bits of an compressed level starting at (bit-) position "codepos" 
byte getBits(byte _level, byte bits) {
  //uses global var codepos for bitoffset
  const byte *pos = levels[_level] + codepos / 8;
  int w = (*(const unsigned char *)(pos)) * 256 + (*(const unsigned char *)(pos + 1));
  w >>= (16 - (codepos % 8) - bits); //shift bits to right
  w = ( w & ((1 << bits) - 1)); //mask desired bits
  codepos += bits;
  return (byte)w;
}

// set Tile to worldmap. Note: codes in level data have slightly different meanings than in world map.
void setTile( byte sprite) {
  byte x = worldpos % 20;
  byte y = worldpos / 20;
  switch (sprite) {
    case 12: world[x][y] = 10 | 128 | 32 /*0x20, 0010 0000  render-state*/; break;
    case 13: world[x][y] = 8 | 192 | 32 /*0x20, 0010 0000  render-state*/; break;
    case 7: world[x][y] = 7 | 0 | 32 /*0x20, 0010 0000  render-state*/; break;
    case 9: world[x][y] = 9 | 0 | 32 /*0x20, 0010 0000  render-state*/; break;
    case 8: world[x][y] = 8 | 64 | 32 /*0x20, 0010 0000  render-state*/; break;
    case 10: world[x][y] = 10 | 64 | 32 /*0x20, 0010 0000  render-state*/; break;
    default: world[x][y] = sprite | 32 /*0x20, 0010 0000  render-state*/; break;
  }
  if (sprite == 11) {
    cursor_x = x;
    cursor_y = y;
  }
}
void nextLevel() {
  if (curlevel < 152 -3) {
    (gamemode == false) ? cureasy++ : curhard++;
    maxeasy = ((maxeasy)>(cureasy)?(maxeasy):(cureasy));
    maxhard = ((maxhard)>(curhard)?(maxhard):(curhard));
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
      gb.getDefaultName( scorename[j] ); //funktioniert nicht richtig, überschreibt [j+1] mit "n"
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
  gamemode = gb.save.get(0);
  cureasy = gb.save.get(1);
  maxeasy = gb.save.get(2);
  curhard = gb.save.get(3);
  maxhard = gb.save.get(4);
  liveseasy = gb.save.get(5);
  liveshard = gb.save.get(6);
  scoreeasy = gb.save.get(7);
  scorehard = gb.save.get(8);
  maxeasy = ((maxeasy)>(cureasy)?(maxeasy):(cureasy));
  maxhard = ((maxhard)>(curhard)?(maxhard):(curhard));
  curlevel = (gamemode == false) ? cureasy : curhard;
  maxlevel = (gamemode == false) ? maxeasy : maxhard;
  lives = (gamemode == false) ? liveseasy : liveshard;
  score = (gamemode == false) ? scoreeasy : scorehard;
}

void saveGame() {
  (gamemode == false) ? cureasy=curlevel : curhard=curlevel;
  (gamemode == false) ? maxeasy=maxlevel : maxhard=maxlevel;
  (gamemode == false) ? liveseasy=lives : liveshard=lives;
  (gamemode == false) ? scoreeasy=score : scorehard=score;
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
# 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Monster.ino"
void monster_die(byte x, byte y) {
  if ( world[x - 1][y - 1] == 11
         || world[x - 1][y] == 11
         || world[x - 1][y + 1] == 11
         || world[x][y - 1] == 11
         || world[x][y + 1] == 11
         || world[x + 1][y - 1] == 11
         || world[x + 1][y] == 11
         || world[x + 1][y + 1] == 11
     ) die();
  if (gamemode == false) {
    world[x][y] = 4 | 32 /*0x20, 0010 0000  render-state*/;
    sIND(x - 1, y + 1, 4);
    sIND(x , y + 1, 4);
    sIND(x + 1, y + 1, 4);
    sIND(x - 1, y - 1, 4);
    sIND(x - 1, y , 4);
    sIND(x , y - 1, 4);
    sIND(x + 1, y - 1, 4);
    sIND(x + 1, y , 4);
    sfx_rock = true;
    gb.lights.fill(WHITE);
    gb.tft.invertDisplay( true );
    gfx_inverse = true;
  } else {
    world[x][y] = 0 | 32 /*0x20, 0010 0000  render-state*/;
    sIND(x - 1, y + 1, 0);
    sIND(x , y + 1, 0);
    sIND(x + 1, y + 1, 0);
    sIND(x - 1, y - 1, 0);
    sIND(x - 1, y , 0);
    sIND(x , y - 1, 0);
    sIND(x + 1, y - 1, 0);
    sIND(x + 1, y , 0);
    sfx_rock = true;
    gb.lights.fill(WHITE);
    gb.tft.invertDisplay( true );
    gfx_inverse = true;
  }

}

void moveMonster(byte x, byte y, byte sprite) {

  if ( (gb.frameCount % (gamemode ? 4 : 8) == 0) && ((world[x][y] & 32 /*0x20, 0010 0000  render-state*/) == 0) ) {

    //straight forward preferred, if not: search new direction
    if (sprite == 7) {
      switch (world[x][y + 1] & 15 /*0x0F, 0000 1111*/) {
        case 0: world[x][y + 1] = world[x][y] | 32 /*0x20, 0010 0000  render-state*/; world[x][y] = 0 | 32 /*0x20, 0010 0000  render-state*/; break;
        case 11: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }
    else if ((sprite == 9)) {
      switch (world[x][y - 1] & 15 /*0x0F, 0000 1111*/ ) {
        case 0: world[x][y - 1] = (world[x][y] | 32 /*0x20, 0010 0000  render-state*/); world[x][y] = 0 | 32 /*0x20, 0010 0000  render-state*/; break;
        case 11: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }
    else if ((sprite == 8)) {
      switch (world[x - 1][y] & 15 /*0x0F, 0000 1111*/ ) {
        case 0: world[x - 1][y] = (world[x][y] | 32 /*0x20, 0010 0000  render-state*/); world[x][y] = 0 | 32 /*0x20, 0010 0000  render-state*/; break;
        case 11: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }
    else if ((sprite == 10)) {
      switch (world[x + 1][y] & 15 /*0x0F, 0000 1111*/ ) {
        case 0: world[x + 1][y] = (world[x][y] | 32 /*0x20, 0010 0000  render-state*/); world[x][y] = 0 | 32 /*0x20, 0010 0000  render-state*/; break;
        case 11: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }

  }
}
void sIND(byte x, byte y, byte sprite) { //setIfNotWorldBorder
  if (x > 0 && x < 20 - 1 && y > 0 && y < 14 - 1) world[x][y] = sprite | 32 /*0x20, 0010 0000  render-state*/;
}

byte getNewDirection(byte x, byte y) {
  byte type = world[x][y] & 192 /*0xC0, 1100 0000*/;
  byte sprite = world[x][y] & 15 /*0x0F, 0000 1111*/;
  switch (type) {
    case 0:
      if (sprite == 7) {
        if ( (world[x][y - 1] & 15 /*0x0F, 0000 1111*/) == 0 )
          sprite = 9;
      }
      else {
        if ( (world[x][y + 1] & 15 /*0x0F, 0000 1111*/) == 0 )
          sprite = 7;
      }
      break;
    case 64:
      if (sprite == 10) {
        if ( (world[x - 1][y] & 15 /*0x0F, 0000 1111*/) == 0 )
          sprite = 8;
      }
      else {
        if ( (world[x + 1][y] & 15 /*0x0F, 0000 1111*/) == 0 )
          sprite = 10;
      }
      break;
    case 128:
      //rechts [ *>]
      sprite++; if (sprite > 10) sprite = 7;
        if (testMove(x, y, sprite))
          break;
      //links [<*<]
      sprite--; sprite--; if (sprite < 7) sprite = 10;
        if (testMove(x, y, sprite))
          break;
      //umkehr [>* ]
      sprite--; if (sprite < 7) sprite = 10;
        if (testMove(x, y, sprite))
          break;
    case 192:
      //rechts [<* ]
      sprite--; if (sprite < 7) sprite = 10;
        if (testMove(x, y, sprite))
          break;
      //links [>*>]
      sprite++; sprite++; if (sprite > 10) sprite = 7;
        if (testMove(x, y, sprite))
          break;
      //umkehr [>* ]
      sprite++; if (sprite > 10) sprite = 7;
        if (testMove(x, y, sprite))
          break;
  }
  return sprite + type;
}

bool testMove(byte x, byte y, byte monster) {
  switch (monster) {
    case 9:
      if (world[x][y - 1] == 11) die();
      return (world[x][y - 1] == 0) ? true : false; break;
    case 8:
      if (world[x - 1][y] == 11) die();
      return (world[x - 1][y] == 0) ? true : false; break;
    case 7:
      if (world[x][y + 1] == 11) die();
      return (world[x][y + 1] == 0) ? true : false; break;
    case 10:
      if (world[x + 1][y] == 11) die();
      return (world[x + 1][y] == 0) ? true : false; break;
    default:
      return true; break;
  }
}
# 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Physics.ino"
void updatePhysics() {
  //Skip borders in Check (x,y=1)
  if (gb.frameCount % (gamemode ? 4 : 5) == 0) {
    for (byte y = 1; y < 14 - 1; y++) {
      for (byte x = 1; x < 20 - 1; x++) {
        //byte sprite = world[x][y] & ~PHYSICSTATE & ~TYPEMASK;
        byte sprite = world[x][y] & ~240 /*0xF0, 1111 0000*/;
        switch (sprite) {
          case 2: falling(x, y, 2); break; //rock
          case 4: falling(x, y, 4); break; //diam
          case 7: moveMonster(x, y, 7); break; //mon_down
          case 9: moveMonster(x, y, 9); break; //mon_up
          case 8: moveMonster(x, y, 8); break;
          case 10: moveMonster(x, y, 10); break;
          default: break;
        }
      }
    }
    for (byte y = 1; y < 14 - 1; y++) {
      for (byte x = 1; x < 20 - 1; x++) {
        world[x][y] &= ~16 /*0x10, 0001 0000  physic-state*/;
      }
    }
  }
}

void falling(byte x, byte y, byte sprite) {
  if ( (world[x][y] & 16 /*0x10, 0001 0000  physic-state*/) > 0 ) {
    switch (world[x][y + 1] & 15 /*0x0F, 0000 1111*/) {
      case 11: die(); sfx_rock = true; break;
      case 7: monster_die(x, y + 1);return; break;
      case 9: monster_die(x, y + 1);return; break;
      case 8: monster_die(x, y + 1);return; break;
      case 10: monster_die(x, y + 1);return; break;
      case 0: break;
      default: sfx_rock = true; break;
    }
  }
  else {
      //gerade runterfallen
      if (world[x][y + 1] == 0) {
        world[x][y + 1] = sprite | 16 /*0x10, 0001 0000  physic-state*/| 32 /*0x20, 0010 0000  render-state*/;
        world[x][y] = 0 | 32 /*0x20, 0010 0000  render-state*/;
        return;
      }
      if (world[x][y + 1] == 2 || world[x][y + 1] == 4) {
        //rechts runterfallen
        if (world[x + 1][y + 1] == 0 && world[x + 1][y] == 0) {
          world[x + 1][y + 1] = sprite | 16 /*0x10, 0001 0000  physic-state*/ | 32 /*0x20, 0010 0000  render-state*/;
          world[x][y] = 0 | 32 /*0x20, 0010 0000  render-state*/;
        //links runterfallen
        } else if (world[x - 1][y + 1] == 0 && world[x - 1][y] == 0) {
          world[x - 1][y + 1] = sprite | 16 /*0x10, 0001 0000  physic-state*/ | 32 /*0x20, 0010 0000  render-state*/;
          world[x][y] = 0 | 32 /*0x20, 0010 0000  render-state*/;
        }
        return;
      }
      if ((sprite == 2) && (world[x][y + 1] == 5) && (world[x][y + 2] == 0)) {
        world[x][y] = 0 | 32 /*0x20, 0010 0000  render-state*/;
        world[x][y + 2] = 4 | 16 /*0x10, 0001 0000  physic-state*/ | 32 /*0x20, 0010 0000  render-state*/;
      }
  }
}

void moveRock(char xoff, char yoff) {
  if (yoff != 0) {
    return;
  }
  if (gb.buttons.repeat(BUTTON_RIGHT, 8) && world[cursor_x + 2][cursor_y] == 0 ) {
    world[cursor_x + 2][cursor_y] = 2 | 32 /*0x20, 0010 0000  render-state*/;
    movePlayer(1, 0);
    sfx_step = true;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 8) && world[cursor_x - 2][cursor_y] == 0 ) {
    world[cursor_x - 2][cursor_y] = 2 | 32 /*0x20, 0010 0000  render-state*/;
    movePlayer(-1, 0);
    sfx_step = true;
  }
}
# 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Player.ino"
void movePlayer(int8_t xoff, int8_t yoff) {
  world[cursor_x][cursor_y] = 0 | 16 /*0x10, 0001 0000  physic-state*/ | 32 /*0x20, 0010 0000  render-state*/;
  cursor_x = cursor_x + xoff;
  cursor_y = cursor_y + yoff;
  world[cursor_x][cursor_y] = 11;
}

void handlePlayer(int8_t xoff, int8_t yoff) {
  ldir = dir;
  //dir = 8 + xoff * 2 + yoff;
  dir = 3 + xoff * 2 + yoff;
  if (dir != ldir) digger_step = 0;
  timer = 4;
  byte target = world[cursor_x + xoff][cursor_y + yoff];
  target &= ~16 /*0x10, 0001 0000  physic-state*/;
  switch ( target ) {
    case 0: movePlayer(xoff, yoff); sfx_step = true; break;
    case 1: break;
    case 2: moveRock(xoff, yoff); break;
    case 3: movePlayer(xoff, yoff); sfx_step = true; break;
    case 4: movePlayer(xoff, yoff); diamonds++; sfx_diamond = true; score += 3; break;
    case 5: break;
    case 6:
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
  world[x][y] = 12 | 32 /*0x20, 0010 0000  render-state*/;
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
  int camera_x_target = cursor_x * 16 - display_width / 2 + 16 / 2;
  int camera_y_target = cursor_y * 16 - display_height / 2 + 16 / 2;

  // nach rechts scrollen
  if (camera_x < camera_x_target - 16 * 2) { //scrolling ON
    scroll_xp = true;
    scroll_xm = false;
  }
  else if (camera_x == camera_x_target) //scrollOff, wenn zentriert
    scroll_xp = false;
  if (scroll_xp) {
    camera_x = camera_x + 2; //scrolle 2 pixel
    if (camera_x > 20 * 16 - display_width) {
      camera_x = 20 * 16 - display_width;
      scroll_xp = false;
    }
  }
  // nach links scrollen
  if (camera_x > camera_x_target + 16 * 2) { //scrolling ON
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
  if (camera_y < camera_y_target - 16 * 2) { //scrolling ON
    scroll_yp = true;
    scroll_ym = false;
  }
  else if (camera_y == camera_y_target) //scrolling OFF, wenn zentriert
    scroll_yp = false;
  if (scroll_yp) {
    camera_y = camera_y + 2; //scrolle 2 pixel
    if (camera_y > 14 * 16 - display_height) {
      camera_y = 14 * 16 - display_height;
      scroll_yp = false;
    }
  }
  // nach oben scrollen
  if (camera_y > camera_y_target + 16 * 2) { //scrolling ON
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
# 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Render.ino"
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

  for (byte y = 0; y < 14; y++) {
    int y_screen = y * 16 - camera_y; //coordinates on the screen depending on the camera position

    for (byte x = 0; x < 20; x++) {
      int x_screen = x * 16 - camera_x; //coordinates on the screen depending on the camera position

      byte sprite = world[x][y];
      sprite &= 15 /*0x0F, 0000 1111*/;

      idle = world[zufall_x][zufall_y];

      //diamond-animation
      if (sprite == 4) {
        sprite = 13 + diamond_step/2;
        world[x][y] = 4 | 32 /*0x20, 0010 0000  render-state*/;}

      //digger-animation
      if (sprite == 11) {
        world[x][y] = 11 | 32 /*0x20, 0010 0000  render-state*/;
        switch (dir) {
          case 1:
            digger_in_idle = false;
            sprite = digger_l_steps[digger_step/2]; //18,19,20,19,18,17, jedes Sprite wird x2 ausgelesen
            digger_step++;
            if (digger_step > 11) //12 Animationsschritte, 0-11
              digger_step = 0;
            //SerialUSB.printf( "sprite_l: %i\n", sprite );
            break;
          case 2:
            digger_in_idle = false;
            sprite = 21 + digger_step/4; //21,22, jedes Sprite wird x4 ausgelesen
            digger_step++;
            if (digger_step > 7) //8 Animationsschritte, 0-7
              digger_step = 0;
            //SerialUSB.printf( "sprite_u: %i\n", sprite );
            break;
          case 3:
            zufall_x++;
            if ( zufall_x > 20 ) {
              zufall_x = 0;
              zufall_y++;
              if ( zufall_y > 14 ) {
                zufall_y = 0;
                zufall_x = 0;
              }
            }
            if ( (!digger_in_idle) && (idle == 2) ) {
              //ROCK --> blinzeln
              digger_in_idle = true;
              idle_sprite = 30;
            }
            else if ( (!digger_in_idle) && (idle == 4) ) {
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
          case 4:
            digger_in_idle = false;
            sprite = 24 + digger_step/4; //24,25, jedes Sprite wird x4 ausgelesen
            digger_step++;
            if (digger_step > 7) //8 Animationsschritte, 0-7
              digger_step = 0;
            //SerialUSB.printf( "sprite_d: %i\n", sprite );
            break;
          case 5:
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
      if ( !(x_screen < -16 -1 || x_screen > display_width-1 || y_screen < 1 || y_screen > display_height-1) ) {
      //partial refresh
      //if ( !(x_screen < -SPRITE_W-1 || x_screen > display_width-1 || y_screen < 1 || y_screen > display_height-1) && (world[x][y] & RENDERSTATE)==RENDERSTATE ) {
      //no refresh
      //if ( (world[x][y] & RENDERSTATE) == RENDERSTATE ) {
        spritesheet.setFrame(sprite);
        gb.display.drawImage(x_screen, y_screen, spritesheet);
      }

      world[x][y] &= ~32 /*0x20, 0010 0000  render-state*/;

    }
  }

  // LED_FX and sound_FX
  if (gb.frameCount % 4 == 0) {
    if (sfx_diamond) {
      gb.sound.play( ton_buffer[2], ton_laenge[2] );
      gb.lights.drawImage(0, 0, ledsprite_collect);
    }
    else if ( sfx_rock ) {
      gb.sound.play( ton_buffer[1], ton_laenge[1] );
      gb.lights.drawImage(0, 0, ledsprite_falled);
    }
    else if ( sfx_step )
      gb.sound.play( ton_buffer[0], ton_laenge[0] );
    else if ( dead )
      gb.lights.drawImage(0, 0, ledsprite_highscore);
    sfx_diamond = false;
    sfx_rock = false;
    sfx_step = false;
  }

  // nach losgelassener Richtungstaste, wieder auf wartend (idle) zurückstellen (timer default: nach 2 frames)
  if (timer == 0)
    dir = 3;
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
  gb.display.print((reinterpret_cast<const __FlashStringHelper *>(("\03 ")))); //HERZ

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
  gb.display.print((reinterpret_cast<const __FlashStringHelper *>(("\04")))); //DIAMANT
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
# 1 "/home/makko/Arduino/DiggerKC85/DiggerKC85/Sounds.ino"
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
      for (n=0; n <= ( rate / 6836 /*CPU_FREQ_KC85_3 / 256 //VT256 -> 6835,9375Hz*/ <<0 ); n++)
        ton_buffer[0][ ( rate * i / 6836 /*CPU_FREQ_KC85_3 / 256 //VT256 -> 6835,9375Hz*/ <<0 ) + n ] = augenblicklicherpeak;
      i++;
    }
    augenblicklicherpeak = ton_low + ton_high - augenblicklicherpeak;
  }
  ton_laenge[0] = (rate * (i-1) / 6836 /*CPU_FREQ_KC85_3 / 256 //VT256 -> 6835,9375Hz*/ <<0) + n-1;
  //SerialUSB.printf( "ton_laenge_schritt: %i bytes\n", ton_laenge[TON_SCHRITT]);

  // TON_STEIN
  augenblicklicherpeak=ton_low;
  for (i=0,j=0x0ff; ; j++) {
    if (j > 256) j = 1;
    if (j == 0x12) break; //j^TC-Reihe: 255,256,1...18 (^0x14 loops)
    for(k=0;k<j;k++){
      for (n = 0; n <= ( rate / 109375 /*CPU_FREQ_KC85_3 / 16  //VT16  -> 109375Hz*/ <<0 ); n++)
        ton_buffer[1][ ( rate * i / 109375 /*CPU_FREQ_KC85_3 / 16  //VT16  -> 109375Hz*/ <<0 ) + n ] = augenblicklicherpeak;
      i++;
    }
    augenblicklicherpeak = ton_low + ton_high - augenblicklicherpeak;
  }
  ton_laenge[1] = (rate * (i-1) / 109375 /*CPU_FREQ_KC85_3 / 16  //VT16  -> 109375Hz*/ <<0) + n-1;
  //SerialUSB.printf( "ton_laenge_stein: %i bytes\n", ton_laenge[TON_STEIN]);

  // TON_DIAMANT
  augenblicklicherpeak=ton_low;
  for (i=0,j=0x40; j>0; j--) {
    for(k=0;k<j;k++) {
      for (n = 0; n <= ( rate / 109375 /*CPU_FREQ_KC85_3 / 16  //VT16  -> 109375Hz*/ <<0 ); n++)
        ton_buffer[2][ ( rate * i / 109375 /*CPU_FREQ_KC85_3 / 16  //VT16  -> 109375Hz*/ <<0 ) + n ] = augenblicklicherpeak;
      i++;
    }
    augenblicklicherpeak = ton_low + ton_high - augenblicklicherpeak;
  }
  ton_laenge[2] = (rate * (i-1) / 109375 /*CPU_FREQ_KC85_3 / 16  //VT16  -> 109375Hz*/ <<0) + n-1;
  //SerialUSB.printf( "ton_laenge_diamant: %i bytes\n", ton_laenge[TON_DIAMANT]);

}
