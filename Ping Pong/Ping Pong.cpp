// Standart libraries
#include <random>
#include <iostream>

// Projects libraries
#include "raylib.h"

// Functions signature
int randomFunction(int minValue, int maxValue);

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

    int directionOfBallForY = randomFunction(1, 2); // If 1 - up btw 2 - down
    int directionOfBallForX = randomFunction(1, 2); // If 1 - up btw 2 - down
    
    Vector2 ballPosition = { screenWidth / 2, screenHeight / 2 };
    Vector2 firstHalfSquarePosition = { halfSquareWidth + 5, screenHeight / 2 - halfSquareHeight + 30};

    InitWindow(screenWidth, screenHeight, "Ping Pong with C++ and raylib");

    SetTargetFPS(screenFPS);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // X coords
        if (directionOfBallForX == 2 && ballPosition.x <= screenWidth - ballRadius)
            ballPosition.x += ballSpeed;
        else
            directionOfBallForX = 1;

        if (directionOfBallForX == 1 && ballPosition.x >= ballRadius)
            ballPosition.x -= ballSpeed;
        else
            directionOfBallForX = 2;

        // Y coords
        if (directionOfBallForY == 2 && ballPosition.y <= screenHeight - ballRadius)
            ballPosition.y += ballSpeed;
        else 
            directionOfBallForY = 1;

        if (directionOfBallForY == 1 && ballPosition.y >= ballRadius)
            ballPosition.y -= ballSpeed;
        else 
            directionOfBallForY = 2;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("WASD and Arrows", 10, 10, 20, DARKGRAY);

        // Draw gaming ball
        DrawCircleV(ballPosition, ballRadius, BLACK);

        // Draw first HalfSquare
        DrawRectangle(firstHalfSquarePosition.x, firstHalfSquarePosition.y, halfSquareWidth, halfSquareHeight, BLACK);

        EndDrawing();
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
