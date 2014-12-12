#ifndef EN_Neutron_H
#define EN_Neutron_H

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

class EN_Neutron{
 private:

   int traw[16];
   int qraw[16];

   int flagprm;
   char* GetNextLine(char s ='#' );
   int Put2Array(char*, int*,int);
   int Put2Array(char*, double*,int);
   char* ltrim(char*);
   char* rtrim(char*);
   char* trim(char*);
   ifstream fi;
 public:
  EN_Neutron();
  EN_Neutron(char* filename);
  ~EN_Neutron(); 
  void ENcode(int raw[10][10][256], double val[10][10][256], int nval );
  int ReadParameters(char* filename);
  int analyser;

};
#endif
