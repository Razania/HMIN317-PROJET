#include "player.h"

Player::Player()
{
    boxCollider->setPos(transform->getLocalPosition());
    //h,w,d
    boxCollider->setSize(QVector3D(2,1,1));
}

void Player::Update(){
    transform->setLocalPosition(camera.getCameraPosition());
    //A VERIFIER
    transform->setLocalRotation(QQuaternion::fromEulerAngles(0,camera.getCameraRotation().y(),0));

    boxCollider->setPos(transform->getLocalPosition());
    for(int i = 0; i<6; i++){
        possibleMovement[i] = 1;
    }
    /*for(int i = 0; i<listBlock;i++){
        if(boxCollider.CollisionLeft(this->boxCollider, listBlock[i].boxCollider)) possibleMovement[0] = false ;
        if(boxCollider.CollisionUp(this->boxCollider, listBlock[i].boxCollider)) possibleMovement[1] = false;
        if(boxCollider.CollisionRight(this->boxCollider, listBlock[i].boxCollider))possibleMovement[2] = false;
        if(boxCollider.CollisionDown(this->boxCollider, listBlock[i].boxCollider))possibleMovement[3] = false;
        if(boxCollider.CollisionFront(this->boxCollider, listBlock[i].boxCollider))possibleMovement[4] = false;
        if(boxCollider.CollisionBack(this->boxCollider, listBlock[i].boxCollider))possibleMovement[5] = false;
    }*/
    if(possibleMovement[0]){
        //Commande bouger gauche
    }
    if(possibleMovement[1]){
        //Commande sauter
    }
    if(possibleMovement[2]){
        //Commande bouger droite
    }
    if(possibleMovement[3]){
        //Camera transform.getLocalPosition.z -= 1 (tombe)
    }
    if(possibleMovement[4]){
        //Commande bouger avant
    }
    if(possibleMovement[5]){
        //Commande bouger arriére
    }
}

Camera *Player::getCamera(){
    return &camera;
}

void Player::setCamera(Camera camera){
    this->camera = camera;
}
