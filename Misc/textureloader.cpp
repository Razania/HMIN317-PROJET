#include "textureloader.h"
#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_1>
#include <QOpenGLExtraFunctions>

TextureLoader::TextureLoader(MainWidget* context) : context(context)
{
    context->makeCurrent();
    int textureIndex = 0;
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

                //qDebug() << textureName << endl;
                QImage* textureImage = new QImage(textureName);
                //(*textureImage) = textureImage->mirrored();
                listOfTextures.push_back(textureImage);
                this->texturesIndexList.insert(QPair<BlockType, TextureFaceDirection>(blockType, textureFaceDirection), textureIndex++);
            }
        }else{
            QString textureName = this->getTextureName(blockType).toStdString().c_str();

            qDebug() << textureName << endl;
            QImage* textureImage = new QImage(textureName);
            //(*textureImage) = textureImage->mirrored();
            listOfTextures.push_back(textureImage);
            this->texturesIndexList.insert(QPair<BlockType, TextureFaceDirection>(blockType, TextureFaceDirection::Bottom), textureIndex);
            this->texturesIndexList.insert(QPair<BlockType, TextureFaceDirection>(blockType, TextureFaceDirection::Side), textureIndex);
            this->texturesIndexList.insert(QPair<BlockType, TextureFaceDirection>(blockType, TextureFaceDirection::Top), textureIndex++);
        }
    }

//    this->texturesList = new QOpenGLTexture(QOpenGLTexture::Target3D);
//    texturesList->create();
//    texturesList->bind(2);

//    texturesList->setMipLevels(0);
//    texturesList->generateMipMaps();

//    texturesList->setSize(listOfTextures[0]->width(), listOfTextures[0]->height(), listOfTextures.size());
//    texturesList->setFormat(QOpenGLTexture::RGBA32I);

//    texturesList->setMinificationFilter(QOpenGLTexture::Linear);
//    texturesList->setMagnificationFilter(QOpenGLTexture::Linear);
//    texturesList->setWrapMode(QOpenGLTexture::ClampToEdge);
//    texturesList->allocateStorage(QOpenGLTexture::PixelFormat::BGRA, QOpenGLTexture::PixelType::UInt32);

//    GLuint textureID = 0;
//    this->context->glGenTextures(1,&textureID);
//    this->context->glBindTexture(GL_TEXTURE_3D,textureID);
//    this->context->glTexStorage3D(GL_TEXTURE_3D, 1, GL_BGRA, listOfTextures[0]->width(), listOfTextures[0]->height(), listOfTextures.size());

//    //this->context->glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, listOfTextures[0]->width(), listOfTextures[0]->height(), 1, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, listOfTextures[0]->data_ptr());
//    //texturesList->setData(0, 0, 0, listOfTextures[0]->width(), listOfTextures[0]->height(), listOfTextures[0]->depth(), 0, QOpenGLTexture::PixelFormat::BGRA, QOpenGLTexture::PixelType::UInt32_RGBA8_Rev, listOfTextures[0]->data_ptr());
//    this->context->glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_TRUE);
//    int layerCount = 0;
//    for(QImage* texture : listOfTextures){
//        this->context->glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, layerCount++, listOfTextures[0]->width(), listOfTextures[0]->height(), listOfTextures.size(), GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, texture->data_ptr());
//    }
//    this->context->glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
}

int TextureLoader::getTextureIndex_Unifaced(BlockType blockType) const
{
    return this->texturesIndexList[QPair<BlockType, TextureFaceDirection>(blockType, TextureFaceDirection::Bottom)];
}

int TextureLoader::getTextureIndex_Multifaced(BlockType blockType, FaceDirection faceDirection) const
{
    return this->texturesIndexList[QPair<BlockType, TextureFaceDirection>(blockType, this->getTextureFaceDirection(faceDirection))];
}

QOpenGLTexture *TextureLoader::getTexturesList() const
{
    return texturesList;
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
