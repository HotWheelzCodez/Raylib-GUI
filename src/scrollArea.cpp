#include "../include/scrollArea.hpp"

void ScrollArea::UpdateAndRender(Rectangle bounds) 
{
	m_Bounds = bounds;

	DrawRectangleRec(m_Bounds, m_Style.backgroundColor);
	DrawRectangle(m_Bounds.x, m_Bounds.y, m_Bounds.width, m_Style.titleHeight, m_Style.titleBackgroundColor);

	switch (m_Style.textAlignment) {
		case TEXT_ALIGNMENT_LEFT:
			DrawText(m_Style.title.c_str(), m_Bounds.x+OFFSET_TEXT, m_Bounds.y+(m_Style.titleHeight>>1)-(m_Style.fontSize>>1), m_Style.fontSize, m_Style.titleColor);
			break;
		case TEXT_ALIGNMENT_CENTER:
			DrawText(m_Style.title.c_str(), m_Bounds.x+(static_cast<int>(m_Bounds.width)>>1)-(MeasureText(m_Style.title.c_str(), m_Style.fontSize)>>1), 
				m_Bounds.y+(m_Style.titleHeight>>1)-(m_Style.fontSize>>1), m_Style.fontSize, m_Style.titleColor);
			break;
		case TEXT_ALIGNMENT_RIGHT:
			DrawText(m_Style.title.c_str(), m_Bounds.x+m_Bounds.width-MeasureText(m_Style.title.c_str(), m_Style.fontSize)-OFFSET_TEXT,
				m_Bounds.y+(m_Style.titleHeight>>1)-(m_Style.fontSize>>1), m_Style.fontSize, m_Style.titleColor);
			break;
	}
}
