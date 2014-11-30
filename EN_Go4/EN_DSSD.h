#ifndef EN_DSSD_H
#define EN_DSSD_H

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

class EN_DSSD{
 private:

   double ch2mev[4][128];
   double offset[4][128];
   double posXL,posYL,posXR,posYR;
   double El_XL,El_YL,El_XR,El_YR;
   int qcal[4][128];
   int XLqraw[128],YLqraw[128],XRqraw[128],YRqraw[128];
   int flagprm;
   char* GetNextLine(char s ='#' );
   int Put2Array(char*, int*,int);
   int Put2Array(char*, double*,int);
   char* ltrim(char*);
   char* rtrim(char*);
   char* trim(char*);
   ifstream fi;
 public:
  EN_DSSD();
  EN_DSSD(char* filename);
  ~EN_DSSD(); 
  void ENcode(int raw[10][10][256], double val[10][10][256], int nval );
  int Calibration();
  int ReadParameters(char* filename);
  int analyser;

};
#endif
