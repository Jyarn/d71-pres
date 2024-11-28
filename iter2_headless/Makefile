EXE=nbody
OBJ=main.o Particle.o equations.o ../common/trace.o
CC=g++
CXXFLAGS=-O3 -fopenmp
LDFLAGS=

run: $(EXE)
	./$(EXE)

build: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $(EXE)

%.o: %.cc
	$(CC) $(CXXFLAGS) -c $? -o $@

clean:
	rm *.o test vgcore*
