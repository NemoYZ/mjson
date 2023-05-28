#include "mjson/number.h"

#include <math.h>
#include <float.h>

#include <limits>

namespace mjson {

Number::Number() 
  : Value(ValueType::JSON_NUMBER), 
    intValue_(0), 
    doubleValue_(0) {
}

Number::Number(int64_t value) 
  : Value(ValueType::JSON_NUMBER), 
    intValue_(value), 
    doubleValue_(static_cast<double>(value)) {
}

Number::Number(double value)
  : Value(ValueType::JSON_NUMBER), 
    intValue_(static_cast<int>(value)), 
    doubleValue_(value) {
}

std::string Number::toString() const {
  if (::fabs(doubleValue_ - intValue_) <= DBL_EPSILON &&
			doubleValue_ <= std::numeric_limits<int64_t>::max() && 
			doubleValue_ >= std::numeric_limits<int64_t>::min()) {
    // 整数
    return std::to_string(intValue_);
  }

  // 浮点数
  return std::to_string(doubleValue_);
}

} // namespace mjson