#pragma once
#include "Sprite.h"
#include"Destructible.h"

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

	int attackRange;
	int attackDamage;
	bool animIdle;
	 int animIdleCount;
	 int animIdleIndeces[10]; //TODO: dont hard code this...
};





