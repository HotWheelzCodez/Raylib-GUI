#include "../include/Button.hpp"

Button::Button(Rectangle bounds, ButtonStyle style)
  : m_Bounds(bounds), m_Style(style) { }

void Button::resize(Rectangle bounds) { m_Bounds = bounds; }

void Button::drawButtonText(Color textColor)
{
	switch (m_Style.textAlignment) 
  {
		case TEXT_ALIGNMENT_LEFT:
			DrawText(m_Style.text.c_str(), m_Bounds.x+5, m_Bounds.y+(static_cast<int>(m_Bounds.height)>>1)-(m_Style.fontSize>>1), m_Style.fontSize, textColor);
			break;
		case TEXT_ALIGNMENT_CENTER:
			DrawText(m_Style.text.c_str(), m_Bounds.x+(static_cast<int>(m_Bounds.width)>>1)-(MeasureText(m_Style.text.c_str(), m_Style.fontSize)>>1),
				m_Bounds.y+(static_cast<int>(m_Bounds.height)>>1)-(m_Style.fontSize>>1), m_Style.fontSize, textColor);
			break;
		case TEXT_ALIGNMENT_RIGHT:
			DrawText(m_Style.text.c_str(), m_Bounds.x+m_Bounds.width-MeasureText(m_Style.text.c_str(), m_Style.fontSize)-5,
				m_Bounds.y+(static_cast<int>(m_Bounds.height)>>1)-(m_Style.fontSize>>1), m_Style.fontSize, textColor);
			break;
	}
}

bool Button::updateAndRender(void)
{
	Color backgroundColor = m_Style.baseBackgroundColor;
	Color textColor       = m_Style.baseTextColor;

	if (CheckCollisionPointRec(GetMousePosition(), m_Bounds)) 
  {
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

		backgroundColor = m_Style.hoverBackgroundColor;
		textColor       = m_Style.hoverTextColor;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
			DrawRectangleRounded(m_Bounds, m_Style.roundness, 100, backgroundColor);
			drawButtonText(textColor);			

			return true;
		}
	}

	DrawRectangleRounded(m_Bounds, m_Style.roundness, 100, backgroundColor);
	drawButtonText(textColor);	

	return false;
}
