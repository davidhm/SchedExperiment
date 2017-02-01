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
  uint diaSetmana;
  Hora *horaSlot;
  string aula;
public:
  Slot(const string &hora, uint dia, const string &aula);
  ~Slot();
};

#endif
