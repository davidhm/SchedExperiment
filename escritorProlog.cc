#ifndef ESCRITOR_PROLOG_CC
#define ESCRITOR_PROLOG_CC

#include "planning.hh"
#include "escritorProlog.hh"
#include <string>
#include <utility>
#include <ostream>
#include <list>

list <uint> EscritorProlog::


EscritorProlog::EscritorProlog(const Planning &planning,PrologWritable &escritor) :
planningAEscriure(planning),escritor(escritor) {}

EscritorProlog::EscritorProlog(Planning &&planning,PrologWritable &escritor) :
planningAEscriure(),escritor(escritor) {
  std::swap(planningAEscriure, planning);
}

EscritorProlog::

#endif
