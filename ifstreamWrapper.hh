#ifndef IFSTREAMWRAPPER_HH
#define IFSTREAMWRAPPER_HH

#include <string>
#include <fstream>

class IfstreamWrapper : public IstreamWrapper {
private:
  ifstream llegidor;
public:
  IstreamWrapper(const string &pathFitxer);
  void getLinia(std::string &linia);
  bool streamAcabat();
};

#endif
