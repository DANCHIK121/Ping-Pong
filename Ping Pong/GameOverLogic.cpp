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
	inline static int GameOverFunction(char* argv[], int numberOfPlayerWin)
	{
		// Initialization
		// Screen settings
		const int screenFPS = 60;
		const int screenWidth = 400;
		const int screenHeight = 150;

		// Button settings
		std::string buttonText = "Exit";
		Rectangle buttonObject = { 160, 80, 100, 25 };

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

			// Draw restart button
			if (GuiButton(buttonObject, buttonText.c_str()))
				system(argv[0]);

			// End drawing
			EndDrawing();
			#pragma endregion
		}

        CloseWindow(); // Program end

		return 0;
	}
}