#ifndef INPUT_BOX_HPP
#define INPUT_BOX_HPP

#include <string>
#include "raylib.h"
#include "definitions.hpp"

typedef struct InputBoxStyle {
	Color 			baseBackgroundColor;
	Color 			hoverBackgroundColor;
	Color 			baseOutlineColor;
	Color 			hoverOutlineColor;
	Color 			baseTextColor;
	Color 			hoverTextColor;
	float 			roundness;
	float       outlineThickness;
	bool        editMode;
	int   			fontSize;
	std::string text;
} InputBoxStyle;

class InputBox {
public:
	InputBox(Rectangle bounds, InputBoxStyle style) : m_Bounds(bounds), m_Style(style) { }	

	bool UpdateAndRender();

private:
	Rectangle     m_Bounds;
	InputBoxStyle m_Style;
};

#endif /* INPUT_BOX_HPP */
