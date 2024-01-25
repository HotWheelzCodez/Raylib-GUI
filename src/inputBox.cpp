#include "../include/inputBox.hpp"

bool InputBox::UpdateAndRender()
{
	Color backgroundColor = m_Style.baseBackgroundColor;
	Color outlineColor    = m_Style.baseOutlineColor;
	Color textColor       = m_Style.baseTextColor;

	if (CheckCollisionPointRec(GetMousePosition(), m_Bounds)) {
		SetMouseCursor(MOUSE_CURSOR_IBEAM);

		backgroundColor = m_Style.hoverBackgroundColor;
		outlineColor    = m_Style.hoverOutlineColor;
		textColor       = m_Style.hoverTextColor;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			DrawRectangleRoundedLines(m_Bounds, m_Style.roundness, 100, m_Style.outlineThickness, outlineColor);
			DrawRectangleRounded((Rectangle){ m_Bounds.x+m_Style.outlineThickness, m_Bounds.y+m_Style.outlineThickness, m_Bounds.height-m_Style.outlineThickness,
				m_Bounds.width-m_Style.outlineThickness }, m_Style.roundness, 100, backgroundColor);
			DrawText(m_Style.text.c_str(), m_Bounds.x+5, m_Bounds.y+((int)(m_Bounds.height)>>1)-(m_Style.fontSize>>1), m_Style.fontSize, textColor);

			m_Style.editMode = !m_Style.editMode;
		}
	}

	DrawRectangleRoundedLines(m_Bounds, m_Style.roundness, 100, m_Style.outlineThickness, outlineColor);
	DrawRectangleRounded((Rectangle){ m_Bounds.x+m_Style.outlineThickness, m_Bounds.y+m_Style.outlineThickness, m_Bounds.height-m_Style.outlineThickness,
		m_Bounds.width-m_Style.outlineThickness }, m_Style.roundness, 100, backgroundColor);
	DrawText(m_Style.text.c_str(), m_Bounds.x+5, m_Bounds.y+((int)(m_Bounds.height)>>1)-(m_Style.fontSize>>1), m_Style.fontSize, textColor);

	return false;
}
