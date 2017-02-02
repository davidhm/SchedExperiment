#ifndef ESCRITOR_PROLOG_HH
#define ESCRITOR_PROLOG_HH

#include "planning.hh"
#include <string>
#include <ostream>

class EscritorProlog {
private:
  Planning planningAEscriure;
public:
  EscritorProlog(const Planning &planning);
  EscritorProlog(Planning &&planning);
  void escriuFitxerProlog(std::ostream &escritor);
};

#endif
