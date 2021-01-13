#ifndef CHUNKGAMEOBJECT_H
#define CHUNKGAMEOBJECT_H

#include <GameObjects/gameobject.h>
#include <Misc/geometryengine.h>
#include <WorldGeneration/chunk.h>
#include <QOpenGLShaderProgram>
#include <QVector3D>

#include <vector>
using namespace std;


class ChunkGameObject : public GameObject
{
public:
    ChunkGameObject(Chunk* chunk);
    void generateSurface(Chunk* chunk);
    void Draw(QOpenGLShaderProgram *program, GeometryEngine *geometries, QMatrix4x4 projection, Camera* camera) override;
private:
    void addBlockFace(Chunk* chunk, QVector3D blockPos, FaceDirection face);

    vector<BasicVertexData> vertices;
    vector<GLushort> indices;
    QOpenGLTexture *texture;
    int textureIndex;
};
#endif // CHUNKGAMEOBJECT_H
