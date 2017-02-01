#ifndef CINWRAPPER_HH
#define CINWRAPPER_HH

#include "IstreamWrapper.hh"
#include <string>

class CinWrapper : public IstreamWrapper {
public:
  void getLinia(std::string &linia);
  bool streamAcabat();
}

#endif
