#include "boxcollider.h"
#include "transform.h"

BoxCollider::BoxCollider(QVector3D size, QVector3D anchorPos) : size(size), anchorPos(anchorPos), transform(new Transform(NULL)) {}

BoxCollider::BoxCollider(Transform* t, QVector3D size, QVector3D anchorPos) : size(size), anchorPos(anchorPos), transform(t) {}

QVector3D BoxCollider::getSize(){
    return size;
}

void BoxCollider::setSize(QVector3D size){
    this->size = size;
}

Transform *BoxCollider::getTransform() const
{
    return transform;
}

QVector3D BoxCollider::getAnchorPos() const
{
    return anchorPos;
}

void BoxCollider::setAnchorPos(const QVector3D &value)
{
    anchorPos = value;
}

bool BoxCollider::Collision(BoxCollider* other, QVector3D *collisionOffSet)
{
    QVector3D offsetX = QVector3D(0, 0, 0);
    QVector3D offsetY = QVector3D(0, 0, 0);
    QVector3D offsetZ = QVector3D(0, 0, 0);

//    qDebug("%f %f %f", this->transform->getWorldPosition().x(), this->transform->getWorldPosition().y(), this->transform->getWorldPosition().z());
//    qDebug("%f %f %f", other->transform->getWorldPosition().x(), other->transform->getWorldPosition().y(), other->transform->getWorldPosition().z());

    bool collisionX = this->CollisionX(other, &offsetX);
    bool collisionY = this->CollisionY(other, &offsetY);
    bool collisionZ = this->CollisionZ(other, &offsetZ);

    collisionOffSet->setX(offsetX.x());
    collisionOffSet->setY(offsetY.y());
    collisionOffSet->setZ(offsetZ.z());

    //qDebug("%f %f %f", collisionOffSet->x(), collisionOffSet->y(), collisionOffSet->z());


    return collisionX && collisionY && collisionZ;
}

bool BoxCollider::CollisionX(BoxCollider* other, QVector3D *collisionOffSet){
    collisionOffSet->setX(0); collisionOffSet->setY(0); collisionOffSet->setZ(0);

    bool collisionFromRight = false;
    bool collisionFromLeft = false;

    float thisRightBorder = this->getTransform()->getWorldPosition().x() + this->getAnchorPos().x() + (this->getSize().x()/2);
    float thisLeftBorder = this->getTransform()->getWorldPosition().x() + this->getAnchorPos().x() - (this->getSize().x()/2);
    float otherRightBorder = other->getTransform()->getWorldPosition().x() + other->getAnchorPos().x() + (other->getSize().x()/2);
    float otherLeftBorder = other->getTransform()->getWorldPosition().x() + other->getAnchorPos().x() - (other->getSize().x()/2);

//    qDebug("%f %f", thisRightBorder, thisLeftBorder);
//    qDebug("%f %f", otherRightBorder, otherLeftBorder);


    if(thisRightBorder >= otherLeftBorder && thisRightBorder <= otherRightBorder){ // Collision par notre droite
        collisionFromRight = true;
    }
    if(thisLeftBorder <= otherRightBorder && thisLeftBorder >= otherLeftBorder){ // Collision par notre gauche
        collisionFromLeft = true;
    }

    if(collisionFromRight && collisionFromLeft){ //Double Collision = On est a l'interieur de l'autre objet
//        if((abs(otherRightBorder - thisLeftBorder)) <= (abs(otherLeftBorder - thisRightBorder))) //Plus proche de leur bordure droite ou ex-aequo
//            collisionOffSet->setX(otherRightBorder - thisLeftBorder); //On ramene notre bordure gauche sur leur bordure droite
//        else //Plus proche de leur bordure gauche
//            collisionOffSet->setX(otherLeftBorder - thisRightBorder); //On ramene notre bordure droite sur leur bordure gauche

        return true;
    } else if(collisionFromRight){ // Collision droite seulement
        collisionOffSet->setX(otherLeftBorder - thisRightBorder); //On ramene notre bordure droite sur leur bordure gauche

        return true;
    } else if(collisionFromLeft){ // Collision gauche seulement
        collisionOffSet->setX(otherRightBorder - thisLeftBorder); //On ramene notre bordure gauche sur leur bordure droite

        return true;
    }

    return false; //Pas de collision
}

