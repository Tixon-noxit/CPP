//
// Created by AdisAlagic on 15.09.2024.
//

#include "../include/OBJParser.h"

#include <chrono>
#include <iostream>

#include "../include/utils.h"
namespace s21 {
const char* GeometricVertex::syntaxOffset_ = "v";
const char* FaceNormal::syntaxOffset_ = "f";

OBJNotation* OBJParser::parse(std::istream& istream) {
  if (notation_) delete notation_;
  notation_ = new OBJNotation();
  auto limeCounter = 0;
  std::string line;
  try {
    while (!istream.eof()) {
      std::string typeStr;
      std::getline(istream, line, '\n');
      std::getline(std::istringstream(line), typeStr, ' ');
      parseType(getType(typeStr.c_str()), line);
      limeCounter++;
    }
  } catch (std::exception& e) {
    throw std::runtime_error(std::string("Invalid line #") +
                             std::to_string(limeCounter) + ":\n" + e.what() +
                             "\nProblem string: \"" + line + "\"");
  }

  return notation_;
}

SyntaxType OBJParser::getType(const char* type) const {
  const std::string typeStr(type);
  if (typeStr == GeometricVertex::syntaxOffset_) {
    return VLine;
  } else if (typeStr == FaceNormal::syntaxOffset_) {
    return FLine;
  } else {
    return static_cast<SyntaxType>(-1);
  }
}

void OBJParser::parseF(const std::string& input) const {
  FaceNormal face_normal;
  if (notation_ == nullptr) return;
  const auto splitted = split(trim(const_cast<std::string&>(input)), ' ');
  if (splitted.size() < 2) throw std::invalid_argument("Invalid face normal");
  for (int i = 1; i < splitted.size(); i++) {
    Face face;
    auto str = splitted[i];
    auto nums = split(trim(str), '/');
    for (int j = 0; j < nums.size(); j++) {
      try {
        if (j == 0) face.v = std::stod(nums[j]);
        if (j == 2) face.vn = std::stod(nums[j]);
      } catch ([[maybe_unused]] const std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Invalid face number: ") + "'" +
                                    nums[j] + "'");
      }
    }
    face_normal.faces.push_back(face);
  }
  notation_->faceNormalVertices.push_back(face_normal);
}

void OBJParser::parseType(const SyntaxType& type, std::string& input) const {
  removeStringSpaces(input);
  switch (type) {
    case VLine:
      parseV(input);
      break;
    case FLine:
      parseF(input);
      break;
    default:
      break;
  }
}

void OBJParser::parseV(std::string const& input) const {
  if (notation_ == nullptr) return;
  std::istringstream iss(input);
  GeometricVertex v;
  std::string type;
  iss >> type;  // ignore
  iss >> v.x.data;
  if (iss.fail()) throw std::invalid_argument("Invalid geometric vertex");
  iss >> v.y.data;
  if (iss.fail()) throw std::invalid_argument("Invalid geometric vertex");
  iss >> v.z.data;
  if (iss.fail()) throw std::invalid_argument("Invalid geometric vertex");
  if (!iss.eof()) iss >> v.w.data;
  if (iss.fail()) v.w = 1.0;
  notation_->geometricVertices.push_back(v);
}

const char* CSTypeStr(const CSType t) {
  switch (t) {
    case bmatrix:
      return "bmatrix";
    case bezier:
      return "bezier";
    case bspline:
      return "bspline";
    case cardinal:
      return "cardinal";
    case taylor:
      return "taylor";
    default:
      return "unknown";
  }
}
CSType stringToCSType(const std::string& type) {
  if (iequals(type, "bmatrix")) return bmatrix;
  if (iequals(type, "bezier")) return bezier;
  if (iequals(type, "bspline")) return bspline;
  if (iequals(type, "cardinal")) return cardinal;
  if (iequals(type, "taylor")) return taylor;
  throw std::invalid_argument("Invalid type");
}
MatrixType stringToMatrixType(std::string const& str) {
  if (iequals(str, "u")) return U;
  if (iequals(str, "v")) return V;
  throw std::invalid_argument("Invalid matrix type");
}
OBJNotation* parseOBJ(std::istream& istream) {
  if (auto parser = OBJParser(); !parser.countParseTime) {
    return parser.parse(istream);
  }
  const auto start = std::chrono::high_resolution_clock::now();
  const auto notation = OBJParser().parse(istream);
  const auto elapsed = std::chrono::high_resolution_clock::now() - start;
  std::cout
      << "Object was parsed in "
      << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
      << " microseconds" << std::endl;
  return notation;
}
}  // namespace s21
