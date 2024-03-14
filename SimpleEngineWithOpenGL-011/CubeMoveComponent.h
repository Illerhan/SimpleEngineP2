#pragma once
#include "MoveComponent.h"
class CubeMoveComponent : public MoveComponent
{
public:
    CubeMoveComponent(class Actor* ownerP);

    void setArrow(class Actor* arrowP);
    Actor* getArrow() const{ return arrow;}
    
    void update(float dt) override;

protected:
    class Actor* arrow;
    
};

