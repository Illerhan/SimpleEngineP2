#pragma once
#include "Actor.h"
class FPSActor :
    public Actor
{
public:
    FPSActor();

    void updateActor(float dt) override;
    void actorInput(const InputState& inputState) override;

    void setFootstepSurface(float value);
    void setVisible(bool isVisible);

private:
    class MoveComponent* moveComponent;
    class MeshComponent* meshComponent;
    class FPSCameraComponent* cameraComponent;
    class Actor* FPSModel;
    float lastFootstep;
};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 10.0f, -10.0f);

