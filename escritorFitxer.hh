#ifndef ESCRITOR_FITXER_HH
#define ESCRITOR_FITXER_HH

#include "planning.hh"
#include <string>
#include <ostream>

class EscritorProlog {
private:
  Planning planning;
  std::string pathFitxer;

public:
  EscritorProlog(const Planning &planning, const std::string &pathFitxer);
  void escriuFitxerProlog(std::ostream &escritor);
};

#endif
