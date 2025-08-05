// Define settings
#define _CRT_SECURE_NO_WARNINGS
#define RAYGUI_IMPLEMENTATION

// Standart libraries
#include <string>
#include <format>
#include <iostream>

// Projects libraries
#ifndef RAY_LIB_CONNECTION
#define RAY_LIB_CONNECTION
#include "raylib.h"
#endif 

#ifndef RAY_GUI_CONNECTION
#define RAY_GUI_CONNECTION
#include "raygui.h"
#endif

// Project files
#include "Json/Json.h"
#include "LevelsMap.cpp"
#include "GameLogicEnums.cpp"
#include "Functions/Functions.h"
#include "Audio/WorkWithAudio.h"
#include "Windows/GameOverLogic.cpp"
#include "Windows/SettingsWindowLogic.cpp"

void main()
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

    // Button settings
    std::string buttonText = "Settings";
    Rectangle buttonObject = { 325, 410, 150, 35 };

    // Ball settings
    float ballRadius = 20;
    float ballSpeed = 2.0f; // If 60 FPS -> 2.0f or if 120 FPS -> 1.0f

    // Screen settings
    int screenFPS = 60;
    const int screenWidth = 800;
    const int screenHeight = 450;

    // FPS Settings
    float preciseFPS = 0.0f;

    // HalfSquare settings
    int halfSquareSpeed = 2.0f;
    const int halfSquareWidth = 20;
    const int halfSquareHeight = 100;

    // Special rectangles
    const int specialRectangleWidth = 5;
    const int specialRectangleHeight = 450;

    // Instances of classes
    JsonLogic::Json* json = new JsonLogic::Json();
    WorkWithAudio::Audio* ballBouncedAudio = new WorkWithAudio::Audio();
    WorkWithAudio::Audio* ballBouncedOffAudio = new WorkWithAudio::Audio();
    ProjectFunctions::Functions* functions = new ProjectFunctions::Functions();

    // Settings for music
    ballBouncedAudio->LoadFileToBuffer(WorkWithAudio::MusicModes::TheBallBounced);
    auto ballBouncedAudioTemp = ballBouncedAudio->LoadBufferToSound();
    ballBouncedAudio->SetVolume(ballBouncedAudioTemp, 30);

    ballBouncedOffAudio->LoadFileToBuffer(WorkWithAudio::MusicModes::TheBallBouncedOff);
    auto ballBouncedOffAudioTemp = ballBouncedOffAudio->LoadBufferToSound();
    ballBouncedOffAudio->SetVolume(ballBouncedOffAudioTemp, 30);

    // Work with json
    nlohmann::json jsonTemp = json->ReadFromFile();

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
    Vector2 leftSpecialRectanglesPostions = { 0, 0 };
    Vector2 rightSpecialRectanglesPostions = { 0, 0 };
    Vector2 ballPosition = { screenWidth / 2, screenHeight / 2 };
    Vector2 firstHalfSquarePosition = { halfSquareWidth, screenHeight / 2 - halfSquareHeight + 30};
    Vector2 secondHalfSquarePosition = { screenWidth - halfSquareWidth - 20, screenHeight / 2 - halfSquareHeight + 30 };

    // Rectangle objects
    Rectangle firstHalfSquare;
    Rectangle secondHalfSquare;

    // Window init
    InitWindow(screenWidth, screenHeight, "Ping Pong with C++ and raylib");

    // Set Icon
    Image icon = LoadImage("./Icon/Icon.png"); // Load png
    SetWindowIcon(icon);
    UnloadImage(icon); // Unload png

    // Gui font settings
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30); // Change size of text
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER); // Center text in button

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        SetWindowSize(screenWidth, screenHeight);

        // FPS Limiter
        screenFPS = jsonTemp["FPSLimiter"].get<int>();
        SetTargetFPS(screenFPS);

        // Show FPS
        if (jsonTemp["ShowFPSInGame"].get<std::string>() == "TRUE") { preciseFPS = 1.0f / GetFrameTime(); }

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

        // Check condition for game over
        if (ballPosition.x == screenWidth - ballRadius || ballPosition.x == ballRadius)
        {
            ballBouncedOffAudio->PlayMusic(ballBouncedOffAudioTemp);

            if (firstPlayerPointsCount > secondPlayerPointsCount) { GameOver::GameOverFunction(1); }
            else if (firstPlayerPointsCount < secondPlayerPointsCount) { GameOver::GameOverFunction(2); }
            else { GameOver::GameOverFunction(0); }

            // functions->ResetGameData(currentLevel, firstPlayerPointsCount, secondPlayerPointsCount, ballRadius, ballSpeed, halfSquareSpeed);

            continue;
        }
        #pragma endregion Ball physics

        #pragma region First Half Square physics
        // Y coords for first half-square
        if (IsKeyDown(KEY_W) && firstHalfSquarePosition.y >= 5)
            firstHalfSquarePosition.y -= halfSquareSpeed;
        if (IsKeyDown(KEY_S) && firstHalfSquarePosition.y <= screenHeight - halfSquareHeight - 10) 
            firstHalfSquarePosition.y += halfSquareSpeed;
        #pragma endregion

        #pragma region Second Half Square physics
        // Y coords for second half-square
        if (IsKeyDown(KEY_UP) && secondHalfSquarePosition.y >= 5)
            secondHalfSquarePosition.y -= halfSquareSpeed;
        if (IsKeyDown(KEY_DOWN) && secondHalfSquarePosition.y <= screenHeight - halfSquareHeight - 10)
            secondHalfSquarePosition.y += halfSquareSpeed;
        #pragma endregion

        #pragma region Level up logic
        // Level up
        if (firstPlayerPointsCount >= GameLevels::LevelsMap[currentLevel] && secondPlayerPointsCount >= GameLevels::LevelsMap[currentLevel] &&
            currentLevel + 1 <= 3)
        {
            // Change ball and half-squares settings
            if (ballRadius / 2 >= 0.5f) { ballRadius /= 2; }
            if (ballSpeed * 2 <= 1000) { ballSpeed *= 2; }
            if (halfSquareSpeed * 2 <= 1000) { halfSquareSpeed *= 2; }

            // Change level index
            currentLevel++;

            // Multiply onePointValue
            onePointValue *= 2;

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
            ballBouncedAudio->PlayMusic(ballBouncedAudioTemp);
            continue;
        }

        // Collision second half-square with ball 
        if (CheckCollisionCircleRec(ballPosition, ballRadius, secondHalfSquare))
        {
            directionOfBallForX = GameEnums::StatusOfBallDirectionForX::Right;
            secondPlayerPointsCount += onePointValue;
            ballBouncedAudio->PlayMusic(ballBouncedAudioTemp);
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

        #pragma region Buttons
        // Draw settings button
        if (GuiButton(buttonObject, buttonText.c_str()))
        {
            SettingsWindow::SettingsWindowFunction();
            continue;
        }
        #pragma endregion

        #pragma region Objects draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Welcome label
        DrawText("Ping Pong Game", screenWidth / 2 - 80, 10, 20, DARKGRAY);

        // Draw middle line
        DrawRectangle(screenWidth / 2, 60, 5, 345, BLACK);

        #pragma region Level label draw
        // Level labels
        // First player
        DrawText(levelLabel.c_str(), 370, 40, 20, DARKGRAY);
        #pragma endregion

        #pragma region Current FPS draw
        // FPS label
        if (jsonTemp["ShowFPSInGame"].get<std::string>() == "TRUE")
            DrawText(std::format("FPS: {}", (int)preciseFPS).c_str(), 710, 10, 20, DARKGRAY);
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

        // Draw special rectangles
        // Left
        DrawRectangle(secondHalfSquarePosition.x, secondHalfSquarePosition.y, halfSquareWidth, halfSquareHeight, BLACK);
        #pragma endregion

        EndDrawing();
        #pragma endregion
    }

    CloseWindow(); // Program end
}
