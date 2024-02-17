#include "../include/InputBox.hpp"

InputBox::InputBox(Rectangle bounds, InputBoxStyle style)
  : m_Bounds(bounds), m_Style(style) { }

void InputBox::resize(Rectangle bounds) { m_Bounds = bounds; }

std::string InputBox::getInput() { return m_Text; }
Rectangle InputBox::getBounds() { return m_Bounds; }

void InputBox::setEditMode(bool editMode) { m_Style.editMode = editMode; }

int InputBox::findLastIndexOf(char toFind)
{
	for (size_t i = m_Text.length()-1; i > 0; i--) 
  {
		if (m_Text[i] == toFind) return static_cast<int>(i);
	}

	return -1;
}

std::string InputBox::getClippedText(void)
{
	std::string clippedText;

	for (size_t i = m_Text.length()-1; i > 0; i--) 
  {
		if (MeasureText(clippedText.c_str(), m_Style.fontSize)+OFFSET_TEXT < m_Bounds.width-OFFSET_TEXT-OFFSET_CURSOR) 
			clippedText += m_Text[i];
		else 
			break;
	}

	std::reverse(clippedText.begin(), clippedText.end());
	return clippedText;
}

void InputBox::handleArrowKeys(int keyPressed)
{
  switch (keyPressed)
  {
    case KEY_ARROW_RIGHT: 
      if (m_CursorPosition < m_Text.length())
        m_CursorPosition++;
      break;
    case KEY_ARROW_LEFT: 
      if (m_CursorPosition > 0)
        m_CursorPosition--;
      break;
    case KEY_ARROW_DOWN: 
      break;  
    case KEY_ARROW_UP: 
      break;  
  }
}

void InputBox::handleSpecialNumberKeys(int keyPressed)
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

void InputBox::handleSpecialCharacters(int keyPressed)
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
      m_Text += '?';
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

void InputBox::handleKeyPress(int keyPressed)
{
  switch (keyPressed) 
  {
		case KEY_LEFT_CONTROL:
			break;
		case KEY_LEFT_SUPER: /* NOTE: KEY_LEFT_SUPER is the command key for mac */
			break;
		case KEY_V:
			if (IsKeyDown(KEY_LEFT_CONTROL || KEY_LEFT_SUPER)) /* NOTE: KEY_LEFT_SUPER is the command key for mac */
      { 
        m_Text += GetClipboardText();
				break;
			}
			break;
		case KEY_SPACE:
			m_Text += ' ' ;
			break;
		case KEY_LEFT_SHIFT: 
			break;
		case KEY_BACKSPACE:
			if (m_Text.length()) 
      {
				if (IsKeyDown(KEY_LEFT_CONTROL || KEY_LEFT_SUPER)) /* NOTE: KEY_LEFT_SUPER is the command key for mac */
        { 
					int indexOfLastSpace = findLastIndexOf(' ');
					if (indexOfLastSpace != -1) 
          {
						m_Text = m_Text.substr(0, indexOfLastSpace);
						break;
					}
					m_Text = "";
					break;
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
          break;
				} 
				m_Text += static_cast<char>(keyPressed);
			} else if (keyPressed >= 48 && keyPressed <= 57) 
      {
				if (IsKeyDown(KEY_LEFT_SHIFT)) 
        {
          handleSpecialNumberKeys(keyPressed);
          break;
				} 
				m_Text += static_cast<char>(keyPressed);
			} else 
      {
				if (IsKeyDown(KEY_LEFT_SHIFT)) 
        {
          handleSpecialCharacters(keyPressed);
          break;
				} 
			  m_Text += static_cast<char>(keyPressed);
	  }
	}
}

bool InputBox::updateAndRender(void)
{
	Color backgroundColor   = m_Style.baseBackgroundColor;
	Color outlineColor      = m_Style.baseOutlineColor;
	Color textColor         = m_Style.baseTextColor;

	std::string displayText = m_Text;
	if (m_Text.length() <= 0) 
		displayText = m_Style.placeholder;

	if (m_Style.editMode) 
  {
		backgroundColor = m_Style.hoverBackgroundColor;
		outlineColor    = m_Style.hoverOutlineColor;
		textColor       = m_Style.hoverTextColor;

		int keyPressed = GetKeyPressed();
    if (keyPressed)
	    handleKeyPress(keyPressed);

		if (MeasureText(m_Text.c_str(), m_Style.fontSize)+OFFSET_TEXT > m_Bounds.width-OFFSET_TEXT) 
			displayText = getClippedText();
		else 
			displayText = m_Text;

    // Draw the cursor
		DrawRectangleRec({ m_Bounds.x+OFFSET_TEXT+MeasureText(displayText.c_str(), m_Style.fontSize)+OFFSET_CURSOR, m_Bounds.y+OFFSET_CURSOR, 
      static_cast<float>(m_Style.cursorThickness), m_Bounds.height-OFFSET_CURSOR-m_Style.outlineThickness }, textColor);
	}

	if (MeasureText(m_Text.c_str(), m_Style.fontSize)+OFFSET_TEXT > m_Bounds.width-OFFSET_TEXT) 
		displayText = getClippedText();

	if (CheckCollisionPointRec(GetMousePosition(), m_Bounds)) 
  {
		SetMouseCursor(MOUSE_CURSOR_IBEAM);

		backgroundColor = m_Style.hoverBackgroundColor;
		outlineColor    = m_Style.hoverOutlineColor;
		textColor       = m_Style.hoverTextColor;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
      // Draw the outline, inner box, and the text
			DrawRectangleRoundedLines(m_Bounds, m_Style.roundness, SEGMENTS, m_Style.outlineThickness, outlineColor);
			DrawRectangleRounded({ m_Bounds.x+m_Style.outlineThickness, m_Bounds.y+m_Style.outlineThickness, m_Bounds.height-m_Style.outlineThickness,
				m_Bounds.width-m_Style.outlineThickness }, m_Style.roundness, SEGMENTS, backgroundColor);
			DrawText(displayText.c_str(), m_Bounds.x+OFFSET_TEXT, m_Bounds.y+(static_cast<int>(m_Bounds.height)>>1)-(m_Style.fontSize>>1), m_Style.fontSize, textColor);

			m_Style.editMode = !m_Style.editMode;
		}
	}

  // Draw the outline, inner box, and the text
	DrawRectangleRoundedLines(m_Bounds, m_Style.roundness, SEGMENTS, m_Style.outlineThickness, outlineColor);
	DrawRectangleRounded({ m_Bounds.x+m_Style.outlineThickness, m_Bounds.y+m_Style.outlineThickness, m_Bounds.height-m_Style.outlineThickness,
		m_Bounds.width-m_Style.outlineThickness }, m_Style.roundness, SEGMENTS, backgroundColor);
	DrawText(displayText.c_str(), m_Bounds.x+OFFSET_TEXT, m_Bounds.y+(static_cast<int>(m_Bounds.height)>>1)-(m_Style.fontSize>>1), m_Style.fontSize, textColor);

  // Draw the 'title' text, i.e the text to the left of the input box
	DrawText(m_Style.title.c_str(), m_Bounds.x-MeasureText(m_Style.title.c_str(), m_Style.fontSize)-OFFSET_TEXT, 
		m_Bounds.y+(static_cast<int>(m_Bounds.height)>>1)-static_cast<float>(m_Style.fontSize>>1), m_Style.fontSize, m_Style.hoverTextColor);	

  if (IsKeyPressed(KEY_ENTER)) 
    return true;
  else 
    return false;
}
