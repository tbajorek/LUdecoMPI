CC=gcc
#Makro CC zawiera nazwę kompilatora
#CFLAGS=-Wall -ansi -pedantic
#Makro CFLAGS zawiera parametry kompilatora
TARGET=main

SOURCEDIR=src/
OBJDIR=obj/
INCLUDEDIR=include/
TARGETDIR=bin/
RESOURCESDIR=resources/

CFILES=$(wildcard $(SOURCEDIR)*.c)
OBJFILES=$(addprefix $(OBJDIR),$(notdir $(CFILES:.c=.o)))
INCFILES=$(wildcard $(INCLUDEDIR)*.h)
TARGETFILE=$(addprefix $(TARGETDIR),$(TARGET))

LIBS=-lm

all: build run

run:
	./$(TARGETFILE)

build:$(OBJDIR) $(TARGETDIR) $(TARGETFILE) $(RESOURCESDIR)

$(TARGETFILE): $(OBJFILES)
	$(CC) $(OBJFILES) -o $(TARGETFILE) $(LIBS)
	@echo executable file $(TARGETFILE) created

$(OBJFILES): $(OBJDIR)%.o: $(SOURCEDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJFILES): $(INCFILES)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(TARGETDIR):
	mkdir -p $(TARGETDIR)
$(RESOURCESDIR):
	mkdir -p $(RESOURCESDIR)

clean:
	rm -f $(OBJDIR)*.o $(TARGETFILE)
	rm -R ${OBJDIR} ${TARGETDIR}
	@echo clean finished

.PHONY: all clean build run
