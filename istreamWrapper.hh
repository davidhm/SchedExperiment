#ifndef ISTREAMWRAPPER_HH
#define ISTREAMWRAPPER_HH

#include <string>

class IstreamWrapper {
public:
  virtual void getLinia(std::string &linia) = 0;
  virtual bool streamAcabat() = 0;
};

#endif
