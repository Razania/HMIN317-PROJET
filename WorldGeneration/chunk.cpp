#include "chunk.h"
#include <QDebug>
#include "noise/src/noise.h"

Chunk::Chunk(WorldGrid* parent, QPair<int, int> position, QVector3D chunkDimensions)
    : parent(parent), position(position), chunkDimensions(chunkDimensions)
{
    this->blocks.resize(chunkDimensions.x(),vector<vector<Block*>>(chunkDimensions.y(),vector<Block*>(chunkDimensions.z())));

    for(int i = 0; i < chunkDimensions.x(); i++)
        for(int k = 0; k < chunkDimensions.z(); k++){
            float freq = 64.0f;
            QVector3D blockWorldPos = this->getChunkWorldPosition() + QVector3D(i,0,k);
            noise::module::Perlin noiseGen = noise::module::Perlin();
            noiseGen.SetFrequency(freq);
            noiseGen.SetOctaveCount(2);
            noiseGen.SetLacunarity(0.1f);

            double f = noiseGen.GetValue(blockWorldPos.x()/freq,blockWorldPos.z()/freq,0);
            f = (f+1)/2;

            //qDebug() << f << endl;
            int maxLayer = (f * (chunkDimensions.y() - 1) / 20) + ((chunkDimensions.y() - 1) / 20);
            int baseLayer = (chunkDimensions.y() - 1) / 8;

            for(int j = 0; j < chunkDimensions.y(); j++){
                if(j<=(maxLayer+baseLayer)){
                    blocks[i][j][k] = new Block(BlockType::Stone);
                } else {
                    blocks[i][j][k] = new Block(BlockType::Air);
                }
            }
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
