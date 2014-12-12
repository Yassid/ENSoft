#include "EN_PPAC_Cal.h"

EN_PPAC_Cal::EN_PPAC_Cal()
{
  //PPAC no: 0 - F1PPAC not use now
  //PPAC no: 1 - F2UPPAC 
  //PPAC no: 2 - F2DPPAC 
  //PPAC no: 3 - F3UPPAC 
  //PPAC no: 4 - F3DPPAC 

  F2distance=482;F3distance=500;
  char fn[20];
  sprintf(fn,"prm/ppac.prm");
  flagprm = ReadParameters(fn);
  analyser = 2;
  printf("ENPPAC:   Initializing - %d\n", analyser);
}
EN_PPAC_Cal::EN_PPAC_Cal(char* filename)
{
  F2distance=482;F3distance=500;
  flagprm = ReadParameters(filename);
  analyser = 2;
  printf("ENPPAC:   Initializing - %d\n", analyser);
}
// ***********************************************************************
EN_PPAC_Cal::~EN_PPAC_Cal(){}
// ***********************************************************************
void   EN_PPAC_Cal::ENcode(int raw[10][10][256], double val[10][10][256], int nval ){
  //  printf("EN_PPAC_Cal::ENcode:  %d\n",raw[2][2][21][4]); 
    int f2ppac[10];
    for (int i=0;i<10;i++){
	f2ppac[i] = raw[analyser][1][i];
 //       f3ppac[10] = raw[2][1][i+10];	
//       printf("EN_PPAC_Cal::ENcode: %d   %d   %d\n",i,f2ppac[i],raw[2][1][i]);
    }
    SetPosition(1,0, f2ppac);
//    SetPosition(0, f2ppac,0, f2ppac);
    int ch =0;
    for (int i=0 ;i<5;i++){
	for (int j=0;j<5;j++){
	    val[analyser][1][ch] = traw[i][j];
	    val[analyser][2][ch] = tcal[i][j];
	    ch++;	
	}
        val[analyser][3][i] = posXns[i];
        val[analyser][3][i+5] = posYns[i];
        val[analyser][4][i] = posXmm[i];
        val[analyser][4][i+5] = posYmm[i];
       
    } 
    val[analyser][5][1] = GetF2ExtrapolationX(750);
    val[analyser][5][2] = GetF2ExtrapolationY(750);
}
// ***********************************************************************
void   EN_PPAC_Cal::SetPosition(int ppacNo, int Left,int Right,int Down,int Up, int Anode ){
  if (flagprm<0) printf("EN_PPAC:     Khong doc dc prm file\n");
  traw[ppacNo][0]=Left;
  traw[ppacNo][1]=Down;
  traw[ppacNo][2]=Right;
  traw[ppacNo][3]=Up;
  if (Anode>0) traw[ppacNo][4]=Anode;
//  printf(" No L D R U:  %d    %d    %d     %d    %d \n",ppacNo, Left,Down,Right,Up);
  for (int i=0;i<5;i++) tcal[ppacNo][i]=traw[ppacNo][i]*ch2ns[ppacNo][i];
  if (traw[ppacNo][0]>0 && traw[ppacNo][2]>0) {
       posXns[ppacNo] = tcal[ppacNo][0] - tcal[ppacNo][2];
       posXmm[ppacNo] = posXns[ppacNo]*ns2mm[ppacNo][0] -offset[ppacNo][0];
  }else{ 
       posXns[ppacNo]=-1000;
       posXmm[ppacNo]=-1000;
  }  
  if (traw[ppacNo][1]>0 && traw[ppacNo][3]>0) {
       posYns[ppacNo] = tcal[ppacNo][1] - tcal[ppacNo][3];
       posYmm[ppacNo] = posYns[ppacNo]*ns2mm[ppacNo][1] -offset[ppacNo][1];
  }else{ 
       posYns[ppacNo]=-1000;
       posYmm[ppacNo]=-1000;
  }

}
// ***********************************************************************
void   EN_PPAC_Cal::SetPosition(int ppacNo, int start, int* rawin){
  SetPosition(ppacNo,  rawin[start+0],rawin[start+2],rawin[start+1],rawin[start+3],rawin[start+4]  );
  SetPosition(ppacNo+1,rawin[start+5],rawin[start+7],rawin[start+6],rawin[start+8],rawin[start+9]  );
}
// ***********************************************************************
void   EN_PPAC_Cal::SetPosition(int start1, int* rawin1, int start2, int* rawin2){
   SetPosition(1, start1, rawin1);
   SetPosition(3, start2, rawin2);
}
// ***********************************************************************
double EN_PPAC_Cal::GetF2_aX_mrad(){
   double exX;
   if (abs(posXmm[1])<50 && abs(posXmm[2])<50)
      exX =  atan2(posXmm[2] - posXmm[1],F2distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double EN_PPAC_Cal::GetF2_aY_mrad(){
   double exX;
   if (abs(posYmm[1])<50 && abs(posYmm[2])<50)
      exX =  atan2(posYmm[2] - posYmm[1],F2distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double EN_PPAC_Cal::GetF3_aX_mrad(){
  double exX;
   if (abs(posXmm[3])<50 && abs(posXmm[4])<50)
      exX =  atan2(posXmm[4] - posXmm[3],F3distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double EN_PPAC_Cal::GetF3_aY_mrad(){
   double exX;
   if (abs(posYmm[3])<50 && abs(posYmm[4])<50)
      exX =  atan2(posYmm[4] - posYmm[3],F3distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double EN_PPAC_Cal::GetF2ExtrapolationX(double atZ){
   double exX;
   if (abs(posXmm[1])<50 && abs(posXmm[2])<50)
      exX =  posXmm[1] + (posXmm[2] - posXmm[1])*atZ/F2distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
double EN_PPAC_Cal::GetF2ExtrapolationY(double atZ){
  double exX;
   if (abs(posYmm[1])<50 && abs(posYmm[2])<50)
      exX =  posYmm[1] + (posYmm[2] - posYmm[1])*atZ/F2distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
double EN_PPAC_Cal::GetF3ExtrapolationX(double atZ){
  double exX;
   if (abs(posXmm[3])<50 && abs(posXmm[4])<50)
      exX =  posXmm[3] + (posXmm[4] - posXmm[3])*atZ/F3distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
double EN_PPAC_Cal::GetF3ExtrapolationY(double atZ){
   double exX;
   if (abs(posYmm[3])<50 && abs(posYmm[4])<50)
      exX =  posYmm[3] + (posYmm[4] - posYmm[3])*atZ/F3distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
int EN_PPAC_Cal::ReadParameters(char* filename){
   fi.open(filename,ios::in);
  if (fi.is_open()){
    double valread[5];
    int ch2nsflag;
    char* buff;
    //read ch2ns 
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,5) == -1) goto l20;
         for (int j=0;j<5;j++) ch2ns[i][j]=valread[j];
       }else for (int j=0;j<5;j++) ch2ns[i][j]=1.;
     }
    //read qdc
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,5) == -1) goto l20;
         for (int j=0;j<5;j++) ch2qdc[i][j]=valread[j];
       }else for (int j=0;j<5;j++) ch2qdc[i][j]=1.;
     }
     //read qdc ped
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,5) == -1) goto l20;
         for (int j=0;j<5;j++) qdcped[i][j]=valread[j];
       }else for (int j=0;j<5;j++) qdcped[i][j]=0;
     }

   //  ns2mm
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,2) == -1) goto l20;
         for (int j=0;j<2;j++) ns2mm[i][j]=valread[j];
       }else for (int j=0;j<2;j++) ns2mm[i][j]=1.;
     }
     //  in off set
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,2) == -1) goto l20;
         for (int j=0;j<2;j++) in_offset[i][j]=valread[j];
       }else for (int j=0;j<2;j++) in_offset[i][j]=0.;
     }
    //  out off set
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,2) == -1) goto l20;
         for (int j=0;j<2;j++) out_offset[i][j]=valread[j];
       }else for (int j=0;j<2;j++) out_offset[i][j]=0.;
     }
      //  geometry off set
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,2) == -1) goto l20;
         for (int j=0;j<2;j++) geo_offset[i][j]=valread[j];
       }else for (int j=0;j<2;j++) geo_offset[i][j]=0.;
     }
     for (int i=0;i<5;i++){
       for (int j=0;j<2;j++) offset[i][j]= in_offset[i][j]+out_offset[i][j]+geo_offset[i][j];
     }

     fi.close();
     printf("EN_PPAC_Cal: Parameters file :\"%s\" |--> LOADED!!!.\n",filename); 
     return 0;
  }else{
     printf("EN_PPAC_Cal: Parameters file :\"%s\" cannot open |--> NOT load!!!\n",filename);
     goto def;
  }
