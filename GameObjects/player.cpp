#include "player.h"
#include "WorldGeneration/chunk.h"

Player::Player()
{
    camera = new Camera(this->transform->getWorldPosition() + QVector3D(0,1.5,0), QVector3D(0,0,-1), QVector3D(0,0,0), QVector3D(0,1,0));
    rigidbody = new RigidBody(this->transform);
    boxCollider = new BoxCollider(transform, QVector3D(1,2,1), QVector3D(0.5,1,0.5));
}


void Player::Start()
{
    rigidbody->initTimer();
    rigidbody->setForce(QVector3D(0,0,0));
}

void Player::Update(){
    camera->setCameraPosition(this->transform->getWorldPosition() + QVector3D(0,1.75,0));
    this->transform->setLocalRotation(QQuaternion::fromEulerAngles(0,this->getCamera()->getCameraRotation().y(),0));

    rigidbody->applyGravity();
    rigidbody->updateBody();

//    std::vector<QPair<int, int>> chunksToCollidePos = worldGrid->getChunksAtWorldPosForSize(this->transform->getWorldPosition(), QVector2D(boxCollider->getSize().x(), boxCollider->getSize().z()));

//    for(QPair<int, int> chunkPos : chunksToCollidePos){
//        ChunkGameObject* chunkGO = (*chunkObjects)[chunkPos];

//        for(BoxCollider* boxCollider : chunkGO->getActiveBlocksColliders()){
//            //qDebug("yo");
//            //qDebug("%f %f %f", boxCollider->getTransform()->getWorldPosition().x(), boxCollider->getTransform()->getWorldPosition().y(), boxCollider->getTransform()->getWorldPosition().z());

//            QVector3D offSet;
//            if(this->getBoxCollider()->Collision(boxCollider, &offSet)){
//                qDebug("Box Collider");
//                qDebug("%f %f %f", boxCollider->getTransform()->getWorldPosition().x(), boxCollider->getTransform()->getWorldPosition().y(), boxCollider->getTransform()->getWorldPosition().z());
//                qDebug("%f %f %f", offSet.x(), offSet.y(), offSet.z());
//                qDebug("%f %f %f", this->transform->getLocalPosition().x(), this->transform->getLocalPosition().y(), this->transform->getLocalPosition().z());
//                this->rigidbody->revertLastMovement(this->boxCollider->getTransform()->getWorldPosition() - boxCollider->getTransform()->getWorldPosition());
//                qDebug("%f %f %f", this->transform->getLocalPosition().x(), this->transform->getLocalPosition().y(), this->transform->getLocalPosition().z());
//            }
//        }
//    }
}

RigidBody *Player::getRigidbody() const
{
    return rigidbody;
}

Camera *Player::getCamera() const
{
    return camera;
}

BoxCollider *Player::getBoxCollider() const
{
    return boxCollider;
}

WorldGrid *Player::getWorldGrid() const
{
    return worldGrid;
}

void Player::setWorldGrid(WorldGrid *value)
{
    worldGrid = value;
}

QMap<QPair<int, int>, ChunkGameObject *> *Player::getChunkObjects() const
{
    return chunkObjects;
}

void Player::setChunkObjects(QMap<QPair<int, int>, ChunkGameObject *> *value)
{
    chunkObjects = value;
}

