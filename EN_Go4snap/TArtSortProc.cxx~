// $Id: TArtSortProc.cxx 933 2013-01-29 15:27:58Z linev $
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

#include "TArtSortProc.h"

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"

#include "TGo4WinCond.h"
#include "TGo4PolyCond.h"
#include "TGo4Analysis.h"

#include "TArtSortEvent.h"
#include "TArtUnpackEvent.h"
#include "TArtF2Param.h"
#include "TArtF3Param.h"
#include "segidlist.h"
#include "analysisFlag.h"
#include "EN_PPAC_Cal.h"
#include "ENFiberCal.h"
#include "ENPlastic.h"
#include "EN_CsI.h"
#include "EN_DSSD.h"
#include "EN_Neutron.h"
#include "EN_MWDC.h"
#include "EN_Coin.h"
//-----------------------------------------------------------
TArtSortProc::TArtSortProc() :
   TGo4EventProcessor()
{
}

//-----------------------------------------------------------
TArtSortProc::TArtSortProc(const Char_t* name) :
   TGo4EventProcessor(name) 
{
   TGo4Log::Info("TArtSortProc: Create");
   srand(1000);  
   char filen[30];
   sprintf(filen,"prm/parameters.prm");
   readParameters(filen);

   readmapfile(mapfile,ExpDetRaw,ExpNumDets);
   readHist1(hstfile,hist1, nhst1,hist2, nhst2, gate1, ngate1, gate2, ngate2);
   MakeGate(gate1, ngate1, gate2, ngate2);


   //// init user analysis objects:

 //  fF2Param = (TArtF2Param*)
 //    MakeParameter("F2Param","TArtF2Param","set_F2Par.C");

   // 28052014 TETSUYA ADD
 //  fF3Param = (TArtF3Param*) 
 //    MakeParameter("F3Param","TArtF3Param","set_F3Par.C");

  if (analist[1]==1) fiber = new ENFiberCal(fiberprmfile);
  if (analist[2]==1) ppac = new EN_PPAC_Cal(ppacprmfile); 
  if (analist[3]==1) plastic = new ENPlastic();
  if (analist[4]==1) csi = new EN_CsI();
  if (analist[5]==1) neutron = new EN_Neutron();
  if (analist[6]==1) coin = new EN_Coin();
  if (analist[7]==1) mwdc = new EN_MWDC();
  if (analist[8]==1) dssd = new EN_DSSD();

  if (showrawdata == 1 ) RawDataMakeHist();

}
//-----------------------------------------------------------
TArtSortProc::~TArtSortProc()
{
   TGo4Log::Info("TArtSortProc: Delete");
   // if (fWinCon) fWinCon->PrintCondition(true);
 
}

