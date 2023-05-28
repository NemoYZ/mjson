#pragma once

#ifndef __MJSON_VALUE_H__
#define __MJSON_VALUE_H__

#include <stdint.h>

#include <string>
#include <string_view>

#include "common/noncopyable.h"

namespace mjson {

class Null;
class Bool;
class Number;
class Array;
class String;
class Object;

class Value : Noncopyable {
public:
  enum class ValueType : int8_t {
    JSON_NULL,
    JSON_OBJECT,
    JSON_NUMBER,
    JSON_BOOL,
    JSON_STRING,
    JSON_ARRAY,
  };

public:
  Value() = delete;
  virtual~ Value();

public:
  Null* getNull();
  Bool* getBool();
  Number* getNumber();
  Array* getArray();
  String* getString();
  Object* getObject();

  const Null* getNull() const;
  const Bool* getBool() const;
  const Number* getNumber() const;
  const Array* getArray() const;
  const String* getString() const;
  const Object* getObject() const;

  ValueType getType() const { return type_; }
  virtual std::string toString() const = 0;

protected:
  Value(ValueType type);

protected:
  ValueType type_;
};

} // namespace mjson

#endif //__MJSON_VALUE_H__