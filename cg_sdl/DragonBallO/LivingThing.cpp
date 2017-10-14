#include "LivingThing.h"
#include "Player.h"
#include "Sprite.h"

extern float gDeltaTime;
extern Camera gCamera;


float idleTimer = 0.0f;
float animIdleSpeed = 12;


LivingThing::LivingThing()
{

}


LivingThing::~LivingThing()
{
}

void LivingThing::AnimIdle()
{
	idleTimer += animIdleSpeed * gDeltaTime;

	int index = (int)idleTimer % animIdleCount;


	mSpriteClipIndex = animIdleIndeces[index];

//	mSpriteClipIndex = 1;
}

void LivingThing::Update()
{
	AnimIdle();
	Sprite::Update();
}
