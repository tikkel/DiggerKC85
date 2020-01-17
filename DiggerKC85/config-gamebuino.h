//Specifications: https://gamebuino.com/creations/config-gamebuino-h
//
//    The memory:
//    A micro SD card is included and loaded with plenty of games, ready to play.
//    You can add more games than there will ever be!
//
//    Battery:
//    The 900mAh LiPo battery will keep your Gamebuino running for 16 hours.
//    You can charge it with the provided micro USB cable, just like your phone.
//
//    Light effects:
//    8 RGB LEDS on the back of the Gamebuino will make the game go beyond
//    the screen by illuminating your hands. Intensity can be adjusted and
//    disabled through the Home menu.
//    The lights are just a tiny image - one with 2x4 pixels.
//      0 <-left- -right-> 1
//    0 x                  x
//    1 x                  x
//    2 x                  x
//    3 x                 RED
//    That means, to turn the LED in the bottom-right red you can do:
//    gb.lights.drawPixel(1, 3, RED);
//
//    Sound:
//    The powerful speaker is powered by a class D audio amp, with a 10bit DAC.
//    If you don't want to bother people, you can use the 3.5mm audio jack.
//    Volume can be adjusted and disabled through the Home menu.
//    #define SOUND_CHANNELS (int) - number of sound sources that can be played at the same time, defaults to 4
//    #define SOUND_FREQ (int) - frequency at which the interrupt runs, default is 44100
#define SOUND_FREQ 44100
//
//    The screen:
//    It's a back-lit LCD display with vibrant colors and high contrasts.
//    With a diagonal of 1.8" it's large enough for simple games, and small enough
//    for your pocket. Default resolution is 80*64px, ideal of pixel art.
//    It can go up to 160*128px.
//
//    The brain:
//    The microcontroller is an ATSAMD21.
//    - 32bit ARM Cortex M0+
//    - 256KB flash
//    - 32KB RAM
//    Same as the Arduino Zero, faster than the Arduino Uno.
//    Some manage to run 3D games on that!

//enable one of the display modes
//if no config-gamebuino.h is present, it defaults to RGB

//#define DISPLAY_MODE DISPLAY_MODE_RGB565        //160*128px*rgb565
#define DISPLAY_MODE DISPLAY_MODE_INDEX         //160*128px*indexed16
//#define DISPLAY_MODE DISPLAY_MODE_INDEX_HALFRES //80*64px*indexed16

//Anzahl der Sprachen im Menu (en, de, fr)
#define LANGUAGE_DEFAULT_SIZE 3 
