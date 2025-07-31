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

// Project files
#include "../Json/Json.h"

namespace SettingsWindow
{
	inline static int SettingsWindowFunction()
	{
		// Initialization
		// Screen settings
		const int screenWidth = 400;
		const int screenHeight = 350;

		// Show FPS
		bool showFPSCheckboxIsChecked;
		Rectangle showFPSCheckboxRect = { 10, 50, 20, 20 };
		std::string showFPSCheckboxText = "Show FPS on screen";

		// Apply button settings
		std::string applyButtonText = "Apply";
		Rectangle applyButtonObject = { 140, 220, 150, 35 };

		// Restart button settings
		std::string restartButtonText = "Restart";
		Rectangle restartButtonObject = { 140, 260, 150, 35 };

		// Exit button settings
		std::string exitButtonText = "Exit";
		Rectangle exitButtonObject = { 140, 300, 150, 35 };

		// Instances of classes
		JsonLogic::Json* json = new JsonLogic::Json();

		// Work with json
		nlohmann::json jsonTemp = json->ReadFromFile();

		while (!WindowShouldClose()) // Detect window close button or ESC key
		{
			// Window init
			SetWindowSize(screenWidth, screenHeight);

			#pragma region Update settings
			// Show FPS
			if (jsonTemp["ShowFPSInGame"].get<std::string>() == "TRUE") { showFPSCheckboxIsChecked == true; }
			if (jsonTemp["ShowFPSInGame"].get<std::string>() == "FALSE") { showFPSCheckboxIsChecked == false; }
			#pragma endregion

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
				if (showFPSCheckboxIsChecked) { jsonTemp["ShowFPSInGame"] = "TRUE"; }
				if (!showFPSCheckboxIsChecked) { jsonTemp["ShowFPSInGame"] = "FALSE"; }

				// Write new settings to json
				json->WriteToFromFile(jsonTemp);
			}

			// Restart button
			if (GuiButton(restartButtonObject, restartButtonText.c_str()))
			{
				return 1;
			}

			// Exit button
			if (GuiButton(exitButtonObject, exitButtonText.c_str()))
			{
				exit(1);
			}
			#pragma endregion

			// End drawing
			EndDrawing();
			#pragma endregion
		}

		return 0;
	}
}