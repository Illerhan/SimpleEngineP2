#pragma once
#include "Actor.h"
#include "ElevatorActor.h"
#include "ShootButton.h"

class BallActor : public Actor
{
public:
	BallActor();

	void updateActor(float dt) override;
	void setPlayer(Actor* player);
	void hitTarget(ShootButton* button);
	void hitElevator();

private:
	class AudioComponent* audio;
	class BallMoveComponent* ballMove;
	float lifetimeSpan;
};

