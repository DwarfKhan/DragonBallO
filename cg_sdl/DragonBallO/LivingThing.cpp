#include "LivingThing.h"
#include "Player.h"
#include "Sprite.h"

extern float gDeltaTime;
extern Camera gCamera;


float idleTimer = 0.0f;
float animIdleSpeed = 6;
bool animIdle = true;


LivingThing::LivingThing()
{

}


LivingThing::~LivingThing()
{
}

void LivingThing::AnimIdle()
{
	if (animIdle) {

	idleTimer += animIdleSpeed * gDeltaTime;

	int index = (int)idleTimer % animIdleCount;


	mSpriteClipIndex = animIdleIndeces[index];
	}
}

void LivingThing::Update()
{
	AnimIdle();
	Sprite::Update();
}
