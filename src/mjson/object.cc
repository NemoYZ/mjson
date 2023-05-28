#include "mjson/object.h"

namespace mjson {

Object::Object() : Value(ValueType::JSON_OBJECT) {
}

void Object::set(std::string_view key, std::unique_ptr<Value>&& value) {
  value_.emplace(key, std::move(value));
}

Value* Object::get(std::string_view key) const {
  // C++20
  auto iter = value_.find(key);
  return iter == value_.end() ? nullptr : iter->second.get();
}

std::string Object::toString() const {
  std::string result = "{";
  //C++17
  for (const auto& [k, v] : value_) {
    result.push_back('\"');
    result += k;
    result.push_back('\"');
    result.push_back(':');
    result += v->toString();
    result.push_back(',');
  }
  // 去掉最后一个',
  if (result.size() > 1) {
    result.pop_back();
  }
  result.push_back('}');
  return result;
}

} // namespace mjson