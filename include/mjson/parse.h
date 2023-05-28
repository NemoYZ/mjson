#pragma once

#ifndef __MJSON_PARSE_H__
#define __MJSON_PARSE_H__

#include <memory>

#include "mjson/null.h"
#include "mjson/bool.h"
#include "mjson/number.h"
#include "mjson/array.h"
#include "mjson/string.h"
#include "mjson/object.h"

namespace mjson {

std::unique_ptr<Null> ParseNull(std::string_view v);
std::unique_ptr<Bool> ParseBool(std::string_view v);
std::unique_ptr<Number> ParseNumber(std::string_view v);
std::unique_ptr<Array> ParseArray(std::string_view v);
std::unique_ptr<String> ParseString(std::string_view v);
std::unique_ptr<Object> ParseObject(std::string_view v);
std::unique_ptr<Value> ParseValue(std::string_view v);

} // namespace mjson

#endif // __MJSON_PARSE_H__