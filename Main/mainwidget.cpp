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
#include <iostream>
#include <Misc/Generic.h>
#include <GameObjects/skyboxgameobject.h>
#include <GameObjects/camera.h>
#include <GameObjects/directionallightobject.h>
#include <GameObjects/rigidbody.h>
#include <Misc/textureloader.h>
#include <WorldGeneration/chunk.h>
#include <QTimer>




std::vector<ChunkGameObject*> chunkObjects;

int X = 0;
int Y = 0;
int mode = 0;

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    angularSpeed(0),
    worldGrid(WorldGrid(1,QVector3D(16,256,16)))
{
    fps = 144;
    playerCurrentVelocityNorm = QVector3D(0,0,0);
    cameraCurrentRotationNorm = QVector3D(0,0,0);

    skybox = new SkyboxGameObject();

    lightning = new LightningEngine();

    tab = chargerTexture();
    label = new QLabel(this);
    labelFps = new QLabel(this);
    entier = 0;
    QPixmap image = QPixmap(tab[entier]);
    QPixmap imageResize;
    imageResize = image.scaled(100,100);
    m_frameCount = 0;
    //label->setPixmap(imageResize);
    labelFps->setPixmap(imageResize);
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete geometries;
    doneCurrent();
}

void MainWidget::paintEvent() {
    if (m_frameCount == 0) {
        m_time.start();

        m_frameCount++;
    } else {
        m_frameCount++;
       // printf("FPS is %f ms\n", m_time.elapsed() / (m_frameCount));
        labelFps->setText(QString::number((int)(((float) m_frameCount) / (((float) m_time.elapsed()) / 1000.0f))) + " FPS");

    }

}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    QVector3D newRotNorm = QVector3D(0,0,0);
    if(e->buttons() == Qt::RightButton){
        if(e->localPos().x() > X){
            newRotNorm -= QVector3D(0,1,0);
            X = e->localPos().x();
        }
        else if(e->localPos().x() < X){
            newRotNorm += QVector3D(0,1,0);
            X = e->localPos().x();
        }
        if(e->localPos().y() > Y){
            newRotNorm -= QVector3D(1,0,0);
            Y = e->localPos().y();
        }
        else if(e->localPos().y() < Y){
            newRotNorm += QVector3D(1,0,0);
            Y = e->localPos().y();
        }
        QVector3D vec = QVector3D(-e->localPos().y()+(this->height()/2), -e->localPos().x()-(this->width()/2), 0);
        player.getCamera()->setCameraRotation(vec);
    }
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

QVector<QString> MainWidget::chargerTexture(){
    QVector<QString> tab;
    tab.push_back(":/grassBottom.png");
    tab.push_back(":/grassSide.png");
    tab.push_back(":/grassTop.png");
    tab.push_back(":/stone.png");
    return tab;
}

void MainWidget::changerTexture(){
    cout << entier << " " << tab.size() << endl;
    if(entier < tab.size()-1)
        entier++;
    else
        entier = 0;

    QPixmap image = QPixmap(tab[entier]);
    QPixmap imageResize;
    imageResize = image.scaled(100,100);

    //label->setPixmap(imageResize);
}

void MainWidget::changerMode(){
    if(mode == 0)
        mode = 1;
    else
        mode = 0;
}

