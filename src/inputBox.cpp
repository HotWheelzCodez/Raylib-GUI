#include "../include/inputBox.hpp"

InputBox::InputBox(Rectangle bounds, InputBoxStyle style)
  : m_Bounds(bounds), m_Style(style) { }

std::string InputBox::getInput() { return m_Style.text; }
Rectangle InputBox::getBounds() { return m_Bounds; }
void InputBox::setEditMode(bool editMode) { m_Style.editMode = editMode; }

int InputBox::findLastIndexOf(char toFind)
{
	for (size_t i = m_Style.text.length()-1; i > 0; i--) 
  {
		if (m_Style.text[i] == toFind) return static_cast<int>(i);
	}

	return -1;
}

std::string InputBox::getClippedText()
{
	std::string clippedText;

	for (size_t i = m_Style.text.length()-1; i > 0; i--) 
  {
		if (MeasureText(clippedText.c_str(), m_Style.fontSize)+OFFSET_TEXT < m_Bounds.width-OFFSET_TEXT-OFFSET_CURSOR) 
			clippedText += m_Style.text[i];
		else 
			break;
	}

	std::reverse(clippedText.begin(), clippedText.end());
	return clippedText;
}

void InputBox::handleSpecialNumberKey(int keyPressed)
{
  switch (keyPressed) 
  {
	  case KEY_ONE: 
			m_Style.text += '!';
			break;
		case KEY_TWO:
			m_Style.text += '@';
			break;
		case KEY_THREE:
			m_Style.text += '#';
		  break;
		case KEY_FOUR:
			m_Style.text += '$';
			break;
		case KEY_FIVE:
			m_Style.text += '%';
			break;
		case KEY_SIX:
			m_Style.text += '^';
		  break;
		case KEY_SEVEN:
			m_Style.text += '&';
			break;
		case KEY_EIGHT:
			m_Style.text += '*';
			break;
		case KEY_NINE:
			m_Style.text += '(';
			break;
		case KEY_ZERO:
			m_Style.text += ')';
		break;
	}
}

void InputBox::handleKeyPress(int keyPressed)
{
  switch (keyPressed) 
  {
		case KEY_LEFT_CONTROL:
			break;
		case KEY_LEFT_SUPER:
			break;
		case KEY_V:
			if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_LEFT_SUPER)) /* NOTE: KEY_LEFT_SUPER is the command key for mac */
      { 
				const char* clipboardText = GetClipboardText();
				m_Style.text += clipboardText;
				break;
			}
			m_Style.text += 'v';
			break;
		case KEY_SPACE:
			m_Style.text += ' ' ;
			break;
		case KEY_LEFT_SHIFT:
			break;
		case KEY_BACKSPACE:
			if (m_Style.text.length() > 0) 
      {
				if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_LEFT_SUPER)) /* NOTE: KEY_LEFT_SUPER is the command key for mac */
        { 
					int indexOfLastSpace = findLastIndexOf(' ');
					if (indexOfLastSpace != -1) 
          {
						m_Style.text = m_Style.text.substr(0, indexOfLastSpace);
						break;
					} else 
          {
						m_Style.text = "";
						break;
					}
				}
				m_Style.text.pop_back();
			}
			break;
		case KEY_NULL:
			break;
		default:
			if (keyPressed >= 65 && keyPressed <= 90) 
      {
				if (!IsKeyDown(KEY_LEFT_SHIFT)) 
        {
					keyPressed += 32;
					m_Style.text += static_cast<char>(keyPressed);
				} else 
        {
					m_Style.text += static_cast<char>(keyPressed);
				}
			} else if (keyPressed >= 48 && keyPressed <= 57) 
      {
				if (IsKeyDown(KEY_LEFT_SHIFT)) 
        {
          handleSpecialNumberKey(keyPressed);
				} else 
        {
					m_Style.text += static_cast<char>(keyPressed);
				}
			} else 
      {
				if (IsKeyDown(KEY_LEFT_SHIFT)) 
        {
					switch (keyPressed) 
          {
						case KEY_MINUS:
							keyPressed = 95;
							break;
						case KEY_EQUAL:
							keyPressed = 43;
							break;
						case KEY_COMMA:
              keyPressed = 60;
							break;
						case KEY_PERIOD:
							keyPressed = 62;
							break;
						case KEY_SLASH:
							keyPressed = 63;
							break;
						case KEY_SEMICOLON:
              keyPressed = 58;
							break;
						case KEY_APOSTROPHE:
							keyPressed = 34;
							break;
						case KEY_BACKSLASH:
							keyPressed = 124;
							break;
						case KEY_LEFT_BRACKET:
							keyPressed = 123;
							break;
						case KEY_RIGHT_BRACKET:
							keyPressed = 125;
							break;
						case KEY_GRAVE:
							keyPressed = 126;
							break;
					}
				}
			m_Style.text += static_cast<char>(keyPressed);
	  }
	}
}

