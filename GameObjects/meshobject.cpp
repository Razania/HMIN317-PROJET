#include <GameObjects/meshobject.h>
#include <vector>
#include <QVector3D>
#include <Misc/geometryengine.h>
using namespace std;
#include <Misc/BasicIO.h>

MeshObject::MeshObject(std::string & modelName, QString textureName)
{
    this->texture = new QOpenGLTexture(QImage(textureName));
    this->texture->setMinificationFilter(QOpenGLTexture::Nearest);
    this->texture->setMagnificationFilter(QOpenGLTexture::Linear);
    this->texture->setWrapMode(QOpenGLTexture::Repeat);

    this->textureIndex = 0;
    int count = 1;

    for(const auto character: textureName){
        this->textureIndex += count * character.unicode();
    }

    vector<QVector3D> objVertices;
    vector<vector<int>> objIndices;

    OBJIO::open(modelName, objVertices, objIndices);

    this->vertices.resize(objVertices.size());
    this->indices.resize(objIndices.size());

    for (unsigned int i = 0; i < objVertices.size(); ++i){
        this->vertices[i] = VertexData{objVertices[i], QVector3D(0,0,0), QVector2D(0,0)};
    }

    for (unsigned int i = 0; i < objIndices.size(); ++i){
        this->indices.push_back(objIndices[i][0]);
        this->indices.push_back(objIndices[i][1]);
        this->indices.push_back(objIndices[i][2]);
    }
}

MeshObject::MeshObject(std::string & modelName, QString textureName,Transform* transform) : GameObject(transform)
{
    this->texture = new QOpenGLTexture(QImage(textureName));
    this->texture->setMinificationFilter(QOpenGLTexture::Nearest);
    this->texture->setMagnificationFilter(QOpenGLTexture::Linear);
    this->texture->setWrapMode(QOpenGLTexture::Repeat);

    this->textureIndex = 0;
    int count = 1;

    for(const auto character: textureName){
        this->textureIndex += count * character.unicode();
    }

    vector<QVector3D> objVertices;
    vector<vector<int>> objIndices;

    OBJIO::open(modelName, objVertices, objIndices);

    this->vertices.resize(objVertices.size());
    this->indices.resize(objIndices.size());

    for (unsigned int i = 0; i < objVertices.size(); ++i){
        this->vertices[i] = VertexData{objVertices[i], QVector3D(0,0,0), QVector2D(0,0)};
    }

    for (unsigned int i = 0; i < objIndices.size(); ++i){
        this->indices.push_back(objIndices[i][0]);
        this->indices.push_back(objIndices[i][1]);
        this->indices.push_back(objIndices[i][2]);
    }
}

void MeshObject::Draw(QOpenGLShaderProgram *program, GeometryEngine *geometries, QMatrix4x4 projection, QMatrix4x4 view) {
    program->setUniformValue("m_matrix", this->transform->worldMatrix());
    program->setUniformValue("v_matrix", view);
    program->setUniformValue("p_matrix", projection);

    texture->bind(textureIndex);
    program->setUniformValue("texture", textureIndex);

    geometries->drawMeshObjGeometry(program);

    GameObject::Draw(program, geometries, projection, view);
}
