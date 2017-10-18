#pragma once
#include "Sprite.h"
#include "Destructible.h"
#include "Weapon.h"

class Player : public Sprite, public Destructible {
public:
	//Base class destructor is ALWAYS implicitly called...
	Player() { mCanBePushedBack = false; }
	virtual ~Player() override {}
	void Update() override;
	void SetWeapon(Weapon *weapon);
	void CheckDirection();
	void SetCorners();


	int lastMoveIndex;
	int lastAttackIndex;
	int attackRange;
	int attackDamage;
	Weapon *playerWeapon;
	int xDirMultiplier;
	int yDirMultiplier;
	MyMath::Float2 topRightCornerPos;
	MyMath::Float2 bottomRightCornerPos;
	MyMath::Float2 topLeftCornerPos;
	MyMath::Float2 bottomLeftCornerPos;

private:
	void Move();
	void Attack();
};