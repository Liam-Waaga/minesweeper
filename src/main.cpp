
/* Copyright c 2026 N Liam Waaga */
/* Permission is hereby granted, free of charge, to any person obtaining a copy of this software */
/* and associated documentation files (the "Software"), to deal in the Software without */
/* restriction, sublicense, and/or sell copies of the Software, and to permit persons to whom the */
/* Software is furnished to do so, subject to the following conditions: */
/* The above copyright notice and this permission notice shall beincluded in all copies or */
/* substantial portions of the Software. */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRENTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING */
/* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULARE PURPOSE AND */
/* NONINFRINGMENT. IN NO EVENT SHALL TEH AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, */
/* DAMAGES OR OTHER LIABILITY< WHETER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING */
/* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */



#include <cstdlib>
#include <ctime>
#include <raylib.h>

#include <array>
#ifndef NDEBUG
#include <iostream>
#endif

const unsigned char ZERO_PNG[] = {
#embed "../resources/0.png"
};

const unsigned char ONE_PNG[] = {
#embed "../resources/1.png"
};

const unsigned char TWO_PNG[] = {
#embed "../resources/2.png"
};

const unsigned char THREE_PNG[] = {
#embed "../resources/3.png"
};

const unsigned char FOUR_PNG[] = {
#embed "../resources/4.png"
};

const unsigned char FIVE_PNG[] = {
#embed "../resources/5.png"
};

const unsigned char SIX_PNG[] = {
#embed "../resources/6.png"
};

const unsigned char SEVEN_PNG[] = {
#embed "../resources/7.png"
};

const unsigned char EIGHT_PNG[] = {
#embed "../resources/8.png"
};

const unsigned char BLANK_PNG[] = {
#embed "../resources/blank.png"
};

const unsigned char BOMB_PNG[] = {
#embed "../resources/bomb_1.png"
};

const unsigned char DIED_BOMB_PNG[] = {
#embed "../resources/died_bomb.png"
};

const unsigned char MARKED_PNG[] = {
#embed "../resources/marked.png"
};

const unsigned char MAYBE_PRESSED_PNG[] = {
#embed "../resources/maybe_pressed.png"
};

const unsigned char MAYBE_PNG[] = {
#embed "../resources/maybe.png"
};

const unsigned char NOT_BOMB_PNG[] = {
#embed "../resources/not_bomb.png"
};

Image ZERO_IMG;
Texture2D ZERO_TEX;
Image ONE_IMG;
Texture2D ONE_TEX;
Image TWO_IMG;
Texture2D TWO_TEX;
Image THREE_IMG;
Texture2D THREE_TEX;
Image FOUR_IMG;
Texture2D FOUR_TEX;
Image FIVE_IMG;
Texture2D FIVE_TEX;
Image SIX_IMG;
Texture2D SIX_TEX;
Image SEVEN_IMG;
Texture2D SEVEN_TEX;
Image EIGHT_IMG;
Texture2D EIGHT_TEX;
Image BLANK_IMG;
Texture2D BLANK_TEX;
Image BOMB_IMG;
Texture2D BOMB_TEX;
Image DIED_BOMB_IMG;
Texture2D DIED_BOMB_TEX;
Image MARKED_IMG;
Texture2D MARKED_TEX;
Image MAYBE_PRESSED_IMG;
Texture2D MAYBE_PRESSED_TEX;
Image MAYBE_IMG;
Texture2D MAYBE_TEX;

Image NOT_BOMB_IMG;
Texture2D NOT_BOMB_TEX;

struct Tile {
  int num;
  bool is_clicked;
  bool is_marked;
  bool is_bomb;
  bool is_unitialized;
};

constexpr int BORDER_WIDTH = 8;
constexpr int HEADER_HEIGHT = 8;

constexpr int BOMB_COUNT = 175;

constexpr int TILE_X = 35;
constexpr int TILE_Y = 25;

constexpr int WINDOW_X = TILE_X * 32 + BORDER_WIDTH * 2;
constexpr int WINDOW_Y = TILE_Y * 32 + BORDER_WIDTH + HEADER_HEIGHT;

