#include "../include/textBox.hpp"

TextBox::TextBox(Rectangle bounds, TextBoxStyle style)
  : m_Bounds(bounds), m_Style(style) { }

void TextBox::updateAndRender(void)
{
  Color outlineColor    = m_Style.baseOutlineColor;
  Color backgroundColor = m_Style.backgroundColor;

  DrawRectangleRoundedLines(m_Bounds, m_Style.roundness, SEGMENTS, m_Style.outlineThickness, outlineColor);
}
