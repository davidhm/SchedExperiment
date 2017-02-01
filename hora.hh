#ifndef HORA_HH
#define HORA_HH

#include <string>
#include <stdexcept>
#include <exception>

typedef unsigned int uint;

class Hora {
private:
  unsigned int slotHora;
public:
  Hora(const std::string &hora);

  uint getSlot() const;
};

#endif
