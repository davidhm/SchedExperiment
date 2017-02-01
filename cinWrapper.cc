#ifndef CINWRAPPER_CC
#define CINWRAPPER_CC

#include <iostream>
#include <string>
#include <ios>
#include <stdexcept>

void CinWrapper::getLinia(std::string &linia) {
  std::getline(std::cin,linia);
  if (std::iostate == failbit) {
    throw std::runtime_error("L'string es mes petit que la linia.");
  }
}

bool CinWrapper::streamAcabat() {
  return std::iostate == eofbit;
}

#endif
