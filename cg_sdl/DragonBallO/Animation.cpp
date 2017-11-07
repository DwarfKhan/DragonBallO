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

void Animation::UpdateSpriteClipIndex(int &spriteClipIndex)
{
	if (!active)
	{
		mTimer = 0;
		mCurrentFrame = 0;
		return;
	}

	mTimer += mSpeed * gDeltaTime;
	int index = (int)mTimer % mFrameCount;

	if (loops)
	{
		spriteClipIndex = mSpriteClips[index];
		return;
	}
	if (mCurrentFrame != index)
	{
			mCurrentFrame++;
			spriteClipIndex = mSpriteClips[index];
			//printf("Current Frame: %d.\n", mCurrentFrame);
			//printf("Spriteclip: %d.\n", mSpriteClips[index]);
		if (mCurrentFrame == mFrameCount)
		{
			spriteClipIndex = mSpriteClips[mFrameCount - 1];
			active = false;
		}
	}
	


}

int Animation::GetFrameCount()
{
	return mFrameCount;
}
