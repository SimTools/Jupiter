########################################################################	##
##
## ---------------------------
##   Makefile for JUPITER 
## ---------------------------
##
## (Version Information)
##   Version: 1.6
##   Release: 01
##
## (Update Record)
##    2001/12/7  K.Hoshina	Original version.
##
## (Description)
## (Targets)
##	all       	: creates libraries in lib.
##	clean     	: deletes *.o ...
## 
########################################################################	

SHELL	= `which bash`
MFLAGS	=
CURRDIR	= .

#SUBDIRS	= kern ir bd cal cdc it vtx sol main
SUBDIRS	= kern ir bd cal cdc it sol lcexp vtx ct main

CPPFLAGS += -D__HOSHINA__

.PHONY: all
all: 
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS); do \
	(cd $$i; echo ``making'' all ``in $(CURRDIR)/$$i...''; \
	$(MAKE) $(MFLAGS)); \
	done

clean:
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS) $(BABYSUBDIRS); do \
	(cd $$i; echo ``making'' clean ``in $(CURRDIR)/$$i...''; \
	$(MAKE) $(MFLAGS) clean); \
	done

