#ifndef PLAYER_H
#define PLAYER_H

#include <GameObjects/boxcollider.h>
#include <WorldGeneration/worldgrid.h>
#include <GameObjects/chunkgameobject.h>
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

    WorldGrid *getWorldGrid() const;
    void setWorldGrid(WorldGrid *value);

    QMap<QPair<int, int>, ChunkGameObject *> *getChunkObjects() const;
    void setChunkObjects(QMap<QPair<int, int>, ChunkGameObject *> *value);

    void Start();

private:
    bool possibleMovement[6]; //0 = Left, 1 = Up, 2 = Right, 3 = Down, 4 = Front, 5 = Back;

    Camera *camera;
    BoxCollider *boxCollider;
    RigidBody *rigidbody;

    WorldGrid* worldGrid;
    QMap<QPair<int, int>, ChunkGameObject*>* chunkObjects;

};

#endif // PLAYER_H
