#Makro CC zawiera nazwę kompilatora
CC=mpicc
MPEPATH?=/home/lukasz/mpe-install/mpe2/
FLAGS=-g -I$(MPEPATH)include -L$(MPEPATH)lib -lmpe -lpthread -lX11
# tbajorek
# MPEPATH= ?
# lukasz22
# MPEPATH=/home/lukasz/mpe-install/mpe2/
# TAURUS
# source source_bash.sh
# MPEPATH=/opt/nfs/mpe2-2.4.9b/
# MPEPATH=/opt/nfs/mpe2-1.3.0/
RUNFLAGS=
#CFLAGS=-Wall -ansi -pedantic
#Makro CFLAGS zawiera parametry kompilatora
TARGET=main
NODES=nodes
MPELOG=mpe_logs

SOURCEDIR=src/
OBJDIR=obj/
INCLUDEDIR=include/
TARGETDIR=bin/
RESOURCESDIR=resources/

CFILES=$(wildcard $(SOURCEDIR)*.c)
OBJFILES=$(addprefix $(OBJDIR),$(notdir $(CFILES:.c=.o)))
INCFILES=$(wildcard $(INCLUDEDIR)*.h)
TARGETFILE=$(addprefix $(TARGETDIR),$(TARGET))
NODESFILE=$(addprefix $(TARGETDIR),$(NODES))
MPELOG_CLOG2FILE=$(addprefix $(TARGETDIR),$(MPELOG).clog2)
MPELOG_SLOG2FILE=$(addprefix $(TARGETDIR),$(MPELOG).slog2)
LIBS=-lm

NUMOFPROCS?=4
MPE_LOGS?=false
all: run

run: build
	mpiexec $(RUNFLAGS) -n $(NUMOFPROCS) ./$(TARGETFILE)

jumpshot: log
	$(MPEPATH)bin/jumpshot $(MPELOG_SLOG2FILE)

log: $(MPELOG_SLOG2FILE) $(MPELOG_CLOG2FILE)

$(MPELOG_SLOG2FILE): $(MPELOG_CLOG2FILE)
	$(MPEPATH)bin/clog2TOslog2 $(MPELOG_CLOG2FILE)
$(MPELOG_CLOG2FILE):
	make run


build:$(OBJDIR) $(TARGETDIR) $(TARGETFILE) $(RESOURCESDIR)

$(TARGETFILE): $(OBJFILES)
	$(CC) $(OBJFILES) -o $(TARGETFILE) $(FLAGS) $(LIBS)
	@echo executable file $(TARGETFILE) created
$(OBJFILES): $(OBJDIR)%.o: $(SOURCEDIR)%.c
ifeq ($(MPE_LOGS),true)
	$(CC) -c $< -o $@ $(FLAGS) -D MPE_LOGS
else
	$(CC) -c $< -o $@ $(FLAGS)
endif

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

mem: build
	valgrind --leak-check=full  $(TARGETFILE)

help:
	@echo '------------------------HELP------------------------'
	@echo 'all      - Execute run task.'
	@echo '           Can trigger log task.'
	@echo 'build    - Generates $(OBJDIR)*.o files, $(TARGETFILE).'
	@echo '             Creates ${OBJDIR} dir, ${TARGETDIR} dir.'
	@echo '             If MPE_LOGS=true, then $(TARGETFILE) is in MPE_LOGS mode.'
	@echo '             DEFAULT: MPE_LOGS=false.'
	@echo 'clean    - Removes $(OBJDIR)*.o files, $(TARGETFILE),'
	@echo '             ${OBJDIR} dir, ${TARGETDIR} dir.'
	@echo 'help     - Shows this printout.'
	@echo 'jumpshot - Runs jumpshot app.'
	@echo '             Can trigger log task.'
	@echo 'log      - Generates $(MPELOG_SLOG2FILE). Can trigger run task.'
	@echo '             $(TARGETFILE) must be in MPE_LOGS mode'
	@echo 'run      - Runs $(TARGETFILE). Can trigger build task.'
	@echo '             If $(TARGETFILE) is in MPE_LOGS mode,'
	@echo '             then this task generates $(MPELOG_CLOG2FILE).'
	@echo ''
	@echo '----------------------Advices----------------------'
	@echo '1) If you want to change MPE_LOGS variable, first you clean project.'
	@echo '2) Check, if MPEPATH variable value is compatible with your env.'
	@echo ''
	@echo '----------------------Examples----------------------'
	@echo 'make clean; make jumpshot MPE_LOGS=true NUMOFPROCS=3'
	@echo ' Clean project. Build project with MPE_LOGS mode'
	@echo ' and run $(TARGETFILE) with 3 proccess. Generate $(MPELOG_CLOG2FILE),'
	@echo ' $(MPELOG_SLOG2FILE). Run jumpshot app.'
	@echo ''
	@echo 'make clean;'
	@echo 'make MPEPATH=/opt/nfs/mpe2-2.4.9b/ MPE_LOGS=true NUMOFPROCS=3'
	@echo ' Clean project. Build project with MPE_LOGS mode'
	@echo ' and run $(TARGETFILE) with 3 proccess.'
	@echo ' MPEPATH variable value is given from command line.'
	@echo ' $(MPELOG_SLOG2FILE). Run jumpshot app.'
	@echo ''
	@echo 'make clean; make'
	@echo ' Clean project. Build project without MPE_LOGS mode'
	@echo ' and run $(TARGETFILE) with 4 proccess.'





.PHONY: all clean build run mem gen jumpshot log help
