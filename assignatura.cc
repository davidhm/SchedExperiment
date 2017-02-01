#ifndef ASSIGNATURA_CC
#define ASSIGNATURA_CC

#include "assignatura.hh"
#include "grup.hh"
#include <list>
#include <stdexcept>
#include <string>

Assignatura::Assignatura(const std::string &nomAssignatura) {
  this -> nomAssignatura = nomAssignatura;
}

bool Assignatura::existeixGrup(uint numeroGrup) {
  auto iterador = llistaGrups.cbegin();
  while (iterador != llistaGrups.cend() and iterador -> getNumeroGrup() != numeroGrup)
    ++iterador;
  return iterador != llistaGrups.cend();
}

void Assignatura::afegeixGrup (uint numeroGrup, bool esTeoric) {
  Grup actual(esTeoric,numeroGrup);
  auto iteradorLlista = llistaGrups.cend();
  while (iteradorLlista != llistaGrups.cbegin() and iteradorLlista -> getNumeroGrup() > numeroGrup)
    --iteradorLlista;
  llistaGrups.insert(iteradorLlista,actual);
}

void Assignatura::afegeixSlotAGrup(uint numeroGrup, const std::string &hora, uint dia, const std::string &aula) {
  auto iterador = llistaGrups.end();
  while (iterador != llistaGrups.begin() and iterador -> getNumeroGrup() >= numeroGrup)
    --iterador;
  if ((++iterador) -> getNumeroGrup() == numeroGrup) {
    std::string nomFitxer(__FILE__);
    std::string linia = std::to_string(__LINE__);
    throw std::runtime_error(nomFitxer.append(" ").append(linia).append(" : Hi ha dos grups amb el mateix numero."));
  }
  --iterador;
  iterador -> afegeixSlot(hora,dia,aula);
}
std::string Assignatura::getNomAssignatura() {
  return nomAssignatura;
}

#endif
