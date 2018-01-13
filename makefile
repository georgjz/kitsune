# simple makefile for Kitsune
CC=clang++
LFLAGS=-O2
LIBS=-lpng -lX11 -lpthread
CCFLAGS=-Wall -Isrc/ -c -g -std=c++11

# directories
SRCDIR=src
OBJDIR=obj
BLDDIR=build

SOURCES=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLE=$(BLDDIR)/kitsune

default: $(EXECUTABLE)

$(OBJDIR):
	@mkdir -p $@

$(BLDDIR):
	@mkdir -p $@

$(EXECUTABLE): $(OBJECTS) | $(BLDDIR)
	$(CC) $(LFLAGS) $^ -o $@ $(LIBS)

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CCFLAGS) -o $@ $<
