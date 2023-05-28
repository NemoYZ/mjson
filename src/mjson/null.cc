#include "mjson/null.h"

namespace mjson {

Null::Null() 
  : Value(ValueType::JSON_NULL), 
    value_() {
}

Null::Null(nullptr_t value) 
  : Value(ValueType::JSON_NULL), 
    value_(value) {
}

} // namespace mjson