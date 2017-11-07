#include "LivingThing.h"
#include "Player.h"
#include "Sprite.h"


extern float gDeltaTime;
extern Camera gCamera;


bool mIsAlive = true;



LivingThing::LivingThing()
{
}


LivingThing::~LivingThing()
{
}

void LivingThing::AnimIdle()
{

	if (mAnimDamage->active || mAnimDeath->active ) {
		return;
	}
	
	mAnimIdle->UpdateSpriteClipIndex(mSpriteClipIndex);
	
}

void LivingThing::AnimDamage()
{
	if (mAnimDeath->active)
	{
		return;
	}
	mAnimDamage->UpdateSpriteClipIndex(mSpriteClipIndex);
}

void LivingThing::AnimDeath()
{
	mAnimDeath->UpdateSpriteClipIndex(mSpriteClipIndex);
}

void LivingThing::Update()
{
	Death();
	AnimDeath();
	AnimDamage();
	AnimIdle();
	Sprite::Update();
}

bool LivingThing::TakeDamage(int damage)
{
	if (mHealth - damage > 0) {
	mAnimDamage->active = true;
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
	}
}

