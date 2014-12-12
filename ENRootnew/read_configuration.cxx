#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#ifdef __MAKECINT__
#pragma link C++ class vector<int>+;
#endif

using namespace std;

char* ltrim (char s[])
{
    while (*s == 32) s++;
    return s;
}
 
char* rtrim (char s[])
{
    int i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
char * trim (char s[])
{
    return ltrim(rtrim(s));  
}

int Put2Array(char*s,double* val,int nval){
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
  if (nf <nval) return -1;
  return 0;
}
int Put2Array(char* s,int* val,int nval){
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
  if (nf <nval) return -1;
  return 0;
}
char* GetNextLine(char s){
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
