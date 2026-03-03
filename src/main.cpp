
#include <raylib.h>

int main() {
    InitWindow(1366, 768, "hi");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("hi", 10, 10, 10, BLACK);
        EndDrawing();
    }
}