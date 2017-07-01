#ifndef SLOT_CC
#define SLOT_CC

#include "hora.hh"
#include "slot.hh"

Slot::Slot(const std::string &horaString, uint dia, const std::string &aula) :
horaSlot(horaString),diaSetmana(dia),aulaSlot(aula) {}

uint Slot::getSlotNormalitzat() const {
  return Hora::getNombreSlotsPerDia()*diaSetmana + horaSlot.getSlot();
}

#endif
