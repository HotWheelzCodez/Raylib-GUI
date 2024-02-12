#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include <string>
#include <vector>
#include "raylib.h"
#include "gui.hpp"

// Style structure
// ---------------------------------------------
typedef struct TextBoxStyle 
{
  Color       backgroundColor;
  Color       baseOutlineColor;
  Color       selectedOutlineHoverColor;
  Color       baseTextColor;
  Color       selectedTextColor;
  float       outlineThickness;
  float       roundness;
  bool        editMode;
  int         textAlignment;
  int         fontSize;
} TextBoxStyle;

// Text box class
// ----------------------------------------------------
class TextBox 
{
public:
  TextBox(Rectangle bounds, TextBoxStyle style);

  // Main public methods
  // ----------------------------------
  void updateAndRender(void);

  // Getter methods
  // -------------------------------
  std::string getText(void);
 
  // Setter methods
  // -----------------------------------------
  void setText(std::string text);
  void setTextAlignment(int textAlignment);
  void setTextSize(int textSize);
  void setTextColor(Color textColor);

private:
  // Member variables
  // ----------------------
  Rectangle    m_Bounds;
  TextBoxStyle m_Style;
  std::string  m_Text;
};

#endif /* TEXT_BOX_HPP */
