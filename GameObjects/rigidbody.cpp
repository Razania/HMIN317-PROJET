#include "rigidbody.h"
#include <algorithm>
#include <math.h>

RigidBody::RigidBody(Transform* body) : body(body)
{
    timer.start();

    this->setForce(QVector3D(0,0,0));
    this->setVelocity(QVector3D(0,0,0));

    this->setGravity(9.71);
    this->setMass(10);
    this->setMaxSpeed(5);
    this->setDampeningRation(0.25f);
    this->setMinimalElapsedTime(0.05f);
}

void RigidBody::updateBody()
{
    float elapsedTime = ((float) timer.elapsed()) / 1000.0f; //Get Elapsed Time

    if(elapsedTime < 0.03f)
        return;

    //qDebug("velocity(%f, %f, %f)", this->getVelocity().x(), this->getVelocity().y(), this->getVelocity().z());
    //qDebug("force(%f, %f, %f) to apply in %f seconds", this->getForce().x(), this->getForce().y(), this->getForce().z(), elapsedTime);

    //MAJ vélocité
    QVector3D scaledForces = (this->getForce() / this->getMass()) * elapsedTime;
        //Dampening
    QVector3D dampenedVelocity = this->getVelocity() / ((1 + (log10(1 + this->getDampeningRation()))) * elapsedTime);
    this->setVelocity(dampenedVelocity);
    //qDebug("velocity(%f, %f, %f)", this->getVelocity().x(), this->getVelocity().y(), this->getVelocity().z());

    this->addVelocity(scaledForces);
    //qDebug("velocity(%f, %f, %f)", this->getVelocity().x(), this->getVelocity().y(), this->getVelocity().z());

    this->setForce(QVector3D(0,0,0));

    //MAJ position body
    QVector3D bodyMovement = this->getVelocity();

    //qDebug("velocity(%f, %f, %f)", bodyMovement.x(), bodyMovement.y(), bodyMovement.z());

        //Check Speed
    QVector3D bodyMovementXZ = QVector3D(this->getVelocity().x(), 0, this->getVelocity().z());
    if(bodyMovementXZ.length() > this->getMaxSpeed())
        bodyMovementXZ *= (this->getMaxSpeed() / bodyMovement.length());

    bodyMovement = QVector3D(bodyMovementXZ.x(), bodyMovement.y(), bodyMovementXZ.z());

        //TimeScale Movement
    bodyMovement *= elapsedTime;
        //Apply Movement
    lastMovement = bodyMovement;
    //qDebug("oldPosition(%f, %f, %f)", body->getLocalPosition().x(), body->getLocalPosition().y(), body->getLocalPosition().z());
    body->setLocalPosition(body->getLocalPosition() + bodyMovement);
    //qDebug("newPosition(%f, %f, %f)\n", body->getLocalPosition().x(), body->getLocalPosition().y(), body->getLocalPosition().z());

    timer.start(); //Restart Timer
}

void RigidBody::applyGravity()
{
    //MAJ Gravité
    if(this->body->getLocalPosition().y() > 0){
        QVector3D scaledGravity = QVector3D(0, -(this->getGravity() * this->getMass()), 0);
        this->addForce(scaledGravity);
    }else{
        this->velocity.setY(0);
    }
}


QVector3D RigidBody::getVelocity() const
{
    return velocity;
}

void RigidBody::setVelocity(const QVector3D &value)
{
    velocity = value;
}

void RigidBody::addVelocity(const QVector3D &value)
{
    velocity += value;
}

QVector3D RigidBody::getForce() const
{
    return force;
}

void RigidBody::setForce(const QVector3D &value)
{
    force = value;
}

void RigidBody::addForce(const QVector3D &value)
{
    force += value;
}

float RigidBody::getGravity() const
{
    return gravity;
}

void RigidBody::setGravity(float value)
{
    gravity = value;
}

float RigidBody::getMass() const
{
    return mass;
}

void RigidBody::setMass(float value)
{
    mass = value;
}

float RigidBody::getMaxSpeed() const
{
    return maxSpeed;
}

void RigidBody::setMaxSpeed(float value)
{
    maxSpeed = value;
}

float RigidBody::getDampeningRation() const
{
    return dampeningRation;
}

void RigidBody::setDampeningRation(float value)
{
    dampeningRation = value;
}

float RigidBody::getMinimalElapsedTime() const
{
    return minimalElapsedTime;
}

void RigidBody::setMinimalElapsedTime(float value)
{
    minimalElapsedTime = value;
}

void RigidBody::initTimer()
{
    timer.start();
}

void RigidBody::revertLastMovement(QVector3D revertAxis)
{
    body->setLocalPosition(body->getLocalPosition() - lastMovement);

}
