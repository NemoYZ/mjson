#pragma once

#ifndef __MJSON_BOOL_H__
#define __MJSON_BOOL_H__

#include "mjson/value.h"

namespace mjson {

class Bool : public Value {
public:
  Bool();
  Bool(bool value);

public:
  std::string toString() const override { return value_ ? "true" : "false"; }
  void set(bool value) { value_ = value; }
  bool get() const { return value_; }

private:
  bool value_;
};

} // namespace mjson

#endif //__MJSON_BOOL_H__