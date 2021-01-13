#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class Transform;
class BoxCollider;

#include <GameObjects/transform.h>
#include <GameObjects/camera.h>
#include <Misc/geometryengine.h>
#include <QOpenGLShaderProgram>

class GameObject
{
    public:
        static int next_id;

        GameObject();
        GameObject(Transform* transform);
        Transform* transform;
        virtual void Start();
        virtual void Update();

        virtual void Draw(QOpenGLShaderProgram *program, GeometryEngine *geometries, QMatrix4x4 projection, Camera* camera);

        int getId() const;

private:
        int id;
};

#endif // GAMEOBJECT_H
