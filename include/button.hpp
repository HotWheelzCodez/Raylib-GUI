#include <string>
#include "raylib.h"
#include "definitions.hpp"

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

	bool UpdateAndRender();

private:
	Rectangle   m_Bounds;
	ButtonStyle m_Style;

	void DrawButtonText(Color textColor);
};