//-----------------------------------------------------------
Bool_t TArtSortProc::BuildEvent(TGo4EventElement* dest)
{
   Bool_t isValid=kFALSE; // validity of output event

   TArtUnpackEvent* inp_evt  = (TArtUnpackEvent*) GetInputEvent();
   TArtSortEvent* out_evt = (TArtSortEvent*) dest;

   // see comments in UnpackProc
   if((inp_evt==0) || !inp_evt->IsValid()){ // input invalid
      out_evt->SetValid(isValid); // invalid
      return isValid; // must be same is for SetValid
   }
   isValid=kTRUE;
  
// For Beam line detector   
// End for Beam line detector

// For user Exp detector  
   RawDataAssign(inp_evt);
 
   if (showrawdata == 1 ) RawDataFillHist(out_evt);
   //
   if (analist[2]==1) ppac->ENcode(rawdt,valnaok,4);
   if (analist[1]==1) fiber->ENcode(rawdt,valnaok,4);
   if (analist[3]==1) plastic->ENcode(rawdt,valnaok,4);
   if (analist[4]==1) csi->ENcode(rawdt,valnaok,4);
   if (analist[5]==1) neutron->ENcode(rawdt,valnaok,4);
   if (analist[6]==1) coin->ENcode(rawdt,valnaok,4);
   if (analist[7]==1) mwdc->ENcode(rawdt,valnaok,4);
   if (analist[8]==1) dssd->ENcode(rawdt,valnaok,4);

   fillHist1(hist1, nhst1,hist2, nhst2);
   // see comments in UnpackProc Yassid

   out_evt->SetValid(isValid);
   return isValid;
}
//*****************************************************************
Int_t TArtSortProc::MakeGate(hst1* gate1, Int_t ng1, hst2* gate2, Int_t ng2){
   char name[20];
   for (int i=0;i<ng2;i++){
   	Double_t pidp[4][2]={{gate2[i].min1,gate2[i].max2},{gate2[i].max1,gate2[i].max2},
			     {gate2[i].max1,gate2[i].min2},{gate2[i].min1,gate2[i].min2}};
	sprintf(name,"gate2_%d",gate2[i].gate);
	gate[gate2[i].gate] = MakePolyCond(name,4,pidp,gate2[i].name);
   }
   return 0;
}
//*****************************************************************
Int_t TArtSortProc::fillHist1(hst1* histo, Int_t numch, hst2* histo2, Int_t numch2){
   
	for (int i=0 ; i<numch;i++) {
	     if (analist[2]==1 && histo[i].anal==2 && histo[i].seg==10 ){ 
		for (int j=0;j<100;j++){
		    double dz = -500 + 2000.0*rand()/RAND_MAX;
		    if (histo[i].num==1) histo[i].hHist1->Fill(dz);
		    if (histo[i].num==2) histo[i].hHist1->Fill(ppac->GetF2ExtrapolationX(dz));
                    if (histo[i].num==3) histo[i].hHist1->Fill(ppac->GetF2ExtrapolationY(dz));
                    if (histo[i].num==4) histo[i].hHist1->Fill(dz);
		    if (histo[i].num==5) histo[i].hHist1->Fill(ppac->GetF3ExtrapolationX(dz));
                    if (histo[i].num==6) histo[i].hHist1->Fill(ppac->GetF3ExtrapolationY(dz));			
		}
              }else histo[i].hHist1->Fill(valnaok[histo[i].anal][histo[i].seg][histo[i].num]);
        }


        for (int i=0 ; i<numch2;i++) {
 	    if (histo2[i].gate==0){
		if (analist[2]==1 && histo2[i].anal1==2 && histo2[i].seg1==10 &&
				     histo2[i].anal2==2 && histo2[i].seg2==10){ 
		  for (int j=0;j<100;j++){
		    double dz = -500 + 2000.0*rand()/RAND_MAX;
		    if (histo2[i].num1==1 && histo2[i].num2==2) histo2[i].hHist2->Fill(dz,ppac->GetF2ExtrapolationX(dz));
		    if (histo2[i].num1==2 && histo2[i].num2==1) histo2[i].hHist2->Fill(ppac->GetF2ExtrapolationX(dz),dz);
		    if (histo2[i].num1==1 && histo2[i].num2==3) histo2[i].hHist2->Fill(dz,ppac->GetF2ExtrapolationY(dz));
		    if (histo2[i].num1==3 && histo2[i].num2==1) histo2[i].hHist2->Fill(ppac->GetF2ExtrapolationY(dz),dz);
		    if (histo2[i].num1==2 && histo2[i].num2==3) histo2[i].hHist2->Fill(ppac->GetF2ExtrapolationX(dz),ppac->GetF2ExtrapolationY(dz));
		    if (histo2[i].num1==3 && histo2[i].num2==2) histo2[i].hHist2->Fill(ppac->GetF2ExtrapolationY(dz),ppac->GetF2ExtrapolationX(dz));
		
		    if (histo2[i].num1==4 && histo2[i].num2==5) histo2[i].hHist2->Fill(dz,ppac->GetF3ExtrapolationX(dz));
		    if (histo2[i].num1==5 && histo2[i].num2==4) histo2[i].hHist2->Fill(ppac->GetF3ExtrapolationX(dz),dz);
		    if (histo2[i].num1==4 && histo2[i].num2==6) histo2[i].hHist2->Fill(dz,ppac->GetF3ExtrapolationY(dz));
		    if (histo2[i].num1==6 && histo2[i].num2==4) histo2[i].hHist2->Fill(ppac->GetF3ExtrapolationY(dz),dz);
		    if (histo2[i].num1==5 && histo2[i].num2==6) histo2[i].hHist2->Fill(ppac->GetF3ExtrapolationX(dz),ppac->GetF3ExtrapolationY(dz));
		    if (histo2[i].num1==6 && histo2[i].num2==5) histo2[i].hHist2->Fill(ppac->GetF3ExtrapolationY(dz),ppac->GetF3ExtrapolationX(dz));
                  }	
		}else if (analist[7]==1 && histo2[i].anal1==7 && histo2[i].seg1==10 &&
				     histo2[i].anal2==7 && histo2[i].seg2==10){ 
		  for (int j=0;j<100;j++){
		    double dz = -500 + 2000.0*rand()/RAND_MAX;
		    if (histo2[i].num1==1 && histo2[i].num2==2) histo2[i].hHist2->Fill(dz,mwdc->GetExtrapolationX(dz));
		    if (histo2[i].num1==2 && histo2[i].num2==1) histo2[i].hHist2->Fill(mwdc->GetExtrapolationX(dz),dz);
		    if (histo2[i].num1==1 && histo2[i].num2==3) histo2[i].hHist2->Fill(dz,mwdc->GetExtrapolationY(dz));
		    if (histo2[i].num1==3 && histo2[i].num2==1) histo2[i].hHist2->Fill(mwdc->GetExtrapolationY(dz),dz);
		    if (histo2[i].num1==2 && histo2[i].num2==3) histo2[i].hHist2->Fill(mwdc->GetExtrapolationX(dz),mwdc->GetExtrapolationY(dz));
		    if (histo2[i].num1==3 && histo2[i].num2==2) histo2[i].hHist2->Fill(mwdc->GetExtrapolationY(dz),mwdc->GetExtrapolationX(dz));
                  }	
		}else histo2[i].hHist2->Fill(valnaok[histo2[i].anal1][histo2[i].seg1][histo2[i].num1],
 		 		             valnaok[histo2[i].anal2][histo2[i].seg2][histo2[i].num2]);

            }else {
                for (int j=0;j<ngate2;j++){
		    if (gate2[j].gate ==histo2[i].gate){
                        if (gate[gate2[j].gate]->Test(valnaok[gate2[j].anal1][gate2[j].seg1][gate2[j].num1],
						      valnaok[gate2[j].anal2][gate2[j].seg2][gate2[j].num2])){
                            if (analist[2]==1 && histo2[i].anal1==2 && histo2[i].seg1==10 &&
				     histo2[i].anal2==2 && histo2[i].seg2==10){ 
				for (int j=0;j<100;j++){
		    		   double dz = -500 + 2000.0*rand()/RAND_MAX;
		    		   if (histo2[i].num1==1 && histo2[i].num2==2) histo2[i].hHist2->Fill(dz,ppac->GetF2ExtrapolationX(dz));
		    		   if (histo2[i].num1==2 && histo2[i].num2==1) histo2[i].hHist2->Fill(ppac->GetF2ExtrapolationX(dz),dz);
		    		   if (histo2[i].num1==1 && histo2[i].num2==3) histo2[i].hHist2->Fill(dz,ppac->GetF2ExtrapolationY(dz));
		    		   if (histo2[i].num1==3 && histo2[i].num2==1) histo2[i].hHist2->Fill(ppac->GetF2ExtrapolationY(dz),dz);
		    		   if (histo2[i].num1==2 && histo2[i].num2==3) histo2[i].hHist2->Fill(ppac->GetF2ExtrapolationX(dz),ppac->GetF2ExtrapolationY(dz));
		   		   if (histo2[i].num1==3 && histo2[i].num2==2) histo2[i].hHist2->Fill(ppac->GetF2ExtrapolationY(dz),ppac->GetF2ExtrapolationX(dz));
		
		    		   if (histo2[i].num1==4 && histo2[i].num2==5) histo2[i].hHist2->Fill(dz,ppac->GetF3ExtrapolationX(dz));
		    		   if (histo2[i].num1==5 && histo2[i].num2==4) histo2[i].hHist2->Fill(ppac->GetF3ExtrapolationX(dz),dz);
		    		   if (histo2[i].num1==4 && histo2[i].num2==6) histo2[i].hHist2->Fill(dz,ppac->GetF3ExtrapolationY(dz));
		    		   if (histo2[i].num1==6 && histo2[i].num2==4) histo2[i].hHist2->Fill(ppac->GetF3ExtrapolationY(dz),dz);
		    		   if (histo2[i].num1==5 && histo2[i].num2==6) histo2[i].hHist2->Fill(ppac->GetF3ExtrapolationX(dz),ppac->GetF3ExtrapolationY(dz));
		    		   if (histo2[i].num1==6 && histo2[i].num2==5) histo2[i].hHist2->Fill(ppac->GetF3ExtrapolationY(dz),ppac->GetF3ExtrapolationX(dz));	
			        }
			    }else if (analist[7]==1 && histo2[i].anal1==7 && histo2[i].seg1==10 &&
				     histo2[i].anal2==7 && histo2[i].seg2==10){ 
				  for (int j=0;j<100;j++){
				    double dz = -500 + 2000.0*rand()/RAND_MAX;
				    if (histo2[i].num1==1 && histo2[i].num2==2) histo2[i].hHist2->Fill(dz,mwdc->GetExtrapolationX(dz));
		   		    if (histo2[i].num1==2 && histo2[i].num2==1) histo2[i].hHist2->Fill(mwdc->GetExtrapolationX(dz),dz);
		   		    if (histo2[i].num1==1 && histo2[i].num2==3) histo2[i].hHist2->Fill(dz,mwdc->GetExtrapolationY(dz));
		    		    if (histo2[i].num1==3 && histo2[i].num2==1) histo2[i].hHist2->Fill(mwdc->GetExtrapolationY(dz),dz);
		    		    if (histo2[i].num1==2 && histo2[i].num2==3) histo2[i].hHist2->Fill(mwdc->GetExtrapolationX(dz),mwdc->GetExtrapolationY(dz));
		    		    if (histo2[i].num1==3 && histo2[i].num2==2) histo2[i].hHist2->Fill(mwdc->GetExtrapolationY(dz),mwdc->GetExtrapolationX(dz));
				  }
                  	    }else 	 
			            histo2[i].hHist2->Fill(valnaok[histo2[i].anal1][histo2[i].seg1][histo2[i].num1],
							    valnaok[histo2[i].anal2][histo2[i].seg2][histo2[i].num2]);
 			    break;	
			}  
 		    }	
		}
 	    }
	} 
    return 0;
}

