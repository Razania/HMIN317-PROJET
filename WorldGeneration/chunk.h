#ifndef CHUNK_H
#define CHUNK_H

class Chunk;

#include <QVector3D>
#include <vector>
#include <WorldGeneration/block.h>
#include <WorldGeneration/worldgrid.h>

class Chunk
{
public:
    Chunk(WorldGrid* parent, QPair<int, int> position, QVector3D chunkDimensions);

    QPair<int, int> getPosition() const;
    QVector3D getChunkWorldPosition() const;

    Block* getBlockAt(QVector3D blockPos) const;
    Chunk* getNeighbour(QPair<int, int> neightbourOffset) const;

    QVector3D getChunkDimensions() const;

private:
    WorldGrid* parent;
    QPair<int, int> position;
    QVector3D chunkDimensions;
    std::vector<std::vector<std::vector<Block*>>> blocks;
};

#endif // CHUNK_H
