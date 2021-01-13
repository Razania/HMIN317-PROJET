#include "worldgrid.h"

WorldGrid::WorldGrid(int seed, QVector3D chunkDimensions)
    : chunkDimensions(chunkDimensions), seed(seed)
{
}

Chunk* WorldGrid::getChunkAtWorldPos(QVector3D worldPos)
{
    QPair<int, int> chunkPos = this->worldPosToChunkPos(worldPos);

    if(this->chunks.count(chunkPos) == 0)
        return nullptr;

    return this->chunks[chunkPos];
}

std::vector<QPair<int, int>> WorldGrid::getChunksAtWorldPosForSize(QVector3D worldPos, QVector2D size)
{
    std::vector<QPair<int, int>> foundValues;

    float xDivider = 2 + size.x() / this->chunkDimensions.x();
    float yDivider = 2 + size.y() / this->chunkDimensions.z();

    //qDebug("2 + (%f / %f) =  %f", size.x(), this->chunkDimensions.x(), xDivider);
    //qDebug("2 + (%f / %f) =  %f", size.y(), this->chunkDimensions.z(), yDivider);

    for(float x = -size.x()/2.0; x <= size.x()/2.0; x+=(size.x() / xDivider))
        for(float y = -size.y()/2.0; y <= size.y()/2.0; y+=(size.y() / yDivider)){
            QVector3D newWorldPos = worldPos + QVector3D(x,0,y);
            QPair<int, int> chunkPos = this->worldPosToChunkPos(newWorldPos);

            //qDebug("(%f, %f, %f) => (%d, %d) -> %d", newWorldPos.x(), newWorldPos.y(), newWorldPos.z(), chunkPos.first, chunkPos.second, std::find(foundValues.begin(), foundValues.end(), chunkPos) == foundValues.end());
            if(this->chunks.count(chunkPos) != 0 && std::find(foundValues.begin(), foundValues.end(), chunkPos) == foundValues.end()){
                foundValues.push_back(chunkPos);
            }
        }

    return foundValues;
}

QPair<int, int> WorldGrid::worldPosToChunkPos(QVector3D worldPos) const{
    int x; //Find x
    if(abs(worldPos.x()) <= this->chunkDimensions.x()/2)
        x = 0;
    else
        x = (worldPos.x() + this->chunkDimensions.x()/2)/this->chunkDimensions.x();

    int y; //Find y
    if(abs(worldPos.z()) <= this->chunkDimensions.z()/2)
        y = 0;
    else
        y = (worldPos.z() + this->chunkDimensions.z()/2)/this->chunkDimensions.z();

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

int WorldGrid::getSeed() const
{
    return seed;
}

QVector3D WorldGrid::getChunkDimensions() const
{
    return chunkDimensions;
}
