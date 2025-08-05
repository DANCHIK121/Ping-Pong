// Standart libraries
#include <format>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

// Project libraries
#ifndef RAY_LIB_CONNECTION
#define RAY_LIB_CONNECTION
#include "raylib.h"
#endif 

#ifndef RAY_GUI_CONNECTION
#define RAY_GUI_CONNECTION
#include "raygui.h"
#endif

namespace GameOver
{
	inline static int GameOverFunction(int numberOfPlayerWin)
	{
		// Initialization
		// Screen settings
		const int screenWidth = 400;
		const int screenHeight = 200;

		// Button settings
		// Exit button
		std::string exitButtonText = "Exit";
		Rectangle exitButtonObject = { 160, 100, 120, 35 };

		while (!WindowShouldClose()) // Detect window close button or ESC key
		{
			// Window init
			SetWindowSize(screenWidth, screenHeight);

			#pragma region Objects draw
            BeginDrawing();

            ClearBackground(RAYWHITE);

            // Game status label
            DrawText("Game Over", 160, 10, 20, DARKGRAY);

			// Which player is win label
			if (numberOfPlayerWin == 1 || numberOfPlayerWin == 2)
				DrawText(std::format("Player Win: {}", numberOfPlayerWin).c_str(), 120, 60, 20, DARKGRAY);
			else
				DrawText("Player Win: Draw", 130, 40, 20, DARKGRAY);

			// Draw exit button
			if (GuiButton(exitButtonObject, exitButtonText.c_str()))
				exit(0);

			// End drawing
			EndDrawing();
			#pragma endregion
		}

		return 0;
	}
}