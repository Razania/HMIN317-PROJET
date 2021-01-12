#ifndef BLOCK_H
#define BLOCK_H

class Block;

#include <Misc/Generic.h>
#include <WorldGeneration/chunk.h>

class Block
{
public:
    Block(Chunk *parentChunk, QVector3D blockPos, BlockType type) : parentChunk(parentChunk), blockPos(blockPos),type(type){}
    BlockType getType() const;

    bool canDrawFaceTowardBlock(Block* targetBlock);

    QVector3D getBlockPos() const;

private:
    Chunk *parentChunk;
    QVector3D blockPos;
    BlockType type;
};

#endif // BLOCK_H
