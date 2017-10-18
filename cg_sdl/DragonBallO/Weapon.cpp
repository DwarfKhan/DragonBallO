#include "Weapon.h"



Weapon::Weapon()
{
}



Weapon::~Weapon()
{
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
	//TODO: attack logic
	Entity::OnCollision(other);
}


