#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include "raylib.h"
#include "gui.hpp"

// Style structure
// -------------------------------------
typedef struct ButtonStyle 
{
	Color       baseBackgroundColor;
	Color       hoverBackgroundColor;
	Color       baseTextColor;
	Color       hoverTextColor;
	float       roundness;
	int         fontSize;
	int         textAlignment;
	std::string text;
} ButtonStyle;

// Button class
// ------------------------------------------------
class Button 
{
public:
	Button(Rectangle bounds, ButtonStyle style);

  // Main methods
  // ----------------------------------------
	bool updateAndRender(void);

private:
  // Member variables
  // -------------------
	Rectangle   m_Bounds;
	ButtonStyle m_Style;

  // Member methods
  // -------------------------------------
	void drawButtonText(Color textColor);
};

#endif /* BUTTON_HPP */
