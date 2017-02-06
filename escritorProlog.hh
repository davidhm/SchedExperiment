#ifndef ESCRITOR_PROLOG_HH
#define ESCRITOR_PROLOG_HH

#include "planning.hh"
#include <string>
#include <ostream>
#include "structsAuxiliars.hh"
#include <list>

class EscritorProlog {
private:
  Planning planningAEscriure;
  PrologWritable &escritor;
  list<uint> getAssignaturesFormatejades();
  list<GrupsAssignatura> getGrupsFormatejats();
public:
  EscritorProlog(const Planning &planning,PrologWritable &escritor);
  EscritorProlog(Planning &&planning,PrologWritable &escritor);
  void escriuFitxerProlog(PrologWritable &escritor);
};

#endif
