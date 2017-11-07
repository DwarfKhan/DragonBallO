#pragma once
#include "Sprite.h"
#include"Destructible.h"
#include "Weapon.h"

class LivingThing :
	public Sprite,
	public Destructible
{
public:
	LivingThing();
	~LivingThing();
	void AnimIdle();
	void AnimDamage();
	void AnimDeath();
	void Update() override;
	void Death();

	bool TakeDamage(int damage); // Not sure why override doesnt work here...
	void SetAttackingWeapon(Weapon *weapon);
	void SetAnimDamage(Animation *anim);
	void SetAnimIdle(Animation *anim);
	void SetAnimDeath(Animation *anim);
	void OnCollision(Entity *other) override;


	int attackRange;
	int attackDamage;
	Weapon *attackingWeapon;




protected:
	bool mIsAlive = true;
	Animation *mAnimIdle;
	Animation *mAnimDamage;
	Animation *mAnimDeath;


};





