#define e390_anl_cxx
#include "e390_anl.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TH1.h>
#include <TCutG.h>

#include <TSystem.h>
#include <iostream>

using namespace std;


void e390_anl::Loop()
{


	// Parameters for PPAC Calibration
	
	Float_t F2UPPAC_Cal_Pos_X_ns;
	Float_t F2UPPAC_Cal_Pos_Y_ns;
	Float_t F2DPPAC_Cal_Pos_X_ns;
	Float_t F2DPPAC_Cal_Pos_Y_ns;
	
	Float_t F2UPPAC_Cal_Pos_X_mm;
	Float_t F2UPPAC_Cal_Pos_Y_mm;
	Float_t F2DPPAC_Cal_Pos_X_mm;
	Float_t F2DPPAC_Cal_Pos_Y_mm;
	
	Float_t fF2UPPAC_tdc_param[4];
	
	  fF2UPPAC_tdc_param[0]= 0.1; // F2 U Left
          fF2UPPAC_tdc_param[1]= 0.1; // F2 U Right
          fF2UPPAC_tdc_param[2]= 0.1; //  F2 U Up
          fF2UPPAC_tdc_param[3]= 0.1; // F2 U Down
   
	Float_t fF2DPPAC_tdc_param[4];

  	 fF2DPPAC_tdc_param[0]= 0.1;// F2 D Left
  	 fF2DPPAC_tdc_param[1]= 0.1; // F2 D Right
  	 fF2DPPAC_tdc_param[2]= 0.1; // F2 D Up
  	 fF2DPPAC_tdc_param[3]= 0.1; // F2 D Down
   
  	Float_t fF2UPPAC_tdc_ns2mm[4];
   

   	 fF2UPPAC_tdc_ns2mm[0]=0.63419;// f2 Upstream X slope
  	 fF2UPPAC_tdc_ns2mm[1]=0.62479;//f2 Upstream Y slope
  	 fF2UPPAC_tdc_ns2mm[2]=-7.262;//f2 Upstream X offset
  	 fF2UPPAC_tdc_ns2mm[3]=-4.923;//f2 Upstream Y offset

	Float_t fF2DPPAC_tdc_ns2mm[4];

  	 fF2DPPAC_tdc_ns2mm[0]=0.62691;//f2 Downstream X slope
  	 fF2DPPAC_tdc_ns2mm[1]=0.62147;//f2 Downstream Y slope
   	 fF2DPPAC_tdc_ns2mm[2]=-2.8068;//f2 Downstream X offset
  	 fF2DPPAC_tdc_ns2mm[3]=0.63758;//f2 Downstream Y offset
   
   	Float_t fF2UPPAC_e390_offset[4];
   
  	 fF2UPPAC_e390_offset[0]= -1.7438+3.93 - 1.64; //f2U X
  	 fF2UPPAC_e390_offset[1]= 0.5954;//f2U Y
   
   	Float_t fF2DPPAC_e390_offset[4];
   
  	 fF2DPPAC_e390_offset[0]= -1.3177 + 4.635 -3.68; //f2D X
  	 fF2DPPAC_e390_offset[1]= -0.38158;//f2D Y
	 
	 Float_t zpos[9];
	 
	 zpos[0]= 0; // F2 Upstream PPAC
         zpos[1]= 482; // F2 Downstream PPAC
         zpos[2]= 88; // F2 Plastic Scintillator 
         zpos[3]= 630;  //F2 Gate valve
   	 zpos[4]= 755;  // F2 Viewer
   	 zpos[5]= 1059; // F2 Entrance of Scattering chamber
         zpos[6]= 1619; // F2 Target position
         zpos[7]= 2179; //  F2 Scattering chamber exit
         zpos[8]= 5459; // Hodoscope

  Float_t Beam_prof_x_06=0;
  
  Float_t Beam_prof_y_06=0;
  
  Int_t beam=0;
 
  TH2I *PID_HODO_dE[13]; 

  TH2I *PID_HODO_dE_cond[13];
  
  TH2I *PID_HODO_E1_cond[16]; 

  TCutG *cutg14O = new TCutG("14O",13);
  TCutG *cutg14OdE = new TCutG("14OdE",10);
  TCutG *cutg11C = new TCutG("11C",13);
  TCutG *cutgug = new TCutG("ug",10);
  TCutG *cutg12N = new TCutG("12N",13);
  TCutG *cutgPPAC = new TCutG("PPAC",14);
  
  Int_t cutinn_14O,cutinn_14OdE,cutinn_11C,cutinn_ug,cutinn_12N,cutinn_PPAC;


  TH2I *PID_F2 = new TH2I("PID_F2","PID_F2",250, 46000., 46500.,4096,1.,4096);
  TH2I *PID_F2_cond = new TH2I("PID_F2_cond","PID_F2_cond",250, 46000., 46500.,4096,1.,4096);
  
  TH2I *Beam_profile_z_06= new TH2I("Beam_profile_z_06","Beam_profile_z_06",1000, -100., 100., 1000, -100., 100.);
  
 //TH2I *PID_HODO_dE_06 = new TH2I("PID_HODO_dE_06","PID_HODO_dE_06",1000, 4096., 4096.,4096,1.,4096);

 //TH2I *PID_HODO_dE_06_cond = new TH2I("PID_HODO_dE_06_cond","PID_HODO_dE_06_cond",1000, 1., 4096.,4096,1.,4096);
 
  cutg14O->SetVarX("PID_F2");
  cutg14O->SetVarY("");
  cutg14O->SetTitle("Graph");
  cutg14O->SetFillColor(1);
  cutg14O->SetPoint(0,46298.11,2703.288);
  cutg14O->SetPoint(1,46324.59,2386.419);
  cutg14O->SetPoint(2,46326.93,1567.196);
  cutg14O->SetPoint(3,46322.25,1095.756);
  cutg14O->SetPoint(4,46314.47,956.6432);
  cutg14O->SetPoint(5,46291.1,902.5436);
  cutg14O->SetPoint(6,46278.64,972.1002);
  cutg14O->SetPoint(7,46268.52,1366.255);
  cutg14O->SetPoint(8,46268.52,1714.038);
  cutg14O->SetPoint(9,46269.3,2108.192);
  cutg14O->SetPoint(10,46280.98,2440.518);
  cutg14O->SetPoint(11,46297.33,2695.559);
  cutg14O->SetPoint(12,46298.11,2703.288);
  
   
   cutg14OdE->SetVarX("PID_HODO_dE_cond_06");
   cutg14OdE->SetVarY("");
   cutg14OdE->SetTitle("Graph");
   cutg14OdE->SetFillColor(1);
   cutg14OdE->SetPoint(0,1395.27,2082.41);
   cutg14OdE->SetPoint(1,1370.868,2045.193);
   cutg14OdE->SetPoint(2,1370.868,1953.392);
   cutg14OdE->SetPoint(3,1385.78,1918.657);
   cutg14OdE->SetPoint(4,1407.471,1903.77);
   cutg14OdE->SetPoint(5,1416.283,1923.619);
   cutg14OdE->SetPoint(6,1420.35,1973.241);
   cutg14OdE->SetPoint(7,1415.605,2050.155);
   cutg14OdE->SetPoint(8,1395.27,2084.891);
   cutg14OdE->SetPoint(9,1395.27,2082.41);
   
   
   cutg11C->SetVarX("PID_F2");
   cutg11C->SetVarY("");
   cutg11C->SetTitle("Graph");
   cutg11C->SetPoint(0,46238.66,2113.569);
   cutg11C->SetPoint(1,46265.12,1799.069);
   cutg11C->SetPoint(2,46267.64,974.8639);
   cutg11C->SetPoint(3,46262.6,508.5371);
   cutg11C->SetPoint(4,46255.04,367.5545);
   cutg11C->SetPoint(5,46231.1,313.3305);
   cutg11C->SetPoint(6,46218.5,378.3994);
   cutg11C->SetPoint(7,46208.42,779.6573);
   cutg11C->SetPoint(8,46208.42,1126.691);
   cutg11C->SetPoint(9,46209.68,1517.104);
   cutg11C->SetPoint(10,46221.02,1853.293);
   cutg11C->SetPoint(11,46237.4,2102.724);
   cutg11C->SetPoint(12,46238.66,2113.569);
   
   
   cutgug->SetVarX("PID_HODO_dE_cond_06");
   cutgug->SetVarY("");
   cutgug->SetTitle("Graph");
   cutgug->SetPoint(0,1330.938,1881.005);
   cutgug->SetPoint(1,1304.548,1837.507);
   cutgug->SetPoint(2,1304.548,1750.512);
   cutgug->SetPoint(3,1319.628,1715.713);
   cutgug->SetPoint(4,1342.249,1698.314);
   cutgug->SetPoint(5,1349.789,1715.713);
   cutgug->SetPoint(6,1353.559,1767.911);
   cutgug->SetPoint(7,1349.789,1846.207);
   cutgug->SetPoint(8,1330.938,1881.005);
   cutgug->SetPoint(9,1330.938,1881.005);
   
   
   cutg12N->SetVarX("PID_F2");
   cutg12N->SetVarY("");
   cutg12N->SetTitle("Graph");
   cutg12N->SetFillColor(1);
   cutg12N->SetPoint(0,46297.88,3176.36);
   cutg12N->SetPoint(1,46324.34,2861.861);
   cutg12N->SetPoint(2,46326.86,2037.655);
   cutg12N->SetPoint(3,46321.82,1571.328);
   cutg12N->SetPoint(4,46314.26,1430.346);
   cutg12N->SetPoint(5,46290.32,1376.122);
   cutg12N->SetPoint(6,46277.72,1441.191);
   cutg12N->SetPoint(7,46267.64,1842.449);
   cutg12N->SetPoint(8,46267.64,2189.483);
   cutg12N->SetPoint(9,46268.9,2579.896);
   cutg12N->SetPoint(10,46280.24,2916.085);
   cutg12N->SetPoint(11,46296.62,3165.515);
   cutg12N->SetPoint(12,46297.88,3176.36);
   cutg12N->Draw("");
   
   
   
   cutgPPAC->SetVarX("Beam_profile_z_06");
   cutgPPAC->SetVarY("");
   cutgPPAC->SetTitle("Graph");
   cutgPPAC->SetFillColor(1);
   cutgPPAC->SetPoint(0,1.289012,-0.9851694);
   cutgPPAC->SetPoint(1,-5.137903,-3.632415);
   cutgPPAC->SetPoint(2,-7.018952,-9.238347);
   cutgPPAC->SetPoint(3,-6.862198,-16.40148);
   cutgPPAC->SetPoint(4,-4.354133,-19.04873);
   cutgPPAC->SetPoint(5,-1.53256,-20.45021);
   cutgPPAC->SetPoint(6,3.170061,-21.69597);
   cutgPPAC->SetPoint(7,7.872682,-18.27013);
   cutgPPAC->SetPoint(8,10.69425,-10.63983);
   cutgPPAC->SetPoint(9,9.910484,-7.836864);
   cutgPPAC->SetPoint(10,7.872682,-4.722458);
   cutgPPAC->SetPoint(11,4.737601,-2.386652);
   cutgPPAC->SetPoint(12,1.60252,-1.14089);
   cutgPPAC->SetPoint(13,1.289012,-0.9851694);
 
  
  
  
  Char_t histoname[100];
  
  for(Int_t i=0;i<13;i++){
  
  
  	sprintf(histoname,"PID_HODO_dE_%02d",i);
  	PID_HODO_dE[i]= new TH2I(histoname,histoname,1000, 1., 4096.,1000,1.,4096);
	sprintf(histoname,"PID_HODO_dE_cond_%02d",i);
  	PID_HODO_dE_cond[i]= new TH2I(histoname,histoname,1000, 1., 4096.,1000,1.,4096);
  
  
  }
  
 
 
   Char_t histoname2[100];
 
 /* for(Int_t i=0;i<16;i++){
  
  	sprintf(histoname2,"PID_HODO_E1_cond_%02d",i);
  	PID_HODO_E1_cond[i]=new TH2I(histoname2,histoname2,4096, 1., 4096.,4096,1.,4096);
  
  }*/
  
   PID_HODO_E1_cond[5]=new TH2I("PID_HODO_E1_cond_5","PID_HODO_E1_cond_5",1000, 1., 4096.,1000,1.,4096);
   PID_HODO_E1_cond[6]=new TH2I("PID_HODO_E1_cond_6","PID_HODO_E1_cond_6",1000, 1., 4096.,1000,1.,4096);
   PID_HODO_E1_cond[7]=new TH2I("PID_HODO_E1_cond_7","PID_HODO_E1_cond_7",1000, 1., 4096.,1000,1.,4096);
   PID_HODO_E1_cond[8]=new TH2I("PID_HODO_E1_cond_8","PID_HODO_E1_cond_8",1000, 1., 4096.,1000,1.,4096);
   PID_HODO_E1_cond[9]=new TH2I("PID_HODO_E1_cond_9","PID_HODO_E1_cond_9",1000, 1., 4096.,1000,1.,4096);

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0 , nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      
      if(jentry%10000==0) cout<<jentry<<"/"<<nentries<< endl;
      
      
        // channels to ns
 
     F2UPPAC_Cal_Pos_X_ns = (fF2UPPAC_tdc_param[0]*SortEvent_F2UPPAC_L) - (fF2UPPAC_tdc_param[1]*SortEvent_F2UPPAC_R );
  
     F2UPPAC_Cal_Pos_Y_ns = (fF2UPPAC_tdc_param[3]*SortEvent_F2UPPAC_D) - (fF2UPPAC_tdc_param[2]*SortEvent_F2UPPAC_U );
     F2DPPAC_Cal_Pos_X_ns = (fF2DPPAC_tdc_param[0]*SortEvent_F2DPPAC_L) - (fF2DPPAC_tdc_param[1]*SortEvent_F2DPPAC_R );
     F2DPPAC_Cal_Pos_Y_ns = (fF2DPPAC_tdc_param[3]*SortEvent_F2DPPAC_D) - (fF2DPPAC_tdc_param[2]*SortEvent_F2DPPAC_U );	

   // ns to mm
 
   F2UPPAC_Cal_Pos_X_mm =(F2UPPAC_Cal_Pos_X_ns*fF2UPPAC_tdc_ns2mm[0]) - fF2UPPAC_tdc_ns2mm[2] ;
   F2UPPAC_Cal_Pos_Y_mm =(F2UPPAC_Cal_Pos_Y_ns*fF2UPPAC_tdc_ns2mm[1]) - fF2UPPAC_tdc_ns2mm[3] ;
   F2DPPAC_Cal_Pos_X_mm =(F2DPPAC_Cal_Pos_X_ns*fF2DPPAC_tdc_ns2mm[0]) - fF2DPPAC_tdc_ns2mm[2] ;
   F2DPPAC_Cal_Pos_Y_mm =(F2DPPAC_Cal_Pos_Y_ns*fF2DPPAC_tdc_ns2mm[1]) - fF2DPPAC_tdc_ns2mm[3] ;


  // e390 user offset	

   F2UPPAC_Cal_Pos_X_mm = F2UPPAC_Cal_Pos_X_mm + fF2UPPAC_e390_offset[0];
   F2UPPAC_Cal_Pos_Y_mm = F2UPPAC_Cal_Pos_Y_mm + fF2UPPAC_e390_offset[1];
   F2DPPAC_Cal_Pos_X_mm = F2DPPAC_Cal_Pos_X_mm + fF2DPPAC_e390_offset[0];
   F2DPPAC_Cal_Pos_Y_mm = F2DPPAC_Cal_Pos_Y_mm + fF2DPPAC_e390_offset[1]; 

      
      
   //  for(int i=0;i<9;i++){
	
	if(SortEvent_F2UPPAC_L>0 && SortEvent_F2UPPAC_R>0 && SortEvent_F2DPPAC_L>0 &&  SortEvent_F2DPPAC_R>0){
	  if(SortEvent_F2UPPAC_U>0 && SortEvent_F2UPPAC_D>0 && SortEvent_F2DPPAC_U>0 &&  SortEvent_F2DPPAC_D>0){	
	
	   Beam_prof_x_06= F2UPPAC_Cal_Pos_X_mm + (( F2DPPAC_Cal_Pos_X_mm-F2UPPAC_Cal_Pos_X_mm)*(zpos[6] -zpos[0]))/(zpos[1]-zpos[0]);
		
		
		
	
	   Beam_prof_y_06= F2UPPAC_Cal_Pos_Y_mm + (( F2DPPAC_Cal_Pos_Y_mm-F2UPPAC_Cal_Pos_Y_mm)*(zpos[6]-zpos[0]))/(zpos[1]-zpos[0]);	
		
		
		}
	}
	
	 Beam_profile_z_06->Fill(Beam_prof_x_06,Beam_prof_y_06);	
      
      
     // }  // If we want to add more layers along the beam line....
      
      
      
      
      
      
      
      cutinn_14O = cutg14O->IsInside(SortEvent_F2_RF - SortEvent_F2_Tref,SortEvent_F2_Scint_Q);
      cutinn_11C = cutg11C->IsInside(SortEvent_F2_RF - SortEvent_F2_Tref,SortEvent_F2_Scint_Q);
      cutinn_12N = cutg12N->IsInside(SortEvent_F2_RF - SortEvent_F2_Tref,SortEvent_F2_Scint_Q); //14O cut in PIDF2 without 12N
      cutinn_14OdE = cutg14OdE->IsInside((-(SortEvent_HODO_dE_UT[6]+SortEvent_HODO_dE_DT[6])/2.0)+(SortEvent_PPAC_Trg)+1000,sqrt(SortEvent_HODO_dE_UQ[6]*SortEvent_HODO_dE_DQ[6]));
      cutinn_ug = cutgug->IsInside((-(SortEvent_HODO_dE_UT[6]+SortEvent_HODO_dE_DT[6])/2.0)+(SortEvent_PPAC_Trg)+1000,sqrt(SortEvent_HODO_dE_UQ[6]*SortEvent_HODO_dE_DQ[6]));
      cutinn_PPAC = cutgPPAC->IsInside(Beam_prof_x_06,Beam_prof_y_06);
     
      PID_F2->Fill(SortEvent_F2_RF - SortEvent_F2_Tref,SortEvent_F2_Scint_Q);
      
      
      for(Int_t i=0;i<13;i++){
      
         PID_HODO_dE[i]->Fill((-(SortEvent_HODO_dE_UT[i]+SortEvent_HODO_dE_DT[i])/2.0)+(SortEvent_PPAC_Trg)+1000,sqrt(SortEvent_HODO_dE_UQ[i]*SortEvent_HODO_dE_DQ[i]));
         	
		if(cutinn_14O && cutinn_PPAC) {
	 
		 PID_HODO_dE_cond[i]->Fill((-(SortEvent_HODO_dE_UT[i]+SortEvent_HODO_dE_DT[i])/2.0)+(SortEvent_PPAC_Trg)+1000,sqrt(SortEvent_HODO_dE_UQ[i]*SortEvent_HODO_dE_DQ[i]));
     		 beam++;
     
     		}
   	
	}// for loop
	
	
	//for(Int_t i=0;i<16;i++) 
	//if(cutinn_14O && cutinn_14OdE){
	
	if(cutinn_14O && cutinn_14OdE ){

        PID_HODO_E1_cond[5]->Fill((-(SortEvent_HODO_E1_LT[5]+SortEvent_HODO_E1_RT[5])/2.0)+(SortEvent_PPAC_Trg)+1000,sqrt(SortEvent_HODO_E1_LQ[5]*SortEvent_HODO_E1_RQ[5]));

	PID_HODO_E1_cond[6]->Fill((-(SortEvent_HODO_E1_LT[6]+SortEvent_HODO_E1_RT[6])/2.0)+(SortEvent_PPAC_Trg)+1000,sqrt(SortEvent_HODO_E1_LQ[6]*SortEvent_HODO_E1_RQ[6]));

	PID_HODO_E1_cond[7]->Fill((-(SortEvent_HODO_E1_LT[7]+SortEvent_HODO_E1_RT[7])/2.0)+(SortEvent_PPAC_Trg)+1000,sqrt(SortEvent_HODO_E1_LQ[7]*SortEvent_HODO_E1_RQ[7]));
	
        PID_HODO_E1_cond[8]->Fill((-(SortEvent_HODO_E1_LT[8]+SortEvent_HODO_E1_RT[8])/2.0)+(SortEvent_PPAC_Trg)+1000,sqrt(SortEvent_HODO_E1_LQ[8]*SortEvent_HODO_E1_RQ[8]));

        PID_HODO_E1_cond[9]->Fill((-(SortEvent_HODO_E1_LT[9]+SortEvent_HODO_E1_RT[9])/2.0)+(SortEvent_PPAC_Trg)+1000,sqrt(SortEvent_HODO_E1_LQ[9]*SortEvent_HODO_E1_RQ[9]));
	
	}
	
	if(cutinn_ug) PID_F2_cond->Fill(SortEvent_F2_RF - SortEvent_F2_Tref,SortEvent_F2_Scint_Q);
   
   
   }// end of events
   
   
   TCanvas *c1 = new TCanvas("c1","c1",500,500);
   PID_F2->Draw("col");
   cutg14O->Draw("SAME");
   
  /* TCanvas *c2 = new TCanvas("c2","c2",500,500);
   c2->Draw();
   c2->Divide(2,2);*/
   
   /*c2->cd(1);

   PID_HODO_dE[0]->Draw("col");
   c2->cd(2);
   PID_HODO_dE[1]->Draw("col");
   c2->cd(3);
   PID_HODO_dE[2]->Draw("col");
   c2->cd(4);
   PID_HODO_dE[3]->Draw("col");*/
   
  /* c2->cd(1);
   PID_HODO_dE[4]->Draw("col");
   c2->cd(2);
   PID_HODO_dE[5]->Draw("col");
   c2->cd(3);
   PID_HODO_dE[6]->Draw("col");*/
   
  /* c2->cd(8);
   PID_HODO_dE[7]->Draw("col");
   c2->cd(9);
   PID_HODO_dE[8]->Draw("col");
   c2->cd(10);
   PID_HODO_dE[9]->Draw("col");
   c2->cd(11);
   PID_HODO_dE[10]->Draw("col");
   c2->cd(12);
   PID_HODO_dE[11]->Draw("col");
   c2->cd(13);
   PID_HODO_dE[12]->Draw("col");*/   
   
   TCanvas *c3 = new TCanvas("c3","c3",500,500);
   c3->Draw();
   c3->Divide(2,3);
   /*c3->cd(1);
   PID_HODO_dE_cond[0]->Draw("col");
   c3->cd(2);
   PID_HODO_dE_cond[1]->Draw("col");
   c3->cd(3);
   PID_HODO_dE_cond[2]->Draw("col");
   c3->cd(4);
   PID_HODO_dE_cond[3]->Draw("col");*/
   
   
   c3->cd(1);
   PID_HODO_dE_cond[4]->Draw("col");
   c3->cd(2);
   PID_HODO_dE_cond[5]->Draw("col");
   c3->cd(3);
   PID_HODO_dE_cond[6]->Draw("col");
   cutg14OdE->Draw("SAME");
   c3->cd(4);
   PID_HODO_dE_cond[7]->Draw("col");
   c3->cd(5);
   PID_HODO_dE_cond[8]->Draw("col");
   
   
   /*c3->cd(9);
   PID_HODO_dE_cond[8]->Draw("col");
   c3->cd(10);
   PID_HODO_dE_cond[9]->Draw("col");
   c3->cd(11);
   PID_HODO_dE_cond[10]->Draw("col");
   c3->cd(12);
   PID_HODO_dE_cond[11]->Draw("col");
   c3->cd(13);
   PID_HODO_dE_cond[12]->Draw("col");*/
   
   
    TCanvas *c4 = new TCanvas("c4","c4",500,500);
    c4->Draw();
    c4->Divide(2,2);
    
    c4->cd(1);
    PID_HODO_E1_cond[5]->Draw("col");
    c4->cd(2);
    PID_HODO_E1_cond[6]->Draw("col");
    c4->cd(3);
    PID_HODO_E1_cond[7]->Draw("col");
    c4->cd(4);
    PID_HODO_E1_cond[8]->Draw("col");
 
    TCanvas *c5 = new TCanvas("c5","c5",500,500);
    c5->Draw();
    PID_F2_cond->Draw("col");
    
    TCanvas *c6 = new TCanvas("c6","c6",500,500);
    c6->Draw();
    Beam_profile_z_06->Draw("col");
    cutgPPAC->Draw("SAME");
    
    cout<<" Total number of counts : "<<beam<<endl;
		
}
