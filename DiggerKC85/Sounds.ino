/* digger sound effects
   inspired by "XDigger" sound.c
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
