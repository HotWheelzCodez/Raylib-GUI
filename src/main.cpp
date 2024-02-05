#include "../include/raylib.h"
#include "../include/gui.hpp"
#include "../include/button.hpp"
#include "../include/inputBox.hpp"
#include "../include/scrollArea.hpp"

int main(void)
{
	int windowWidth  = 1000;
	int windowHeight = 800;

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
		2,
		false,
		10,
		"Username: ",
		"Your username...",
		""
	};

	Button b_Exit({ static_cast<float>(windowWidth)-30, 0, 30, 20 }, bs_Exit);

	InputBox ib_Test({ static_cast<float>(windowWidth>>1)-100, static_cast<float>(windowHeight>>1)-10, 200, 20 }, ibs_Test);

	while (!WindowShouldClose()) {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		windowWidth  = GetScreenWidth();
		windowHeight = GetScreenHeight();
		BeginDrawing();
			ClearBackground(BACKGROUND_COLOR);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				ib_Test.SetEditMode(false);
			}

			if (b_Exit.UpdateAndRender({ static_cast<float>(windowWidth)-30, 0, 30, 20 })) {
				break;
			}

			ib_Test.UpdateAndRender({ static_cast<float>(windowWidth>>1)-100, static_cast<float>(windowHeight>>1)-10, 200, 20 });
		EndDrawing();
	}

	CloseWindow();
}
