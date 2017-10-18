#pragma once
#include "Entity.h"
class Weapon :
	public Entity
{
public:

	bool attacking;




	Weapon();
	~Weapon();
	void Update() override;
	void OnCollision(Entity *other) override;


};

