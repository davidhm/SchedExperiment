#ifndef GRUP_CC
#define GRUP_CC

#include "slot.hh"
#include "grup.hh"
#include <list>

typedef unsigned int uint;

Grup::Grup(uint nombreGrup) :
esGrupTeoric(true),nombreGrup(nombreGrup),slotsGrup() {}

Grup::Grup(bool esGrupTeoric, uint nombreGrup) :
esGrupTeoric(esGrupTeoric),nombreGrup(nombreGrup),slotsGrup() {}

void Grup::afegeixSlot(const std::string &hora, uint dia, const std::string &aula) {
  Slot actual(hora,dia,aula);
  slotsGrup.push_back(actual);
}
uint Grup::getNombreGrup() const {
  return nombreGrup;
}

std::list<uint> Grup::getSlotsNormalitzats() const {
  std::list<uint> ret;
  for (Slot i : slotsGrup) {
    ret.push_back(i.getSlotNormalitzat());
  }
  return ret;
}

bool Grup::operator== (const Grup &rhs) const {
  return nombreGrup == rhs.nombreGrup;
}


#endif
