#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"
#include "camera.h"
#include "transform.h"

class Player : public GameObject
{
public:
    Player();
    void Update();
    Camera* getCamera();
    void setCamera(Camera camera);

private:
    Camera camera;
    bool possibleMovement[6]; //0 = Left, 1 = Up, 2 = Right, 3 = Down, 4 = Front, 5 = Back;
};

#endif // PLAYER_H
