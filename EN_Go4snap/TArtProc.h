#ifndef TUNPACKPROCESSOR_H
#define TUNPACKPROCESSOR_H

#include "TGo4EventProcessor.h"
class TArtEvent;
//class TArtParam;
class TArtRawEventObject;

class TArtProc : public TGo4EventProcessor {
   public:
      TArtProc() ;
      TArtProc(const char* name);
      virtual ~TArtProc() ;
      // event processing function, default name
      Bool_t BuildEvent(TGo4EventElement* target);
 private:
      TH1           *fHis1;  
   ClassDef(TArtProc,1)
};
#endif //TUNPACKPROCESSOR_H


//----------------------------END OF GO4 SOURCE FILE ---------------------
