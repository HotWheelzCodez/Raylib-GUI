#include "../include/raylib.h"
#include "../include/gui.hpp"
#include "../include/button.hpp"
#include "../include/inputBox.hpp"
#include "../include/panel.hpp"
#include "../include/textBox.hpp"

#define BACKGROUND_COLOR { 25, 25, 30, 255 }

int main(void)
{
	int windowWidth  = 800;
	int windowHeight = 600;

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

  InputBoxStyle ibs_Input = {
    CLEAR,
    CLEAR,
    DARKBLUE,
    BLUE,
    GRAY,
    WHITE,
    0.5f,
    0.2f,
    false,
    10,
    1,
    "Input: ",
    "Input..."
  };

  TextBoxStyle tbs_Output = {
    GRAY,
    DARKBLUE,
    BLUE,
    GRAY,
    WHITE,
    0.2f,
    0.5f,
    false,
    TEXT_ALIGNMENT_LEFT,
    10,
    1
  };

	Button b_Exit({ static_cast<float>(windowWidth)-30, 0, 30, 20 }, bs_Exit);

  InputBox ib_Input({ static_cast<float>(windowWidth>>1)-100, (static_cast<float>(windowHeight)/10)-10, 200, 20 }, ibs_Input);

	while (!WindowShouldClose()) {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		windowWidth  = GetScreenWidth();
		windowHeight = GetScreenHeight();
		BeginDrawing();
			ClearBackground(BACKGROUND_COLOR);

      ib_Input.updateAndRender();

      if (b_Exit.updateAndRender()) {
				break;
			}

		EndDrawing();
	}

	CloseWindow();
}
