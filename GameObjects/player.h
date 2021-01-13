#ifndef PLAYER_H
#define PLAYER_H

#include <GameObjects/boxcollider.h>
#include "GameObjects/rigidbody.h"
#include "GameObjects/camera.h"

class Player : public GameObject
{
public:
    Player();
    void Update();

    RigidBody *getRigidbody() const;
    Camera *getCamera() const;
    BoxCollider *getBoxCollider() const;

private:
    bool possibleMovement[6]; //0 = Left, 1 = Up, 2 = Right, 3 = Down, 4 = Front, 5 = Back;

    Camera *camera;
    BoxCollider *boxCollider;
    RigidBody *rigidbody;
};

#endif // PLAYER_H
