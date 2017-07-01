#ifndef SLOT_HH
#define SLOT_HH

#include "hora.hh"
#include <string>

typedef unsigned int uint;

class Slot {
private:
  /*
  Dilluns = 1, Dimarts = 2, Dimecres = 3, Dijous = 4, Divendres = 5.
  */
  Hora horaSlot;
  uint diaSetmana;
  std::string aulaSlot;
public:
  Slot(const std::string &hora, uint dia, const std::string &aula);
  uint getSlotNormalitzat() const;
};

#endif
