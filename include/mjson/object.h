#pragma once

#ifndef __MJSON_OBJECT_H__
#define __MJSON_OBJECT_H__

#include <memory>
#include <unordered_map>

#include "common/hash.h"
#include "mjson/value.h"

namespace mjson {

class Object : public Value {
public:
  using ObjectMap = std::unordered_map<std::string,
                                      std::unique_ptr<Value>, 
                                      StringHash,
                                      std::equal_to<>
                                    >;

public:
  Object();
  void set(std::string_view key, std::unique_ptr<Value>&& value);
  Value* get(std::string_view key) const;
  std::string toString() const override;

private:
  ObjectMap value_;
};

} // namespace ejson

#endif // __MJSON_OBJECT_H__