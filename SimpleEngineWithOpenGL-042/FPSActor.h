#pragma once
#include "AABB.h"
#include "Actor.h"
#include "Vector3.h"

class FPSActor : public Actor
{
public:
	FPSActor();
	void resolveCollision(const AABB& playerBox, const AABB& otherBox, Vector3& pos);

	void updateActor(float dt) override;
	void actorInput(const struct InputState& inputState) override;
	void shoot();

	void setFootstepSurface(float value);
	void setVisible(bool isVisible);
	void fixCollisions();
	void setHP();
	int getHP(){ return HP;}
	int getMaxHP(){ return maxHP;}

private:
	class MoveComponent* moveComponent;
	class AudioComponent* audioComponent;
	class MeshComponent* meshComponent;
	class FPSCameraComponent* cameraComponent;
	class Actor* FPSModel;
	float lastFootstep;
	class BoxComponent* boxComponent;
	int HP;
	int maxHP;
};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 10.0f, -10.0f);
