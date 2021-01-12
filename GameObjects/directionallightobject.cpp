#include "directionallightobject.h"

DirectionalLightObject::DirectionalLightObject()
{
    light = new DirectionalLight();
}

DirectionalLight* DirectionalLightObject::getLight()
{
    return light;
}
