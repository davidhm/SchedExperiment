#ifndef ESCRITOR_PROLOG_CC
#define ESCRITOR_PROLOG_CC

#include "planning.hh"
#include "escritorProlog.hh"
#include <string>
#include <utility>
#include <ostream>

EscritorProlog::EscritorProlog(Planning planning) :
planningAEscriure(planning) {}

EscritorProlog::EscritorProlog(Planning &&planning) :
planningAEscriure() {
  std::swap(planningAEscriure, planning);
}
void EscritorProlog::escriuFitxerProlog(std::ostream &escritor) {
  escritor << "test" << std::endl;
}

#endif
