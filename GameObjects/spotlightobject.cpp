#include "spotlightobject.h"

SpotLightObject::SpotLightObject()
{
    light = new SpotLight();
}

SpotLight* SpotLightObject::getLight()
{
    return light;
}
