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

namespace SettingsWindow
{
	inline static int SettingsWindowFunction()
	{
		// Initialization
		// Screen settings
		const int screenWidth = 400;
		const int screenHeight = 350;

		while (!WindowShouldClose()) // Detect window close button or ESC key
		{
			// Window init
			SetWindowSize(screenWidth, screenHeight);

			#pragma region Objects draw
            BeginDrawing();

            ClearBackground(RAYWHITE);

            // Settings label
            DrawText("Settings", 160, 10, 20, DARKGRAY);

			// End drawing
			EndDrawing();
			#pragma endregion
		}

		return 0;
	}
}