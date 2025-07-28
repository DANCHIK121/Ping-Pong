// Standart libraries
#include <iostream>

// Project libraries
#include "raylib.h"

namespace GameOver
{
	inline static void GameOverFunction()
	{
		// Initialization
		// Screen settings
		const int screenFPS = 60;
		const int screenWidth = 200;
		const int screenHeight = 100;

		// Window init
		InitWindow(screenWidth, screenHeight, "Ping Pong with C++ and raylib");

		SetTargetFPS(screenFPS);

		while (!WindowShouldClose()) // Detect window close button or ESC key
		{
			#pragma region Objects draw
            BeginDrawing();

            ClearBackground(RAYWHITE);

            // Welcome label
            DrawText("Game Over", 10, 10, 20, DARKGRAY);

            // Draw first HalfSquare
            // DrawRectangle(firstHalfSquarePosition.x, firstHalfSquarePosition.y, halfSquareWidth, halfSquareHeight, BLACK);

			// End drawing
			EndDrawing();
			#pragma endregion
		}

        CloseWindow(); // Program end
	}
}