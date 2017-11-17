#include "LivingThing.h"
#include "Player.h"
#include "Sprite.h"
#include "MyMath.h"



extern float gDeltaTime;
extern Camera gCamera;

using namespace MyMath;
using Float2 = MyMath::Float2;



LivingThing::LivingThing()
{
}


LivingThing::~LivingThing()
{
}

void LivingThing::Animate()
{
	bool finished;

	switch(animState) {

	case sIdle:
		mAnimIdle->UpdateSpriteClipIndex(mSpriteClipIndex);
		break;

	case sDamage:
		finished = mAnimDamage->UpdateSpriteClipIndex(mSpriteClipIndex);
		if (finished) {
			animState = sIdle;
			mAnimIdle->active = true;
		}
		break;

	case sDeath:
		mAnimDeath->UpdateSpriteClipIndex(mSpriteClipIndex);
		break;

	case sMove:
		switch (mFacingDirection) {

		case 0:

		mAnimMoveUp->active = true;
		finished = mAnimMoveUp->UpdateSpriteClipIndex(mSpriteClipIndex);
			break;

		case 1:

			mAnimMoveDown->active = true;
			finished = mAnimMoveDown->UpdateSpriteClipIndex(mSpriteClipIndex);
			break;

		case 2:
			mAnimMoveLeft->active = true;
			finished = mAnimMoveLeft->UpdateSpriteClipIndex(mSpriteClipIndex);
			break;

		case 3:
			mAnimMoveRight->active = true;
			finished = mAnimMoveRight->UpdateSpriteClipIndex(mSpriteClipIndex);
			break;

		}
		if (finished) {
			animState = sIdle;
			mAnimIdle->active = true;
		}

		break;
	}
}


void LivingThing::Update()
{

	Death();
	Animate();
	Move();
	Sprite::Update();
}

bool LivingThing::TakeDamage(int damage)
{
	if (mHealth - damage > 0) {
	mAnimDamage->active = true;
	animState = sDamage;
	}
	printf("HP: %d \n", (mHealth - damage));
	return Destructible::TakeDamage(damage);
}

void LivingThing::SetAttackingWeapon(Weapon * weapon)
{
	attackingWeapon = weapon;
}

void LivingThing::SetFollowTarget(Entity * target)
{

	mFollowTarget = target;

}

void LivingThing::SetAnimDamage(Animation * anim)
{
	mAnimDamage = anim;
}

void LivingThing::SetAnimIdle(Animation* anim)
{
	mAnimIdle = anim;
}

void LivingThing::SetAnimDeath(Animation * anim)
{
	mAnimDeath = anim;
}

void LivingThing::SetAnimMoveUp(Animation * anim)
{
	mAnimMoveUp = anim;
}

void LivingThing::SetAnimMoveDown(Animation * anim)
{
	mAnimMoveDown = anim;
}

void LivingThing::SetAnimMoveLeft(Animation * anim)
{
	mAnimMoveLeft = anim;
}

void LivingThing::SetAnimMoveRight(Animation * anim)
{
	mAnimMoveRight = anim;
}

void LivingThing::OnCollision(Entity * other)
{



	Entity::OnCollision(other);
}

void LivingThing::OnProxCollision(Entity * other)
{
}

void LivingThing::Move()
{
	if (!mIsAlive)
	{
		return;
	}

	MyMath::Float2 difPos;

	switch (moveState) {

	case sNotMoving:
		moveDir = none;
		mFollowVector = { 0,0 };
		return;
		break;

	case sRandom:


		randomNavTimer -= gDeltaTime;
		//printf("navTimer: %f\n", randomNavTimer);

		if (randomNavTimer <= 0)
		{
		//choose a new direction
			if(DiceRoll(0, 1) == 0) {
				mFollowVector = 0;
			}
			else {
				//set x and y to random values between -1 and 1
				mFollowVector.x = (((float)DiceRoll(0, 200) / 100.0f) - 1.0f);
				mFollowVector.y = (((float)DiceRoll(0, 200) / 100.0f) - 1.0f);

				//Normalize (set length of follow vector to 1)
				MyMath::Normalize(mFollowVector);
			}

			//reset timer
			float newTime = (
				((float)DiceRoll(randomNavMinTime, randomNavMaxTime))
				/10.0f);
				randomNavTimer = newTime;

		}

		break;

	case sDirectFollow:

		//making sure there is a target to follow
		if (mFollowTarget == nullptr) {
			printf("No target selected to follow, returning to default movestate.\n");
			moveState = defaultMoveState;
			break;
		}

		difPos = mFollowTarget->GetPos() - mPos;
		
		if (Mag(difPos) > awareDist)//if target is outside aware distance
		{
			mFollowVector = { 0,0 };
			moveDir = none;
			break;
		}
		mFollowVector = difPos;
		Normalize(mFollowVector);

		break;

	default:
		printf("Invalid movestate, returning to default movestate.\n");
		moveState = defaultMoveState;

		break;

	}



	MyMath::Float2 newPos = mPos;
		AnimState tempState;

		//Display idle if not moving
		if (mFollowVector.x == 0 && mFollowVector.y == 0)
		{
			tempState = sIdle;
		}
		else {
			tempState = sMove;
			//printf("newPos before speed/time x: %f, y: %f.\n", newPos.x, newPos.y);
			newPos += (mFollowVector * mMoveSpeed * gDeltaTime);
			//printf("newPos after speed/time x: %f, y: %f.\n", newPos.x, newPos.y);

		}

		//Decide on facingDirection
		if (.1 + Abs(mFollowVector.x) >= Abs(mFollowVector.y)) {//Further in x distance
			if (mFollowVector.x >= 0) {//right
				mFacingDirection = 3;
			}
			else {//left
				mFacingDirection = 2;
			}
		}
		else {
			if (mFollowVector.y >=0) {//Down
				mFacingDirection = 1;
			}
			else {
				mFacingDirection = 0;
			}
		}
		//damage animation takes priority over move animation
		if (!(animState == sDamage && mAnimDamage->active == true)) {
			animState = tempState;
		}

		mPos = newPos;
}

void LivingThing::Death()
{
	if ( (mHealth <= 0) && (mIsAlive) ) {
		mAnimDeath->active = true;
		mAnimIdle->active = false;
		mIsAlive = false;
		animState = sDeath;
	}
}


// TEMPLATE
	/*
	1: declare in declerations namespace
	2: Cleanup
	3: Update
	4: render
	*/
// LIVING THING 
	//health

	//postiotn

	//size

	//collision

	//Path name

	//Load Texture

	//Init sprite sheet

	//Spriteclips

	//Anchor offsets

	//Animation

// END LIVING THING 