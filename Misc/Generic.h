#ifndef GENERIC_H
#define GENERIC_H

#include <QFileInfo>
#include <QVector3D>
#include <QVector2D>
#include <regex>
#include <Misc/enum.h>

BETTER_ENUM(FaceDirection, char, Right, Left, Top, Bottom, Back, Front);
BETTER_ENUM(BlockType, char, Air, Stone, Dirt, Grass);

//Vertices
struct BasicVertexData
{
    QVector3D position;
    QVector3D normal;
    QVector2D texCoord;
    unsigned int texLayer;
};

struct SkyboxVertexData
{
    QVector3D position;
};

//Lights
struct DirectionalLight{
    QVector3D direction;

    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
};

struct PointLight{
    QVector3D position;

    float constant;
    float linear;
    float quadratic;

    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
};

struct SpotLight{
    QVector3D direction;
    QVector3D position;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;

    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
};

#ifndef M_PI
    #define M_PI 3.1415926535
#endif

inline double to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

inline double to_radians(double degrees) {
    return (degrees * M_PI) / 180.0;
}

#include <type_traits>
template < typename C, C beginVal, C endVal>
class Iterator {
  typedef typename std::underlying_type<C>::type val_t;
  int val;
public:
  Iterator(const C & f) : val(static_cast<val_t>(f)) {}
  Iterator() : val(static_cast<val_t>(beginVal)) {}
  Iterator operator++() {
    ++val;
    return *this;
  }
  C operator*() { return static_cast<C>(val); }
  Iterator begin() { return *this; } //default ctor is good
  Iterator end() {
      static const Iterator endIter=++Iterator(endVal); // cache it
      return endIter;
  }
  bool operator!=(const Iterator& i) { return val != i.val; }
};

inline bool fileExists(QString path) {
    QFileInfo check_file(path);
    // check if path exists and if yes: Is it really a file and no directory?
    return check_file.exists() && check_file.isFile();
}

#endif // GENERIC_H
