#ifndef HORA_CC
#define HORA_CC

#include "hora.hh"
#include <string>
#include <stdexcept>

Hora::Hora(const std::string &hora) :
slotHora(){
  if (hora.length() > 5) {
    std::string nomFitxer(__FILE__);
    std::string linia = std::to_string(__LINE__);
    throw std::runtime_error(nomFitxer.append(" ").append(linia).append(" : String es major de 5"));
  }
  try {
    slotHora = stoi(hora.substr(0,2));
  }
  catch (std::invalid_argument) {
    throw;
  }
  slotHora -= 7;
}

uint Hora::getSlot() const {
  return slotHora;
}

uint Hora::getNombreSlotsPerDia() {
  return 13;
}

#endif
