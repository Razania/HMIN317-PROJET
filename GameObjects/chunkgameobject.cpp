#include "chunkgameobject.h"

#include <Misc/textureloader.h>

ChunkGameObject::ChunkGameObject(Chunk* chunk)
{
    generateSurface(chunk);
}

void ChunkGameObject::generateSurface(Chunk* chunk)
{
    this->vertices.resize(0);
    this->indices.resize(0);

    //qDebug("Generate Surface of Chunk (%d, %d)\n",chunk->getPosition().first, chunk->getPosition().second);

    //Reset BoxColliders
    //this->stashCurrentActiveBlocksColliders();

    for(int i = 0; i<chunk->getChunkDimensions().x(); i++) //x
        for(int j = 0; j<chunk->getChunkDimensions().y(); j++) //y
            for(int k = 0; k<chunk->getChunkDimensions().z(); k++){ //z
                Block* currentBlock = chunk->getBlockAt(QVector3D(i,j,k));

                bool isDrawn = false;

                if(currentBlock->getType()._value == BlockType::Air) //If current block is air no need to draw it
                    continue;

                //To Bottom Face
                if(j == 0){//Bottom of Chunk => Always draw
                    //Draw Bottom Face
                    this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Bottom);
                    isDrawn = true;
                } else {
                    if(currentBlock->canDrawFaceTowardBlock(chunk->getBlockAt(QVector3D(i,j-1,k)))){
                        //Draw Bottom Face
                        this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Bottom);
                        isDrawn = true;
                    }
                }

                //To Top Face
                if(j == chunk->getChunkDimensions().y() - 1){//Top of Chunk => Always draw
                    //Draw Top Face
                    this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Top);
                    isDrawn = true;
                } else {
                    if(currentBlock->canDrawFaceTowardBlock(chunk->getBlockAt(QVector3D(i,j+1,k)))){
                        //Draw Top Face
                        this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Top);
                        isDrawn = true;
                    }
                }

                //To Left Face
                if(i == 0){//Left of Chunk => Check Block of Left Neighbour Chunk
                    Chunk* neighbour = chunk->getNeighbour(QPair<int,int>(-1,0));

                    if(neighbour == nullptr || (neighbour != nullptr && currentBlock->canDrawFaceTowardBlock(neighbour->getBlockAt(QVector3D(chunk->getChunkDimensions().x() - 1,j,k))))){
                        //Draw Left Face
                        this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Left);
                        isDrawn = true;
                    }
                } else {
                    if(currentBlock->canDrawFaceTowardBlock(chunk->getBlockAt(QVector3D(i-1,j,k)))){
                        //Draw Left Face
                        this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Left);
                        isDrawn = true;
                    }
                }

                //To Right Face
                if(i == chunk->getChunkDimensions().x() - 1){//Right of Chunk => Check Block of Right Neighbour Chunk
                    Chunk* neighbour = chunk->getNeighbour(QPair<int,int>(1,0));

                    if(neighbour == nullptr || (neighbour != nullptr && currentBlock->canDrawFaceTowardBlock(neighbour->getBlockAt(QVector3D(0,j,k))))){
                        //Draw Right Face
                        this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Right);
                        isDrawn = true;
                    }
                } else {
                    if(currentBlock->canDrawFaceTowardBlock(chunk->getBlockAt(QVector3D(i+1,j,k)))){
                        //Draw Right Face
                        this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Right);
                        isDrawn = true;
                    }
                }

                //To Back Face
                if(k == 0){//Back of Chunk => Check Block of Back Neighbour Chunk
                    Chunk* neighbour = chunk->getNeighbour(QPair<int,int>(0,-1));

                    if(neighbour == nullptr || (neighbour != nullptr && currentBlock->canDrawFaceTowardBlock(neighbour->getBlockAt(QVector3D(i,j,chunk->getChunkDimensions().z() -1))))){
                        //Draw Back Face
                        this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Back);
                        isDrawn = true;
                    }
                } else {
                    if(currentBlock->canDrawFaceTowardBlock(chunk->getBlockAt(QVector3D(i,j,k-1)))){
                        //Draw Back Face
                        this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Back);
                        isDrawn = true;
                    }
                }

                //To Front Face
                if(k == chunk->getChunkDimensions().z() - 1){//Front of Chunk => Check Block of Front Neighbour Chunk
                    Chunk* neighbour = chunk->getNeighbour(QPair<int,int>(0,1));

                    if(neighbour == nullptr || (neighbour != nullptr && currentBlock->canDrawFaceTowardBlock(neighbour->getBlockAt(QVector3D(i,j,0))))){
                        //Draw Front Face
                        this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Front);
                        isDrawn = true;
                    }
                } else {
                    if(currentBlock->canDrawFaceTowardBlock(chunk->getBlockAt(QVector3D(i,j,k+1)))){
                        //Draw Front Face
                        this->addBlockFace(chunk, QVector3D(i,j,k), FaceDirection::Front);
                        isDrawn = true;
                    }
                }

                if(false && isDrawn){
                    //Ajouter BoxCollider pour ce cube
                    BoxCollider * collider = this->fetchNewActiveBlockCollider();
                    collider->getTransform()->setParent(this->transform);

                    collider->getTransform()->setLocalPosition(QVector3D(i,j,k));
                    qDebug("%f %f %f", collider->getTransform()->getWorldPosition().x(), collider->getTransform()->getWorldPosition().y(), collider->getTransform()->getWorldPosition().z());
                }
            }
}

