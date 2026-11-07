#include <raylib.h>
#include <iostream>

enum PenguinState
{
    ALIVE,
    DYING,
    DEAD
};

class Penguin
{
public:
    Vector2 position = { 400, 300 };
    PenguinState state = ALIVE;

    int frameWidth = 0;
    int frameHeight = 0;

    int currentFrame = 0;
    int currentDirection = 0; // Row 0 (facing down/forward)

    // Animation tracking
    float animationTimer = 0.0f;
    float animationSpeed = 0.15f;

    // Track the total columns and rows in your sheet
    const int totalCols = 8;
    const int totalRows = 11;

    Penguin() {}
    ~Penguin() {}

    void Initialize(Texture2D texture)
    {
        frameWidth = texture.width / totalCols;
        frameHeight = texture.height / totalRows;
    }

    void Update()
    {
        animationTimer += GetFrameTime();

        if (state == ALIVE)
        {
            // Normal idle/waddle animation loop (using the first 3 frames of row 0)
            currentDirection = 5; // row index facing forward waddling
            if (animationTimer >= animationSpeed)
            {
                currentFrame++;
                if (currentFrame >= 3) currentFrame = 0;
                animationTimer = 0.0f;
            }
        }
        else if (state == DYING)
        {
            // Play the dying animation (sliding flat on belly)
            currentDirection = 6; // row index for slide/death frames
            if (animationTimer >= animationSpeed)
            {
                currentFrame++;
                // The dying sequence row has about 4 key frames
                if (currentFrame >= 4)
                {
                    currentFrame = 3; // Stay stuck on the last flat frame
                    state = DEAD;
                }
                animationTimer = 0.0f;
            }
        }
    }

    Rectangle GetBounds()
    {
        return { position.x, position.y, (float)frameWidth, (float)frameHeight };
    }

    void Draw(Texture2D texture)
    {
        if (texture.id != 0)
        {
            Rectangle sourceRec = {
                (float)(currentFrame * frameWidth),
                (float)(currentDirection * frameHeight),
                (float)frameWidth,
                (float)frameHeight
            };

            DrawTextureRec(texture, sourceRec, position, WHITE);
        }
    }
};

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
        if (IsKeyDown(KEY_D))
        {
            bearPosition.x += movementSpeed * GetFrameTime();
            currentDirection = 1;
        }

        // Move left
        if (IsKeyDown(KEY_A))
        {
            bearPosition.x -= movementSpeed * GetFrameTime();
            currentDirection = 3;
        }

        // Move up
        if (IsKeyDown(KEY_W))
        {
            bearPosition.y -= movementSpeed * GetFrameTime();
            currentDirection = 0;
        }

        // Move down
        if (IsKeyDown(KEY_S))
        {
            bearPosition.y += movementSpeed * GetFrameTime();
            currentDirection = 2;
        }

        // Check if the bear is moving
        bool isMoving =
            IsKeyDown(KEY_D) ||
            IsKeyDown(KEY_A) ||
            IsKeyDown(KEY_W) ||
            IsKeyDown(KEY_S);

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

    InitWindow(windowWidth, windowHeight, "Polar Bear Game");

    SetTargetFPS(60);

    PolarBear bear;
    Penguin penguin;

    Texture2D snowbackground = LoadTexture("Assets/SnowBackground.png");
    Texture2D polarBear = LoadTexture("Assets/polar_bear.png");
    Texture2D penguinSheet = LoadTexture("Assets/PenguinSpriteSheet.png");

    // Calculate individual bear sprite frame dimensions
    if (polarBear.id != 0)
    {
        bear.frameWidth = polarBear.width / 3;
        bear.frameHeight = polarBear.height / 4;
    }
    else
    {
        std::cout << "Failed to load polar_bear.png" << std::endl;
    }

    // Initialize penguin sprite properties safely
    if (penguinSheet.id != 0)
    {
        penguin.Initialize(penguinSheet);
    }
    else
    {
        std::cout << "Failed to load PenguinSpriteSheet.png" << std::endl;
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
        // Update components
        bear.Update();
        penguin.Update();

        // Check for collision proximity between bear bounding box and penguin bounding box
        Rectangle bearBounds = {
            bear.bearPosition.x,
            bear.bearPosition.y,
            (float)bear.frameWidth,
            (float)bear.frameHeight
        };

        if (penguin.state == ALIVE && CheckCollisionRecs(bearBounds, penguin.GetBounds()))
        {
            penguin.state = DYING;
            penguin.currentFrame = 0;
            penguin.animationTimer = 0.0f;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw snow background
        if (snowbackground.id != 0)
        {
            Rectangle totalScreenRec = { 0, 0, (float)windowWidth, (float)windowHeight };
            Vector2 position = { 0, 0 };
            DrawTextureRec(snowbackground, totalScreenRec, position, WHITE);
        }

        // Draw Penguin
        penguin.Draw(penguinSheet);

        // Draw polar bear animation
        if (polarBear.id != 0)
        {
            Rectangle bearFrame = {
                (float)(bear.currentFrame * bear.frameWidth),
                (float)(bear.currentDirection * bear.frameHeight),
                (float)bear.frameWidth,
                (float)bear.frameHeight
            };

            DrawTextureRec(polarBear, bearFrame, bear.bearPosition, WHITE);
        }

        EndDrawing();
    }

    // Clean up all textures properly on exit
    if (polarBear.id != 0) UnloadTexture(polarBear);
    if (snowbackground.id != 0) UnloadTexture(snowbackground);
    if (penguinSheet.id != 0) UnloadTexture(penguinSheet);

    CloseWindow();

    return 0;
}
