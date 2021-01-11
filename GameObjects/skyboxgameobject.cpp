#include "skyboxgameobject.h"

#include <Misc/Generic.h>
#include <Misc/TextureLoader.h>

SkyboxGameObject::SkyboxGameObject()
{
    vertices = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f)}  // v23
    };

    indices = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };
}

void SkyboxGameObject::Draw(QOpenGLShaderProgram *program, GeometryEngine *geometries, QMatrix4x4 projection, Camera camera)
{
    program->bind();

    GLint OldCullFaceMode;
    glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
    GLint OldDepthFuncMode;
    glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);

    program->setUniformValue("v_matrix", camera.getOriginViewMatrix());
    program->setUniformValue("p_matrix", projection);
    TextureLoader::instance()->getContext()->glActiveTexture(GL_TEXTURE1);
    TextureLoader::instance()->getContext()->glBindTexture(GL_TEXTURE_CUBE_MAP, TextureLoader::instance()->getSkyboxTextureIndex());
    program->setUniformValue("skyboxTexture", 1);

    geometries->drawMeshObjGeometry_SkyboxVertexData(program, &vertices, &indices);

    glCullFace(OldCullFaceMode);
    glDepthFunc(OldDepthFuncMode);

    program->release();
}
