#ifndef GRUP_CC
#define GRUP_CC

#include "slot.hh"
#include "grup.hh"
#include <list>



Grup::Grup(bool esGrupTeoric, uint numeroGrup) {
  this -> esGrupTeoric = esGrupTeoric;
  this -> numeroGrup = numeroGrup;
}
void Grup::afegeixSlot(const string &hora, uint dia, const string &aula) {
  Slot actual(hora,dia,aula);
  slotsGrup.push_back(actual);
}
uint Grup::getNumeroGrup() const {
  return numeroGrup;
}

#endif
