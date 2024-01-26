#ifndef INPUT_BOX_HPP
#define INPUT_BOX_HPP

#include <string>
#include <algorithm>
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

	void UpdateAndRender();
	std::string GetInput();

private:
	Rectangle     m_Bounds;
	InputBoxStyle m_Style;

	std::string GetClippedText();
};

#endif /* INPUT_BOX_HPP */
