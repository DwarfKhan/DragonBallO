#include "LivingThing.h"
#include "Player.h"
#include "Sprite.h"


extern float gDeltaTime;
extern Camera gCamera;


float idleTimer = 0.0f;
Weapon weaponTypeHolder;



LivingThing::LivingThing()
{

}


LivingThing::~LivingThing()
{
}

void LivingThing::AnimIdle()
{
	if (!animIdleActive) {
		return;
	}
	mSpriteClipIndex = mAnimIdle->UpdateSpriteClipIndex();
}

void LivingThing::Update()
{
	AnimIdle();
	Sprite::Update();
}

bool LivingThing::TakeDamage(int damage)
{
	return Destructible::TakeDamage(damage);
}

void LivingThing::SetAttackingWeapon(Weapon * weapon)
{
	attackingWeapon = weapon;
}

void LivingThing::SetAnimIdle(Animation* anim)
{
	mAnimIdle = anim;
}

void LivingThing::OnCollision(Entity * other)
{
	if (typeid(*other) == typeid(weaponTypeHolder)) {
	//	Destructible::TakeDamage(attackingWeapon->attackDamage);
		animIdleActive = true;
	}


	Entity::OnCollision(other);
}

void LivingThing::Death()
{
	if (!TakeDamage(0)) {

	}
}

