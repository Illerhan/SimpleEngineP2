#include "FPSActor.h"
#include "MoveComponent.h"
#include "Game.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "BallActor.h"
#include "BoxComponent.h"
#include "Collisions.h"
#include "ElevatorDoor.h"

FPSActor::FPSActor() : 
	Actor(), 
	moveComponent(nullptr), 
	audioComponent(nullptr), 
	meshComponent(nullptr),
	cameraComponent(nullptr),
	lastFootstep(0.0f),
	boxComponent(nullptr),
	HP(4)
{
	moveComponent = new MoveComponent(this);
	cameraComponent = new FPSCameraComponent(this);


	FPSModel = new Actor();
	FPSModel->setScale(Vector3(0.75f,0.75f,0.75f));
	meshComponent = new MeshComponent(FPSModel);
	meshComponent->setMesh(Assets::getMesh("Mesh_Rifle"));

	boxComponent = new BoxComponent(this);
	AABB collision(Vector3(-25.0f, -25.0f, -87.5f), Vector3(25.0f, 25.0f, 87.5f));
	boxComponent->setObjectBox(collision);
	boxComponent->setShouldRotate(false);
}

void FPSActor::resolveCollision(const AABB& playerBox, const AABB& otherBox, Vector3& pos) {
	// Calculate all our differences
	float dx1 = otherBox.max.x - playerBox.min.x;
	float dx2 = otherBox.min.x - playerBox.max.x;
	float dy1 = otherBox.max.y - playerBox.min.y;
	float dy2 = otherBox.min.y - playerBox.max.y;
	float dz1 = otherBox.max.z - playerBox.min.z;
	float dz2 = otherBox.min.z - playerBox.max.z;

	// Set dx to whichever of dx1/dx2 have a lower abs
	float dx = Maths::abs(dx1) < Maths::abs(dx2) ? dx1 : dx2;
	// Ditto for dy
	float dy = Maths::abs(dy1) < Maths::abs(dy2) ? dy1 : dy2;
	// Ditto for dz
	float dz = Maths::abs(dz1) < Maths::abs(dz2) ? dz1 : dz2;

	// Whichever is closest, adjust x/y position
	if (Maths::abs(dx) <= Maths::abs(dy) && Maths::abs(dx) <= Maths::abs(dz)) {
		pos.x += dx;
	} else if (Maths::abs(dy) <= Maths::abs(dx) && Maths::abs(dy) <= Maths::abs(dz)) {
		pos.y += dy;
	} else {
		pos.z += dz;
	}
}

void FPSActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	// Play the footstep if we're moving and haven't recently
	lastFootstep -= dt;
	if (!Maths::nearZero(moveComponent->getForwardSpeed()) && lastFootstep <= 0.0f)
	{
		lastFootstep = 0.5f;
	}
	
	// Update position and rotation of model relatively to position
	Vector3 modelPosition = getPosition();
	modelPosition += getForward() * MODEL_OFFSET.x;
	modelPosition += getRight() * MODEL_OFFSET.y;
	modelPosition.z += MODEL_OFFSET.z;
	FPSModel->setPosition(modelPosition);
	Quaternion q = getRotation();
	q = Quaternion::concatenate(q, Quaternion(getRight(), cameraComponent->getPitch()));
	FPSModel->setRotation(q);

	fixCollisions();
}

void FPSActor::actorInput(const InputState& inputState)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;
	// wasd movement
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_W))
	{
		forwardSpeed += 1000.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_S))
	{
		forwardSpeed -= 1000.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
	{
		strafeSpeed -= 1000.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
	{
		strafeSpeed += 1000.0f;
	}
	
	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setStrafeSpeed(strafeSpeed);
	// Mouse mouvement
	Vector2 mousePosition = inputState.mouse.getPosition();
	float x = mousePosition.x;
	float y = mousePosition.y;
	const int maxMouseSpeed = 500;
	const float maxAngularSpeed = Maths::pi * 8;
	float angularSpeed = 0.0f;
	if (x != 0)
	{
		angularSpeed = x / maxMouseSpeed;
		angularSpeed *= maxAngularSpeed;
	}
	moveComponent->setAngularSpeed(angularSpeed);
	const float maxPitchSpeed = Maths::pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		pitchSpeed = y / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	cameraComponent->setPitchSpeed(pitchSpeed);

	// Shoot
	if (inputState.mouse.getButtonState(1) == ButtonState::Pressed)
	{
		shoot();
	}
	if (inputState.keyboard.getKeyState(SDL_SCANCODE_L) == ButtonState::Pressed)
	{
		loseHP();
		std::cout << HP << std::endl;
	}

	
}

void FPSActor::shoot()
{
	// Get start point (in center of screen on near plane)
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	Vector3 start = getGame().getRenderer().unproject(screenPoint);
	// Get end point (in center of screen, between near and far)
	screenPoint.z = 0.9f;
	Vector3 end = getGame().getRenderer().unproject(screenPoint);
	// Get direction vector
	Vector3 dir = end - start;
	dir.normalize();
	// Spawn a ball
	BallActor* ball = new BallActor();
	ball->setPlayer(this);
	ball->setPosition(start + dir * 20.0f);
	// Rotate the ball to face new direction
	ball->rotateToNewForward(dir);
	// Play shooting sound
}

void FPSActor::setFootstepSurface(float value)
{
	// Pause here because the way I setup the parameter in FMOD
	// changing it will play a footstep

}

void FPSActor::setVisible(bool isVisible)
{
	meshComponent->setVisible(isVisible);
}

void FPSActor::fixCollisions() {
	// Need to recompute world transform to update world box
	computeWorldTransform();

	const AABB& playerBox = boxComponent->getWorldBox();
	Vector3 pos = getPosition();

	// Check collisions with planes
	auto& planes = getGame().getPlanes();
	for (auto pa : planes) {
		const AABB& planeBox = pa->getBox()->getWorldBox();
		if (Collisions::intersect(playerBox, planeBox)) {
			resolveCollision(playerBox, planeBox, pos);
		}
	}

	// Check collisions with cubes
	const auto& cubes = getGame().getCubes();
	for (const auto& cube : cubes) {
		const AABB& cubeBox = cube->getBox()->getWorldBox();
		if (Collisions::intersect(playerBox, cubeBox)) {
			resolveCollision(playerBox, cubeBox, pos);
		}
	}

	const auto& doors = getGame().getDoors();
	for (const auto& door : doors) {
		const AABB& doorBox = door->getBox()->getWorldBox();
		if (Collisions::intersect(playerBox, doorBox)) {
			resolveCollision(playerBox, doorBox, pos);
		}
	}

	const auto& end = getGame().getEnd();
		const AABB& endBox = end->getBox()->getWorldBox();
		if (Collisions::intersect(playerBox, endBox)) {
			std::cout << "Collide with end gg !" << std::endl;
			finished = true;
		}

	

	// Update position and box component
	setPosition(pos);
	boxComponent->onUpdateWorldTransform();


}

void FPSActor::loseHP()
{
	setHP(HP-=1);
}

void FPSActor::setHP(int sHP)
{
	HP = sHP;
}

void FPSActor::setFinished(bool ended)
{
	finished = ended;
}
