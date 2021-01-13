#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <QVector3D>
#include <GameObjects/transform.h>

class BoxCollider
{
public:
    BoxCollider(QVector3D size, QVector3D anchorPos);
    BoxCollider(Transform *t, QVector3D size, QVector3D anchorPos);

    bool Collision(BoxCollider* other, QVector3D *collisionOffSet);
    bool CollisionX(BoxCollider* other, QVector3D *collisionOffSet);
    bool CollisionY(BoxCollider* other, QVector3D *collisionOffSet);
    bool CollisionZ(BoxCollider* other, QVector3D *collisionOffSet);

    QVector3D getSize();
    void setSize(QVector3D t);

    Transform *getTransform() const;

    QVector3D getAnchorPos() const;
    void setAnchorPos(const QVector3D &value);

private:
    QVector3D size;
    QVector3D anchorPos;
    Transform *transform;
};

#endif // BOXCOLLIDER_H
