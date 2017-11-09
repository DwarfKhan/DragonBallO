#include "CollisionLayer.h"



CollisionLayer::CollisionLayer()
{
}


CollisionLayer::~CollisionLayer()
{
}

void CollisionLayer::AddEntity(Entity & ent)
{
	mEntities.push_back(&ent);
	mSize++;
}

void CollisionLayer::CollideWith(Entity & ent)
{
	for (int i = 0; i < mSize ; i++)
	{
		if (&ent == mEntities[i])
		{
			return;
		}
		ent.AddCollidableEntity(*mEntities[i]);
		mEntities[i]->AddCollidableEntity(ent);
	}
}
