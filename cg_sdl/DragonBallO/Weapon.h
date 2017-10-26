#pragma once
#include "Entity.h"

class Weapon :
	public Entity
{
public:

	bool attacking;
	int attackRange;  //
	int attackDamage; // these are set to the player's variables of the same name. 



	Weapon();
	~Weapon();
	void SetAttack(int range, int damage);
	void Update() override;
	void OnCollision(Entity *other) override;



};

