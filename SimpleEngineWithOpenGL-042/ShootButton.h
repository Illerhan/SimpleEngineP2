#pragma once
#include "ActivableDoor.h"

class ShootButton : public Actor
{
    ~ShootButton();
    ShootButton() = default;
   
public:
     ShootButton(ActivableDoor* door);
private:
    ActivableDoor* door;

public:
    ActivableDoor* getDoor() {return door;}
};
