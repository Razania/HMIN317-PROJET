#include "boxcollider.h"
#include "transform.h"

BoxCollider::BoxCollider(QVector3D size) : size(size), transform(NULL) {}

BoxCollider::BoxCollider(Transform* t, QVector3D size) : size(size), transform(t) {}

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

bool BoxCollider::Collision(BoxCollider other, QVector3D *collisionOffSet)
{
    QVector3D offsetX = QVector3D(0, 0, 0);
    QVector3D offsetY = QVector3D(0, 0, 0);
    QVector3D offsetZ = QVector3D(0, 0, 0);

    bool collisionX = this->CollisionX(other, &offsetX);
    bool collisionY = this->CollisionX(other, &offsetY);
    bool collisionZ = this->CollisionX(other, &offsetZ);

    collisionOffSet->setX(offsetX.x());
    collisionOffSet->setY(offsetX.y());
    collisionOffSet->setZ(offsetX.z());

    return collisionX || collisionY || collisionZ;
}

bool BoxCollider::CollisionX(BoxCollider other, QVector3D *collisionOffSet){
    collisionOffSet->setX(0); collisionOffSet->setY(0); collisionOffSet->setZ(0);

    bool collisionFromRight = false;
    bool collisionFromLeft = false;

    float thisRightBorder = this->getTransform()->getWorldPosition().x() + (this->getSize().x()/2);
    float thisLeftBorder = this->getTransform()->getWorldPosition().x() - (this->getSize().x()/2);
    float otherRightBorder = other.getTransform()->getWorldPosition().x() + (other.getSize().x()/2);
    float otherLeftBorder = other.getTransform()->getWorldPosition().x() - (other.getSize().x()/2);

    if(thisRightBorder > otherLeftBorder){ // Collision par notre droite
        collisionFromRight = true;
    }
    if(thisLeftBorder > otherRightBorder){ // Collision par notre gauche
        collisionFromLeft = true;
    }

    if(collisionFromRight && collisionFromLeft){ //Double Collision = On est a l'interieur de l'autre objet
        if((abs(thisRightBorder - otherRightBorder)) >= (abs(thisLeftBorder - otherLeftBorder))) //Plus proche de leur bordure droite ou ex-aequo
            collisionOffSet->setX(otherRightBorder - thisLeftBorder); //On ramene notre bordure gauche sur leur bordure droite
        else //Plus proche de leur bordure gauche
            collisionOffSet->setX(otherLeftBorder - thisRightBorder); //On ramene notre bordure droite sur leur bordure gauche

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

bool BoxCollider::CollisionY(BoxCollider other, QVector3D *collisionOffSet){
    collisionOffSet->setX(0); collisionOffSet->setY(0); collisionOffSet->setZ(0);

    bool collisionFromTop = false;
    bool collisionFromBottom = false;

    float thisTopBorder = this->getTransform()->getWorldPosition().y() + (this->getSize().y()/2);
    float thisBottomBorder = this->getTransform()->getWorldPosition().y() - (this->getSize().y()/2);
    float otherTopBorder = other.getTransform()->getWorldPosition().y() + (other.getSize().y()/2);
    float otherBottomBorder = other.getTransform()->getWorldPosition().y() - (other.getSize().y()/2);

    if(thisTopBorder > otherBottomBorder){ // Collision par notre haut
        collisionFromTop = true;
    }
    if(thisBottomBorder > otherTopBorder){ // Collision par notre bas
        collisionFromBottom = true;
    }

    if(collisionFromTop && collisionFromBottom){ //Double Collision = On est a l'interieur de l'autre objet
        if((abs(thisTopBorder - otherTopBorder)) >= (abs(thisBottomBorder - otherBottomBorder))) //Plus proche de leur bordure haute ou ex-aequo
            collisionOffSet->setX(otherTopBorder - thisBottomBorder); //On ramene notre bordure basse sur leur bordure haute
        else //Plus proche de leur bordure basse
            collisionOffSet->setX(otherBottomBorder - thisTopBorder); //On ramene notre bordure haute sur leur bordure basse

        return true;
    } else if(collisionFromTop){ // Collision haute seulement
        collisionOffSet->setX(otherBottomBorder - thisTopBorder); //On ramene notre bordure haute sur leur bordure basse

        return true;
    } else if(collisionFromBottom){ // Collision basse seulement
        collisionOffSet->setX(otherTopBorder - thisBottomBorder); //On ramene notre bordure basse sur leur bordure haute

        return true;
    }

    return false; //Pas de collision
}
bool BoxCollider::CollisionZ(BoxCollider other, QVector3D *collisionOffSet){
    collisionOffSet->setX(0); collisionOffSet->setY(0); collisionOffSet->setZ(0);

    bool collisionFromFront = false;
    bool collisionFromBack = false;

    float thisFrontBorder = this->getTransform()->getWorldPosition().y() + (this->getSize().y()/2);
    float thisBackBorder = this->getTransform()->getWorldPosition().y() - (this->getSize().y()/2);
    float otherFrontBorder = other.getTransform()->getWorldPosition().y() + (other.getSize().y()/2);
    float otherBackBorder = other.getTransform()->getWorldPosition().y() - (other.getSize().y()/2);

    if(thisFrontBorder > otherBackBorder){ // Collision par notre avant
        collisionFromFront = true;
    }
    if(thisBackBorder > otherFrontBorder){ // Collision par notre arriere
        collisionFromBack = true;
    }

    if(collisionFromFront && collisionFromBack){ //Double Collision = On est a l'interieur de l'autre objet
        if((abs(thisFrontBorder - otherFrontBorder)) >= (abs(thisBackBorder - otherBackBorder))) //Plus proche de leur bordure avant ou ex-aequo
            collisionOffSet->setX(otherFrontBorder - thisBackBorder); //On ramene notre bordure basse sur leur bordure avant
        else //Plus proche de leur bordure arriere
            collisionOffSet->setX(otherBackBorder - thisFrontBorder); //On ramene notre bordure haute sur leur bordure arriere

        return true;
    } else if(collisionFromFront){ // Collision avant seulement
        collisionOffSet->setX(otherBackBorder - thisFrontBorder); //On ramene notre bordure avant sur leur bordure arriere

        return true;
    } else if(collisionFromBack){ // Collision arriere seulement
        collisionOffSet->setX(otherFrontBorder - thisBackBorder); //On ramene notre bordure arriere sur leur bordure avant

        return true;
    }

    return false; //Pas de collision
}