bool is_alive = true;
bool won = false;
int current_mine_count = BOMB_COUNT;

typedef std::array<std::array<Tile, TILE_Y>, TILE_X> GameState;

int count_bombs(GameState &game_state, int x, int y) {
  int num = 0;
  if (y > 0 && x > 0 && game_state[x - 1][y - 1].is_bomb)
    num++;
  if (y > 0 && game_state[x][y - 1].is_bomb)
    num++;
  if (x > 0 && game_state[x - 1][y].is_bomb)
    num++;
  if (y > 0 && x < TILE_X - 1 && game_state[x + 1][y - 1].is_bomb)
    num++;
  if (x < TILE_X - 1 && game_state[x + 1][y].is_bomb)
    num++;
  if (y < TILE_Y - 1 && x < TILE_X - 1 && game_state[x + 1][y + 1].is_bomb)
    num++;
  if (y < TILE_Y - 1 && game_state[x][y + 1].is_bomb)
    num++;
  if (y < TILE_Y - 1 && x > 0 && game_state[x - 1][y + 1].is_bomb)
    num++;
  return num;
}

int count_marked(GameState &game_state, int x, int y) {
  int num = 0;
  if (y > 0 && x > 0 && game_state[x - 1][y - 1].is_marked)
    num++;
  if (y > 0 && game_state[x][y - 1].is_marked)
    num++;
  if (x > 0 && game_state[x - 1][y].is_marked)
    num++;
  if (y > 0 && x < TILE_X - 1 && game_state[x + 1][y - 1].is_marked)
    num++;
  if (x < TILE_X - 1 && game_state[x + 1][y].is_marked)
    num++;
  if (y < TILE_Y - 1 && x < TILE_X - 1 && game_state[x + 1][y + 1].is_marked)
    num++;
  if (y < TILE_Y - 1 && game_state[x][y + 1].is_marked)
    num++;
  if (y < TILE_Y - 1 && x > 0 && game_state[x - 1][y + 1].is_marked)
    num++;
  return num;
}


GameState generate_board(GameState &game_state, int freex, int freey) {

  game_state[freex][freey].is_unitialized = false;
  game_state[freex][freey].is_bomb = false;
  game_state[freex][freey].is_clicked = false;
  game_state[freex][freey].is_marked = false;

  if (freey > 0 && freex > 0) {
    game_state[freex - 1][freey - 1].is_unitialized = false;
    game_state[freex - 1][freey - 1].is_bomb = false;
    game_state[freex - 1][freey - 1].is_marked = false;
    game_state[freex - 1][freey - 1].is_clicked = false;
  }
  if (freey > 0) {
    game_state[freex][freey - 1].is_unitialized = false;
    game_state[freex][freey - 1].is_bomb = false;
    game_state[freex][freey - 1].is_marked = false;
    game_state[freex][freey - 1].is_clicked = false;
  }
  if (freex > 0) {
    game_state[freex - 1][freey].is_unitialized = false;
    game_state[freex - 1][freey].is_bomb = false;
    game_state[freex - 1][freey].is_marked = false;
    game_state[freex - 1][freey].is_clicked = false;
  }
  if (freey > 0 && freex < TILE_X - 1) {
    game_state[freex + 1][freey - 1].is_unitialized = false;
    game_state[freex + 1][freey - 1].is_bomb = false;
    game_state[freex + 1][freey - 1].is_marked = false;
    game_state[freex + 1][freey - 1].is_clicked = false;
  }
  if (freex < TILE_X - 1) {
    game_state[freex + 1][freey].is_unitialized = false;
    game_state[freex + 1][freey].is_bomb = false;
    game_state[freex + 1][freey].is_marked = false;
    game_state[freex + 1][freey].is_clicked = false;
  }
  if (freey < TILE_Y - 1 && freex < TILE_X - 1) {
    game_state[freex + 1][freey + 1].is_unitialized = false;
    game_state[freex + 1][freey + 1].is_bomb = false;
    game_state[freex + 1][freey + 1].is_marked = false;
    game_state[freex + 1][freey + 1].is_clicked = false;
  }
  if (freey < TILE_Y - 1) {
    game_state[freex][freey + 1].is_unitialized = false;
    game_state[freex][freey + 1].is_bomb = false;
    game_state[freex][freey + 1].is_marked = false;
    game_state[freex][freey + 1].is_clicked = false;
  }
  if (freey < TILE_Y - 1 && freex > 0) {
    game_state[freex - 1][freey + 1].is_unitialized = false;
    game_state[freex - 1][freey + 1].is_bomb = false;
    game_state[freex - 1][freey + 1].is_marked = false;
    game_state[freex - 1][freey + 1].is_clicked = false;
  }

  for (int i = 0; i < BOMB_COUNT; i++) {
    int x = rand() % TILE_X;
    int y = rand() % TILE_Y;

    if (game_state[x][y].is_unitialized && !game_state[x][y].is_bomb &&
        (abs(freex - x) != 1 && abs(freey - y) != 1)) {
      game_state[x][y].is_bomb = true;
      game_state[x][y].is_unitialized = false;
    } else {
      --i;
    }
  }
  for (int x = 0; x < TILE_X; x++) {
    for (int y = 0; y < TILE_Y; y++) {

      if (game_state[x][y].is_bomb)
        continue;

      game_state[x][y].num = count_bombs(game_state, x, y);

      game_state[x][y].is_unitialized = false;
    }
  }
  return game_state;
}

