#pragma once
#ifndef INCLUDED_RESIDENT_H_
#define INCLUDED_RESIDENT_H_

#include "SceneManager.h"
#include "Fps.h"
#include "InputKey.h"
#include "InputMouse.h"

class Resident
{
public:
	Resident();
	~Resident();

	SceneManager sceneManag;
	InputKey inputKey;
	InputMouse inputMouse;
	Fps fpsCalc;
};

#endif // !INCLUDED_RESIDENT_H_