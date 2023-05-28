#include <iostream>

int main(int argc, char** argv) {
  const char* s = "20.30300 This is test";
  char* endPtr = nullptr;
  double d = ::strtod(s, &endPtr);
  std::cout << endPtr << std::endl;
  std::cout << endPtr - s << std::endl;
  
  return 0;
}