#include <raylib.h>
#include <iostream>

int main()
{
    InitWindow(720, 900, "Polar Bear");

    Texture2D snowbackground = LoadTexture("Assets/SnowBackground.png");


    if (snowbackground.id == 0)
    {
        std::cout << "Failed to load SnowBackground.jpg" << std::endl;
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);

        if (snowbackground.id != 0)
        {
            DrawTexture(snowbackground, 0, 0, WHITE);
        }

        EndDrawing();
    }

    if (snowbackground.id != 0)
    {
        UnloadTexture(snowbackground);
    }

    CloseWindow();

    return 0;
}