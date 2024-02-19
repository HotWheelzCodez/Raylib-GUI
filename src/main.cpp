#include "../include/raylib.h"
#include "../include/gui.hpp"
#include "../include/Button.hpp"
#include "../include/InputBox.hpp"
#include "../include/Panel.hpp"
#include "../include/TextBox.hpp"

#define BACKGROUND_COLOR { 25, 25, 30, 255 }

int main(void)
{
  int windowWidth  = 1200;
  int windowHeight = 1000;

  ButtonStyle bs_Exit = {
    CLEAR,
    RED,
    WHITE,
    WHITE,
    0.0f,
    20,
    TEXT_ALIGNMENT_CENTER,
    "Exit"
  };

  ButtonStyle bs_Submit = {
    BLUE,
    DARKBLUE,
    BACKGROUND_COLOR,
    WHITE,
    0.5f,
    20,
    TEXT_ALIGNMENT_CENTER,
    "Submit"
  };

  InputBoxStyle ibs_Input = {
    CLEAR,
    CLEAR,
    BLUE,
    DARKBLUE,
    GRAY,
    WHITE,
    0.5f,
    0.2f,
    false,
    30,
    2,
    "Input: ",
    "Input..."
  };

  TextBoxStyle tbs_Output = {
    GRAY,
    BLUE,
    DARKBLUE,
    WHITE,
    WHITE,
    0.5f,
    0.2f,
    false,
    TEXT_ALIGNMENT_LEFT,
    40,
    2
  };

  int b_ExitWidth  = windowWidth/20;
  int b_ExitHeight = windowHeight/20;
  Button b_Exit({ static_cast<float>(windowWidth)-b_ExitWidth, 0, static_cast<float>(b_ExitWidth), static_cast<float>(b_ExitHeight) }, bs_Exit);

  int ib_InputWidth  = windowWidth/3;
  int ib_InputHeight = windowHeight/15;
  InputBox ib_Input({ static_cast<float>(windowWidth>>1)-(ib_InputWidth>>1), static_cast<float>(windowHeight)/10,
    static_cast<float>(ib_InputWidth), static_cast<float>(ib_InputHeight )}, ibs_Input);
             
  int b_SubmitWidth  = windowWidth/5;
  int b_SubmitHeight = windowHeight/15;
  Button b_Submit({ static_cast<float>(windowWidth>>1)+(ib_InputWidth>>1)+OFFSET_TEXT, static_cast<float>(windowHeight)/10,
    static_cast<float>(b_SubmitWidth), static_cast<float>(b_SubmitHeight) }, bs_Submit);

  int tb_OutputWidth  = windowWidth>>1;
  int tb_OutputHeight = windowHeight>>1;
  TextBox tb_Output({ static_cast<float>(windowWidth>>1)-(tb_OutputWidth>>1), static_cast<float>(windowHeight>>1)-(tb_OutputHeight>>1),
    static_cast<float>(tb_OutputWidth), static_cast<float>(tb_OutputHeight) }, tbs_Output);

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(windowWidth, windowHeight, "Raylib-GUI Test");
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);

    windowWidth  = GetScreenWidth();
    windowHeight = GetScreenHeight();

    b_ExitWidth  = windowWidth/20;
    b_ExitHeight = windowHeight/20;
    b_Exit.resize({ static_cast<float>(windowWidth)-b_ExitWidth, 0, static_cast<float>(b_ExitWidth), static_cast<float>(b_ExitHeight) });

    ib_InputWidth  = windowWidth/3;
    ib_InputHeight = windowHeight/15;
    ib_Input.resize({ static_cast<float>(windowWidth>>1)-(ib_InputWidth>>1), static_cast<float>(windowHeight)/10, static_cast<float>(ib_InputWidth),
      static_cast<float>(ib_InputHeight )});

    b_SubmitWidth  = windowHeight/5;
    b_SubmitHeight = windowHeight/15;
    b_Submit.resize({ static_cast<float>(windowWidth>>1)+(ib_InputWidth>>1)+OFFSET_TEXT, static_cast<float>(windowHeight)/10,
      static_cast<float>(b_SubmitWidth), static_cast<float>(b_SubmitHeight) });

    tb_OutputWidth  = windowWidth>>1;
    tb_OutputHeight = windowHeight>>1;
    tb_Output.resize({ static_cast<float>(windowWidth>>1)-(tb_OutputWidth>>1), static_cast<float>(windowHeight>>1)-(tb_OutputHeight>>1),
      static_cast<float>(tb_OutputWidth), static_cast<float>(tb_OutputHeight) });

    ib_Input.updateAndRender();

    tb_Output.updateAndRender();

    if (b_Submit.updateAndRender())
    {
      std::string text = ib_Input.getInput();
      if (text.length())
        tb_Output.setText(text[text.length()-1]);
    }

    if (b_Exit.updateAndRender()) 
      break;

    EndDrawing();
  }

  CloseWindow();
}
