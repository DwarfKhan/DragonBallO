#include "Animation.h"


extern float gDeltaTime;

Animation::Animation()
{
	mFrameCount = 0;
}


Animation::~Animation()
{
}

void Animation::AddSpriteClip(int spriteclip)
{
	mSpriteClips.push_back(spriteclip);
	mFrameCount++;
}

void Animation::SetAnimSpeed(float speed)
{
	mSpeed = speed;
}

int Animation::UpdateSpriteClipIndex()
{
	mTimer += mSpeed * gDeltaTime;

	int index = (int)mTimer % mFrameCount;

	return index;


	return 0;
}
