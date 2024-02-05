#ifndef SCROLL_AREA_HPP
#define SCROLL_AREA_HPP

#include <string>
#include "raylib.h"
#include "gui.hpp"

typedef struct ScrollAreaStyle {
	Color 			backgroundColor;
	Color       titleBackgroundColor;
	Color       titleColor;
	int         titleHeight;
	int         itemAlignment;
	int         fontSize;
	int         textAlignment;
	std::string title;  
} ScrollAreaStyle;

class ScrollArea {
public:
	ScrollArea(Rectangle bounds, ScrollAreaStyle style) : m_Bounds(bounds), m_Style(style) { }

	void UpdateAndRender(Rectangle bounds);

private:
	Rectangle 			m_Bounds;
	ScrollAreaStyle m_Style;
};

#endif /* SCROLL_AREA_HPP */