//*****************************************************************
Int_t TArtSortProc::RawDataMakeHist(){
  
  Char_t fullname[250],histoname[50];
  for (Int_t i=0;i<ExpNumDets;i++) {
      if (strcmp(ExpDetRaw[i].name,ExpDetRaw[i].namech)==0) sprintf(fullname,"Raw/%s",ExpDetRaw[i].name);
      else sprintf(fullname,"Raw/%s/%s",ExpDetRaw[i].name,ExpDetRaw[i].namech);
      sprintf(histoname,"%s ch#%d",ExpDetRaw[i].name,i);
      if (ExpDetRaw[i].mod==V1190) hExpDet[i] = MakeTH1('F',fullname,histoname, 4096., 0.5, 40960.5);
      else hExpDet[i] = MakeTH1('F',fullname,histoname, 4096., 0.5, 4096.5);
   }
  return 1;
}
//*****************************************************************
Int_t TArtSortProc::RawDataFillHist(TArtSortEvent*){
  for (Int_t i=0;i<ExpNumDets;i++) {
       hExpDet[i]->Fill(ExpDetRaw[i].val);
   } 
   return 1;
}
//*****************************************************************
Int_t TArtSortProc::RawDataAssign(TArtUnpackEvent* inp_evt){
  for (Int_t i = 0;i<ExpNumDets;i++){
    //if(abs(inp_evt->v1190[ExpDetRaw[i].det][121][0]-11800)<1000){//ST
    //V1190refval=inp_evt->v1190[ExpDetRaw[i].det][121][0]-11800;//ST
    //}else{
    //V1190refval=0;
    //}
    if ((ExpDetRaw[i].mod==V1190 || ExpDetRaw[i].mod==AMTTDC) && ExpDetRaw[i].edge==0) ExpDetRaw[i].val= inp_evt->v1190[ExpDetRaw[i].det][ExpDetRaw[i].ch][ExpDetRaw[i].hit] -0* V1190refval;
    else if ((ExpDetRaw[i].mod==V1190 || ExpDetRaw[i].mod==AMTTDC) && ExpDetRaw[i].edge==1) ExpDetRaw[i].val= inp_evt->v1190[ExpDetRaw[i].det][ExpDetRaw[i].ch][ExpDetRaw[i].hit+10] -0* V1190refval;
    //if ((ExpDetRaw[i].mod==V1190 || ExpDetRaw[i].mod==AMTTDC) && ExpDetRaw[i].edge==0) ExpDetRaw[i].val= inp_evt->v1190[ExpDetRaw[i].det][ExpDetRaw[i].ch][ExpDetRaw[i].hit] -1* V1190refval;
    //else if ((ExpDetRaw[i].mod==V1190 || ExpDetRaw[i].mod==AMTTDC) && ExpDetRaw[i].edge==1) ExpDetRaw[i].val= inp_evt->v1190[ExpDetRaw[i].det][ExpDetRaw[i].ch][ExpDetRaw[i].hit+10] -1* V1190refval;
    else ExpDetRaw[i].val= inp_evt->rawdata[ExpDetRaw[i].seg][ExpDetRaw[i].det][ExpDetRaw[i].mod][ExpDetRaw[i].ch];
    
    rawdt[ExpDetRaw[i].cad][ExpDetRaw[i].aid][ExpDetRaw[i].pos] = ExpDetRaw[i].val;
  }
   return 1;
}
//*****************************************************************

