#include "EN_CsI.h"

EN_CsI::EN_CsI()
{
  analyser=4;
   printf("EN_CsI:   Initializing - %d\n", analyser); 
}
EN_CsI::EN_CsI(char* filename)
{
  analyser=4;
   printf("EN_CsI:   Initializing - %d\n", analyser); 
}
// ***********************************************************************
EN_CsI::~EN_CsI(){}
// ***********************************************************************
void   EN_CsI::ENcode(int raw[10][10][256], double val[10][10][256], int nval ){

  float calib[32]={
		   1.0557,0.9191,1.0081,1.0068,1.1300,0.9785,0.9781,0.9521
		   ,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00
		   ,35.5,42.3,40.8,36.9,34.7,38.7,40.3,42.8
		   ,35.5,37.7,30.1,24.3,34.4,29.0,32.0,27.0};//ST
  /*
  float calib[32]={1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00
		   ,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00
		   ,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00
		   ,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00};//ST
  */
   for (int i=0;i<16;i++){
	qraw[i] = raw[analyser][1][i];
        traw[i] = raw[analyser][2][i];
   }

   for (int i=0;i<16;i++){
     //val[analyser][1][i+1] = qraw[i];
     val[analyser][1][i+1] = calib[i]*(qraw[i]-calib[i+16]);//ST
     val[analyser][2][i+1] = traw[i];
   }
   
   for (int i=0;i<4;i++){
	val[analyser][1][i+1] = qraw[i];
        val[analyser][2][i+1] = traw[i];
   }
   int CsIE[4];
   for (int i=0;i<4;i++) CsIE[i]=-1;
   for (int i=0;i<4;i++)
     for (int j=0;j<4;j++)
       if(val[analyser][1][4*i+j+1] > CsIE[i]){
	 CsIE[i]=val[analyser][1][4*i+j+1];
	 val[analyser][3][i+1] = CsIE[i];
       }//ST
}
// ***********************************************************************
int EN_CsI::ReadParameters(char* filename){
   
  return -1;
}

// ***********************************************************************
char* EN_CsI::ltrim (char s[])
{
    while (*s == 32) s++;
    return s;
}
// *********************************************************************** 
char* EN_CsI::rtrim (char s[])
{
    int i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
// ***********************************************************************
char * EN_CsI::trim (char s[])
{
    return ltrim(rtrim(s));  
}
// ***********************************************************************
int EN_CsI::Put2Array(char*s,double* val,int nval){
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
int EN_CsI::Put2Array(char* s,int* val,int nval){
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
char* EN_CsI::GetNextLine(char s){
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
