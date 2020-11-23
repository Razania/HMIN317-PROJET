#ifndef BLOCK_H
#define BLOCK_H

#include <Misc/Generic.h>
#include <Misc/enum.h>

BETTER_ENUM(FaceDirection, char, Bottom, Top, Right, Left, Front, Back);
BETTER_ENUM(BlockType, char, Air, Stone, Dirt);

class Block
{
public:
    Block(BlockType type) : type(type){}
    BlockType getType() const;

    bool canDrawFaceTowardBlock(Block* targetBlock);

private:
    BlockType type;
};

#endif // BLOCK_H
