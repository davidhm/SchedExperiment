#ifndef ESCRITOR_PROLOG_CC
#define ESCRITOR_PROLOG_CC

#include "planning.hh"
#include "escritorFitxer.hh"
#include <string>
#include <utility>
#include <ostream>

EscritorProlog::EscritorProlog(const Planning &planning, const std::string &pathFitxer) {
  this -> planning = planning;
  this -> pathFitxer = pathFitxer;
}
void EscritorProlog::escriuFitxerProlog(std::ostream &escritor) {
  escritor << "test" << std::endl;
}

#endif
