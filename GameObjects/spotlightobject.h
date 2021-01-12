#ifndef SPOTLIGHTOBJECT_H
#define SPOTLIGHTOBJECT_H

#include "gameobject.h"
#include "Misc/Generic.h"

class SpotLightObject : public GameObject
{
public:
    SpotLightObject();

    SpotLight* getLight();

private:
    SpotLight* light;
};

#endif // SPOTLIGHTOBJECT_H
