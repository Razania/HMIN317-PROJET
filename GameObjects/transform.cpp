#include <GameObjects/transform.h>
#include <iostream>
#include <QDebug>
Transform::Transform(GameObject* gameObject,QVector3D localPosition, QQuaternion localRotation, QVector3D localScale)
: gameObject(gameObject), parentNode(nullptr), localPosition(localPosition), localRotation(localRotation), localScale(localScale)
{}
Transform::Transform(GameObject* gameObject, Transform* parentNode, QVector3D localPosition, QQuaternion localRotation, QVector3D localScale)
    : gameObject(gameObject), parentNode(parentNode), localPosition(localPosition), localRotation(localRotation), localScale(localScale)
{}

void Transform::setParent(Transform* parentNode){
    if(this->parentNode != NULL){
        this->parentNode->removeChild(this);
    }

    this->parentNode = parentNode;
    if(this->parentNode == NULL)
        return;
    for(unsigned int i = 0 ;i<this->parentNode->getChilds().size(); i++)
        if(this->parentNode->getChilds()[i]->gameObject->getId() == this->gameObject->getId())
            return;
    parentNode->addChild(this);
}

void Transform::addChild(Transform* child){
    this->childs.push_back(child);

    if(child->getParent() != NULL && child->getParent()->gameObject->getId() != this->gameObject->getId())
        child->setParent(this);
}

void Transform::removeChild(Transform* child){
    for(unsigned int i = 0 ;i<this->getChilds().size(); i++)
        if(this->getChilds()[i]->gameObject->getId() == child->gameObject->getId()){
            this->childs.erase(this->getChilds().begin() + i);
            break;
        }
}

QVector3D Transform::getWorldPosition()
{
    QVector3D worldPos = this->getLocalPosition();

    if(this->parentNode != nullptr)
        worldPos += this->parentNode->getWorldPosition();

    return worldPos;
}

QMatrix4x4 Transform::worldMatrix(){
    QMatrix4x4 transformMatrix = QMatrix4x4();
    transformMatrix.setToIdentity();
    transformMatrix.translate(this->getLocalPosition());
    //qDebug() << transformMatrix;
    //qDebug() << this->getLocalRotation();

    //qDebug() << transformMatrix;
    transformMatrix.scale(this->getLocalScale());
    transformMatrix.rotate(this->getLocalRotation());
    if(this->parentNode != nullptr)
        return this->parentNode->worldMatrix() * transformMatrix;

    return transformMatrix;
}
