#ifndef ASTRONOMICALBODYOBJECT_H
#define ASTRONOMICALBODYOBJECT_H

#include "GameObjects/meshobject.h"

class AstronomicalBodyObject : public MeshObject
{
public:
    AstronomicalBodyObject(std::string & modelName, QString textureName, float orbitalRadius = 0, float orbitalInclination = 0, float axialTilt = 0, float revolutionAngleVelocity = 0);
    AstronomicalBodyObject(std::string & modelName, QString textureName, Transform* transform, float orbitalRadius = 0, float orbitalInclination = 0, float axialTilt = 0, float revolutionAngleVelocity = 0);

    void Start() override;
    void Update() override;

private :
    float orbitalRadius;
    float orbitalInclination;
    float axialTilt;
    float revolutionAngleVelocity;
};

#endif // ASTRONOMICALBODYOBJECT_H
