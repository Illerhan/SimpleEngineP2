#pragma once
#include "Actor.h"
class FollowActor : public Actor
{
public:
	FollowActor();

	void actorInput(const InputState& inputState) override;
	void setVisible(bool isVisibleP);
	void setSpeed(float speedP);
	void fixCollisions();
	void updateActor(float dt) override;
	void shoot();

private:
	class MoveComponent* moveComponent;
	class FollowCameraComponent* cameraComponent;
	class MeshComponent* meshComponent;
	float speed;
	class BoxComponent* boxComponent;
};

