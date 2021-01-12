#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H


class BoxCollider
{
public:
    BoxCollider();
    BoxCollider(int x, int y, int z, int h, int d, int w);
    bool Collision(BoxCollider box1, BoxCollider box2);
    bool CollisionUp(BoxCollider box1, BoxCollider box2);
    bool CollisionLeft(BoxCollider box1, BoxCollider box2);
    bool CollisionDown(BoxCollider box1, BoxCollider box2);
    bool CollisionRight(BoxCollider box1, BoxCollider box2);

    float x,y,z;
    float w,h,d;
};

#endif // BOXCOLLIDER_H
