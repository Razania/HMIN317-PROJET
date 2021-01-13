#ifndef TRANSFORM_H
#define TRANSFORM_H

class GameObject;

#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>
#include <GameObjects/gameobject.h>

class Transform
{
    public:
        Transform(GameObject* gameObject, QVector3D localPosition = QVector3D(0,0,0), QQuaternion localRotation = QQuaternion(), QVector3D localScale = QVector3D(1,1,1));
        Transform(GameObject* gameObject, Transform* parentNode, QVector3D localPosition = QVector3D(0,0,0), QQuaternion localRotation = QQuaternion(), QVector3D localScale = QVector3D(1,1,1));

        Transform* getParent() { return this->parentNode; }
        void setParent(Transform* parentNode);

        std::vector<Transform*> getChilds(){ return childs; }
        void addChild(Transform* child);
        void removeChild(Transform* child);

        QVector3D getLocalPosition(){ return this->localPosition; }
        QQuaternion getLocalRotation(){ return this->localRotation; }
        QVector3D getLocalRotationEuleurAngles(){ return this->localRotation.toEulerAngles(); }
        QVector3D getLocalScale(){ return this->localScale; }

        void setLocalPosition(QVector3D newLocalPosition){ this->localPosition = newLocalPosition; }
        void setLocalRotation(QQuaternion newLocalRotation){ this->localRotation = newLocalRotation; }
        void setLocalScale(QVector3D newLocalScale){ this->localScale = newLocalScale; }

        QVector3D getWorldPosition();

        QMatrix4x4 worldMatrix();

        GameObject* gameObject;

    private:
        Transform* parentNode;
        std::vector<Transform*> childs;
        QVector3D localPosition;
        QQuaternion localRotation;
        QVector3D localScale;
};
#endif // TRANSFORM_H
