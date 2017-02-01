#ifndef GRUP_CC
#define GRUP_CC

#include "slot.hh"
#include "grup.hh"
#include <list>

Grup::Grup(bool esGrupTeoric, uint numeroGrup) :
esGrupTeoric(esGrupTeoric),numeroGrup(numeroGrup),slotsGrup() {}

void Grup::afegeixSlot(const std::string &hora, uint dia, const std::string &aula) {
  Slot actual(hora,dia,aula);
  slotsGrup.push_back(actual);
}
uint Grup::getNumeroGrup() const {
  return numeroGrup;
}

#endif
