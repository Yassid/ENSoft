#define F2Cal_cxx
#include "F2Cal.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>



TH2I* PID_Si =new TH2I("PID_Si","PID_Si",4096,0,4096,4096,0,4096);
TH2I* PID_Scint =new TH2I("PID_Pla","PID_Pla",4096,0,4096,4096,0,4096);

void F2Cal::Loop()
{

   gSystem->Load("libanacore.so");

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      PID_Si->Fill(SortEvent_HODO_RF_Del,SortEvent_F2_Silicon);
      PID_Scint->Fill(SortEvent_HODO_RF_Del,SortEvent_F2_Scint_Q);
      
      
   }
   
   TCanvas *c1 = new TCanvas("c1","c1",500,500);
   PID_Si->Draw("col");
   TCanvas *c2 = new TCanvas("c2","c2",500,500);
   PID_Scint->Draw("col");
   
}
