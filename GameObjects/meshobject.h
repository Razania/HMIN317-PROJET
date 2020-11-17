#ifndef MESHOBJET_H
#define MESHOBJET_H

#include <GameObjects/gameobject.h>
#include <Misc/geometryengine.h>
#include <QOpenGLShaderProgram>

#include <QVector3D>
#include <vector>

class MeshObject : public GameObject
{
public:
    MeshObject(std::string & modelName, QString textureName);
    MeshObject(std::string & modelName, QString textureName,Transform* transform);
    void Draw(QOpenGLShaderProgram *program, GeometryEngine *geometries, QMatrix4x4 projection, QMatrix4x4 view) override;
    private:
        std::vector<VertexData> vertices;
        std::vector<GLushort> indices;
        QOpenGLTexture *texture;
        int textureIndex;
};

#endif // MESHOBJET_H
