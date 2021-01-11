#include "TextureLoader.h"
#include "lightningengine.h"

LightningEngine::LightningEngine()
{

}

void LightningEngine::updateLightning(QOpenGLShaderProgram *program, QVector3D viewPosition) {
    program->bind();

    program->setUniformValue("viewPos", viewPosition);

    GLchar* uniformName = "directionalLights";
    GLuint uniformIdx;

    TextureLoader::instance()->getContext()->glGetUniformIndices(program->programId(), 1, &uniformName, &uniformIdx);

    int nameLen = strlen("directionalLights") + 1;
    char* name = new char[nameLen];
    GLint uniformSize = 0;
    GLenum uniformType = GL_NONE;
    TextureLoader::instance()->getContext()->glGetActiveUniform(program->programId(), uniformIdx, nameLen, NULL,
                       &uniformSize, &uniformType, name);

    int index = 0;
    for(std::pair<int,DirectionalLightObject*> it : directionalLights){
        if(index != uniformSize)
            loadDirectionalLightToShader(program, index++,it.second->getLight());
    }
    program->setUniformValue("nbOfDirectionalLights", index);

    uniformName = "pointLights";

    TextureLoader::instance()->getContext()->glGetUniformIndices(program->programId(), 1, &uniformName, &uniformIdx);

    nameLen = strlen("pointLights") + 1;
    name = new char[nameLen];
    uniformSize = 0;
    uniformType = GL_NONE;
    TextureLoader::instance()->getContext()->glGetActiveUniform(program->programId(), uniformIdx, nameLen, NULL,
                       &uniformSize, &uniformType, name);

    index = 0;
    for(std::pair<int,PointLightObject*> it : pointLights){
        if(index != uniformSize)
        loadPointLightToShader(program, index++,it.second->getLight());
    }
    program->setUniformValue("nbOfPointLights", index);

    uniformName = "spotLights";

    TextureLoader::instance()->getContext()->glGetUniformIndices(program->programId(), 1, &uniformName, &uniformIdx);

    nameLen = strlen("spotLights") + 1;
    name = new char[nameLen];
    uniformSize = 0;
    uniformType = GL_NONE;
    TextureLoader::instance()->getContext()->glGetActiveUniform(program->programId(), uniformIdx, nameLen, NULL,
                       &uniformSize, &uniformType, name);

    index = 0;
    for(std::pair<int,SpotLightObject*> it : spotLights){
        if(index != uniformSize)
        loadSpotLightToShader(program, index++,it.second->getLight());
    }
    program->setUniformValue("nbOfSpotLights", index);

    program->release();
}

void LightningEngine::loadDirectionalLightToShader(QOpenGLShaderProgram *program, int lightIndex, DirectionalLight light)
{
    GLuint loc = program->uniformLocation("directionalLights[" + QString::number(lightIndex) + "].direction");
    program->setUniformValue(loc, light.direction);

    loc = program->uniformLocation("directionalLights[" + QString::number(lightIndex) + "].ambient");
    program->setUniformValue(loc, light.ambient);

    loc = program->uniformLocation("directionalLights[" + QString::number(lightIndex) + "].diffuse");
    program->setUniformValue(loc, light.diffuse);

    loc = program->uniformLocation("directionalLights[" + QString::number(lightIndex) + "].specular");
    program->setUniformValue(loc, light.specular);
}

void LightningEngine::loadPointLightToShader(QOpenGLShaderProgram *program, int lightIndex, PointLight light)
{
    GLuint loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].position");
    program->setUniformValue(loc, light.position);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].constant");
    program->setUniformValue(loc, light.constant);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].linear");
    program->setUniformValue(loc, light.linear);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].quadratic");
    program->setUniformValue(loc, light.quadratic);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].ambient");
    program->setUniformValue(loc, light.ambient);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].diffuse");
    program->setUniformValue(loc, light.diffuse);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].specular");
    program->setUniformValue(loc, light.specular);
}

void LightningEngine::loadSpotLightToShader(QOpenGLShaderProgram *program, int lightIndex, SpotLight light)
{
    GLuint loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].direction");
    program->setUniformValue(loc, light.direction);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].position");
    program->setUniformValue(loc, light.position);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].cutoff");
    program->setUniformValue(loc, light.cutoff);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].ambient");
    program->setUniformValue(loc, light.ambient);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].diffuse");
    program->setUniformValue(loc, light.diffuse);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].specular");
    program->setUniformValue(loc, light.specular);

}

void LightningEngine::addDirectionalLight(DirectionalLightObject *light)
{
    directionalLights.insert(std::pair<int,DirectionalLightObject *>(light->getId(), light));
}

void LightningEngine::addPointLight(PointLightObject *light)
{
    pointLights.insert(std::pair<int,PointLightObject *>(light->getId(), light));
}

void LightningEngine::addSpotLight(SpotLightObject *light)
{
    spotLights.insert(std::pair<int,SpotLightObject *>(light->getId(), light));
}

void LightningEngine::removeDirectionalLight(DirectionalLightObject *light)
{
    directionalLights.erase(light->getId());
}

void LightningEngine::removePointLight(PointLightObject *light)
{
    pointLights.erase(light->getId());
}

void LightningEngine::removeSpotLight(SpotLightObject *light)
{
    spotLights.erase(light->getId());
}

