#include <Gamebuino-Meta.h>

// define a checkerbox bitmap
const uint8_t bitmap[] = {
  8, 8,
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010,
};

uint8_t dir = 1;
uint8_t tmp [80*2];
uint8_t c = 0;
uint16_t* dst;
uint16_t* src;

void setup() {
  gb.begin();
  gb.setFrameRate(60);
  dst = gb.display._buffer;
  src = dst;
  gb.display.clear();
  // draw the checkered bitmap in yellow
  gb.display.setColor(YELLOW);
  gb.display.drawBitmap(0, 0, bitmap, 8);
  gb.display.drawBitmap(64, 0, bitmap, 8);
}

void loop() {
  while(!gb.update());

  if (gb.buttons.pressed(BUTTON_UP)) dir = 1;
  else if (gb.buttons.pressed(BUTTON_DOWN)) dir = 2;
  else if (gb.buttons.pressed(BUTTON_LEFT)) dir = 3;
  else if (gb.buttons.pressed(BUTTON_RIGHT)) dir = 4;

  // 80*2 bei lowres-RGB-mode
  // 80/2 bei lowres-IDX-mode
  
  switch(dir) {
    case 1:
      memcpy(tmp, src+80*0, 80*2); //save top line
      memcpy(dst+80*0, src+80*1, 80*2*63); //up
      memcpy(dst+80*63, tmp, 80*2); //restore bottom line
      break;
    case 2:
      memcpy(tmp, src+80*63, 80*2); //save bottom line
      memmove(dst+80*1, src+80*0, 80*2*63); //down
      memcpy(dst+80*0, tmp, 80*2); //restore top line
      break;
    case 3:
      for (c = 0; c < 64; c++) { memcpy(tmp+c*2, src+80*c, 1*2); } //save left column
      memcpy(dst+0, src+1, 80*2*64); //left
      for (c = 0; c < 64; c++) { memcpy(src+80*(c+1)-1, tmp+2*c, 1*2); } //restore right column
      break;
    case 4:
      for (c = 0; c < 64; c++) { memcpy(tmp+2*c, src+80*(c+1)-1, 1*2); } //save right column
      memmove(dst+1, src+0, 80*2*64); //left
      for (c = 0; c < 64; c++) { memcpy(src+80*c, tmp+c*2, 1*2); } //restore left column
      break;
  }

}
