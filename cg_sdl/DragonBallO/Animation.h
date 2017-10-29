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
	int UpdateSpriteClipIndex();

protected:
	int mFrameCount;
	float mSpeed;
	float mTimer;
	vector<int> mSpriteClips;




};