constexpr GameState blank_board() {
  GameState game_state;
  for (int x = 0; x < TILE_X; x++) {
    for (int y = 0; y < TILE_Y; y++) {
      game_state[x][y] = {-6, false, false, false, true};
    }
  }
  return game_state;
}

void click(GameState &game_state, int x, int y, bool is_mark = false) {
  if (x < 0 || x >= TILE_X)
    return;
  if (y < 0 || y >= TILE_Y)
    return;

  if (!is_mark) {
    if (game_state[x][y].is_marked) {
      return;
    }
    if (game_state[x][y].is_bomb) {
      is_alive = false;
      game_state[x][y].is_clicked = true;
      return;
    }
    if (!game_state[x][y].is_clicked) {
      game_state[x][y].is_clicked = true;

      if (game_state[x][y].num == 0) {
        if (x > 0 && y > 0 && !game_state[x - 1][y - 1].is_clicked)
          click(game_state, x - 1, y - 1, false);
        if (x && y > 0 && !game_state[x][y - 1].is_clicked)
          click(game_state, x, y - 1, false);
        if (x < TILE_X - 1 && y > 0 && !game_state[x + 1][y - 1].is_clicked)
          click(game_state, x + 1, y - 1, false);
        if (x < TILE_X - 1 && !game_state[x + 1][y].is_clicked)
          click(game_state, x + 1, y, false);
        if (x < TILE_X - 1 && y < TILE_Y - 1 &&
            !game_state[x + 1][y + 1].is_clicked)
          click(game_state, x + 1, y + 1, false);
        if (y < TILE_Y - 1 && !game_state[x][y + 1].is_clicked)
          click(game_state, x, y + 1, false);
        if (x > 0 && y < TILE_Y - 1 && !game_state[x - 1][y + 1].is_clicked)
          click(game_state, x - 1, y + 1, false);
        if (x > 0 && !game_state[x - 1][y].is_clicked)
          click(game_state, x - 1, y, false);
      }
    } else {
      if (count_marked(game_state, x, y) == game_state[x][y].num) {
        /* TODO: auto clearing */
        if (y > 0 && x > 0 && !game_state[x - 1][y - 1].is_marked &&
            !game_state[x - 1][y - 1].is_clicked)
          click(game_state, x - 1, y - 1);
        if (y > 0 && !game_state[x][y - 1].is_marked &&
            !game_state[x][y - 1].is_clicked)
          click(game_state, x, y - 1);
        if (x > 0 && !game_state[x - 1][y].is_marked &&
            !game_state[x - 1][y].is_clicked)
          click(game_state, x - 1, y);
        if (y > 0 && x < TILE_X - 1 && !game_state[x + 1][y - 1].is_marked &&
            !game_state[x + 1][y - 1].is_clicked)
          click(game_state, x + 1, y - 1);
        if (x < TILE_X - 1 && !game_state[x + 1][y].is_marked &&
            !game_state[x + 1][y].is_clicked)
          click(game_state, x + 1, y);
        if (y < TILE_Y - 1 && x < TILE_X - 1 &&
            !game_state[x + 1][y + 1].is_marked &&
            !game_state[x + 1][y + 1].is_clicked)
          click(game_state, x + 1, y + 1);
        if (y < TILE_Y - 1 && !game_state[x][y + 1].is_marked &&
            !game_state[x][y + 1].is_clicked)
          click(game_state, x, y + 1);
        if (y < TILE_Y - 1 && x > 0 && !game_state[x - 1][y + 1].is_marked &&
            !game_state[x - 1][y + 1].is_clicked)
          click(game_state, x - 1, y + 1);
      }
    }

  } else {
    if (game_state[x][y].is_marked) {
      game_state[x][y].is_marked = false;
    } else {
      game_state[x][y].is_marked =
          !game_state[x][y].is_clicked; /* if it has already been clicked, then we
                                           are doing the auto mark thing */
    }
    /* TODO: auto marking */
  }
}

