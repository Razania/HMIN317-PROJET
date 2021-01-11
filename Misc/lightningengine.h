#ifndef LIGHTNINGENGINE_H
#define LIGHTNINGENGINE_H

#include <vector>

#include <map>
#include <GameObjects/directionallightobject.h>
#include <GameObjects/pointlightobject.h>
#include <GameObjects/spotlightobject.h>

class LightningEngine
{
public:
    LightningEngine();

    void updateLightning(QOpenGLShaderProgram *program, QVector3D viewPosition);

    void addDirectionalLight(DirectionalLightObject* light);
    void addPointLight(PointLightObject* light);
    void addSpotLight(SpotLightObject* light);

    void removeDirectionalLight(DirectionalLightObject* light);
    void removePointLight(PointLightObject* light);
    void removeSpotLight(SpotLightObject* light);

private:
    std::map<int, DirectionalLightObject*> directionalLights;
    std::map<int, PointLightObject*> pointLights;
    std::map<int, SpotLightObject*> spotLights;

    void loadDirectionalLightToShader(QOpenGLShaderProgram *program, int lightIndex, DirectionalLight light);
    void loadPointLightToShader(QOpenGLShaderProgram *program, int lightIndex, PointLight light);
    void loadSpotLightToShader(QOpenGLShaderProgram *program, int lightIndex, SpotLight light);
};

#endif // LIGHTNINGENGINE_H
