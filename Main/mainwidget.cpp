/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <Main/mainwidget.h>

#include <QMouseEvent>

#include <math.h>
#include <Misc/Generic.h>
#include <GameObjects/skyboxgameobject.h>
#include <GameObjects/chunkgameobject.h>
#include <GameObjects/camera.h>
#include <GameObjects/directionallightobject.h>
#include <Misc/textureloader.h>
#include <WorldGeneration/worldgrid.h>
#include <WorldGeneration/chunk.h>

std::vector<ChunkGameObject*> chunkObjects;

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    angularSpeed(0)
{
    fps = 144;
    cameraCurrentVelocityNorm = QVector3D(0,0,0);
    cameraCurrentRotationNorm = QVector3D(0,0,0);
    camera = Camera(QVector3D(40,60,40), QVector3D(0,0,-1), QVector3D(0,0,0),QVector3D(0,1,0));

    skybox = new SkyboxGameObject();

    lightning = new LightningEngine();
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete geometries;
    doneCurrent();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void MainWidget::timerEvent(QTimerEvent *)
{
    //Mouvement Camera
    if(camera.getCameraMode() == camera.CAMERA_MODE_ORBITAL){
        //qDebug("cameraDirection => (%f,%f,%f)", this->camera.getCameraDirection().x(), this->camera.getCameraDirection().y(), this->camera.getCameraDirection().z());
        //qDebug("cameraPosition => (%f,%f,%f)", this->camera.getCameraPosition().x(), this->camera.getCameraPosition().y(), this->camera.getCameraPosition().z());
    } else if(camera.getCameraMode() == camera.CAMERA_MODE_STATIONARY){
        this->updateCameraVelNorm();
        QVector3D cameraVelocity = (cameraCurrentVelocityNorm * this->CAMERA_MOVEMENT_SPEED);
        QVector3D newCameraPosition = this->camera.getCameraPosition() + cameraVelocity;
        //qDebug("newCameraPosition => (%f,%f,%f)",newCameraPosition.x(),newCameraPosition.y(),newCameraPosition.z());
        //qDebug("newCameraRotation => (%f,%f,%f)",this->camera.getCameraRotation().x(),this->camera.getCameraRotation().y(),this->camera.getCameraRotation().z());

        this->camera.setCameraPosition(newCameraPosition);
        this->camera.setCameraRotation(this->camera.getCameraRotation() + cameraCurrentRotationNorm);
    }

    //Rotation souris
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01)
        angularSpeed = 0.0;
    else // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

    update();
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable polygon mode
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glEnable(GL_TEXTURE_2D_ARRAY);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);

    //Init Model
    geometries = new GeometryEngine;
    this->sceneRoot = new GameObject();

    WorldGrid worldGrid = WorldGrid(1,QVector3D(16,256,16));

    short viewRange = 8;

    for(short i = -(abs(viewRange)); i <= (abs(viewRange)); i++)
        for(short j = -(abs(viewRange)); j <= (abs(viewRange)); j++)
            worldGrid.generateChunk(QPair<int, int>(i, j));

    for(short i = -(abs(viewRange)); i <= (abs(viewRange)); i++)
        for(short j = -(abs(viewRange)); j <= (abs(viewRange)); j++){
            chunkObjects.push_back(new ChunkGameObject(worldGrid.getChunk(QPair<int, int>(i, j))));
            chunkObjects[chunkObjects.size() - 1]->transform->setParent(this->sceneRoot->transform);
        }

    //Init Lightning
    DirectionalLightObject baseLight = DirectionalLightObject();
    DirectionalLight* lightAttributes = baseLight.getLight();

    lightAttributes->direction = QVector3D(0.5,-1,0.5);
    lightAttributes->ambient = QVector3D(0,0,0);
    lightAttributes->diffuse = QVector3D(0,0,0);
    lightAttributes->specular = QVector3D(0,0,0);

    lightning->addDirectionalLight(baseLight);

    PointLightObject testPointLight = PointLightObject();
    testPointLight.transform->setLocalPosition(QVector3D(0,60,0));
    PointLight* testPointLightAttributes = testPointLight.getLight();

    testPointLightAttributes->position = testPointLight.transform->getLocalPosition();
    testPointLightAttributes->constant = 1;
    testPointLightAttributes->linear = 0.009;
    testPointLightAttributes->quadratic = 0.0032;
    testPointLightAttributes->ambient = QVector3D(0,0,0.1);
    testPointLightAttributes->diffuse = QVector3D(0,0,1);
    testPointLightAttributes->specular = QVector3D(0,0,0);

    lightning->addPointLight(testPointLight);

    PointLightObject testPointLight2 = PointLightObject();
    testPointLight2.transform->setLocalPosition(QVector3D(-40,58,-40));
    PointLight* testPointLightAttributes2 = testPointLight2.getLight();

    testPointLightAttributes2->position = testPointLight2.transform->getLocalPosition();
    testPointLightAttributes2->constant = 1;
    testPointLightAttributes2->linear = 0.09;
    testPointLightAttributes2->quadratic = 0.032;
    testPointLightAttributes2->ambient = QVector3D(0.1,0.1,0.1);
    testPointLightAttributes2->diffuse = QVector3D(1,1,1);
    testPointLightAttributes2->specular = QVector3D(0,0,0);

    lightning->addPointLight(testPointLight2);

    SpotLightObject testSpotLight = SpotLightObject();
    testSpotLight.transform->setLocalPosition(QVector3D(40,60,40));
    SpotLight* testSpotLightAttributes = testSpotLight.getLight();

    testSpotLightAttributes->position = testSpotLight.transform->getLocalPosition();
    testSpotLightAttributes->direction = QVector3D(0.8,-1,0.8);
    testSpotLightAttributes->constant = 1;
    testSpotLightAttributes->linear = 0.009;
    testSpotLightAttributes->quadratic = 0.0032;
    testSpotLightAttributes->cutOff = cos(to_radians(10));
    testSpotLightAttributes->outerCutOff = cos(to_radians(15));
    testSpotLightAttributes->ambient = QVector3D(0.1,0.1,0.1);
    testSpotLightAttributes->diffuse = QVector3D(1,0,0);
    testSpotLightAttributes->specular = QVector3D(0,0,0);

    lightning->addSpotLight(testSpotLight);

    // Use QBasicTimer because its faster than QTimer
    timer.start(1000.0f/fps, this);
}

