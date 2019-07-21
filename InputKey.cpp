#include "InputKey.h"

#include "DxLib.h"

InputKey::InputKey()
{
	GetHitKeyStateAll(preKey);
}


InputKey::~InputKey()
{
}

void InputKey::setKey() {
	char key[SET_KEY_NUM];
	GetHitKeyStateAll(key);

	for (int i = 0; i < SET_KEY_NUM; i++) {
		if (key[i] == 0) {	//キーが押されていない
			if (preKey[i] == key[i]) {
				keyState[i] = KEY_UP_KEEP;
				continue;
			}
			keyState[i] = KEY_UP;
			continue;
		}

		//キーが押されている
		if (preKey[i] == key[i]) {
			keyState[i] = KEY_DOWN_KEEP;
			continue;
		}
		keyState[i] = KEY_DOWN;
	}

	for (int i = 0; i < SET_KEY_NUM; i++) {
		preKey[i] = key[i];
	}
}
