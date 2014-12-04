#ifndef EN_MWDC_H
#define EN_MWDC_H

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

class EN_MWDC{
 private:
   int traw[3][8][17];
   int tfirst[3][8];
   int hitwire[3][8][17],hitwiref[3][8];
   int nhits,nhitbc[3],nhitpl[3][9];
   float pospl[3][9][32],bpospl[3][9];
   double tcal[5][5];
   double ch2ns[5][5];
   double ch2qdc[5][5];
   double qdcped[5][5];
   double ns2mm[5][2];
   double in_offset[5][2];
   double out_offset[5][2];
   double geo_offset[5][2];
   double offset[5][2];
   double posXmm[5],posYmm[5];
   double posXns[5],posYns[5];
   double F2distance,F3distance;
   double aX_mrad,aY_mrad;
   float ywei[3][8][1000];

   int flagprm;
   char* GetNextLine(char s ='#' );
   int Put2Array(char*, int*,int);
   int Put2Array(char*, double*,int);
   char* ltrim(char*);
   char* rtrim(char*);
   char* trim(char*);
   ifstream fi;
 public:
  int analyser;
  EN_MWDC();
  EN_MWDC(char* filename);
  ~EN_MWDC(); 
  void ENcode(int raw[10][10][256], double val[10][10][256], int nval );
  int ReadParameters(char* filename);
  void DataAssign(int raw[10][10][256]);
  void LookupHits();
  void SetPosition();
  double GetX_Time(int no){return posXns[no];};
  double GetY_Time(int no){return posYns[no];};
  double GetX_Position(int no){return posXmm[no];};
  double GetY_Position(int no){return posYmm[no];};
  int GetLinearPar(double XY[][2], int npoint,double *hs);
  double GetF2_aY_mrad();
  double GetF3_aX_mrad();
  double GetF3_aY_mrad();
  double GetF2ExtrapolationX(double atZ);
  double GetF2ExtrapolationY(double atZ);
  double GetF3ExtrapolationX(double atZ);
  double GetF3ExtrapolationY(double atZ);

};
#endif
