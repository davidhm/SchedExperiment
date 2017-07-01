#ifndef PROLOGWRITABLE_HH
#define PROLOGWRITABLE_HH

#include <ostream>
#include <list>
#include "structsAuxiliars.hh"

typedef unsigned int uint;

class PrologWritable {
public:
  PrologWritable (const PrologWritable &other) = delete;
  PrologWritable& operator=(const PrologWritable &other) = delete;
  virtual ~PrologWritable();
  virtual void escriuAssignatures(const std::list<uint> &assignatures) = 0;
  virtual void escriuGrups(const std::list<GrupsAssignatura> &grupsArg) = 0;
  virtual void escriuSlots(const std::list<GrupsAssignatura> &slotsArg) = 0;
};

#endif
