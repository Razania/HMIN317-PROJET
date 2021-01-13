#include <GameObjects/gameobject.h>
#include <GameObjects/transform.h>

int GameObject::next_id = 0;

GameObject::GameObject()
{
    this->id = GameObject::next_id;
    GameObject::next_id++;
    this->transform = new Transform(this);
}

GameObject::GameObject(Transform* transform)
{
    this->id = GameObject::next_id;
    GameObject::next_id++;
    this->transform = transform;
}

int GameObject::getId() const
{
    return id;
}

void GameObject::Start(){}

void GameObject::Update(){
    for(unsigned int i = 0 ;i<this->transform->getChilds().size(); i++)
        this->transform->getChilds()[i]->gameObject->Update();
}

void GameObject::Draw(QOpenGLShaderProgram *program, GeometryEngine *geometries, QMatrix4x4 projection, Camera* camera){
    //qDebug("Drawing Object %i\n",this->getId());

    for(unsigned int i = 0 ;i<this->transform->getChilds().size(); i++)
        this->transform->getChilds()[i]->gameObject->Draw(program, geometries, projection, camera);
}

