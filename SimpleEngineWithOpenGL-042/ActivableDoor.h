#pragma once
#include "CubeActor.h"

class ActivableDoor : public CubeActor
{
public:
    ActivableDoor();
    ~ActivableDoor();
    class BoxComponent* getBox() { return box; }

private:
    class BoxComponent* box;
};
