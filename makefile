#Makro CC zawiera nazwę kompilatora
CC=mpicc
MPEPATH?=/home/lukasz/mpe-install/mpe2/
FLAGS=-g -Iinclude/ -I$(MPEPATH)include -L$(MPEPATH)lib -lmpe -lpthread -lX11
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
METHOD_TYPE?=METHOD_MPI # METHOD_SEQ
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
	$(CC) -c $< -o $@ $(FLAGS) -D MPE_LOGS -D $(METHOD_TYPE)
else
	$(CC) -c $< -o $@ $(FLAGS) -D $(METHOD_TYPE)
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
	@echo '             DEFAULT: MPE_LOGS=false. METHOD_TYPE=METHOD_MPI'
	@echo '             If project is built with METHOD_TYPE=METHOD_MPI flag, '
	@echo '             then this task runs program in parallel version.'
	@echo '             If project was built with METHOD_TYPE=METHOD_SEQ flag, '
	@echo '             then this task runs program in sequential version.'
	@echo 'clean    - Removes $(OBJDIR)*.o files, $(TARGETFILE),'
	@echo '             ${OBJDIR} dir, ${TARGETDIR} dir.'
	@echo 'help     - Shows this printout.'
	@echo 'jumpshot - Runs jumpshot app. Project must be build in MPE_LOGS mode'
	@echo '             and METHOD_TYPE=METHOD_MPI.'
	@echo '             Can trigger log task.'
	@echo 'log      - Generates $(MPELOG_SLOG2FILE). Can trigger run task.'
	@echo '             Project must be build in MPE_LOGS mode'
	@echo '             and METHOD_TYPE=METHOD_MPI.'
	@echo 'mem    - Runs valgrind --leak-check=full  $(TARGETFILE)'
	@echo '             Can trigger build task.'
	@echo 'run      - Runs $(TARGETFILE). Can trigger build task.'
	@echo '             If project was built in MPE_LOGS mode'
	@echo	'			        and METHOD_TYPE=METHOD_MPI,'
	@echo '             then this task generates $(MPELOG_CLOG2FILE).'
	@echo '             If project was built with METHOD_TYPE=METHOD_MPI flag, '
	@echo '             then this task runs program in parallel version.'
	@echo '             If project was built with METHOD_TYPE=METHOD_SEQ flag, '
	@echo '             then this task runs program in sequential version.'
	@echo ''
	@echo '----------------------Advices----------------------'
	@echo '1) If you want to change MPE_LOGS or METHOD_TYPE variables,'
	@echo '    first you clean project.'
	@echo '2) Check, if MPEPATH variable value is compatible with your env.'
	@echo ''
	@echo '----------------------Examples----------------------'
	@echo 'make clean; make jumpshot MPE_LOGS=true NUMOFPROCS=3 '
	@echo ' Clean project. Build project parallel version with MPE_LOGS mode'
	@echo ' and run $(TARGETFILE) with 3 proccesses. Generate $(MPELOG_CLOG2FILE),'
	@echo ' $(MPELOG_SLOG2FILE). Run jumpshot app.'
	@echo ''
	@echo 'make clean;'
	@echo 'make MPEPATH=/opt/nfs/mpe2-2.4.9b/ MPE_LOGS=true NUMOFPROCS=3 '
	@echo '     METHOD_TYPE=METHOD_MPI'
	@echo ' Clean project. Build project parallel version with MPE_LOGS mode'
	@echo ' and run $(TARGETFILE) with 3 proccesses.'
	@echo ' MPEPATH variable value is given from command line.'
	@echo ' $(MPELOG_SLOG2FILE). Run jumpshot app.'
	@echo ''
	@echo 'make clean; make'
	@echo ' Clean project. Build project parallel version without MPE_LOGS mode'
	@echo ' and run $(TARGETFILE) with 4 proccesses.'
	@echo ''
	@echo 'make clean; make METHOD_TYPE=METHOD_SEQ NUMOFPROCS=1'
	@echo ' Clean project. Build project sequential version without MPE_LOGS mode'
	@echo ' and run $(TARGETFILE) with 1 proccess.'





.PHONY: all clean build run mem gen jumpshot log help
