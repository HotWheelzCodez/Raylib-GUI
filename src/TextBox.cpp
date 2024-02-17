#include "../include/TextBox.hpp"

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
  // Add the special character of the corresponding number character this only runs when the user is typing a number character and is holding down the shift-key
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
  // This only gets ran when the shift-key is being held down, thus these are the 'caps' versions of the keys
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
    // Don't do anything for control or command
    case KEY_LEFT_CONTROL:
      break;
    case KEY_LEFT_SUPER: /* NOTE: KEY_LEFT_SUPER is the command key for mac */
      break;
    case KEY_V:
      // Check to see if control or command is being pressed, that means we gotta paste
      if (IsKeyDown(KEY_LEFT_CONTROL || KEY_LEFT_SUPER))
      {
        m_Text += GetClipboardText();
      } else
      {
        m_Text += 'v'; // Just add the letter 'v' else
      }
      break;
    case KEY_SPACE:
      m_Text += ' ';
      break;
    case KEY_LEFT_SHIFT || KEY_RIGHT_SHIFT: // Ignore LEFT_SHIFT and RIGHT_SHIFT
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
        // Else just delete the last character
        m_Text.pop_back();
      }
      break;
    default: // If there is no 'special operation' then just process normal keyboard input
      // Normal characters  i.e no numbers or anything
      if (keyPressed >= 65 && keyPressed <= 90) 
      {
        if (!IsKeyDown(KEY_LEFT_SHIFT))
        {
          keyPressed += 32; // Lowercase the key by shifting the ascii value
          m_Text += static_cast<char>(keyPressed);
        } else
        {
          m_Text + static_cast<char>(keyPressed);
        }
      } else if (keyPressed >= 48 && keyPressed <= 90)
      {
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
          handleSpecialNumberKeys(keyPressed); // Add the corresponding special character keys for the numbers
        } else
        {
          m_Text += static_cast<char>(keyPressed);
        }
        break;
      } else
      {
        // Cases for all the other special characters
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
    if (keyPressed) 
      handleKeyPress(keyPressed);

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

    if (displayText.length())
    {
      for (size_t i = 0; i < displayText.length()-1; i++)
      {
        if (displayText[i] == '\n')
          height++;
      }
      height *= m_Style.fontSize + (m_Style.fontSize>>1);

      line = "";
      for (size_t i = displayText.length()-1; i >= 0; i--) 
      {
        if (displayText[i] == '\n')
          break;
  
        line += displayText[i];
      }

      width = MeasureText(line.c_str(), m_Style.fontSize);
    }
    
    DrawRectangleRounded({ m_Bounds.x+(OFFSET_TEXT<<1)+width, m_Bounds.y+OFFSET_TEXT+m_Style.fontSize+height-(m_Style.fontSize>>1),
      static_cast<float>(m_Style.cursorWidth), static_cast<float>(m_Style.fontSize<<1) }, m_Style.roundness, SEGMENTS, textColor);
  }

  displayText = getClippedText();

  // Draw the text based off of the text alignment type
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
