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

  ButtonStyle bs_Submit = {
    BLUE,
    DARKBLUE,
    BACKGROUND_COLOR,
    WHITE,
    0.5f,
    10,
    TEXT_ALIGNMENT_CENTER,
    "Submit"
  };

  InputBoxStyle ibs_Input = {
    BACKGROUND_COLOR,
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
    WHITE,
    WHITE,
    0.2f,
    0.25f,
    false,
    TEXT_ALIGNMENT_LEFT,
    10,
    1
  };

	Button b_Exit({ static_cast<float>(windowWidth)-30, 0, 30, 20 }, bs_Exit);
  Button b_Submit({ static_cast<float>(windowWidth>>1)-100+200+OFFSET_TEXT, (static_cast<float>(windowHeight)/10)-10+5, 40, 10 }, bs_Submit);

  InputBox ib_Input({ static_cast<float>(windowWidth>>1)-100, (static_cast<float>(windowHeight)/10)-10, 200, 20 }, ibs_Input);
 
  TextBox tb_Output({ static_cast<float>(windowWidth>>1)-200, static_cast<float>(windowHeight>>1)-100, 400, 200 }, tbs_Output);

	while (!WindowShouldClose()) {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		windowWidth  = GetScreenWidth();
		windowHeight = GetScreenHeight();
		BeginDrawing();
			ClearBackground(BACKGROUND_COLOR);

      ib_Input.updateAndRender();
      tb_Output.updateAndRender();

      if (b_Submit.updateAndRender())
      {
        std::string text = ib_Input.getInput();
        std::string output = "";
        output += text[text.length()-1];
        tb_Output.setText(output);
      }

      if (b_Exit.updateAndRender()) {
				break;
			}

      b_Exit.resize({ static_cast<float>(windowWidth)-30, 0, 30, 20 });
      ib_Input.resize({ static_cast<float>(windowWidth>>1)-100, (static_cast<float>(windowHeight)/10)-10, 200, 20 });
      tb_Output.resize({ static_cast<float>(windowWidth>>1)-200, static_cast<float>(windowHeight>>1)-100, 400, 200 });

		EndDrawing();
	}

	CloseWindow();
}
