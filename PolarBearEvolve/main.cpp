
#include <raylib.h>
#include <iostream>

class PolarBear
{
public:

    // Animation variables
    float animationTimer = 0.0f;
    float animationSpeed = 0.15f;

    int currentFrame = 0;
    int currentDirection = 2;

    // Bear position
    Vector2 bearPosition = { 500, 300 };

    // Sprite sheet dimensions
    int frameWidth = 0;
    int frameHeight = 0;

    // Movement speed
    float movementSpeed = 200.0f;

    void Update()
    {
        // Move right
        if (IsKeyDown(KEY_RIGHT))
        {
            bearPosition.x += movementSpeed * GetFrameTime();
            currentDirection = 1;
        }

        // Move left
        if (IsKeyDown(KEY_LEFT))
        {
            bearPosition.x -= movementSpeed * GetFrameTime();
            currentDirection = 3;
        }

        // Move up
        if (IsKeyDown(KEY_UP))
        {
            bearPosition.y -= movementSpeed * GetFrameTime();
            currentDirection = 0;
        }

        // Move down
        if (IsKeyDown(KEY_DOWN))
        {
            bearPosition.y += movementSpeed * GetFrameTime();
            currentDirection = 2;
        }

        // Check if the bear is moving
        bool isMoving =
            IsKeyDown(KEY_RIGHT) ||
            IsKeyDown(KEY_LEFT) ||
            IsKeyDown(KEY_UP) ||
            IsKeyDown(KEY_DOWN);

        // Handle animation
        if (isMoving)
        {
            animationTimer += GetFrameTime();

            if (animationTimer >= animationSpeed)
            {
                currentFrame++;

                if (currentFrame >= 3)
                {
                    currentFrame = 0;
                }

                animationTimer = 0.0f;
            }
        }
        else
        {
            currentFrame = 0;
            animationTimer = 0.0f;
        }
    }
};


int main()
{
    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Polar Bear");

    SetTargetFPS(60);

    PolarBear bear;

    Texture2D snowbackground =
        LoadTexture("Assets/SnowBackground.png");

    Texture2D polarBear =
        LoadTexture("Assets/polar_bear.png");

    // Calculate individual sprite frame dimensions
    if (polarBear.id != 0)
    {
        bear.frameWidth = polarBear.width / 3;
        bear.frameHeight = polarBear.height / 4;
    }
    else
    {
        std::cout << "Failed to load polar_bear.png" << std::endl;
    }

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
        // Update bear movement and animation
        bear.Update();

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw snow background
        if (snowbackground.id != 0)
        {
            Rectangle totalScreenRec = {
                0, 0,
                (float)windowWidth,
                (float)windowHeight
            };

            Vector2 position = { 0, 0 };

            DrawTextureRec(
                snowbackground,
                totalScreenRec,
                position,
                WHITE
            );
        }

        // Draw polar bear animation
        if (polarBear.id != 0)
        {
            Rectangle bearFrame = {
                (float)(bear.currentFrame * bear.frameWidth),
                (float)(bear.currentDirection * bear.frameHeight),
                (float)bear.frameWidth,
                (float)bear.frameHeight
            };

            DrawTextureRec(
                polarBear,
                bearFrame,
                bear.bearPosition,
                WHITE
            );
        }

        EndDrawing();
    }

    // Unload textures
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
