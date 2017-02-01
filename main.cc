#ifndef MAIN_CC
#define MAIN_CC

#include "escritorFitxer.hh"
#include <iostream>
#include <fstream>

int main () {
  std::ofstream escritor("./test.txt");
  EscritorProlog test(Planning(),"puyol");
  escriuFitxerProlog(escritor);
  escriuFitxerProlog(cout);
}
#endif
