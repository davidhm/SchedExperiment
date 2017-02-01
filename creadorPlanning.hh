#ifndef CREADORPLANNING_HH
#define CREADORPLANNING_HH

#include "planning.hh"
#include <istream>
#include <string>
#include <sstream>
#include <fstream>



class CreadorPlanning {
private:
  std::istream llegidor;
  Planning planning;

public:
  CreadorPlanning(std::istream &&stream);
  CreadorPlanning(std::istream stream);
  void omplePlanning();

  Planning getPlanning();

};

#endif
