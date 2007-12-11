# $Id$
# --------------------------------------------------------------
#   GNUmakefile for examples module.
#                             .G4UserGroup, 2000
# --------------------------------------------------------------

name     := Jupiter
G4TARGET := $(name)
G4EXLIB  := 
G4TMP    := $(JUPITERROOT)/tmp
G4BIN	 := $(JUPITERROOT)/bin

ifndef G4WORKDIR
  G4WORKDIR := .
endif

# Folowing lines are included to use object dependantly with version number
G4Version = $(shell grep define $(G4INSTALL)/include/G4Version.hh |grep G4VERSION_NUMBER | sed -e 's/  / /g'  | cut -d" " -f3 )

USEG4PropagatorInField=$(shell test $(G4Version) -gt 820 && echo yes)


.PHONY: all
all:: bin 

includes:

G4LIBS = $(shell \
         $(G4INSTALL)/lib/$(G4SYSTEM)/liblist \
          -d $(JUPITERROOT)/tmp/$(G4SYSTEM) \
          < $(G4INSTALL)/lib/$(G4SYSTEM)/libname.map)


include $(G4INSTALL)/config/architecture.gmk
include $(JUPITERROOT)/config/architecture.gmk

EXTRALIBS = 	$(EXTRAOBJS) \
		-L$(JUPITERROOT)/lib/$(G4SYSTEM) \
		-lJ4ir \
		-lJ4bd \
		-lJ4vtx \
		-lJ4it \
		-lJ4cal \
		-lJ4clx \
		-lJ4cdc \
		-lJ4tpc \
		-lJ4sol \
		-lJ4mud \
		-lJ4lcexp \
		-lJ4kern \
		$(G4LIBS)

EXTRA_LINK_DEPENDENCIES += $(shell \
        echo $(JUPITERROOT)/tmp/$(G4SYSTEM)/*/obj.last)

CPPFLAGS  += -I../ir/include \
	     -I../bd/include \
	     -I../vtx/include \
	     -I../it/include \
	     -I../cdc/include \
	     -I../tpc/include \
	     -I../cal/include \
	     -I../clx/include \
	     -I../sol/include \
	     -I../mud/include \
	     -I../lcexp/include \
	     -I../kern/include

CPPFLAGS += -D__HOSHINA__

include $(JUPITERROOT)/config/CLHEPversion.gmk

ifneq ($(findstring g++, $(G4SYSTEM)),)
   CXXFLAGS := $(subst -fno-for-scope,-ffor-scope,$(CXXFLAGS)) 
endif

G4TMPDIR  = $(G4TMP)/$(G4SYSTEM)/$(G4TARGET)

ifeq ($(UNAME_MACHINE),x86_64)
   LDFLAGS += -L/usr/X11R6/lib64
endif

include $(G4INSTALL)/config/binmake.gmk

CXXFLAGS_WITHOUT_O := $(filter-out -O%, $(CXXFLAGS))

ifeq ($(G4SYSTEM),Darwin-g++)
$(G4TMPDIR)/J4DetectorConstruction.o: src/J4DetectorConstruction.cc
	$(CXX) $(CXXFLAGS_WITHOUT_O) $(CPPFLAGS) -c -o $@ \
	  src/J4DetectorConstruction.cc
endif

ifeq ($(G4SYSTEM),Linux-g++)
$(G4TMPDIR)/J4DetectorConstruction.o: src/J4DetectorConstruction.cc
	$(CXX) $(CXXFLAGS_WITHOUT_O) $(CPPFLAGS) -c -o $@ \
	  src/J4DetectorConstruction.cc
endif


