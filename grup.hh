#ifndef GRUP_HH
#define GRUP_HH

#include "slot.hh"
#include <list>

typedef unsigned int uint;

class Grup {
private:
  bool esGrupTeoric;
  uint nombreGrup;
  std::list <Slot> slotsGrup;
public:
  Grup(uint nombreGrup);

  Grup(bool esGrupTeoric, uint nombreGrup);

  void afegeixSlot(const std::string &hora, uint dia, const std::string &aula);

  uint getNombreGrup() const;

  std::list<uint> getSlotsNormalitzats() const;

  bool operator==(const Grup &rhs) const;
};

#endif