void MainWidget::initShaders()
{
    // Init main Shader Program
    if (!mainProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();
    if (!mainProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();
    if (!mainProgram.link())
        close();

    // Init skybox Shader Program
    if (!skyboxProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/skybox_vshader.glsl"))
        close();
    if (!skyboxProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/skybox_fshader.glsl"))
        close();
    if (!skyboxProgram.link())
        close();
}

void MainWidget::initTextures()
{
    TextureLoader::initInstance(this);

    if (!mainProgram.bind())
        close();

    TextureLoader::instance()->loadBlocksTextures();

    mainProgram.release();

    if (!skyboxProgram.bind())
        close();

    TextureLoader::instance()->loadSkyboxTextures();

    skyboxProgram.release();
}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.2, zFar = 256.0, fov = 60.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Update Lights
    lightning->updateLightning(&mainProgram, camera.getCameraPosition());

    skybox->Draw(&skyboxProgram, geometries, projection, this->camera);

    sceneRoot->Update();
    sceneRoot->Draw(&mainProgram,geometries, projection,this->camera);
}

void MainWidget::keyPressEvent(QKeyEvent *ev)
{
    if(isPressed.find(ev->text()) == isPressed.end())
        isPressed.insert(ev->text(),false);

    if(ev->key() == Qt::Key_Control && isPressed.find("ctrl") == isPressed.end())
        isPressed.insert("ctrl",false);

    if(ev->text() == "w" && !isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = true;
    else if(ev->text() == "s" && !isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = true;
    else if(ev->text() == "a" && !isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = true;
    else if(ev->text() == "d" && !isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = true;
    else if(ev->text() == "c" && !isPressed.value(ev->text())){
        //qDebug("Changement de Caméra");
        if(this->camera.getCameraMode() == this->camera.CAMERA_MODE_ORBITAL)
            this->camera.setCameraToStationaryMode();
        else if(this->camera.getCameraMode() == this->camera.CAMERA_MODE_STATIONARY)
            this->camera.setCameraToOrbitalMode();
        isPressed.find(ev->text()).value() = true;
    }else if(ev->text() == " " && !isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = true;
    else if(ev->key() == Qt::Key_Control && !isPressed.value("ctrl"))
            isPressed.find("ctrl").value() = true;
    else if(ev->text() == "r" && !isPressed.value(ev->text()))
            isPressed.find(ev->text()).value() = true;
    else if(ev->text() == "f" && !isPressed.value(ev->text()))
            isPressed.find(ev->text()).value() = true;
    else if(ev->text() == "q" && !isPressed.value(ev->text()))
            isPressed.find(ev->text()).value() = true;
    else if(ev->text() == "e" && !isPressed.value(ev->text()))
            isPressed.find(ev->text()).value() = true;
}

void MainWidget::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->text() == "w" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == "s" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == "a" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == "d" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == "c" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == " " && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->key() == Qt::Key_Control && isPressed.value("ctrl"))
        isPressed.find("ctrl").value() = false;
    else if(ev->text() == "r" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == "f" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == "q" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == "e" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;

}

void MainWidget::updateCameraVelNorm(){
    QVector3D newVelNorm = QVector3D(0,0,0);
    QVector3D newRotNorm = QVector3D(0,0,0);

    if(this->isPressed.value("w"))
        newVelNorm += this->camera.getCameraDirection()*20;
    if(this->isPressed.value("s"))
        newVelNorm -= this->camera.getCameraDirection()*20;
    if(this->isPressed.value("d"))
        newVelNorm += this->camera.getCameraRight()*20;
    if(this->isPressed.value("a"))
        newVelNorm -= this->camera.getCameraRight()*20;

    if(this->isPressed.value(" "))
        newVelNorm += this->camera.getCameraUp()*15;
    if(this->isPressed.value("ctrl"))
        newVelNorm -= this->camera.getCameraUp()*15;

    if(this->isPressed.value("r"))
        newRotNorm += QVector3D(1,0,0);
    if(this->isPressed.value("f"))
        newRotNorm -= QVector3D(1,0,0);
    if(this->isPressed.value("q"))
        newRotNorm += QVector3D(0,1,0);
    if(this->isPressed.value("e"))
        newRotNorm -= QVector3D(0,1,0);

    this->cameraCurrentVelocityNorm = newVelNorm;
    this->cameraCurrentRotationNorm = newRotNorm;
}
