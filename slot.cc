#ifndef SLOT_CC
#define SLOT_CC

#include "hora.hh"
#include "slot.hh"
#include <string>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <iostream>



Slot::Slot(const string &horaString, uint dia, const string &aula) {
  diaSetmana = dia;
  this -> aula = aula;
  try {
    horaSlot = new Hora(horaString);
  }
  catch (invalid_argument e) {
    cerr << e.what() << endl;
    cerr << "La hora donada " << horaString << " no te un format valid." << endl;
    exit(1);
  }
  catch (exception e) {
    cerr << e.what() << endl;
    exit(1);
  }
}

Slot::~Slot() {
  delete horaSlot;
}

#endif
