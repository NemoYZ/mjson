#pragma once

#ifndef __MJSON_NUMBER_H__
#define __MJSON_NUMBER_H__

#include "mjson/value.h"

namespace mjson {

class Number : public Value {
public:
  Number();
  Number(int64_t value);
  Number(double value);

  int64_t getInt() const { return intValue_; }
  double getDouble() const { return doubleValue_; }
  void set(int64_t value) { intValue_ = value; }
  void set(double value) { doubleValue_ = value; }

  std::string toString() const override;

private:
  int64_t intValue_;
  double doubleValue_;
};

} // namespace msjon

#endif // __MJSON_NUMBER_H__