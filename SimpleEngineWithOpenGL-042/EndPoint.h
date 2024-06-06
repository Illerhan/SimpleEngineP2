#pragma once
#include "Actor.h"

class EndPoint : public Actor
{
public:
    EndPoint();
    ~EndPoint();
    class BoxComponent* getBox() { return box; }

private:
    class BoxComponent* box;
};
