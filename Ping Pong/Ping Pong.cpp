// Standart libraries
#include <random>
#include <iostream>

// Projects libraries
#include "raylib.h"

// Functions signature
int randomFunction(int minValue, int maxValue);

enum StatusOfBallDirectionForY
{
    Up,
    Down,
};

enum StatusOfBallDirectionForX
{
    Left,
    Right,
};

void main()
{
    // Initialization
    // Ball settings
    const int ballRadius = 20;
    const float ballSpeed = 2.0f;
    // Screen settings
    const int screenFPS = 60;
    const int screenWidth = 800;
    const int screenHeight = 450;
    // HalfSquare settings
    const int halfSquareWidth = 20;
    const int halfSquareHeight = 100;
    const int firstHalfSquareSpeed = 2.0f;
    const int secondHalfSquareSpeed = 2.0f;
    // Variables of random ball direction
    int directionOfBallForYInInt = randomFunction(1, 2); 
    int directionOfBallForXInInt = randomFunction(1, 2);
    StatusOfBallDirectionForY directionOfBallForY;
    StatusOfBallDirectionForX directionOfBallForX;

    // Convert values
    if (directionOfBallForXInInt == 1)
        directionOfBallForX = StatusOfBallDirectionForX::Left;
    else
        directionOfBallForX = StatusOfBallDirectionForX::Right;
    if (directionOfBallForYInInt == 1)
        directionOfBallForY = StatusOfBallDirectionForY::Up;
    else
        directionOfBallForY = StatusOfBallDirectionForY::Down;

    // Objects position
    Vector2 ballPosition = { screenWidth / 2, screenHeight / 2 };
    Vector2 firstHalfSquarePosition = { halfSquareWidth, screenHeight / 2 - halfSquareHeight + 30};
    Vector2 secondHalfSquarePosition = { screenWidth - halfSquareWidth - 20, screenHeight / 2 - halfSquareHeight + 30 };

    InitWindow(screenWidth, screenHeight, "Ping Pong with C++ and raylib");

    SetTargetFPS(screenFPS);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        #pragma region Ball physics
        // X coords
        if (directionOfBallForX == StatusOfBallDirectionForX::Left && ballPosition.x <= screenWidth - ballRadius)
            ballPosition.x += ballSpeed;
        else
            directionOfBallForX = StatusOfBallDirectionForX::Right;

        if (directionOfBallForX == StatusOfBallDirectionForX::Right && ballPosition.x >= ballRadius)
            ballPosition.x -= ballSpeed;
        else
            directionOfBallForX = StatusOfBallDirectionForX::Left;

        // Y coords
        if (directionOfBallForY == StatusOfBallDirectionForY::Up && ballPosition.y <= screenHeight - ballRadius)
            ballPosition.y += ballSpeed;
        else 
            directionOfBallForY = StatusOfBallDirectionForY::Down;

        if (directionOfBallForY == StatusOfBallDirectionForY::Down && ballPosition.y >= ballRadius)
            ballPosition.y -= ballSpeed;
        else 
            directionOfBallForY = StatusOfBallDirectionForY::Up;
        #pragma endregion Ball physics

        #pragma region First Half Square physics
        // Y coords
        if (IsKeyDown(KEY_W) && firstHalfSquarePosition.y >= 5)
            firstHalfSquarePosition.y -= firstHalfSquareSpeed;
        if (IsKeyDown(KEY_S) && firstHalfSquarePosition.y <= screenHeight - halfSquareHeight - 10) 
            firstHalfSquarePosition.y += firstHalfSquareSpeed;
        #pragma endregion

        #pragma region Second Half Square physics
        // Y coords
        if (IsKeyDown(KEY_UP) && secondHalfSquarePosition.y >= 5)
            secondHalfSquarePosition.y -= secondHalfSquareSpeed;
        if (IsKeyDown(KEY_DOWN) && secondHalfSquarePosition.y <= screenHeight - halfSquareHeight - 10)
            secondHalfSquarePosition.y += secondHalfSquareSpeed;
        #pragma endregion

        #pragma region Objects draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Ping Pong Game", screenWidth / 2 - 80, 10, 20, DARKGRAY);

        // Draw gaming ball
        DrawCircleV(ballPosition, ballRadius, BLACK);

        // Draw first HalfSquare
        DrawRectangle(firstHalfSquarePosition.x, firstHalfSquarePosition.y, halfSquareWidth, halfSquareHeight, BLACK);

        // Draw second HalfSquare
        DrawRectangle(secondHalfSquarePosition.x, secondHalfSquarePosition.y, halfSquareWidth, halfSquareHeight, BLACK);

        EndDrawing();
        #pragma endregion
    }

    CloseWindow();
}

int randomFunction(int minValue, int maxValue)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(minValue, maxValue);

    return dist6(rng);
}

// Update
        //----------------------------------------------------------------------------------
        /*if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;*/
        //----------------------------------------------------------------------------------
