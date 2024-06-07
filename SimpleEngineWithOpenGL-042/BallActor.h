#pragma once
#include "Actor.h"
#include "ShootButton.h"

class BallActor : public Actor
{
public:
	BallActor();

	void updateActor(float dt) override;
	void setPlayer(Actor* player);
	void hitTarget(ShootButton* button);


private:
	class AudioComponent* audio;
	class BallMoveComponent* ballMove;
	float lifetimeSpan;
};

