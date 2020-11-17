#ifndef BLOCK_H
#define BLOCK_H

enum class BlockType{
    Air = 0,
    Stone = 1,
    Dirt = 2
};


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
