#include "ENPlastic.h"

ENPlastic::ENPlastic()
{
  
  analyser=3;
}
ENPlastic::ENPlastic(char* filename)
{
 
  analyser=3;
}
// ***********************************************************************
ENPlastic::~ENPlastic(){}
// ***********************************************************************
void   ENPlastic::ENcode(int raw[10][10][256], double val[10][10][256], int nval ){
   double tref;
   RF = raw[analyser][3][0];
   Ref= raw[analyser][4][0];
   tref=Ref-20200;
   F1PL_T = raw[analyser][8][0]-tref;F1PL_Q = raw[analyser][7][0];
//    int F2PL_T,F2PL_Q;
   F2DPL_LT = raw[analyser][1][0]-tref;F2DPL_LQ = raw[analyser][2][0];
   F2DPL_RT = raw[analyser][1][1]-tref;F2DPL_RQ = raw[analyser][2][1];
   
   F3PL_LT = raw[analyser][1][2]-tref;F3PL_LQ = raw[analyser][2][2];
   F3PL_RT = raw[analyser][1][3]-tref;F3PL_RQ = raw[analyser][2][3];
   
   F3DPL_LT = raw[analyser][1][4]-tref;F3DPL_LQ = raw[analyser][2][4];
   F3DPL_RT = raw[analyser][1][5]-tref;F3DPL_RQ = raw[analyser][2][5];

   val[analyser][1][1] = RF-tref;
   val[analyser][1][2] = Ref-tref;
   val[analyser][1][3] = F1PL_T;
   val[analyser][1][4] = F2PL_T;
   val[analyser][1][5] = F2DPL_LT;
   val[analyser][1][6] = F2DPL_RT; 
   val[analyser][1][7] = F3PL_LT;
   val[analyser][1][8] = F3PL_RT;     
   val[analyser][1][9] = F3DPL_LT;
   val[analyser][1][10] = F3DPL_RT; 
   
//   val[analyser][1][1] = RF;
//   val[analyser][1][2] = Ref;
   val[analyser][2][3] = F1PL_Q;
   val[analyser][2][4] = F2PL_Q;
   val[analyser][2][3] = F2DPL_LQ;
   val[analyser][2][4] = F2DPL_RQ; 
   val[analyser][2][5] = F3PL_LQ;
   val[analyser][2][6] = F3PL_RQ;     
   val[analyser][2][7] = F3DPL_LQ;
   val[analyser][2][8] = F3DPL_RQ; 
   
   val[analyser][3][1] = sqrt(F2DPL_LQ*F2DPL_RQ);
   val[analyser][3][2] = sqrt(F3PL_LQ*F3PL_RQ);  
   val[analyser][3][3] = sqrt(F3DPL_LQ*F3DPL_RQ); 
}

// ***********************************************************************
int ENPlastic::ReadParameters(char* filename){
   
  return -1;
}

// ***********************************************************************
char* ENPlastic::ltrim (char s[])
{
    while (*s == 32) s++;
    return s;
}
// *********************************************************************** 
char* ENPlastic::rtrim (char s[])
{
    int i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
// ***********************************************************************
char * ENPlastic::trim (char s[])
{
    return ltrim(rtrim(s));  
}
// ***********************************************************************
int ENPlastic::Put2Array(char*s,double* val,int nval){
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
  if (nf<nval) return -1;
  return 0;
}
// ***********************************************************************
int ENPlastic::Put2Array(char* s,int* val,int nval){
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
  if (nf<nval) return -1;
  return 0;
}
// ***********************************************************************
char* ENPlastic::GetNextLine(char s){
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
// ***********************************************************************
