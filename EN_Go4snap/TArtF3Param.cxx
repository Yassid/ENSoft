#include "TArtF3Param.h"
#include "Riostream.h"

//***********************************************************

TArtF3Param::TArtF3Param() : TGo4Parameter("F3Parameter"),
fArr()
{
  fFill	  = kTRUE;
  fOutput = kFALSE;
  fOffset = 0;
  fFactor = 1;
  frP1	  = 10;
  frP2	  = 20;
  fbHisto = kTRUE;
  
  /*   fF3UPPAC_X_slope	= 1.255; 
       fF3UPPAC_Y_slope	= 1.263;
       fF3DPPAC_X_slope	= 1.238;
       fF3DPPAC_Y_slope	= 1.237;
       
       fF3UPPAC_X_offset = 0.0;
       fF3UPPAC_Y_offset = 0.0;
       fF3DPPAC_X_offset = 1.18;
       fF3DPPAC_Y_offset = - 2.1;
  */  
 
}
//***********************************************************
TArtF3Param::TArtF3Param(const char* name) : TGo4Parameter(name),
fArr()
{
  fFill	  = kTRUE;
  fOutput = kFALSE;
  fOffset = 0;
  fFactor = 1;
  frP1	  = 10;
  frP2	  = 20;
  fbHisto = kTRUE;
 
  
  /*  fF3UPPAC_X_slope = 1.255; 
   fF3UPPAC_Y_slope    = 1.263;
   fF3DPPAC_X_slope    = 1.238;
   fF3DPPAC_Y_slope    = 1.237;
   fF3UPPAC_X_offset = 0.0;
   fF3UPPAC_Y_offset = 0.0;
   fF3DPPAC_X_offset = 1.18;
   fF3DPPAC_Y_offset = - 2.1;
  */
 
 
}
//***********************************************************
TArtF3Param::~TArtF3Param()
{
}
//***********************************************************

//-----------------------------------------------------------
Int_t TArtF3Param::PrintParameter()
{
  cout << "F3Parameter " << GetName() << ":";
  cout << " fill="     << fFill;
  cout << " output="   << fOutput;
  cout << " offset="   << fOffset;
  cout << " factor="   << fFactor << endl;
  return 0;
}
//-----------------------------------------------------------
Int_t TArtF3Param::PrintParameter(Text_t * n, Int_t)
{
  PrintParameter();
  return 0;
}
//-----------------------------------------------------------
Bool_t TArtF3Param::UpdateFrom(TGo4Parameter *pp)
{
  if(pp->InheritsFrom("TArtF3Param"))
  {
    TArtF3Param *	from;
    from    = (TArtF3Param *) pp;
    cout << "**** TArtF3Param " << GetName() << " updated from auto save file" << endl;
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
