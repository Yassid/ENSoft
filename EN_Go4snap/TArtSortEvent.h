// $Id: TArtSortEvent.h 755 2011-05-20 08:04:11Z linev $
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

#ifndef TArtSORTEVENT_H
#define TArtSORTEVENT_H

#include "TGo4EventElement.h"
#include "TArtUnpackEvent.h"

class TArtSortEvent : public TGo4EventElement {
   public:
 TArtSortEvent() : TGo4EventElement() {}
 TArtSortEvent(const char* name) : TGo4EventElement(name) {}
  virtual ~TArtSortEvent() {}
  
  virtual void  Clear(Option_t *t="");
  
      /// Detector cables sorting Yassid 28082013 E390
  
      /// Adding F3 Upstream PPAC and CsI+Si detectors of the active target Yassid 06112013 16:32
      
  
      // Yassid 10122013 F1 Fiber Scintillator
      
      // *************** F1 FIBER *****************//
      
      Int_t F1FIBER_time[310];
      Int_t F1FIBER_Y_POS[310];
      
       Int_t F1_Tref;

      //**************** F2 PPACS ****************//

      Int_t F2UPPAC_L;
      Int_t F2UPPAC_D;
      Int_t F2UPPAC_R;
      Int_t F2UPPAC_U;
      Int_t F2UPPAC_A;
      
      Int_t F2DPPAC_L;
      Int_t F2DPPAC_D;
      Int_t F2DPPAC_R;
      Int_t F2DPPAC_U;
      Int_t F2DPPAC_A;

      //*************** F3 PPACS ******************//

      Int_t F3UPPAC_L;
      Int_t F3UPPAC_D;
      Int_t F3UPPAC_R;
      Int_t F3UPPAC_U;
      Int_t F3UPPAC_A;
      // TETSUYA 28052014 ADD
      Int_t F3DPPAC_L;
      Int_t F3DPPAC_D;
      Int_t F3DPPAC_R;
      Int_t F3DPPAC_U;
      Int_t F3DPPAC_A;
      // ------------------------------
      //*************** F2&F3 PLASTICS ******************//
      // TETSUYA ADD 30052014
      Int_t F2PLASTIC;
      Int_t F3PLASTIC_L;
      Int_t F3PLASTIC_R;
      Int_t RFrequ;
      Int_t F2PLASTIC_T;
      Int_t F3PLASTIC_L_T;
      Int_t F3PLASTIC_R_T;
      Int_t F2SSD;
      Int_t F3SSD;
      // -----------------------------------------      
      Int_t F2_Silicon;
      Int_t F3_Silicon; // 28052014 TETSUYA ADD

      Int_t F2_Scint_Q;
      Int_t F2_Scint_T;

      Int_t F2_RF;
      Int_t F2_Tref;

      Int_t PPAC_Trg;

      /*
      //Added for E428 by ST
      Int_t ElossmaxXL;
      Int_t ElossmaxYL;
      Int_t ElossmaxXR;
      Int_t ElossmaxYR;
      Int_t ELl;
      Int_t ERl;
      Int_t ELh;
      Int_t ERh;
      */
      
      //	    F3 Detectors for E372 experiment Yassid 19062014
      Int_t F3VETO_L;
      Int_t F3VETO_R;
      Int_t F3VETO_L_T;
      Int_t F3VETO_R_T;
      Int_t F3NaI_H;
      Int_t F3NaI_L;
      Int_t F3MUSIC_E[8];
      Int_t F3MUSIC_T[8];
      Int_t F3MUSIC_dE;
       

   ClassDef(TArtSortEvent,1)
};
#endif //TArtSORTEVENT_H



