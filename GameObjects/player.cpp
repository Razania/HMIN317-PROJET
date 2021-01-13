#include "player.h"

Player::Player()
{
    camera = new Camera(this->transform->getWorldPosition() + QVector3D(0,1.5,0), QVector3D(0,0,-1), QVector3D(0,0,0), QVector3D(0,1,0));
    rigidbody = new RigidBody(this->transform);
    boxCollider = new BoxCollider(transform, QVector3D(1,2,1));
}

void Player::Update(){
    camera->setCameraPosition(this->transform->getWorldPosition() + QVector3D(0,1.5,0));
    this->transform->setLocalRotation(QQuaternion::fromEulerAngles(0,this->getCamera()->getCameraRotation().y(),0));

    rigidbody->applyGravity();
    rigidbody->updateBody();
}

RigidBody *Player::getRigidbody() const
{
    return rigidbody;
}

Camera *Player::getCamera() const
{
    return camera;
}

BoxCollider *Player::getBoxCollider() const
{
    return boxCollider;
}
