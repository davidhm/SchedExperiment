#ifndef CREADORPLANNING_CC
#define CREADORPLANNING_CC

#include "planning.hh"
#include "creadorPlanning.hh"
#include <istream>
#include <string>
#include <sstream>
#include <fstream>



CreadorPlanning::CreadorPlanning(std::istream &&stream) :
llegidor(std::move(stream)),planning() {}

CreadorPlanning::CreadorPlanning(std::istream stream) :
llegidor(stream),planning() {}

void CreadorPlanning::omplePlanning() {
  std::string linia;
  while (not (getline(llegidor,linia).eof())) {
    std::istringstream llegidorLinia(linia);
    std::string assignatura;
    llegidorLinia >> std::ws >> assignatura >> std::ws;
    if (not planning.existeixAssignatura(assignatura))
      planning.afegeixAssignatura(assignatura);
    uint grup, dia;
    std::string hora;
    char laboOTeoria;
    std::string aula;
    bool esTeoric;
    llegidorLinia >> std::ws >> grup >> std::ws >> dia >> std::ws;
    llegidorLinia >> hora >> std::ws >> laboOTeoria >> std::ws >> aula;
    esTeoric = laboOTeoria == 'T';
    if (not planning.existeixGrupEnAssignatura(assignatura,grup)) {
      planning.afegeixGrupAssignatura(assignatura,grup,esTeoric);
    }
    planning.afegeixSlotGrupAssignatura(assignatura,grup,hora,dia,aula);
  }
}
Planning CreadorPlanning::getPlanning() {
  return planning;
}


#endif
