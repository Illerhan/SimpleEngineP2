#include "BallMoveComponent.h"
#include "Actor.h"
#include "Vector3.h"
#include "LineSegment.h"
#include "Collisions.h"
#include "PhysicsSystem.h"
#include "BallActor.h"
#include "TargetActor.h"
#include "Game.h"

BallMoveComponent::BallMoveComponent(Actor* ownerP) : MoveComponent(ownerP), player(nullptr), arrow(nullptr)
{
}

void BallMoveComponent::setPlayer(Actor* playerP)
{
	player = playerP;
}

void BallMoveComponent::setArrow(Actor* arrowP)
{
	arrow = arrowP;
}

void BallMoveComponent::update(float dt)
{
	// Construct segment in direction of travel
	const float segmentLength = 5.0f;
	Vector3 start = owner.getPosition();
	Vector3 dir = owner.getForward();
	Vector3 end = start + dir * segmentLength;
	
	// Create line segment
	LineSegment l(start, end);

	// Test segment vs world
	PhysicsSystem::CollisionInfo info;
	// (Don't collide vs player)
	if (owner.getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != player && info.actor != arrow)
	{
		CubeActor* target = dynamic_cast<CubeActor*>(info.actor);
		if (target && target !=arrow)
		{
			static_cast<BallActor*>(&owner)->hitTarget(target);
		}
	}

	// Base class update moves based on forward speed
	MoveComponent::update(dt);
}
