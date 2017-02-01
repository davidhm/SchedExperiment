#ifndef SLOT_CC
#define SLOT_CC

#include "hora.hh"
#include "slot.hh"
#include <string>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <iostream>



Slot::Slot(const std::string &horaString, uint dia, const std::string &aula) {
  diaSetmana = dia;
  this -> aula = aula;
  try {
    horaSlot = new Hora(horaString);
  }
  catch (std::invalid_argument e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "La hora donada " << horaString << " no te un format valid." << std::endl;
    exit(1);
  }
  catch (std::exception e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }
}

Slot::~Slot() {
  delete horaSlot;
}

#endif
