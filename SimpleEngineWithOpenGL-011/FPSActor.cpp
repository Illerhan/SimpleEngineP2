#include "FPSActor.h"
#include "MoveComponent.h"
#include "AudioComponent.h"
#include "Game.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "BallActor.h"
#include "BoxComponent.h"
#include "Collisions.h"
#include "CubeActor.h"


FPSActor::FPSActor() : 
	Actor(), 
	moveComponent(nullptr), 
	//audioComponent(nullptr), 
	meshComponent(nullptr),
	cameraComponent(nullptr),
	lastFootstep(0.0f),
	boxComponent(nullptr)
{
	moveComponent = new MoveComponent(this);
	//audioComponent = new AudioComponent(this);
	cameraComponent = new FPSCameraComponent(this);

	//footstep = audioComponent->playEvent("event:/Footstep");
	//footstep.setPaused(true);

	FPSModel = new Actor();
	FPSModel->setScale(Vector3(1.0f,0.75f,1.f));
	//meshComponent = new MeshComponent(FPSModel);
	//meshComponent->setMesh(Assets::getMesh("Mesh_Rifle"));

	boxComponent = new BoxComponent(this);
	AABB collision(Vector3(-25.0f, -25.0f, -87.5f), Vector3(25.0f, 25.0f, 87.5f));
	boxComponent->setObjectBox(collision);
	boxComponent->setShouldRotate(false);
}

void FPSActor::updateActor(float dt)
{
	Actor::updateActor(dt);
	delay-=1*dt;

	if(shootCount == 2 && delay <= 2)
	{
		CubeActor* scoring = new CubeActor(std::to_string(getGame().getScore()));
		scoring->setScale(Vector3(0.5,0.5,1));
		getGame().addCubes(scoring);
	}
	
	
	if (shootCount>=2 && delay <= 0)
	{
		getGame().deleteCubes(getGame().getCubes());
		getGame().initiateGame();
		shootCount=0;
		getGame().setScore(0);
	}
	if (delay <=0 && hasShoot)
	{
		hasShoot = false;
		
	}

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

	// Shoot
	if (delay <=0 && shootCount < 2)
	{
		if (inputState.mouse.getButtonState(1) == ButtonState::Pressed && dirSelected && powerSelected && !hasShoot)
		{
			shoot();
			getGame().getArrow()->setScale(Vector3(50.0f,10.0f,1.f));
			hasShoot = true;
			dirSelected = false;
			powerSelected = false;
			shootCount++;
			delay =7;
		}
		if (inputState.mouse.getButtonState(1)== ButtonState::Pressed && dirSelected && !powerSelected &&  !hasShoot)
		{
			powerSelected = true;
		}
		if (inputState.mouse.getButtonState(1)== ButtonState::Pressed && !dirSelected &&  !hasShoot)
		{
			dirSelected = true;
		}
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
	
	Vector3 dir = Vector3(getGame().getArrow()->getRotation().w,getGame().getArrow()->getRotation().z,0);
	dir.normalize();
	// Spawn a ball
	BallActor* ball = new BallActor();
	ball->setPlayer(this);
	ball->setArrow(getGame().getArrow());
	ball->setPosition(Vector3(-50,35,10));
	ball->setScale(Vector3(0.75,0.75,0.75));
	// Rotate the ball to face new direction
	ball->rotateToNewForward(dir);
	// Play shooting sound
	//audioComponent->playEvent("event:/Shot");
}

void FPSActor::setFootstepSurface(float value)
{
}

void FPSActor::setVisible(bool isVisible)
{
	meshComponent->setVisible(isVisible);
}

void FPSActor::fixCollisions()
{
	// Need to recompute world transform to update world box
	computeWorldTransform();

	const AABB& playerBox = boxComponent->getWorldBox();
	Vector3 pos = getPosition();

	auto& planes = getGame().getPlanes();
	for (auto pa : planes)
	{
		// Do we collide with this PlaneActor?
		const AABB& planeBox = pa->getBox()->getWorldBox();
		if (Collisions::intersect(playerBox, planeBox))
		{
			// Calculate all our differences
			float dx1 = planeBox.max.x - playerBox.min.x;
			float dx2 = planeBox.min.x - playerBox.max.x;
			float dy1 = planeBox.max.y - playerBox.min.y;
			float dy2 = planeBox.min.y - playerBox.max.y;
			float dz1 = planeBox.max.z - playerBox.min.z;
			float dz2 = planeBox.min.z - playerBox.max.z;

			// Set dx to whichever of dx1/dx2 have a lower abs
			float dx = Maths::abs(dx1) < Maths::abs(dx2) ? dx1 : dx2;
			// Ditto for dy
			float dy = Maths::abs(dy1) < Maths::abs(dy2) ? dy1 : dy2;
			// Ditto for dz
			float dz = Maths::abs(dz1) < Maths::abs(dz2) ? dz1 : dz2;

			// Whichever is closest, adjust x/y position
			if (Maths::abs(dx) <= Maths::abs(dy) && Maths::abs(dx) <= Maths::abs(dz))
			{
				pos.x += dx;
			}
			else if (Maths::abs(dy) <= Maths::abs(dx) && Maths::abs(dy) <= Maths::abs(dz))
			{
				pos.y += dy;
			}
			else
			{
				pos.z += dz;
			}

			// Need to set position and update box component
			setPosition(pos);
			boxComponent->onUpdateWorldTransform();
		}
	}
}
