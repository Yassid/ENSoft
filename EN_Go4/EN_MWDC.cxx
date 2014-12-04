#include "EN_MWDC.h"

EN_MWDC::EN_MWDC()
{
  

  F2distance=482;F3distance=500;
  char fn[20];
  sprintf(fn,"prm/mwdc_y.prm");
  flagprm = ReadParameters(fn);
  analyser = 7;
  printf("WMDC:   Initializing - %d\n", analyser);
   double x[4][2],hs[2];
  x[0][0] = 0; x[0][1] = 3;
  x[1][0] = 2; x[1][1] = 3;
  x[2][0] = 4; x[2][1] = 4;
  x[3][0] =-1; x[3][1] = 2;
  GetLinearPar(x,4,hs);
}
EN_MWDC::EN_MWDC(char* filename)
{
  F2distance=482;F3distance=500;
  flagprm = ReadParameters(filename);
  analyser = 7;
  printf("ENMWDC:   Initializing - %d\n", analyser);
  double x[4][2],hs[2];
  x[0][0] = 0; x[0][1] = 3;
  x[1][0] = 2; x[1][1] = 3;
  x[2][0] = 4; x[2][1] = 4;
  x[3][0] =-1; x[3][1] = 2;
  GetLinearPar(x,4,hs);
}
// ***********************************************************************
EN_MWDC::~EN_MWDC(){}
// ***********************************************************************
void   EN_MWDC::ENcode(int raw[10][10][256], double val[10][10][256], int nval ){
    DataAssign(raw);
    LookupHits();
 //   SetPosition();
    val[analyser][1][1] = nhits;
    val[analyser][1][2] = nhitbc[1];
    val[analyser][1][3] = nhitbc[2];
    for (int i=1;i<3;i++){
      for (int j= 0;j<8;j++){
         val[analyser][1][j+4+(i-1)*8] = nhitpl[i][j];
         val[analyser][i+5][j+1] = tfirst[i][j];
         if (hitwiref[i][j]>0) val[analyser][i+7][j+1] = hitwiref[i][j];
         for (int k=0;k<16;k++){
             val[analyser][i+3][j*16+k+1] = traw[i][j][k];
             if (bpospl[i][j]>-10000) val[analyser][i+3][j] = bpospl[i][j];
             if (hitwire[i][j][k] ==1){
                val[analyser][i+1][j] = k;
                val[analyser][i+3][j] = pospl[i][j][k];
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
   memset(nhitpl,0,sizeof(nhitpl));
   memset(pospl,-10000,sizeof(pospl));
   memset(bpospl,-10000,sizeof(bpospl));
   for (int i=1;i<3;i++){
      for (int j= 0;j<8;j++){
         tfirst[i][j]= 300000000;
         hitwiref[i][j]=-1;
         for (int k=0;k<16;k++){
	     hitwire[i][j][k] = 0;
 	     if (traw[i][j][k]> 10 && traw[i][j][k]< tfirst[i][j]){
		tfirst[i][j] = traw[i][j][k];
                hitwiref[i][j]=k;
	     }	
//printf("sdsds  %f \n",ywei[i][j][traw[i][j][k]]);	
             if (ywei[i][j][traw[i][j][k]]>0){
      		hitwire[i][j][k] = 1;
                pospl[i][j][2*nhitpl[i][j]]    = - 2.5*(j%2) + (k-7)*5 - 1.25 + ywei[i][j][traw[i][j][k]];
                pospl[i][j][2*nhitpl[i][j]+1]  = - 2.5*(j%2) + (k-7)*5 - 1.25 - ywei[i][j][traw[i][j][k]];
        //        printf("Pospl %d  %d  %d  %f  %f\n",j%2,j,k,pospl[i][j][k],pospl[i][j][k+16]);
        //        tfirst[i][j] = traw[i][j][k];
                nhits++;
  	   	nhitbc[i]++;
                nhitpl[i][j]++;
 	     } 
         }
      }
   }
   double XZ[2][8]; 
   if (nhitpl[1][0]>0) for (int i10=0;i10<nhitpl[1][0];i10++)
     if (nhitpl[1][1]>0) for (int i11=0;i11<nhitpl[1][1];i11++)
       if (nhitpl[1][2]>0) for (int i12=0;i12<nhitpl[1][2];i12++)
         if (nhitpl[1][3]>0) for (int i13=0;i13<nhitpl[1][3];i13++)
            if (nhitpl[2][0]>0) for (int i20=0;i20<nhitpl[2][0];i20++)
     	       if (nhitpl[2][1]>0) for (int i21=0;i21<nhitpl[2][1];i21++)
       		 if (nhitpl[2][2]>0) for (int i22=0;i22<nhitpl[2][2];i22++)
         	   if (nhitpl[2][3]>0) for (int i23=0;i23<nhitpl[2][3];i23++){
			 if (nhitpl[1][0]>0) {XZ[n][0] = pospl[1][0][i10]; n++}
			 if (nhitpl[1][1]>0) {XZ[n][0] = pospl[1][0][i11]; n++}
			 if (nhitpl[1][2]>0) {XZ[n][0] = pospl[1][0][i12]; n++}
			 if (nhitpl[1][3]>0) {XZ[n][0] = pospl[1][0][i13]; n++}
                         if (nhitpl[2][0]>0) {XZ[n][0] = pospl[1][0][i20]; n++}
			 if (nhitpl[2][1]>0) {XZ[n][0] = pospl[1][0][i21]; n++}
			 if (nhitpl[2][2]>0) {XZ[n][0] = pospl[1][0][i22]; n++}
			 if (nhitpl[2][3]>0) {XZ[n][0] = pospl[1][0][i23]; n++}
		   }
	  
   for (int i=1;i<3;i++){
      for (int j= 0;j<4;j++){
         float dmin = 100000;
         for (int k=0;k<32;k++){
	     if (pospl[i][2*j][k]>-10000){
       //         printf("dmin\t%d\t%d\t%d\t",i,j,k); 
        //        printf("%d %d %d %f  %f  %f  %f\n",i,j,k,pospl[i][2*j][k],pospl[i][2*j+1][k-1],pospl[i][2*j+1][k],pospl[i][2*j+1][k+1]);
                for (int k1=0;k1<32;k1++){
                   if (pospl[i][2*j+1][k1]>-10000){
         //          printf("%d\t%f\t",k1,abs(pospl[i][2*j][k]-pospl[i][2*j+1][k1]));
                   if (abs(pospl[i][2*j][k]-pospl[i][2*j+1][k1])<dmin){
          
                     dmin =  abs(pospl[i][2*j][k]-pospl[i][2*j+1][k1]);
                     bpospl[i][2*j] = pospl[i][2*j][k];
     		     bpospl[i][2*j+1] = pospl[i][2*j+1][k1];
	}	   }
                }
           //     printf("\t%f   \n",dmin); 
 	     }
 
         }
      }
   }
}
// ***********************************************************************
void   EN_MWDC::SetPosition(){
    nhits=0;nhitbc[1]=0;nhitbc[2]=0;
   memset(nhitpl,0,sizeof(nhitpl));
   for (int i=1;i<3;i++){
      for (int j= 0;j<2;j++){
         for (int k=0;k<16;k++){		
             if (hitwire[i][0][k]*(hitwire[i][1][k] + hitwire[i][1][k+1] + hitwire[i][1][k-1])>0){
                nhits++;
  	   	nhitbc[i]++;
                nhitpl[i][0]++;
                tfirst[i][0] = traw[i][0][k];
 	     }
             if (hitwire[i][1][k]*(hitwire[i][0][k] + hitwire[i][0][k+1] + hitwire[i][0][k-1])>0){
                nhits++;
  	   	nhitbc[i]++;
                nhitpl[i][1]++;
                tfirst[i][1] = traw[i][1][k];
 	     } 
	     if (hitwire[i][2][k]*(hitwire[i][3][k] + hitwire[i][3][k+1] + hitwire[i][3][k-1])>0){
                nhits++;
  	   	nhitbc[i]++;
                nhitpl[i][2]++;
                tfirst[i][2] = traw[i][2][k];
 	     }
             if (hitwire[i][3][k]*(hitwire[i][2][k] + hitwire[i][2][k+1] + hitwire[i][2][k-1])>0){
                nhits++;
  	   	nhitbc[i]++;
                nhitpl[i][3]++;
                tfirst[i][3] = traw[i][3][k];
 	     } 
           
             if (hitwire[i][4][k]*(hitwire[i][5][k] + hitwire[i][5][k+1] + hitwire[i][5][k-1])>0){
                nhits++;
  	   	nhitbc[i]++;
                nhitpl[i][4]++;
                tfirst[i][4] = traw[i][4][k];
 	     } 
	     if (hitwire[i][5][k]*(hitwire[i][4][k] + hitwire[i][4][k+1] + hitwire[i][4][k-1])>0){
                nhits++;
  	   	nhitbc[i]++;
                nhitpl[i][5]++;
                tfirst[i][5] = traw[i][5][k];
 	     }
             if (hitwire[i][6][k]*(hitwire[i][7][k] + hitwire[i][7][k+1] + hitwire[i][7][k-1])>0){
                nhits++;
  	   	nhitbc[i]++;
                nhitpl[i][3]++;
                tfirst[i][3] = traw[i][3][k];
	     }
	     if (hitwire[i][7][k]*(hitwire[i][6][k] + hitwire[i][6][k+1] + hitwire[i][6][k-1])>0){
                nhits++;
  	   	nhitbc[i]++;
                nhitpl[i][7]++;
                tfirst[i][7] = traw[i][7][k];
 	     }	
         }

      }
   }
}
// ***********************************************************************
int EN_MWDC::GetLinearPar(double XY[][2], int npoint,double *hs){
   double A[2][2],A1[2][2],B[2],detA;
   for (int i=0;i<2;i++){
      B[i] = 0;
      for (int j=0;j<2;j++){
         A[i][j] = 0;
   } }
        printf("\tX      \tY    \n");
         for (int i =0;i<npoint;i++){
            printf("\t%f\t%f\n",XY[i][0],XY[i][1]);
            A[0][0] += XY[i][0]*XY[i][0];
            A[0][1] += XY[i][0];
            A[1][0] += XY[i][0];
            A[1][1] += 1;
            B[0] += XY[i][0]*XY[i][1];
            B[1] += XY[i][1];
         } 
      detA = A[0][0]*A[1][1] - A[0][1]*A[0][1];
      printf("A : %f    %f\n",A[0][0],A[0][1]);
      printf("A : %f    %f\n",A[0][1],A[1][1]);
      printf("A : %f    %f\n",B[0],B[1]);
      printf("detA :   %f\n",detA);
   if (detA==0) return -1;
      A1[0][0] = A[1][1]/detA; A1[0][1] = -A[1][0]/detA;
      A1[1][1] = A[0][0]/detA; A1[1][0] = -A[0][1]/detA;
     printf("A : %f    %f\n",A1[0][0],A1[0][1]);
      printf("A : %f    %f\n",A1[0][1],A1[1][1]);
      hs[0] = A1[0][0]*B[0] + A1[0][1]*B[1];
      hs[1] = A1[1][0]*B[0] + A1[1][1]*B[1];
      printf("He so : %f    %f\n",hs[0],hs[1]);
      detA=0;
      for (int i =0;i<npoint;i++) detA+=pow(XY[i][1] - hs[0]*XY[i][0]-hs[1],2);
      printf("bpdl :   %f\n",detA);
   return 0;
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
    int ii,jj,ch;
    char* buff;
    //read ch2ns 
 //  printf("bdc prm reading\n");
    while (not fi.eof()){
 //  for (int i=0;i<10;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (Put2Array(buff,valread,3) == -1) goto l20;
       if (valread[0]<9) {ii=1;       jj = int(valread[0])-1;}
       else {ii=2;       jj = int(valread[0])-9;}

       ch = int(valread[1]);
       ywei[ii][jj][ch] = valread[2];
 //      printf("bdc prm  %d\t%d\t%d\t%f\n",ii,jj,ch,ywei[ii][jj][ch]);
    }
     fi.close();
     printf("EN_MWDC: Parameters file :\"%s\" |--> LOADED!!!.\n",filename); 
     return 0;
  }else{
     printf("EN_MWDC: Parameters file :\"%s\" cannot open |--> NOT load!!!\n",filename);
     goto def;
  }
l20:  printf("EN_MWDC: Parameters file :\"%s\" not true format |--> NOT load!!!\n",filename);

def:  return -1;
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
