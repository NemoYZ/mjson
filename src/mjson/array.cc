#include "mjson/array.h"

namespace mjson {

Array::Array() : Value(ValueType::JSON_ARRAY) {
}

std::string Array::toString() const {
  std::string result = "[";
  for (const auto& v : value_) {
    result += v->toString();
    result.push_back(',');
  }
  // 去掉最后一个 ','
  if (result.size() > 1) {
    result.pop_back();
  }
  result.push_back(']');
  return result;
}

} // namespace mjson