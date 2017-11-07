#pragma once
#include "Entity.h"

class Weapon :
	public Entity
{
public:

	bool attacking;
	int attackDamage; // these are set to the player's variables of the same name. 



	Weapon();
	~Weapon();
	void SetDamage(int damage);
	void Update() override;
	void OnCollision(Entity *other) override;



};

