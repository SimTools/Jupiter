########################################################################	
##
## ---------------------------
##   Makefile for JUPITER 
## ---------------------------
##
## (Version Information)
##   Version: 2002a
##   Release: 1
##
## (Update Record)
##    2001/12/7  K.Hoshina	Original version.
##
## (Description)
## (Targets)
##	all       	: creates libraries in lib.
##	clean     	: deletes *.o ...
##	distclean     	: clean up for distribution.
## 
########################################################################	

SHELL	= `which bash`
MFLAGS	=
CURRDIR	= .

SUBDIRS	= sources 

.PHONY: all clean

all:
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS); do \
	(cd $$i; echo ``making'' all ``in $(CURRDIR)/$$i...''; \
	$(MAKE) $(MFLAGS)); \
	done

clean:
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS); do \
	(cd $$i; echo ``making'' clean ``in $(CURRDIR)/$$i...''; \
	$(MAKE) $(MFLAGS) clean); \
	done

distclean: clean
	find . -name '*~'      -exec rm -rf {} \;
	find . -name '*.bak'   -exec rm -rf {} \;
	find . -name '*.ORIG'  -exec rm -rf {} \;
	find . -name '*.tmp'   -exec rm -rf {} \;
	find . -name '*.keep'  -exec rm -rf {} \;
	find . -name '.gdb*'   -exec rm -rf {} \;
	find . -name '.Apple*' -exec rm -rf {} \;
	find . -name '.DS*'    -exec rm -rf {} \;
	find . -name '.DAWN*'  -exec rm -rf {} \;
	find . -name '.VRML*'  -exec rm -rf {} \;


