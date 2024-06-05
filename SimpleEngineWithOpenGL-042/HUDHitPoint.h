#pragma once
#include "UIScreen.h"

class HUDHitPoint : public UIScreen
{
public:
    HUDHitPoint();
    ~HUDHitPoint();

    void draw(class Shader& shader) override;

protected:
    class Texture* hitPoint;
    class Texture* hitPoint2;
    class Texture* hitPoint3;
    class Texture* hitPoint4;

};
