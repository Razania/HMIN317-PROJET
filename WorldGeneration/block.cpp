#include "block.h"

BlockType Block::getType() const
{
    return type;
}

bool Block::canDrawFaceTowardBlock(Block* targetBlock)
{
    if(this->type == BlockType::Air)
        return false;
    if(targetBlock->getType() != BlockType::Air)
        return false;

    return true;
}
