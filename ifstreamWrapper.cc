#ifndef IFSTREAMWRAPPER_CC
#define IFSTREAMWRAPPER_CC

#include <string>
#include <fstream>
#include <ios>
#include <stdexcept>

IfstreamWrapper::IfstreamWrapper(const string &pathFitxer) :
llegidor(pathFitxer) {}

void IfstreamWrapper::getLinia(std::string &linia) {
  std::getline(llegidor,linia);
  if (std::iostate = failbit)
    throw runtime_error("La linia no cap a l'string.")
}

bool IfstreamWrapper::streamAcabat() {
  return std::iostate = eofbit;
}

#endif
