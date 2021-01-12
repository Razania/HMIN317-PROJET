#ifndef POINTLIGHTOBJECT_H
#define POINTLIGHTOBJECT_H

#include "gameobject.h"
#include "Misc/Generic.h"

class PointLightObject : public GameObject
{
public:
    PointLightObject();

    PointLight* getLight();

private:
    PointLight* light;
};

#endif // POINTLIGHTOBJECT_H
