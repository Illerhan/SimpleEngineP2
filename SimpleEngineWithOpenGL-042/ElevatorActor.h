#pragma once
#include "Actor.h"

class ElevatorActor : public Actor
{
public:
    ElevatorActor();
    ~ElevatorActor();
    class BoxComponent* getBox() { return box; }

private:
    class BoxComponent* box;
};
