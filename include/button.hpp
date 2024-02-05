#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include "raylib.h"
#include "gui.hpp"

typedef struct ButtonStyle {
	Color       baseBackgroundColor;
	Color       hoverBackgroundColor;
	Color       baseTextColor;
	Color       hoverTextColor;
	float       roundness;
	int         fontSize;
	int         textAlignment;
	std::string text;
} ButtonStyle;

class Button {
public:
	Button(Rectangle bounds, ButtonStyle style) : m_Bounds(bounds), m_Style(style) { }

	bool UpdateAndRender(Rectangle bounds);

private:
	Rectangle   m_Bounds;
	ButtonStyle m_Style;

	void DrawButtonText(Color textColor);
};

#endif /* BUTTON_HPP */
