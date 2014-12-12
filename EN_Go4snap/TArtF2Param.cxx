#include "TArtF2Param.h"
#include "Riostream.h"

//***********************************************************
TArtF2Param::TArtF2Param() : TGo4Parameter("F2Parameter"),
fArr()
{
  fFill	  = kTRUE;
  fOutput = kFALSE;
  fOffset = 0;
  fFactor = 1;
  frP1	  = 10;
  frP2	  = 20;
  fbHisto = kTRUE;
  
  /*   fF2UPPAC_X_slope	= 1.255; 
   fF2UPPAC_Y_slope	= 1.263;
   fF2DPPAC_X_slope	= 1.238;
   fF2DPPAC_Y_slope	= 1.237;

   fF2UPPAC_X_offset = 0.0;
   fF2UPPAC_Y_offset = 0.0;
   fF2DPPAC_X_offset = 1.18;
   fF2DPPAC_Y_offset = - 2.1;*/  
 
}
//***********************************************************
TArtF2Param::TArtF2Param(const char* name) : TGo4Parameter(name),
fArr()
{
  fFill	  = kTRUE;
  fOutput = kFALSE;
  fOffset = 0;
  fFactor = 1;
  frP1	  = 10;
  frP2	  = 20;
  fbHisto = kTRUE;
 
  
  /*  fF2UPPAC_X_slope = 1.255; 
      fF2UPPAC_Y_slope    = 1.263;
      fF2DPPAC_X_slope    = 1.238;
      fF2DPPAC_Y_slope    = 1.237;
      
      fF2UPPAC_X_offset = 0.0;
      fF2UPPAC_Y_offset = 0.0;
      fF2DPPAC_X_offset = 1.18;
      fF2DPPAC_Y_offset = - 2.1; */
 
 
}
//***********************************************************
TArtF2Param::~TArtF2Param()
{
}
//***********************************************************

//-----------------------------------------------------------
Int_t TArtF2Param::PrintParameter()
{
  cout << "F2Parameter " << GetName() << ":";
  cout << " fill="     << fFill;
  cout << " output="   << fOutput;
  cout << " offset="   << fOffset;
  cout << " factor="   << fFactor << endl;
  return 0;
}
//-----------------------------------------------------------
Int_t TArtF2Param::PrintParameter(Text_t * n, Int_t)
{
  PrintParameter();
  return 0;
}
//-----------------------------------------------------------
Bool_t TArtF2Param::UpdateFrom(TGo4Parameter *pp)
{
  if(pp->InheritsFrom("TArtF2Param"))
  {
    TArtF2Param *	from;
    from    = (TArtF2Param *) pp;
    cout << "**** TArtF2Param " << GetName() << " updated from auto save file" << endl;
    fFill   = from->fFill;
    fOutput = from->fOutput;
    fOffset = from->fOffset;
    fFactor = from->fFactor;
    PrintParameter();
  }
     else
     cout << "Wrong parameter object: " << pp->ClassName() << endl;
  return kTRUE;
}

//----------------------------END OF GO4 SOURCE FILE ---------------------