void draw_board(GameState &game_state) {
  ClearBackground(GRAY);

  /* TODO: Draw Header */

  for (int x = 0; x < TILE_X; x++) {
    for (int y = 0; y < TILE_Y; y++) {
      int x_px = BORDER_WIDTH + x * 32;
      int y_px = HEADER_HEIGHT + y * 32;

      Texture2D tex;

      if (game_state[x][y].is_unitialized) {
        tex = BLANK_TEX;
      } else {
        if (game_state[x][y].is_clicked) {
          if (game_state[x][y].is_bomb) {
            tex = DIED_BOMB_TEX;
          } else {
            switch (game_state[x][y].num) {
            case 0:
              tex = ZERO_TEX;
              break;
            case 1:
              tex = ONE_TEX;
              break;
            case 2:
              tex = TWO_TEX;
              break;
            case 3:
              tex = THREE_TEX;
              break;
            case 4:
              tex = FOUR_TEX;
              break;
            case 5:
              tex = FIVE_TEX;
              break;
            case 6:
              tex = SIX_TEX;
              break;
            case 7:
              tex = SEVEN_TEX;
              break;
            case 8:
              tex = EIGHT_TEX;
              break;
            default:
              tex = MAYBE_TEX;
              break;
            }
          }
        } else if (game_state[x][y].is_marked) {
          if (is_alive) {
            tex = MARKED_TEX;
          } else {
            if (game_state[x][y].is_bomb) {
              tex = BOMB_TEX;
            } else {
              tex = NOT_BOMB_TEX;
            }
          }
        } else {

          tex = BLANK_TEX;
        }
        if (!is_alive) {
          if (game_state[x][y].is_bomb) {
            tex = BOMB_TEX;
          }
        }
      }
      DrawTexture(tex, x_px, y_px, WHITE);
    }
  }
}

