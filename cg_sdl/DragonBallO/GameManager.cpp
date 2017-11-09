#include "GameManager.h"
#include "SDLInit.h"
#include "World.h"
#include "Player.h"
#include "Camera.h"
#include "MoveTrigger.h"
#include "LivingThing.h"
#include "Weapon.h"
#include "CollisionLayer.h"

#define CAMERA_MODE Camera::Mode::PAN
#define SHOW_COLLIDERS true

//Also camera dimension...
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

Camera gCamera(CAMERA_MODE);
World gWorld;

static SDLInit sdlInit;

namespace {
	Player player;
	Sprite tree;
	Sprite boulder;
	LivingThing target;
		Animation targetIdle;
		Animation targetDamage;
		Animation targetDeath;
	LivingThing guard;
		Animation guardIdle;
		Animation guardDamage;
		Animation guardDeath;
		Animation guardMoveUp;
		Animation guardMoveDown;
		Animation guardMoveLeft;
		Animation guardMoveRight;
	MoveTrigger moveTrigger;
	Weapon playerWeapon;

	CollisionLayer lLivingThings;
	CollisionLayer lWeapons;
	CollisionLayer lMoveTriggers;
}

void InitEntities() {

//PLAYER

	//path name
	player.SetTexturePath("textures/link_sheet.png");

	//load texture
	sdlInit.LoadTexture(player);

	//position
	player.SetPosition({0, 0});

	//size
	player.SetSize(70, 70);

	//Init Sprite Sheet
	player.InitSpriteSheet(0, 14, 6);

	//walk sprite clips
	player.SetSpriteClip(90, 1, 30, 30, 3);			//up...
	player.SetSpriteClip(90, 31, 30, 30, 17);		//up move...
	player.SetSpriteClip(30, 1, 30, 30, 1);			//down...
	player.SetSpriteClip(30, 31, 30, 30, 15);		//down move...
	player.SetSpriteClip(120, 1, 30, 30, 4);		//right...
	player.SetSpriteClip(120, 31, 30, 30, 18);		//right move...
	player.SetSpriteClip(60, 1, 30, 30, 2);			//left...
	player.SetSpriteClip(60, 31, 30, 30, 16);		//left move...

	//Attack sprite clips
	player.SetSpriteClip(170, 141, 30, 31, 5);		//up attack...
	player.SetSpriteClip(173, 71, 30, 30, 6);		//left attack...
	player.SetSpriteClip(203, 142, 30, 30, 7);		//right attack...
	player.SetSpriteClip(295, 59, 30, 32, 8);		//down attack...

	//attack anchor positions
	player.SetAnchorOffset({-16, -13}, 5);			//up attack...
	player.SetAnchorOffset({-26, -5}, 6);			//left attack...
	player.SetAnchorOffset({4, 0}, 7);				//right attack...
	player.SetAnchorOffset({ -23, 8 }, 8);		//down attack...
	
	//collision
	player.ConfigureCollision(true, true, { 0, 14 }, { 35, 16 });
	lLivingThings.AddEntity(player);
	
	//setWeapon
	player.SetWeapon(&playerWeapon, 33);



//END PLAYER

//PLAYERWEAPON

	//
	playerWeapon.attacking = true;


	//size
	playerWeapon.SetSize(5,5);

	//collision
	playerWeapon.ConfigureCollision(false, true);
	lWeapons.AddEntity(playerWeapon);

//END PLAYERWEAPON

//TREE

	//path name
	tree.SetTexturePath("textures/tree_green.gif");

	//load texture
	sdlInit.LoadTexture(tree);

	//position
	tree.SetPosition({ 200, 300 });

	//size
	tree.SetSize(64, 78);

	//collision
	tree.ConfigureCollision(true, false);
	lLivingThings.AddEntity(tree);

//END TREE

//BOULDER

	//path name
	boulder.SetTexturePath("textures/boulder.png");

	//load texture
	sdlInit.LoadTexture(boulder);

	//position
	boulder.SetPosition({ 200, 150 });

	//size
	boulder.SetSize(45, 45);

	//collision
	boulder.ConfigureCollision(false, true);
	lLivingThings.AddEntity(boulder);


//END BOULDER

//MOVETRIGGER

	//position
	moveTrigger.SetPosition({ 300, 150 });

	//size
	moveTrigger.SetSize(45, 45);

	//collision
	moveTrigger.ConfigureCollision(false, false);
	lMoveTriggers.AddEntity(moveTrigger);

	//destination
	moveTrigger.SetMovePos({ 960, 200 });

//END MOVETRIGGER

//TARGET

	//path name
	target.SetTexturePath("textures/scarecrow.png");

	//load texture
	sdlInit.LoadTexture(target);

	//init sprite sheet
	target.InitSpriteSheet(0, 4, 2);

	//sprite clips
	target.SetSpriteClip(0, 0, 31, 31, 0);
	target.SetSpriteClip(32, 0, 32, 32, 1);
	target.SetSpriteClip(64, 0, 32, 32, 2);
	target.SetSpriteClip(96, 0, 32, 32, 3);
	target.SetSpriteClip(0, 32, 32, 32, 4);
	target.SetSpriteClip(32, 32, 32, 32,5);

	//anchor offsets
	//target.SetAnchorOffset({ 0, -13 }, 0);

	//animation

	target.SetAnimIdle(&targetIdle);
	targetIdle.active = true;
	targetIdle.SetAnimSpeed(5);
	targetIdle.AddSpriteClip(0);
	targetIdle.AddSpriteClip(0);
	
	
	target.SetAnimDamage(&targetDamage);
	targetDamage.loops = false;
	targetDamage.SetAnimSpeed(15);
	targetDamage.AddSpriteClip(1);
	targetDamage.AddSpriteClip(1);


	target.SetAnimDeath(&targetDeath);
	targetDeath.loops = false;
	targetDeath.SetAnimSpeed(7.5);
	targetDeath.AddSpriteClip(1);
	targetDeath.AddSpriteClip(2);
	targetDeath.AddSpriteClip(3);
	targetDeath.AddSpriteClip(4);
	targetDeath.AddSpriteClip(5);


	//Health
	target.Destructible::SetHealth(3, 3);

	//position
	target.SetPosition({990 , 200 });

	//size
	target.SetSize(50, 50);

	//collision
	target.ConfigureCollision(true, false);
	lLivingThings.AddEntity(target);
	

//END TARGET

// GUARD
	//health
	guard.Destructible::SetHealth(5,5);
	//Path name
	guard.SetTexturePath("textures/Guard.png");
	//Load Texture
	sdlInit.LoadTexture(guard);
	//Init sprite sheet
	guard.InitSpriteSheet(0, 11, 6);
	//position
	guard.SetPosition({116,220});
	//size
	guard.SetSize(60, 60);
	//collision
	guard.ConfigureCollision(true, false, { 0,17 }, {26,0});
	lLivingThings.AddEntity(guard);
	//Spriteclips
	guard.SetSpriteClip(0, 1, 25, 25, 0);
	guard.SetSpriteClip(25, 1, 25, 25, 1);
	guard.SetSpriteClip(50, 1, 25, 25, 2);
	guard.SetSpriteClip(75, 1, 25, 25, 3);
	guard.SetSpriteClip(0, 26, 25, 25, 4);
	guard.SetSpriteClip(25, 26, 25, 25, 5);
	guard.SetSpriteClip(50, 26, 25, 25, 6);
	guard.SetSpriteClip(75, 26, 25, 25, 7);
	guard.SetSpriteClip(0, 51, 25, 25, 8);
	guard.SetSpriteClip(25, 51, 25, 25, 9);
	guard.SetSpriteClip(50, 51, 25, 25, 10);
	guard.SetSpriteClip(75, 51, 25, 25, 11);
	guard.SetSpriteClip(0, 76, 25, 25, 12);
	guard.SetSpriteClip(25, 76, 25, 25, 13);
	guard.SetSpriteClip(50, 76, 25, 25, 14);
	guard.SetSpriteClip(75, 76, 25, 25, 15);
	guard.SetSpriteClip(0, 101, 25, 25, 16);
	guard.SetSpriteClip(25, 101, 25, 25, 17);
	guard.SetSpriteClip(50, 101, 25, 25, 18);
	guard.SetSpriteClip(75, 101, 25, 25, 19);
	guard.SetSpriteClip(0, 126, 25, 25, 20);
	guard.SetSpriteClip(25, 126, 25, 25, 21);
	guard.SetSpriteClip(50, 126, 25, 25, 22);
	guard.SetSpriteClip(75, 126, 25, 25, 23);
	guard.SetSpriteClip(175, 101, 25, 25, 24);
	guard.SetSpriteClip(250, 26, 25, 25, 25);

	//Anchor offsets
	guard.SetAnchorOffset({-26,0}, 19);
	guard.SetAnchorOffset({-26,0}, 23);

	//Animation
	guard.SetAnimIdle(&guardIdle);
	guardIdle.active = true;
	guardIdle.SetAnimSpeed(5);
	guardIdle.AddSpriteClip(16);
	guardIdle.AddSpriteClip(16);
	
	guard.SetAnimDamage(&guardDamage);
	guardDamage.loops = false;
	guardDamage.SetAnimSpeed(15);
	guardDamage.AddSpriteClip(24);
	guardDamage.AddSpriteClip(24);
	guardDamage.AddSpriteClip(24);

	guard.SetAnimDeath(&guardDeath);
	guardDeath.loops = false;
	guardDeath.SetAnimSpeed(15);
	guardDeath.AddSpriteClip(25);
	guardDeath.AddSpriteClip(25);

	guard.SetAnimMoveUp(&guardMoveUp);
	guardMoveUp.loops = true;
	guardMoveUp.SetAnimSpeed(10);
	guardMoveUp.AddSpriteClip(20);
	guardMoveUp.AddSpriteClip(21);

	guard.SetAnimMoveDown(&guardMoveDown);
	guardMoveDown.loops = true;
	guardMoveDown.SetAnimSpeed(10);
	guardMoveDown.AddSpriteClip(8);
	guardMoveDown.AddSpriteClip(9);
	
	guard.SetAnimMoveLeft(&guardMoveLeft);
	guardMoveLeft.loops = true;
	guardMoveLeft.SetAnimSpeed(10);
	guardMoveLeft.AddSpriteClip(2);
	guardMoveLeft.AddSpriteClip(3);

	guard.SetAnimMoveRight(&guardMoveRight);
	guardMoveRight.loops = true;
	guardMoveRight.SetAnimSpeed(10);
	guardMoveRight.AddSpriteClip(12);
	guardMoveRight.AddSpriteClip(13);

// END GUARD 

// Must come after all entities have been added to their layers
	lLivingThings.CollideWith(player);
	lLivingThings.CollideWith(boulder);
	lLivingThings.CollideWith(guard);
	lLivingThings.CollideWith(target);
	lLivingThings.CollideWith(tree);
	lLivingThings.CollideWith(playerWeapon);
	lMoveTriggers.CollideWith(player);

	//TODO: Don't hard-code this...
	gWorld.InitWorldGrid({ 0, 70 - 35, 14, 70 - 16});
}


bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup();
	if (initSuccess) {
		InitEntities();
	}

	return initSuccess;
}

void GameManager::Cleanup(){
	sdlInit.CleanupSprite(player);
	sdlInit.CleanupSprite(tree);
	sdlInit.CleanupSprite(boulder);
	sdlInit.CleanupSprite(target);
	sdlInit.CleanupSprite(guard);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	tree.Update();
	target.Update();
	boulder.Update();
	guard.Update();
	player.Update();

	//Needs to come last...
	gCamera.LookAt(player);

	//gCamera.RestrictTargetToWorld(player);

	sdlInit.Update();
}

void GameManager::Render(){
	sdlInit.Render();

	sdlInit.DrawSprite(tree);
	sdlInit.DrawSprite(target);
	sdlInit.DrawSprite(guard);
	sdlInit.DrawSprite(boulder);
	sdlInit.DrawSprite(player);

	//Needs to come last...
	if (SHOW_COLLIDERS) {
		sdlInit.DrawEntityCollider(moveTrigger);
		sdlInit.DrawEntityCollider(target);
		sdlInit.DrawEntityCollider(tree);
		sdlInit.DrawEntityCollider(boulder);
		sdlInit.DrawEntityCollider(player);
		sdlInit.DrawEntityCollider(playerWeapon);
		sdlInit.DrawEntityCollider(guard);
	}
}
