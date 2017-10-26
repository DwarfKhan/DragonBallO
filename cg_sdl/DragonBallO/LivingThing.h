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
	void OnCollision(Entity *other) override;
	void Death();

	int attackRange;
	int attackDamage;
	bool animIdle;
	int animIdleCount;
	Weapon *attackingWeapon;
	int animIdleIndeces[10]; //TODO: dont hard code this...
};





