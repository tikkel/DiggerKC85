const byte ledsprite_collectBuff[]={
   2,4,  //width, height
   8,0,  //8 frames animation
   1,    //frameloop on
   0x00, //transparent color
   1,    //indexed colors
   0xa0, 0x00, 0x00, 0x00, //0xa = YELLOW
   0x00, 0x00, 0xa0, 0x00,
   0x00, 0x0a, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xa0,
   0x00, 0xa0, 0x00, 0x00,
   0x0a, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x0a, 0x00,
   0x00, 0x00, 0x00, 0x0a,
};
Image ledsprite_collect(ledsprite_collectBuff);

const byte ledsprite_falledBuff[]={
   2,4,  //width, height
   8,0,  //8 frames animation
   1,    //frameloop on
   0x00, //transparent color
   1,    //indexed colors
   0x00, 0x00, 0x00, 0x03, //0x3 = LILAC
   0x30, 0x00, 0x00, 0x00,
   0x00, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x30, 0x00,
   0x00, 0x00, 0x00, 0x30,
   0x00, 0x00, 0x03, 0x00,
   0x00, 0x30, 0x00, 0x00,
   0x03, 0x00, 0x00, 0x00,
};
Image ledsprite_falled(ledsprite_falledBuff);

const byte ledsprite_collectedBuff[]={
   2,4,  //width, height
   20,0,  //8 frames animation
   1,    //frameloop on
   0xff, //no transparent color
   1,    //indexed colors
   0x00, 0x00, 0x00, 0x00, //0xa = RED
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x88,
   0x00, 0x00, 0x00, 0x88,
   0x00, 0x00, 0x00, 0x88,
   0x00, 0x00, 0x00, 0x88,
   0x00, 0x00, 0x88, 0x00,
   0x00, 0x00, 0x88, 0x00,
   0x00, 0x00, 0x88, 0x00,
   0x00, 0x00, 0x88, 0x00,
   0x00, 0x88, 0x00, 0x00,
   0x00, 0x88, 0x00, 0x00,
   0x00, 0x88, 0x00, 0x00,
   0x00, 0x88, 0x00, 0x00,
   0x88, 0x00, 0x00, 0x00,
   0x88, 0x00, 0x00, 0x00,
   0x88, 0x00, 0x00, 0x00,
   0x88, 0x00, 0x00, 0x00,
};
Image ledsprite_collected(ledsprite_collectedBuff);

const byte ledsprite_highscoreBuff[]={
   2,4,  //width, height
   8,0,  //8 frames animation
   1,    //frameloop on
   0xFF, //no transparent color
   1,    //indexed colors
   0xb0, 0x00, 0x00, 0x00, //0xb = LIGHTGREEN
   0x0b, 0x00, 0x00, 0x00,
   0x00, 0x0b, 0x00, 0x00,
   0x00, 0x00, 0x0b, 0x00,
   0x00, 0x00, 0x00, 0x0b,
   0x00, 0x00, 0x00, 0xb0,
   0x00, 0x00, 0xb0, 0x00,
   0x00, 0xb0, 0x00, 0x00,
};
Image ledsprite_highscore(ledsprite_highscoreBuff);

