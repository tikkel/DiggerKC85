void monster_die(byte x, byte y) {
  if (   world[x - 1][y - 1] == PLAYER
         || world[x - 1][y] == PLAYER
         || world[x - 1][y + 1] == PLAYER
         || world[x][y - 1] == PLAYER
         || world[x][y + 1] == PLAYER
         || world[x + 1][y - 1] == PLAYER
         || world[x + 1][y] == PLAYER
         || world[x + 1][y + 1] == PLAYER
     ) die();
  if (gamemode == EASY) {
    world[x][y] = DIAMOND | RENDERSTATE;
    sIND(x - 1, y + 1, DIAMOND);
    sIND(x  , y + 1, DIAMOND);
    sIND(x + 1, y + 1, DIAMOND);
    sIND(x - 1, y - 1, DIAMOND);
    sIND(x - 1, y  , DIAMOND);
    sIND(x  , y - 1, DIAMOND);
    sIND(x + 1, y - 1, DIAMOND);
    sIND(x + 1, y  , DIAMOND);
    sfx_rock = true;
    gb.lights.fill(INDEX_WHITE);
    gb.tft.invertDisplay( true );
    gfx_inverse = true;
  } else {
    world[x][y] = EMPTY | RENDERSTATE;
    sIND(x - 1, y + 1, EMPTY);
    sIND(x  , y + 1, EMPTY);
    sIND(x + 1, y + 1, EMPTY);
    sIND(x - 1, y - 1, EMPTY);
    sIND(x - 1, y  , EMPTY);
    sIND(x  , y - 1, EMPTY);
    sIND(x + 1, y - 1, EMPTY);
    sIND(x + 1, y  , EMPTY);
    sfx_rock = true;
    gb.lights.fill(INDEX_WHITE);
    gb.tft.invertDisplay( true );
    gfx_inverse = true;
  }

}

void moveMonster(byte x, byte y, byte sprite) {

  if ( (gb.frameCount % (gamemode ? 4 : 8) == 0) && ((world[x][y] & RENDERSTATE) == 0) ) {
    
    //straight forward preferred, if not: search new direction
    if (sprite == MONSTER_D) {
      switch (world[x][y + 1] & SPRITEMASK) {
        case EMPTY: world[x][y + 1] = world[x][y] | RENDERSTATE; world[x][y] = EMPTY | RENDERSTATE; break;
        case PLAYER: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }
    else if ((sprite == MONSTER_U)) {
      switch (world[x][y - 1] & SPRITEMASK ) {
        case EMPTY: world[x][y - 1] = (world[x][y] | RENDERSTATE); world[x][y] = EMPTY | RENDERSTATE; break;
        case PLAYER: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }
    else if ((sprite == MONSTER_L)) {
      switch (world[x - 1][y] & SPRITEMASK ) {
        case EMPTY: world[x - 1][y] = (world[x][y] | RENDERSTATE); world[x][y] = EMPTY | RENDERSTATE; break;
        case PLAYER: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }
    else if ((sprite == MONSTER_R)) {
      switch (world[x + 1][y] & SPRITEMASK ) {
        case EMPTY: world[x + 1][y] = (world[x][y] | RENDERSTATE); world[x][y] = EMPTY | RENDERSTATE; break;
        case PLAYER: die(); break;
        default: world[x][y] = getNewDirection(x, y); break;
      }
    }

  }
}
void sIND(byte x, byte y, byte sprite) { //setIfNotWorldBorder
  if (x > 0 && x < WORLD_W - 1 && y > 0 && y < WORLD_H - 1)   world[x][y] = sprite | RENDERSTATE;
}

byte getNewDirection(byte x, byte y) {
  byte type = world[x][y] & TYPEMASK;
  byte sprite = world[x][y] & SPRITEMASK;
  switch (type) {
    case TYPE_UD:
      if (sprite == MONSTER_D) {
        if ( (world[x][y - 1] & SPRITEMASK) == EMPTY )
          sprite = MONSTER_U;
      }
      else {
        if ( (world[x][y + 1] & SPRITEMASK) == EMPTY )
          sprite = MONSTER_D;
      }
      break;
    case TYPE_LR:
      if (sprite == MONSTER_R) {
        if ( (world[x - 1][y] & SPRITEMASK) == EMPTY )
          sprite = MONSTER_L;
      }
      else {
        if ( (world[x + 1][y] & SPRITEMASK) == EMPTY )
          sprite = MONSTER_R;
      }
      break;
    case TYPE_RT:
      //rechts [ *>]
      sprite++; if (sprite > MONSTER_R) sprite = MONSTER_D;
        if (testMove(x, y, sprite))
          break;
      //links [<*<]
      sprite--; sprite--; if (sprite < MONSTER_D) sprite = MONSTER_R; 
        if (testMove(x, y, sprite))
          break;
      //umkehr [>* ]
      sprite--; if (sprite < MONSTER_D) sprite = MONSTER_R;
        if (testMove(x, y, sprite))
          break;
    case TYPE_LT:
      //rechts [<* ]
      sprite--; if (sprite < MONSTER_D) sprite = MONSTER_R;
        if (testMove(x, y, sprite))
          break;
      //links [>*>]
      sprite++; sprite++; if (sprite > MONSTER_R) sprite = MONSTER_D;
        if (testMove(x, y, sprite))
          break;
      //umkehr [>* ]
      sprite++; if (sprite > MONSTER_R) sprite = MONSTER_D;
        if (testMove(x, y, sprite))
          break;
  }
  return sprite + type;
}

bool testMove(byte x, byte y, byte monster) {
  switch (monster) {
    case MONSTER_U:
      if (world[x][y - 1] == PLAYER) die();
      return (world[x][y - 1] == EMPTY) ? true : false; break;
    case MONSTER_L:
      if (world[x - 1][y] == PLAYER) die();
      return (world[x - 1][y] == EMPTY) ? true : false; break;
    case MONSTER_D:
      if (world[x][y + 1] == PLAYER) die();
      return (world[x][y + 1] == EMPTY) ? true : false; break;
    case MONSTER_R:
      if (world[x + 1][y] == PLAYER) die();
      return (world[x + 1][y] == EMPTY) ? true : false; break;
    default:
      return true; break;
  }
}
