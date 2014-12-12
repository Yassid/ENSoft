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
    val[analyser][2][1] = Ax;
    val[analyser][3][1] = Ay;
    val[analyser][2][2] = X0;
    val[analyser][3][2] = Y0;
    val[analyser][2][3] = GetExtrapolationX(1378.5);
    val[analyser][3][3] = GetExtrapolationY(1378.5);
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
             if (ywei[i][j][traw[i][j][k]]>0){
                tfirst[i][j] = traw[i][j][k];
      		hitwire[i][j][k] = 1;
                pospl[i][j][nhitpl[i][j]]  = (- 2.5*(j%2-1) + (k-7)*5.0 - 1.25) + 1*ywei[i][j][traw[i][j][k]];
		nhitpl[i][j]++;
		pospl[i][j][nhitpl[i][j]]  = (- 2.5*(j%2-1) + (k-7)*5.0 - 1.25) - 1*ywei[i][j][traw[i][j][k]];
        //        printf("Pospl %d  %d  %d  %f  %f\n",j%2,j,k,pospl[i][j][k],pospl[i][j][k+16]);
        //        tfirst[i][j] = traw[i][j][k];
                nhits++;
  	   	nhitbc[i]++;
                nhitpl[i][j]++;
 	     } 
         }
      }
   }
   double XZ[8][2],hs[2],dlmax,dl; 
   
   for (int i=0;i<4;i++)
      for (int j=0;j<4;j++){
         Xmm[i][j] = -1000;
	 Ymm[i][j] = -1000;

         if (nhitpl[i][j]==0) nhitpl[i][j]=1;
	 if (nhitpl[i][j+4]==0) nhitpl[i][j+4]=1;
      }
   Ax=1000;Ay=1000;
   int n,n1;
   dlmax = 1E39;
//    printf(" Start for one evt  %d\n" ,nhits);
   for (int i10=0;i10<nhitpl[1][0];i10++)
     for (int i11=0;i11<nhitpl[1][1];i11++)
       for (int i12=0;i12<nhitpl[1][2];i12++)
         for (int i13=0;i13<nhitpl[1][3];i13++)
            for (int i20=0;i20<nhitpl[2][0];i20++)
     	       for (int i21=0;i21<nhitpl[2][1];i21++)
       		 for (int i22=0;i22<nhitpl[2][2];i22++)
         	   for (int i23=0;i23<nhitpl[2][3];i23++){
			 n=0;
			 if (nhitpl[1][0]>1) {XZ[n][0] =   0.0; XZ[n][1] = pospl[1][0][i10]; n++;}
			 if (nhitpl[1][1]>1) {XZ[n][0] =   4.8; XZ[n][1] = pospl[1][1][i11]; n++;}
			 if (nhitpl[1][2]>1) {XZ[n][0] =  19.2; XZ[n][1] = pospl[1][2][i12]; n++;}
			 if (nhitpl[1][3]>1) {XZ[n][0] =  24.0; XZ[n][1] = pospl[1][3][i13]; n++;}
                         if (n==0) goto forY;n1=n; 
                         if (nhitpl[2][0]>1) {XZ[n][0] = 998.5; XZ[n][1] = pospl[2][0][i20]; n++;}
			 if (nhitpl[2][1]>1) {XZ[n][0] =1003.3; XZ[n][1] = pospl[2][1][i21]; n++;}
			 if (nhitpl[2][2]>1) {XZ[n][0] =1017.7; XZ[n][1] = pospl[2][2][i22]; n++;}
			 if (nhitpl[2][3]>1) {XZ[n][0] =1022.5; XZ[n][1] = pospl[2][3][i23]; n++;}
                         if (n==n1) goto forEnd;
			 dl = GetLinearPar(XZ,n,hs);
			 if (dl<dlmax){
			   dlmax=dl;//printf("Min \t%f \t%f \t%f\n",dl,hs[0],hs[1]);
			 //   for (int i=0;i<n;i++)
         		 //      printf("\t%d\t%f \t%f\n",i, XZ[i][0],XZ[i][1]);
                           Ax = hs[0];X0=hs[1];
 			   n=0;	
                           if (nhitpl[1][0]>1) {Xmm[1][0] = XZ[n][1];Zmm[1][0] = XZ[n][0]; n++;}
 			   if (nhitpl[1][1]>1) {Xmm[1][1] = XZ[n][1];Zmm[1][1] = XZ[n][0]; n++;}
			   if (nhitpl[1][2]>1) {Xmm[1][2] = XZ[n][1];Zmm[1][2] = XZ[n][0]; n++;}
			   if (nhitpl[1][3]>1) {Xmm[1][3] = XZ[n][1];Zmm[1][3] = XZ[n][0]; n++;}
                           if (nhitpl[2][0]>1) {Xmm[2][0] = XZ[n][1];Zmm[2][0] = XZ[n][0]; n++;}
			   if (nhitpl[2][1]>1) {Xmm[2][1] = XZ[n][1];Zmm[2][1] = XZ[n][0]; n++;}
			   if (nhitpl[2][2]>1) {Xmm[2][2] = XZ[n][1];Zmm[2][2] = XZ[n][0]; n++;}
			   if (nhitpl[2][3]>1) {Xmm[2][3] = XZ[n][1];Zmm[2][3] = XZ[n][0]; n++;}
   			  
			}
		   }
   //    for (int i=0;i<n;i++)
   //    		       printf("\t%d\t%f \t%f\n",i, XZ[i][0],XZ[i][1]);
