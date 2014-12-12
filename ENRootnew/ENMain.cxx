 /******************************************************************
  ***                     ENRoot                                 ***
  ***  Dedicated framework to analyze RCNP EN Course Experiments ***
  ***  Developers: Y. Ayyad (yassid.ayyad@rcnp.osaka-u.ac.jp)    ***
  ***              T.D.Trong (tdtrong@rcnp.osaka-u.ac.jp)        ***
  ******************************************************************/


#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>

#include <vector>
#include "TROOT.h"
#include "ENMain.h"
#include "../EN_Go4/EN_PPAC_Cal.h"
#include "../EN_Go4/ENFiberCal.h"
#include "../EN_Go4/ENPlastic.h"
#include "../EN_Go4/EN_CsI.h"
#include "../EN_Go4/EN_DSSD.h"
#include "../EN_Go4/EN_Neutron.h"
#include "../EN_Go4/EN_MWDC.h"
#include "../EN_Go4/EN_Coin.h"
#ifdef __MAKECINT__
#pragma link C++ class vector<int>+;
#endif

using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
char* ltrim (char s[])
{
    while (*s == 32) s++;
    return s;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
char* rtrim (char s[])
{
    int i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
char * trim (char s[])
{
    return ltrim(rtrim(s));  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int Put2Array(char*s,double* val,int nval){
  int nf =0;
  s = trim(s);
  char * pch;
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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int Put2Array(char* s,int* val,int nval){
  int nf =0;
  s = trim(s);
  char * pch;
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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
char* GetNextLine(char s){
   char buffer[1000];
   char* buff; 
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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int readmapfile(char *filename,mapping* map, int& numch){
  Char_t* detname;
  Int_t arr[9]={0}; 
//  ifstream fi;
  fi.open(filename,ios::in);
  if (fi.is_open()){
     Char_t* buff;
     while (!fi.eof()){
       buff = GetNextLine('#');
 //      printf("Get\t%s\n",buff);
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
Int_t readHist1(Char_t *filename, hst1* hist1, Int_t& numh1,Int_t* analist){
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
     nhst1=0;
     while (!fi.eof()){
       buff = GetNextLine('#');
       //   printf("Get   %s\n",buff);
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

		  //	  hist1[numh1].hHist1 = MakeTH1('F',hist1[numh1].folder,hist1[numh1].name, hist1[numh1].nbin, hist1[numh1].min, hist1[numh1].max);

		  // 	  printf("%d\t%d\t%d\t%d\t%d\t%f\t%f\t%s\n",numh1,hist1[numh1].anal,hist1[numh1].seg,hist1[numh1].num,hist1[numh1].nbin,hist1[numh1].min,hist1[numh1].max,hist1[numh1].name);
            	  numh1 +=1;
               }else goto lerr; 
            }
            else if (nowhist==2){
	      if (Put2Array(buff,arr,13)==0){
           
              }else goto lerr; 
            }
            else if (nowhist==4){
	      if (Put2Array(buff,arr,11)==0){
           
              }else goto lerr; 
            }
	 }   
       }else goto lerr;
     }
rfinish:    fi.close();
     printf("HISTO-Infor:  Histogram file :\"%s\" with %d  Histogram 1, %d  histogram2 and %d gate |---> LOADED!!!.\n",filename,numh1,0,0);
     return 0;
  }else{
     printf("HISTO-Infor:  Cannot open file :\"%s\" |---> NOT loaded!!!-->STOP now!!!\n",filename);
     return -1;
  }
lerr: printf("HISTO-Error:  File \"%s\" not correct format |---> NOT loaded!!! --> STOP now!!!\n",filename);
  return -1;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int read_int_prm(char *filename){
  fi.open(filename,ios::in);
  if (fi.is_open()){
     char* buff;
     buff = GetNextLine('#');if (buff ==NULL) goto lerr;
     rootsaveflag=atoi(buff);
     buff = GetNextLine('#');if (buff ==NULL) goto lerr;
     rootonefile=atoi(buff);
     buff = GetNextLine('#');if (buff ==NULL) goto lerr;
     txtsaveflag=atoi(buff);
     buff = GetNextLine('#');if (buff ==NULL) goto lerr;
     nmaxevt=atoi(buff);
     buff = GetNextLine('#');if (buff ==NULL) goto lerr;
     rawpath=buff;
     buff = GetNextLine('#');if (buff ==NULL) goto lerr;
     memcpy(runname,buff,sizeof(runname));
     buff = GetNextLine('#');if (buff ==NULL) goto lerr;
     rootpath=buff;
     buff = GetNextLine('#');if (buff ==NULL) goto lerr;
     txtpath=buff;
     fi.close();
     printf(" ENCovert-Infor:  Initial file :\"%s\" with %d  channel(s) |---> LOADED!!!.\n",filename,0); 
     return 0;
  }else{
     printf(" ENCovert-Infor:  Cannot open file :\"%s\" |---> NOT loaded!!!-->STOP now!!!\n",filename);
     return -1;
  }
lerr: printf(" ENCovert-Error:  File \"%s\" not correct format |---> NOT loaded!!! --> STOP now!!!\n",filename);
  return -1;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int main(int argc, char **argv)
{
  
//  gSystem->AddIncludePath("-I$TARTSYS/include/");
//  gSystem->Load("libanacore.so");
//  gSystem->Load("ENMain_cxx.so");
//  gROOT->ProcessLine(".L ENMain.cxx+");  
  
  std::stringstream  finss;   
  std::stringstream  foutss;   
  cout<<argc<<endl;
  int nstop,nstart;
  nstop=0;
  nstart=0;
  if(argc==1){
    nstart=29;
    nstop=228;
    cout<<" ENCovert-Infor:  Input START run number and STOP run number: ";
    cin>>nstart>>nstop;   
    if (nstop<nstart) cout<<" ENCovert-Infor:   Input run START larger than STOP, Program stop now."<<endl; 
  }
  else if(argc==2){
    finss<<argv[1];
    foutss<<argv[1];
  }
  
  else if(argc==3){
    finss<<argv[1];
    foutss<<argv[2];
  }
  
  else {
    cout<<argc<<endl;
    cout<<"***********   Input param is wrong ***********"<<endl;
    cout<<"If you use the same name for the input and output files:"<<endl;
    cout<<"    ex) ./ENMain inputfilename [ENTER]"<<endl;
    cout<<"Otherwise: "<<endl;
    cout<<"    ex) ./ENMain inputfilename  outputfilename [ENTER]"<<endl;
    return -1;
  }
  rawpath  = "./ridf/";  
  rootpath = "rootfiles/";
  txtpath  = "txtfiles/";
//  runname  = "e428_run"; 
  TString       ridfext  = ".ridf";
  TString       rootext  = ".root";
  TString	txtext   = ".txt"; 
  char prmfile[20]="readme.txt";
  if (read_int_prm(prmfile)==-1) return-1;
  if (rootsaveflag==0 && txtsaveflag==0){
    printf("\n ENCovert-Infor: No output file (ROOT or TXT) required, Programe will STOP now !!!\n\n");return -1;
  }
  char treename[20];
  sprintf(treename,"../map/mapping.map");
  if (readmapfile(treename,ExpDetRaw, ExpNumDets)==-1) return -1;
  sprintf(treename,"histconvert.hist");
  if (readHist1(treename,hist1, nhst1,analist)==-1) return -1;
//  printf("ENMain:   Khong doc dc prm file\n");
  sprintf(treename,"../EN_Go4/prm/fiber.prm");
  if (analist[1]==1) fiber = new ENFiberCal(treename);
  sprintf(treename,"../EN_Go4/prm/ppac.prm");
  if (analist[2]==1) ppac = new EN_PPAC_Cal(treename); 
  if (analist[3]==1) plastic = new ENPlastic();
  if (analist[4]==1) csi = new EN_CsI();
  if (analist[5]==1) neutron = new EN_Neutron();
  if (analist[6]==1) coin = new EN_Coin();
  sprintf(treename,"../EN_Go4/prm/mwdc_y.prm");
  if (analist[7]==1) mwdc = new EN_MWDC(treename);
  sprintf(treename,"../EN_Go4/prm/dssd.prm");
  if (analist[8]==1) dssd = new EN_DSSD(treename);


  string        ridffilename;  
  string        rootfilename;
  string fins,fouts;  
  fins=finss.str();fouts=foutss.str();
  if (nstop>nstart) cout<<endl<< " ENCovert-Infor:   Now starting to convert from run  "<<nstart<<"  to run "<<nstop<<endl; 

   // PREPARE INPUT FILE NAME   
  TFile	*file=0;
  TTree	*E372=0;
  TTree	*rawt=0;
  int aux_i=0;
  int aux_filenum=0;
  double ntotal =0.;
  ofstream *outtxt =0;

for (int ifile=nstart;ifile<=nstop;ifile++){

        
//  cout<<fins<<" o "<<fouts<<endl;
  if (nstart>= nstop){
    ridffilename = rawpath + finss.str() + ridfext;
    rootfilename = rootpath + foutss.str() + rootext;
    cout<<"**** Note: You can convert multi file by run \"./ENConvert\". "<<endl<<endl;
  }
  else {
     char tbuff[100]="0";
     if(ifile<10) sprintf(tbuff,"%s000%d",runname,ifile);
     else if(ifile<100) sprintf(tbuff,"%s00%d",runname,ifile);
     else if(ifile<1000) sprintf(tbuff,"%s0%d",runname,ifile);
     else sprintf(tbuff,"%s%d",runname,ifile);
     cout<<" ENCovert-Infor: File  "<<tbuff<<"  is converting, please wait...."<<endl<<endl;
     ridffilename = rawpath + tbuff + ridfext;
     rootfilename = rootpath + tbuff + rootext;
     fins=tbuff;
     fouts=tbuff;
  }
  string foutsbuff;
  foutsbuff=fouts; 
  
  char	*ridffile		= new char[ridffilename.size()+1];
  ridffile[ridffilename.size()]	= 0;
  memcpy(ridffile,ridffilename.c_str(),ridffilename.size());
  
  //  cout<<"ENRoot Analyzing data file: "<<filename<<endl;
  cout<<"ENRoot Analyzing data file: "<<ridffilename.c_str()<<endl;
 
 // gSystem->Load("libXMLParser.so");

//add Jul 9

   if(estore==0) estore	= new TArtEventStore();
   bool flag		= 0;
   flag			= estore->Open(ridffilename.c_str());
   if (!flag){ printf("\n ENCovert-Infor: File \"%s\" not found, Programe will STOP now !!!\n\n",ridffilename.c_str());return -1;}
   rawevent		= estore->GetRawEventObject();

   string        txtfilename;
   string        filenum="_000";
  
  if (rootsaveflag==1 && (rootonefile==0 || ntotal == 0.)){
     file = new TFile(rootfilename.c_str(),"RECREATE");  
     E372 = new TTree("cal","EN raw data convert by T D Trong using ENConvert");
     rawt  = new TTree("raw","EN raw data convert by T D Trong using ENConvert");
     E372->Branch("evtNo",		&nevt,		"evtNo/I");
     for (int i =0;i<nhst1;i++){
        sprintf(treename,"%s/D",hist1[i].name);
        E372->Branch(hist1[i].name, 	&hist1[i].val,	treename); 
     }
     rawt->Branch("evtNo",		&nevt,		"evtNo/I");
     for (int i =0;i<ExpNumDets;i++){
        sprintf(treename,"%s/I",ExpDetRaw[i].namech);
        rawt->Branch(ExpDetRaw[i].namech, 	&ExpDetRaw[i].val,	treename); 
     }
     cout<<endl<<"Created a new ROOT file:  "<<rootfilename.c_str() <<endl<<endl;
  }
  
  txtfilename = txtpath + fouts + filenum + txtext;
// Trong add
  if (txtsaveflag==1){
     outtxt=new ofstream(txtfilename.c_str());
     *outtxt<<"evt	";
     for (int i =0;i<nhst1;i++) *outtxt<<hist1[i].name<<"	";
     *outtxt<<endl; //
     cout<<endl<<endl<<endl<<"********************* Preparing for dump data to TXT file ************************"<<endl;
     cout<<" ENCovert-Infor: Maximum events store in one TXT file: ";	
     cout<<"  ---->  "<<nmaxevt<<"   has ACCEPTED!!!!!"<<endl<<endl<<endl;
     cout<<endl<<"Created a new TXT file:  "<<txtfilename.c_str() <<endl<<endl;
   }
   nevt=0;
   while(estore->GetNextEvent()){
//    Clear();
    for (Int_t i = 0;i<ExpNumDets;i++){
        ExpDetRaw[i].val= 0;
    } 
     for (Int_t i = 0;i<10;i++){
        for (Int_t j = 0;j<10;j++){
            for (Int_t k = 0;k<256;k++){
               rawdt[i][j][k]= 0;
	    }
	}
     }
    for(int i1=0;i1<rawevent->GetNumSeg();i1++){
      seg	      = rawevent->GetSegment(i1);	// get segment
      //      int cadid =	seg->GetDevice();
      int segid =	seg->GetFP();       
      int detid =	seg->GetDetector();             // change 
      int modid =	seg->GetModule();
         // v1190 multi hit handling
      int  mhitl[128]={0};
      int  mhitt[128]={0};
      for(int j=0;j<seg->GetNumData();j++){
	  TArtRawDataObject	*d   = seg->GetData(j);	
	  int			 val = d->GetVal();
	  int			 ch  = d->GetCh();
          int edge = 0;
          if (modid == V1190){ 
	     edge=d->GetEdge(); 
             if(mhitl[ch]<10 && edge==0) mhitl[ch]++; //Leading
             if(mhitt[ch]<10 && edge==1) mhitt[ch]++; //Trailing
          }
	  for (Int_t i = 0;i<ExpNumDets;i++){
            if (ExpDetRaw[i].seg==segid && ExpDetRaw[i].det==detid && ExpDetRaw[i].mod==modid && ExpDetRaw[i].ch==ch && ExpDetRaw[i].edge==edge && (ExpDetRaw[i].hit==mhitl[ch] || ExpDetRaw[i].hit==mhitt[ch])){
	      ExpDetRaw[i].val= val;
	      rawdt[ExpDetRaw[i].cad][ExpDetRaw[i].aid][ExpDetRaw[i].pos] = ExpDetRaw[i].val;
	      break;
	    }
	  } 
       }    //Segments loop	       	
    }//Events loop

    if (analist[2]==1) ppac->ENcode(rawdt,valnaok,4);
    if (analist[1]==1) fiber->ENcode(rawdt,valnaok,4);
    if (analist[3]==1) plastic->ENcode(rawdt,valnaok,4);
    if (analist[4]==1) csi->ENcode(rawdt,valnaok,4);
    if (analist[5]==1) neutron->ENcode(rawdt,valnaok,4);
    if (analist[6]==1) coin->ENcode(rawdt,valnaok,4);
    if (analist[7]==1) mwdc->ENcode(rawdt,valnaok,4);
    if (analist[8]==1) dssd->ENcode(rawdt,valnaok,4);
    nevt++;    
    
    for (int i=0;i<nhst1;i++){
      hist1[i].val=valnaok[hist1[i].anal][hist1[i].seg][hist1[i].num];
    }

    if(nevt%50000==0) cout<<" ENCovert-Infor: Unpacking, Dumping to file, please be patient... Event number: "<<nevt<<endl;            
  /****** Dumping raw data in txt file (Fast and dirty solution)*********************/

    if(txtsaveflag==1){
        if(aux_i>nmaxevt) {
	   //outtxt->close();
           char buff[100]="0";
	   aux_filenum++;
	   if(aux_filenum<10) sprintf(buff,"_00%d",aux_filenum);
           else if(aux_filenum<100) sprintf(buff,"_0%d",aux_filenum);
	   else if(aux_filenum<1000) sprintf(buff,"_%d",aux_filenum);
	   aux_i=0;
	   filenum = buff;
           txtfilename = txtpath + fouts + filenum + txtext;
	   ofstream *outtxt_buff=new ofstream(txtfilename.c_str());
	   //outtxt->open(txtfilename.c_str());
	   outtxt=outtxt_buff;
// Trong add
           *outtxt<<"evt	";
    	   for (int i =0;i<nhst1;i++) *outtxt<<hist1[i].name<<"	";
   	   *outtxt<<endl;
	   cout<<endl<<"Created a new TXT file:  "<<txtfilename.c_str() <<endl<<endl;
//			
        }
      
// Write this event to TXT file
        *outtxt<<nevt<<"	";
        for (int i =0;i<nhst1;i++) *outtxt<<hist1[i].val<<"	";
        *outtxt<<endl;
        aux_i++;		
    } // end txtsaveflag
    if (rootsaveflag==1) {E372->Fill();rawt->Fill();}
    ntotal+=1;
   }// end evt loop

 /***********************************************************/
   if (rootsaveflag==1 && rootonefile==0) {
//   	cout<<" Preparing to write ROOT file"<<endl;
   	E372->Write();//file->Write();
        rawt->Write();
//   	cout<<" Write ROOT file OK"<<endl;
   	file->Close();
//   	cout<<" Close ROOT file OK"<<endl;
   	file->Delete();
//   	cout<<" Delete ROOT file OK"<<endl;
   	cout<<endl<<" ENCovert-Infor: There are  "<<nevt<<"  events fill to ROOT file. Done!!!!"<<endl<<endl;
        ntotal = 0.;
   }
   if (txtsaveflag==1) {
   	cout<<" ENCovert-Infor: There are  "<<nevt<<"  events dump to TXT file. Done!!!!"<<endl<<endl;
        outtxt->close();
   }
}// End loop file
   if (rootsaveflag==1 && rootonefile!=0){
//   	cout<<" Preparing to write ROOT file"<<endl;
   	E372->Write();
        rawt->Write();
//   	cout<<" Write ROOT file OK"<<endl;
   	file->Close();
//   	cout<<" Close ROOT file OK"<<endl;
   	file->Delete();
//   	cout<<" Delete ROOT file OK"<<endl;
	cout<<endl<<" ENCovert-Infor: There are  "<<ntotal<<"  events fill to ROOT file. Done!!!!"<<endl<<endl;
   }
   cout<<" ENCovert-Infor: Convert data has done!!!!. Enjoin :)"<<endl<<endl<<endl;
  return 0;
}