void MainWidget::timerEvent(QTimerEvent *)
{
    //Mouvement Camera
    if(player.getCamera()->getCameraMode() == player.getCamera()->CAMERA_MODE_ORBITAL){
        //qDebug("cameraDirection => (%f,%f,%f)", this->camera.getCameraDirection().x(), this->camera.getCameraDirection().y(), this->camera.getCameraDirection().z());
        //qDebug("cameraPosition => (%f,%f,%f)", this->camera.getCameraPosition().x(), this->camera.getCameraPosition().y(), this->camera.getCameraPosition().z());
    } else if(player.getCamera()->getCameraMode() == player.getCamera()->CAMERA_MODE_STATIONARY){
        this->updateCameraVelNorm();
        QVector3D playerVelocity = (playerCurrentVelocityNorm * this->CAMERA_MOVEMENT_SPEED);\
        //qDebug("newCameraPosition => (%f,%f,%f)",newCameraPosition.x(),newCameraPosition.y(),newCameraPosition.z());
        //qDebug("newCameraRotation => (%f,%f,%f)",this->camera.getCameraRotation().x(),this->camera.getCameraRotation().y(),this->camera.getCameraRotation().z());

        player.getRigidbody()->addForce(QVector3D(playerVelocity.x(), playerVelocity.y(), playerVelocity.z()));
        player.getCamera()->setCameraRotation(player.getCamera()->getCameraRotation() + cameraCurrentRotationNorm);
    }

    //Rotation souris
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01)
        angularSpeed = 0.0;
    else // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

    if(mode == 0){
        player.getRigidbody()->setGravity(0.0f);
    }
    else{
        player.getRigidbody()->setGravity(9.71f);
    }
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

    player.transform->setParent(this->sceneRoot->transform);
    player.transform->setLocalPosition(QVector3D(0,65,0));


    player.setWorldGrid(&worldGrid);
    player.setChunkObjects(&chunkObjects);

    short viewRange = 16;

    for(short i = -(abs(viewRange)); i <= (abs(viewRange)); i++)
        for(short j = -(abs(viewRange)); j <= (abs(viewRange)); j++)
            worldGrid.generateChunk(QPair<int, int>(i, j));

    for(short i = -(abs(viewRange)); i <= (abs(viewRange)); i++)
        for(short j = -(abs(viewRange)); j <= (abs(viewRange)); j++){
            chunkObjects.insert(QPair<int, int>(i, j), new ChunkGameObject(worldGrid.getChunk(QPair<int, int>(i, j))));
            chunkObjects[QPair<int, int>(i, j)]->transform->setParent(this->sceneRoot->transform);
        }

//    std::vector<QPair<int, int>> chunksPos = worldGrid.getChunksAtWorldPosForSize(QVector3D(0,0,0), QVector2D(1,1));
//    qDebug("Nb Chunks trouvés = %lld", chunksPos.size());
//    for(QPair<int, int> chunkPos : chunksPos)
//        qDebug("%d %d", chunkPos.first, chunkPos.second);

    //Init Lightning
    DirectionalLightObject baseLight = DirectionalLightObject();
    DirectionalLight* lightAttributes = baseLight.getLight();

    lightAttributes->direction = QVector3D(0.5,-1,0.5);
    lightAttributes->ambient = QVector3D(0.2,0.2,0.2);
    lightAttributes->diffuse = QVector3D(1,1,1);
    lightAttributes->specular = QVector3D(0,0,0);

    lightning->addDirectionalLight(baseLight);

//    PointLightObject pointLight1 = PointLightObject();
//    PointLight* pointLight1Attributes = pointLight1.getLight();

//    pointLight1Attributes->position = QVector3D(100,63,100);

//    pointLight1Attributes->constant = 1.0;
//    pointLight1Attributes->linear = 0.07;
//    pointLight1Attributes->quadratic = 0.017;

//    pointLight1Attributes->ambient = QVector3D(0.2,0.2,0.2);
//    pointLight1Attributes->diffuse = QVector3D(1,0,0);
//    pointLight1Attributes->specular = QVector3D(0,0,0);

//    lightning->addPointLight(pointLight1);

//    PointLightObject pointLight2 = PointLightObject();
//    PointLight* pointLight2Attributes = pointLight2.getLight();

//    pointLight2Attributes->position = QVector3D(0,65,0);

//    pointLight2Attributes->constant = 1.0;
//    pointLight2Attributes->linear = 0.014;
//    pointLight2Attributes->quadratic = 0.0002;

//    pointLight2Attributes->ambient = QVector3D(0.2,0.2,0.2);
//    pointLight2Attributes->diffuse = QVector3D(1,0.5,0);
//    pointLight2Attributes->specular = QVector3D(0,0,0);

//    lightning->addPointLight(pointLight2);

//    SpotLightObject spotLight = SpotLightObject();
//    SpotLight* spotLightAttributes = spotLight.getLight();

