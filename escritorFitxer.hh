#ifndef ESCRITOR_FITXER_HH
#define ESCRITOR_FITXER_HH

#include "planning.hh"
#include <string>
#include <ostream>

class EscritorProlog {
private:
  Planning planning;
  string pathFitxer;

public:
  EscritorProlog(Planning planning, std::string pathFitxer);
  EscritorProlog(Planning &&planning, std::string &&pathFitxer);
  void escriuFitxerProlog(std::ostream &escritor);
};

#endif
