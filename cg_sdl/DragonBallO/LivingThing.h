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

	 int animIdleCount;
	 int animIdleIndeces[10];
};





