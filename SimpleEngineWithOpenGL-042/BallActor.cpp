#include "BallActor.h"

#include <valarray>

#include "MeshComponent.h"
#include "Assets.h"

#include "BallMoveComponent.h"
#include "Game.h"

BallActor::BallActor() : Actor(), lifetimeSpan(2.0f), audio(nullptr), ballMove(nullptr)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
	ballMove = new BallMoveComponent(this);
	ballMove->setForwardSpeed(1500.0f);
}

void BallActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	lifetimeSpan -= dt;
	if (lifetimeSpan < 0.0f)
	{
		setState(ActorState::Dead);
	}
}

void BallActor::setPlayer(Actor* player)
{
	ballMove->setPlayer(player);
}

void BallActor::hitTarget(ShootButton* button)
{
	std::cout << button->getPosition().x << std::endl;
	button->getDoor()->setState(ActorState::Dead);
}
