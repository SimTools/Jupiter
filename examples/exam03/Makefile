
CERNLIB=/proj/soft/ext/cernlib/pro

OBJS   = pythia_main.o
FFLAGS = -I$(CERNLIB)/include -fno-automatic -fPIC \
			-fdollar-ok -fno-backslash -fno-automatic -fno-f90 -fugly-complex \
			-fno-globals -fugly-init -Wno-globals \
			-fno-second-underscore 

LIBS   = -L$(CERNLIB)/lib -lpythia6205 -lpdflib804 \
		-lmathlib -lpacklib -lnsl -lcrypt -ldl

all: pythia.exe

pythia.exe: $(OBJS)
	$(FC) $(FFLAGS) -o pythia.exe $(OBJS) $(LIBS)


clean:
	rm -f *~ *.o *.exe