void ChunkGameObject::addBlockFace(Chunk* chunk, QVector3D blockPos, FaceDirection face)
{
    QVector3D chunckBaseWorldPos = chunk->getChunkWorldPosition();
    QVector3D voxelSize = QVector3D(1, 1, 1);
    unsigned int firstFaceVertexIndex = this->vertices.size();
    Block* block = chunk->getBlockAt(blockPos);

    //qDebug("Block of Type %s for Face %s -> texture %d", block->getType()._to_string(), face._to_string(), TextureLoader::instance()->getBlockFaceTexture(block->getType(), face));

    switch(face._value){
        case FaceDirection::Bottom :
            // --- Bottom Face ---
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(0,-1,0)
                                      , QVector2D(0,0)
                                      , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                    }); // Bottom Back Left
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(0,-1,0)
                                      , QVector2D(1,0)
                                      , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                    }); // Bottom Back Right
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(0,-1,0)
                                      , QVector2D(1,1)
                                      , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                    }); // Bottom Front Right
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(0,-1,0)
                                      , QVector2D(0,1)
                                      , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                    }); // Bottom Front Left
            break;
        case FaceDirection::Top :
            // --- Top Face ---
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(0,1,0)
                                      , QVector2D(0,0)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                    }); // Top Back Right
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(0,1,0)
                                      , QVector2D(1,0)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                    }); // Top Back Left
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(0,1,0)
                                      , QVector2D(1,1)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Top Front Left
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(0,1,0)
                                      , QVector2D(0,1)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Top Front Right
            break;
        case FaceDirection::Left :
            // --- Left Face ---
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(-1,0,0)
                                      , QVector2D(0,0)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Top Front Left
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(-1,0,0)
                                      , QVector2D(1,0)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Top Back Left
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(-1,0,0)
                                      , QVector2D(1,1)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Bottom Back Left
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(-1,0,0)
                                      , QVector2D(0,1)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Bottom Front Left
            break;
        case FaceDirection::Right :
            // --- Right Face ---
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(1,0,0)
                                      , QVector2D(0,0)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Top Back  Right
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(1,0,0)
                                      , QVector2D(1,0)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Top Front  Right
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(1,0,0)
                                      , QVector2D(1,1)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Bottom Front  Right
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(1,0,0)
                                      , QVector2D(0,1)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Bottom Back Right
            break;
        case FaceDirection::Back :
            // --- Back Face ---
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(0,0,-1)
                                      , QVector2D(0,0)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Top Back Left
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(0,0,-1)
                                      , QVector2D(1,0)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Top Back Right
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(0,0,-1)
                                      , QVector2D(1,1)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Bottom Back Right
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z())
                                      , QVector3D(0,0,-1)
                                      , QVector2D(0,1)
                                         , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Bottom Back Left
            break;
        case FaceDirection::Front :
            // --- Front Face ---
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(0,0,1)
                                      , QVector2D(0,0)
                                      , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Top Front Right
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y() + voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(0,0,1)
                                      , QVector2D(1,0)
                                      , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Top Front Left
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(0,0,1)
                                      , QVector2D(1,1)
                                      , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Bottom Front Left
            this->vertices.push_back(BasicVertexData{
                                        QVector3D( chunckBaseWorldPos.x() + blockPos.x() * voxelSize.x() + voxelSize.x()
                                                 , chunckBaseWorldPos.y() + blockPos.y() * voxelSize.y()
                                                 , chunckBaseWorldPos.z() + blockPos.z() * voxelSize.z() + voxelSize.z())
                                      , QVector3D(0,0,1)
                                      , QVector2D(0,1)
                                      , TextureLoader::instance()->getBlockFaceTexture(block->getType(),face)
                                     }); // Bottom Front Right
            break;
        default : return; //Unknown Face => Don't draw / trigger error
    }

    //Triangle1
    this->indices.push_back(firstFaceVertexIndex);
    this->indices.push_back(firstFaceVertexIndex+1);
    this->indices.push_back(firstFaceVertexIndex+2);
    //Triangle2
    this->indices.push_back(firstFaceVertexIndex+2);
    this->indices.push_back(firstFaceVertexIndex+3);
    this->indices.push_back(firstFaceVertexIndex);
}