//    spotLightAttributes->direction = QVector3D(-0.75,-1,0.75);
//    spotLightAttributes->position = QVector3D(-100,65,-100);

//    spotLightAttributes->constant = 1.0;
//    spotLightAttributes->linear = 0.07;
//    spotLightAttributes->quadratic = 0.017;

//    spotLightAttributes->cutOff = cos(to_radians(25));
//    spotLightAttributes->outerCutOff = cos(to_radians(35));

//    spotLightAttributes->ambient = QVector3D(0.2,0.2,0.2);
//    spotLightAttributes->diffuse = QVector3D(1,1,1);
//    spotLightAttributes->specular = QVector3D(0,0,0);

//    lightning->addSpotLight(spotLight);

    this->sceneRoot->Start();

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
    lightning->updateLightning(&mainProgram, player.getCamera()->getCameraPosition());

    skybox->Draw(&skyboxProgram, geometries, projection, player.getCamera());

    sceneRoot->Update();
    sceneRoot->Draw(&mainProgram,geometries, projection, player.getCamera());

    paintEvent();
}

void MainWidget::keyPressEvent(QKeyEvent *ev)
{
    if(isPressed.find(ev->text()) == isPressed.end())
        isPressed.insert(ev->text(),false);

    if(ev->key() == Qt::Key_Control && isPressed.find("ctrl") == isPressed.end())
        isPressed.insert("ctrl",false);

    if(ev->text() == "z" && !isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = true;
    else if(ev->text() == "s" && !isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = true;
    else if(ev->text() == "q" && !isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = true;
    else if(ev->text() == "d" && !isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = true;
    else if(ev->text() == "c" && !isPressed.value(ev->text())){
        //qDebug("Changement de Caméra");
        if(player.getCamera()->getCameraMode() == player.getCamera()->CAMERA_MODE_ORBITAL)
            player.getCamera()->setCameraToStationaryMode();
        else if(player.getCamera()->getCameraMode() == player.getCamera()->CAMERA_MODE_STATIONARY)
            player.getCamera()->setCameraToOrbitalMode();
        isPressed.find(ev->text()).value() = true;
    }
    else if(ev->text() == " " && !isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = true;
    else if(ev->key() == Qt::Key_Control && !isPressed.value("ctrl"))
            isPressed.find("ctrl").value() = true;
    else if(ev->text() == "t" && !isPressed.value(ev->text()))
            isPressed.find(ev->text()).value() = true;
}

void MainWidget::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->text() == "z" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == "s" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == "q" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == "d" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == "c" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->text() == " " && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;
    else if(ev->key() == Qt::Key_Control && isPressed.value("ctrl"))
        isPressed.find("ctrl").value() = false;
    else if(ev->text() == "t" && isPressed.value(ev->text()))
        isPressed.find(ev->text()).value() = false;

    if(ev->key() == Qt::Key_T){
        changerTexture();
    }
    if(ev->key() == Qt::Key_M){
        changerMode();
    }
}

void MainWidget::updateCameraVelNorm(){
    QVector3D newVelNorm = QVector3D(0,0,0);
    QVector3D newRotNorm = QVector3D(0,0,0);

    if(this->isPressed.value("z"))
        newVelNorm += this->player.getCamera()->getCameraFront();
    if(this->isPressed.value("s"))
        newVelNorm -= this->player.getCamera()->getCameraFront();
    if(this->isPressed.value("d"))
        newVelNorm += player.getCamera()->getCameraRight();
    if(this->isPressed.value("q"))
        newVelNorm -= player.getCamera()->getCameraRight();

    if(this->isPressed.value(" ") and mode == 0)
        newVelNorm += player.getCamera()->getCameraUp();

    else if(this->isPressed.value(" ") and mode == 1){
        player.getRigidbody()->addForce(QVector3D(0,30 * player.getRigidbody()->getMass(),0));
    }


    if(this->isPressed.value("ctrl") and mode == 0)
        newVelNorm -= player.getCamera()->getCameraUp();

    this->playerCurrentVelocityNorm = newVelNorm;
    this->cameraCurrentRotationNorm = newRotNorm;
}
