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
	bool updateAndRender(void); // Get the input, draw the box and input text, return true if the user hit enter, else false

  // Setter methods
  // -------------------------------------
	void setEditMode(bool editMode);

  // Getter methods
  // --------------------------
	std::string getInput(void);
  Rectangle getBounds(void);

private:
  // Member variables
  // ----------------------
  int           m_CursorPosition;
	Rectangle     m_Bounds;
  std::string   m_Text;
	InputBoxStyle m_Style;

  // Member methods
  // ---------------------------------------------
	int findLastIndexOf(char toFind);
  void handleKeyPress(int keyPressed);
  void handleSpecialNumberKeys(int keyPressed);
  void handleSpecialCharacters(int keyPressed);
  void handleArrowKeys(int keyPressed);
	std::string getClippedText(void);
};

#endif /* INPUT_BOX_HPP */
