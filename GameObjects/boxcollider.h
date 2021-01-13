#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <QVector3D>
#include <GameObjects/transform.h>

class BoxCollider
{
public:
    BoxCollider();
    BoxCollider(Transform *t, QVector3D size);

    bool Collision(BoxCollider other, QVector3D *collisionOffSet);
    bool CollisionX(BoxCollider other, QVector3D *collisionOffSet);
    bool CollisionY(BoxCollider other, QVector3D *collisionOffSet);
    bool CollisionZ(BoxCollider other, QVector3D *collisionOffSet);

    QVector3D getSize();
    void setSize(QVector3D t);

    Transform *getTransform() const;

private:
    QVector3D size;
    Transform *transform;
};

#endif // BOXCOLLIDER_H
