#include "textureloader.h"
#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_1>
#include <QOpenGLExtraFunctions>

TextureLoader::TextureLoader(MainWidget* context) : context(context) {}

void TextureLoader::loadSkyboxTextures()
{
    std::vector<QImage> listOfTextures;
    context->makeCurrent();

    std::string baseName = ":/skybox";
    std::string ext = ".png";

    for(FaceDirection faceDirection : FaceDirection::_values()){
        QString fileName = QString((baseName + faceDirection._to_string() + ext).c_str());
        if(!fileExists(fileName))
            qDebug("Missing Texture %s", fileName.toStdString().c_str());

        QImage textureImage = QImage(fileName);
        listOfTextures.push_back(textureImage);
    }

    context->glActiveTexture(GL_TEXTURE1);
    context->glGenTextures(1, &skyboxTextureIndex);
    context->glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureIndex);

    unsigned int incr = 0;
    for(QImage image : listOfTextures){
        if(image.format() != QImage::Format::Format_ARGB32)
            image = image.convertToFormat(QImage::Format::Format_ARGB32);

        if(image.width() != 1024)
            image = image.scaledToWidth(1024);
        if(image.height() != 1024)
            image = image.scaledToHeight(1024);

        context->glTexImage2D(
               GL_TEXTURE_CUBE_MAP_POSITIVE_X + (incr++),
               0, GL_RGBA8, image.width(), image.height(), 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, image.bits()
           );
    }

    context->glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    context->glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    context->glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    context->glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    context->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

//    uchar* bits = ((uchar*) malloc(sizeof(uchar) * 1024 * 1024 * 4));
//    glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, bits);
//    for(int i = (1024 * 1024 * 4) - 4; i<(1024 * 1024 * 4); i++)
//        qDebug("%d ", bits[i]);
}

void TextureLoader::loadBlocksTextures()
{
    std::vector<QImage> listOfTextures;
    context->makeCurrent();
    unsigned int textureIndex = 0;
    for(BlockType blockType : BlockType::_values()){
        if(blockType._value == BlockType::Air)
            continue;

        bool multiFaced = true;
        for(FaceDirection faceDirection : FaceDirection::_values())
            if(!fileExists(this->getTextureName(blockType,faceDirection)))
                multiFaced = false;

        if(multiFaced){
            for(TextureFaceDirection textureFaceDirection : TextureFaceDirection::_values()){
                QString textureName = this->getTextureName(blockType,textureFaceDirection).toStdString().c_str();

                //qDebug("%lld -> %s", listOfTextures.size(), textureName.toStdString().c_str());
                QImage textureImage = QImage(textureName);
                listOfTextures.push_back(textureImage);
                this->texturesIndexList.insert(QPair<BlockType, TextureFaceDirection>(blockType, textureFaceDirection), textureIndex++);
            }
        }else{
            QString textureName = this->getTextureName(blockType).toStdString().c_str();

            //qDebug("%lld -> %s", listOfTextures.size(), textureName.toStdString().c_str());
            QImage textureImage = QImage(textureName);

            listOfTextures.push_back(textureImage);
            this->texturesIndexList.insert(QPair<BlockType, TextureFaceDirection>(blockType, TextureFaceDirection::Bottom), textureIndex);
            this->texturesIndexList.insert(QPair<BlockType, TextureFaceDirection>(blockType, TextureFaceDirection::Side), textureIndex);
            this->texturesIndexList.insert(QPair<BlockType, TextureFaceDirection>(blockType, TextureFaceDirection::Top), textureIndex++);
        }
    }

    context->glActiveTexture(GL_TEXTURE0);
    context->glGenTextures(1, &texturesListIndex);
    context->glBindTexture(GL_TEXTURE_2D_ARRAY, texturesListIndex);

    GLsizei depth = listOfTextures.size();

    unsigned int layer = 0;
    for(QImage image : listOfTextures){
        if(image.format() != QImage::Format::Format_ARGB32)
            image = image.convertToFormat(QImage::Format::Format_ARGB32);

        if(image.width() != 480)
            image = image.scaledToWidth(480);
        if(image.height() != 480)
            image = image.scaledToHeight(480);

        if(layer == 0)
            context->glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, image.width(), image.height(), depth);

        context->glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer++, image.width(), image.height(), 1, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, image.bits());
    }

    context->glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    context->glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    context->glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    context->glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    context->glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, GL_REPEAT);


//    uchar* bits = ((uchar*) malloc(sizeof(uchar) * 4 * 480 * 480 * depth));
//    glGetTexImage(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);
//    for(int i = (4 * 480 * 480 * 3); i<(4 * 480 * 480 * 3) + 4; i++)
//        qDebug("%d ", bits[i]);
}

MainWidget *TextureLoader::getContext() const
{
    return context;
}

unsigned int TextureLoader::getTextureIndex_Unifaced(BlockType blockType) const
{
    return this->texturesIndexList[QPair<BlockType, TextureFaceDirection>(blockType, TextureFaceDirection::Bottom)];
}

unsigned int TextureLoader::getTextureIndex_Multifaced(BlockType blockType, FaceDirection faceDirection) const
{
    return this->texturesIndexList[QPair<BlockType, TextureFaceDirection>(blockType, this->getTextureFaceDirection(faceDirection))];
}

unsigned int TextureLoader::getBlockFaceTexture(BlockType blockType, FaceDirection faceDirection) const
{
    return this->getTextureIndex_Multifaced(blockType, faceDirection);
}

TextureFaceDirection TextureLoader::getTextureFaceDirection(FaceDirection faceDirection) const
{
    if(faceDirection._value == FaceDirection::Bottom)
        return TextureFaceDirection::Bottom;
    else if(faceDirection._value == FaceDirection::Top)
        return TextureFaceDirection::Top;
    else
        return TextureFaceDirection::Side;
}

QString TextureLoader::getTextureName(BlockType blockType, TextureFaceDirection textureFaceDirection) const
{
    std::string blockTypeName = blockType._to_string();
    std::transform(blockTypeName.begin(), blockTypeName.end(), blockTypeName.begin(), ::tolower);
    std::string faceDirectionName = textureFaceDirection._to_string();
    std::transform(faceDirectionName.begin(), faceDirectionName.end(), faceDirectionName.begin(), ::tolower);
    faceDirectionName[0] = toupper(faceDirectionName[0]);

    std::string textureName = ":/" + blockTypeName + faceDirectionName + ".png";

    return QString(textureName.c_str());
}

QString TextureLoader::getTextureName(BlockType blockType, FaceDirection faceDirection) const
{
    std::string blockTypeName = blockType._to_string();
    std::transform(blockTypeName.begin(), blockTypeName.end(), blockTypeName.begin(), ::tolower);
    std::string faceDirectionName = this->getTextureFaceDirection(faceDirection)._to_string();
    std::transform(faceDirectionName.begin(), faceDirectionName.end(), faceDirectionName.begin(), ::tolower);
    faceDirectionName[0] = toupper(faceDirectionName[0]);

    std::string textureName = ":/" + blockTypeName + faceDirectionName + ".png";

    return QString(textureName.c_str());
}

QString TextureLoader::getTextureName(BlockType blockType) const
{
    std::string blockTypeName = blockType._to_string();
    std::transform(blockTypeName.begin(), blockTypeName.end(), blockTypeName.begin(), ::tolower);

    std::string textureName = ":/" + blockTypeName + ".png";

    return QString(textureName.c_str());
}

GLuint TextureLoader::getSkyboxTextureIndex() const
{
    return skyboxTextureIndex;
}

GLuint TextureLoader::getTextureArrayIndex()
{
    return this->texturesListIndex;
}

