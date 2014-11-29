#include "TArtProc.h"
#include "Riostream.h"
#include "TH1.h"
#include "TH2.h"
#include "TCutG.h"
#include "snprintf.h"
#include "TGo4WinCond.h"
#include "TGo4PolyCond.h"
#include "TGo4CondArray.h"
#include "TGo4Picture.h"
//#include "TArtParam.h"
// if we have this class:
#include "TArtRawEvent.h"
#include "TArtUnpackEvent.h"
#include "segidlist.h"

//***********************************************************
TArtProc::TArtProc() : TGo4EventProcessor("Proc")
{
  cout << "**** TArtProc: Create instance " << endl;
}
//***********************************************************
TArtProc::~TArtProc()
{
  cout << "**** TArtProc: Delete instance " << endl;
}
//***********************************************************
// this one is used in standard factory
TArtProc::TArtProc(const char* name) : TGo4EventProcessor(name)
{
  cout << "**** TArtProc: Create instance " << name << endl;

 
    fHis1  = MakeTH1('I',"His1","Data Segments",100,1,100,"Channels");
    cout << "**** TArtProc: Created objects" << endl;
  
}
//-----------------------------------------------------------
// event function
Bool_t TArtProc::BuildEvent(TGo4EventElement* target)
{
 
    Bool_t isValid=kFALSE; // validity of output event

  TArtRawEventObject    * rawobj;
  TArtRawEvent    * raw;
  TArtRawSegmentObject *seg;
  TArtRawDataObject *d;

  raw = (TArtRawEvent* ) GetInputEvent();
  rawobj = (TArtRawEventObject *) raw->raweve;
  
    TArtUnpackEvent* out_evt = dynamic_cast<TArtUnpackEvent*> (target);
    
     if (raw==0) {
      cout << "TArtProc: no input event !"<< endl;
       out_evt->SetValid(isValid); // to store or not to store
      // default calling Fill method will set validity of out_evt to return value!
      return isValid;
      }
      // isValid=kTRUE;
      
      Int_t nsegments = rawobj->GetNumSeg();
 
      fHis1->Fill(nsegments);
    //  int nch =0;	
      for(int i=0;i<nsegments;i++){
	       seg = rawobj->GetSegment(i);
//	       int cadid =seg->GetDevice();
	       int segid1=seg->GetFP();	      
	       int detid=seg->GetDetector();
	       int modid=seg->GetModule();
               int mhitl[128]={0};
	       int mhitt[128]={0}; 
	       for (int j=0;j<seg->GetNumData();j++){
		  d = seg->GetData(j);//get rawdata
		  int ch = d->GetCh();
		  int val = d->GetVal();
		  int edge= 0;
                  if (modid == V1190){
		    edge=d->GetEdge(); 
                    if(mhitl[ch]<10){ //Leading
		      if(edge==0){ 
			    //out_evt-> v7768_tdc[16][ch][mhitl[ch]]= val;
			out_evt->v1190[detid][ch][mhitl[ch]]= val;
//	if (segid1==F3 && modid==AMTTDC) cout<<cadid<<"-"<<segid1<<"-"<<detid<<"-"<<modid<<"-"<<ch<<":   "<<val<<"  edge:  "<<edge<<"  hit:  "<<mhitl[ch]<<endl;
		        mhitl[ch]++;
		      }
		    }
                    if(mhitt[ch]<10){ //Trailing
		       if(edge==1){ 
			 //out_evt-> v7768_tdc[16][ch][mhitl[ch]]= val;
			 out_evt->v1190[detid][ch][mhitt[ch]+10]= val;
			 mhitt[ch]++;
//if (segid1==F3 && modid==AMTTDC) cout<<cadid<<"-"<<segid1<<"-"<<detid<<"-"<<modid<<"-"<<ch<<":   "<<val<<"  edge:  "<<edge<<"  hit:  "<<mhitt[ch]<<endl;
		       }
		    } 	
		  }
		  else{
		    if (ch< 64) out_evt->rawdata[segid1][detid][modid][ch]=val;
		  }
              /*    out_evt->rawdatan[nch].filled = 1;
                  out_evt->rawdatan[nch].cad = cadid;
                  out_evt->rawdatan[nch].seg = segid1;
                  out_evt->rawdatan[nch].det = detid;
                  out_evt->rawdatan[nch].mod = modid;
                  out_evt->rawdatan[nch].ch = ch;            
                  out_evt->rawdatan[nch].edge = edge;
                  out_evt->rawdatan[nch].val = val;
                  if (edge==0) out_evt->rawdatan[nch].hit = mhitl[ch];
                  else out_evt->rawdatan[nch].hit = mhitt[ch];
                  nch++;
*/
//	if (segid1==F3 && modid==20) cout<<cadid<<"-"<<segid1<<"-"<<detid<<"-"<<modid<<"-"<<ch<<":   "<<val<<"  edge:  "<<edge<<endl;
       	}

     } // Segment loop
    // out_evt->numch=nch;
  return kTRUE;
}

//-----------------------------------------------------------

//----------------------------END OF GO4 SOURCE FILE ---------------------
