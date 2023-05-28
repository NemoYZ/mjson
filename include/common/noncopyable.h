#pragma once

#ifndef __MJSON_NONCOPYABLE_H__
#define __MJSON_NONCOPYABLE_H__

namespace mjson {

class Noncopyable {
public:
  Noncopyable() = default;
  ~Noncopyable() = default;

  Noncopyable(const Noncopyable& other) = delete;
  Noncopyable& operator=(const Noncopyable& other) = delete;
};

} // namespace mjson

#endif // __MJSON_NONCOPYABLE_H__