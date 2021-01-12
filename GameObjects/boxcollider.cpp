#include "boxcollider.h"

BoxCollider::BoxCollider()
{

}

BoxCollider::BoxCollider(Transform* t, QVector3D size)
{
    this->transform = t;
    this->pos = transform->getLocalPosition();
    this->size = size;
}

void BoxCollider::setTransform(Transform* t)
{
    this->transform = t;

}

QVector3D BoxCollider::getPos(){
    return pos;
}
QVector3D BoxCollider::getSize(){
    return size;
}

void BoxCollider::setSize(QVector3D size){
    this->size = size;
}

void BoxCollider::setPos(QVector3D pos){
    this->pos = pos;
}

bool BoxCollider::Collision(BoxCollider box1,BoxCollider box2)
{

   if((box2.pos[0] >= box1.pos[0] + box1.size[0])      // trop à droite
    || (box2.pos[0] + box2.size[0] <= box1.pos[0]) // trop à gauche
    || (box2.pos[1] >= box1.pos[1] + box1.size[1]) // trop en bas
    || (box2.pos[1] + box2.size[1] <= box1.pos[1])  // trop en haut
        || (box2.pos[2] >= box1.pos[2] + box1.size[2])   // trop derrière
    || (box2.pos[2] + box2.size[2] <= box1.pos[2]))  // trop devant
          return false;
   else
          return true;
}
bool BoxCollider::CollisionFront(BoxCollider box1,BoxCollider box2)
{
   if((box2.pos[2] + box2.size[2] > box1.pos[2]))
          return true;
   else
          return false;
}
bool BoxCollider::CollisionBack(BoxCollider box1,BoxCollider box2)
{
   if((box2.pos[2] < box1.pos[2] + box1.size[2]))
          return true;
   else
          return false;
}
bool BoxCollider::CollisionRight(BoxCollider box1,BoxCollider box2)
{
   if((box2.pos[0] < box1.pos[0] + box1.size[0]))
          return true;
   else
          return false;
}
bool BoxCollider::CollisionUp(BoxCollider box1,BoxCollider box2)
{
   if((box2.pos[1] + box2.size[1] > box1.pos[1]))
          return true;
   else
          return false;
}
bool BoxCollider::CollisionDown(BoxCollider box1,BoxCollider box2)
{
   if(box2.pos[1] < box1.pos[1] + box1.size[1])
          return true;
   else
          return false;
}

bool BoxCollider::CollisionLeft(BoxCollider box1,BoxCollider box2)
{
   if((box2.pos[0] + box2.size[0] > box1.pos[0]))      // trop à droite
          return true;
   else
          return false;
}
