#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include "raylib.h"
#include "gui.hpp"

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

class Button 
{
public:
	Button(Rectangle bounds, ButtonStyle style);

	bool updateAndRender(Rectangle bounds);

private:
	Rectangle   m_Bounds;
	ButtonStyle m_Style;

	void drawButtonText(Color textColor);
};

#endif /* BUTTON_HPP */
