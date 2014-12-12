// $Id: TArtAnlEvent.h 755 2011-05-20 08:04:11Z linev $
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

#ifndef TArtANLEVENT_H
#define TArtANLEVENT_H

#include "TGo4EventElement.h"
#include "TArtSortEvent.h"

class TArtAnlEvent : public TGo4EventElement {
   public:
      TArtAnlEvent() : TGo4EventElement() {}
      TArtAnlEvent(const char* name) : TGo4EventElement(name) {}
      virtual ~TArtAnlEvent() {}

      virtual void  Clear(Option_t *t="");
      Float_t dr;
      Float_t F2UPPAC_Xns;
      Float_t F2UPPAC_Yns;
      Float_t F2DPPAC_Xns;
      Float_t F2DPPAC_Yns;
      
      Float_t F2UPPAC_Xmm;
      Float_t F2UPPAC_Ymm;
      Float_t F2DPPAC_Xmm;
      Float_t F2DPPAC_Ymm; 

      Float_t F3UPPAC_Xns;
      Float_t F3UPPAC_Yns;
      Float_t F3DPPAC_Xns;
      Float_t F3DPPAC_Yns;
      
      Float_t F3UPPAC_Xmm;
      Float_t F3UPPAC_Ymm;
      Float_t F3DPPAC_Xmm;
      Float_t F3DPPAC_Ymm;

      Float_t Beam_prof_x[11];
      Float_t Beam_prof_y[11]; 
      
      Float_t dr_ang;
      Float_t Beam_trck_X;
      Float_t Beam_trck_Y;  


      Float_t F2Sil_Energy;

      Float_t F2Scint_Cal_ToF;
      
      

      

   ClassDef(TArtAnlEvent,1)
};
#endif //TArtANLEVENT_H



