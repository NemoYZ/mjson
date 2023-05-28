#pragma once

#ifndef __MJSON_STRING_H__
#define __MJSON_STRING_H__

#include "mjson/value.h"

namespace mjson {

class String : public Value {
public:
  String() = default;
  String(std::string_view value);

  const std::string& get() const { return value_; }
  void set(const std::string& value) { value_ = value; }
  void set(std::string&& value) { value_ = std::move(value); }
  String& trim();
  std::string& getStdString() { return value_; }

  std::string toString() const override;

private:
  std::string value_;
};

} // namespace mjson

#endif // __MJSON_STRING_H__