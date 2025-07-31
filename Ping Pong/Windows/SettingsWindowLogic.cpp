// Standart libraries
#include <string>
#include <iostream>

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

		// Show FPS
		bool showFPSCheckboxIsChecked = false;
		Rectangle showFPSCheckboxRect = { 10, 50, 20, 20 };
		std::string showFPSCheckboxText = "Show FPS on screen";

		// Apply button settings
		std::string applyButtonText = "Apply";
		Rectangle applyButtonObject = { 140, 300, 150, 35 };

		while (!WindowShouldClose()) // Detect window close button or ESC key
		{
			// Window init
			SetWindowSize(screenWidth, screenHeight);

			#pragma region Objects draw
            BeginDrawing();

            ClearBackground(RAYWHITE);

            // Settings label
            DrawText("Settings", 160, 10, 20, DARKGRAY);

			#pragma region Settings
			// Show FPS settings
			GuiCheckBox(showFPSCheckboxRect, showFPSCheckboxText.c_str(), &showFPSCheckboxIsChecked);
			#pragma endregion

			#pragma region Buttons
			// Apply button
			if (GuiButton(applyButtonObject, applyButtonText.c_str()))
			{
				if (showFPSCheckboxIsChecked)
					DrawText("GOIDA", 160, 10, 20, DARKGRAY);
			}
			#pragma endregion

			// End drawing
			EndDrawing();
			#pragma endregion
		}

		return 0;
	}
}