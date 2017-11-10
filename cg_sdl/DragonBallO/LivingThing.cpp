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

void LivingThing::Move()
{
	if (!mIsAlive)
	{
		return;
	}


	switch (moveState) {

	case sNotMoving:
		moveDir = none;
		return;
		break;

	case sRandom:


		randomNavTimer -= gDeltaTime;
		printf("navTimer: %f\n", randomNavTimer);

		if (randomNavTimer <= 0)
		{
		//choose a new direction
			switch (DiceRoll(0, 8)) {

			case 0://stand still
				moveDir = none;
				break;

			case 5://stand still
				moveDir = none;
				break;

			case 6://stand still
				moveDir = none;
				break;

			case 7://stand still
				moveDir = none;
				break;

			case 8://stand still
				moveDir = none;
				break;

			case 1:
				moveDir = up;
				break;

			case 2:
				moveDir = down;
				break;

			case 3:
				moveDir = left;
				break;

			case 4:
				moveDir = right;
				break;
			}
			//reset timer
			float newTime = (float)DiceRoll(0, randomNavMaxTime);
				randomNavTimer = newTime;

		}

		break;

	}


	printf("moving: %d", moveDir);
	MyMath::Float2 newPos = mPos;
		AnimState tempState;
	switch (moveDir) {
	case none:
		mFacingDirection = 1;
		tempState = sIdle;
		mAnimIdle->active = true;
		break;

	case up:
		mFacingDirection = 0;
		tempState = sMove;

		newPos.y -= (gDeltaTime * mMoveSpeed);
		break;

	case down:
		mFacingDirection = 1;
		tempState = sMove;

		newPos.y += (gDeltaTime * mMoveSpeed);
		break;

	case left:
		mFacingDirection = 2;
		tempState = sMove;

		newPos.x -= (gDeltaTime * mMoveSpeed);
		break;

	case right:
		mFacingDirection = 3;
		tempState = sMove;

		newPos.x += (gDeltaTime * mMoveSpeed);
		break;
	}
	mPos = newPos;

	//damage animation takes priority over move animation
	if (!(animState == sDamage && mAnimDamage->active == true)) {
		animState = tempState;
	}
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