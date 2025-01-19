//
// Created by yadoc on 21.09.2024.
//

#ifndef UTILS_H
#define UTILS_H
#include <algorithm>
#include <string>

inline bool bothAreSpaces(const char lhs, const char rhs) {
  return (lhs == rhs) && (lhs == ' ');
}
inline void removeStringSpaces(std::string& str) {
  const auto new_end = std::unique(str.begin(), str.end(), bothAreSpaces);
  str.erase(new_end, str.end());
}
inline bool ichar_equals(const char a, const char b) {
  return std::tolower(static_cast<unsigned char>(a)) ==
         std::tolower(static_cast<unsigned char>(b));
}

inline bool iequals(const std::string& a, const std::string& b) {
  return a.size() == b.size() &&
         std::equal(a.begin(), a.end(), b.begin(), ichar_equals);
}

inline auto ws = " \t\n\r\f\v";

// trim from end of string (right)
inline std::string& rtrim(std::string& s, const char* t = ws) {
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}

// trim from beginning of string (left)
inline std::string& ltrim(std::string& s, const char* t = ws) {
  s.erase(0, s.find_first_not_of(t));
  return s;
}

// trim from both ends of string (right then left)
inline std::string& trim(std::string& s, const char* t = ws) {
  return ltrim(rtrim(s, t), t);
}

inline std::vector<std::string> split(const std::string& str,
                                      const char delimiter) {
  std::vector<std::string> result;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delimiter)) {
    result.push_back(token);
  }

  return result;
}
#endif  // UTILS_H
