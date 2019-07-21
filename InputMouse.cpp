#include "InputMouse.h"

#include "DxLib.h"

#include <cassert>

InputMouse::InputMouse()
{
	preMouseState = GetMouseInput();

	for (int i = 0; i < MOUSE_BUTTON; i++) {
		if (preMouseState & (1 << i)) {
			mouseState[i] = BUTTON_DOWN;
		}
		else {
			mouseState[i] = BUTTON_UP_KEEP;
		}
	}
}


InputMouse::~InputMouse()
{
}

void InputMouse::setMouseState() {
	GetMousePoint(&posX, &posY);  //カーソル位置をセット

	int currentMouseState = GetMouseInput();

	for (int i = 0; i < MOUSE_BUTTON; i++) {
		if (currentMouseState & (1 << i)) {
			switch (mouseState[i]) {
			case BUTTON_DOWN : 
				mouseState[i] = BUTTON_DOWN_KEEP;
				break;
			case BUTTON_UP_KEEP : case BUTTON_UP : 
				mouseState[i] = BUTTON_DOWN;
				break;
			}
		}
		else {
			switch (mouseState[i]) {
			case BUTTON_UP:
				mouseState[i] = BUTTON_UP_KEEP;
				break;
			case BUTTON_DOWN: case BUTTON_DOWN_KEEP:
				mouseState[i] = BUTTON_UP;
				break;
			}
		}
	}

}

MouseButtonState InputMouse::getMouseState(const unsigned int button) const {
	MouseButtonState state = MouseButtonState::UNKNOWN;
	switch (button) {
	case MOUSE_INPUT_LEFT :
		state = mouseState[0];
		break;
	case MOUSE_INPUT_RIGHT : 
		state = mouseState[1];
		break;
	case MOUSE_INPUT_MIDDLE : 
		state = mouseState[2];
		break;
	}

	assert(state != MouseButtonState::UNKNOWN);

	return state;
}