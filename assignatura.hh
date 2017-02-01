#ifndef ASSIGNATURA_HH
#define ASSIGNATURA_HH

#include "grup.hh"
#include <list>



class Assignatura {
private:
  string nomAssignatura;
  list <Grup> llistaGrups;
public:
  Assignatura(const string &nomAssignatura);
  bool existeixGrup(uint numeroGrup);
  void afegeixGrup (uint numeroGrup, bool esTeoric);
  void afegeixSlotAGrup(uint numeroGrup, const string &hora, uint dia, const string &aula);
  string getNomAssignatura();
};

#endif
