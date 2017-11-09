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

bool Animation::UpdateSpriteClipIndex(int &spriteClipIndex)
{
	if (!active)
	{
		return false;
	}

	mTimer += mSpeed * gDeltaTime;
	int index = (int)mTimer % mFrameCount;

	if (loops)
	{
		spriteClipIndex = mSpriteClips[index];
		return false;
	}
	if (mCurrentFrame != index)
	{
			mCurrentFrame++;
			spriteClipIndex = mSpriteClips[index];
			//printf("Current Frame: %d.\n", mCurrentFrame);
			//printf("Spriteclip: %d.\n", mSpriteClips[index]);
		if (mCurrentFrame >= mFrameCount)
		{
			spriteClipIndex = mSpriteClips[mFrameCount - 1];
			active = false;
			mTimer = 0;
			mCurrentFrame = 0;
			return true;
		}
	}
	

	return false;
}

int Animation::GetFrameCount()
{
	return mFrameCount;
}
