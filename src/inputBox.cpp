#include "../include/inputBox.hpp"

std::string InputBox::GetInput() { return m_Style.text; }

/* NOTE: Find a more effiecent way then reversing the string at the end */
std::string InputBox::GetClippedText()
{
	std::string clippedText;

	for (size_t i = m_Style.text.length()-1; i > 0; i--) {
		if (MeasureText(clippedText.c_str(), m_Style.fontSize)+OFFSET_TEXT < m_Bounds.width-OFFSET_TEXT-OFFSET_CURSOR) {
			clippedText += m_Style.text[i];
		} else {
			break;
		}
	}

	std::reverse(clippedText.begin(), clippedText.end());
	return clippedText;
}

void InputBox::UpdateAndRender()
{
	Color backgroundColor   = m_Style.baseBackgroundColor;
	Color outlineColor      = m_Style.baseOutlineColor;
	Color textColor         = m_Style.baseTextColor;

	std::string displayText = m_Style.text;

	if (m_Style.editMode) {
		backgroundColor = m_Style.hoverBackgroundColor;
		outlineColor    = m_Style.hoverOutlineColor;
		textColor       = m_Style.hoverTextColor;

		int keyPressed = GetKeyPressed();

		/* NOTE: Add shift-key functionality - and have it work with other characters like ,.:'/<>?[]{}()\|!@#$%%^&*()-_=+'" */
		/* NOTE: Refactor to work using switch - check if the key is KEY_V then do the checks for ctrl and cmd then check the other things in the switch */
		/* NOTE: Add backspace repeat */
		if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_LEFT_SUPER)) { /* KEY_LEFT_SUPER is the command key on mac */
			if (keyPressed == KEY_V) {
				/* NOTE: Update functionality to treat '\n' as ' ' */
				const char* clipboardText = GetClipboardText();
				m_Style.text += clipboardText;
			}
		} else if (keyPressed == KEY_BACKSPACE) {
			if (m_Style.text.length() > 0)
				m_Style.text.pop_back();
		} else if (keyPressed == KEY_SPACE) {
				m_Style.text += ' ';
		} else if (keyPressed != KEY_NULL) { 
			keyPressed += 32;
			m_Style.text += static_cast<char>(keyPressed);
		}

		if (MeasureText(m_Style.text.c_str(), m_Style.fontSize)+OFFSET_TEXT > m_Bounds.width-OFFSET_TEXT) {
			displayText = GetClippedText();
		}

		DrawRectangleRec({ m_Bounds.x+OFFSET_TEXT+MeasureText(displayText.c_str(), m_Style.fontSize)+OFFSET_CURSOR, m_Bounds.y+OFFSET_CURSOR, 2,
			m_Bounds.height-OFFSET_CURSOR-m_Style.outlineThickness }, textColor);
	}

	if (MeasureText(m_Style.text.c_str(), m_Style.fontSize)+OFFSET_TEXT > m_Bounds.width-OFFSET_TEXT) {
		displayText = GetClippedText();
	}

	/* NOTE: Change display format to show the outline with the 'Input' text overlaping the top part of the outline - thus clearing the input field */
	if (CheckCollisionPointRec(GetMousePosition(), m_Bounds)) {
		SetMouseCursor(MOUSE_CURSOR_IBEAM);

		backgroundColor = m_Style.hoverBackgroundColor;
		outlineColor    = m_Style.hoverOutlineColor;
		textColor       = m_Style.hoverTextColor;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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
}
