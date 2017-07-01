#ifndef ESCRITOR_PROLOG_CC
#define ESCRITOR_PROLOG_CC

#include "planning.hh"
#include "escritorProlog.hh"
#include <string>
#include <utility>
#include <ostream>
#include <list>
#include "structsAuxiliars.hh"

typedef unsigned int uint;

EscritorProlog::EscritorProlog(const Planning &planning) :
planningAEscriure(planning),escritor(escritor) {}

EscritorProlog::EscritorProlog(Planning &&planning) :
planningAEscriure(),escritor(escritor) {
  std::swap(planningAEscriure, planning);
}

void EscritorProlog::escriuFitxerProlog(PrologWritable &escritor) {
  escritor.escriuAssignatures(getAssignaturesFormatejades());
  std::list<GrupsAssignatura> grups = getGrupsFormatejats();
  escritor.escriuGrups(grups);
  escritor.escriuSlots(grups);
}

std::list<uint> EscritorProlog::getAssignaturesFormatejades() {
  std::list<uint> ret;
  for (uint i = 1; i <= planning.getNombreAssignatures(); ++i)
    ret.push_back(i);
  return ret;
}

std::list<GrupsAssignatura> EscritorProlog::getGrupsFormatejats() {
  std::list<GrupsAssignatura> ret;
  for (uint i = 1; i <= planning.getNombreAssignatures(); ++i) {
    GrupsAssignatura grupAssignatura;
    actual.assignatura = i;
    for (uint j : planning.getGrupsAssignatura(i)) {
      GrupAmbSlots grupAmbSlots;
      grupAmbSlots.grup = j;
      for ()
    }
  }
}

#endif
