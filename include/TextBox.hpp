#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include <string>
#include <vector>
#include <algorithm>
#include "raylib.h"
#include "gui.hpp"

// Style structure
// ---------------------------------------------
typedef struct TextBoxStyle 
{
  Color backgroundColor;
  Color baseOutlineColor;
  Color selectedOutlineHoverColor;
  Color baseTextColor;
  Color selectedTextColor;
  float outlineThickness;
  float roundness;
  bool  editMode;
  int   textAlignment;
  int   fontSize;
  int   cursorWidth;
} TextBoxStyle;

// Text box class
// ----------------------------------------------------
class TextBox 
{
public:
  TextBox(Rectangle bounds, TextBoxStyle style);

  // Main methods
  // ----------------------------------
  void updateAndRender(void);    // Will draw the text box, get user input, and draw the text
  void resize(Rectangle bounds); // Will set the bounds of the text box to the given bounds;

  // Getter methods
  // -------------------------------
  std::string getText(void); // Will return the text inside the text box
 
  // Setter methods
  // -----------------------------------------
  void setText(std::string text);           // Will set the text of the text box
  void setTextAlignment(int textAlignment); // Will set the text alignment of text box
  void setTextSize(int textSize);           // Will set the font size of the text
  void setTextColor(Color textColor);       // Will set the color of the text

private:
  // Member variables
  // ----------------------
  Rectangle    m_Bounds;
  TextBoxStyle m_Style;
  std::string  m_Text;

  // Member methods
  // --------------
  int findLastIndexOf(char toFind);             // Will return the index of the first occurence of the given character going right to left
  void handleSpecialNumberKeys(int keyPressed); // Will add the corresponding 'special' number key to the text i.e: !@#$%^&*() - called only when shift is down
  void handleSpecialCharacters(int keyPressed); // Will add any other 'special' characters to the text i.e: ~_+{}|:"<>? - called only when shift is down
  void handleKeyPress(int keyPressed);          // Will update the cursor position depending on the pressed arrow key
  std::string getClippedText(void);             // Will return the portion of text that fits within the bounds
};

#endif /* TEXT_BOX_HPP */