bool InputBox::updateAndRender(Rectangle bounds)
{
	m_Bounds = bounds;

	Color backgroundColor   = m_Style.baseBackgroundColor;
	Color outlineColor      = m_Style.baseOutlineColor;
	Color textColor         = m_Style.baseTextColor;

	std::string displayText = m_Style.text;
	if (m_Style.text.length() <= 0) 
		displayText = m_Style.placeholder;

	if (m_Style.editMode) 
  {
		backgroundColor = m_Style.hoverBackgroundColor;
		outlineColor    = m_Style.hoverOutlineColor;
		textColor       = m_Style.hoverTextColor;

		int keyPressed = GetKeyPressed();
	  handleKeyPress(keyPressed);

		if (MeasureText(m_Style.text.c_str(), m_Style.fontSize)+OFFSET_TEXT > m_Bounds.width-OFFSET_TEXT) 
			displayText = getClippedText();
		else 
			displayText = m_Style.text;

		DrawRectangleRec({ m_Bounds.x+OFFSET_TEXT+MeasureText(displayText.c_str(), m_Style.fontSize)+OFFSET_CURSOR, m_Bounds.y+OFFSET_CURSOR, 2,
			m_Bounds.height-OFFSET_CURSOR-m_Style.outlineThickness }, textColor);
	}

	if (MeasureText(m_Style.text.c_str(), m_Style.fontSize)+OFFSET_TEXT > m_Bounds.width-OFFSET_TEXT) 
		displayText = getClippedText();

	/* TODO: Change display format to show the outline with the 'Input' text overlaping the top part of the outline - thus clearing the input field */
	if (CheckCollisionPointRec(GetMousePosition(), m_Bounds)) 
  {
		SetMouseCursor(MOUSE_CURSOR_IBEAM);

		backgroundColor = m_Style.hoverBackgroundColor;
		outlineColor    = m_Style.hoverOutlineColor;
		textColor       = m_Style.hoverTextColor;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
			DrawRectangleRoundedLines(m_Bounds, m_Style.roundness, 100, m_Style.outlineThickness, outlineColor);
			DrawRectangleRounded({ m_Bounds.x+m_Style.outlineThickness, m_Bounds.y+m_Style.outlineThickness, m_Bounds.height-m_Style.outlineThickness,
				m_Bounds.width-m_Style.outlineThickness }, m_Style.roundness, 100, backgroundColor);
			DrawText(displayText.c_str(), m_Bounds.x+5, m_Bounds.y+(static_cast<int>(m_Bounds.height)>>1)-(m_Style.fontSize>>1), m_Style.fontSize, textColor);

			m_Style.editMode = !m_Style.editMode;
		}
	}

	DrawRectangleRoundedLines(m_Bounds, m_Style.roundness, 100, m_Style.outlineThickness, outlineColor);
	DrawRectangleRounded({ m_Bounds.x+m_Style.outlineThickness, m_Bounds.y+m_Style.outlineThickness, m_Bounds.height-m_Style.outlineThickness,
		m_Bounds.width-m_Style.outlineThickness }, m_Style.roundness, 100, backgroundColor);
	DrawText(displayText.c_str(), m_Bounds.x+5, m_Bounds.y+(static_cast<int>(m_Bounds.height)>>1)-(m_Style.fontSize>>1), m_Style.fontSize, textColor);

	DrawText(m_Style.title.c_str(), m_Bounds.x-MeasureText(m_Style.title.c_str(), m_Style.fontSize)-OFFSET_TEXT, 
		m_Bounds.y+(static_cast<int>(m_Bounds.height)>>1)-static_cast<float>(m_Style.fontSize>>1), m_Style.fontSize, m_Style.hoverTextColor);	

  if (IsKeyPressed(KEY_ENTER)) 
    return true;
  else 
    return false;
}
