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
	void Move();
	void Animate();
	void Death();
	bool TakeDamage(int damage); // Not sure why override doesnt work here...
	void SetAttackingWeapon(Weapon *weapon);
	void SetFollowTarget(Entity *target);

	void SetAnimDamage(Animation *anim);
	void SetAnimIdle(Animation *anim);
	void SetAnimDeath(Animation *anim);
	void SetAnimMoveUp(Animation *anim);
	void SetAnimMoveDown(Animation *anim);
	void SetAnimMoveLeft(Animation *anim);
	void SetAnimMoveRight(Animation *anim);


	enum AnimState {sIdle, sDeath, sDamage, sMove};
	AnimState animState = sIdle;
	enum MoveState {sNotMoving, sDirectFollow, sRandom};
	MoveState defaultMoveState = sNotMoving;
	MoveState moveState;

	int attackRange;
	int attackDamage;
	Weapon *attackingWeapon;
	




protected:

	float randomNavTimer = 0;
	float randomNavMaxTime = 1;

	enum MoveDir { up, down, left, right, none };
	MoveDir moveDir;

	bool mIsAlive = true;
	Animation *mAnimIdle;
	Animation *mAnimDamage;
	Animation *mAnimDeath;
	Animation *mAnimMoveUp;
	Animation *mAnimMoveDown;
	Animation *mAnimMoveLeft;
	Animation *mAnimMoveRight;

	Entity * mFollowTarget;
	MyMath::Float2 mFollowVector;

};





