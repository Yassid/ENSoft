#ifndef ENFiberCal_H
#define ENFiberCal_H

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

class ENFiberCal{
 private:
   int nfire;
   int pos_fire[300],ch_L[300] ,ch_R[300];
   int width_L[300] ,width_R[300];
   int traw[128];
   int trawt[128];
   double tcal[128][2];
   double ch2ns[128];
   double threshold_t;
   double threshold_Y;
   double ns2mm[2];
   double offset[2];
   double posY[305];
   double weiY[305];
   double posX,posY1,width;

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
  ENFiberCal();
  ENFiberCal(char* filename);
  ~ENFiberCal();
  void ENcode(int raw[10][10][256], double val[10][10][256], int nval );
  void SetLeading(int ch, int val){traw[ch] = val;};
  void SetTrailing(int ch, int val){trawt[ch] = val;}; 
  void Reset(int val = 0){
       memset(traw ,val,sizeof(traw));
       memset(trawt,val,sizeof(trawt));};
  int ReadParameters(char* filename);
  void SetPosition();
  void SetPosition1();
  void SetPosition(int,int* );
  double GetX_Position(){return posX;};
  double GetX_Position(int no){return (pos_fire[no] - 150)*ns2mm[0] - offset[0];};
  double GetY_Position(){return posY1;};
  double GetY_Position(int no){return posY[no];};
  double Get_Width(){return width;};
  double Get_Width_L(int i){return width_L[i];};
  double Get_Width_R(int i){return width_R[i];};
  int segid;
  int detid;
  int modid;
};
#endif
