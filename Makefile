WARNING_FLAGS = -Wall -Weffc++ -pedantic  \
-pedantic-errors -Wextra -Wcast-align \
-Wcast-qual \
-Wdisabled-optimization \
-Werror -Wfloat-equal -Wformat=2 \
-Wformat-nonliteral -Wformat-security  \
-Wformat-y2k \
-Wimport  -Winit-self  -Winline \
-Winvalid-pch   \
-Wlong-long \
-Wmissing-field-initializers -Wmissing-format-attribute   \
-Wmissing-include-dirs -Wmissing-noreturn \
-Wpacked -Wpointer-arith \
-Wredundant-decls \
-Wstack-protector \
-Wstrict-aliasing=2 -Wswitch-default \
-Wswitch-enum \
-Wunreachable-code -Wunused \
-Wunused-parameter \
-Wvariadic-macros \
-Wwrite-strings
COMPILE_FLAGS = $(WARNING_FLAGS) -std=c++11
OBJECT_FLAGS = $(COMPILE_FLAGS) -c
EXEC_NAME = scheduler.x

all: creadorPlanning.o planning.o assignatura.o grup.o hora.o slot.o main.cc escritorProlog.o
	$(CXX) -o $(EXEC_NAME) $(COMPILE_FLAGS) $^

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

escritorProlog.o: escritorProlog.cc
	$(CXX) $(OBJECT_FLAGS) $^

defaultPrologWritable.o : defaultPrologWritable.cc
	$(CXX) $(OBJECT_FLAGS) $^
