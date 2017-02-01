#ifndef GRUP_HH
#define GRUP_HH

#include "slot.hh"
#include <list>



class Grup {
private:
  bool esGrupTeoric;
  uint numeroGrup;
  std::list <Slot> slotsGrup;
public:
  Grup(bool esGrupTeoric, uint numeroGrup);

  void afegeixSlot(const std::string &hora, uint dia, const std::string &aula);

  uint getNumeroGrup() const;
};

#endif
