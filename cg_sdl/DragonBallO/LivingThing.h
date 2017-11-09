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

	void Update() override;
	void OnCollision(Entity *other) override;
	void Animate();
	void Death();
	bool TakeDamage(int damage); // Not sure why override doesnt work here...
	void SetAttackingWeapon(Weapon *weapon);

	void SetAnimDamage(Animation *anim);
	void SetAnimIdle(Animation *anim);
	void SetAnimDeath(Animation *anim);
	void SetAnimMoveUp(Animation *anim);
	void SetAnimMoveDown(Animation *anim);
	void SetAnimMoveLeft(Animation *anim);
	void SetAnimMoveRight(Animation *anim);


	enum AnimState {sIdle, sDeath, sDamage, sMoveUp, sMoveDown, sMoveLeft, sMoveRight};
	int attackRange;
	int attackDamage;
	AnimState animState = sIdle;
	Weapon *attackingWeapon;
	




protected:
	bool mIsAlive = true;
	Animation *mAnimIdle;
	Animation *mAnimDamage;
	Animation *mAnimDeath;
	Animation *mAnimMoveUp;
	Animation *mAnimMoveDown;
	Animation *mAnimMoveLeft;
	Animation *mAnimMoveRight;


};





