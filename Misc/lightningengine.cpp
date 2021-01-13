#include "textureloader.h"
#include "lightningengine.h"

LightningEngine::LightningEngine() : haveBeenUpdated(false)
{
}

void LightningEngine::updateLightning(QOpenGLShaderProgram *program, QVector3D viewPosition) {
    if(!haveBeenUpdated)
        return;

    program->bind();

    program->setUniformValue("viewPos", viewPosition);

    int maxLights = 2;

    int index = 0;
    for(DirectionalLightObject light : directionalLights.values()){
        if(index != maxLights)
            loadDirectionalLightToShader(program, index++, light.getLight());
    }
    program->setUniformValue("nbOfDirectionalLights", index);

    maxLights = 20;

    index = 0;
    for(PointLightObject light : pointLights.values()){
        if(index != maxLights)
            loadPointLightToShader(program, index++, light.getLight());
    }
    program->setUniformValue("nbOfPointLights", index);

    maxLights = 20;

    index = 0;
    for(SpotLightObject light : spotLights.values()){
        if(index != maxLights)
            loadSpotLightToShader(program, index++, light.getLight());
    }
    program->setUniformValue("nbOfSpotLights", index);

    program->release();

    haveBeenUpdated = false;
}

void LightningEngine::loadDirectionalLightToShader(QOpenGLShaderProgram *program, int lightIndex, DirectionalLight* light)
{
    GLuint loc = program->uniformLocation("directionalLights[" + QString::number(lightIndex) + "].direction");
    program->setUniformValue(loc, light->direction);

    loc = program->uniformLocation("directionalLights[" + QString::number(lightIndex) + "].ambient");
    program->setUniformValue(loc, light->ambient);

    loc = program->uniformLocation("directionalLights[" + QString::number(lightIndex) + "].diffuse");
    program->setUniformValue(loc, light->diffuse);

    loc = program->uniformLocation("directionalLights[" + QString::number(lightIndex) + "].specular");
    program->setUniformValue(loc, light->specular);
}

void LightningEngine::loadPointLightToShader(QOpenGLShaderProgram *program, int lightIndex, PointLight* light)
{
    GLuint loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].position");
    program->setUniformValue(loc, light->position);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].constant");
    program->setUniformValue(loc, light->constant);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].linear");
    program->setUniformValue(loc, light->linear);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].quadratic");
    program->setUniformValue(loc, light->quadratic);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].ambient");
    program->setUniformValue(loc, light->ambient);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].diffuse");
    program->setUniformValue(loc, light->diffuse);

    loc = program->uniformLocation("pointLights[" + QString::number(lightIndex) + "].specular");
    program->setUniformValue(loc, light->specular);
}

void LightningEngine::loadSpotLightToShader(QOpenGLShaderProgram *program, int lightIndex, SpotLight* light)
{
    GLuint loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].direction");
    program->setUniformValue(loc, light->direction);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].position");
    program->setUniformValue(loc, light->position);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].constant");
    program->setUniformValue(loc, light->constant);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].linear");
    program->setUniformValue(loc, light->linear);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].quadratic");
    program->setUniformValue(loc, light->quadratic);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].cutOff");
    program->setUniformValue(loc, light->cutOff);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].outerCutOff");
    program->setUniformValue(loc, light->outerCutOff);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].ambient");
    program->setUniformValue(loc, light->ambient);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].diffuse");
    program->setUniformValue(loc, light->diffuse);

    loc = program->uniformLocation("spotLights[" + QString::number(lightIndex) + "].specular");
    program->setUniformValue(loc, light->specular);

}

void LightningEngine::addDirectionalLight(DirectionalLightObject light)
{
    directionalLights.insert(light.getId(), light);
    haveBeenUpdated = true;
}

void LightningEngine::addPointLight(PointLightObject light)
{
    pointLights.insert(light.getId(), light);
    haveBeenUpdated = true;
}

void LightningEngine::addSpotLight(SpotLightObject light)
{
    spotLights.insert(light.getId(), light);
    haveBeenUpdated = true;
}

void LightningEngine::removeDirectionalLight(DirectionalLightObject light)
{
    directionalLights.remove(light.getId());
    haveBeenUpdated = true;
}

void LightningEngine::removePointLight(PointLightObject light)
{
    pointLights.remove(light.getId());
    haveBeenUpdated = true;
}

void LightningEngine::removeSpotLight(SpotLightObject light)
{
    spotLights.remove(light.getId());
    haveBeenUpdated = true;
}

