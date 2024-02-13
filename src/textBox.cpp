#include "../include/textBox.hpp"
#include <algorithm>
#include <iostream>

TextBox::TextBox(Rectangle bounds, TextBoxStyle style)
  : m_Bounds(bounds), m_Style(style) { }

void TextBox::setText(std::string text) 
{
  m_Text = text;
  std::string temp;

  for (size_t i = 0; i < m_Text.length(); i++)
  {
    if (MeasureText(temp.c_str(), m_Style.fontSize) >= m_Bounds.width-OFFSET_TEXT-(OFFSET_TEXT<<1)-m_Style.fontSize)
    {
      m_Text.insert(i, "\n");
      temp = "";
    }
    temp += m_Text[i];
  }
}

void TextBox::updateAndRender(void)
{
  Color outlineColor = m_Style.baseOutlineColor;
  Color textColor    = m_Style.baseTextColor;

  // Check if mouse is hovering over the text box, and update properties
  if (CheckCollisionPointRec(GetMousePosition(), m_Bounds)) 
  {
    outlineColor = m_Style.selectedOutlineHoverColor;
    textColor    = m_Style.selectedTextColor;
    SetMouseCursor(MOUSE_CURSOR_IBEAM);

    // Check if the user clicked the text box
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
      m_Style.editMode = !m_Style.editMode;
  }

  // Draw the outline and the inner box
  DrawRectangleRoundedLines(m_Bounds, m_Style.roundness, SEGMENTS, m_Style.outlineThickness, outlineColor);
  DrawRectangleRounded({ m_Bounds.x+OFFSET_TEXT, m_Bounds.y+OFFSET_TEXT, m_Bounds.width-(OFFSET_TEXT<<1), m_Bounds.height-(OFFSET_TEXT<<1) },
    m_Style.roundness, SEGMENTS, m_Style.backgroundColor);

  // If the user is editing the text box
  if (m_Style.editMode) 
  {
    outlineColor = m_Style.selectedOutlineHoverColor;
    textColor    = m_Style.selectedTextColor;

    // Get the key, determine the key, add the char to the string
    int keyPressed = GetKeyPressed();
    if (keyPressed != 0) 
    {
      if (keyPressed == 257)
      {
        m_Text += '\n';
      } else if (keyPressed == 32)
      {
        m_Text += ' ';
      } else if (keyPressed == KEY_BACKSPACE)
      {
        if (m_Text[m_Text.length()-1] == '\n')
          m_Text = m_Text.substr(0, m_Text.length()-2);
        else 
          m_Text.pop_back();
      } else 
      {
        m_Text += static_cast<char>(keyPressed+32);
      }
    }

    // Check to see if you need to start a new line, i.e: if the text is at the ends of the bounds of the text box
    std::string line = "";
    for (size_t i = m_Text.length()-1; i > 0; i--) 
    {
      if (m_Text[i] == '\n')
        break;

      line += m_Text[i];
    }

    if (MeasureText(line.c_str(), m_Style.fontSize) >= m_Bounds.width-OFFSET_TEXT-(OFFSET_TEXT<<1)-m_Style.fontSize)
      m_Text += '\n';

    // Draw the cursor
    int height = 0;
    int width  = 0; 

    if (m_Text.length())
    {
      for (size_t i = 0; i < m_Text.length()-1; i++)
      {
        if (m_Text[i] == '\n')
          height++;
      }
      height *= m_Style.fontSize + (m_Style.fontSize>>1);

      line = "";
      for (size_t i = m_Text.length()-1; i >= 0; i--) 
      {
        if (m_Text[i] == '\n')
          break;
  
        line += m_Text[i];
      }

      width = MeasureText(line.c_str(), m_Style.fontSize);
    }
    
    DrawRectangleRounded({ m_Bounds.x+(OFFSET_TEXT<<1)+width, m_Bounds.y+OFFSET_TEXT+m_Style.fontSize+height-(m_Style.fontSize>>1),
      static_cast<float>(m_Style.cursorWidth), static_cast<float>(m_Style.fontSize<<1) }, m_Style.roundness, SEGMENTS, textColor);
  }

  // Draw the text based off of the text alignment type
  switch (m_Style.textAlignment) 
  {
    case TEXT_ALIGNMENT_LEFT:
      DrawText(m_Text.c_str(), m_Bounds.x+(OFFSET_TEXT<<1), m_Bounds.y+OFFSET_TEXT+m_Style.fontSize, m_Style.fontSize, textColor);
      break;
    case TEXT_ALIGNMENT_CENTER:
      break;
    case TEXT_ALIGNMENT_RIGHT:
      break;
  }

  
}
