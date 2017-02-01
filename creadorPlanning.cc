#ifndef CREADORPLANNING_CC
#define CREADORPLANNING_CC

#include "planning.hh"
#include "creadorPlanning.hh"
#include <istream>
#include <string>
#include <sstream>
#include <fstream>



CreadorPlanning::CreadorPlanning(istream *stream) {
  llegidor = stream;
}
void CreadorPlanning::omplePlanning() {
  string linia;
  while (not (getline(*llegidor,linia).eof())) {
    istringstream llegidorLinia(linia);
    string assignatura;
    llegidorLinia >> ws >> assignatura >> ws;
    if (not planning.existeixAssignatura(assignatura))
      planning.afegeixAssignatura(assignatura);
    uint grup, dia;
    string hora;
    char laboOTeoria;
    string aula;
    bool esTeoric;
    llegidorLinia >> ws >> grup >> ws >> dia >> ws >> hora >> ws >> laboOTeoria >> ws >> aula;
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
