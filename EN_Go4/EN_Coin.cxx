#include "EN_Coin.h"

EN_Coin::EN_Coin()
{
  
  analyser=6;
  printf("EN_Coin:   Initializing - %d\n", analyser);
}
EN_Coin::EN_Coin(char* filename)
{
 
  analyser=6;
  printf("EN_Coin:   Initializing - %d\n", analyser);
}
// ***********************************************************************
EN_Coin::~EN_Coin(){}
// ***********************************************************************
void   EN_Coin::ENcode(int raw[10][10][256], double val[10][10][256], int nval ){
   double tref=0;
   for (int i=0;i<16;i++){
       if (raw[analyser][1][i]==1) {val[analyser][1][1] = i+1;tref=tref+1;} 
   }
   val[analyser][1][2] = tref;
}

// ***********************************************************************
int EN_Coin::ReadParameters(char* filename){
   
  return -1;
}

// ***********************************************************************
char* EN_Coin::ltrim (char s[])
{
    while (*s == 32) s++;
    return s;
}
// *********************************************************************** 
char* EN_Coin::rtrim (char s[])
{
    int i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
// ***********************************************************************
char * EN_Coin::trim (char s[])
{
    return ltrim(rtrim(s));  
}
// ***********************************************************************
int EN_Coin::Put2Array(char*s,double* val,int nval){
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
int EN_Coin::Put2Array(char* s,int* val,int nval){
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
char* EN_Coin::GetNextLine(char s){
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
