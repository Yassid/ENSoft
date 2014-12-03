#include "EN_MWDC.h"

EN_MWDC::EN_MWDC()
{
  

  F2distance=482;F3distance=500;
  char fn[20];
  sprintf(fn,"prm/ppac.prm");
  flagprm = ReadParameters(fn);
  analyser = 7;
  printf("WMDC:   Initializing - %d\n", analyser);
}
EN_MWDC::EN_MWDC(char* filename)
{
  F2distance=482;F3distance=500;
  flagprm = ReadParameters(filename);
  analyser = 7;
  printf("ENMWDC:   Initializing - %d\n", analyser);
}
// ***********************************************************************
EN_MWDC::~EN_MWDC(){}
// ***********************************************************************
void   EN_MWDC::ENcode(int raw[10][10][256], double val[10][10][256], int nval ){
    DataAssign(raw);
    LookupHits();
    val[analyser][1][1] = nhits;
    val[analyser][1][2] = nhitbc[1];
    val[analyser][1][3] = nhitbc[2];
    for (int i=1;i<3;i++){
      for (int j= 0;j<8;j++){
         val[analyser][i+5][j+1] = tfirst[i][j];
         for (int k=0;k<16;k++){
             val[analyser][i+3][j*16+k+1] = traw[i][j][k];
             if (hitwire[i][j][k] ==1){
                val[analyser][i+1][j] = k;
 	     } 
         }
      }
    }
}
// ***********************************************************************
void   EN_MWDC::DataAssign(int raw[10][10][256]){
   for (int i=0;i<16;i++){
      traw[1][0][i] = raw[analyser][1][i];
      traw[1][1][i] = raw[analyser][1][i+16];
      traw[1][2][i] = raw[analyser][1][i+32];
      traw[1][3][i] = raw[analyser][1][i+48];
      traw[1][4][i] = raw[analyser][2][i];
      traw[1][5][i] = raw[analyser][2][i+16];
      traw[1][6][i] = raw[analyser][2][i+32];
      traw[1][7][i] = raw[analyser][2][i+48];
      traw[2][0][i] = raw[analyser][3][i];
      traw[2][1][i] = raw[analyser][3][i+16];
      traw[2][2][i] = raw[analyser][3][i+32];
      traw[2][3][i] = raw[analyser][3][i+48];
      traw[2][4][i] = raw[analyser][4][i];
      traw[2][5][i] = raw[analyser][4][i+16];
      traw[2][6][i] = raw[analyser][4][i+32];
      traw[2][7][i] = raw[analyser][4][i+48];
   } 
}
// ***********************************************************************
void   EN_MWDC::LookupHits(){
   nhits=0;nhitbc[1]=0;nhitbc[2]=0;
   for (int i=1;i<3;i++){
      for (int j= 0;j<8;j++){
         tfirst[i][j]= 300000000;
         for (int k=0;k<16;k++){
	     hitwire[i][j][k] = 0;
 	     if (traw[i][j][k]> 0 && traw[i][j][k]< tfirst[i][j]){
		tfirst[i][j] = traw[i][j][k];
	     }		
             if (traw[i][j][k]>0){
                nhits++;
  	   	nhitbc[i]++;
      		hitwire[i][j][k] = 1;
 	     } 
         }
      }
   }
}
// ***********************************************************************
void   EN_MWDC::SetPosition(int start1, int* rawin1, int start2, int* rawin2){
    
}
// ***********************************************************************
double EN_MWDC::GetF2_aX_mrad(){
   double exX;
   if (abs(posXmm[1])<50 && abs(posXmm[2])<50)
      exX =  atan2(posXmm[2] - posXmm[1],F2distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double EN_MWDC::GetF2_aY_mrad(){
   double exX;
   if (abs(posYmm[1])<50 && abs(posYmm[2])<50)
      exX =  atan2(posYmm[2] - posYmm[1],F2distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double EN_MWDC::GetF3_aX_mrad(){
  double exX;
   if (abs(posXmm[3])<50 && abs(posXmm[4])<50)
      exX =  atan2(posXmm[4] - posXmm[3],F3distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double EN_MWDC::GetF3_aY_mrad(){
   double exX;
   if (abs(posYmm[3])<50 && abs(posYmm[4])<50)
      exX =  atan2(posYmm[4] - posYmm[3],F3distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double EN_MWDC::GetF2ExtrapolationX(double atZ){
   double exX;
   if (abs(posXmm[1])<50 && abs(posXmm[2])<50)
      exX =  posXmm[1] + (posXmm[2] - posXmm[1])*atZ/F2distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
double EN_MWDC::GetF2ExtrapolationY(double atZ){
  double exX;
   if (abs(posYmm[1])<50 && abs(posYmm[2])<50)
      exX =  posYmm[1] + (posYmm[2] - posYmm[1])*atZ/F2distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
double EN_MWDC::GetF3ExtrapolationX(double atZ){
  double exX;
   if (abs(posXmm[3])<50 && abs(posXmm[4])<50)
      exX =  posXmm[3] + (posXmm[4] - posXmm[3])*atZ/F3distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
double EN_MWDC::GetF3ExtrapolationY(double atZ){
   double exX;
   if (abs(posYmm[3])<50 && abs(posYmm[4])<50)
      exX =  posYmm[3] + (posYmm[4] - posYmm[3])*atZ/F3distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
int EN_MWDC::ReadParameters(char* filename){
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
     printf("EN_MWDC: Parameters file :\"%s\" |--> LOADED!!!.\n",filename); 
     return 0;
  }else{
     printf("EN_MWDC: Parameters file :\"%s\" cannot open |--> NOT load!!!\n",filename);
     goto def;
  }
l20:  printf("EN_MWDC: Parameters file :\"%s\" not true format |--> NOT load!!!\n",filename);
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
char* EN_MWDC::ltrim (char s[])
{
    while (*s == 32) s++;
    return s;
}
// *********************************************************************** 
char* EN_MWDC::rtrim (char s[])
{
    int i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
// ***********************************************************************
char * EN_MWDC::trim (char s[])
{
    return ltrim(rtrim(s));  
}
// ***********************************************************************
int EN_MWDC::Put2Array(char*s,double* val,int nval){
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
int EN_MWDC::Put2Array(char* s,int* val,int nval){
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
char* EN_MWDC::GetNextLine(char s){
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
