#ifndef ENOthers_H
#define ENOthers_H

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

class ENOthers{
 private:
   int flagprm;
   char* GetNextLine(char s ='#' );
   int Put2Array(char*, int*,int);
   int Put2Array(char*, double*,int);
   char* ltrim(char*);
   char* rtrim(char*);
   char* trim(char*);
   ifstream fi;
 public:
  ENOthers();
  ENOthers(char* filename);
  ~ENOthers(); 
  void ENcode(int raw[10][10][256], double val[10][10][256], int nval );
  int ReadParameters(char* filename);
  int analyser;

};
#endif
