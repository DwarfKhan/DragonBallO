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
	bool UpdateSpriteClipIndex(int &spriteClipIndex); //returns true for completed animation, returns false for all other cases
	int GetFrameCount();

	bool active = false;
	bool loops = true;



protected:
	float mTimer;
	int mFrameCount;
	int mCurrentFrame;
	float mSpeed;
	vector<int> mSpriteClips; //must have at least 2 sprite clips to work




};

