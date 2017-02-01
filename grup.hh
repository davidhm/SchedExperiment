#ifndef GRUP_HH
#define GRUP_HH

#include "slot.hh"
#include <list>



class Grup {
private:
  bool esGrupTeoric;
  uint numeroGrup;
  list <Slot> slotsGrup;
public:
  Grup(bool esGrupTeoric, uint numeroGrup);

  void afegeixSlot(const string &hora, uint dia, const string &aula);

  uint getNumeroGrup() const;
};

#endif
