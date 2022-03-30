SRCBASE=$(wildcard src/*.cpp)

SRC=$(SRCBASE) main.cpp
TEST=$(SRCBASE) $(wildcard test/*.cpp)

EXE=prog.exe
# EXETEST=test.exe

DOSSIER=build
DOSSIER_INCLUDE=./include
DOSSIER_LIB=./lib

WARNING+=-Wall -Wextra
CXXFLAGS+= -MMD -g -O2 -fdiagnostics-color=auto -I $(DOSSIER_INCLUDE)

LDSFML= -L $(DOSSIER_LIB) -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS=  $(LDSFML) #-lSDL

OBJ=$(addprefix $(DOSSIER)/, $(SRC:.cpp=.o) )
DEP=$(addprefix $(DOSSIER)/, $(SRC:.cpp=.d) )

# Test
OBJTEST=$(addprefix $(DOSSIER)/, $(TEST:.cpp=.o) )
DEPTEST=$(addprefix $(DOSSIER)/, $(TEST:.cpp=.d) )


all: $(OBJ)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)


$(DOSSIER)/%.o: %.cpp
	@mkdir -p $(DOSSIER)
	$(CXX) $(CXXFLAGS) -o $@ -c $<


test : $(OBJTEST)
	$(CXX) -o $(EXETEST) $^ $(LDFLAGS)


clean:
	rm -rf *.o

mrproper: clean
	rm $(EXE)

-include $(DEP) 
-include $(DEPTEST)
# -include $(DOSSIER_INCLUDE)