l20:  printf("EN_PPAC_Cal: Parameters file :\"%s\" not true format |--> NOT load!!!\n",filename);
def:;
  for (int i=0;i<5;i++){
     for (int j=0;j<5;j++){
        ch2ns[i][j]= 1;
        ch2qdc[i][j] =1;
        qdcped[i][j] =0;
     }
  }
  for (int i=0;i<5;i++){
     for (int j=0;j<2;j++){
        ns2mm[i][j] = 1;
   	in_offset[i][j] = 0;
   	out_offset[i][j] = 0;
   	geo_offset[i][j] = 0;
        offset[i][j]= in_offset[i][j]+out_offset[i][j]+geo_offset[i][j];
     }
  }
  return -1;
}

// ***********************************************************************
char* EN_PPAC_Cal::ltrim (char s[])
{
    while (*s == 32) s++;
    return s;
}
// *********************************************************************** 
char* EN_PPAC_Cal::rtrim (char s[])
{
    int i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
// ***********************************************************************
char * EN_PPAC_Cal::trim (char s[])
{
    return ltrim(rtrim(s));  
}
// ***********************************************************************
int EN_PPAC_Cal::Put2Array(char*s,double* val,int nval){
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
int EN_PPAC_Cal::Put2Array(char* s,int* val,int nval){
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
char* EN_PPAC_Cal::GetNextLine(char s){
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
