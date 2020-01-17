byte diamond_step = 7;
byte digger_l_steps[6] = { 18, 19, 20, 19, 18, 17 };
byte digger_r_steps[6] = { 27, 28, 29, 28, 27, 26 };

void drawWorld() {
  byte crop_y = 0;
  
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
      if ( !(x_screen < -SPRITE_W-1 || x_screen > display_width-1 || y_screen < -TOPBAR_H || y_screen > display_height-1) ) {
      //partial refresh
      //if ( !(x_screen < -SPRITE_W-1 || x_screen > display_width-1 || y_screen < -TOPBAR_H || y_screen > display_height-1) && (world[x][y] & RENDERSTATE)==RENDERSTATE ) {
      //no refresh
      //if ( (world[x][y] & RENDERSTATE) == RENDERSTATE ) {
        spritesheet.setFrame(sprite);
        //crop menubar
        if (y_screen < TOPBAR_H)
          crop_y = TOPBAR_H - y_screen;
        else
          crop_y = 0;
        gb.display.drawImage( x_screen, y_screen + crop_y, spritesheet, 0, crop_y, SPRITE_W, SPRITE_H );
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

  // S T A T U S Z E I L E :_rr_ll*_cccc_dd*00_
  if ( gb.frameCount % 4 == 0 ) {
    // clear
    if (clr_flag) {
      clr_flag = false;
      gb.display.fill(zbg);
    }

    gb.display.setFont(font8x8);
    gb.display.setFontSize(1);
    gb.display.setTextWrap( false );
    gb.display.cursorY = TOPBAR_H/4;

    // raum
    if (zr_flag) {
      zr_flag = false;
      gb.display.cursorX = 0;
      gb.display.setColor(zfg, zbg);
      zr = String(curlevel + 1);
      while (zr.length() < 2)
        zr = String("0" + zr);
      gb.display.print(zr);
    }
  
    // leben
    if (zl_flag) {
      zl_flag = false;
      gb.display.cursorX = 20;
      gb.display.setColor(zfg, zbg);
      zl = String(lives);
      while (zl.length() < 2)
        zl = String("0" + zl);
      gb.display.print(zl);
      gb.display.cursorX = 34;
      gb.display.setColor(INDEX_RED, zbg); //KCF_ROT
      gb.display.print(F("\03"));          //HERZ
    }
  
    // countdown
    gb.display.cursorX = 46;
    gb.display.setColor(zfg, zbg);
    zc = String(countdown);
    while (zc.length() < 4)
      zc = String("0" + zc);
    if ( (gb.frameCount % 6 == 0) && (countdown < 1000) )
      countdown_toggle ? countdown_toggle = false : countdown_toggle = true; 
    countdown_toggle ? gb.display.print("    ") : gb.display.print(zc);
  
    // diamanten
    if (zd_flag) {
      zd_flag = false;
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
    }
  
    // score
    if (zs_flag) {
      zs_flag = false;
      gb.display.cursorX = 122;
      zs = String(score);
      while (zs.length() < 5)
        zs = String("0" + zs);
      gb.display.print(zs);
    }

  }

}
