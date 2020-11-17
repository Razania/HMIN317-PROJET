#include "chunk.h"

Chunk::Chunk(WorldGrid* parent, QPair<int, int> position, QVector3D chunkDimensions)
    : parent(parent), position(position), chunkDimensions(chunkDimensions)
{
    this->blocks.resize(chunkDimensions.x(),vector<vector<Block*>>(chunkDimensions.y(),vector<Block*>(chunkDimensions.z())));

    for(int i = 0; i < chunkDimensions.x(); i++)
        for(int j = 0; j < chunkDimensions.y(); j++)
            for(int k = 0; k < chunkDimensions.z(); k++)
                if(j<=64 || (j<= (64 + (chunkDimensions.x() - i - 1) + (chunkDimensions.z() - k - 1)))){
                    blocks[i][j][k] = new Block(BlockType::Stone);
                } else {
                    blocks[i][j][k] = new Block(BlockType::Air);
                }
}

QPair<int, int> Chunk::getPosition() const
{
    return position;
}

QVector3D Chunk::getChunkWorldPosition() const{
    float x = -this->getChunkDimensions().x()/2;
    float y = 0;
    float z = -this->getChunkDimensions().x()/2;

    if(this->getPosition().first != 0)
        x += (this->getPosition().first * this->getChunkDimensions().x()) ;
    if(this->getPosition().second != 0)
        z += (this->getPosition().second * this->getChunkDimensions().z());

    return QVector3D(x,y,z);
}

Block* Chunk::getBlockAt(QVector3D blockPos) const
{
    return blocks[blockPos.x()][blockPos.y()][blockPos.z()];
}

Chunk* Chunk::getNeighbour(QPair<int, int> neightbourOffset) const
{
    return this->parent->getChunk(QPair<int, int>(this->getPosition().first + neightbourOffset.first, this->getPosition().second + neightbourOffset.second));
}

QVector3D Chunk::getChunkDimensions() const
{
    return chunkDimensions;
}
