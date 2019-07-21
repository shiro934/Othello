#pragma once
#ifndef INCLUDED_MOUSE_H_
#define INCLUDED_MOUSE_H_

#include "MouseButtonState.h"

#define MOUSE_BUTTON 3

class InputMouse
{
public:
	InputMouse();
	~InputMouse();

	void setMouseState();

	void getMousePos(int& x, int& y) const {	//マウスカーソルの現在位置を返す
		x = posX;
		y = posY;
	};

	MouseButtonState getMouseState(const unsigned int button) const;
private : 
	int posX, posY;	//マウスカーソルの現在地
	int preMouseState;
	MouseButtonState mouseState[MOUSE_BUTTON];
};

#endif // !INCLUDED_MOUSE_H_
