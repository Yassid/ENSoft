// $Id: TArtAnlEvent.cxx 755 2011-05-20 08:04:11Z linev $
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

#include "TArtAnlEvent.h"

void TArtAnlEvent::Clear(Option_t *t)
{

   dr = 0;
   F2UPPAC_Xns=0;
   F2UPPAC_Yns=0;
   F2DPPAC_Xns=0;
   F2DPPAC_Yns=0;
   
   F2UPPAC_Xmm=-1000;
   F2UPPAC_Ymm=-1000;
   F2DPPAC_Xmm=-1000;
   F2DPPAC_Ymm=-1000;

   F3UPPAC_Xns=0;
   F3UPPAC_Yns=0;
   F3DPPAC_Xns=0;
   F3DPPAC_Yns=-1000;
   
   F3UPPAC_Xmm=-1000;
   F3UPPAC_Ymm=-1000;
   F3DPPAC_Xmm=-1000;
   F3DPPAC_Ymm=-1000;

   
   dr_ang=0;
   Beam_trck_X=0;
   Beam_trck_Y=0;
   
    for(int i=0;i<11;i++) {
   
   Beam_prof_x[i]=0;
   Beam_prof_y[i]=0;
   
   }
   

   F2Sil_Energy=0;
    
   F2Scint_Cal_ToF=0;
}
