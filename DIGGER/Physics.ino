void updatePhysics() {
  //Skip borders in Check (x,y=1)
  if (gb.frameCount % 4 == 0) {
    for (byte y = 1; y < WORLD_H - 1; y++) {
      for (byte x = 1; x < WORLD_W - 1; x++) {
        //byte sprite = world[x][y] & ~PHYSICSTATE & ~TYPEMASK;
        byte sprite = world[x][y] & ~STATEMASK;
        switch (sprite) {
          case ROCK: falling(x, y, ROCK); break;               //rock
          case DIAMOND: falling(x, y, DIAMOND); break;         //diam
          case MONSTER_D: moveMonster(x, y, MONSTER_D); break; //mon_down
          case MONSTER_U: moveMonster(x, y, MONSTER_U); break; //mon_up
          case MONSTER_L: moveMonster(x, y, MONSTER_L); break;
          case MONSTER_R: moveMonster(x, y, MONSTER_R); break;
          default: break;
        }
      }
    }
    for (byte y = 1; y < WORLD_H - 1; y++) {
      for (byte x = 1; x < WORLD_W - 1; x++) {
        world[x][y] &= ~PHYSICSTATE;
      }
    }
  }
}

void falling(byte x, byte y, byte sprite) {
  if ( (world[x][y] & PHYSICSTATE) > 0 ) {
    switch (world[x][y + 1] & SPRITEMASK) {
      case PLAYER: die(); sfx_rock = true; break;
      case MONSTER_D: monster_die(x, y + 1);return; break;
      case MONSTER_U: monster_die(x, y + 1);return; break;
      case MONSTER_L: monster_die(x, y + 1);return; break;
      case MONSTER_R: monster_die(x, y + 1);return; break;
      case EMPTY: break;
      default: sfx_rock = true; break;
    }
  }
  else {
      //gerade runterfallen
      if (world[x][y + 1] == EMPTY) {
        world[x][y + 1] = sprite | PHYSICSTATE| RENDERSTATE;
        world[x][y] = EMPTY | RENDERSTATE;
        return;
      }
      if (world[x][y + 1] == ROCK || world[x][y + 1] == DIAMOND) {
        //rechts runterfallen
        if (world[x + 1][y + 1] == EMPTY && world[x + 1][y] == EMPTY) {
          world[x + 1][y + 1] = sprite | PHYSICSTATE | RENDERSTATE;
          world[x][y] = EMPTY | RENDERSTATE;
        //links runterfallen
        } else if (world[x - 1][y + 1] == EMPTY && world[x - 1][y] == EMPTY) {
          world[x - 1][y + 1] = sprite | PHYSICSTATE | RENDERSTATE;
          world[x][y] = EMPTY | RENDERSTATE;
        }
        return;
      }
      if ((sprite == ROCK) && (world[x][y + 1] == CHANGER) && (world[x][y + 2] == EMPTY)) {
        world[x][y] = EMPTY | RENDERSTATE;
        world[x][y + 2] = DIAMOND | PHYSICSTATE | RENDERSTATE;
      }
  }
}

void moveRock(char xoff, char yoff) {
  if (yoff != 0) {
    return;
  }
  if (gb.buttons.repeat(BUTTON_RIGHT, 8) && world[cursor_x + 2][cursor_y] == EMPTY ) {
    world[cursor_x + 2][cursor_y] = ROCK | RENDERSTATE;
    movePlayer(1, 0);
    sfx_step = true;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 8) && world[cursor_x - 2][cursor_y] == EMPTY ) {
    world[cursor_x - 2][cursor_y] = ROCK | RENDERSTATE;
    movePlayer(-1, 0);
    sfx_step = true;
  }
}
