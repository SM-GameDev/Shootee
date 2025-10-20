#include "raylib.h"
#include "screen.h"
#include "level.h"
#include "entity.h"
#include "functions.h"
#include "mouse.h"
#include "sounds.h"
#include <iostream>

int main(void) {
    const int screenWidth = 640;
    const int screenHeight = 480;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Shootee");
	InitAudioDevice();

	Level currLevel = Level("levels/level_1.lvl");
	Screen mainScreen = Screen(640, 480);
	mouse = Mouse(&mainScreen, 0.1f);
	loadSounds();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

		//Mouse Control
		if (IsCursorOnScreen()) {
			HideCursor();
		} else {
			ShowCursor();
		}

		//Logic
		mouse.update();
		currLevel.update();

		//Drawing
        BeginDrawing();

			ClearBackground(BLACK);
	
			mainScreen.beginDrawing();

				ClearBackground(BLACK);
				currLevel.draw();
				mouse.draw();
				//DrawRectangleRec(recFromCenter(GetMouseX(), GetMouseY(), 40, 40), RED);

			mainScreen.endDrawing();

			//Render screen to window
			//DrawTexture(mainScreen.texture.texture, 0, 0, WHITE);
			mainScreen.renderTo(Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, CENTER);

		EndDrawing();
		std::cout << std::flush;
    }

    // De-Initialization
	unloadSounds();
	CloseAudioDevice();
    CloseWindow();
    return 0;
}
