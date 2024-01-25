#include "../include/raylib.h"
#include "../include/definitions.hpp"
#include "../include/button.hpp"
#include "../include/inputBox.hpp"

int main(void)
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raylib GUI");
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
		2,
		false,
		10,
		"Input"
	};

	Button b_Exit((Rectangle){ WINDOW_WIDTH-30, 0, 30, 20 }, bs_Exit);

	InputBox ib_Test((Rectangle){ 100, 100, 200, 20 }, ibs_Test);

	while (!WindowShouldClose()) {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		BeginDrawing();
			ClearBackground(BACKGROUND_COLOR);
			DrawFPS(10, 10);

			if (b_Exit.UpdateAndRender()) {
				break;
			}

			if (ib_Test.UpdateAndRender()) {

			}

		EndDrawing();
	}

	CloseWindow();
}
