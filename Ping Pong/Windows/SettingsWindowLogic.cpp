// Standart libraries
#include <string>
#include <format>
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

		// FPS Limiter
		int currentValueOfFPSLimiter = 0;
		std::string fpsLimiterText = "FPS limiter -> ";
		// Right
		std::string fpsLimiterLeftArrowText = "<";
		std::string fpsLimiterRightArrowText = ">";
		// Positions
		Rectangle fpsLimiterLeftButtonRect = { 310, 80, 30, 30 };
		Rectangle fpsLimiterRightButtonRect = { 350, 80, 30, 30 };

		// Apply button settings
		std::string applyButtonText = "Apply";
		Rectangle applyButtonObject = { 140, 220, 150, 35 };

		// Exit button settings
		std::string exitButtonText = "Exit";
		Rectangle exitButtonObject = { 140, 260, 150, 35 };

		// Instances of classes
		JsonLogic::Json* json = new JsonLogic::Json();

		// Work with json
		nlohmann::json jsonTemp = json->ReadFromFile();

		// Read values
		currentValueOfFPSLimiter = jsonTemp["FPSLimiter"].get<int>();

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

			// FPS Limiter
			fpsLimiterText = std::format("FPS limiter -> {}", currentValueOfFPSLimiter); // Read actual value

			DrawText(fpsLimiterText.c_str(), 35, 80, 30, DARKGRAY);

			if (GuiButton(fpsLimiterLeftButtonRect, fpsLimiterLeftArrowText.c_str()))
				if (currentValueOfFPSLimiter - 60 >= 60) { currentValueOfFPSLimiter -= 60; }

			if (GuiButton(fpsLimiterRightButtonRect, fpsLimiterRightArrowText.c_str()))
				if (currentValueOfFPSLimiter + 60 <= 240) { currentValueOfFPSLimiter += 60; }
			#pragma endregion

			#pragma region Buttons
			// Apply button
			if (GuiButton(applyButtonObject, applyButtonText.c_str()))
			{
				// Show FPS
				if (showFPSCheckboxIsChecked) { jsonTemp["ShowFPSInGame"] = "TRUE"; }
				if (!showFPSCheckboxIsChecked) { jsonTemp["ShowFPSInGame"] = "FALSE"; }

				// FPS Limiter
				jsonTemp["FPSLimiter"] = currentValueOfFPSLimiter;

				// Write new settings to json
				json->WriteToFromFile(jsonTemp);
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