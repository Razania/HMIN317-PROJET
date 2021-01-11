#ifndef SKYBOXGAMEOBJECT_H
#define SKYBOXGAMEOBJECT_H

#include "gameobject.h"

class SkyboxGameObject : public GameObject
{
public:
    SkyboxGameObject();

    void Draw(QOpenGLShaderProgram *program, GeometryEngine *geometries, QMatrix4x4 projection, Camera camera);

private:
    std::vector<SkyboxVertexData> vertices;
    std::vector<GLushort> indices;
};

#endif // SKYBOXGAMEOBJECT_H