forY:   dlmax = 1E39;
 //  printf(" Start for one evt Y  %d\n" ,nhits);
   for (int i10=0;i10<nhitpl[1][4];i10++)
     for (int i11=0;i11<nhitpl[1][5];i11++)
       for (int i12=0;i12<nhitpl[1][6];i12++)
         for (int i13=0;i13<nhitpl[1][7];i13++)
            for (int i20=0;i20<nhitpl[2][4];i20++)
     	       for (int i21=0;i21<nhitpl[2][5];i21++)
       		 for (int i22=0;i22<nhitpl[2][6];i22++)
         	   for (int i23=0;i23<nhitpl[2][7];i23++){
			 n=0;
			 if (nhitpl[1][4]>1) {XZ[n][0] =   0.0; XZ[n][1] = pospl[1][4][i10]; n++;}
			 if (nhitpl[1][5]>1) {XZ[n][0] =   4.8; XZ[n][1] = pospl[1][5][i11]; n++;}
			 if (nhitpl[1][6]>1) {XZ[n][0] =  19.2; XZ[n][1] = pospl[1][6][i12]; n++;}
			 if (nhitpl[1][7]>1) {XZ[n][0] =  24.0; XZ[n][1] = pospl[1][7][i13]; n++;}
                         if (n==0) goto forEnd;n1=n; 
                         if (nhitpl[2][4]>1) {XZ[n][0] = 998.5; XZ[n][1] = pospl[2][4][i20]; n++;}
			 if (nhitpl[2][5]>1) {XZ[n][0] =1003.3; XZ[n][1] = pospl[2][5][i21]; n++;}
			 if (nhitpl[2][6]>1) {XZ[n][0] =1017.7; XZ[n][1] = pospl[2][6][i22]; n++;}
			 if (nhitpl[2][7]>1) {XZ[n][0] =1022.5; XZ[n][1] = pospl[2][7][i23]; n++;}
			 if (n==n1) goto forEnd;
                         dl = GetLinearPar(XZ,n,hs);
			 if (dl<dlmax){
                         
			   dlmax=dl;//printf("Min \t%f \t%f \t%f\n",dl,hs[0],hs[1]);
			 //   for (int i=0;i<n;i++)
         		     //  printf("\t%d\t%f \t%f\n",i, XZ[i][0],XZ[i][1]);
			   Ay=hs[0];Y0=hs[1];
			   n=0;
                           if (nhitpl[1][4]>1) {Ymm[1][0] = XZ[n][1];Zmm[1][0] = XZ[n][1]; n++;}
 			   if (nhitpl[1][5]>1) {Ymm[1][1] = XZ[n][1];Zmm[1][1] = XZ[n][1]; n++;}
			   if (nhitpl[1][6]>1) {Ymm[1][2] = XZ[n][1];Zmm[1][2] = XZ[n][1]; n++;}
			   if (nhitpl[1][7]>1) {Ymm[1][3] = XZ[n][1];Zmm[1][3] = XZ[n][1]; n++;}
                           if (nhitpl[2][4]>1) {Ymm[2][0] = XZ[n][1];Zmm[2][0] = XZ[n][1]; n++;}
			   if (nhitpl[2][5]>1) {Ymm[2][1] = XZ[n][1];Zmm[2][1] = XZ[n][1]; n++;}
			   if (nhitpl[2][6]>1) {Ymm[2][2] = XZ[n][1];Zmm[2][2] = XZ[n][1]; n++;}
			   if (nhitpl[2][7]>1) {Ymm[2][3] = XZ[n][1];Zmm[2][3] = XZ[n][1]; n++;}
   			  
			}
		   }	  

forEnd:   return ;
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
double EN_MWDC::GetLinearPar(double XY[][2], int npoint,double *hs){
   double A[2][2],A1[2][2],B[2],detA;
   for (int i=0;i<2;i++){
      B[i] = 0;
      for (int j=0;j<2;j++){
         A[i][j] = 0;
   } }
  //      printf("\tX      \tY    \n");
         for (int i =0;i<npoint;i++){
  //          printf("%d\t%f  \t%f\n",i,XY[i][0],XY[i][1]);
            A[0][0] += XY[i][0]*XY[i][0];
            A[0][1] += XY[i][0];
            A[1][0] += XY[i][0];
            A[1][1] += 1;
            B[0] += XY[i][0]*XY[i][1];
            B[1] += XY[i][1];
         } 
      detA = A[0][0]*A[1][1] - A[0][1]*A[0][1];
//      printf("A : %f    %f\n",A[0][0],A[0][1]);
//      printf("A : %f    %f\n",A[0][1],A[1][1]);
//      printf("A : %f    %f\n",B[0],B[1]);
//      printf("detA :   %f\n",detA);
   if (detA==0) return -1;
      A1[0][0] = A[1][1]/detA; A1[0][1] = -A[1][0]/detA;
      A1[1][1] = A[0][0]/detA; A1[1][0] = -A[0][1]/detA;
//     printf("A : %f    %f\n",A1[0][0],A1[0][1]);
//      printf("A : %f    %f\n",A1[0][1],A1[1][1]);
      hs[0] = A1[0][0]*B[0] + A1[0][1]*B[1];
      hs[1] = A1[1][0]*B[0] + A1[1][1]*B[1];
  //    printf("He so : %f    %f\n",hs[0],hs[1]);
      detA=0;
      for (int i =0;i<npoint;i++) detA+=pow(XY[i][1] - hs[0]*XY[i][0]-hs[1],2);
 //     printf("bpdl :   %f\n",detA);
   return detA;
}
// ***********************************************************************
double EN_MWDC::GetExtrapolationX(double atZ){
   double exX;
   if (Ax!=1000 && Xmm[1][0]!=-1000)
      exX =  Ax*atZ + X0;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
double EN_MWDC::GetExtrapolationY(double atZ){
  double exX;
   if (Ay!=1000 && Ymm[1][0]!=-1000)
      exX =  Ay*(atZ+10) + Y0;
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
