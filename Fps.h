#pragma once
#ifndef INCLUDED_FPS_H_
#define INCLUDED_FPS_H_

class Fps
{
public:
	Fps();
	~Fps();

	void update();
	void drawFPS() const;
	void wait() const ;

	int getFrameCount() const { return frameCount; }	//何フレーム目かを返す
private : 
	unsigned int startTime;		//測定開始時刻
	int frameCount;
	float fps;			//計算したフレーム数
};

#endif // !INCLUDED_FPS_H_
