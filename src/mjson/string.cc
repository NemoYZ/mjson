#include "mjson/string.h"

namespace mjson {

String::String(std::string_view value) 
  : Value(ValueType::JSON_STRING),
    value_(value) {
}

String& String::trim() {
  std::string::iterator startOfPrintable = value_.begin();
  std::string::iterator endOfPrintable = value_.end();
  while (startOfPrintable != endOfPrintable && *startOfPrintable <= ' ') {
    ++startOfPrintable;
  }
  while (startOfPrintable < endOfPrintable) {
    std::string::iterator iter = endOfPrintable;
    --iter;
    if (*iter <= ' ') {
      endOfPrintable = iter;
    } else {
      break;
    }
  }

  if (startOfPrintable != value_.begin() && endOfPrintable != value_.end()) {
    std::string tmp(startOfPrintable, endOfPrintable);
    value_ = tmp;
  }

  return *this;
}

std::string String::toString() const {
  std::string result;
  result.reserve(value_.size());
  result.push_back('\"');

  for (const char v : value_) {
    switch (v) {
      case '\\':
        result.push_back('\\');
        break;
      case '\"':
        result.push_back('\"');	
        break;
      case '\b':
        result.push_back('\\');
        result.push_back('b');	
        break;
      case '\n':
        result.push_back('\\');
        result.push_back('n');	
        break;
      case '\r':
        result.push_back('\\');
        result.push_back('r');	
        break;
      case '\t':
        result.push_back('\\');
        result.push_back('t');	
        break;
      default:
        result.push_back(v);
    }
  }
  result.push_back('\"');

  return result;
}

} // namespace mjson