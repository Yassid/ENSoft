  class TArtRawEventObject;
  class TArtRawSegmentObject;
  class EN_PPAC_Cal;
  class ENFiberCal;
//  class TString;
#include "TArtEventStore.hh"
#include "segidlist.h"

  TArtEventStore *estore;
  TArtRawEventObject *rawevent;
  TArtRawSegmentObject *seg; 
  EN_PPAC_Cal *ppac; 
  ENFiberCal *fiber;
  struct mapping{
    int cad;
    int seg;
    int det;
    int mod;
    int ch;
    int hit;
    int edge;
    char name[20];
    float val;
  };
  mapping ENraw[1000];
  int numch,f1fiberFlag,f2ppacFlag,f3ppacFlag;
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

