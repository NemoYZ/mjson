#include "mjson/value.h"

#include "mjson/null.h"
#include "mjson/bool.h"
#include "mjson/number.h"
#include "mjson/array.h"
#include "mjson/string.h"
#include "mjson/object.h"

namespace mjson {

Value::Value(ValueType type) : type_(type) {
}

Value::~Value() {
}

Null* Value::getNull() { 
  return static_cast<Null*>(this);
}

Bool* Value::getBool() {
  return static_cast<Bool*>(this);
}

Number* Value::getNumber() {
  return static_cast<Number*>(this);
}

Array* Value::getArray() {
  return static_cast<Array*>(this);
}

String* Value::getString() {
  return static_cast<String*>(this);
}

Object* Value::getObject() {
  return static_cast<Object*>(this);
}

const Null* Value::getNull() const {
  return static_cast<const Null*>(this);
}

const Bool* Value::getBool() const {
  return static_cast<const Bool*>(this);
}

const Number* Value::getNumber() const {
  return static_cast<const Number*>(this);
}

const Array* Value::getArray() const {
  return static_cast<const Array*>(this);
}

const String* Value::getString() const {
  return static_cast<const String*>(this);
}

const Object* Value::getObject() const {
  return static_cast<const Object*>(this);
}

} // namespace mjson