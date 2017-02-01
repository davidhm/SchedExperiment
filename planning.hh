#ifndef PLANNING_HH
#define PLANNING_HH

#include "assignatura.hh"
#include <string>
#include <vector>


class Planning {
private:
  vector <Assignatura> assignatures;
  int trobaAssignatura(const string &nomAssignatura);

public:
  Planning();
  bool existeixAssignatura(const string &nomAssignatura);

  bool existeixGrupEnAssignatura(const string &nomAssignatura, uint numeroGrup);

  void afegeixAssignatura(const string &nomAssignatura);

  void afegeixGrupAssignatura(const string &nomAssignatura, uint numeroGrup, bool esTeoric);

  void afegeixSlotGrupAssignatura(const string &nomAssignatura, uint numeroGrup, const string &hora,
  uint dia, const string &aula);
};

#endif
