#ifndef ASSIGNATURA_HH
#define ASSIGNATURA_HH

#include "grup.hh"
#include <list>



class Assignatura {
private:
  std::string nomAssignatura;

  std::list <Grup> llistaGrups;

public:
  Assignatura(const std::string &nomAssignatura);

  bool existeixGrup(uint numeroGrup);

  void afegeixGrup (uint numeroGrup, bool esTeoric);

  void afegeixSlotAGrup(uint numeroGrup, const std::string &hora, uint dia, const std::string &aula);

  std::string getNomAssignatura();

  

};

#endif
