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
    case DIAMOND: movePlayer(xoff, yoff); diamonds++; sfx_diamond = true; score += 3; zs_flag = true; zd_flag = true; break;
    case CHANGER: break;
    case DOOR:
      if (diams_need <= diamonds) {
        movePlayer(xoff, yoff);
        sfx_diamond = true;
        score += 100;
        zs_flag = true;
        zd_flag = true;
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
  if (camera_y > camera_y_target + SPRITE_H * 2 - TOPBAR_H) { //scrolling ON
    scroll_ym = true;
    scroll_yp = false;
  }
  else if (camera_y == camera_y_target) //scrolling OFF, wenn zentriert
    scroll_ym = false;
  if (scroll_ym) {
    camera_y = camera_y - 2; //scrolle 2 pixel
    if (camera_y < -TOPBAR_H) { //12 ist gleich die Menüzeilenhöhe
      camera_y = -TOPBAR_H;
      scroll_ym = false;
    }
  }

}
