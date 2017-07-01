#ifndef ASSIGNATURA_HH
#define ASSIGNATURA_HH

#include "grup.hh"
#include <list>

typedef unsigned int uint;

class Assignatura {
private:
  std::string nomAssignatura;

  std::list <Grup> llistaGrups;

public:
  Assignatura(const std::string &nomAssignatura);

  bool existeixGrup(uint numeroGrup) const;

  void afegeixGrup (uint numeroGrup, bool esTeoric);

  void afegeixSlotAGrup(uint numeroGrup, const std::string &hora, uint dia, const std::string &aula);

  std::string getNomAssignatura() const;

  std::list<uint> getGrups() const;

  std::list<uint> getSlotsGrup(uint nombreGrup) const;

};

#endif