//*****************************************************************
Char_t* TArtSortProc::ltrim (Char_t s[])
{
    while (*s == 32) s++;
    return s;
}
//***************************************************************** 
Char_t* TArtSortProc::rtrim (Char_t s[])
{
    Int_t i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
//*****************************************************************
Char_t * TArtSortProc::trim (Char_t s[])
{
    return ltrim(rtrim(s));  
}
//*****************************************************************
Int_t TArtSortProc::Put2Array(Char_t*s,Double_t* val,Int_t nval){
  Int_t nf =0;
  s = trim(s);
  Char_t * pch;
  pch = strtok (s," 	");
  while (pch != NULL && nf<nval)
  {
    val[nf] = atof(pch);
    pch = strtok (NULL, " 	");
    nf++;
  }
  if (pch != NULL) strcpy(s,pch);
  if (nf <nval) return -1;
  return 0;
}
//*****************************************************************
Int_t TArtSortProc::Put2Array(Char_t* s,Int_t* val,Int_t nval){
  Int_t nf =0;
  s = trim(s);
  Char_t * pch;
  pch = strtok (s," 	");
  while (pch != NULL && nf<nval)
  {
    val[nf] = atoi(pch);
    pch = strtok (NULL, " 	");
    nf++;
  }
  if (pch != NULL) strcpy(s,pch);
  if (nf <nval) return -1;
  return 0;
}
//*****************************************************************
Char_t* TArtSortProc::GetNextLine(Char_t s){
   Char_t buffer[1000];
   Char_t* buff; 
//   ifstream fi;
   while (1)
    {
        if (fi.eof()) return NULL;
        buffer[0] = '\0';
        fi.getline(buffer, 1000, '\n');
        buff=trim(buffer);
        if (strlen(buff) > 0)
        {
            if (buff[0] != s)
            {
                return buff;
            }
        }
    }
   return NULL; 
}
//*****************************************************************
Int_t TArtSortProc::readmapfile(Char_t *filename,mapping* map, Int_t& numch){
  Char_t* detname;
  Int_t arr[9]={0}; 
//  ifstream fi;
  fi.open(filename,ios::in);
  if (fi.is_open()){
     Char_t* buff;
     while (!fi.eof()){
       buff = GetNextLine('#');
 //      printf("Get   %s\n",buff);
       if (buff !=NULL){
        if (Put2Array(buff,arr,9)==0){
         detname = buff;
         for (Int_t j=0;j<arr[5];j++){
	    map[numch].cad =  arr[0];
      	    map[numch].aid =  arr[1];
            map[numch].pos =  j;
	    map[numch].seg =  arr[2];
      	    map[numch].det =  arr[3];
            map[numch].mod =  arr[4];
            map[numch].nch =  arr[5];
            map[numch].ch  =  arr[6]+j;
            map[numch].hit =  arr[7];
            map[numch].edge=  arr[8];
            sprintf(map[numch].name,"%s",detname);
            if (arr[5]==1) sprintf(map[numch].namech,"%s",detname);
            else sprintf(map[numch].namech,"%s_%d",detname,j);
//            printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",map[numch].cad,map[numch].seg,map[numch].det,map[numch].mod,map[numch].ch,map[numch].hit,map[numch].edge,map[numch].name);
            numch +=1;
         }
        }else goto lerr;
       }
     }
     fi.close();
     printf("MAPPING-Infor:  Mapping file :\"%s\" with %d  channel(s) |---> LOADED!!!.\n",filename,numch); 
     return 0;
  }else{
     printf("MAPPING-Infor:  Cannot open file :\"%s\" |---> NOT loaded!!!-->STOP now!!!\n",filename);
     return -1;
  }
lerr: printf("MAPPING-Error:  File \"%s\" not correct format |---> NOT loaded!!! --> STOP now!!!\n",filename);
  return -1;
}
//*****************************************************************
//*****************************************************************
Int_t TArtSortProc::readHist1(Char_t *filename, hst1* hist1, Int_t& numh1, hst2* hist2, Int_t& numh2, hst1* gate1, Int_t& ngat1, hst2* gate2, Int_t& ngat2){
  Char_t* detname;
  Char_t ht1[5],ht2[5];
  Double_t arr[13]={0};
  Int_t nowhist = 0; 
  Int_t itemp;
  for (int i=0;i<10;i++) analist[i]=0;
  sprintf(ht1,"%s","hst1");sprintf(ht2,"%s","hst2");
//  ifstream fi;
  fi.open(filename,ios::in);
  if (fi.is_open()){
     Char_t* buff;
     nhst1=0;nhst2=0;ngat1=0;ngat2=0;
     while (!fi.eof()){
       buff = GetNextLine('#');
 //      printf("Get   %s\n",buff);
       if (buff !=NULL){
         if (strcmp(buff,ht1)==0) nowhist = 1;
         else if(strcmp(buff,ht2)==0) nowhist = 2;
         else if(strcmp(buff,"gate1")==0) nowhist = 3;
	 else if(strcmp(buff,"gate2")==0) nowhist = 4;
         else if(strcmp(buff,"raw")==0) nowhist = 5;
         else if(strcmp(buff,"analyser")==0) nowhist = 6;
	 else if(strcmp(buff,"exit")==0) goto rfinish;
         else{
	    if (nowhist == 6) {
		itemp = atoi(buff);
		analist[itemp] = 1;
	    }
            else if (nowhist == 5) showrawdata = atoi(buff);
            else if (nowhist==1){
	       if (Put2Array(buff,arr,7)==0){
           	  detname = buff;
                  hist1[numh1].gate =  arr[0]; 
      	    	  hist1[numh1].anal =  arr[1];
      	    	  hist1[numh1].seg =  arr[2];
      	    	  hist1[numh1].num =  arr[3];
 	    	  hist1[numh1].nbin =  arr[4];
            	  hist1[numh1].min  =  arr[5];
            	  hist1[numh1].max  =  arr[6];
            	  sprintf(hist1[numh1].name,"%s",detname);
            	  sprintf(hist1[numh1].folder,"%s",detname);

            	  hist1[numh1].hHist1 = MakeTH1('F',hist1[numh1].folder,hist1[numh1].name, hist1[numh1].nbin, hist1[numh1].min, hist1[numh1].max);

//            	  printf("%d\t%d\t%d\t%d\t%f\t%f\t%s\n",hist1[numh1].anal,hist1[numh1].seg,hist1[numh1].num,hist1[numh1].nbin,hist1[numh1].min,hist1[numh1].max,hist1[numh1].name);
            	  numh1 +=1;
               }else goto lerr; 
            }
            else if (nowhist==2){
	      if (Put2Array(buff,arr,13)==0){
           	detname = buff;
                hist2[numh2].gate  =  arr[0];
                hist2[numh2].anal1 =  arr[1];
      	    	hist2[numh2].seg1  =  arr[2];
      	    	hist2[numh2].num1  =  arr[3];
 	    	hist2[numh2].anal2 =  arr[4];
      	    	hist2[numh2].seg2  =  arr[5];
      	    	hist2[numh2].num2  =  arr[6];
 	    	hist2[numh2].nbin1 =  arr[7];
            	hist2[numh2].min1  =  arr[8];
            	hist2[numh2].max1  =  arr[9];
		hist2[numh2].nbin2 =  arr[10];
            	hist2[numh2].min2  =  arr[11];
            	hist2[numh2].max2  =  arr[12];
 		sprintf(hist2[numh2].name,"%s",detname);
            	sprintf(hist2[numh2].folder,"%s",detname);

            	hist2[numh2].hHist2 = MakeTH2('F',hist2[numh2].folder,hist2[numh2].name, hist2[numh2].nbin1, hist2[numh2].min1, hist2[numh2].max1,
										   hist2[numh2].nbin2, hist2[numh2].min2, hist2[numh2].max2);
		numh2++;
              }else goto lerr; 
            }
            else if (nowhist==4){
	      if (Put2Array(buff,arr,11)==0){
           	detname = buff;
                gate2[ngat2].gate  =  arr[0];
                gate2[ngat2].anal1 =  arr[1];
      	    	gate2[ngat2].seg1  =  arr[2];
      	    	gate2[ngat2].num1  =  arr[3];
 	    	gate2[ngat2].anal2 =  arr[4];
      	    	gate2[ngat2].seg2  =  arr[5];
      	    	gate2[ngat2].num2  =  arr[6];
// 	    	gate2[ngat2].nbin1 =  arr[6];
            	gate2[ngat2].min1  =  arr[7];
            	gate2[ngat2].max1  =  arr[8];
//		gate2[ngat2].nbin2 =  arr[9];
            	gate2[ngat2].min2  =  arr[9];
            	gate2[ngat2].max2  =  arr[10];
 		sprintf(gate2[ngat2].name,"%s",detname);
            	sprintf(gate2[ngat2].folder,"Hist2/%s",detname);
  	        ngat2++;
              }else goto lerr; 
            }
	 }   
       }else goto lerr;
     }
rfinish:    fi.close();
     printf("HISTO-Infor:  Histogram file :\"%s\" with %d  Histogram 1, %d  histogram2 and %d gate |---> LOADED!!!.\n",filename,numh1,numh2,ngat2);
     return 0;
  }else{
     printf("HISTO-Infor:  Cannot open file :\"%s\" |---> NOT loaded!!!-->STOP now!!!\n",filename);
     return -1;
  }
lerr: printf("HISTO-Error:  File \"%s\" not correct format |---> NOT loaded!!! --> STOP now!!!\n",filename);
  return -1;
}
//*****************************************************************
//*****************************************************************
Int_t TArtSortProc::readParameters(Char_t *filename){
 
  fi.open(filename,ios::in);
  if (fi.is_open()){
     Char_t* buff;
    
       buff = GetNextLine('#');
       if (buff ==NULL) goto lerr;
       sprintf(mapfile,"%s",buff);
 printf("Parameters-Infor:  Parameters file 1:\"%s\"  |---> LOADED!!!.  %s\n",buff,mapfile); 
       buff = GetNextLine('#');
       if (buff ==NULL) goto lerr;
       sprintf(hstfile,"%s",buff);
 printf("Parameters-Infor:  Parameters file 2:\"%s\"  |---> LOADED!!!.  %s\n",buff,hstfile); 
       buff = GetNextLine('#');
       if (buff ==NULL) goto lerr;
       sprintf(fiberprmfile,"%s",buff);
printf("Parameters-Infor:  Parameters file 3:\"%s\"  |---> LOADED!!!.  %s\n",buff,fiberprmfile); 
       buff = GetNextLine('#');
       if (buff ==NULL) goto lerr;
       sprintf(ppacprmfile,"%s",buff);
     fi.close();
     printf("Parameters-Infor:  Parameters file :\"%s\"  |---> LOADED!!!.  %s  %s  %s  %s\n",filename,mapfile,hstfile,fiberprmfile,ppacprmfile); 
     return 0;
  }else{
     printf("Parameters-Infor:  Cannot open file :\"%s\" |---> NOT loaded!!!-->STOP now!!!\n",filename);
     return -1;
  }
lerr: printf("MAPPING-Error:  File \"%s\" not correct format |---> NOT loaded!!! --> STOP now!!!\n",filename);
  return -1;
}

