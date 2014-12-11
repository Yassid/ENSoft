// $Id: TArtAnlProc.cxx 933 2013-01-29 15:27:58Z linev $
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

#include "TArtAnlProc.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"

#include "TGo4WinCond.h"
#include "TGo4Analysis.h"

#include "TArtAnlEvent.h"
#include "TArtSortEvent.h"
#include "TArtF2Param.h"
#include "TArtF3Param.h"

//-----------------------------------------------------------
TArtAnlProc::TArtAnlProc() :
   TGo4EventProcessor(),
   fF2Param(0),fF3Param(0), fWinCon(0),PID_Raw_GATE_Scint(0) // TETSUYA ADD 28052014
{
}

//-----------------------------------------------------------
TArtAnlProc::TArtAnlProc(const char* name) :
   TGo4EventProcessor(name),
   fF2Param(0),fF3Param(0), fWinCon(0),PID_Raw_GATE_Scint(0) // TETSUYA ADD 28052014
{
   TGo4Log::Info("TArtAnlProc: Create");
   
   // Yassid 11092013 Add parameters
   //   for calibration of detectors only in this step

   //// init user analysis objects:
   // create and load parameter here
   // set_Par.C macro executed after parameter load from auto-save file

   fF2Param = (TArtF2Param*)
     MakeParameter("F2Param","TArtF2Param","set_F2Par.C");

   // 28052014 TETSUYA ADD
   fF3Param = (TArtF3Param*) 
     MakeParameter("F3Param","TArtF3Param","set_F3Par.C");
   //------------------------------------
 
   // this one is created in TArtAnalysis, because it is used in both steps
   fWinCon = (TGo4WinCond *) GetAnalysisCondition("wincon1", "TGo4WinCond");
   if (fWinCon) fWinCon->PrintCondition(true);
	srand(1000);
/*/	F2_UPPAC_XLT = MakeTH1('I', "Calibration/F2/F2UPPAC_XL_ns", "F2UPPAC XL in ns", 1000, -100., 100.);
//      	F2_UPPAC_YDT = MakeTH1('I', "Calibration/F2/F2UPPAC_YD_ns", "F2UPPAC YD in ns", 1000, -100., 100.); 
//        F2_UPPAC_XRT = MakeTH1('I', "Calibration/F2/F2UPPAC_XR_ns", "F2UPPAC XR in ns", 1000, -100., 100.);
 //     	F2_UPPAC_YUT = MakeTH1('I', "Calibration/F2/F2UPPAC_YU_ns", "F2UPPAC YU in ns", 1000, -100., 100.);
//        F2_UPPAC_XT  = MakeTH1('I', "Calibration/F2/F2UPPAC_X_ns", "F2UPPAC X in ns", 1000, -100., 100.);
//        F2_UPPAC_YT  = MakeTH1('I', "Calibration/F2/F2UPPAC_Y_ns", "F2UPPAC Y in ns", 1000, -100., 100.);
//        F2_UPPAC_Xmm = MakeTH1('I', "Calibration/F2/F2UPPAC_X_mm", "F2UPPAC X in mm", 1000, -60., 60.);
//        F2_UPPAC_Ymm = MakeTH1('I', "Calibration/F2/F2UPPAC_Y_mm", "F2UPPAC Y in mm", 1000, -60., 60.);

//        F2_UPPAC_XYT = MakeTH2('I', "Calibration/F2/F2UPPAC_XY_ns", "F2UPPAC Postion Calibrated in ns", 1000, -100., 100., 1000, -100., 100.);      	
//	F2_UPPAC_XYT->GetXaxis()->SetTitle("X Position (ns)");
//    	F2_UPPAC_XYT->GetYaxis()->SetTitle("Y Position (ns)");
*/

		//*****************************Yassid N.B.: We move all histograms to E372 Go4 Folder 21062014 ***************************************//

        F2_UPPAC_XYmm = MakeTH2('I', "E372/F2PPAC/F2UPPAC_XY_mm", "F2UPPAC Postion Calibrated in mm", 1000, -160., 160., 1000, -160., 160.);      	
	F2_UPPAC_XYmm->GetXaxis()->SetTitle("X Position (mm)");
    	F2_UPPAC_XYmm->GetYaxis()->SetTitle("Y Position (mm)");


	F2_UPPAC_XYmm_cond = MakeTH2('I', "E372/F2PPAC/F2UPPAC_XY_mm_cond", "F2UPPAC Postion Calibrated in mm conditioned", 1000, -60., 60., 1000, -60., 60.);      	
	F2_UPPAC_XYmm_cond->GetXaxis()->SetTitle("X Position (mm)");
    	F2_UPPAC_XYmm_cond->GetYaxis()->SetTitle("Y Position (mm)");

/*
        F2_DPPAC_XLT = MakeTH1('I', "Calibration/F2/F2DPPAC_XL_ns", "F2DPPAC XL in ns", 1000, -100., 100.);
      	F2_DPPAC_YDT = MakeTH1('I', "Calibration/F2/F2DPPAC_YD_ns", "F2DPPAC YD in ns", 1000, -100., 100.); 
        F2_DPPAC_XRT = MakeTH1('I', "Calibration/F2/F2DPPAC_XR_ns", "F2DPPAC XR in ns", 1000, -100., 100.);
      	F2_DPPAC_YUT = MakeTH1('I', "Calibration/F2/F2DPPAC_YU_ns", "F2DPPAC YU in ns", 1000, -500, 1500.);
        F2_DPPAC_XT  = MakeTH1('I', "Calibration/F2/F2DPPAC_X_ns", "F2DPPAC X in ns", 1000, -100., 100.);
        F2_DPPAC_YT  = MakeTH1('I', "Calibration/F2/F2DPPAC_Y_ns", "F2DPPAC Y in ns", 1000, -100., 100.);
        F2_DPPAC_Xmm = MakeTH1('I', "Calibration/F2/F2DPPAC_X_mm", "F2DPPAC X in mm", 1000, -60., 60.);
        F2_DPPAC_Ymm = MakeTH1('I', "Calibration/F2/F2DPPAC_Y_mm", "F2DPPAC Y in mm", 1000, -60., 60.);

        F2_DPPAC_XYT = MakeTH2('I', "Calibration/F2/F2DPPAC_XY_ns", "F2DPPAC Postion Calibrated in ns", 1000, -100., 100., 1000, -100., 100.);      	
	F2_DPPAC_XYT->GetXaxis()->SetTitle("X Position (ns)");
    	F2_DPPAC_XYT->GetYaxis()->SetTitle("Y Position (ns)");
*/
        F2_DPPAC_XYmm = MakeTH2('I', "E372/F2PPAC/F2DPPAC_XY_mm", "F2DPPAC Postion Calibrated in mm", 1000, -60., 60., 1000, -60., 60.);      	
	F2_DPPAC_XYmm->GetXaxis()->SetTitle("X Position (mm)");
    	F2_DPPAC_XYmm->GetYaxis()->SetTitle("Y Position (mm)");


	F2_DPPAC_XYmm_cond = MakeTH2('I', "E372/F2PPAC/F2DPPAC_XY_mm_cond", "F2DPPAC Postion Calibrated in mm conditioned", 1000, -60., 60., 1000, -60., 60.);      	
	F2_DPPAC_XYmm_cond->GetXaxis()->SetTitle("X Position (mm)");
    	F2_DPPAC_XYmm_cond->GetYaxis()->SetTitle("Y Position (mm)");
        
        F2_PPAC_ZXmm = MakeTH2('I', "E372/F2PPAC/F2PPAC_ZX_mm", "F2PPAC Postion extrapolation", 1000, -500., 1500., 1000, -100., 100.);      	
	F2_PPAC_ZXmm->GetXaxis()->SetTitle("Z Position (mm)");
    	F2_PPAC_ZXmm->GetYaxis()->SetTitle("X Position (mm)");
	F2_PPAC_ZYmm = MakeTH2('I', "E372/F2PPAC/F2PPAC_ZY_mm", "F2PPAC Postion extrapolation", 1000, -500., 1500., 1000, -100., 100.);      	
	F2_PPAC_ZYmm->GetXaxis()->SetTitle("Z Position (mm)");
    	F2_PPAC_ZYmm->GetYaxis()->SetTitle("Y Position (mm)");


	F2_PPAC_ZXmm_cond = MakeTH2('I', "E372/F2PPAC/F2PPAC_ZX_mm_cond", "F2PPAC Postion extrapolation conditioned", 1000, -500., 1500., 1000, -100., 100.);      	
	F2_PPAC_ZXmm_cond->GetXaxis()->SetTitle("Z Position (mm)");
    	F2_PPAC_ZXmm_cond->GetYaxis()->SetTitle("X Position (mm)");
	F2_PPAC_ZYmm_cond = MakeTH2('I', "E372/F2PPAC/F2PPAC_ZY_mm_cond", "F2PPAC Postion extrapolation conditioned", 1000, -500., 1500., 1000, -100., 100.);      	
	F2_PPAC_ZYmm_cond->GetXaxis()->SetTitle("Z Position (mm)");
    	F2_PPAC_ZYmm_cond->GetYaxis()->SetTitle("Y Position (mm)");

    // 28052014 TETSUYA ADD   
    //	F3_UPPAC_XLT = MakeTH1('I', "Calibration/F2/F2UPPAC_XL_ns", "F2UPPAC XL in ns", 1000, -100., 100.);
//      	F2_UPPAC_YDT = MakeTH1('I', "Calibration/F2/F2UPPAC_YD_ns", "F2UPPAC YD in ns", 1000, -100., 100.); 
//        F3_UPPAC_XRT = MakeTH1('I', "Calibration/F2/F2UPPAC_XR_ns", "F2UPPAC XR in ns", 1000, -100., 100.);
 //     	F3_UPPAC_YUT = MakeTH1('I', "Calibration/F2/F2UPPAC_YU_ns", "F2UPPAC YU in ns", 1000, -100., 100.);
/*        F3_UPPAC_XT  = MakeTH1('I', "Calibration/F3/F3UPPAC_X_ns", "F3UPPAC X in ns", 1000, -100., 100.);
        F3_UPPAC_YT  = MakeTH1('I', "Calibration/F3/F3UPPAC_Y_ns", "F3UPPAC Y in ns", 1000, -100., 100.);
        F3_UPPAC_Xmm = MakeTH1('I', "Calibration/F3/F3UPPAC_X_mm", "F3UPPAC X in mm", 1000, -100., 100.);
        F3_UPPAC_Ymm = MakeTH1('I', "Calibration/F3/F3UPPAC_Y_mm", "F3UPPAC Y in mm", 1000, -100., 100.);

        F3_UPPAC_XYT = MakeTH2('I', "Calibration/F3/F3UPPAC_XY_ns", "F3UPPAC Postion Calibrated in ns", 1000, -100., 100., 1000, -100., 100.);      	
	F3_UPPAC_XYT->GetXaxis()->SetTitle("X Position (ns)");
    	F3_UPPAC_XYT->GetYaxis()->SetTitle("Y Position (ns)");
*/
        F3_UPPAC_XYmm = MakeTH2('I', "E372/F3PPAC/F3UPPAC_XY_mm", "F3UPPAC Postion Calibrated in mm", 1000, -100., 100., 1000, -100., 100.);      	
	F3_UPPAC_XYmm->GetXaxis()->SetTitle("X Position (mm)");
    	F3_UPPAC_XYmm->GetYaxis()->SetTitle("Y Position (mm)");

	F3_UPPAC_XYmm_cond = MakeTH2('I', "E372/F3PPAC/F3UPPAC_XY_mm_cond", "F3UPPAC Postion Calibrated in mm conditioned", 1000, -100., 100., 1000, -100., 100.);      	
	F3_UPPAC_XYmm_cond->GetXaxis()->SetTitle("X Position (mm)");
    	F3_UPPAC_XYmm_cond->GetYaxis()->SetTitle("Y Position (mm)");


    //    F3_DPPAC_XLT = MakeTH1('I', "Calibration/F2/F2DPPAC_XL_ns", "F2DPPAC XL in ns", 1000, -100., 100.);
    //  	F3_DPPAC_YDT = MakeTH1('I', "Calibration/F2/F2DPPAC_YD_ns", "F2DPPAC YD in ns", 1000, -100., 100.); 
    /*/    F3_DPPAC_XRT = MakeTH1('I', "Calibration/F2/F2DPPAC_XR_ns", "F2DPPAC XR in ns", 1000, -100., 100.);
      	F3_DPPAC_YUT = MakeTH1('I', "Calibration/F3/F3DPPAC_YU_ns", "F3DPPAC YU in ns", 1000, -500, 1500.);
        F3_DPPAC_XT  = MakeTH1('I', "Calibration/F3/F3DPPAC_X_ns", "F3DPPAC X in ns", 1000, -100., 100.);
        F3_DPPAC_YT  = MakeTH1('I', "Calibration/F3/F3DPPAC_Y_ns", "F3DPPAC Y in ns", 1000, -100., 100.);
        F3_DPPAC_Xmm = MakeTH1('I', "Calibration/F3/F3DPPAC_X_mm", "F3DPPAC X in mm", 1000, -100., 100.);
        F3_DPPAC_Ymm = MakeTH1('I', "Calibration/F3/F3DPPAC_Y_mm", "F3DPPAC Y in mm", 1000, -100., 100.);

        F3_DPPAC_XYT = MakeTH2('I', "Calibration/F3/F3DPPAC_XY_ns", "F3DPPAC Postion Calibrated in ns", 1000, -100., 100., 1000, -100., 100.);      	
	F3_DPPAC_XYT->GetXaxis()->SetTitle("X Position (ns)");
    	F3_DPPAC_XYT->GetYaxis()->SetTitle("Y Position (ns)");
*/
        F3_DPPAC_XYmm = MakeTH2('I', "E372/F3PPAC/F3DPPAC_XY_mm", "F3DPPAC Postion Calibrated in mm", 1000, -100., 100., 1000, -100., 100.);      	
	F3_DPPAC_XYmm->GetXaxis()->SetTitle("X Position (mm)");
    	F3_DPPAC_XYmm->GetYaxis()->SetTitle("Y Position (mm)");

	F3_DPPAC_XYmm_cond = MakeTH2('I', "E372/F3PPAC/F3DPPAC_XY_mm_cond", "F3DPPAC Postion Calibrated in mm conditioned", 1000, -100., 100., 1000, -100., 100.);      	
	F3_DPPAC_XYmm_cond->GetXaxis()->SetTitle("X Position (mm)");
    	F3_DPPAC_XYmm_cond->GetYaxis()->SetTitle("Y Position (mm)");

        
        F3_PPAC_ZXmm = MakeTH2('I', "E372/F3PPAC/F3PPAC_ZX_mm", "F3PPAC Postion extrapolation", 1000, -500., 2000., 1000, -100., 100.);      	
	F3_PPAC_ZXmm->GetXaxis()->SetTitle("Z Position (mm)");
    	F3_PPAC_ZXmm->GetYaxis()->SetTitle("X Position (mm)");
	F3_PPAC_ZYmm = MakeTH2('I', "E372/F3PPAC/F3PPAC_ZY_mm", "F3PPAC Postion extrapolation", 1000, -500., 2000., 1000, -100., 100.);      	
	F3_PPAC_ZYmm->GetXaxis()->SetTitle("Z Position (mm)");
    	F3_PPAC_ZYmm->GetYaxis()->SetTitle("Y Position (mm)");

	   
        F3_PPAC_ZXmm_cond = MakeTH2('I', "E372/F3PPAC/F3PPAC_ZX_mm_cond", "F3PPAC Postion extrapolation conditioned", 1000, -500., 2000., 1000, -100., 100.);      	
	F3_PPAC_ZXmm_cond->GetXaxis()->SetTitle("Z Position (mm)");
    	F3_PPAC_ZXmm_cond->GetYaxis()->SetTitle("X Position (mm)");
	F3_PPAC_ZYmm_cond = MakeTH2('I', "E372/F3PPAC/F3PPAC_ZY_mm_cond", "F3PPAC Postion extrapolation conditioned", 1000, -500., 2000., 1000, -100., 100.);      	
	F3_PPAC_ZYmm_cond->GetXaxis()->SetTitle("Z Position (mm)");
    	F3_PPAC_ZYmm_cond->GetYaxis()->SetTitle("Y Position (mm)");



    //------------------------------------

	RF1_F3Si_Anl = MakeTH2('I', "E372/PID/RF1_F3Si_Anl","RF1_F3Si_PID_Anl",1000, -1500., 2500.,1000,1., 100.);

	Double_t pidpanl[4][2]={{646,22},{848,21},{848,14},{646,14}};
      
        PID_Raw_GATE_Anl = MakePolyCond("PID_Raw_Gate_Anl",4,pidpanl,"RF1_F3Si_Anl");
   
    // Yassid 061013 These guys are not working currently (Segmentation violation) TODO Fix later
    
    //Beam_trckZX = MakeTH2('I', "Calibration/Beam_trackingZX", "Beam tracking ZX",  100, 0., 5000., 100, 0., 5000.);
    //Beam_trckZY = MakeTH2('I', "Calibration/Beam_trackingZY", "Beam tracking ZY",  100, 0., 5000., 100, 0., 5000.);
   
//    PID_RF_Scint_cond = MakeTH2('I', "Calibration/PID/F2_PID_HODOCond", "PID RF v1190 - Scint HODO Cond",100, 1., 4096., 100, 1., 4096.);
   
//    RF_Cond = MakeTH1('I', "Calibration/F2/F2_RaF_Cond", "F2_Radiofrequency_Cond", 500, 1., 50000.);
    
    //char fullnameBeamZ[100];
    //char histonameBeamZ[100];
    
    
    for(int i=0;i<9;i++){
    
    Beam_profile_z[i] = MakeH2I_Profile("E372/Beam_Profiles",i);
    Beam_profile_z_cond[i] = MakeH2I_Profile_cond("E372/Beam_Profiles_Cond_All",i,10);
    //Beam_profile_z_cond5[i] = MakeH2I_Profile_cond("Calibration/Beam_Profiles_Cond_05",i,5);
    //Beam_profile_z_cond6[i] = MakeH2I_Profile_cond("Calibration/Beam_Profiles_Cond_06",i,6);
    //Beam_profile_z_cond7[i] = MakeH2I_Profile_cond("Calibration/Beam_Profiles_Cond_07",i,7);
    
    }
    
    


}
//-----------------------------------------------------------
TArtAnlProc::~TArtAnlProc()
{
  TGo4Log::Info("TArtAnlProc: Delete");
   if (fWinCon) fWinCon->PrintCondition(true);
 
}
//-----------------------------------------------------------
Bool_t TArtAnlProc::BuildEvent(TGo4EventElement* dest)
{
   Bool_t isValid=kFALSE; // validity of output event

   TArtSortEvent* inp_evt  = (TArtSortEvent*) GetInputEvent();
   TArtAnlEvent* out_evt = (TArtAnlEvent*) dest;

   // see comments in UnpackProc
   if((inp_evt==0) || !inp_evt->IsValid()){ // input invalid
      out_evt->SetValid(isValid); // invalid
      return isValid; // must be same is for SetValid
   }
   isValid=kTRUE;

 //  Int_t cnt(0);
   
   //cout<<"TEST:"<<inp_evt->ELl<<":"<<inp_evt->ElossmaxXL<<endl;

////////////////// PPACs /////////////////////
// channels to ns
   //cout<<"AnalProc   "<<inp_evt-> F2UPPAC_R<<endl;
   out_evt-> F2UPPAC_Xns = (fF2Param->fF2UPPAC_ch2ns_XL*inp_evt-> F2UPPAC_L) - (fF2Param->fF2UPPAC_ch2ns_XR*inp_evt-> F2UPPAC_R );   
   out_evt-> F2UPPAC_Yns = (fF2Param->fF2UPPAC_ch2ns_YD*inp_evt-> F2UPPAC_D) - (fF2Param->fF2UPPAC_ch2ns_YU*inp_evt-> F2UPPAC_U );

   out_evt-> F2DPPAC_Xns = (fF2Param->fF2DPPAC_ch2ns_XL*inp_evt-> F2DPPAC_L) - (fF2Param->fF2DPPAC_ch2ns_XR*inp_evt-> F2DPPAC_R );
   out_evt-> F2DPPAC_Yns = (fF2Param->fF2DPPAC_ch2ns_YD*inp_evt-> F2DPPAC_D) - (fF2Param->fF2DPPAC_ch2ns_YU*inp_evt-> F2DPPAC_U );	

   out_evt-> F3UPPAC_Xns = (fF3Param->fF3UPPAC_ch2ns_XL*inp_evt-> F3UPPAC_L) - (fF3Param->fF3UPPAC_ch2ns_XR*inp_evt-> F3UPPAC_R );   
   out_evt-> F3UPPAC_Yns = (fF3Param->fF3UPPAC_ch2ns_YD*inp_evt-> F3UPPAC_D) - (fF3Param->fF3UPPAC_ch2ns_YU*inp_evt-> F3DPPAC_U );

   out_evt-> F3DPPAC_Xns = (fF3Param->fF3DPPAC_ch2ns_XL*inp_evt-> F3DPPAC_L) - (fF2Param->fF2DPPAC_ch2ns_XR*inp_evt-> F3DPPAC_R );
   out_evt-> F3DPPAC_Yns = (fF3Param->fF3DPPAC_ch2ns_YD*inp_evt-> F3DPPAC_D) - (fF2Param->fF2DPPAC_ch2ns_YU*inp_evt-> F3DPPAC_U );
 // ns to mm
  if (inp_evt-> F2UPPAC_L>0 and inp_evt-> F2UPPAC_R>0) 
  	out_evt-> F2UPPAC_Xmm = (out_evt-> F2UPPAC_Xns*fF2Param->fF2UPPAC_ns2mm_X) - fF2Param->fF2UPPAC_offset_X;
  if (inp_evt-> F2UPPAC_D>0 and inp_evt-> F2UPPAC_U>0)
  	out_evt-> F2UPPAC_Ymm = (out_evt-> F2UPPAC_Yns*fF2Param->fF2UPPAC_ns2mm_Y) - fF2Param->fF2UPPAC_offset_Y;
  if (inp_evt-> F2DPPAC_L>0 and inp_evt-> F2DPPAC_R>0)
	  out_evt-> F2DPPAC_Xmm = (out_evt-> F2DPPAC_Xns*fF2Param->fF2DPPAC_ns2mm_X) - fF2Param->fF2DPPAC_offset_X;
  if (inp_evt-> F2UPPAC_D>0 and inp_evt-> F2UPPAC_U>0)
	  out_evt-> F2DPPAC_Ymm = (out_evt-> F2DPPAC_Yns*fF2Param->fF2DPPAC_ns2mm_Y) - fF2Param->fF2DPPAC_offset_Y;
  if (inp_evt-> F3UPPAC_L>0 and inp_evt-> F3UPPAC_R>0)
  	out_evt-> F3UPPAC_Xmm = (out_evt-> F3UPPAC_Xns*fF3Param->fF3UPPAC_ns2mm_X) - fF3Param->fF3UPPAC_offset_X;
  if (inp_evt-> F3UPPAC_D>0 and inp_evt-> F3UPPAC_U>0)
	  out_evt-> F3UPPAC_Ymm = (out_evt-> F3UPPAC_Yns*fF3Param->fF3UPPAC_ns2mm_Y) - fF3Param->fF3UPPAC_offset_Y;
  if (inp_evt-> F3DPPAC_L>0 and inp_evt-> F3DPPAC_R>0)
	  out_evt-> F3DPPAC_Xmm = (out_evt-> F3DPPAC_Xns*fF3Param->fF3DPPAC_ns2mm_X) - fF3Param->fF3DPPAC_offset_X;
  if (inp_evt-> F3DPPAC_U>0 and inp_evt-> F3DPPAC_D>0)
	  out_evt-> F3DPPAC_Ymm = (out_evt-> F3DPPAC_Yns*fF3Param->fF3DPPAC_ns2mm_Y) - fF3Param->fF3DPPAC_offset_Y;

// Position calibration of PPACS Yassid 10092013
   
  // if (inp_evt-> F2UPPAC_L>0 and inp_evt-> F2UPPAC_R>0) F2_UPPAC_XT ->Fill( out_evt-> F2UPPAC_Xns);   
  // if (inp_evt-> F2UPPAC_D>0 and inp_evt-> F2UPPAC_U>0) F2_UPPAC_YT ->Fill( out_evt-> F2UPPAC_Yns);   

 // if ((inp_evt-> F2UPPAC_L>0 and inp_evt-> F2UPPAC_R>0) and     
  //     (inp_evt-> F2UPPAC_D>0 and inp_evt-> F2UPPAC_U>0)) F2_UPPAC_XYT->Fill( out_evt-> F2UPPAC_Xns, out_evt-> F2UPPAC_Yns );

 //  if (inp_evt-> F2UPPAC_L>0 and inp_evt-> F2UPPAC_R>0) F2_UPPAC_Xmm ->Fill( out_evt-> F2UPPAC_Xmm);     
 //  if (inp_evt-> F2UPPAC_D>0 and inp_evt-> F2UPPAC_U>0) F2_UPPAC_Ymm ->Fill( out_evt-> F2UPPAC_Ymm);
   
   if(inp_evt->F2UPPAC_L>0 && inp_evt->F2UPPAC_R>0 && inp_evt-> F2UPPAC_U>0 &&  inp_evt-> F2UPPAC_D>0)
      F2_UPPAC_XYmm->Fill(out_evt-> F2UPPAC_Xmm,out_evt-> F2UPPAC_Ymm);

  // if (inp_evt-> F2DPPAC_L>0 and inp_evt-> F2DPPAC_R>0) F2_DPPAC_XT ->Fill( out_evt-> F2DPPAC_Xns);     
  // if (inp_evt-> F2DPPAC_D>0 and inp_evt-> F2DPPAC_U>0) F2_DPPAC_YT ->Fill( out_evt-> F2DPPAC_Yns);

  // if ((inp_evt-> F2DPPAC_L>0 and inp_evt-> F2DPPAC_R>0) and 
   //    (inp_evt-> F2DPPAC_D>0 and inp_evt-> F2DPPAC_U>0)) F2_DPPAC_XYT->Fill( out_evt-> F2DPPAC_Xns, out_evt-> F2DPPAC_Yns );

 //  if (inp_evt-> F2DPPAC_L>0 and inp_evt-> F2DPPAC_R>0) F2_DPPAC_Xmm ->Fill( out_evt-> F2DPPAC_Xmm);
  // if (inp_evt-> F2DPPAC_D>0 and inp_evt-> F2DPPAC_U>0) F2_DPPAC_Ymm ->Fill( out_evt-> F2DPPAC_Ymm);

    if(inp_evt->F2DPPAC_L>0 && inp_evt->F2DPPAC_R>0 && inp_evt-> F2DPPAC_U>0 &&  inp_evt-> F2DPPAC_D>0)
    F2_DPPAC_XYmm->Fill(out_evt-> F2DPPAC_Xmm,out_evt-> F2DPPAC_Ymm);
/*/------ See beam
        out_evt-> F2UPPAC_Xmm=-25+50.0* rand()/RAND_MAX;
        out_evt-> F2DPPAC_Xmm=-25+50.0* rand()/RAND_MAX;
        out_evt-> F2UPPAC_Ymm=-25+50.0* rand()/RAND_MAX;
        out_evt-> F2DPPAC_Ymm=-25+50.0* rand()/RAND_MAX;
*/   
     if (out_evt->F2UPPAC_Xmm>-900 and out_evt->F2UPPAC_Ymm>-900 and 
         out_evt->F2DPPAC_Xmm>-900 and out_evt->F2DPPAC_Ymm>-900) {
      for (int i=1;i<100;++i) {
        out_evt->dr = -500 + 2000.0*rand()/RAND_MAX;        
        F2_PPAC_ZXmm ->Fill(out_evt->dr, 
                       out_evt-> F2UPPAC_Xmm + (out_evt-> F2DPPAC_Xmm - out_evt-> F2UPPAC_Xmm)*(out_evt->dr-fF2Param->zpos[0])/(fF2Param->zpos[1]-fF2Param->zpos[0]));
        F2_PPAC_ZYmm ->Fill(out_evt->dr, 
                       out_evt-> F2UPPAC_Ymm + (out_evt-> F2DPPAC_Ymm - out_evt-> F2UPPAC_Ymm)*(out_evt->dr-fF2Param->zpos[0])/(fF2Param->zpos[1]-fF2Param->zpos[0]));
       // F2_DPPAC_YUT->Fill(out_evt->dr);
        
        out_evt-> Beam_prof_x [8]= out_evt-> F2UPPAC_Xmm + ((out_evt-> F2DPPAC_Xmm-out_evt-> F2UPPAC_Xmm)*(fF2Param->zpos[4] -
		fF2Param->zpos[0]))/(fF2Param->zpos[1]-fF2Param->zpos[0]);		
	
	out_evt-> Beam_prof_y [8]= out_evt-> F2UPPAC_Ymm + 
		((out_evt-> F2DPPAC_Ymm-out_evt-> F2UPPAC_Ymm)*(fF2Param->zpos[4] -
		  fF2Param->zpos[0]))/(fF2Param->zpos[1]-fF2Param->zpos[0]);	
	
	Beam_profile_z[8]->Fill(out_evt-> Beam_prof_x [8],out_evt-> Beam_prof_y [8]);	
    }
    }
        out_evt->dr = -50 + 100.0*rand()/RAND_MAX;        
        F2_PPAC_ZXmm ->Fill(fF2Param->zpos[0],out_evt->dr);
        F2_PPAC_ZYmm ->Fill(fF2Param->zpos[0],out_evt->dr);
        F2_PPAC_ZXmm ->Fill(fF2Param->zpos[1],out_evt->dr);
        F2_PPAC_ZYmm ->Fill(fF2Param->zpos[1],out_evt->dr);
        F2_PPAC_ZXmm ->Fill(fF2Param->zpos[4],out_evt->dr);
        F2_PPAC_ZYmm ->Fill(fF2Param->zpos[4],out_evt->dr);  
     

   // 28052014 TETSUYA ADD
  // Position calibration of PPACS Yassid 10092013
   
  // if (inp_evt-> F3UPPAC_L>0 and inp_evt-> F3UPPAC_R>0) F3_UPPAC_XT ->Fill( out_evt-> F3UPPAC_Xns);     
  // if (inp_evt-> F3UPPAC_D>0 and inp_evt-> F3UPPAC_U>0) F3_UPPAC_YT ->Fill( out_evt-> F3UPPAC_Yns);

  // if ((inp_evt-> F3UPPAC_L>0 and inp_evt-> F3UPPAC_R>0) and     
  //     (inp_evt-> F3UPPAC_D>0 and inp_evt-> F3UPPAC_U>0)) F3_UPPAC_XYT->Fill( out_evt-> F3UPPAC_Xns, out_evt-> F3UPPAC_Yns );

  // if (inp_evt-> F3UPPAC_L>0 and inp_evt-> F3UPPAC_R>0) F3_UPPAC_Xmm ->Fill( out_evt-> F3UPPAC_Xmm);     
  // if (inp_evt-> F3UPPAC_D>0 and inp_evt-> F3UPPAC_U>0) F3_UPPAC_Ymm ->Fill( out_evt-> F3UPPAC_Ymm);
   
   if(inp_evt->F3UPPAC_L>0 && inp_evt->F3UPPAC_R>0 && inp_evt-> F3UPPAC_U>0 &&  inp_evt-> F3UPPAC_D>0)
      F3_UPPAC_XYmm->Fill(out_evt-> F3UPPAC_Xmm,out_evt-> F3UPPAC_Ymm);

  // if (inp_evt-> F3DPPAC_L>0 and inp_evt-> F3DPPAC_R>0) F3_DPPAC_XT ->Fill( out_evt-> F3DPPAC_Xns);     
  // if (inp_evt-> F3DPPAC_D>0 and inp_evt-> F3DPPAC_U>0) F3_DPPAC_YT ->Fill( out_evt-> F3DPPAC_Yns);

  // if ((inp_evt-> F3DPPAC_L>0 and inp_evt-> F3DPPAC_R>0) and 
  //     (inp_evt-> F3DPPAC_D>0 and inp_evt-> F3DPPAC_U>0)) F3_DPPAC_XYT->Fill( out_evt-> F3DPPAC_Xns, out_evt-> F3DPPAC_Yns );

 //  if (inp_evt-> F3DPPAC_L>0 and inp_evt-> F3DPPAC_R>0) F3_DPPAC_Xmm ->Fill( out_evt-> F3DPPAC_Xmm);
 //  if (inp_evt-> F3DPPAC_D>0 and inp_evt-> F3DPPAC_U>0) F3_DPPAC_Ymm ->Fill( out_evt-> F3DPPAC_Ymm);

    if(inp_evt->F3DPPAC_L>0 && inp_evt->F3DPPAC_R>0 && inp_evt-> F3DPPAC_U>0 &&  inp_evt-> F3DPPAC_D>0)
    F3_DPPAC_XYmm->Fill(out_evt-> F3DPPAC_Xmm,out_evt-> F3DPPAC_Ymm);
/*/------ See beam
        out_evt-> F3UPPAC_Xmm=-25+50.0* rand()/RAND_MAX;
        out_evt-> F3DPPAC_Xmm=-25+50.0* rand()/RAND_MAX;
        out_evt-> F3UPPAC_Ymm=-25+50.0* rand()/RAND_MAX;
        out_evt-> F3DPPAC_Ymm=-25+50.0* rand()/RAND_MAX;
/*/
      if (out_evt->F3UPPAC_Xmm>-900 and out_evt->F3UPPAC_Ymm>-900 and out_evt->F3DPPAC_Xmm>-900 and out_evt->F3DPPAC_Ymm>-900) { 
       for (int i=1;i<100;++i) {
        out_evt->dr = -500 + 2500.0*rand()/RAND_MAX;        
        F3_PPAC_ZXmm ->Fill(out_evt->dr, 
                       out_evt-> F3UPPAC_Xmm + (out_evt-> F3DPPAC_Xmm - out_evt-> F3UPPAC_Xmm)*(out_evt->dr-fF3Param->zpos[0])/(fF3Param->zpos[1]-fF3Param->zpos[0]));
        F3_PPAC_ZYmm ->Fill(out_evt->dr, 
                       out_evt-> F3UPPAC_Ymm + (out_evt-> F3DPPAC_Ymm - out_evt-> F3UPPAC_Ymm)*(out_evt->dr-fF3Param->zpos[0])/(fF3Param->zpos[1]-fF3Param->zpos[0]));
       /* F3_DPPAC_YUT->Fill(out_evt->dr);*/ 
        }
       for(int i=0;i<8;i++){
	out_evt-> Beam_prof_x [i]= out_evt-> F3UPPAC_Xmm + ((out_evt-> F3DPPAC_Xmm-out_evt-> F3UPPAC_Xmm)*(fF3Param->zpos[i] -
		fF3Param->zpos[0]))/(fF3Param->zpos[1]-fF3Param->zpos[0]);		
	
	out_evt-> Beam_prof_y [i]= out_evt-> F3UPPAC_Ymm + 
		((out_evt-> F3DPPAC_Ymm-out_evt-> F3UPPAC_Ymm)*(fF3Param->zpos[i] -
		  fF3Param->zpos[0]))/(fF2Param->zpos[1]-fF3Param->zpos[0]);	
	
	Beam_profile_z[i]->Fill(out_evt-> Beam_prof_x [i],out_evt-> Beam_prof_y [i]);	
       }
    }
        out_evt->dr = -50 + 100.0*rand()/RAND_MAX;       
        F3_PPAC_ZXmm ->Fill(fF3Param->zpos[0],out_evt->dr);  // U PPAC
        F3_PPAC_ZYmm ->Fill(fF3Param->zpos[0],out_evt->dr);  
        F3_PPAC_ZXmm ->Fill(fF3Param->zpos[1],out_evt->dr);  // D PPAC
        F3_PPAC_ZYmm ->Fill(fF3Param->zpos[1],out_evt->dr);
	F3_PPAC_ZXmm ->Fill(fF3Param->zpos[5],out_evt->dr);  // Entrance MS
        F3_PPAC_ZYmm ->Fill(fF3Param->zpos[5],out_evt->dr);
	F3_PPAC_ZXmm ->Fill(fF3Param->zpos[6],out_evt->dr);  // Exit MS
        F3_PPAC_ZYmm ->Fill(fF3Param->zpos[6],out_evt->dr);
        out_evt->dr = -45 + 90.0*rand()/RAND_MAX;
	F3_PPAC_ZXmm ->Fill(fF3Param->zpos[7],out_evt->dr);  // NaI
        F3_PPAC_ZYmm ->Fill(fF3Param->zpos[7],out_evt->dr);
        out_evt->dr = -15 + 30.0*rand()/RAND_MAX;
        F3_PPAC_ZXmm ->Fill(fF3Param->zpos[2],out_evt->dr);  // Veto
        F3_PPAC_ZYmm ->Fill(fF3Param->zpos[2],out_evt->dr);
	F3_PPAC_ZXmm ->Fill(fF3Param->zpos[3],out_evt->dr);  // Triger
        F3_PPAC_ZYmm ->Fill(fF3Param->zpos[3],out_evt->dr);
        F3_PPAC_ZXmm ->Fill(fF3Param->zpos[4],out_evt->dr);  // Tar
        F3_PPAC_ZYmm ->Fill(fF3Param->zpos[4],out_evt->dr);




		

  
/////////////////////// Beam profiles along the beam line    ////////////////////////////////


	// Beam profile at different Z positions

	// Yassid 071013 05:11 if conditions are needed to eliminate zeros and multihit residual contribution

	for(int i=0;i<9;i++){
	
	if(inp_evt->F2UPPAC_L>0 && inp_evt->F2UPPAC_R>0 && inp_evt-> F2DPPAC_L>0 &&  inp_evt-> F2DPPAC_R>0){
	  if(inp_evt->F2UPPAC_U>0 && inp_evt->F2UPPAC_D>0 && inp_evt-> F2DPPAC_U>0 &&  inp_evt-> F2DPPAC_D>0){	
	
	out_evt-> Beam_prof_x [i]= out_evt-> F2UPPAC_Xmm + 
		((out_evt-> F2DPPAC_Xmm-out_evt-> F2UPPAC_Xmm)*(fF2Param->zpos[i] -
		fF2Param->zpos[0]))/(fF2Param->zpos[1]-fF2Param->zpos[0]);
		
		
		
	
	out_evt-> Beam_prof_y [i]= out_evt-> F2UPPAC_Ymm + 
		((out_evt-> F2DPPAC_Ymm-out_evt-> F2UPPAC_Ymm)*(fF2Param->zpos[i] -
		  fF2Param->zpos[0]))/(fF2Param->zpos[1]-fF2Param->zpos[0]);	
		
		
		}
	}
	
	Beam_profile_z[i]->Fill(out_evt-> Beam_prof_x [i],out_evt-> Beam_prof_y [i]);



	//******************* PID Histogram for gating profile histograms Yassid 21062014 *********************************//

	RF1_F3Si_Anl -> Fill(inp_evt->F2_Tref-inp_evt->RFrequ,0.03968*inp_evt->F3SSD-0.03861);


		//****** Here we go with gated histograms

			//***** F2 Block*****//

		if(PID_Raw_GATE_Anl->Test(  inp_evt->F2_Tref-inp_evt->RFrequ,0.03968*inp_evt->F3SSD-0.03861 )){ 

				   if(inp_evt->F2UPPAC_L>0 && inp_evt->F2UPPAC_R>0 && inp_evt-> F2UPPAC_U>0 &&  inp_evt-> F2UPPAC_D>0)
      						F2_UPPAC_XYmm_cond->Fill(out_evt-> F2UPPAC_Xmm,out_evt-> F2UPPAC_Ymm);


				    if(inp_evt->F2DPPAC_L>0 && inp_evt->F2DPPAC_R>0 && inp_evt-> F2DPPAC_U>0 &&  inp_evt-> F2DPPAC_D>0)
    						F2_DPPAC_XYmm_cond->Fill(out_evt-> F2DPPAC_Xmm,out_evt-> F2DPPAC_Ymm);

					     if (out_evt->F2UPPAC_Xmm>-900 and out_evt->F2UPPAC_Ymm>-900 and 
         					out_evt->F2DPPAC_Xmm>-900 and out_evt->F2DPPAC_Ymm>-900) {
     						
						for (int i=1;i<100;++i) {
      						out_evt->dr = -500 + 2000.0*rand()/RAND_MAX;         
       						F2_PPAC_ZXmm_cond ->Fill(out_evt->dr, 
                       				out_evt-> F2UPPAC_Xmm + (out_evt-> F2DPPAC_Xmm - out_evt-> F2UPPAC_Xmm)*(out_evt->dr-fF2Param->zpos[0])/(fF2Param->zpos[1]-fF2Param->zpos[0]));
      						F2_PPAC_ZYmm_cond ->Fill(out_evt->dr, 
                    				out_evt-> F2UPPAC_Ymm + (out_evt-> F2DPPAC_Ymm - out_evt-> F2UPPAC_Ymm)*(out_evt->dr-fF2Param->zpos[0])/(fF2Param->zpos[1]-fF2Param->zpos[0]));
						out_evt-> Beam_prof_x [8]= out_evt-> F2UPPAC_Xmm + ((out_evt-> F2DPPAC_Xmm-out_evt-> F2UPPAC_Xmm)*(fF2Param->zpos[4] -
						fF2Param->zpos[0]))/(fF2Param->zpos[1]-fF2Param->zpos[0]);		
	
						out_evt-> Beam_prof_y [8]= out_evt-> F2UPPAC_Ymm + 
						((out_evt-> F2DPPAC_Ymm-out_evt-> F2UPPAC_Ymm)*(fF2Param->zpos[4] -
		 				 fF2Param->zpos[0]))/(fF2Param->zpos[1]-fF2Param->zpos[0]);	
	
						Beam_profile_z_cond[8]->Fill(out_evt-> Beam_prof_x [8],out_evt-> Beam_prof_y [8]);	


       						}
   					      }
        						out_evt->dr = -50 + 100.0*rand()/RAND_MAX;               
        						F2_PPAC_ZXmm_cond ->Fill(fF2Param->zpos[0],out_evt->dr);
       						        F2_PPAC_ZYmm_cond ->Fill(fF2Param->zpos[0],out_evt->dr);
        						F2_PPAC_ZXmm_cond ->Fill(fF2Param->zpos[1],out_evt->dr);
        						F2_PPAC_ZYmm_cond ->Fill(fF2Param->zpos[1],out_evt->dr);
        						F2_PPAC_ZXmm_cond ->Fill(fF2Param->zpos[4],out_evt->dr);
       						        F2_PPAC_ZYmm_cond ->Fill(fF2Param->zpos[4],out_evt->dr);  


			//***** F3 Block*****//

				if(inp_evt->F3UPPAC_L>0 && inp_evt->F3UPPAC_R>0 && inp_evt-> F3UPPAC_U>0 &&  inp_evt-> F3UPPAC_D>0)
      						F3_UPPAC_XYmm_cond->Fill(out_evt-> F3UPPAC_Xmm,out_evt-> F3UPPAC_Ymm);

				if(inp_evt->F3DPPAC_L>0 && inp_evt->F3DPPAC_R>0 && inp_evt-> F3DPPAC_U>0 &&  inp_evt-> F3DPPAC_D>0)
   						F3_DPPAC_XYmm_cond->Fill(out_evt-> F3DPPAC_Xmm,out_evt-> F3DPPAC_Ymm);


					 if (out_evt->F3UPPAC_Xmm>-900 and out_evt->F3UPPAC_Ymm>-900 and out_evt->F3DPPAC_Xmm>-900 and out_evt->F3DPPAC_Ymm>-900) { 
       						for (int i=1;i<100;++i) {
        					 out_evt->dr = -500 + 2500.0*rand()/RAND_MAX;        
        					 F3_PPAC_ZXmm_cond ->Fill(out_evt->dr, 
                      				 out_evt-> F3UPPAC_Xmm + (out_evt-> F3DPPAC_Xmm - out_evt-> F3UPPAC_Xmm)*(out_evt->dr-fF3Param->zpos[0])/(fF3Param->zpos[1]-fF3Param->zpos[0]));
       						 F3_PPAC_ZYmm_cond ->Fill(out_evt->dr, 
                      				 out_evt-> F3UPPAC_Ymm + (out_evt-> F3DPPAC_Ymm - out_evt-> F3UPPAC_Ymm)*(out_evt->dr-fF3Param->zpos[0])/(fF3Param->zpos[1]-fF3Param->zpos[0]));
       
       					 }
      						 for(int i=0;i<8;i++){
						 out_evt-> Beam_prof_x [i]= out_evt-> F3UPPAC_Xmm + ((out_evt-> F3DPPAC_Xmm-out_evt-> F3UPPAC_Xmm)*(fF3Param->zpos[i] -
						fF3Param->zpos[0]))/(fF3Param->zpos[1]-fF3Param->zpos[0]);		
	
						out_evt-> Beam_prof_y [i]= out_evt-> F3UPPAC_Ymm + 
						((out_evt-> F3DPPAC_Ymm-out_evt-> F3UPPAC_Ymm)*(fF3Param->zpos[i] -
		 				 fF3Param->zpos[0]))/(fF2Param->zpos[1]-fF3Param->zpos[0]);	
	
						Beam_profile_z_cond[i]->Fill(out_evt-> Beam_prof_x [i],out_evt-> Beam_prof_y [i]);	
       						}
   					 }
       
						 out_evt->dr = -50 + 100.0*rand()/RAND_MAX;       
        				         F3_PPAC_ZXmm_cond ->Fill(fF3Param->zpos[0],out_evt->dr);  // U PPAC
        					 F3_PPAC_ZYmm_cond ->Fill(fF3Param->zpos[0],out_evt->dr);  
       						 F3_PPAC_ZXmm_cond ->Fill(fF3Param->zpos[1],out_evt->dr);  // D PPAC
       						 F3_PPAC_ZYmm_cond ->Fill(fF3Param->zpos[1],out_evt->dr);
					         F3_PPAC_ZXmm_cond ->Fill(fF3Param->zpos[5],out_evt->dr);  // Entrance MS
        					 F3_PPAC_ZYmm_cond ->Fill(fF3Param->zpos[5],out_evt->dr);
						 F3_PPAC_ZXmm_cond ->Fill(fF3Param->zpos[6],out_evt->dr);  // Exit MS
       						 F3_PPAC_ZYmm_cond ->Fill(fF3Param->zpos[6],out_evt->dr);
        					 out_evt->dr = -45 + 90.0*rand()/RAND_MAX;
						 F3_PPAC_ZXmm_cond ->Fill(fF3Param->zpos[7],out_evt->dr);  // NaI
       						 F3_PPAC_ZYmm_cond ->Fill(fF3Param->zpos[7],out_evt->dr);
       						 out_evt->dr = -15 + 30.0*rand()/RAND_MAX;
       						 F3_PPAC_ZXmm_cond ->Fill(fF3Param->zpos[2],out_evt->dr);  // Veto
       						 F3_PPAC_ZYmm_cond ->Fill(fF3Param->zpos[2],out_evt->dr);
						 F3_PPAC_ZXmm_cond ->Fill(fF3Param->zpos[3],out_evt->dr);  // Triger
      					         F3_PPAC_ZYmm_cond ->Fill(fF3Param->zpos[3],out_evt->dr);
        					 F3_PPAC_ZXmm_cond ->Fill(fF3Param->zpos[4],out_evt->dr);  // Tar
        					 F3_PPAC_ZYmm_cond ->Fill(fF3Param->zpos[4],out_evt->dr);







		}// Gate bracer

	
	
	/////////// Conditioned histograms for Beam Profiles////// Yassid 03102013
	//cout<<inp_evt->HODO_dE_Hit<<endl;
	
	//if(PID_Raw_GATE_Scint && PID_Raw_GATE_Scint->Test(inp_evt->F2_RF - inp_evt->F2_Tref,inp_evt->F2_Scint_Q)) { // For PID Gate
	  
	  //if(out_evt->HODO_dE_Hit>=1){
	  
	 // Beam_profile_z_cond[i]->Fill(out_evt-> Beam_prof_x [i],out_evt-> Beam_prof_y [i]);
	  
	  
	//}
			
			
			/*if(out_evt->HODO_dE5_Hit>=1){
			  
			Beam_profile_z_cond5[i]->Fill(out_evt-> Beam_prof_x [i],out_evt-> Beam_prof_y [i]);
		
		
			}
			
			
			if(out_evt->HODO_dE6_Hit>=1){
		
			Beam_profile_z_cond6[i]->Fill(out_evt-> Beam_prof_x [i],out_evt-> Beam_prof_y [i]);
		
		
			}
			
			if(out_evt->HODO_dE7_Hit>=1){
		
			Beam_profile_z_cond7[i]->Fill(out_evt-> Beam_prof_x [i],out_evt-> Beam_prof_y [i]);
		
		
			}*/
			
	 
		
	}// End of for for 9 beam line positions
	



	
	
	
	/*Float_t Rndnum = randomnum->Rndm();
	
	out_evt-> dr_ang = -1000 +  (fF2Param->zpos[8]+1000)*Rndnum;
	
	out_evt-> dr_ang = 0;
	
	out_evt->Beam_trck_X = out_evt-> F2UPPAC_Cal_Pos_X_mm + 
		((out_evt-> F2DPPAC_Cal_Pos_X_mm-out_evt-> F2UPPAC_Cal_Pos_X_mm)*(out_evt->dr_ang -
		fF2Param->zpos[0]))/(fF2Param->zpos[1]-fF2Param->zpos[0]);	
		
		
	out_evt->Beam_trck_Y = out_evt-> F2UPPAC_Cal_Pos_Y_mm + 
		((out_evt-> F2DPPAC_Cal_Pos_Y_mm-out_evt-> F2UPPAC_Cal_Pos_Y_mm)*(out_evt->dr_ang -
		fF2Param->zpos[0]))/(fF2Param->zpos[1]-fF2Param->zpos[0]);
		
		
		Beam_trckZX->Fill(out_evt->dr_ang,out_evt->Beam_trck_X);
		Beam_trckZY->Fill(out_evt->dr_ang,out_evt->Beam_trck_Y);	*/
			
		
     

   /*  for(Int_t ii=0;ii<Art_NUM_CHAN/2;ii++)
     // out_evt->frData[cnt++] = inp_evt->fiCrate1[ii];

   for(Int_t ii=0; ii<Art_NUM_CHAN/2; ii++)
     // out_evt->frData[cnt++] = inp_evt->fiCrate2[ii];

   for(Int_t ii=0;ii<Art_NUM_CHAN;ii++)
     if(out_evt->frData[ii]) {
        if(fWinCon && fWinCon->Test(out_evt->frData[ii])) fSum1->Fill(out_evt->frData[ii]);
        fSum2->Fill(out_evt->frData[ii]);
        fSum3->Fill(out_evt->frData[ii]);
	}*/

   // see comments in UnpackProc
   out_evt->SetValid(isValid);
   return isValid;
}

