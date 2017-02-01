#ifndef PLANNING_HH
#define PLANNING_HH

#include "assignatura.hh"
#include <string>
#include <vector>


class Planning {
private:
  std::vector <Assignatura> assignatures;
  int trobaAssignatura(const std::string &nomAssignatura);

public:
  Planning();
  bool existeixAssignatura(const std::string &nomAssignatura);

  bool existeixGrupEnAssignatura(const std::string &nomAssignatura, uint numeroGrup);

  void afegeixAssignatura(const std::string &nomAssignatura);

  void afegeixGrupAssignatura(const std::string &nomAssignatura, uint numeroGrup, bool esTeoric);

  void afegeixSlotGrupAssignatura(const std::string &nomAssignatura, uint numeroGrup, const std::string &hora,
  uint dia, const std::string &aula);
};

#endif
