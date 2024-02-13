#include "../include/inputBox.hpp"

InputBox::InputBox(Rectangle bounds, InputBoxStyle style)
  : m_Bounds(bounds), m_Style(style) { }

// Getter methods
// ------------------------------------------------------
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

  // Get the most recent text that is within the bounds of the input box
	for (size_t i = m_Text.length()-1; i > 0; i--) 
  {
		if (MeasureText(clippedText.c_str(), m_Style.fontSize)+OFFSET_TEXT < m_Bounds.width-OFFSET_TEXT-OFFSET_CURSOR) 
			clippedText += m_Text[i];
		else 
			break;
	}

  // Reverse and return the text
	std::reverse(clippedText.begin(), clippedText.end());
	return clippedText;
}

void InputBox::handleArrowKeys(int keyPressed)
{
  switch (keyPressed)
  {
    case KEY_ARROW_RIGHT: // Right arrow key
      if (m_CursorPosition < m_Text.length())
        m_CursorPosition++;
      break;
    case KEY_ARROW_LEFT: // Left arrow key
      if (m_CursorPosition > 0)
        m_CursorPosition--;
      break;
    case KEY_ARROW_DOWN: // Down arrow key
      break;  // Down is unapplicable for input-box
    case KEY_ARROW_UP: // Up arrow key
      break;  // Up is unapplicable for input-box
  }
}

void InputBox::handleSpecialNumberKeys(int keyPressed)
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

void InputBox::handleSpecialCharacters(int keyPressed)
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

void InputBox::handleKeyPress(int keyPressed)
{
  switch (keyPressed) 
  {
    // Don't do anything if control or command is pressed
		case KEY_LEFT_CONTROL:
			break;
		case KEY_LEFT_SUPER: /* NOTE: KEY_LEFT_SUPER is the command key for mac */
			break;
		case KEY_V:
      // Check to see if control or command is held down, if so get the clipbard text and add the to the text
			if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_LEFT_SUPER)) /* NOTE: KEY_LEFT_SUPER is the command key for mac */
      { 
        m_Text += GetClipboardText();
				break;
			}
      // Else just add the character 'v'
			m_Text += 'v';
			break;
		case KEY_SPACE:
			m_Text += ' ' ;
			break;
		case KEY_LEFT_SHIFT: // Ignore if just left-shift is pressed
			break;
		case KEY_BACKSPACE:
			if (m_Text.length() > 0) 
      {
        // Check to see if the user wants to delete a word
				if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_LEFT_SUPER)) /* NOTE: KEY_LEFT_SUPER is the command key for mac */
        { 
          // Remove the last word of the text
					int indexOfLastSpace = findLastIndexOf(' ');
					if (indexOfLastSpace != -1) 
          {
						m_Text = m_Text.substr(0, indexOfLastSpace);
						break;
					} else 
          {
						m_Text = "";
						break;
					}
				}
        // Else just delete the last character
				m_Text.pop_back();
			}
			break;
		default: // If there are no special character or things to handle then check regular keys and casses
      // Normal character i.e not a number or something
			if (keyPressed >= 65 && keyPressed <= 90) // Normal character
      {
				if (!IsKeyDown(KEY_LEFT_SHIFT)) 
        {
					keyPressed += 32; // Lowercase the key by shifting the ascii value
					m_Text += static_cast<char>(keyPressed);
				} else 
        {
					m_Text += static_cast<char>(keyPressed);
				}
			} else if (keyPressed >= 48 && keyPressed <= 57) // Number character
      {
				if (IsKeyDown(KEY_LEFT_SHIFT)) 
        {
          handleSpecialNumberKeys(keyPressed); // Add the corresponding special character keys for the numbers
				} else 
        {
					m_Text += static_cast<char>(keyPressed);
				}
			} else 
      {
        // Cases for all of the special characters
				if (IsKeyDown(KEY_LEFT_SHIFT)) 
        {
          handleSpecialCharacters(keyPressed);
				} else
        {
			    m_Text += static_cast<char>(keyPressed);
        }
	  }
	}
}

bool InputBox::updateAndRender(void)
{
	Color backgroundColor   = m_Style.baseBackgroundColor;
	Color outlineColor      = m_Style.baseOutlineColor;
	Color textColor         = m_Style.baseTextColor;

  // Set the display text to placeholder text if the user has no input in the box
	std::string displayText = m_Text;
	if (m_Text.length() <= 0) 
		displayText = m_Style.placeholder;

	if (m_Style.editMode) 
  {
		backgroundColor = m_Style.hoverBackgroundColor;
		outlineColor    = m_Style.hoverOutlineColor;
		textColor       = m_Style.hoverTextColor;

    // Handle the key press and update the 'displayText' to have it fit inside the input box
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

  // Mouse is hovering the input box
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
