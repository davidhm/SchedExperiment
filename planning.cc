#ifndef PLANNING_CC
#define PLANNING_CC

#include "assignatura.hh"
#include "planning.hh"
#include <vector>
#include <string>
#include <stdexcept>

Planning::Planning() {}

int Planning::trobaAssignatura(const std::string &nomAssignatura) {
  if (assignatures.size() == 0)
    return -1;
  uint i = assignatures.size()-1;
  while (i >= 0 and assignatures.at(i).getNomAssignatura() != nomAssignatura)
    --i;
  return i >= 0 ? i : -1;
}

bool Planning::existeixAssignatura(const std::string &nomAssignatura) {
  return trobaAssignatura(nomAssignatura) != -1;
}

bool Planning::existeixGrupEnAssignatura(const std::string &nomAssignatura, uint numeroGrup) {
  int i = trobaAssignatura(nomAssignatura);
  if (i == -1)
    return false;
  return assignatures.at(i).existeixGrup(numeroGrup);
}

void Planning::afegeixAssignatura(const std::string &nomAssignatura) {
  int i = trobaAssignatura(nomAssignatura);
  if (i == -1) {
    Assignatura actual(nomAssignatura);
    assignatures.push_back(actual);
  }
  else
    throw std::logic_error("Afegir assignatura: La assignatura ja existeix.");
}

void Planning::afegeixGrupAssignatura(const std::string &nomAssignatura, uint numeroGrup, bool esTeoric) {
  int i = trobaAssignatura(nomAssignatura);
  if (i == -1)
    throw std::logic_error("Afegir grup assignatura: La assignatura no existeix.");
  assignatures.at(i).afegeixGrup(numeroGrup,esTeoric);
}

void Planning::afegeixSlotGrupAssignatura(const std::string &nomAssignatura, uint numeroGrup, const std::string &hora,
uint dia, const std::string &aula) {
  int i = trobaAssignatura(nomAssignatura);
  if (i == -1)
    throw std::logic_error("Afegir slot grup assignatura: La assignatura no existeix.");
  assignatures.at(i).afegeixSlotAGrup(numeroGrup,hora,dia,aula);
}

#endif
