#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "GameObjects/transform.h"

#include <QVector3D>
#include <QElapsedTimer>



class RigidBody
{
public:
    RigidBody(Transform* body);

    void updateBody();
    void applyGravity();

    QVector3D getVelocity() const;
    void setVelocity(const QVector3D &value);
    void addVelocity(const QVector3D &value);

    QVector3D getForce() const;
    void setForce(const QVector3D &value);
    void addForce(const QVector3D &value);

    float getGravity() const;
    void setGravity(float value);

    float getMass() const;
    void setMass(float value);

    float getMaxSpeed() const;
    void setMaxSpeed(float value);

    float getDampeningRation() const;
    void setDampeningRation(float value);

    float getMinimalElapsedTime() const;
    void setMinimalElapsedTime(float value);

    void initTimer();

    void revertLastMovement(QVector3D revertAxis);

private:
    QVector3D velocity;
    QVector3D force;
    float gravity;
    float mass;
    float dampeningRation;

    float maxSpeed;

    float minimalElapsedTime;

    QElapsedTimer timer;

    QVector3D lastMovement;

    Transform* body;
};

#endif // RIGIDBODY_H
