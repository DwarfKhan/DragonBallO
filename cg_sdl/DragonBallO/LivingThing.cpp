#include "LivingThing.h"
#include "Player.h"
#include "Sprite.h"


extern float gDeltaTime;
extern Camera gCamera;





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

	case sMoveUp:
		mAnimMoveUp->UpdateSpriteClipIndex(mSpriteClipIndex);
		break;

	case sMoveDown:
		mAnimMoveDown->UpdateSpriteClipIndex(mSpriteClipIndex);
		break;

	case sMoveLeft:
		mAnimMoveLeft->UpdateSpriteClipIndex(mSpriteClipIndex);
		break;

	case sMoveRight:
		mAnimMoveRight->UpdateSpriteClipIndex(mSpriteClipIndex);
		break;
	}
}


void LivingThing::Update()
{
	Death();
	Animate();
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