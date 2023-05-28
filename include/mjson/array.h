#pragma once

#ifndef __MJSON_ARRAY_H_
#define __MJSON_ARRAY_H_

#include <vector>
#include <memory>

#include "mjson/value.h"

namespace mjson {

class Array : public Value {
public:
  Array();

  Value& operator[](size_t index) { return *value_[index]; }
  const Value& operator[](size_t index) const { return *value_[index]; }
  void push(std::unique_ptr<Value>&& v) {value_.push_back(std::move(v)); }
  void pop() { value_.pop_back(); }
  size_t size() const { return value_.size(); }

  std::string toString() const override;

private:
  std::vector<std::unique_ptr<Value>> value_;
};

} // namespace mjson

#endif // __MJSON_ARRAY_H_