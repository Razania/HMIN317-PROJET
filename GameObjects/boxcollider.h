#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
class BoxCollider;
#include <QVector3D>
#include <GameObjects/transform.h>

class BoxCollider
{
public:
    BoxCollider();
    BoxCollider(Transform *t, QVector3D size);
    bool Collision(BoxCollider box1, BoxCollider box2);
    bool CollisionUp(BoxCollider box1, BoxCollider box2);
    bool CollisionLeft(BoxCollider box1, BoxCollider box2);
    bool CollisionDown(BoxCollider box1, BoxCollider box2);
    bool CollisionRight(BoxCollider box1, BoxCollider box2);
    bool CollisionFront(BoxCollider box1, BoxCollider box2);
    bool CollisionBack(BoxCollider box1, BoxCollider box2);
    QVector3D getPos();
    QVector3D getSize();
    void setPos(QVector3D t);
    void setTransform(Transform* t);
    void setSize(QVector3D t);
private:
    QVector3D pos;
    QVector3D size;
    Transform* transform;
};

#endif // BOXCOLLIDER_H
