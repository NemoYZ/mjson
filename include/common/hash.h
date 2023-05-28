#pragma once

#ifndef __MJSON_HASH_H__
#define __MJSON_HASH_H__

#include <functional>
#include <string_view>
#include <string>

namespace mjson {

// see https://en.cppreference.com/w/cpp/container/unordered_map/find
struct StringHash {
  using hash_type = std::hash<std::string_view>;
  using is_transparent = void;

  std::size_t operator()(const char* str) const        { return hash_type{}(str); }
  std::size_t operator()(std::string_view str) const   { return hash_type{}(str); }
  std::size_t operator()(const std::string& str) const { return hash_type{}(str); }
};

} // namespace mjson

#endif // __MJSON_HASH_H__