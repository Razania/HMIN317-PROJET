#include "block.h"

BlockType Block::getType() const
{
    return type;
}

bool Block::canDrawFaceTowardBlock(Block* targetBlock)
{
    if(this->type._value == BlockType::Air)
        return false;
    if(targetBlock->getType()._value != BlockType::Air)
        return false;

    return true;
}

QVector3D Block::getBlockPos() const
{
    return blockPos;
}
