
#include <raylib.h>
#include <iostream>

class PolarBear
{
public:

    Texture2D polarbear;


    Vector2 bearPosition = { 500, 300 };

    int frameWidth;
    int frameHeight;

    float movementSpeed = 200.0f;

    void Update() {
        if (IsKeyDown(KEY_RIGHT)) bearPosition.x += movementSpeed * GetFrameTime();
       
        if (IsKeyDown(KEY_LEFT)) bearPosition.x -= movementSpeed * GetFrameTime();
        

        if (IsKeyDown(KEY_UP)) bearPosition.y -= movementSpeed * GetFrameTime();
       
        if (IsKeyDown(KEY_DOWN)) bearPosition.y += movementSpeed * GetFrameTime();
        
    }

};


int main()
{
    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Polar Bear");

    PolarBear bear;

    Texture2D snowbackground = LoadTexture("Assets/SnowBackground.png");

    Texture2D polarBear = LoadTexture("Assets/polar_bear.png");

    if (snowbackground.id == 0)
    {
        std::cout << "Failed to load SnowBackground.png" << std::endl;
    }
    else
    {
        SetTextureWrap(snowbackground, TEXTURE_WRAP_REPEAT);
    }

    while (!WindowShouldClose())
    {
        bear.Update();
        BeginDrawing();
        ClearBackground(BLACK);

        if (snowbackground.id != 0)
        {
            Rectangle totalScreenRec = {
                0, 0,
                (float)windowWidth,
                (float)windowHeight
            };

            Vector2 position = { 0, 0 };

            DrawTextureRec(snowbackground, totalScreenRec, position, WHITE);
        }

        if (polarBear.id != 0)
        {
            Rectangle bearFrame = {
                0,
                0,
                polarBear.width / 3.0f,
            polarBear.height / 4.0f
            };

            

            DrawTextureRec(polarBear, bearFrame, bear.bearPosition, WHITE);
            


        }

        EndDrawing();
    }

    if (polarBear.id != 0)
    {
        UnloadTexture(polarBear);
    }

    if (snowbackground.id != 0)
    {
        UnloadTexture(snowbackground);
        
    }

    CloseWindow();
    return 0;
}
