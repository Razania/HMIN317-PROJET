#include <GameObjects/astronomicalbodyobject.h>

AstronomicalBodyObject::AstronomicalBodyObject(std::string & modelName, QString textureName, float orbitalRadius, float orbitalInclination, float axialTilt, float revolutionAngleVelocity)
    : MeshObject(modelName, textureName), orbitalRadius(orbitalRadius), orbitalInclination(orbitalInclination), axialTilt(axialTilt), revolutionAngleVelocity(revolutionAngleVelocity)
{
    this->Start();
}

AstronomicalBodyObject::AstronomicalBodyObject(std::string & modelName, QString textureName, Transform* transform, float orbitalRadius, float orbitalInclination, float axialTilt, float revolutionAngleVelocity)
    : MeshObject(modelName, textureName, transform), orbitalRadius(orbitalRadius), orbitalInclination(orbitalInclination), axialTilt(axialTilt), revolutionAngleVelocity(revolutionAngleVelocity)
{
    this->Start();
}

void AstronomicalBodyObject::Start() {
    QQuaternion tiltRotation = QQuaternion::fromAxisAndAngle(QVector3D(1,0,0), this->axialTilt);
    this->transform->setLocalRotation(this->transform->getLocalRotation() * tiltRotation);

    this->transform->setLocalPosition(QVector3D(orbitalRadius,0,0));

    QQuaternion orbitalInclination = QQuaternion::fromAxisAndAngle(QVector3D(0,0,1), this->orbitalInclination);
    this->transform->setLocalPosition(orbitalInclination.rotatedVector(this->transform->getLocalPosition()));

    MeshObject::Start();
}

void AstronomicalBodyObject::Update() {
    QQuaternion revolutionRotation = QQuaternion::fromAxisAndAngle(QVector3D(0,1,0), this->revolutionAngleVelocity);
    this->transform->setLocalRotation(this->transform->getLocalRotation() * revolutionRotation); //On applique la révolution

    MeshObject::Update();
}
