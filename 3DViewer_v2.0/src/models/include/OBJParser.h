//
// Created by AdisAlagic on 15.09.2024.
//

#ifndef OBJPARSER_H
#define OBJPARSER_H
#include <istream>
#include <sstream>
#include <vector>

namespace s21 {
typedef enum CSType { bmatrix, bezier, bspline, cardinal, taylor } CSType;
typedef enum MatrixType { U, V } MatrixType;
typedef enum SyntaxType {
  VLine,
  FLine,
  CSTypeLine,
} SyntaxType;

template <typename T>
struct OBJType {
  T data;
  bool isOptional = false;
  explicit OBJType(const T &data) : data(data) {}
  explicit OBJType(double data, const bool optional)
      : data(data), isOptional(optional) {}
  OBJType &operator=(const T &data) {
    this->data = data;
    return *this;
  }
  bool operator==(const T &b) { return this->data == b.data; }
};

constexpr double NO_DATA_DOUBLE = 0xFFFFFFFFFF;
constexpr int NO_DATA_INT = 0xFFFFFFF;

using ODouble = OBJType<double>;
using OLong = OBJType<long>;

typedef struct vertex_ {
  ODouble u = ODouble(NO_DATA_DOUBLE), v = ODouble(NO_DATA_DOUBLE),
          w = ODouble(1.0, true);
} vertex_;

typedef struct GeometricVertex {
  static const char *syntaxOffset_;
  ODouble x = ODouble(NO_DATA_DOUBLE), y = ODouble(NO_DATA_DOUBLE),
          z = ODouble(NO_DATA_DOUBLE), w = ODouble(1.0, true);
} GeometricVertex;

typedef struct VertexNormal {
  static const char *syntaxOffset_;
  ODouble i = ODouble(NO_DATA_DOUBLE), j = ODouble(NO_DATA_DOUBLE),
          k = ODouble(NO_DATA_DOUBLE);
} VertexNormal;

typedef struct Face {
  ODouble v = ODouble(NO_DATA_DOUBLE),
          //          vt = ODouble(NO_DATA_DOUBLE, true),
      vn = ODouble(NO_DATA_DOUBLE, true);
} Face;

typedef struct FaceNormal {
  static const char *syntaxOffset_;
  std::vector<Face> faces;
} FaceNormal;

typedef struct OBJNotation {
  std::vector<GeometricVertex> geometricVertices;
  std::vector<FaceNormal> faceNormalVertices;
} OBJNotation;

class OBJParser {
 public:
  OBJNotation *parse(std::istream &istream);

#ifdef TEST
 public:
#else
 private:
#endif
  bool countParseTime = true;
  SyntaxType context = static_cast<SyntaxType>(-1);
  long long int currentMatrixIndex_ = -1;
  OBJParser() = default;
  ~OBJParser() = default;
  OBJNotation *notation_ = nullptr;

  SyntaxType getType(const char *type) const;
  void parseF(const std::string &input) const;
  void parseType(const SyntaxType &type, std::string &input) const;
  void parseV(std::string const &input) const;

  friend OBJNotation *parseOBJ(std::istream &istream);
};

inline const char *CSTypeStr(CSType t);
inline CSType stringToCSType(const std::string &type);
inline MatrixType stringToMatrixType(std::string const &str);
OBJNotation *parseOBJ(std::istream &istream);

}  // namespace s21

#endif  // OBJPARSER_H
