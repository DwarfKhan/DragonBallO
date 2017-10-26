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

bool LivingThing::TakeDamage(int damage)
{
	return Destructible::TakeDamage(damage);
}

void LivingThing::SetAttackingWeapon(Weapon * weapon)
{
	attackingWeapon = weapon;
}

void LivingThing::OnCollision(Entity * other)
{
	if (typeid(other) == typeid(Weapon*)) {
		Destructible::TakeDamage(attackingWeapon->attackDamage);
	}


	Entity::OnCollision(other);
}

void LivingThing::Death()
{
	if (!TakeDamage(0)) {

	}
}

