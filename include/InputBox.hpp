#ifndef INPUT_BOX_HPP
#define INPUT_BOX_HPP

#include <string>
#include "raylib.h"
#include "gui.hpp"

// Style structure
// ------------------------------------
typedef struct InputBoxStyle 
{
	Color       baseBackgroundColor;
	Color       hoverBackgroundColor;
	Color       baseOutlineColor;
	Color       hoverOutlineColor;
	Color       baseTextColor;
	Color       hoverTextColor;
	float       roundness;
	float       outlineThickness;
	bool        editMode;
	int         fontSize;
  int         cursorThickness;
	std::string title;
	std::string placeholder;
} InputBoxStyle;

// Input box class
// ------------------------------------------------------
class InputBox 
{
public:
	InputBox(Rectangle bounds, InputBoxStyle style);

  // Main methods
  // -----------------------------------------
	bool updateAndRender(void);    // Get the input, draw the box and input text, return true if the user hit enter, else false
  void resize(Rectangle bounds); // Set the bounds of the input box to the given bounds

  // Setter methods
  // -------------------------------------
	void setEditMode(bool editMode); // Will set 'editMode' to the given boolean value

  // Getter methods
  // --------------------------
	std::string getInput(void); // Returns the current text inside of the input box
  Rectangle getBounds(void);  // Returns the Rectangle bounds of the input box

private:
  // Member variables
  // ----------------------
	Rectangle     m_Bounds;
	InputBoxStyle m_Style;
  std::string   m_Text;
  std::string   m_DisplayText;
  int           m_CursorPosition;
  int           m_CursorOffset;

  // Member methods
  // ---------------------------------------------
	int findLastIndexOf(char toFind);             // Will return the index of the first occurence of the given character going right to left
  void handleKeyPress(int keyPressed);          // Will add the given key to the text, will work with all 'special' keys
  void handleSpecialNumberKeys(int keyPressed); // Will add the corresponding 'special' number key to the text i.e: !@#$%^&*() - called only when shift is down
  void handleSpecialCharacters(int keyPressed); // Will add any other 'special' characters to the text i.e: ~_+{}|:"<>? - called only when shift is down
  void handleArrowKeys(int keyPressed);         // Will update the cursor position depending on the pressed arrow key
	std::string getClippedText(void);             // Will return the portion of text that fits within the bounds
};

#endif /* INPUT_BOX_HPP */
