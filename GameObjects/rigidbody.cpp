#include "rigidbody.h"
#include <algorithm>
#include <math.h>

RigidBody::RigidBody(Transform* body) : body(body)
{
    timer.start();

    this->setForce(QVector3D(0,0,0));
    this->setVelocity(QVector3D(0,0,0));

    this->setGravity(9.71);
    this->setMass(30);
    this->setMaxSpeed(5);
    this->setDampeningRation(0.25f);
}

void RigidBody::updateBody()
{
    float elapsedTime = ((float) timer.elapsed()) / 1000.0f; //Get Elapsed Time

    qDebug("force(%f, %f, %f) to apply in %f seconds", this->getForce().x(), this->getForce().y(), this->getForce().z(), elapsedTime);

    //MAJ vélocité
    QVector3D scaledForces = (this->getForce() / this->getMass()) * elapsedTime;
    this->setVelocity(this->getVelocity() / (1 + (log10(1 + this->getDampeningRation())))); //Dampening
    this->addVelocity(scaledForces);

    this->setForce(QVector3D(0,0,0));

    //MAJ position body
    QVector3D bodyMovement = this->getVelocity();

    qDebug("velocity(%f, %f, %f)", bodyMovement.x(), bodyMovement.y(), bodyMovement.z());

        //Check Speed
    if(bodyMovement.length() > this->getMaxSpeed())
        bodyMovement *= (this->getMaxSpeed() / bodyMovement.length());

        //TimeScale Movement
    bodyMovement *= elapsedTime;
        //Apply Movement
    qDebug("oldPosition(%f, %f, %f)", body->getLocalPosition().x(), body->getLocalPosition().y(), body->getLocalPosition().z());
    body->setLocalPosition(body->getLocalPosition() + bodyMovement);
    qDebug("newPosition(%f, %f, %f)\n", body->getLocalPosition().x(), body->getLocalPosition().y(), body->getLocalPosition().z());


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
