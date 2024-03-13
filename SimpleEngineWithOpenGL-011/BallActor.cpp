#include "BallActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "AudioComponent.h"
#include "BallMoveComponent.h"
#include "CubeActor.h"
#include "Game.h"

BallActor::BallActor() : Actor(), lifetimeSpan(20.0f), /*audio(nullptr),*/ ballMove(nullptr)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
	//audio = new AudioComponent(this);
	ballMove = new BallMoveComponent(this);
	ballMove->setForwardSpeed(5*getGame().getArrow()->getScale().x);
	std::cout << ballMove->getForwardSpeed() << "\n";
}

void BallActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	lifetimeSpan -= dt;
	// Friction
	ballMove->setForwardSpeed(ballMove->getForwardSpeed()*0.995);
	
	if (lifetimeSpan < 0.0f || ballMove->getForwardSpeed()<0  || ballMove->getOwner().getPosition().x >= 750)
	{
		setState(ActorState::Dead);
	}

	if (ballMove->getOwner().getPosition().y > 135 || ballMove->getOwner().getPosition().y < -50)
	{
		ballMove->getOwner().rotateToNewForward(Vector3::unitX);
	}
}

void BallActor::setPlayer(Actor* player)
{
	ballMove->setPlayer(player);
}

void BallActor::hitTarget()
{
	//audio->playEvent("event:/Ding");
}
