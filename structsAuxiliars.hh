#ifndef STRUCTSAUXILIARS_HH
#define STRUCTSAUXILIARS_HH

#include <list>

typedef unsigned int uint;

struct GrupInfo {
  bool esTeoric;
  uint grup;
};

struct GrupAmbSlots {
  GrupInfo grup;
  std::list<uint> slots;
};

struct GrupsAssignatura {
  uint assignatura;
  std::list<GrupAmbSlots> grups;
};



#endif
