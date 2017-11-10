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

bool Animation::UpdateSpriteClipIndex(int &spriteClipIndex) //returns true for a finished non-looping animation
{
	if (!active)
	{
		return false;
	}

	// one frame animations get buggy, so this doubles one frame animations
	if (mFrameCount == 1)
	{
		AddSpriteClip(mSpriteClips[0]);
		SetAnimSpeed(mSpeed * 2);
	}
	
	//math for finding which frame needs to be displayed
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

			
		if (mCurrentFrame >= mFrameCount) // if the animation is over end animation and reset timing values
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
