#include "boxcollider.h"

BoxCollider::BoxCollider()
{

}

BoxCollider::BoxCollider(int x, int y, int z, int h, int d, int w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    this->h = h;
    this->d = d;
}


bool Collision(BoxCollider box1,BoxCollider box2)
{
   if((box2.x >= box1.x + box1.w)      // trop à droite
    || (box2.x + box2.w <= box1.x) // trop à gauche
    || (box2.y >= box1.y + box1.h) // trop en bas
    || (box2.y + box2.h <= box1.y)  // trop en haut
        || (box2.z >= box1.z + box1.d)   // trop derrière
    || (box2.z + box2.d <= box1.z))  // trop devant
          return false;
   else
          return true;
}

bool CollisionRight(BoxCollider box1,BoxCollider box2)
{
   if((box2.x < box1.x + box1.w))
          return true;
   else
          return false;
}
bool CollisionUp(BoxCollider box1,BoxCollider box2)
{
   if((box2.y + box2.h > box1.y))
          return true;
   else
          return false;
}
bool CollisionDown(BoxCollider box1,BoxCollider box2)
{
   if(box2.y < box1.y + box1.h)
          return true;
   else
          return false;
}

bool CollisionLeft(BoxCollider box1,BoxCollider box2)
{
   if((box2.x + box2.w > box1.x))      // trop à droite
          return true;
   else
          return false;
}
