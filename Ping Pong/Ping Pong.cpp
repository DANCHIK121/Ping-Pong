#pragma comment(lib, "raylib.lib")

// Standart libraries
#include <string>
#include <format>
#include <iostream>

// Projects libraries
#include "raylib.h"

// Project files
#include "GameLogicEnums.cpp"
#include "Functions/Functions.h"



int main()
{
    // Initialization
    // Level label object settings
    int currentLevel = 1;
    std::string levelLabel;
    
    // Points settings
    int onePointValue = 100;
    int firstPlayerPointsCount = 0;
    int secondPlayerPointsCount = 0;
    std::string firstPlayerPointsLabel;
    std::string secondPlayerPointsLabel;

    // Ball settings
    int ballRadius = 20;
    float ballSpeed = 2.0f;

    // Screen settings
    const int screenFPS = 60;
    const int screenWidth = 800;
    const int screenHeight = 450;

    // HalfSquare settings
    const int halfSquareWidth = 20;
    const int halfSquareHeight = 100;
    const int firstHalfSquareSpeed = 2.0f;
    const int secondHalfSquareSpeed = 2.0f;

    // Instances of classes
    ProjectFunctions::Functions* functions = new ProjectFunctions::Functions();

    // Variables of random ball direction
    int directionOfBallForYInInt = functions->RandomFunction(1, 2); 
    int directionOfBallForXInInt = functions->RandomFunction(1, 2);
    GameEnums::StatusOfBallDirectionForY directionOfBallForY;
    GameEnums::StatusOfBallDirectionForX directionOfBallForX;

    // Convert values
    // X coords
    if (directionOfBallForXInInt == 1)
        directionOfBallForX = GameEnums::StatusOfBallDirectionForX::Left;
    else
        directionOfBallForX = GameEnums::StatusOfBallDirectionForX::Right;

    // Y coords
    if (directionOfBallForYInInt == 1)
        directionOfBallForY = GameEnums::StatusOfBallDirectionForY::Up;
    else
        directionOfBallForY = GameEnums::StatusOfBallDirectionForY::Down;

    // Objects position
    Vector2 ballPosition = { screenWidth / 2, screenHeight / 2 };
    Vector2 firstHalfSquarePosition = { halfSquareWidth, screenHeight / 2 - halfSquareHeight + 30};
    Vector2 secondHalfSquarePosition = { screenWidth - halfSquareWidth - 20, screenHeight / 2 - halfSquareHeight + 30 };

    // Rectangle objects
    Rectangle firstHalfSquare;
    Rectangle secondHalfSquare;

    InitWindow(screenWidth, screenHeight, "Ping Pong with C++ and raylib");

    SetTargetFPS(screenFPS);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Rectangles update
        firstHalfSquare = { firstHalfSquarePosition.x, firstHalfSquarePosition.y, halfSquareWidth, halfSquareHeight };
        secondHalfSquare = { secondHalfSquarePosition.x, secondHalfSquarePosition.y, halfSquareWidth, halfSquareHeight };

        #pragma region Ball physics
        // X coords
        if (directionOfBallForX == GameEnums::StatusOfBallDirectionForX::Left && ballPosition.x <= screenWidth - ballRadius)
            ballPosition.x += ballSpeed;
        else
            directionOfBallForX = GameEnums::StatusOfBallDirectionForX::Right;

        if (directionOfBallForX == GameEnums::StatusOfBallDirectionForX::Right && ballPosition.x >= ballRadius)
            ballPosition.x -= ballSpeed;
        else
            directionOfBallForX = GameEnums::StatusOfBallDirectionForX::Left;

        // Y coords
        if (directionOfBallForY == GameEnums::StatusOfBallDirectionForY::Up && ballPosition.y <= screenHeight - ballRadius)
            ballPosition.y += ballSpeed;
        else 
            directionOfBallForY = GameEnums::StatusOfBallDirectionForY::Down;

        if (directionOfBallForY == GameEnums::StatusOfBallDirectionForY::Down && ballPosition.y >= ballRadius)
            ballPosition.y -= ballSpeed;
        else 
            directionOfBallForY = GameEnums::StatusOfBallDirectionForY::Up;
        #pragma endregion Ball physics

        #pragma region First Half Square physics
        // Y coords for first half-square
        if (IsKeyDown(KEY_W) && firstHalfSquarePosition.y >= 5)
            firstHalfSquarePosition.y -= firstHalfSquareSpeed;
        if (IsKeyDown(KEY_S) && firstHalfSquarePosition.y <= screenHeight - halfSquareHeight - 10) 
            firstHalfSquarePosition.y += firstHalfSquareSpeed;
        #pragma endregion

        #pragma region Second Half Square physics
        // Y coords for second half-square
        if (IsKeyDown(KEY_UP) && secondHalfSquarePosition.y >= 5)
            secondHalfSquarePosition.y -= secondHalfSquareSpeed;
        if (IsKeyDown(KEY_DOWN) && secondHalfSquarePosition.y <= screenHeight - halfSquareHeight - 10)
            secondHalfSquarePosition.y += secondHalfSquareSpeed;
        #pragma endregion

        #pragma region Level up logic
        // Level up
        if (firstPlayerPointsCount >= 1000 && secondPlayerPointsCount >= 1000)
        {
            // Change ball settings
            if (ballRadius - 2 >= 2) { ballRadius -= 2; }
            if (ballSpeed * 2 <= 1000) { ballSpeed *= 2; }

            // Change level index
            currentLevel++;

            // Reset player points
            firstPlayerPointsCount = 0;
            secondPlayerPointsCount = 0;

            continue;
        }
        #pragma endregion

        #pragma region Collision check
        // Collision first half-square with ball
        if (CheckCollisionCircleRec(ballPosition, ballRadius, firstHalfSquare))
        {
            directionOfBallForX = GameEnums::StatusOfBallDirectionForX::Left;
            firstPlayerPointsCount += onePointValue;
            continue;
        }

        // Collision second half-square with ball 
        if (CheckCollisionCircleRec(ballPosition, ballRadius, secondHalfSquare))
        {
            directionOfBallForX = GameEnums::StatusOfBallDirectionForX::Right;
            secondPlayerPointsCount += onePointValue;
            continue;
        }
        #pragma endregion

        #pragma region Update points
        firstPlayerPointsLabel = std::format("Your points: {}", firstPlayerPointsCount);
        secondPlayerPointsLabel = std::format("Your points: {}", secondPlayerPointsCount);
        #pragma endregion

        #pragma region Update level label
        // Update level label
        levelLabel = std::format("Level: {}", currentLevel);
        #pragma endregion

        #pragma region Objects draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Welocome label
        DrawText("Ping Pong Game", screenWidth / 2 - 80, 10, 20, DARKGRAY);

        #pragma region Level label draw
        // Level labels
        // First player
        DrawText(levelLabel.c_str(), 370, 40, 20, DARKGRAY);
        #pragma endregion

        #pragma region Poins draw
        // Points label
        // First player
        DrawText("First player", 5, 410, 20, DARKGRAY);
        DrawText(firstPlayerPointsLabel.c_str(), 5, 430, 20, DARKGRAY);

        // Second player
        DrawText("Second player", 615, 410, 20, DARKGRAY);
        DrawText(secondPlayerPointsLabel.c_str(), 615, 430, 20, DARKGRAY);
        #pragma endregion

        #pragma region Game objects draw
        // Draw gaming ball
        DrawCircleV(ballPosition, ballRadius, BLACK);

        // Draw first HalfSquare
        DrawRectangle(firstHalfSquarePosition.x, firstHalfSquarePosition.y, halfSquareWidth, halfSquareHeight, BLACK);

        // Draw second HalfSquare
        DrawRectangle(secondHalfSquarePosition.x, secondHalfSquarePosition.y, halfSquareWidth, halfSquareHeight, BLACK);
        #pragma endregion

        EndDrawing();
        #pragma endregion
    }

    CloseWindow(); // Program end

    return 0;
}
