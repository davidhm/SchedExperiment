#ifndef PLANNING_HH
#define PLANNING_HH

#include "assignatura.hh"
#include <string>
#include <vector>

typedef unsigned int uint;

class Planning {
private:
  std::vector <Assignatura> assignatures;
  int trobaAssignatura(const std::string &nomAssignatura);

public:
  Planning();
  bool existeixAssignatura(const std::string &nomAssignatura) const;

  bool existeixGrupEnAssignatura(const std::string &nomAssignatura, uint numeroGrup) const;

  void afegeixAssignatura(const std::string &nomAssignatura);

  void afegeixGrupAssignatura(const std::string &nomAssignatura, uint numeroGrup, bool esTeoric);

  void afegeixSlotGrupAssignatura(const std::string &nomAssignatura, uint numeroGrup, const std::string &hora,
  uint dia, const std::string &aula);

  uint getNombreAssignatures();

  list<uint> getGrupsTeoricsAssignatura(uint indexAssignatura);

  list<uint> getGrupsLaboratoriAssignatura(uint indexAssignatura);

  list<uint> getSlotsGrupAssignatura(uint indexAssignatura, uint grupAssignatura);

};

#endif
