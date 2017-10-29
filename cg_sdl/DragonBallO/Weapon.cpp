#include "Weapon.h"
#include "LivingThing.h"

LivingThing livingThingTypeHolder;

Weapon::Weapon()
{
}



Weapon::~Weapon()
{
}

void Weapon::SetAttack(int range, int damage)
{
	attackRange = range;
	attackDamage = damage;
}

void Weapon::Update()
{
	Entity::Update();
}

void Weapon::OnCollision(Entity * other)
{
	if (!attacking) {
		return;
	}

	if (typeid(*other) != typeid(livingThingTypeHolder)) {
		attacking = false;
		Entity::OnCollision(other);
		return;
	}
	//TODO: figure out how to acess other's LivingThing/Destructible Functions
	printf("Weapon hit LivingThing. ");






	attacking = false;
	Entity::OnCollision(other);
}




