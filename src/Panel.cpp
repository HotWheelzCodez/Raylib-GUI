#include "../include/panel.hpp"

Panel::Panel(Rectangle bounds, PanelStyle style, bool resizeTop, bool resizeRight, bool resizeBottom, bool resizeLeft)
  : m_Bounds(bounds), m_Style(style), m_ResizeTop(resizeTop), m_ResizeRight(resizeRight), m_ResizeBottom(resizeBottom), m_ResizeLeft(resizeLeft) { }

// Getter methods
// --------------------------------------------------------
Rectangle Panel::getBounds(void) { return m_Bounds; }

// Setter methods
// ----------------------------------------------------------------
void Panel::setWidth(int width) { m_Bounds.width = width; }
void Panel::setHeight(int height) { m_Bounds.height = height; }
void Panel::setXPos(int x) { m_Bounds.x = x; }
void Panel::setYPos(int y) { m_Bounds.y = y; }

void Panel::resize(Rectangle bounds) { m_Bounds = bounds; }

void Panel::updateAndRender()
{
  // Draw the panel title area and the main panel area
  DrawRectangleRec(m_Bounds, m_Style.backgroundColor);
  DrawRectangle(m_Bounds.x, m_Bounds.y, m_Bounds.width, m_Style.titleHeight, m_Style.backgrondColorTitle);
 
  // Draw the text based off of the text alignment
  switch (m_Style.textAlignment) 
  {
    case TEXT_ALIGNMENT_LEFT:
      DrawText(m_Style.title.c_str(), m_Bounds.x+OFFSET_TEXT, m_Bounds.y+(m_Style.titleHeight>>1)-(m_Style.fontSize>>1), m_Style.fontSize, m_Style.titleColor);
      break;
    case TEXT_ALIGNMENT_CENTER:
      DrawText(m_Style.title.c_str(), m_Bounds.x+(static_cast<int>(m_Bounds.width)>>1)-(MeasureText(m_Style.title.c_str(), m_Style.fontSize)>>1),
        m_Bounds.y+(m_Style.titleHeight>>1)-(m_Style.fontSize>>1), m_Style.fontSize, m_Style.titleColor);
      break;
    case TEXT_ALIGNMENT_RIGHT:
      DrawText(m_Style.title.c_str(), m_Bounds.width-MeasureText(m_Style.title.c_str(), m_Style.fontSize)-OFFSET_TEXT,
        m_Bounds.y+(m_Style.titleHeight>>1)-(m_Style.fontSize>>1), m_Style.fontSize, m_Style.titleColor);
      break;
  }
}
