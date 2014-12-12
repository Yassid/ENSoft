  class TArtRawEventObject;
  class TArtRawSegmentObject;
  class EN_PPAC_Cal;
  class ENFiberCal;
  class ENPlastic;
  class EN_CsI;
  class EN_DSSD;
  class EN_MWDC;
  class EN_Neutron;
  class EN_Coin;class EN_PPAC_Cal;

//  class TString;
#include "TArtEventStore.hh"
#include "segidlist.h"

  TArtEventStore *estore;
  TArtRawEventObject *rawevent;
  TArtRawSegmentObject *seg; 
EN_PPAC_Cal 	*ppac;
      ENFiberCal	*fiber; 
      ENPlastic		*plastic;
      EN_CsI		*csi;
      EN_DSSD		*dssd;	
      EN_Neutron	*neutron;
      EN_MWDC		*mwdc;	
	EN_Coin		*coin;

  struct mapping{
        Int_t filled;
    	Int_t cad;
        Int_t aid;
	Int_t pos;
    	Int_t seg;
    	Int_t det;
    	Int_t mod;
    	Int_t nch;
	Int_t ch;
    	Int_t hit;
    	Int_t edge;
    	Char_t name[20];
        Char_t namech[20];
    	Int_t val;
  };
  struct hst1{
        Int_t filled;
        Int_t gate;
    	Int_t anal;
    	Int_t seg;
    	Int_t num;
  	Int_t nbin;
        Double_t min;
	Double_t max;
	Char_t folder[20];
	Char_t name[20];
    	Double_t val;
        TH1* hHist1;
      };
  mapping ExpDetRaw[5000];
  hst1 hist1[5000];
  Int_t rawdt[10][10][256];
  Double_t valnaok[10][10][256];
int nhst1,ExpNumDets,analist[11],showrawdata;
  int f1fiber_ch,f2ppac_ch,f3ppac_ch;
  ifstream fi;  
  string	rawpath;
  char	runname[20];   
  string	rootpath;
  string       txtpath;
  int txtsaveflag;
  int rootsaveflag;
  int rootonefile;
  int nevt;
  int nmaxevt;
  
  float F1Fiber_X,F1Fiber_Y,F1Fiber_W;
  float F2UPPAC_X,F2UPPAC_Y;
  float F2DPPAC_X,F2DPPAC_Y;
  float F3UPPAC_X,F3UPPAC_Y;
  float F3DPPAC_X,F3DPPAC_Y;