TH2* TArtAnlProc::MakeH2I_Profile(const char* foldername, 
				int index) {
   
   
    char zposname[100];
    char fullname[100];
    char histoname[100];
    
    if(index==0) sprintf(zposname,"F3UPPAC_Pos");
    else if(index==1) sprintf(zposname,"F3DPPAC_Pos");
    else if(index==2) sprintf(zposname,"Veto_Pos");
    else if(index==3) sprintf(zposname,"Triger_Pos");
    else if(index==4) sprintf(zposname,"Tar_Pos");
    else if(index==5) sprintf(zposname,"MSin_Pos");
    else if(index==6) sprintf(zposname,"MSout_Pos");
    else if(index==7) sprintf(zposname,"NaI_Pos");
    else if(index==8) sprintf(zposname,"F2Viewer_Pos");
    
    
    sprintf(fullname,"%s/Profile_%s",foldername,zposname);
    sprintf(histoname,"Profile_%s",zposname);
   
 
    return MakeTH2('I',fullname,histoname, 1000, -100., 100., 1000, -100., 100.);
    
}   


TH2* TArtAnlProc::MakeH2I_Profile_cond(const char* foldername, 
				int index, int cond) {
   
   
    char zposname[100];
    char fullname[100];
    char histoname[100];
    

	if(index==0) sprintf(zposname,"F3UPPAC_Pos");
    else if(index==1) sprintf(zposname,"F3DPPAC_Pos");
    else if(index==2) sprintf(zposname,"Veto_Pos");
    else if(index==3) sprintf(zposname,"Triger_Pos");
    else if(index==4) sprintf(zposname,"Tar_Pos");
    else if(index==5) sprintf(zposname,"MSin_Pos");
    else if(index==6) sprintf(zposname,"MSout_Pos");
    else if(index==7) sprintf(zposname,"NaI_Pos");
    else if(index==8) sprintf(zposname,"F2Viewer_Pos");

    
    
    sprintf(fullname,"%s/Profile_cond_%s_%02d",foldername,zposname,cond);
    sprintf(histoname,"Profile_cond_%s_%02d",zposname,cond);
   
 
    return MakeTH2('I',fullname,histoname, 1000, -100., 100., 1000, -100., 100.);
    
}     


TH2* TArtAnlProc::MakeH2I_TPC_ID(const char* foldername, 
				int index) {
   
   
    char posname[100];
    char fullname[100];
    char histoname[100];
    
    if(index==0) sprintf(posname,"Right-Up");
    else if(index==1) sprintf(posname,"Right-Down");
    else if(index==2) sprintf(posname,"Left-Up");
    else if(index==3) sprintf(posname,"Left-Down");
  
    
    
    sprintf(fullname,"%s/TPC_PID_%s",foldername,posname);
    sprintf(histoname,"TPC_PID_%s",posname);
   
 
    return MakeTH2('I',fullname,histoname, 1024, 1., 4096.,1024 , 1.,4096.);
    
}   
