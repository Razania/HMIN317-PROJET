#ifndef GENERIC_H
#define GENERIC_H

#include <QFileInfo>
#include <regex>

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
