#ifndef MAIN_CC
#define MAIN_CC

#include "escritorProlog.hh"
#include <iostream>
#include <fstream>

int main () {
  std::ofstream escritor("./test.txt");
  EscritorProlog test(Planning{});
  //If you do EscritorProlog test(Planning()) then you have
  //a most vexing parse and C++ will interpret as function with function
  //pointer as argument.
  test.escriuFitxerProlog(escritor);
}
#endif
