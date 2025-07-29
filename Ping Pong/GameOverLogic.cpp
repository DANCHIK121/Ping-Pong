// Standart libraries
#include <format>
#include <iostream>

// Project libraries
#include "raylib.h"
#include "raygui.h"

namespace GameOver
{
	inline static void GameOverFunction(char* argv[], int numberOfPlayerWin)
	{
		// Initialization
		// Screen settings
		const int screenFPS = 60;
		const int screenWidth = 400;
		const int screenHeight = 100;

		// Window init
		InitWindow(screenWidth, screenHeight, "Ping Pong with C++ and raylib");

		SetTargetFPS(screenFPS);

		while (!WindowShouldClose()) // Detect window close button or ESC key
		{
			#pragma region Objects draw
            BeginDrawing();

            ClearBackground(RAYWHITE);

            // Game status label
            DrawText("Game Over", 160, 10, 20, DARKGRAY);

			// Which player is win label
			if (numberOfPlayerWin == 1 || numberOfPlayerWin == 2)
				DrawText(std::format("Player Win: {}", numberOfPlayerWin).c_str(), 10, 60, 20, DARKGRAY);
			else
				DrawText("Player Win: Draw", 120, 40, 20, DARKGRAY);

			// End drawing
			EndDrawing();
			#pragma endregion
		}

        CloseWindow(); // Program end
	}
}