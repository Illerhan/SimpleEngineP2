#pragma once
#include "CameraComponent.h"
class FPSCameraComponent :
    public CameraComponent
{
public:
    FPSCameraComponent(Actor* ownerP);

    void update(float dt) override;

    float getPitch() const { return pitch; }
    float getPitchSpeed() const { return pitchSpeed; }
    float getMaxPitch() const { return maxPitch; }

    void setPitchSpeed(float speed);
    void setMaxPitch(float pitch);

private:
    // Rotation/sec speed of pitch
    float pitchSpeed;
    // Maximum pitch deviation from for ward
    float maxPitch;
    // Current maxPitch
    float pitch;
};

