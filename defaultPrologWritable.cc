#ifndef DEFAULTPROLOGWRITABLE_CC
#define DEFAULTPROLOGWRITABLE_CC

#include <string>

DefaultPrologWritable::DefaultPrologWritable(std:: ostream &escritor) :
escritor(escritor) {}

static void DefaultPrologWritable::escriuAssignatura(uint assig) {
  std::string aux(SUBJ_PREDICATE);
  escritor << aux.append("(").append(std::to_string(assig)).append(").") << std::endl;
}

static void DefaultPrologWritable::escriuGrupTeoria(uint assig, uint grup) {
  std::string aux(THEORY_GROUP_PREDICATE);
  escritor << aux.append("(").append(std::to_string(assig)).append(",").append(std::to_string(grup)).append(").");
  escritor << std::endl;
}

static void DefaultPrologWritable::escriuGrupLaboratori(uint assig, uint grup) {
  std::string aux(LAB_GROUP_PREDICATE);
  escritor << aux.append("(").append(std::to_string(assig)).append(",").append(std::to_string(grup)).append(").");
  escritor << std::endl;
}

static void DefaultPrologWritable::escriuSlot(uint assig, uint grup, uint slot) {
  std::string aux(SLOT_PREDICATE);
  aux.append("(").append(std::to_string(assig)).append(",").append(std::to_string(grup)).append(",");
  aux.append(std::to_string(slot)).append(").")
  escritor << aux << std::endl;
}

void DefaultPrologWritable::escriuAssignatures(const list<uint> &assignatures) override {
  for (uint i : assignatures)
    escriuAssignatura(i);
}

void DefaultPrologWritable::escriuGrups(const list<GrupsAssignatura> &grupsArg) override {
  for (GrupsAssignatura i : grupsArg) {
    for (GrupInfo j : i.grups) {
      if (j.grup.esTeoric)
        escriuGrupTeoria(i.assignatura,j.grup);
      else
        escriuGrupLaboratori(i.assignatura,j.grup);
    }
  }
}

void DefaultPrologWritable::escriuSlots(const list<GrupsAssignatura> &slotsArg) override {
  for (GrupsAssignatura i : slotsArg)
    for (GrupAmbSlots j : i.grups)
      for (uint slot : j.slots)
        escriuSlot(i.assignatura,j.grup.grup,slot);
}

#endif
