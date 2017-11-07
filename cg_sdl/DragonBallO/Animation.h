#pragma once
#include <time.h>
#include <vector>
using namespace std;
class Animation
{
public:
	Animation();
	~Animation();
	void AddSpriteClip(int spriteclip);
	void SetAnimSpeed(float speed);
	void UpdateSpriteClipIndex(int &spriteClipIndex);
	int GetFrameCount();

	bool active;
	bool loops;



protected:
	float mTimer;
	int mFrameCount;
	int mCurrentFrame;
	float mSpeed;
	vector<int> mSpriteClips;




};

