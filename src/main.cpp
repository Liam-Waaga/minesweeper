
#include <cstdlib>
#include <raylib.h>

#include <array>

const unsigned char ZERO_PNG[] = {
#embed "../resources/0.png"
};

Image ZERO_IMG = LoadImageFromMemory("png", ZERO_PNG, sizeof(ZERO_PNG));
Texture2D ZERO_TEX = LoadTextureFromImage(ZERO_IMG);

const unsigned char ONE_PNG[] = {
#embed "../resources/1.png"
};

Image ONE_IMG = LoadImageFromMemory("png", ONE_PNG, sizeof(ONE_PNG));
Texture2D ONE_TEX = LoadTextureFromImage(ONE_IMG);

const unsigned char TWO_PNG[] = {
#embed "../resources/2.png"
};

Image TWO_IMG = LoadImageFromMemory("png", TWO_PNG, sizeof(TWO_PNG));
Texture2D TWO_TEX = LoadTextureFromImage(TWO_IMG);

const unsigned char THREE_PNG[] = {
#embed "../resources/3.png"
};

Image THREE_IMG = LoadImageFromMemory("png", THREE_PNG, sizeof(THREE_PNG));
Texture2D THREE_TEX = LoadTextureFromImage(THREE_IMG);

const unsigned char FOUR_PNG[] = {
#embed "../resources/4.png"
};

Image FOUR_IMG = LoadImageFromMemory("png", FOUR_PNG, sizeof(FOUR_PNG));
Texture2D FOUR_TEX = LoadTextureFromImage(FOUR_IMG);

const unsigned char FIVE_PNG[] = {
#embed "../resources/5.png"
};

Image FIVE_IMG = LoadImageFromMemory("png", FIVE_PNG, sizeof(FIVE_PNG));
Texture2D FIVE_TEX = LoadTextureFromImage(FIVE_IMG);

const unsigned char SIX_PNG[] = {
#embed "../resources/6.png"
};

Image SIX_IMG = LoadImageFromMemory("png", SIX_PNG, sizeof(SIX_PNG));
Texture2D SIX_TEX = LoadTextureFromImage(SIX_IMG);

const unsigned char SEVEN_PNG[] = {
#embed "../resources/7.png"
};

Image SEVEN_IMG = LoadImageFromMemory("png", SEVEN_PNG, sizeof(SEVEN_PNG));
Texture2D SEVEN_TEX = LoadTextureFromImage(SEVEN_IMG);

const unsigned char EIGHT_PNG[] = {
#embed "../resources/8.png"
};

Image EIGHT_IMG = LoadImageFromMemory("png", EIGHT_PNG, sizeof(EIGHT_PNG));
Texture2D EIGHT_TEX = LoadTextureFromImage(EIGHT_IMG);

const unsigned char BLANK_PNG[] = {
#embed "../resources/blank.png"
};

Image BLANK_IMG = LoadImageFromMemory("png", BLANK_PNG, sizeof(BLANK_PNG));
Texture2D BLANK_TEX = LoadTextureFromImage(BLANK_IMG);

const unsigned char BOMB_PNG[] = {
#embed "../resources/bomb_1.png"
};

Image BOMB_IMG = LoadImageFromMemory("png", BOMB_PNG, sizeof(BOMB_PNG));
Texture2D BOMB_TEX = LoadTextureFromImage(BOMB_IMG);

const unsigned char DIED_BOMB_PNG[] = {
#embed "../resources/died_bomb.png"
};

Image DIED_BOMB_IMG =
    LoadImageFromMemory("png", DIED_BOMB_PNG, sizeof(DIED_BOMB_PNG));
Texture2D DIED_BOMB_TEX = LoadTextureFromImage(DIED_BOMB_IMG);

const unsigned char MARKED_PNG[] = {
#embed "../resources/marked.png"
};

Image MARKED_IMG = LoadImageFromMemory("png", MARKED_PNG, sizeof(MARKED_PNG));
Texture2D MARKED_TEX = LoadTextureFromImage(MARKED_IMG);

const unsigned char MAYBE_PRESSED_PNG[] = {
#embed "../resources/maybe_pressed.png"
};

Image MAYBE_PRESSED_IMG =
    LoadImageFromMemory("png", MAYBE_PRESSED_PNG, sizeof(MAYBE_PRESSED_PNG));
Texture2D MAYBE_PRESSED_TEX = LoadTextureFromImage(MAYBE_PRESSED_IMG);

const unsigned char MAYBE_PNG[] = {
#embed "../resources/maybe.png"
};

Image MAYBE_IMG = LoadImageFromMemory("png", MAYBE_PNG, sizeof(MAYBE_PNG));
Texture2D MAYBE_TEX = LoadTextureFromImage(MAYBE_IMG);

