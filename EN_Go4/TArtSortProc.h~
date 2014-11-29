// $Id: TArtSortProc.h 813 2011-12-02 12:33:40Z linev $
//-----------------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//-----------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum für Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
//-----------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//-----------------------------------------------------------------------

#ifndef TArtSORTPROCESSOR_H
#define TArtSORTPROCESSOR_H

#include "TGo4EventProcessor.h"
#include "TArtUnpackEvent.h"
#include "TRandom.h"
#include <fstream>

class TArtSortEvent;
class TArtUnpackEvent;
class EN_PPAC_Cal;
class ENFiberCal;
class ENPlastic;
class EN_CsI;
class EN_Neutron;

//class TArtF2Param;
//class TArtF3Param;

class TArtSortProc : public TGo4EventProcessor {
   public:
      TArtSortProc();
      TArtSortProc(const Char_t * name);
      virtual ~TArtSortProc();
      
      virtual Bool_t BuildEvent(TGo4EventElement* dest);

//      TArtF2Param      *fF2Param;
//      TArtF3Param      *fF3Param;

      EN_PPAC_Cal 	*ppac;
      ENFiberCal	*fiber; 
      ENPlastic		*plastic;
      EN_CsI		*csi;
      EN_Neutron	*neutron;	

      TGo4PolyCond      *gate[20];
      TH1 *hExpDet[1000];
 private:
      Int_t analist[10];
      Int_t showrawdata;
      Double_t valnaok[10][10][256];
      Int_t rawdt[10][10][256];

      Int_t V1190refval;
      Int_t ExpNumDets;
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
    	Int_t val;
        TH1* hHist1;
      };
      struct hst2{
        Int_t filled;
        Int_t gate;
    	Int_t anal1;
    	Int_t seg1;
    	Int_t num1;
  	Int_t nbin1;
        Double_t min1;
	Double_t max1;
        Int_t anal2;
    	Int_t seg2;
    	Int_t num2;
  	Int_t nbin2;
        Double_t min2;
	Double_t max2; 
	Char_t folder[20];
	Char_t name[20];
    	Int_t val;
        TH2* hHist2;
      };
      mapping ExpDetRaw[1000];
      hst1 hist1[1000];
      hst2 hist2[1000];
      hst1 gate1[10];
      hst2 gate2[10];
      int nhst1,nhst2,ngate1,ngate2;
      
      Int_t F1_Fiber_MakeHist();
      Int_t F1_Fiber_CalibMakeHist();
      Int_t F1_Fiber_FillHist(TArtUnpackEvent*,TArtSortEvent*);
      Int_t F1_Fiber_Assign(TArtUnpackEvent*,TArtSortEvent*); 

      Int_t BeamLineMakeHist();
      Int_t BeamLineFillHist(TArtSortEvent*);
      Int_t BeamLineAssign(TArtUnpackEvent*,TArtSortEvent*);


      Int_t PPACMakeHist();
      Int_t PPACFillHist(TArtSortEvent*);
      Int_t PPACCalibration(TArtSortEvent*);
      
      Int_t RawDataMakeHist();
      Int_t RawDataFillHist(TArtSortEvent*);
      Int_t RawDataAssign(TArtUnpackEvent*); 
      Int_t MWDC_cal(TArtUnpackEvent*,TArtSortEvent*);
     
      Int_t readParameters(Char_t *filename);
      Int_t readmapfile(Char_t *filename,mapping* map, Int_t& numch);
      Int_t readHist1(Char_t *filename, hst1* map1, Int_t& numch1, hst2* map2, Int_t& numch2,
					hst1* map3, Int_t& numch3, hst2* map4, Int_t& numch4);
      Int_t MakeGate(hst1* gate1, Int_t ng1, hst2* gate2, Int_t ng2);
      Int_t fillHist1(hst1* histo, Int_t numch,hst2* histo2, Int_t numch2);
      Char_t* GetNextLine(Char_t s ='#' );
      Int_t Put2Array(Char_t*, Int_t*,Int_t);
      Int_t Put2Array(Char_t*, Double_t*,Int_t);
      Char_t* ltrim(Char_t*);
      Char_t* rtrim(Char_t*);
      Char_t* trim(Char_t*);
      ifstream fi;
      Char_t mapfile[100];
      Char_t hstfile[100];
      Char_t fiberprmfile[100];
      Char_t ppacprmfile[100];
      ClassDef(TArtSortProc, 1)
	};
#endif //TArtSORTPROCESSOR_H
