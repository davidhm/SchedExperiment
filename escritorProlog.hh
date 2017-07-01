#ifndef ESCRITOR_PROLOG_HH
#define ESCRITOR_PROLOG_HH

#include "planning.hh"
#include <string>
#include <ostream>
#include "structsAuxiliars.hh"
#include "prologWritable.hh"
#include <list>

class EscritorProlog {
private:
  Planning planningAEscriure;
  std::list<uint> getAssignaturesFormatejades();
  std::list<GrupsAssignatura> getGrupsFormatejats();
public:
  EscritorProlog(const Planning &planning);
  EscritorProlog(Planning &&planning);
  void escriuFitxerProlog(PrologWritable &escritor);
};

#endif
