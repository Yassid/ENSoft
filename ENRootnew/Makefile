# MAKE FILE FOR ENROOT
OBJ = ENConvert
#sourcefile = ENMain.cxx TENUnpack.cxx TENDumptxt.h TENDumptxt.cxx TENUnpack.h TENPPAC_Sort.cxx TENPPAC_Sort.h TENPla_Sort.cxx TENPla_Sort.h TENNaI_Sort.cxx TENNaI_Sort.h TENIonChamb_Sort.cxx TENIonChamb_Sort.h TENSSD_Sort.cxx TENSSD_Sort.h TENTS_Sort.cxx TENTS_Sort.h 

sourcefile = ENMain.cxx ENMain.h ../EN_Go4/EN_PPAC_Cal.cxx ../EN_Go4/EN_PPAC_Cal.h ../EN_Go4/ENFiberCal.cxx ../EN_Go4/ENFiberCal.h ../EN_Go4/ENPlastic.cxx ../EN_Go4/EN_CsI.cxx ../EN_Go4/EN_DSSD.cxx ../EN_Go4/EN_Neutron.cxx ../EN_Go4/EN_MWDC.cxx ../EN_Go4/EN_Coin.cxx ../EN_Go4/ENPlastic.h ../EN_Go4/EN_CsI.h ../EN_Go4/EN_DSSD.h ../EN_Go4/EN_Neutron.h ../EN_Go4/EN_MWDC.h ../EN_Go4/EN_Coin.h

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

CFLAGS = -Wall -O2 -I$(TARTSYS)/include -I$(ROOTSYS)/include -L$(TARTSYS)/lib -lXMLParser -lanacore

GXX = g++ -std=c++0x

all:$(OBJ)

$(OBJ): $(sourcefile)
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ $(filter %.cxx ,$(sourcefile)) 

clean:
	rm -f *~ *.o $(OBJ)
