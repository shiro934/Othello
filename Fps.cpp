#include "Fps.h"

#include "DxLib.h"

#define FPS 60	//設定フレーム数
#define STRING_COLOR 0xffffff	//文字の色

Fps::Fps()
{
	startTime = 0;
	frameCount = 0;
	fps = 0;
}


Fps::~Fps()
{
}

void Fps::update() {
	if (frameCount == 0) {
		startTime = GetNowCount();
	}
	if (frameCount == FPS) {	//FPSで設定した値なら平均を計算
		int time = GetNowCount();
		fps = 1000.0f / (static_cast<float>(time - startTime) / FPS);
		frameCount = 0;
		startTime = time;
	}
	frameCount++;
}

void Fps::drawFPS() const {
	DrawFormatString(0, 0, STRING_COLOR, "%.1f", fps);
}

void Fps::wait() const {
	int elapsedTime = GetNowCount() - startTime;	//経過時間
	int waitTime = frameCount * 1000 / FPS - elapsedTime;	//待機時間
	if (waitTime > 0) {
		Sleep(waitTime);
	}
}