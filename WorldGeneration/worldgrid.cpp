#include "worldgrid.h"

WorldGrid::WorldGrid(QVector3D chunkDimensions)
    : chunkDimensions(chunkDimensions)
{}

Chunk* WorldGrid::getChunkAtWorldPos(QVector3D worldPos)
{
    QPair<int, int> chunkPos = this->worldPosToChunkPos(worldPos);

    if(this->chunks.count(chunkPos) == 0)
        return nullptr;

    return this->chunks[chunkPos];
}

QPair<int, int> WorldGrid::worldPosToChunkPos(QVector3D worldPos) const{
    int x; //Find x
    if(abs(worldPos.x()) <= this->chunkDimensions.x()/2)
        x = 0;
    else
        x = (worldPos.x() + this->chunkDimensions.x()/2)/this->chunkDimensions.x();

    int y; //Find y
    if(abs(worldPos.y()) <= this->chunkDimensions.x()/2)
        y = 0;
    else
        y = (worldPos.y() + this->chunkDimensions.x()/2)/this->chunkDimensions.x();

    return QPair<int, int>(x,y);
}

Chunk *WorldGrid::getChunk(QPair<int, int> chunkPos)
{
    if(this->chunks.count(chunkPos) == 0)
        return nullptr;
    return this->chunks[chunkPos];
}

void WorldGrid::generateChunk(QPair<int, int> chunkPos){
    this->chunks[chunkPos] = new Chunk(this, chunkPos, this->chunkDimensions);
}
