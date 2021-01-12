#ifndef DIRECTIONALLIGHTOBJECT_H
#define DIRECTIONALLIGHTOBJECT_H

#include "gameobject.h"
#include "Misc/Generic.h"

class DirectionalLightObject : public GameObject
{
public:
    DirectionalLightObject();

    DirectionalLight* getLight();

private:
    DirectionalLight* light;
};

#endif // DIRECTIONALLIGHTOBJECT_H
