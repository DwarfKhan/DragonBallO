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
	void Update() override;
	bool TakeDamage(int damage); // Not sure why override doesnt work here...
	void SetAttackingWeapon(Weapon *weapon);
	void SetAnimIdle(Animation *anim);
	void OnCollision(Entity *other) override;
	void Death();


	int attackRange;
	int attackDamage;
	Weapon *attackingWeapon;


	bool animIdleActive; 


protected:
	float mIdleTimer;
	Animation *mAnimIdle;


};





