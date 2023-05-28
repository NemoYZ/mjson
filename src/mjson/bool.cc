#include "mjson/bool.h"

#include <string.h>

namespace mjson {

Bool::Bool() 
  : Value(ValueType::JSON_BOOL), 
    value_() {
}

Bool::Bool(bool value) 
  : Value(ValueType::JSON_BOOL), 
    value_(value) {
}

} // namespace mjson