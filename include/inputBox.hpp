#ifndef INPUT_BOX_HPP
#define INPUT_BOX_HPP

#include <string>
#include "raylib.h"
#include "gui.hpp"

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
	std::string title;
	std::string placeholder;
	std::string text;
} InputBoxStyle;

class InputBox 
{
public:
	InputBox(Rectangle bounds, InputBoxStyle style);

	bool updateAndRender(Rectangle bounds);
	void setEditMode(bool editMode);
	std::string getInput(void);
  Rectangle getBounds(void);

private:
	Rectangle     m_Bounds;
	InputBoxStyle m_Style;

	int findLastIndexOf(char toFind);
  void handleKeyPress(int keyPressed);
  void handleSpecialNumberKey(int keyPressed);
	std::string getClippedText(void);
};

#endif /* INPUT_BOX_HPP */
