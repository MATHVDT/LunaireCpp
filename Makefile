SRCBASE=$(wildcard src/*.cpp)


SRC=$(SRCBASE) main.cpp
TEST=$(SRCBASE) $(wildcard tests/*.cpp) 

EXE=prog.exe
EXETEST=test.exe

DOSSIER_SRC=src/
DOSSIER_TESTS=tests/

DOSSIER_BUILD=build
DOSSIER_INCLUDE=./include
DOSSIER_LIB=./lib/

WARNING+=-Wall -Wextra
OPTIMISATION=
CXXFLAGS+= -MMD -g $(OPTIMISATION) -fdiagnostics-color=auto -I $(DOSSIER_INCLUDE)

# -L $(DOSSIER_LIB)

LDSFML= -L $(DOSSIER_LIB) -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS=  $(LDSFML) 


OBJ=$(addprefix $(DOSSIER_BUILD)/, $(SRC:%.cpp=%.o) )
DEP=$(addprefix $(DOSSIER_BUILD)/, $(SRC:%.cpp=%.d) )

# Test
OBJTEST=$(addprefix $(DOSSIER_BUILD)/, $(TEST:%.cpp=%.o) )
DEPTEST=$(addprefix $(DOSSIER_BUILD)/, $(TEST:%.cpp=%.d) )


all: $(OBJ)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)

# Generation des fichier objet .o et .d
$(DOSSIER_BUILD)/%.o: %.cpp
	@mkdir -p $(DOSSIER_BUILD)/src/
	@mkdir -p $(DOSSIER_BUILD)/tests/
	$(CXX) $(CXXFLAGS) -o $@ -c $<


test : $(OBJTEST)
	$(CXX) -o $(EXETEST) $^ $(LDFLAGS)


clean:
	rm -rf build/*

mrproper: clean
	rm $(EXE)

-include $(DEP) 
-include $(DEPTEST)