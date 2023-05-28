#pragma once

#ifndef __MJSON_NULL_H__
#define __MJSON_NULL_H__

#include <stddef.h>

#include "mjson/value.h"

namespace mjson {

class Null : public Value {
public:
  Null();
  Null(nullptr_t value);

public:
  std::string toString() const override { return "null"; }
  void set(nullptr_t value) { value_ = value; }
  nullptr_t get() const { return value_; }

private:
  nullptr_t value_;
};

} // namespace mjson

#endif //__MJSON_NULL_H__