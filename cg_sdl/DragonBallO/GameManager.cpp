#include "GameManager.h"
#include "SDLInit.h"
#include "World.h"
#include "Player.h"
#include "Camera.h"
#include "MoveTrigger.h"
#include "LivingThing.h"

#define CAMERA_MODE Camera::Mode::PAN
#define SHOW_COLLIDERS false

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
	MoveTrigger moveTrigger;
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

	player.AddCollidableEntity(tree);
	player.AddCollidableEntity(boulder);
	player.AddCollidableEntity(moveTrigger);
	player.AddCollidableEntity(target);

//END PLAYER

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

//END BOULDER

//MOVETRIGGER

	//position
	moveTrigger.SetPosition({ 300, 150 });

	//size
	moveTrigger.SetSize(45, 45);

	//collision
	moveTrigger.ConfigureCollision(false, false);

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
	target.SetAnchorOffset({ 0, -13 }, 0);

	//animation
	target.animIdle = false;

	//Health
	target.Destructible::SetHealth(3, 3);

	//position
	target.SetPosition({990 , 200 });

	//size
	target.SetSize(50, 50);

	//collision
	target.ConfigureCollision(true, false);

//END TARGET

	

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
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	tree.Update();
	target.Update();
	boulder.Update();
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
	sdlInit.DrawSprite(boulder);
	sdlInit.DrawSprite(player);

	//Needs to come last...
	if (SHOW_COLLIDERS) {
		sdlInit.DrawEntityCollider(moveTrigger);
		sdlInit.DrawEntityCollider(target);
		sdlInit.DrawEntityCollider(tree);
		sdlInit.DrawEntityCollider(boulder);
		sdlInit.DrawEntityCollider(player);
	}
}