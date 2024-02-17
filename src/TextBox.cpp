#include "../include/TextBox.hpp"
#include <iostream>

TextBox::TextBox(Rectangle bounds, TextBoxStyle style)
  : m_Bounds(bounds), m_Style(style) { }

void TextBox::resize(Rectangle bounds) { m_Bounds = bounds; }

void TextBox::setText(std::string text) 
{
  m_Text = text;
  std::string temp;

  for (size_t i = 0; i < m_Text.length(); i++)
  {
    temp += m_Text[i];
    if (MeasureText(temp.c_str(), m_Style.fontSize) >= m_Bounds.width-OFFSET_TEXT-(OFFSET_TEXT<<1)-m_Style.fontSize)
    {
      m_Text.insert(i, "\n");
      temp = "";
    }
  }
}

void TextBox::setText(char character)
{
  m_Text = "";
  m_Text += character;
}

int TextBox::findLastIndexOf(char toFind)
{
  for (size_t i = m_Text.length()-1; i > 0; i--)
  {
    if (m_Text[i] == toFind) return static_cast<int>(i);
  }

  return -1;
}

std::string TextBox::getClippedText(void)
{
  return m_Text;
}

void TextBox::handleSpecialNumberKeys(int keyPressed)
{
  switch (keyPressed) 
  {
	  case KEY_ONE: 
			m_Text += '!';
			break;
		case KEY_TWO:
			m_Text += '@';
			break;
		case KEY_THREE:
			m_Text += '#';
		  break;
		case KEY_FOUR:
			m_Text += '$';
			break;
		case KEY_FIVE:
			m_Text += '%';
			break;
		case KEY_SIX:
			m_Text += '^';
		  break;
		case KEY_SEVEN:
			m_Text += '&';
			break;
		case KEY_EIGHT:
			m_Text += '*';
			break;
		case KEY_NINE:
			m_Text += '(';
			break;
		case KEY_ZERO:
			m_Text += ')';
		break;
	}
}

void TextBox::handleSpecialCharacters(int keyPressed)
{
  switch (keyPressed) 
  {
		case KEY_MINUS:
			m_Text += '_';
			break;
		case KEY_EQUAL:
			m_Text += '+';
			break;
		case KEY_COMMA:
      m_Text += '<';
			break;
		case KEY_PERIOD:
      m_Text += '>' ;
			break;
		case KEY_SLASH:
      m_Text += '>';
			break;
		case KEY_SEMICOLON:
      m_Text += ':';
			break;
		case KEY_APOSTROPHE:
      m_Text += '"';
			break;
		case KEY_BACKSLASH:
      m_Text += '|';
			break;
		case KEY_LEFT_BRACKET:
      m_Text += '{';
			break;
		case KEY_RIGHT_BRACKET:
      m_Text += '}';
			break;
		case KEY_GRAVE:
      m_Text += '~';
			break;
	}
}

void TextBox::handleKeyPress(int keyPressed)
{
  switch (keyPressed)
  {
    case KEY_LEFT_CONTROL:
      break;
    case KEY_LEFT_SUPER: /* NOTE: KEY_LEFT_SUPER is the command key for mac */
      break;
    case KEY_V:
      if (IsKeyDown(KEY_LEFT_CONTROL || KEY_LEFT_SUPER))
      {
        m_Text += GetClipboardText();
      } else
      {
        m_Text += 'v'; 
      }
      break;
    case KEY_SPACE:
      m_Text += ' ';
      break;
    case KEY_LEFT_SHIFT || KEY_RIGHT_SHIFT: 
      break;
    case KEY_BACKSPACE:
      if (m_Text.length())
      {
        if (IsKeyDown(KEY_LEFT_CONTROL || KEY_LEFT_SUPER))
        {
          int indexOfLastSpace = findLastIndexOf(' ');
          if (indexOfLastSpace != -1)
          {
            m_Text = m_Text.substr(0, indexOfLastSpace);
          } else 
          {
            m_Text = "";
          }
        }
        m_Text.pop_back();
      }
      break;
    default: 
      // Upercase ascii values
      if (keyPressed >= 65 && keyPressed <= 90) 
      {
        if (!IsKeyDown(KEY_LEFT_SHIFT))
        {
          keyPressed += 32; // Lowercase the key by shifting the ascii value
          m_Text += static_cast<char>(keyPressed);
        } else
        {
          m_Text += static_cast<char>(keyPressed);
        }
      } else if (keyPressed >= 48 && keyPressed <= 90)
      {
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
          handleSpecialNumberKeys(keyPressed); 
        } else
        {
          m_Text += static_cast<char>(keyPressed);
        }
        break;
      } else
      {
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
          handleSpecialCharacters(keyPressed);
        } else
        {
          m_Text += static_cast<char>(keyPressed);
        }
        break;
      }
  }
}

