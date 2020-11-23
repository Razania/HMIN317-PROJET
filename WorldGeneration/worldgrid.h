#ifndef WORLDGRID_H
#define WORLDGRID_H

#include <QVector3D>
#include <QMap>
#include <QPair>

#include <PerlinNoise/PerlinNoise.hpp>
class WorldGrid;

#include "chunk.h"


class WorldGrid
{
public:
    WorldGrid(int seed,QVector3D chunkDimensions);

    Chunk* getChunk(QPair<int, int> chunkPos);
    Chunk* getChunkAtWorldPos(QVector3D worldPos);

    QPair<int, int> worldPosToChunkPos(QVector3D worldPos) const;

    void generateChunk(QPair<int, int> chunkPos);

    int getSeed() const;

private:
    QVector3D chunkDimensions;
    int seed;
    QMap<QPair<int,int>,Chunk*> chunks;

};

#endif // WORLDGRID_H
