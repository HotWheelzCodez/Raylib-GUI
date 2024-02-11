#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include <string>
#include "raylib.h"
#include "gui.hpp"

typedef struct TextBoxStyle 
{
  Color       backgroundColor;
  Color       baseOutlineColor;
  Color       selectedOutlineHoverColor;
  Color       baseTextColor;
  Color       selectedTextColor;
  int         outlineThickness;
  int         roundness;
  int         textAlignment;
  int         fontSize;
  std::string text;
} TextBoxStyle;

class TextBox 
{
public:
  TextBox(Rectangle bounds, TextBoxStyle style);

  void updateAndRender(void);

  std::string getText(void);
  
  void setTextAlignment(int textAlignment);
  void setTextSize(int textSize);
  void setTextColor(Color textColor);

private:
  Rectangle    m_Bounds;
  TextBoxStyle m_Style;
};

#endif /* TEXT_BOX_HPP */
