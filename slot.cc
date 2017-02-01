#ifndef SLOT_CC
#define SLOT_CC

#include "hora.hh"
#include "slot.hh"
#include <string>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <iostream>



Slot::Slot(const std::string &horaString, uint dia, const std::string &aula) :
horaSlot(horaString),diaSetmana(dia),aulaSlot(aula) {}

#endif
