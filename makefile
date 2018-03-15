IDIR =./include
INDIR =./lib
CC=g++
CFLAGS=-I$(IDIR) -I$(INDIR)
GLFLAGS= -lglut -lGL -lGLU
GTK= `pkg-config gtkmm-3.0 --cflags --libs`

ODIR =./bin
LDIR =./lib
SDIR =./src
BDIR =./build

LIBS=-lm

_DEPS = Classes.h gui.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Point.o Object3D.o Projection2D.o OrthoProjection.o Main.o Maingui.o Pointgui.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

ESS = ./bin/Point.o ./bin/Main.o

_BUILDS = main
BUILDS = $(patsubst %,$(BDIR)/%,$(_BUILDS))

MKDIR = mkdir -p

OUT_DIR = bin build

GTKFLAG = `pkg-config gtkmm-3.0 --cflags --libs`

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(GTKFLAG)

all: directories $(BUILDS)

directories: 
	$(MKDIR) $(OUT_DIR)

$(BDIR)/point: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BDIR)/object3d: $(OBJ) ./bin/Object3D.o ./bin/OrthoProjection.o
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BDIR)/projection2d: $(OBJ) ./bin/Projection2D.o ./bin/OrthoProjection.o
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BDIR)/ortho: $(OBJ) ./bin/OrthoProjection.o
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BDIR)/main: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(GTKFLAG) $(LIBS) 
