#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QTime>
#include <QQuaternion>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_1>

class Camera
{
public:
    static const int CAMERA_MODE_STATIONARY = 0;
    static const int CAMERA_MODE_ORBITAL = 1;

    Camera(QVector3D position = QVector3D(0,0,0), QVector3D front = QVector3D(0,0,-1), QVector3D target = QVector3D(0,0,0), QVector3D Up = QVector3D(0,1,0));

    void setCameraToStationaryMode();
    void setCameraToOrbitalMode();

    QMatrix4x4 getViewMatrix();

    QVector3D getCameraDirection();
    QVector3D getCameraRight();

    //Base Getters/Setters
    int getCameraMode() const;
    void setCameraMode(int value);
    QVector3D getCameraPosition() const;
    void setCameraPosition(const QVector3D &value);
    QVector3D getCameraTarget() const;
    void setCameraTarget(const QVector3D &value);
    QVector3D getCameraUp() const;
    void setCameraUp(const QVector3D &value);
    QVector3D getCameraFront() const;
    void setCameraFront(const QVector3D &value);

    QVector3D getCameraRotation() const;
    void setCameraRotation(const QVector3D &value);

private:
    int cameraMode;
    QVector3D cameraPosition;
    QVector3D cameraFront;
    QVector3D cameraTarget;
    QVector3D cameraUp;

    QVector3D cameraRotation;

    //CAMERA_MODE_ORBITAL
    float CAMERA_MODE_radius;
    QTime CAMERA_MODE_timer;
};

#endif // CAMERA_H