const byte sprites[]={
  SPRITE_W, SPRITE_H,
  NUM_SPRITES,0, //frames
  0,  //frameloop dis
  0xFF, //transparent color
  1, //indexed colors

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //00 empty

  0x00, 0x00, 0x77, 0x00, 0x77, 0x77, 0x77, 0x70,
  0x77, 0x70, 0x77, 0x70, 0x77, 0x77, 0x77, 0x00,
  0x77, 0x00, 0x77, 0x00, 0x07, 0x77, 0x77, 0x70,
  0x77, 0x70, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00,
  0x77, 0x00, 0x77, 0x07, 0x77, 0x70, 0x77, 0x70,
  0x77, 0x70, 0x77, 0x77, 0x77, 0x00, 0x77, 0x00,
  0x77, 0x00, 0x70, 0x70, 0x70, 0x70, 0x77, 0x70,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x00,
  0x77, 0x77, 0x77, 0x00, 0x77, 0x77, 0x77, 0x70,
  0x77, 0x77, 0x77, 0x70, 0x77, 0x77, 0x77, 0x00,
  0x07, 0x07, 0x77, 0x00, 0x70, 0x70, 0x70, 0x70,
  0x00, 0x00, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00,
  0x77, 0x70, 0x77, 0x00, 0x77, 0x77, 0x07, 0x77,
  0x77, 0x00, 0x77, 0x70, 0x77, 0x70, 0x07, 0x77,
  0x77, 0x70, 0x07, 0x00, 0x77, 0x77, 0x00, 0x70,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, //01 wall
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x33, 0x30, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x33, 0x33, 0x33, 0x30, 0x00, 0x00,
  0x00, 0x03, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00,
  0x00, 0x33, 0x33, 0x33, 0x33, 0x33, 0x30, 0x00,
  0x03, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x00,
  0x03, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x00,
  0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x30,
  0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x30, 0x30,
  0x33, 0x33, 0x33, 0x33, 0x33, 0x30, 0x33, 0x30,
  0x03, 0x33, 0x33, 0x33, 0x33, 0x33, 0x03, 0x00,
  0x03, 0x33, 0x33, 0x33, 0x33, 0x03, 0x33, 0x00,
  0x00, 0x33, 0x33, 0x03, 0x03, 0x30, 0x30, 0x00,
  0x00, 0x03, 0x03, 0x33, 0x30, 0x33, 0x00, 0x00,
  0x00, 0x00, 0x33, 0x30, 0x33, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x33, 0x30, 0x00, 0x00, 0x00, //02 rock  
  
  0xa9, 0x9a, 0x9a, 0xa9, 0xa9, 0xa9, 0xa9, 0xa9,
  0x9a, 0x9a, 0x9a, 0x9a, 0x9a, 0x9a, 0x9a, 0x9a,
  0xaa, 0xa9, 0x99, 0xa9, 0xa9, 0x99, 0x99, 0xa9,
  0x9a, 0xa9, 0xa9, 0xa9, 0xaa, 0xa9, 0x99, 0x9a,
  0x99, 0x99, 0xa9, 0xaa, 0x99, 0x9a, 0x9a, 0x99,
  0xa9, 0x9a, 0x9a, 0x9a, 0x9a, 0x9a, 0x9a, 0x99,
  0x9a, 0x9a, 0x9a, 0x9a, 0x9a, 0xa9, 0xaa, 0x99,
  0xa9, 0xa9, 0xa9, 0x99, 0x9a, 0xa9, 0x9a, 0x9a,
  0x9a, 0x9a, 0x99, 0x9a, 0x9a, 0x9a, 0x9a, 0x99,
  0x99, 0xa9, 0xaa, 0x9a, 0xa9, 0xa9, 0xa9, 0xa9,
  0x9a, 0xa9, 0xa9, 0x99, 0xa9, 0xaa, 0x9a, 0xa9,
  0xa9, 0xa9, 0x99, 0xaa, 0x9a, 0x9a, 0xaa, 0x9a,
  0xa9, 0xa9, 0xa9, 0xa9, 0xa9, 0x99, 0xaa, 0x99,
  0x99, 0xa9, 0x99, 0xa9, 0x99, 0xa9, 0xaa, 0x9a,
  0xa9, 0x9a, 0xa9, 0x9a, 0x9a, 0xaa, 0x99, 0xa9,
  0x99, 0x99, 0xaa, 0x9a, 0x9a, 0x9a, 0x99, 0xaa, //03 soil

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xaa, 0xa0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0a, 0xaa, 0xaa, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xa0, 0x00, 0x00, 0xa0, 0x00, 0x00,
  0x00, 0x04, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x40, 0x00,
  0x04, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa0,
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa0,
  0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
  0x00, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa0, 0x00,
  0x00, 0x04, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x40, 0x00, 0x00, 0x00, //04 diamond

  0x11, 0x1c, 0xc1, 0x11, 0x11, 0x1c, 0xc1, 0x11,
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
  0xc1, 0x11, 0x11, 0x1c, 0xc1, 0x11, 0x11, 0x1c,
  0x1c, 0x11, 0x11, 0xcc, 0x1c, 0x11, 0x11, 0xcc,
  0xcc, 0x11, 0x11, 0xcc, 0xcc, 0x11, 0x11, 0xcc,
  0xcc, 0x11, 0x11, 0xcc, 0xcc, 0x11, 0x11, 0xcc,
  0xc1, 0x11, 0x11, 0x1c, 0xc1, 0x11, 0x11, 0x1c,
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
  0x11, 0x1c, 0xc1, 0x11, 0x11, 0x1c, 0xc1, 0x11,
  0x11, 0xcc, 0x1c, 0x11, 0x11, 0xcc, 0x1c, 0x11,
  0x11, 0xcc, 0xcc, 0x11, 0x11, 0xcc, 0xcc, 0x11,
  0x11, 0xcc, 0xcc, 0x11, 0x11, 0xcc, 0xcc, 0x11,
  0x11, 0x1c, 0xc1, 0x11, 0x11, 0x1c, 0xc1, 0x11,
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
  0xc1, 0x11, 0x11, 0x1c, 0xc1, 0x11, 0x11, 0x1c,
  0x1c, 0x11, 0x11, 0xcc, 0x1c, 0x11, 0x11, 0xcc, //05 changer

  0xbd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdb,
  0xdb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbd,
  0xdb, 0xbd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdb, 0xbd,
  0xdb, 0xdb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbd, 0xbd,
  0xdb, 0xdb, 0xbd, 0xdd, 0xdd, 0xdb, 0xbd, 0xbd,
  0xdb, 0xdb, 0xdb, 0xbb, 0xbb, 0xbd, 0xbd, 0xbd,
  0xdb, 0xdb, 0xdb, 0xbd, 0xdb, 0xbd, 0xbd, 0xbd,
  0xdb, 0xdb, 0xdb, 0xdb, 0xbd, 0xbd, 0xbd, 0xbd,
  0xdb, 0xdb, 0xdb, 0xdb, 0xbd, 0xbd, 0xbd, 0xbd,
  0xdb, 0xdb, 0xdb, 0xbd, 0xdb, 0xbd, 0xbd, 0xbd,
  0xdb, 0xdb, 0xdb, 0xbb, 0xbb, 0xbd, 0xbd, 0xbd,
  0xdb, 0xdb, 0xbd, 0xdd, 0xdd, 0xdb, 0xbd, 0xbd,
  0xdb, 0xdb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbd, 0xbd,
  0xdb, 0xbd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdb, 0xbd,
  0xdb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbd,
  0xbd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdb, //06 door

  0x00, 0x88, 0x88, 0x80, 0x08, 0x88, 0x88, 0x00,
  0x00, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x08, 0x80, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x88, 0x88, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x08, 0x80, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x08, 0x80, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x06, 0x66, 0x66, 0x60, 0x00, 0x00,
  0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00,
  0x00, 0x60, 0x06, 0x66, 0x66, 0x60, 0x06, 0x00,
  0x06, 0x66, 0x06, 0x66, 0x66, 0x60, 0x66, 0x60,
  0x00, 0x00, 0x05, 0x55, 0x55, 0x50, 0x00, 0x00,
  0x00, 0x05, 0x55, 0x55, 0x55, 0x55, 0x50, 0x00,
  0x00, 0x05, 0x50, 0x00, 0x00, 0x05, 0x50, 0x00,
  0x05, 0x55, 0x50, 0x00, 0x00, 0x05, 0x55, 0x50, //07 monster_d, initial/preferred direction of monster-movement: down up lefturn rightturn
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00,
  0x00, 0x0e, 0xee, 0xee, 0x88, 0x08, 0x88, 0x00,
  0x0e, 0xee, 0xe0, 0x00, 0x88, 0x88, 0x88, 0x00,
  0x0e, 0xe0, 0x00, 0x00, 0x88, 0x00, 0x88, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x88, 0x88, 0x00,
  0x00, 0x00, 0x00, 0x06, 0x66, 0x66, 0x00, 0x00,
  0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x60,
  0x00, 0x00, 0x60, 0x06, 0x66, 0x66, 0x00, 0x60,
  0x00, 0x06, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66,
  0x00, 0x00, 0x00, 0x05, 0x55, 0x55, 0x00, 0x00,
  0x00, 0x00, 0x05, 0x55, 0x55, 0x55, 0x55, 0x00,
  0x00, 0x00, 0x05, 0x50, 0x00, 0x00, 0x55, 0x00,
  0x00, 0x05, 0x55, 0x50, 0x00, 0x00, 0x55, 0x55, //08 monster_l
  
  0x00, 0x88, 0x88, 0x80, 0x08, 0x88, 0x88, 0x00,
  0x00, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x88, 0x88, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00,
  0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00,
  0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x88, 0x88, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x06, 0x66, 0x66, 0x60, 0x00, 0x00,
  0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00,
  0x00, 0x60, 0x06, 0x66, 0x66, 0x60, 0x06, 0x00,
  0x06, 0x66, 0x06, 0x66, 0x66, 0x60, 0x66, 0x60,
  0x00, 0x00, 0x05, 0x55, 0x55, 0x50, 0x00, 0x00,
  0x00, 0x05, 0x55, 0x55, 0x55, 0x55, 0x50, 0x00,
  0x00, 0x05, 0x50, 0x00, 0x00, 0x05, 0x50, 0x00,
  0x05, 0x55, 0x50, 0x00, 0x00, 0x05, 0x55, 0x50, //09 monster_u
  
  0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x88, 0x80, 0x88, 0xee, 0xee, 0xe0, 0x00,
  0x00, 0x88, 0x88, 0x88, 0x00, 0x0e, 0xee, 0xe0,
  0x00, 0x88, 0x00, 0x88, 0x00, 0x00, 0x0e, 0xe0,
  0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x88, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x66, 0x66, 0x60, 0x00, 0x00, 0x00,
  0x06, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00,
  0x06, 0x00, 0x66, 0x66, 0x60, 0x06, 0x00, 0x00,
  0x66, 0x60, 0x66, 0x66, 0x60, 0x66, 0x60, 0x00,
  0x00, 0x00, 0x55, 0x55, 0x50, 0x00, 0x00, 0x00,
  0x00, 0x55, 0x55, 0x55, 0x55, 0x50, 0x00, 0x00,
  0x00, 0x55, 0x00, 0x00, 0x05, 0x50, 0x00, 0x00,
  0x55, 0x55, 0x00, 0x00, 0x05, 0x55, 0x50, 0x00, //10 monster_r
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x00, 0x00, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x20, 0x00, 0x00, 0x02, 0x20, 0x00,
  0x02, 0x22, 0x20, 0x00, 0x00, 0x02, 0x22, 0x20, //11 digger_d
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0x77, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x70, 0x77, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x70, 0x77, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x70, 0x77, 0x00, 0x00, 0x00,
  0x00, 0x07, 0x77, 0x77, 0x77, 0x77, 0x77, 0x00,
  0x00, 0x70, 0x77, 0x77, 0x77, 0x77, 0x77, 0x00,
  0x00, 0x77, 0x00, 0x07, 0x77, 0x00, 0x07, 0x00,
  0x00, 0x77, 0x77, 0x70, 0x77, 0x77, 0x70, 0x00,
  0x00, 0x00, 0x00, 0x70, 0x77, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x70, 0x77, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x77, 0x77, 0x77, 0x77, 0x70, 0x00,
  0x00, 0x07, 0x70, 0x70, 0x77, 0x07, 0x77, 0x00,
  0x00, 0x77, 0x07, 0x77, 0x77, 0x70, 0x77, 0x70,
  0x07, 0x07, 0x77, 0x07, 0x70, 0x77, 0x77, 0x77,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //12 death
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x04, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x40, 0x00,
  0x04, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x04, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x40, 0x00, 0x00, 0x00, //13 diamond1
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x0a, 0xaa, 0xaa, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xa0, 0x00, 0x00, 0xa0, 0x00, 0x00,
  0x00, 0x04, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x40, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
  0x00, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa0, 0x00,
  0x00, 0x04, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //14 diamond2
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xaa, 0xa0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0a, 0xaa, 0xaa, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xa0, 0x00, 0x00, 0xa0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa0,
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa0,
  0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
  0x00, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //15 diamond3

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xaa, 0xa0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x04, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa0,
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  0x00, 0x00, 0x04, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x40, 0x00, 0x00, 0x00, //16 diamond4
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, //17 digger_l dir=1  <- links
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00,
  0x00, 0x00, 0x22, 0x22, 0x00, 0x02, 0x00, 0x00, //18 digger_l dir=1  <- links2
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00,
  0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00,
  0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00,
  0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x00, //19 digger_l dir=1  <- links3
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
  0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, //20 digger_l dir=1  <- links4
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x00, 0x00, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x0f, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x20, 0x00, 0x00, 0x02, 0x22, 0x20,
  0x02, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, //21 digger_u dir=2  ^  hoch
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x00, 0x00, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xf0,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x02, 0x22, 0x20, 0x00, 0x00, 0x02, 0x20, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x20, //22 digger_u dir=2  ^  hoch2
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x00, 0x00, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x20, 0x00, 0x00, 0x02, 0x20, 0x00,
  0x02, 0x22, 0x20, 0x00, 0x00, 0x02, 0x22, 0x20, //23 digger_d dir=3     stay
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x00, 0x00, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x0f, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x20, 0x00, 0x00, 0x02, 0x22, 0x20,
  0x02, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, //24 digger_d dir=4  v  runter
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x00, 0x00, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xf0,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x02, 0x22, 0x20, 0x00, 0x00, 0x02, 0x20, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x20, //25 digger_d dir=4  v  runter2
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, //26 digger_r dir=5 -> rechts
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x22, 0x22, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x20, 0x00, 0x22, 0x22, 0x00, 0x00, //27 digger_r dir=5 -> rechts2
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00,
  0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
  0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
  0x00, 0x20, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, //28 digger_r dir=5 -> rechts3
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, //29 digger_r dir=5 -> rechts4
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x00, 0x00, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x20, 0x00, 0x00, 0x02, 0x20, 0x00,
  0x02, 0x22, 0x20, 0x00, 0x00, 0x02, 0x22, 0x20, //30 digger_blinzeln
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x00, 0x00, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x20, 0x00, 0x00, 0x02, 0x20, 0x00,
  0x02, 0x22, 0x20, 0x00, 0x00, 0x02, 0x22, 0x20, //31 digger_blinzeln2
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x00, 0x00, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x44, 0x00, 0x44, 0x44, 0x00, 0x44, 0x00,
  0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x20, 0x00,
  0x02, 0x22, 0x20, 0x00, 0x00, 0x02, 0x20, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x20 //32 digger_stampfen
};
Image spritesheet(sprites);
