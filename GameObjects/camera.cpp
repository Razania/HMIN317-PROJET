#include <GameObjects/camera.h>
#include <Qt3DCore/QTransform>
#include <QOpenGLWidget>
#include <algorithm>
#include <cstdint>
#include <QOpenGLFunctions_3_1>
//Constructors
Camera::Camera(QVector3D position, QVector3D front, QVector3D target, QVector3D Up)
    : cameraMode(this->CAMERA_MODE_STATIONARY), cameraPosition(position), cameraFront(front),  cameraTarget(target), cameraUp(Up)
{}

//Functions
void Camera::setCameraToStationaryMode(){ this->cameraMode = this->CAMERA_MODE_STATIONARY; }
void Camera::setCameraToOrbitalMode(){
    this->CAMERA_MODE_radius = (this->getCameraPosition() - this->getCameraTarget()).length();
    this->cameraMode = this->CAMERA_MODE_ORBITAL;
    this->CAMERA_MODE_timer.start();
}

QVector3D Camera::getCameraDirection(){
    if(this->getCameraMode() == this->CAMERA_MODE_ORBITAL)
        return (this->getCameraTarget() - this->getCameraPosition()).normalized();

    QQuaternion rot = QQuaternion::fromAxisAndAngle(0,1,0,this->getCameraRotation().y());
    return rot.rotatedVector(this->getCameraFront());
}
QVector3D Camera::getCameraRight(){
    if(this->getCameraDirection().z() < 0)
        return -(QVector3D::crossProduct(this->getCameraUp(), this->getCameraDirection())).normalized();
    QQuaternion rot = QQuaternion::fromAxisAndAngle(0,1,0,this->getCameraRotation().y());
    return rot.rotatedVector((QVector3D::crossProduct(this->getCameraUp(), this->getCameraDirection())).normalized());
}

QMatrix4x4 Camera::getViewMatrix(){
    QMatrix4x4 view = QMatrix4x4();
    view.lookAt(this->getCameraPosition() + QVector3D(0,0,0), this->getCameraPosition() + this->getCameraDirection(), this->getCameraUp());

    return view;
}

QMatrix4x4 Camera::getOriginViewMatrix(){
    QMatrix4x4 view = QMatrix4x4();
    view.lookAt(QVector3D(0,0,0), this->getCameraDirection(), this->getCameraUp());

    return view;
}


//Base Getters/Setters
QVector3D Camera::getCameraPosition() const
{
    QVector3D cameraPos = this->cameraPosition;

    if(this->getCameraMode() == this->CAMERA_MODE_ORBITAL){
        cameraPos = ((this->CAMERA_MODE_radius) * (cameraPos - this->getCameraTarget()).normalized()) + this->getCameraTarget();
        cameraPos -= this->getCameraTarget();

        QTime now; now.start();
        QQuaternion rotation = QQuaternion::fromAxisAndAngle(QVector3D(1,0,0), -45);
        cameraPos = rotation.rotatedVector(cameraPos);
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(0,1,0), ((float )this->CAMERA_MODE_timer.msecsTo(now))/(100));
        cameraPos = rotation.rotatedVector(cameraPos);

        cameraPos += this->getCameraTarget();
    }

    return cameraPos;
}

void Camera::setCameraPosition(const QVector3D &value)
{
    if(this->getCameraMode() == this->CAMERA_MODE_ORBITAL)
        return;
    cameraPosition = value;
}

QVector3D Camera::getCameraTarget() const
{
    return cameraTarget;
}

void Camera::setCameraTarget(const QVector3D &value)
{
    cameraTarget = value;
}

QVector3D Camera::getCameraUp() const
{


    return cameraUp;
}

void Camera::setCameraUp(const QVector3D &value)
{
    cameraUp = value;
}

QVector3D Camera::getCameraFront() const
{
    QQuaternion rot = QQuaternion::fromAxisAndAngle(1,0,0,this->getCameraRotation().x());
    return rot.rotatedVector(cameraFront);
}

void Camera::setCameraFront(const QVector3D &value)
{
    cameraFront = value;
}

QVector3D Camera::getCameraRotation() const
{
    return cameraRotation;
}

void Camera::setCameraRotation(const QVector3D &value)
{
    QVector3D newRot = value;
    if(newRot.x() < -89)
        newRot.setX(-89);
    if(newRot.x() > 89)
        newRot.setX(89);

    newRot.setZ(0);

    cameraRotation = newRot;
}

int Camera::getCameraMode() const
{
    return cameraMode;
}
