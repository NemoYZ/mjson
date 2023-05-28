#include "mjson/parse.h"

#include <string.h>
#include <math.h>

namespace mjson {

constexpr static std::string_view trueStringView = "true";
constexpr static std::string_view falseStringView = "false";
constexpr static std::string_view nullStringView = "null";

static std::string_view trim(std::string_view v) {
  std::string_view::iterator startOfPrintable = v.begin();
  std::string_view::iterator endOfPrintable = v.end();
  while (startOfPrintable != endOfPrintable && *startOfPrintable <= ' ') {
    ++startOfPrintable;
  }
  while (startOfPrintable < endOfPrintable) {
    std::string_view::iterator iter = endOfPrintable;
    --iter;
    if (*iter <= ' ') {
      endOfPrintable = iter;
    } else {
      break;
    }
  }

  std::size_t len = std::distance(startOfPrintable, endOfPrintable);

  return std::string_view(&*startOfPrintable, len);
}

static std::string_view skipNonprinting(std::string_view v) {
  std::size_t len = 0;
  while (len < v.size() && v[len] <= ' ') {
    ++len;
  }
  v.remove_prefix(len);
  return v;
}

static bool ParseNumberAuxiliary(std::string_view& v, std::unique_ptr<Value>& value);
static bool ParseArrayAuxiliary(std::string_view& v, std::unique_ptr<Value>& value);
static bool ParseStringAuxiliary(std::string_view& v, std::unique_ptr<Value>& value);
static bool ParseObjectAuxiliary(std::string_view& v, std::unique_ptr<Value>& value);
static bool ParseValueAuxiliary(std::string_view& v, std::unique_ptr<Value>& value);

static bool ParseNumberAuxiliary(std::string_view& v,
                                std::unique_ptr<Value>& value) {
  const char* startPtr = v.data();
  char* endPtr = nullptr;
  double n = ::strtod(startPtr, &endPtr);
  value = std::make_unique<Number>(n);
  v.remove_prefix(endPtr - startPtr);
  return true;
}

static bool ParseArrayAuxiliary(std::string_view& v, 
                                std::unique_ptr<Value>& value) {
  if (v[0] != '[') {
    return false;
  }
  // 去掉'['
  v.remove_prefix(1);
  // 去掉空格
  v = skipNonprinting(v);
  if (v.empty()) {
    return false;
  }

  value = std::make_unique<Array>();
  // 空数组
  if (v[0] == ']') {
    return true;
  }

  Array* arrayValue = static_cast<Array*>(value.get());

  while (true) {
    std::unique_ptr<Value> tmp;
    if (!ParseValueAuxiliary(v, tmp)) {
      return false;
    }
    arrayValue->push(std::move(tmp));
    if (v[0] != ',') {
      break;
    } else {
      // 去掉最前面的','
      v.remove_prefix(1);
      // 去掉空格
      v = skipNonprinting(v);
    }
  }
  if (v[0] != ']') {
    return false;
  } else {
    // 去掉']'
    v.remove_prefix(1);
    v = skipNonprinting(v);
  }
  return true;
}

static bool ParseStringAuxiliary(std::string_view& v, 
                                std::unique_ptr<Value>& value) {
  auto iter = v.begin();
  if (*iter != '\"') {
    return false;
  }
  ++iter;
  while (iter != v.end() && *iter != '\"') {
    // 如果字符串里还有"
    // 这里会跳过
    if (*iter == '\\') {
      ++iter;
    }
    ++iter;
  }
  if (iter == v.end()) {
    return false;
  }
  value = std::make_unique<String>(std::string_view(v.begin() + 1, iter - v.begin() - 1));
  v.remove_prefix(iter - v.begin() + 1);
  return true;
}

static bool ParseObjectAuxiliary(std::string_view& v, 
                                std::unique_ptr<Value>& value) {
  if (v[0] != '{') {
    return false;
  }
  v.remove_prefix(1);
  v = skipNonprinting(v);
  if (v.empty()) {
    return false;
  }

  value = std::make_unique<Object>();
  if (v[0] == '}') {
    return true;
  }

  Object* objectValue = static_cast<Object*>(value.get());

  while (true) {
    const char* delimiter = ::strchr(v.data(), ':');
    if (*delimiter == '\0') {
      return false;
    }
    // "a":2
    // 双引号不要，从1开始
    std::string_view key = v.substr(1, delimiter - v.data() - 2);
    v.remove_prefix(delimiter - v.data() + 1);
    v = skipNonprinting(v);
    std::unique_ptr<Value> tmp;
    if (!ParseValueAuxiliary(v, tmp)) {
      return false;
    }
    objectValue->set(key, std::move(tmp));
    if (v[0] != ',') {
      break;
    } else {
      // 去掉最前面的','
      v.remove_prefix(1);
      v = skipNonprinting(v);
    }
  }
  if (v[0] != '}') {
    return false;
  } else {
    // 去掉'}'
    v.remove_prefix(1);
    v = skipNonprinting(v);
  }
  return true;
}

static bool ParseValueAuxiliary(std::string_view& v, 
                                std::unique_ptr<Value>& value) {
  if (::strncmp(v.data(), nullStringView.data(), nullStringView.size()) == 0) {
    value = std::make_unique<Null>();
    v.remove_prefix(nullStringView.size());
    return true;
  }
  if (::strncmp(v.data(), trueStringView.data(), trueStringView.size()) == 0) {
    value = std::make_unique<Bool>(true);
    v.remove_prefix(trueStringView.size());
    return true;
  }
  if (::strncmp(v.data(), falseStringView.data(), falseStringView.size()) == 0) {
    value = std::make_unique<Bool>(false);
    v.remove_prefix(falseStringView.size());
    return true;
  }

  switch (v[0]) {
    case '\"':
      return ParseStringAuxiliary(v, value);
      break;
    case '-':
      [[fallthrough]];
    case '+':
      [[fallthrough]];
    case '0':
      [[fallthrough]];
    case '1':
      [[fallthrough]];
    case '2':
      [[fallthrough]];
    case '3':
      [[fallthrough]];
    case '4':
      [[fallthrough]];
    case '5':
      [[fallthrough]];
    case '6':
      [[fallthrough]];
    case '7':
      [[fallthrough]];
    case '8':
      [[fallthrough]];
    case '9':
      return ParseNumberAuxiliary(v, value);
      break;
    case '[':
      return ParseArrayAuxiliary(v, value);
      break;
    case '{':
      return ParseObjectAuxiliary(v, value);
      break;
    default:
      return false;
      break;
  }

  return false;
}

// no use
std::unique_ptr<Null> ParseNull(std::string_view v) {
  if (nullStringView == v) {
    return std::make_unique<Null>();
  }

  return nullptr;
}

// no use
std::unique_ptr<Bool> ParseBool(std::string_view v) {
  if (trueStringView == v) {
    return std::make_unique<Bool>(true);
  } else if (falseStringView == v) {
    return std::make_unique<Bool>(false);
  }

  return nullptr;
}

std::unique_ptr<Number> ParseNumber(std::string_view v) {
  double n = atof(v.data());
	return std::make_unique<Number>(n);
}

std::unique_ptr<Array> ParseArray(std::string_view v) {
  if (*v.begin() != '[' || v.back() != ']') {
    return nullptr;
  }

  std::unique_ptr<Value> tmp;
  if (!ParseArrayAuxiliary(v, tmp)) {
    return nullptr;
  }

  std::unique_ptr<Array> result(static_cast<Array*>(tmp.get()));
  tmp.release();

  return result;
}

std::unique_ptr<String> ParseString(std::string_view v) {
  if (*v.begin() != '\"' || v.back() != '\"') {
    return nullptr;
  }
  // 去掉首尾的 ""
  v.remove_prefix(1);
  v.remove_suffix(1);

  return std::make_unique<String>(v);
}

std::unique_ptr<Object> ParseObject(std::string_view v) {
  if (*v.begin() != '{' || v.back() != '}') {
    return nullptr;
  }
  std::unique_ptr<Value> tmp;
  if (!ParseObjectAuxiliary(v, tmp)) {
    return nullptr;
  }

  std::unique_ptr<Object> result(static_cast<Object*>(tmp.get()));
  tmp.release();

  return result;
}

std::unique_ptr<Value> ParseValue(std::string_view v) {
  std::unique_ptr<Value> result;
  if (!ParseValueAuxiliary(v, result)) {
    return nullptr;
  }

  return result;
}

} // namespace mjson