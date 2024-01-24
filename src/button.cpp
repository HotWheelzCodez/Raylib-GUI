#include "../include/button.hpp"

void Button::DrawButtonText(Color textColor)
{
	switch (m_Style.textAlignment) {
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

bool Button::UpdateAndRender()
{
	Color backgroundColor = m_Style.baseBackgroundColor;
	Color textColor       = m_Style.baseTextColor;

	if (CheckCollisionPointRec(GetMousePosition(), m_Bounds)) {
		backgroundColor = m_Style.hoverBackgroundColor;
		textColor       = m_Style.hoverTextColor;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			DrawRectangleRounded(m_Bounds, m_Style.roundness, 100, backgroundColor);
			DrawButtonText(textColor);			

			return true;
		}
	}

	DrawRectangleRounded(m_Bounds, m_Style.roundness, 100, backgroundColor);
	DrawButtonText(textColor);	

	return false;
}
