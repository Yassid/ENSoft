// $Id: TArtUnpackEvent.h 755 2011-05-20 08:04:11Z linev $
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

#ifndef TArtEVENT_H
#define TArtEVENT_H

#define Art_NUM_CHAN 8

#include "TGo4EventElement.h"
#include "analysisFlag.h"
class TArtUnpackEvent : public TGo4EventElement {
   public:
 /*     struct mapping{
        Int_t filled;
    	Int_t cad;
    	Int_t seg;
    	Int_t det;
    	Int_t mod;
    	Int_t ch;
    	Int_t hit;
    	Int_t edge;
    	Char_t name[20];
    	Int_t val;
     };

   */   TArtUnpackEvent() : TGo4EventElement() {}
      TArtUnpackEvent(const char* name) : TGo4EventElement(name) {}
      virtual ~TArtUnpackEvent() {}

      /**
       * Method called by the event owner (analysis step) to clear the
       * event element.
       */
      virtual void Clear(Option_t *t="");
      Int_t rawdata[maxFP+1][maxDet+1][maxMod+1][maxCh+1];
      Int_t v1190[maxDetV+1][maxChV+1][maxHit+1];

   private:
     
   ClassDef(TArtUnpackEvent,1)
};
#endif //TArtEVENT_H



