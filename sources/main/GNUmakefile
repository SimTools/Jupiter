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

.PHONY: all
all:: bin

G4LIBS = $(shell \
         $(G4INSTALL)/lib/$(G4SYSTEM)/liblist \
          -d $(JUPITERROOT)/tmp/$(G4SYSTEM) \
          < $(G4INSTALL)/lib/$(G4SYSTEM)/libname.map)


include $(G4INSTALL)/config/architecture.gmk
include $(JUPITERROOT)/config/architecture.gmk

EXTRALIBS =	-L$(JUPITERROOT)/lib/$(G4SYSTEM) \
		-lJ4ir \
		-lJ4bd \
		-lJ4vtx \
		-lJ4it \
		-lJ4cdc \
		-lJ4cal \
		-lJ4sol \
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
	     -I../cal/include \
	     -I../sol/include \
	     -I../lcexp/include \
	     -I../kern/include

CPPFLAGS += -D__HOSHINA__

ifneq ($(findstring g++, $(G4SYSTEM)),)
   CXXFLAGS := $(subst -fno-for-scope,-ffor-scope,$(CXXFLAGS)) 
endif

G4TMPDIR  = $(G4TMP)/$(G4SYSTEM)/$(G4TARGET)

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

