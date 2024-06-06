#pragma once
#include "CubeActor.h"

class ElevatorDoor : public CubeActor
{
public:
    ElevatorDoor();
    ~ElevatorDoor();
    class BoxComponent* getBox() { return box; }
    class MoveComponent* getMove() {return moveC;}

private:
    class BoxComponent* box;
    class MoveComponent* moveC;
};
