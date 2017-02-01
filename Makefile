COMPILE_FLAGS = -Wall -std=c++11
OBJECT_FLAGS = $(COMPILE_FLAGS) -c
EXEC_NAME = scheduler.x

all: creadorPlanning.o planning.o assignatura.o grup.o hora.o slot.o main.cc escritorFitxer.o
	$(CXX) -o $(EXEC_NAME) $(BUILD_FLAGS) $^

debug: COMPILE_FLAGS += -g -D_GLIBCXX_DEBUG
debug: all

clean:
	rm *.x *.o

creadorPlanning.o: creadorPlanning.cc
	$(CXX) $(OBJECT_FLAGS) $^

planning.o: planning.cc
	$(CXX) $(OBJECT_FLAGS) $^

assignatura.o: assignatura.cc
	$(CXX) $(OBJECT_FLAGS) $^

grup.o: grup.cc
	$(CXX) $(OBJECT_FLAGS) $^

hora.o: hora.cc
	$(CXX) $(OBJECT_FLAGS) $^

slot.o: slot.cc
	$(CXX) $(OBJECT_FLAGS) $^

escritorFitxer.o: escritorFitxer.cc
	$(CXX) $(OBJECT_FLAGS) $^
