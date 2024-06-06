#pragma once
#include "UIScreen.h"

class HUDHitPoint : public UIScreen
{
public:
    HUDHitPoint();
    ~HUDHitPoint();
    void update(float dt) override;

    void draw(class Shader& shader) override;
    void updateHP(float dt);

protected:
    class Texture* hitPoint;
    class Texture* hitPoint2;
    class Texture* hitPoint3;
    class Texture* hitPoint4;

};
