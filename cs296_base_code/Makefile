.SUFFIXES: .cpp .hpp

STATIC_LIB = TRUE
SLIB_N = libCS296.a
DLIB_N = libCS296.so
direct=TRUE

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_exe_05
TARGETLIB = cs296_exe_05_lib
GRP_NUM = 05

# Project Paths
PROJECT_ROOT=.
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/myobjs
BINDIR = $(PROJECT_ROOT)/mybins
DOCDIR = $(PROJECT_ROOT)/doc
LIBDIR = $(PROJECT_ROOT)/mylibs
SCPTDIR = $(PROJECT_ROOT)/scripts/

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS := -lBox2D -lglui -lglut -lGLU -lGL 

# Compiler and Linker flags
CPPFLAGS =-g -Wall -pg  
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include -fPIC 
LDFLAGS+=-L $(LIBDIR) -L $(BOX2D_ROOT)/lib  -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
TEMP := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJS := $(patsubst $(OBJDIR)/main.o,,$(TEMP))



.PHONY: all setup doc clean distclean exe exehelper exelib exelibhelper compile compileExe compileExeLib

all: exeoptimized

exeoptimized: optimizer exehelper setup compileExe
optimizer:
	$(eval CPPFLAGS:=$(CPPFLAGS) -O3)

exe: exehelper setup compileExe $(BINDIR)/$(TARGET)
exehelper:
	$(eval forexe:=$(OBJS))
	$(eval direct := TRUE )

exelib: exelibhelper setup compileExeLib

exelibhelper:
	$(eval LIBS := -lCS296 $(LIBS) )
	$(eval direct := FALSE )


setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p myobjs
	@mkdir -p mybins
	@mkdir -p mylibs


compileExeLib: $(LIBDIR)/$(DLIB_N) $(LIBDIR)/$(SLIB_N) $(OBJDIR)/main.o compile

compileExe:$(TEMP) compile

$(BINDIR)/$(TARGET_SLIB): $(OBJS) main.cpp
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $(BINDIR)/$(TARGET) $(LDFLAGS) $(CPPFLAGS) $(OBJDIR)/main.o $(forexe) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err


$(BINDIR)/$(TARGET_DLIB): $(OBJS) main.cpp
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $(BINDIR)/$(TARGET) $(LDFLAGS) $(CPPFLAGS) $(OBJDIR)/main.o $(forexe) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

$(BINDIR)/$(TARGET): $(LIBDIR)/$(DLIB_N) $(LIBDIR)/$(SLIB_N) main.cpp
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $(BINDIR)/$(TARGET) $(LDFLAGS) $(CPPFLAGS) $(OBJDIR)/main.o $(forexe) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(TEMP:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
ifeq($(direct),TRUE)
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err
endif

$(LIBDIR)/$(DLIB_N): $(OBJS)
ifeq($(direct),false)
ifneq ($(STATIC_LIB),TRUE)
	@$(CC) -shared -Wl,-soname,libCS296.so -o $(LIBDIR)/libCS296.so $(OBJS)
endif
endif
	
$(LIBDIR)/$(SLIB_N) : $(OBJS)
ifeq($(direct),false)
ifeq ($(STATIC_LIB),TRUE)
	@rm -f $@
	@ar -cq  $@ $(OBJS)
endif
endif

$(PROJECT_ROOT)/external/lib/libBox2D.a :
	@cd external/src/; \
	 tar -xvf Box2D.tgz; \
	 cd Box2D; \
	 mkdir build296; \
	 cd build296; \
	 cmake ../ && make && make install 
	
	
report:$(PROJECT_ROOT)/external/lib/libBox2D.a all
	@mkdir -p data
	@mkdir -p plots
	@python3 ./scripts/g05_gen_csv.py
	@python3 ./scripts/g05_gen_plots.py
	@python3 ./scripts/g05_gen_html.py
	
reporttemp:
	@latex ./doc/g05_prof_report.tex
	@dvipdf g05_prof_report.dvi $(DOCDIR)/g05_prof_report.pdf 	 
	@$(RM) g05_prof_report.* 


reporttemo:
	@latex $(DOCDIR)/report_cs296_05.tex 
	@bibtex report_cs296_05.aux 
	@latex $(DOCDIR)/report_cs296_05.tex 
	@latex $(DOCDIR)/report_cs296_05.tex 
	@dvipdf report_cs296_05.dvi $(DOCDIR)/report_cs296_05.pdf 
	@$(RM) report_cs296_05.* 

plot01:
	@mkdir -p data
	@mkdir -p plots
	@./scripts/gen_data.sh
	@./scripts/gen_csv.sh
	@./scripts/gen_plots.sh

plot02:
	@mkdir -p data
	@mkdir -p plots
	@./scripts/gen_data_csv.sh
	@./scripts/gen_plots.sh
plot:
	@mkdir -p plots
	@./scripts/gen_plots.sh

release_prof:clean
	cd external/src/; \
	 rm -rf Box2D;\
	 tar -xvf Box2D.tgz; \
	 cd Box2D; \
	 mkdir build296; \
	 cd build296; \
	 cmake -DCMAKE_BUILD_TYPE=Release ../ && make && make install 
	@make exeoptimized
	@$(BINDIR)/$(TARGET) 
	@gprof $(BINDIR)/$(TARGET) gmon.out > 	g05_release_prof.dat

debug_prof: clean
	cd external/src/; \
	 rm -rf Box2D;\
	 tar -xvf Box2D.tgz; \
	 cd Box2D; \
	 mkdir build296; \
	 cd build296; \
	 cmake -DCMAKE_BUILD_TYPE=Debug ../ && make && make install 
	@make exedebug
	@$(BINDIR)/$(TARGET) 
	@gprof $(BINDIR)/$(TARGET) gmon.out > 	g05_debug_prof.dat



Box2D:
	cd external/src/; \
	 tar -xvf Box2D.tgz; \
	 cd Box2D; \
	 mkdir build296; \
	 cd build296; \
	 cmake ../ && make && make install 

removeBox2D:
	rm -rf external
	cp -rf ~/ssl/cs296_base_code/external .

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ data plots $(BINDIR) *.dat gmon.out 
	@$(RM) -rf ./doc/g05_lab09_plot0?.png ./doc/*.html 
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(DOCDIR)/html $(LIBDIR) $(DOCDIR)/report_cs296_05.pdf

