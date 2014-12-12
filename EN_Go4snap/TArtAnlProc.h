// $Id: TArtAnlProc.h 813 2011-12-02 12:33:40Z linev $
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

#ifndef TArtANLPROCESSOR_H
#define TArtANLPROCESSOR_H

#include "TGo4EventProcessor.h"

#include "TArtSortEvent.h"
#include "TGo4PolyCond.h"

#include "TRandom.h"

class TArtF2Param;
class TArtF3Param;
class TArtAnlEvent;

class TArtAnlProc : public TGo4EventProcessor {
   public:
      TArtAnlProc();
      TArtAnlProc(const char * name);
      virtual ~TArtAnlProc();

      virtual Bool_t BuildEvent(TGo4EventElement* dest);      
      TH1              *TPC_PID_Center[4];
// F2U PPAC
    /*  TH1              *F2_UPPAC_XLT;
      TH1              *F2_UPPAC_YDT; 
      TH1              *F2_UPPAC_XRT;
      TH1              *F2_UPPAC_YUT;
    */  TH1              *F2_UPPAC_XT;
      TH1              *F2_UPPAC_YT;
      TH1              *F2_UPPAC_Xmm;
      TH1              *F2_UPPAC_Ymm;
      TH2              *F2_UPPAC_XYT;
      TH2              *F2_UPPAC_XYmm;

//***************** Yassid E372 ad hoc conditioned histograms  ************************//

	TH2              *F2_UPPAC_XYmm_cond;
        TH2              *F2_DPPAC_XYmm_cond;
	TH2		*F2_PPAC_ZXmm_cond;
	TH2		*F2_PPAC_ZYmm_cond;

	TH2              *F3_UPPAC_XYmm_cond;
        TH2              *F3_DPPAC_XYmm_cond;
	TH2		*F3_PPAC_ZXmm_cond;
	TH2		*F3_PPAC_ZYmm_cond;

/*/ F2D PPAC      
      TH1              *F2_DPPAC_XLT;
      TH1              *F2_DPPAC_YDT; 
      TH1              *F2_DPPAC_XRT;
  */    TH1              *F2_DPPAC_YUT;
      TH1              *F2_DPPAC_XT;
      TH1              *F2_DPPAC_YT;       
      TH1              *F2_DPPAC_Xmm;
      TH1              *F2_DPPAC_Ymm;      
      TH2              *F2_DPPAC_XYT;      
      TH2              *F2_DPPAC_XYmm;
      TH2              *F2_PPAC_ZXmm;      
      TH2              *F2_PPAC_ZYmm;

     // F3U PPAC
    /*  TH1              *F3_UPPAC_XLT;
      TH1              *F3_UPPAC_YDT; 
      TH1              *F3_UPPAC_XRT;
      TH1              *F3_UPPAC_YUT;
    */  TH1              *F3_UPPAC_XT;
      TH1              *F3_UPPAC_YT;
      TH1              *F3_UPPAC_Xmm;
      TH1              *F3_UPPAC_Ymm;
      TH2              *F3_UPPAC_XYT;
      TH2              *F3_UPPAC_XYmm;
/*/ F3D PPAC      
      TH1              *F3_DPPAC_XLT;
      TH1              *F3_DPPAC_YDT; 
      TH1              *F3_DPPAC_XRT;
  */    TH1              *F3_DPPAC_YUT;
      TH1              *F3_DPPAC_XT;
      TH1              *F3_DPPAC_YT;       
      TH1              *F3_DPPAC_Xmm;
      TH1              *F3_DPPAC_Ymm;      
      TH2              *F3_DPPAC_XYT;      
      TH2              *F3_DPPAC_XYmm;
      TH2              *F3_PPAC_ZXmm;      
      TH2              *F3_PPAC_ZYmm;

      // -----------------------------
      
      TH2              *Beam_profile_z[9];
      TH2              *Beam_profile_z_cond[9];
      
      TH2              *Beam_profile_z_cond5[9];
      TH2              *Beam_profile_z_cond6[9];
      TH2              *Beam_profile_z_cond7[9];

      TH1              *F2_Sil_Energy;

      TH1              *F2_Scint_TOF;
      
      TH2              *Beam_trckZX;
      TH2              *Beam_trckZY;
      
      TH2              *PID_RF_Scint_cond;
      TH2              *RF1_F3Si_Anl;
      
      TH1              *RF_Cond;
     
      TArtF2Param      *fF2Param;
      TArtF3Param      *fF3Param; // 28952014 TETSUYA ADD

      TGo4WinCond      *fWinCon;
      
      TGo4PolyCond     *PID_Raw_GATE_Scint;
      TGo4PolyCond     *PID_Raw_GATE_Anl;
      
      TRandom          *randomnum;
      
   

   private:
   
   	TH2* MakeH2I_Profile(const char* foldername, 
				int index);

	TH2* MakeH2I_Profile_cond(const char* foldername, 
				int index, int cond);

        TH2* MakeH2I_TPC_ID(const char* foldername, 
				int index);

   ClassDef(TArtAnlProc, 1)
};
#endif //TArtANLPROCESSOR_H
