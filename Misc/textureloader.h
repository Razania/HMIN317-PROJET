#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <QMap>
#include <WorldGeneration/block.h>
#include <Misc/Generic.h>
#include <QOpenGLFunctions_3_1>
#include <QOpenGLTexture>
#include <optional>
#include <Misc/enum.h>
#include <Main/mainwidget.h>

BETTER_ENUM(TextureFaceDirection, char, Bottom, Side, Top);

class TextureLoader
{
public:

    static TextureLoader * instance() { return _instance; }

    static void initInstance(MainWidget* context) {
        if ( _instance == nullptr ) {
            _instance = new TextureLoader(context);
        }
    }

    int getTextureIndex_Unifaced(BlockType blockType) const;
    int getTextureIndex_Multifaced(BlockType blockType, FaceDirection faceDirection) const;

    QOpenGLTexture *getTexturesList() const;

private:
    TextureLoader(MainWidget* context);

    MainWidget* context;
    inline static TextureLoader * _instance = nullptr;
    QOpenGLTexture* texturesList;
    std::vector<QImage*> listOfTextures;
    QMap<QPair<BlockType, TextureFaceDirection>, int> texturesIndexList;

    TextureFaceDirection getTextureFaceDirection(FaceDirection faceDirection) const;

    QString getTextureName(BlockType blockType, TextureFaceDirection textureFaceDirection) const;
    QString getTextureName(BlockType blockType, FaceDirection faceDirection) const;
    QString getTextureName(BlockType blockType) const;
};

#endif // TEXTURELOADER_H