bool BoxCollider::CollisionY(BoxCollider* other, QVector3D *collisionOffSet){
    collisionOffSet->setX(0); collisionOffSet->setY(0); collisionOffSet->setZ(0);

    bool collisionFromTop = false;
    bool collisionFromBottom = false;

    float thisTopBorder = this->getTransform()->getWorldPosition().y() + this->getAnchorPos().y() + (this->getSize().y()/2);
    float thisBottomBorder = this->getTransform()->getWorldPosition().y() + this->getAnchorPos().y() - (this->getSize().y()/2);
    float otherTopBorder = other->getTransform()->getWorldPosition().y() + other->getAnchorPos().y() + (other->getSize().y()/2);
    float otherBottomBorder = other->getTransform()->getWorldPosition().y() + other->getAnchorPos().y() - (other->getSize().y()/2);

//    qDebug("%f %f", thisTopBorder, thisBottomBorder);
//    qDebug("%f %f", otherTopBorder, otherBottomBorder);

    if(thisTopBorder >= otherBottomBorder && thisTopBorder <= otherTopBorder){ // Collision par notre haut
        collisionFromTop = true;
    }
    if(thisBottomBorder <= otherTopBorder && thisBottomBorder >= otherBottomBorder){ // Collision par notre bas
        collisionFromBottom = true;
    }

    if(collisionFromTop && collisionFromBottom){ //Double Collision = On est a l'interieur de l'autre objet
//        if((abs(otherTopBorder - thisBottomBorder)) <= (abs(otherBottomBorder - thisTopBorder))) //Plus proche de leur bordure haute ou ex-aequo
//            collisionOffSet->setY(otherTopBorder - thisBottomBorder); //On ramene notre bordure basse sur leur bordure haute
//        else //Plus proche de leur bordure basse
//            collisionOffSet->setY(otherBottomBorder - thisTopBorder); //On ramene notre bordure haute sur leur bordure basse

        return true;
    } else if(collisionFromTop){ // Collision haute seulement
        collisionOffSet->setY(otherBottomBorder - thisTopBorder); //On ramene notre bordure haute sur leur bordure basse

        return true;
    } else if(collisionFromBottom){ // Collision basse seulement
        collisionOffSet->setY(otherTopBorder - thisBottomBorder); //On ramene notre bordure basse sur leur bordure haute

        return true;
    }

    return false; //Pas de collision
}
bool BoxCollider::CollisionZ(BoxCollider* other, QVector3D *collisionOffSet){
    collisionOffSet->setX(0); collisionOffSet->setY(0); collisionOffSet->setZ(0);

    bool collisionFromFront = false;
    bool collisionFromBack = false;

    float thisFrontBorder = this->getTransform()->getWorldPosition().z() + this->getAnchorPos().z() + (this->getSize().z()/2);
    float thisBackBorder = this->getTransform()->getWorldPosition().z() + this->getAnchorPos().z() - (this->getSize().z()/2);
    float otherFrontBorder = other->getTransform()->getWorldPosition().z() + other->getAnchorPos().z() + (other->getSize().z()/2);
    float otherBackBorder = other->getTransform()->getWorldPosition().z() + other->getAnchorPos().z() - (other->getSize().z()/2);

    if(thisFrontBorder >= otherBackBorder && thisFrontBorder <= otherFrontBorder){ // Collision par notre avant
        collisionFromFront = true;
    }
    if(thisBackBorder <= otherFrontBorder && thisBackBorder >= otherBackBorder){ // Collision par notre arriere
        collisionFromBack = true;
    }

    if(collisionFromFront && collisionFromBack){ //Double Collision = On est a l'interieur de l'autre objet
//        if((abs(otherFrontBorder - thisBackBorder)) <= (abs(otherBackBorder - thisFrontBorder))) //Plus proche de leur bordure avant ou ex-aequo
//            collisionOffSet->setZ(otherFrontBorder - thisBackBorder); //On ramene notre bordure basse sur leur bordure avant
//        else //Plus proche de leur bordure arriere
//            collisionOffSet->setZ(otherBackBorder - thisFrontBorder); //On ramene notre bordure haute sur leur bordure arriere

        return true;
    } else if(collisionFromFront){ // Collision avant seulement
        collisionOffSet->setZ(otherBackBorder - thisFrontBorder); //On ramene notre bordure avant sur leur bordure arriere

        return true;
    } else if(collisionFromBack){ // Collision arriere seulement
        collisionOffSet->setZ(otherFrontBorder - thisBackBorder); //On ramene notre bordure arriere sur leur bordure avant

        return true;
    }

    return false; //Pas de collision
}
