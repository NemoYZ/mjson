#include <assert.h>

#include <iostream>

#include "mjson/parse.h"

static void ParseNullTest();
static void ParseBoolTest();
static void ParseNumberTest();
static void ParseStringTest();
static void ParseArrayTest();
static void ParseObjectTest();

int main(int argc, char** argv) {
  // ParseNullTest();
  // ParseBoolTest();
  // ParseNumberTest();
  // ParseStringTest();
  // ParseArrayTest();
   ParseObjectTest();

  return 0;
}

void ParseNullTest() {
  std::unique_ptr<mjson::Null> value = mjson::ParseNull("null");
  std::cout << value->toString() << std::endl;
}

void ParseBoolTest() {
  std::unique_ptr<mjson::Bool> trueValue = mjson::ParseBool("true");
  std::unique_ptr<mjson::Bool> falseValue = mjson::ParseBool("false");
  std::cout << trueValue->toString() << std::endl;
  std::cout << falseValue->toString() << std::endl;
}

void ParseNumberTest() {
  std::unique_ptr<mjson::Number> intValue = mjson::ParseNumber("314");
  std::unique_ptr<mjson::Number> doubleValue = mjson::ParseNumber("3.14");
  std::unique_ptr<mjson::Number> exponentValue = mjson::ParseNumber("-3.14e+2");
  std::cout << intValue->toString() << std::endl;
  std::cout << doubleValue->toString() << std::endl;
  std::cout << exponentValue->toString() << std::endl;
}

void ParseStringTest() {
  std::unique_ptr<mjson::String> stringValue = mjson::ParseString("\"My name is Van\"");
  std::cout << stringValue->toString() << std::endl;
}

void ParseArrayTest() {
  std::unique_ptr<mjson::Array> arrayValue1 = mjson::ParseArray("[]");
  std::unique_ptr<mjson::Array> arrayValue2 = mjson::ParseArray("[0, 1, 2, 4]");
  std::unique_ptr<mjson::Array> arrayValue3 = mjson::ParseArray("[\"foo\", 0, 3.14, -2, true, null]");
  std::unique_ptr<mjson::Array> arrayValue4 = mjson::ParseArray("[{\"name\":\"Van\",\"age\":30},true]");
  std::cout << arrayValue1->toString() << std::endl;
  std::cout << arrayValue2->toString() << std::endl;
  std::cout << arrayValue3->toString() << std::endl;
  std::cout << arrayValue4->toString() << std::endl;
}

void ParseObjectTest() {
  constexpr std::string_view jsonString = "{"
    "\"bar\": [0, 1, 3.14, 1.1e5, {\"name\":\"Van\",\"age\":30}, null],"
    "\"unemployment\": true,"
    "\"cryTimes\": 5,"
    "\"hasHome\": \"maybe\","
    "\"sb. to confide\": null,"
    "\"Want to survive\": false"
  "}";
  std::cout << "jsonString=" << jsonString << std::endl;
  std::unique_ptr<mjson::Value> objectValue = mjson::ParseObject(jsonString);

  std::cout << objectValue->toString() << std::endl;
}