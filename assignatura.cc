#ifndef ASSIGNATURA_CC
#define ASSIGNATURA_CC

#include "assignatura.hh"
#include "grup.hh"
#include <list>
#include <stdexcept>
#include <string>
#include <algorithm>

Assignatura::Assignatura(const std::string &nomAssignatura) :
nomAssignatura(nomAssignatura),llistaGrups() {}

bool Assignatura::existeixGrup(uint numeroGrup) const {
  auto iterador = llistaGrups.cbegin();
  while (iterador != llistaGrups.cend() and iterador -> getNombreGrup() != numeroGrup)
    ++iterador;
  return iterador != llistaGrups.cend();
}

void Assignatura::afegeixGrup (uint numeroGrup, bool esTeoric) {
  Grup actual(esTeoric,numeroGrup);
  auto iteradorLlista = llistaGrups.cend();
  while (iteradorLlista != llistaGrups.cbegin() and iteradorLlista -> getNombreGrup() > numeroGrup)
    --iteradorLlista;
  llistaGrups.insert(iteradorLlista,actual);
}

void Assignatura::afegeixSlotAGrup(uint numeroGrup, const std::string &hora, uint dia, const std::string &aula) {
  auto iterador = llistaGrups.end();
  while (iterador != llistaGrups.begin() and iterador -> getNombreGrup() >= numeroGrup)
    --iterador;
  if ((++iterador) -> getNombreGrup() == numeroGrup) {
    std::string nomFitxer(__FILE__);
    std::string linia = std::to_string(__LINE__);
    throw std::runtime_error(nomFitxer.append(" ").append(linia).append(" : Hi ha dos grups amb el mateix numero."));
  }
  --iterador;
  iterador -> afegeixSlot(hora,dia,aula);
}
std::string Assignatura::getNomAssignatura() const {
  return nomAssignatura;
}

std::list<uint> Assignatura::getGrups() const {
  std::list<uint> ret;
  for (Grup i : llistaGrups) {
    ret.push_back(i.getNombreGrup());
  }
  return ret;
}

std::list<uint> Assignatura::getSlotsGrup(uint nombreGrup) const {
  return std::find(llistaGrups.cbegin(),llistaGrups.cend(),Grup(nombreGrup)) -> getSlotsNormalitzats();
}

#endif
