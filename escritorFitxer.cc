#ifndef ESCRITOR_FITXER_CC
#define ESCRITOR_FITXER_CC

#include "planning.hh"
#include "escritorFitxer.hh"
#include <string>
#include <utility>
#include <ostream>

EscritorProlog::EscritorProlog(Planning planning, std::string pathFitxer) {
  this -> planning = planning;
  this -> pathFitxer = pathFitxer;
}

EscritorProlog::EscritorProlog(Planning &&planning, std::string &&pathFitxer){
  std::swap(this->planning,planning);
  std::swap(this->pathFitxer,pathFitxer);
}

void EscritorProlog::escriuFitxerProlog(std::ostream &escritor) {
  escritor << "test" << std::endl;
}

#endif
