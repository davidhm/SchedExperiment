#ifndef DEFAULTPROLOGWRITABLE_HH
#define DEFAULTPROLOGWRITABLE_HH

#include "structsAuxiliars.hh"
#include <string>

class DefaultPrologWritable : public PrologWritable {
private:
  std::ostream &escritor;
  static const std::string SUBJ_PREDICATE = "subject";
  static const std::string THEORY_GROUP_PREDICATE = "theoryGroup";
  static const std::string LAB_GROUP_PREDICATE = "labGroup";
  static const std::string SLOT_PREDICATE = "class";
  static void escriuAssignatura(uint assig);
  static void escriuGrupTeoria(uint assig, uint grup);
  static void escriuGrupLaboratori(uint assig, uint grup);
  static void escriuSlot(uint assig,uint grup,uint slot);
public:
  DefaultPrologWritable(std::ostream &escritor);
  void escriuAssignatures(const list<uint> &assignatures) override;
  void escriuGrups(const list<GrupsAssignatura> &grupsArg) override;
  void escriuSlots(const list<GrupsAssignatura> &slotsArg) override;
};

#endif