int main() {
  srand(time(NULL));
  InitWindow(WINDOW_X, WINDOW_Y, "Minesweeper");

  ZERO_IMG = LoadImageFromMemory(".png", ZERO_PNG, sizeof(ZERO_PNG));
  ZERO_TEX = LoadTextureFromImage(ZERO_IMG);

  ONE_IMG = LoadImageFromMemory(".png", ONE_PNG, sizeof(ONE_PNG));
  ONE_TEX = LoadTextureFromImage(ONE_IMG);

  TWO_IMG = LoadImageFromMemory(".png", TWO_PNG, sizeof(TWO_PNG));
  TWO_TEX = LoadTextureFromImage(TWO_IMG);

  THREE_IMG = LoadImageFromMemory(".png", THREE_PNG, sizeof(THREE_PNG));
  THREE_TEX = LoadTextureFromImage(THREE_IMG);

  FOUR_IMG = LoadImageFromMemory(".png", FOUR_PNG, sizeof(FOUR_PNG));
  FOUR_TEX = LoadTextureFromImage(FOUR_IMG);

  FIVE_IMG = LoadImageFromMemory(".png", FIVE_PNG, sizeof(FIVE_PNG));
  FIVE_TEX = LoadTextureFromImage(FIVE_IMG);

  SIX_IMG = LoadImageFromMemory(".png", SIX_PNG, sizeof(SIX_PNG));
  SIX_TEX = LoadTextureFromImage(SIX_IMG);

  SEVEN_IMG = LoadImageFromMemory(".png", SEVEN_PNG, sizeof(SEVEN_PNG));
  SEVEN_TEX = LoadTextureFromImage(SEVEN_IMG);

  EIGHT_IMG = LoadImageFromMemory(".png", EIGHT_PNG, sizeof(EIGHT_PNG));
  EIGHT_TEX = LoadTextureFromImage(EIGHT_IMG);

  BLANK_IMG = LoadImageFromMemory(".png", BLANK_PNG, sizeof(BLANK_PNG));
  BLANK_TEX = LoadTextureFromImage(BLANK_IMG);

  BOMB_IMG = LoadImageFromMemory(".png", BOMB_PNG, sizeof(BOMB_PNG));
  BOMB_TEX = LoadTextureFromImage(BOMB_IMG);

  DIED_BOMB_IMG =
      LoadImageFromMemory(".png", DIED_BOMB_PNG, sizeof(DIED_BOMB_PNG));
  DIED_BOMB_TEX = LoadTextureFromImage(DIED_BOMB_IMG);

  MARKED_IMG = LoadImageFromMemory(".png", MARKED_PNG, sizeof(MARKED_PNG));
  MARKED_TEX = LoadTextureFromImage(MARKED_IMG);

  MAYBE_PRESSED_IMG =
      LoadImageFromMemory(".png", MAYBE_PRESSED_PNG, sizeof(MAYBE_PRESSED_PNG));
  MAYBE_PRESSED_TEX = LoadTextureFromImage(MAYBE_PRESSED_IMG);

  MAYBE_IMG = LoadImageFromMemory(".png", MAYBE_PNG, sizeof(MAYBE_PNG));
  MAYBE_TEX = LoadTextureFromImage(MAYBE_IMG);

  NOT_BOMB_IMG =
      LoadImageFromMemory(".png", NOT_BOMB_PNG, sizeof(NOT_BOMB_PNG));
  NOT_BOMB_TEX = LoadTextureFromImage(NOT_BOMB_IMG);

  SetTargetFPS(60);

  GameState game_state = blank_board();
  generate_board(game_state, TILE_X / 2, TILE_Y / 2);
  click(game_state, TILE_X / 2, TILE_Y / 2);

#ifndef NDEBUG
  for (int y = 0; y < TILE_Y; y++) {
    for (int x = 0; x < TILE_X; x++) {
      std::cout << (char)(game_state[x][y].num + '0') << " ";
    }
    std::cout << "\n";
  }
#endif

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    if (is_alive) {
      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        int x = (GetMouseX() - BORDER_WIDTH) / 32;
        int y = (GetMouseY() - HEADER_HEIGHT) / 32;
        if (x >= 0 && y >= 0) {
          click(game_state, x, y);
        }
      }
      if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
        int x = (GetMouseX() - BORDER_WIDTH) / 32;
        int y = (GetMouseY() - HEADER_HEIGHT) / 32;
        if (x >= 0 && y >= 0) {
          click(game_state, x, y, true);
        }
      }
    }
    draw_board(game_state);
    EndDrawing();
    if (IsKeyReleased(KEY_R)) {
      game_state = blank_board();
      generate_board(game_state, TILE_X / 2, TILE_Y / 2);
      click(game_state, TILE_X / 2, TILE_Y / 2);
      is_alive = true;
    }
  }
}
