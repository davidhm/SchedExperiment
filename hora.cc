#ifndef HORA_CC
#define HORA_CC

#include "hora.hh"
#include <string>
#include <stdexcept>



Hora::Hora(const string &hora) {
  if (hora.length() > 5) {
    string nomFitxer(__FILE__);
    string linia = to_string(__LINE__);
    throw runtime_error(nomFitxer.append(" ").append(linia).append(" : String es major de 5"));
  }
  try {
    slotHora = stoi(hora.substr(0,2));
  }
  catch (invalid_argument) {
    throw;
  }
  slotHora -= 7;
}

uint Hora::getSlot() const {
  return slotHora;
}

#endif