BoxCollider *ChunkGameObject::fetchNewActiveBlockCollider()
{
    BoxCollider * blockCollider;
    if(reserveBlocksColliders.size() != 0){
        blockCollider = reserveBlocksColliders.at(reserveBlocksColliders.size() - 1);
        reserveBlocksColliders.pop_back();
    }
    else
        blockCollider = new BoxCollider(QVector3D(0,0,0), QVector3D(0,0,0));

    blockCollider->setSize(QVector3D(1,1,1));
    blockCollider->setAnchorPos(QVector3D(0.5,0.5,0.5));

    activeBlocksColliders.push_back(blockCollider);

    return blockCollider;
}

void ChunkGameObject::stashCurrentActiveBlocksColliders()
{
    if(activeBlocksColliders.size() == 0)
        return;

    std::vector<BoxCollider*> buffer;
    buffer.reserve(activeBlocksColliders.size() + reserveBlocksColliders.size());

    buffer.insert(buffer.end(), reserveBlocksColliders.begin(), reserveBlocksColliders.end());
    buffer.insert(buffer.end(), activeBlocksColliders.begin(), activeBlocksColliders.end());

    reserveBlocksColliders.clear();
    reserveBlocksColliders = buffer;
}

std::vector<BoxCollider*> ChunkGameObject::getActiveBlocksColliders() const
{
    return activeBlocksColliders;
}

void ChunkGameObject::Draw(QOpenGLShaderProgram *program, GeometryEngine *geometries, QMatrix4x4 projection, Camera* camera) {
    program->bind();

    program->setUniformValue("m_matrix", this->transform->worldMatrix());
    program->setUniformValue("v_matrix", camera->getViewMatrix());
    program->setUniformValue("p_matrix", projection);

    TextureLoader::instance()->getContext()->glActiveTexture(GL_TEXTURE0);
    TextureLoader::instance()->getContext()->glBindTexture(GL_TEXTURE_2D_ARRAY, TextureLoader::instance()->getTextureArrayIndex());
    program->setUniformValue("textureList", 0);

    geometries->drawMeshObjGeometry_BasicVertexData(program, &vertices, &indices);

    program->release();
}

void ChunkGameObject::Start() {}
void ChunkGameObject::Update() {}


