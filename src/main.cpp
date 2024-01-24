#include "../include/raylib.h"
#include "../include/definitions.hpp"
#include "../include/button.hpp"

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

	Button b_Exit((Rectangle){ WINDOW_WIDTH-30, 0, 30, 20 }, bs_Exit);

	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(BACKGROUND_COLOR);

			if (b_Exit.UpdateAndRender()) {
				break;
			}

			DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();
}
