#include "pointlightobject.h"

PointLightObject::PointLightObject()
{
    light = new PointLight();
}

PointLight* PointLightObject::getLight()
{
    return light;
}
