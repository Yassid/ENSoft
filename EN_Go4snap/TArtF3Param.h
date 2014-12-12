#ifndef SPARF3_H
#define SPARF3_H

#include	"TGo4Parameter.h"
#include "TArrayI.h"
//#include "TArrayF.h"

class TArtF3Param : public TGo4Parameter {
 public:
  TArtF3Param();
  TArtF3Param(const char* name);
  virtual ~TArtF3Param();
  virtual Int_t		PrintParameter(Text_t * n, Int_t);
      Int_t		PrintParameter();
      virtual Bool_t	UpdateFrom(TGo4Parameter *);

      Bool_t	fFill;		// enable filling histograms 
      Bool_t	fOutput;	// enable filling TArt event
      Float_t	fOffset;	// offset used for unpack
      Float_t	fFactor;	// factor used for unpack
      
      Float_t	frP1;		// Offset for calibration
      Float_t	frP2;		// Factor for Calibration
      Bool_t	fbHisto;	// Enable Histogramming
      
      TArrayI	fArr;		// example of usage of array in the parameter 
   
       // F2U PPAC
       Float_t fF3UPPAC_ch2ns_XL;	 
       Float_t fF3UPPAC_ch2ns_XR;	 
       Float_t fF3UPPAC_ch2ns_YD;	 
       Float_t fF3UPPAC_ch2ns_YU;

       Float_t	fF3UPPAC_ns2mm_X;	 
       Float_t	fF3UPPAC_ns2mm_Y;	 

       Float_t	fF3UPPAC_inoffset_X;	 
       Float_t	fF3UPPAC_inoffset_Y;
       Float_t	fF3UPPAC_outoffset_X;	 
       Float_t	fF3UPPAC_outoffset_Y;
       Float_t	fF3UPPAC_geomoffset_X;	 
       Float_t	fF3UPPAC_geomoffset_Y;
       Float_t	fF3UPPAC_offset_X;	 
       Float_t	fF3UPPAC_offset_Y;
   // F2DPPAC
       Float_t fF3DPPAC_ch2ns_XL;	 
       Float_t fF3DPPAC_ch2ns_XR;	 
       Float_t fF3DPPAC_ch2ns_YD;	 
       Float_t fF3DPPAC_ch2ns_YU;

       Float_t	fF3DPPAC_ns2mm_X;	 
       Float_t	fF3DPPAC_ns2mm_Y;	 

       Float_t	fF3DPPAC_inoffset_X;	 
       Float_t	fF3DPPAC_inoffset_Y;
       Float_t	fF3DPPAC_outoffset_X;	 
       Float_t	fF3DPPAC_outoffset_Y;
       Float_t	fF3DPPAC_geomoffset_X;	 
       Float_t	fF3DPPAC_geomoffset_Y;
       Float_t	fF3DPPAC_offset_X;	 
       Float_t	fF3DPPAC_offset_Y;
        
       Float_t zpos[11];	//Positions

	ClassDef(TArtF3Param,1)
	  };

#endif //SPAR_H

//----------------------------END OF GO4 SOURCE FILE ---------------------