void TextBox::updateAndRender(void)
{
  Color outlineColor = m_Style.baseOutlineColor;
  Color textColor    = m_Style.baseTextColor;

  std::string displayText = getClippedText();

  if (CheckCollisionPointRec(GetMousePosition(), m_Bounds)) 
  {
    outlineColor = m_Style.selectedOutlineHoverColor;
    textColor    = m_Style.selectedTextColor;
    SetMouseCursor(MOUSE_CURSOR_IBEAM);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
      m_Style.editMode = !m_Style.editMode;
  }

  // Draw the outline and the inner box
  DrawRectangleRoundedLines(m_Bounds, m_Style.roundness, SEGMENTS, m_Style.outlineThickness, outlineColor);
  DrawRectangleRounded({ m_Bounds.x+OFFSET_TEXT, m_Bounds.y+OFFSET_TEXT, m_Bounds.width-(OFFSET_TEXT<<1), m_Bounds.height-(OFFSET_TEXT<<1) },
    m_Style.roundness, SEGMENTS, m_Style.backgroundColor);

  if (m_Style.editMode) 
  {
    outlineColor = m_Style.selectedOutlineHoverColor;
    textColor    = m_Style.selectedTextColor;

    int keyPressed = GetKeyPressed();
    if (keyPressed) 
      handleKeyPress(keyPressed);

    std::string line = "";

    if (m_Text.length())
    {
      for (size_t i = m_Text.length()-1; i > 0; i--) 
      {
        if (m_Text[i] == '\n')
          break;

        line += m_Text[i];
      }

      if (MeasureText(line.c_str(), m_Style.fontSize) >= m_Bounds.width-OFFSET_TEXT-(OFFSET_TEXT<<1)-m_Style.fontSize)
        m_Text += '\n';
    }

    displayText = getClippedText();

    // Calculate cursor position
    int height = 0;
    int width  = 0; 

    if (displayText.length())
    {
      for (size_t i = 0; i < displayText.length()-1; i++)
      {
        if (displayText[i] == '\n')
          height++;
      }
      height *= m_Style.fontSize;

      line = "";
      for (int i = displayText.length()-1; i >= 0; i--) 
      {
        if (displayText[i] == '\n')
          break;
  
        line += displayText[i];
      }

      width = MeasureText(line.c_str(), m_Style.fontSize);
    }
   
    // Draw the cursor
    DrawRectangleRounded({ m_Bounds.x+(OFFSET_TEXT<<1)+width, m_Bounds.y+OFFSET_TEXT+m_Style.fontSize+height-(m_Style.fontSize>>1),
      static_cast<float>(m_Style.cursorWidth), static_cast<float>(m_Style.fontSize) }, m_Style.roundness, SEGMENTS, textColor);
  }

  displayText = getClippedText();

  switch (m_Style.textAlignment) 
  {
    case TEXT_ALIGNMENT_LEFT:
      DrawText(displayText.c_str(), m_Bounds.x+(OFFSET_TEXT<<1), m_Bounds.y+OFFSET_TEXT+m_Style.fontSize, m_Style.fontSize, textColor);
      break;
    case TEXT_ALIGNMENT_CENTER:
      break;
    case TEXT_ALIGNMENT_RIGHT:
      break;
  }
}
