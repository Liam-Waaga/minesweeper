
#include <cstdlib>
#include <raylib.h>

#include <array>


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


int main() {
    InitWindow(1366, 768, "hi");

    SetTargetFPS(60);

    std::array<std::array<Tile, TILE_Y>, TILE_X> game_state;

    for (int x = 0; x < TILE_X; x++) {
        for (int y = 0; y < TILE_Y; y++) {
            game_state[x][y] = {
                -1,
                false,
                false,
                false,
                true
            };
        }
    }

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
            /* todo set numbers*/
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("hi", 10, 10, 10, BLACK);
        EndDrawing();
    }
}