const unsigned char NOT_BOMB_PNG[] = {
#embed "../resources/not_bomb.png"
};

Image NOT_BOMB_IMG =
    LoadImageFromMemory("png", NOT_BOMB_PNG, sizeof(NOT_BOMB_PNG));
Texture2D NOT_BOMB_TEX = LoadTextureFromImage(NOT_BOMB_IMG);

struct Tile {
  int num;
  bool is_clicked;
  bool is_marked;
  bool is_bomb;
  bool is_unitialized;
};

constexpr int BORDER_WIDTH = 8;
constexpr int HEADER_HEIGHT = 0;

constexpr int BOMB_COUNT = 55;

constexpr int TILE_X = 35;
constexpr int TILE_Y = 15;

constexpr int WINDOW_X = TILE_X * 32 + BORDER_WIDTH;
constexpr int WINDOW_Y = TILE_Y * 32 + BORDER_WIDTH + HEADER_HEIGHT;

bool is_alive = true;
bool won = false;
int current_mine_count = BOMB_COUNT;

typedef std::array<std::array<Tile, TILE_Y>, TILE_X> GameState;

GameState generate_board(int freex, int freey) {
  std::array<std::array<Tile, TILE_Y>, TILE_X> game_state;

  for (int x = 0; x < TILE_X; x++) {
    for (int y = 0; y < TILE_Y; y++) {
      game_state[x][y] = {-1, false, false, false, true};
    }
  }

  game_state[freex][freey].is_unitialized = false;

  srand(GetTime());

  for (int i = 0; i < BOMB_COUNT; i++) {
    int x = rand() % TILE_X;
    int y = rand() % TILE_Y;

    if (game_state[x][y].is_unitialized) {
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

      game_state[x][y].num = 0;

      if (y > 0 && x > 0 && game_state[x - 1][y - 1].is_bomb)
        game_state[x][y].num++;
      if (y > 0 && game_state[x][y - 1].is_bomb)
        game_state[x][y].num++;
      if (x > 0 && game_state[x - 1][y].is_bomb)
        game_state[x][y].num++;
      if (y > 0 && x < TILE_X - 1 && game_state[x + 1][y - 1].is_bomb)
        game_state[x][y].num++;
      if (x < TILE_X - 1 && game_state[x + 1][y].is_bomb)
        game_state[x][y].num++;
      if (y < TILE_Y - 1 && x < TILE_X - 1 && game_state[x + 1][y + 1].is_bomb)
        game_state[x][y].num++;
      if (y < TILE_Y - 1 && game_state[x][y + 1].is_bomb)
        game_state[x][y].num++;
      if (y < TILE_Y - 1 && x > 0 && game_state[x - 1][y + 1].is_bomb)
        game_state[x][y].num++;
      game_state[x][y].is_unitialized = false;
    }
  }
  return game_state;
}

void click(GameState &game_state, int x, int y, bool is_mark = false) {
  if (!is_mark) {
    game_state[x][y].is_clicked = true;
    if (game_state[x][y].is_bomb) {
      is_alive = false;
      return;
    }
    /* TODO: zero propagation */
    /* TODO: auto clearing */
  } else {
    game_state[x][y].is_marked =
        !game_state[x][y].is_clicked; /* if it has already been clicked, then we
                                         are doing the auto mark thing */
    if (game_state[x][y].is_marked)
      current_mine_count--;
    /* TODO: auto marking */
  }
}

void draw_board(GameState &game_state) {
  ClearBackground(GRAY);

  /* TODO: Draw Header */

  for (int x = 0; x < TILE_X; x++) {
    for (int y = 0; y < TILE_Y; y++) {
      int x_px = BORDER_WIDTH + x * 32;
      int y_px = BORDER_WIDTH + HEADER_HEIGHT + y * 32;

      Texture2D tex;

      if (game_state[x][y].is_clicked) {
        if (game_state[x][y].is_bomb) {
          tex = DIED_BOMB_TEX;
        } else {
          switch (game_state[x][y].num) {
          case 0:
            tex = ZERO_TEX;
          case 1:
            tex = ONE_TEX;
          case 2:
            tex = TWO_TEX;
          case 3:
            tex = THREE_TEX;
          case 4:
            tex = FOUR_TEX;
          case 5:
            tex = FIVE_TEX;
          case 6:
            tex = SIX_TEX;
          case 7:
            tex = SEVEN_TEX;
          case 8:
            tex = EIGHT_TEX;
          default:
            tex = MAYBE_TEX;
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

      DrawTexture(tex, x_px, y_px, WHITE);
    }
  }
}

int main() {
  InitWindow(1366, 768, "hi");

  SetTargetFPS(60);

  GameState game_state;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("hi", 10, 10, 10, BLACK);
    EndDrawing();
  }
}
