#include "EN_DSSD.h"

EN_DSSD::EN_DSSD()
{
  analyser=8;
   flagprm = ReadParameters("c");
   printf("EN_DSSD:   Initializing - %d\n", analyser); 
}
EN_DSSD::EN_DSSD(char* filename)
{
  analyser=8;
   flagprm = ReadParameters(filename);
   printf("EN_DSSD:   Initializing - %d\n", analyser); 
}
// ***********************************************************************
EN_DSSD::~EN_DSSD(){}
// ***********************************************************************
void   EN_DSSD::ENcode(int raw[10][10][256], double val[10][10][256], int nval ){

   for (int i=0;i<64;i++){
	XLqraw[i] = raw[analyser][1][i]; XLqraw[i+64] = raw[analyser][1][127-i];
        YLqraw[i] = raw[analyser][2][i]; YLqraw[i+64] = raw[analyser][2][127-i];
        XRqraw[i] = raw[analyser][3][64+i]; XRqraw[i+64] = raw[analyser][3][63-i];
        YRqraw[i] = raw[analyser][4][i]; YRqraw[i+64] = raw[analyser][4][127-i];
  //      traw[i] = raw[analyser][2][i];
   }
   Calibration();
   for (int i=0;i<128;i++){
	val[analyser][1][i+1] = XLqraw[i];
        val[analyser][2][i+1] = YLqraw[i];
        val[analyser][3][i+1] = XRqraw[i];
        val[analyser][4][i+1] = YRqraw[i];
        for (int j=0;j<4;j++) val[analyser][5+j][i+1] = qcal[j][i];
   }
   val[analyser][9][1] =  El_XL;
   val[analyser][9][2] =  El_YL;
   val[analyser][9][3] =  El_XR;
   val[analyser][9][4] =  El_YR;
   val[analyser][9][5] =  posXL;
   val[analyser][9][6] =  posYL;
   val[analyser][9][7] =  posXR;
   val[analyser][9][8] =  posYR;
}

// ***********************************************************************
int EN_DSSD::ReadParameters(char* filename){
  for (int i=0;i<128;i++){
     ch2mev[0][i] =1; offset[0][i] =0; 
     ch2mev[1][i] =1; offset[1][i] =0;
     ch2mev[2][i] =1; offset[2][i] =0;
     ch2mev[3][i] =1; offset[3][i] =0;
  }  
  return 0;
}

// ***********************************************************************
int EN_DSSD::Calibration(){
  for (int i=0;i<128;i++){
     qcal[0][i] = XLqraw[i]*ch2mev[0][i] - offset[0][i]; 
     qcal[1][i] = YLqraw[i]*ch2mev[1][i] - offset[1][i];
     qcal[2][i] = XRqraw[i]*ch2mev[2][i] - offset[2][i];
     qcal[3][i] = YRqraw[i]*ch2mev[3][i] - offset[3][i];
  } 
   posXL=-100;posYL=-100;posXR=-100;posYR=-100;
   El_XL=-100;El_YL=-100;El_XR=-100;El_YR=-100;
   for (int i=0;i<128;i++){
     if (qcal[0][i]>El_XL){ El_XL = qcal[0][i]; posXL=i+1;} 
     if (qcal[1][i]>El_YL){ El_YL = qcal[1][i]; posYL=i+1;} 
     if (qcal[2][i]>El_XR){ El_XR = qcal[2][i]; posXR=i+1;} 
     if (qcal[3][i]>El_XL){ El_YR = qcal[3][i]; posYR=i+1;} 
   }
  return 0;
}

// ***********************************************************************
char* EN_DSSD::ltrim (char s[])
{
    while (*s == 32) s++;
    return s;
}
// *********************************************************************** 
char* EN_DSSD::rtrim (char s[])
{
    int i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
// ***********************************************************************
char * EN_DSSD::trim (char s[])
{
    return ltrim(rtrim(s));  
}
// ***********************************************************************
int EN_DSSD::Put2Array(char*s,double* val,int nval){
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
int EN_DSSD::Put2Array(char* s,int* val,int nval){
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
char* EN_DSSD::GetNextLine(char s){
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
