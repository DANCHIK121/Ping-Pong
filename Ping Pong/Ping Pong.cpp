// Standart libraries
#include <random>
#include <iostream>

// Projects libraries
#include "raylib.h"

// Functions signature
int randomFunction();

void main()
{
	std::cout << "Hello World!" << std::endl;

    // Initialization
    const int ballRadius = 20;
    const int screenWidth = 800;
    const int screenHeight = 450;

    int directionOfBallForY = randomFunction(); // If 1 - up btw 2 - down
    int directionOfBallForX = randomFunction(); // If 1 - up btw 2 - down
    
    Vector2 ballPosition = { ballRadius, ballRadius };

    InitWindow(screenWidth, screenHeight, "Ping Pong with C++ and raylib");

    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // X coords
        if (directionOfBallForX == 2 && ballPosition.x <= screenWidth - ballRadius)
            ballPosition.x += 2.0f;
        else
            directionOfBallForX = 1;

        if (directionOfBallForX == 1 && ballPosition.x >= ballRadius)
            ballPosition.x -= 2.0f;
        else
            directionOfBallForX = 2;

        // Y coords
        if (directionOfBallForY == 2 && ballPosition.y <= screenHeight - ballRadius)
            ballPosition.y += 2.0f;
        else 
            directionOfBallForY = 1;

        if (directionOfBallForY == 1 && ballPosition.y >= ballRadius)
            ballPosition.y -= 2.0f;
        else 
            directionOfBallForY = 2;

        // Drawing space
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("WASD", 10, 10, 20, DARKGRAY);

        DrawCircleV(ballPosition, ballRadius, BLACK);

        EndDrawing();
    }

    CloseWindow();
}

int randomFunction()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 2);

    return dist6(rng);
}

// Update
        //----------------------------------------------------------------------------------
        /*if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;*/
        //----------------------------------------------------------------------------------
