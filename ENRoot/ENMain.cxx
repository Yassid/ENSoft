 /******************************************************************
  ***                     ENRoot                                 ***
  ***  Dedicated framework to analyze RCNP EN Course Experiments ***
  ***  Developers: Y. Ayyad (yassid.ayyad@rcnp.osaka-u.ac.jp)    ***
  ***              T. Yamamoto (tetsuya@rcnp.osaka-u.ac.jp)      ***
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
  s = trim(s);  
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
  char* detname;
  int arr[9]={0}; 
//  ifstream fi;
  f1fiberFlag = 0;
  f2ppacFlag = 0;
  f3ppacFlag = 0;
  fi.open(filename,ios::in);
  if (fi.is_open()){
     char* buff;
   //  buff = GetNextLine('#');if (buff ==NULL) goto lerr;
   //  f1fiberFlag=atoi(buff);
  //   buff = GetNextLine('#');if (buff ==NULL) goto lerr;
  //   f2ppacFlag=atoi(buff);
  //   buff = GetNextLine('#');if (buff ==NULL) goto lerr;
  //   f3ppacFlag=atoi(buff);
     numch = 0;
     while (!fi.eof()){
       buff = GetNextLine('#');
 //      printf("Get   %s\n",buff); 
       if (buff !=NULL){
        if (Put2Array(buff,arr,9)==0){
         detname = buff;
          if (arr[0] == 1 && arr[1]==1) {f1fiberFlag=1;f1fiber_ch=numch;}
          if (arr[0] == 2 && arr[1]==1) {f2ppacFlag=1;f2ppac_ch=numch;} 
          if (arr[0] == 2 && arr[1]==2) {f3ppacFlag=1;f3ppac_ch=numch;}
         for (int j=0;j<arr[5];j++){
      	    map[numch].cad =  arr[1];
      	    map[numch].seg =  arr[2];
      	    map[numch].det =  arr[3];
            map[numch].mod =  arr[4];
            map[numch].ch  =  arr[6]+j;
            map[numch].hit =  arr[7];
            map[numch].edge=  arr[8];
            if (arr[5]==1) sprintf(map[numch].name,"%s",detname);
            else sprintf(map[numch].name,"%s_%d",detname,j);
//            printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",map[numch].cad,map[numch].seg,map[numch].det,map[numch].mod,map[numch].ch,map[numch].hit,map[numch].edge,map[numch].name);
            numch +=1;
         }
        }else goto lerr;
       }
     }
     fi.close();
     printf("MAPPING-Infor:  Mapping file :\"%s\" with %d  channel(s) %d   %d   %d|---> LOADED!!!.\n",filename,numch,f1fiber_ch,f2ppac_ch,f3ppac_ch); 
     return 0;
  }else{
     printf("MAPPING-Infor:  Cannot open file :\"%s\" |---> NOT loaded!!!-->STOP now!!!\n",filename);
     return -1;
  }
lerr: printf("MAPPING-Error:  File \"%s\" not correct format |---> NOT loaded!!! --> STOP now!!!\n",filename);
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
     printf(" ENCovert-Infor:  Initial file :\"%s\" with %d  channel(s) |---> LOADED!!!.\n",filename,numch); 
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
  if (readmapfile(treename,ENraw, numch)==-1) return -1;
//  printf("ENMain:   Khong doc dc prm file\n");
  sprintf(treename,"../EN_Go4/prm/fiber.prm");
  fiber = new ENFiberCal(treename);
  sprintf(treename,"../EN_Go4/prm/ppac.prm");
  ppac = new EN_PPAC_Cal(treename); 

  string        ridffilename;  
  string        rootfilename;
  string fins,fouts;  
  fins=finss.str();fouts=foutss.str();
  if (nstop>nstart) cout<<endl<< " ENCovert-Infor:   Now starting to convert from run  "<<nstart<<"  to run "<<nstop<<endl; 

   // PREPARE INPUT FILE NAME   
  TFile	*file=0;
  TTree	*E372=0;
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
     E372 = new TTree("ENrawtree","EN raw data convert by T D Trong using ENConvert");
     E372->Branch("evtNo",		&nevt,		"evtNo/I");
     if (f1fiberFlag==1){
        E372->Branch("F1FiberX", 	&F1Fiber_X,	"F1FiberX/F");
        E372->Branch("F1FiberY", 	&F1Fiber_Y,	"F1FiberY/F");
        E372->Branch("F1FiberW", 	&F1Fiber_W,	"F1FiberW/F");
     }
     if (f2ppacFlag==1){
        E372->Branch("F2UPPACX", 	&F2UPPAC_X,	"F2UPPACX/F");
        E372->Branch("F2UPPACY", 	&F2UPPAC_Y,	"F2UPPACY/F");
        E372->Branch("F2DPPACX", 	&F2DPPAC_X,	"F2DPPACX/F");
        E372->Branch("F2DPPACY", 	&F2DPPAC_Y,	"F2DPPACY/F");
     }
     if (f3ppacFlag==1){
        E372->Branch("F3UPPACX", 	&F3UPPAC_X,	"F3UPPACX/F");
        E372->Branch("F3UPPACY", 	&F3UPPAC_Y,	"F3UPPACY/F");
        E372->Branch("F3DPPACX", 	&F3DPPAC_X,	"F3DPPACX/F");
        E372->Branch("F3DPPACY", 	&F3DPPAC_Y,	"F3DPPACY/F");
     }
     for (int i =0;i<numch;i++){
        sprintf(treename,"%s/F",ENraw[i].name);
        E372->Branch(ENraw[i].name, 	&ENraw[i].val,	treename); 
     }
     cout<<endl<<"Created a new ROOT file:  "<<rootfilename.c_str() <<endl<<endl;
  }
  
  txtfilename = txtpath + fouts + filenum + txtext;
// Trong add
  if (txtsaveflag==1){
     outtxt=new ofstream(txtfilename.c_str());
     *outtxt<<"evt	";
     if (f1fiberFlag==1) *outtxt<<"F1FiberX	F1FiberY	F1FiberWidth	";
     if (f2ppacFlag ==1) *outtxt<<"F2UPPACX	F2UPPACY	F2DPPACX	F2DPPACY	";
     if (f3ppacFlag ==1) *outtxt<<"F3UPPACX	F3UPPACY	F3DPPACX	F3DPPACY	";
     for (int i =0;i<numch;i++) *outtxt<<ENraw[i].name<<"	";
     *outtxt<<endl; //
     cout<<endl<<endl<<endl<<"********************* Preparing for dump data to TXT file ************************"<<endl;
     cout<<" ENCovert-Infor: Maximum events store in one TXT file: ";	
     cout<<"  ---->  "<<nmaxevt<<"   has ACCEPTED!!!!!"<<endl<<endl<<endl;
     cout<<endl<<"Created a new TXT file:  "<<txtfilename.c_str() <<endl<<endl;
   }
   nevt=0;
   while(estore->GetNextEvent()){
//    Clear();
    for (int i =0;i<numch;i++){
       ENraw[i].val=0;
    } 
    if (f1fiberFlag==1) fiber->Reset();
    for(int i=0;i<rawevent->GetNumSeg();i++){
      seg	      = rawevent->GetSegment(i);	// get segment
      int cadid =	seg->GetDevice();
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
          if (f1fiberFlag==1 && cadid == 5 && segid == fiber->segid &&
              detid == fiber->detid && modid == fiber->modid){
             if(mhitl[ch]==1 && edge==0) fiber->SetLeading(ch,val);
             if(mhitt[ch]==1 && edge==1) fiber->SetTrailing(ch,val);  
          }else
	  for (int j1 = 0;j1< numch;j1++){
	     if (cadid == 5 && segid == ENraw[j1].seg &&
                 detid == ENraw[j1].det && modid == ENraw[j1].mod &&   
                 ch == ENraw[j1].ch ){
                 if (modid == V1190){ 
		    if((mhitl[ch]== ENraw[j1].hit+1 || mhitt[ch]== ENraw[j1].hit+1 ) && edge==ENraw[j1].edge){ 
                       ENraw[j1].val = val;
                       break;
 		    }	
		 }
		 else{
                     ENraw[j1].val = val;
                     break;
                 }
             }
	  } 
       }    //Segments loop	       	
    }//Events loop
    nevt++;    
    if(nevt%50000==0) cout<<" ENCovert-Infor: Unpacking, Dumping to file, please be patient... Event number: "<<nevt<<endl;            
    if (f1fiberFlag==1){
        fiber->SetPosition();
	F1Fiber_X=fiber->GetX_Position();F1Fiber_Y=fiber->GetY_Position();
	F1Fiber_W=fiber->Get_Width();
    }
    if (f2ppacFlag==1){
        int traw[10];
        for (int i=0;i<10;i++) traw[i]= ENraw[i+f2ppac_ch].val;
	ppac->SetPosition(1,0, traw );
        F2UPPAC_X=ppac->GetX_Position(1);F2UPPAC_Y=ppac->GetY_Position(1);
        F2DPPAC_X=ppac->GetX_Position(2);F2DPPAC_Y=ppac->GetY_Position(2);
    }
    if (f3ppacFlag==1){
	int traw[10];
        for (int i=0;i<10;i++) traw[i]= ENraw[i+f3ppac_ch].val;
	ppac->SetPosition(3, 0, traw );
        F3UPPAC_X=ppac->GetX_Position(3);F3UPPAC_Y=ppac->GetY_Position(3);
        F3DPPAC_X=ppac->GetX_Position(4);F3DPPAC_Y=ppac->GetY_Position(4);
    }
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
   	   if (f1fiberFlag==1) *outtxt<<"F1FiberX	F1FiberY	F1FiberWidth	";
           if (f2ppacFlag ==1) *outtxt<<"F2UPPACX	F2UPPACY	F2DPPACX	F2DPPACY	";
       	   if (f3ppacFlag ==1)  *outtxt<<"F3UPPACX	F3UPPACY	F3DPPACX	F3DPPACY	";
      
    	   for (int i =0;i<numch;i++) *outtxt<<ENraw[i].name<<"	";
   	   *outtxt<<endl;
	   cout<<endl<<"Created a new TXT file:  "<<txtfilename.c_str() <<endl<<endl;
//			
        }
      
// Write this event to TXT file
        *outtxt<<nevt<<"	";
        if (f1fiberFlag==1)  *outtxt<<F1Fiber_X<<"	"<<F1Fiber_Y<<"	"<<F1Fiber_W<<"	";
        if (f2ppacFlag ==1)  *outtxt<<F2UPPAC_X<<"	"<<F2UPPAC_Y<<"	"<<F2DPPAC_X<<"	"<<F2DPPAC_Y<<"	";
        if (f3ppacFlag ==1)  *outtxt<<F3UPPAC_X<<"	"<<F3UPPAC_Y<<"	"<<F3DPPAC_X<<"	"<<F3DPPAC_Y<<"	";
        for (int i =0;i<numch;i++) *outtxt<<ENraw[i].val<<"	";
        *outtxt<<endl;
        aux_i++;		
    } // end txtsaveflag
    if (rootsaveflag==1) E372->Fill();
    ntotal+=1;
   }// end evt loop

 /***********************************************************/
   if (rootsaveflag==1 && rootonefile==0) {
//   	cout<<" Preparing to write ROOT file"<<endl;
   	E372->Write();//file->Write();
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
