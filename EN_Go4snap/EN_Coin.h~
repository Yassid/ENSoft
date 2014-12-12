#ifndef ENPlastic_H
#define ENPlastic_H

#include <TH1.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <vector>
//#include "TArtEventStore.hh"
#include "segidlist.h"

using namespace std;

class ENPlastic{
 private:
  
   int RF,Ref;
   int F1PL_T,F1PL_Q;
   int F2PL_T,F2PL_Q;
   int F2DPL_LT,F2DPL_LQ,F2DPL_RT,F2DPL_RQ;
   int F3PL_LT,F3PL_LQ,F3PL_RT,F3PL_RQ;
   int F3DPL_LT,F3DPL_LQ,F3DPL_RT,F3DPL_RQ;


   int flagprm;
   char* GetNextLine(char s ='#' );
   int Put2Array(char*, int*,int);
   int Put2Array(char*, double*,int);
   char* ltrim(char*);
   char* rtrim(char*);
   char* trim(char*);
   ifstream fi;
 public:
  ENPlastic();
  ENPlastic(char* filename);
  ~ENPlastic(); 
  void ENcode(int raw[10][10][256], double val[10][10][256], int nval );
  int ReadParameters(char* filename);
  int analyser;

};
#endif
