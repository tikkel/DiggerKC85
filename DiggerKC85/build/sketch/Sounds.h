/* digger sound effects
   forked from original "XDigger" sound.c
   found at http://zenway.ru/page/xdigger
   XDigger  Copyright (C) 1988-99 Alexander Lang
*/

#define TON_SCHRITT 0
#define TON_STEIN 1
#define TON_DIAMANT 2

#define KC_FREQ           58472     //XDigger, 58472 Hz Samplefrequenz
#define CPU_FREQ_KC85_2   1750000   //CPU-Takt KC85/2
#define CPU_FREQ_KC85_3   1750000   //CPU-Takt KC85/3
#define CPU_FREQ_KC85_4   1773447.5 //CPU-Takt KC85/4
#define KC_CTC_FREQ_VT16  109375    //CPU_FREQ_KC85_3 / 16  //VT16  -> 109375Hz
#define KC_CTC_FREQ_VT256 6836      //CPU_FREQ_KC85_3 / 256 //VT256 -> 6835,9375Hz

#define TON_LOW 0x00
#define TON_HIGH 0xff
#define TON_RATE 44100 //default 44100Hz, META Samplefreq.

int ton_laenge[3];
byte ton_buffer[3][TON_RATE * ((0x40 * 0x40 + 0x40) / 2) / KC_CTC_FREQ_VT16 <<0]; //Puffergröße vorberechnen mit längstem Ton, Diamant (Gaußsche Summenformel)
