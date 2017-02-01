#ifndef CREADORPLANNING_HH
#define CREADORPLANNING_HH

#include "planning.hh"
#include <istream>
#include <string>
#include <sstream>
#include <fstream>



class CreadorPlanning {
private:
  Planning planning;
  istream *llegidor;

public:
  CreadorPlanning(istream *stream);

  void omplePlanning();

  Planning getPlanning();

};

#endif
