#include "../include/raylib.h"
#include "../include/gui.hpp"
#include "../include/button.hpp"
#include "../include/inputBox.hpp"
#include "../include/panel.hpp"

#define BACKGROUND_COLOR (Color){ 25, 25, 30, 255 }

int main(void)
{
	float windowWidth  = 1000.0;
	float windowHeight = 800.0;

	InitWindow(windowWidth, windowHeight, "Raylib GUI");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);

	ButtonStyle bs_Exit = {
		CLEAR,
		RED,
		WHITE,
		WHITE,
		0.0f,
		10,
		TEXT_ALIGNMENT_CENTER,
		"Exit"
	};

  InputBoxStyle ibs_Test = {
    CLEAR,
    CLEAR,
    BLUE,
    DARKBLUE,
    GRAY,
    WHITE,
    0.5f,
    0.5f,
    false,
    10,
    "Input: ",
    "Input...",
    ""
  };

	Button b_Exit((Rectangle){ static_cast<float>(windowWidth)-30, 0, 30, 20 }, bs_Exit);

  InputBox ib_Test((Rectangle){ 100, 100, 200, 20 }, ibs_Test);

	while (!WindowShouldClose()) {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		windowWidth  = GetScreenWidth();
		windowHeight = GetScreenHeight();
		BeginDrawing();
			ClearBackground(BACKGROUND_COLOR);

      ib_Test.updateAndRender((Rectangle){ 100, 100, 200, 20 });

      if (b_Exit.updateAndRender((Rectangle){ static_cast<float>(windowWidth)-30, 0, 30, 20 })) {
				break;
			}

		EndDrawing();
	}

	CloseWindow();
}
