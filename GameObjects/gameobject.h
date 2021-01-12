#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject;
#include <GameObjects/boxcollider.h>

#include <Misc/geometryengine.h>
#include <QOpenGLShaderProgram>

class GameObject
{
    public:
        static int next_id;

        GameObject();
        GameObject(Transform* transform);
        Transform* transform;
        BoxCollider* boxCollider;
        virtual void Start();
        virtual void Update();

        virtual void Draw(QOpenGLShaderProgram *program, GeometryEngine *geometries, QMatrix4x4 projection, QMatrix4x4 view);

        int getId() const;

private:
        int id;
};

#endif // GAMEOBJECT_H
