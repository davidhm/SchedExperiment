#ifndef MAIN_CC
#define MAIN_CC

#include "escritorProlog.hh"
#include <iostream>
#include <fstream>

int main () {
  std::ofstream escritor("./test.txt");
  EscritorProlog test(Planning());
  test.escriuFitxerProlog(escritor);
}
#endif
