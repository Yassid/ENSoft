#include "EN_DSSD.h"

EN_DSSD::EN_DSSD()
{
  analyser=8;
  flagprm = ReadParameters("prm/dssd.prm");
  //flagprm = ReadParameters("prm/dssd2.prm");
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

  double xx,yy;

   for (int i=0;i<64;i++){
	XLqraw[i] = raw[analyser][1][i]; XLqraw[i+64] = raw[analyser][1][127-i];
        YLqraw[i] = raw[analyser][2][i]; YLqraw[i+64] = raw[analyser][2][127-i];
        XRqraw[i] = raw[analyser][3][64+i]; XRqraw[i+64] = raw[analyser][3][63-i];
        YRqraw[i] = raw[analyser][4][i]; YRqraw[i+64] = raw[analyser][4][127-i];
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
// neib of maximum
   for (int i=9;i<17;i++) val[analyser][9][i]=0;
   if (posXL>1   ) val[analyser][9][9] =  qcal[0][posXL-2];
   if (posXL<128 ) val[analyser][9][10] = qcal[0][posXL];

   if (posYL>1   ) val[analyser][9][11] =  qcal[0][posYL-2];
   if (posYL<128 ) val[analyser][9][12] =  qcal[0][posYL];
   
   if (posXR>1   ) val[analyser][9][13] =  qcal[0][posXR-2];
   if (posXR<128 ) val[analyser][9][14] = qcal[0][posXR];
   if (posYR>0   ) val[analyser][9][15] =  qcal[0][posYR-2];
   if (posYR<128 ) val[analyser][9][16] =  qcal[0][posYR];

   //Angle Calc ST
   if(abs(posXL-64)<65&&abs(posYL-64)<65&&El_XL>30&&El_YL>30){
     xx =-65.+(posXL-64.)*100./128.-val[7][4][1];
     yy = 00.+(posYL-64.)*100./128.-val[7][5][1];
     val[analyser][8][1] =-acos(140./sqrt(xx*xx+yy*yy+140.*140.))*180./3.14159;
   }else{
     val[analyser][8][1] =-1.e-10;
   }     
   if(abs(posXR-64)<65&&abs(posYR-64)<65&&El_XR>30&&El_YR>30){
     xx = 65.+(posYR-64.)*100./128.-val[7][4][1];
     yy = 00.+(posXR-64.)*100./128.-val[7][5][1];
     val[analyser][8][2] = acos(140./sqrt(xx*xx+yy*yy+140.*140.))*180./3.14159;
   }else{
     val[analyser][8][2] = 1.e-10;
   }

   val[analyser][8][3] =  El_XL/cos(val[analyser][8][1]/180.*3.14159);
   val[analyser][8][4] =  El_YL/cos(val[analyser][8][1]/180.*3.14159);
   val[analyser][8][5] =  El_XR/cos(val[analyser][8][2]/180.*3.14159);
   val[analyser][8][6] =  El_YR/cos(val[analyser][8][2]/180.*3.14159);

   //   cout<<endl;
   //cout<<El_XL<<":"<<El_YL<<":"<<El_YR<<":"<<El_XR<<endl;
   //cout<<posXL<<":"<<posYL<<":"<<posYR<<":"<<posXR<<endl;
   //cout<<xx<<":"<<yy<<":"<<val[analyser][9][9]<<endl;
     
}
// ***********************************************************************
int EN_DSSD::Calibration(){
    int temp;
/*    for (int i=0;i<128;i=i+2){
       temp = XLqraw[i];XLqraw[i] = XLqraw[i+1];XLqraw[i+1] = temp; 
       temp = YLqraw[i];YLqraw[i] = YLqraw[i+1];YLqraw[i+1] = temp;
       temp = XRqraw[i];XRqraw[i] = XRqraw[i+1];XRqraw[i+1] = temp;
       temp = YRqraw[i];YRqraw[i] = YRqraw[i+1];YRqraw[i+1] = temp;
    }
/  for (int i=0;i<128;i++){
     if (i<2) {
       qcal[0][i] = XLqraw[i] - XLqraw[i+2]; 
       qcal[1][i] = YLqraw[i] - YLqraw[i+2];
       qcal[2][i] = XRqraw[i] - XRqraw[i+2];
       qcal[3][i] = YRqraw[i] - YRqraw[i+2];
    }else if (i>125) {
       qcal[0][i] = XLqraw[i] - XLqraw[i-2]; 
       qcal[1][i] = YLqraw[i] - YLqraw[i-2];
       qcal[2][i] = XRqraw[i] - XRqraw[i-2];
       qcal[3][i] = YRqraw[i] - YRqraw[i-2];
    }else{
       qcal[0][i] = XLqraw[i] -0.5*( XLqraw[i-2]+XLqraw[i+2]); 
       qcal[1][i] = YLqraw[i] -0.5*( YLqraw[i-2]+YLqraw[i+2]);
       qcal[2][i] = XRqraw[i] -0.5*( XRqraw[i-2]+XRqraw[i+2]);
       qcal[3][i] = YRqraw[i] -0.5*( YRqraw[i-2]+YRqraw[i+2]);
    }
  } 
  for (int i=0;i<128;i++){
     qcal[0][i] = qcal[0][i]*ch2mev[0][i] - offset[0][i]; 
     qcal[1][i] = qcal[1][i]*ch2mev[1][i] - offset[1][i];
     qcal[2][i] = qcal[2][i]*ch2mev[2][i] - offset[2][i];
     qcal[3][i] = qcal[3][i]*ch2mev[3][i] - offset[3][i];
  }
*/ 
  
  for (int i=0;i<128;i++){
     qcal[0][i] = XLqraw[i]*ch2mev[0][i] - offset[0][i]; 
     qcal[1][i] = YLqraw[i]*ch2mev[1][i] - offset[1][i];
     qcal[2][i] = XRqraw[i]*ch2mev[2][i] - offset[2][i];
     qcal[3][i] = YRqraw[i]*ch2mev[3][i] - offset[3][i];
   } 
   for (int j=0;j<4;j++)
     for (int i=0;i<128;i=i+2){
       temp = qcal[j][i];qcal[j][i] = qcal[j][i+1];qcal[j][i+1] = temp; 
     }

   posXL=-100;posYL=-100;posXR=-100;posYR=-100;
   El_XL=-100;El_YL=-100;El_XR=-100;El_YR=-100;
   for (int i=0;i<128;i++){
     if (qcal[0][i]>El_XL){ El_XL = qcal[0][i]; posXL=i+1;} 
     if (qcal[1][i]>El_YL){ El_YL = qcal[1][i]; posYL=i+1;} 
     if (qcal[2][i]>El_XR){ El_XR = qcal[2][i]; posXR=i+1;} 
     if (qcal[3][i]>El_YR){ El_YR = qcal[3][i]; posYR=i+1;} 
   }
//   printf("max    %d  %f    %d  %f     %d  %f      %d  %f\n",posXL,El_XL,posYL,El_YL,posXR,El_XR,posYR,El_YR);
//   printf("max1   %f    %f     %f      %f\n",qcal[0][posXL-1],qcal[1][posYL-1],qcal[2][posXR-1],qcal[3][posYR-1]);
  return 0;
}

// ***********************************************************************
int EN_DSSD::ReadParameters(char* filename){
  
  for (int i=0;i<128;i++){
     ch2mev[0][i] =1; offset[0][i] =0; 
     ch2mev[1][i] =1; offset[1][i] =0;
     ch2mev[2][i] =1; offset[2][i] =0;
     ch2mev[3][i] =1; offset[3][i] =0;
  }  
  fi.open(filename,ios::in);
  if (fi.is_open()){
    double valread[5];
    int ii,jj;
    char* buff;
    //read ch2ns 
 //  printf("bdc prm reading\n");
    ii=0;
    jj=0;
    while (not fi.eof()){
 //  for (int i=0;i<10;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
//printf("sdsd  %s\n",buff);
       if (Put2Array(buff,valread,3) == -1) goto l20;
       offset[ii][jj] = valread[1];
       ch2mev[ii][jj] =1;
//       printf("Dssd prm  %d\t%d\t%f\t%f\n",ii,jj,offset[ii][jj],ch2mev[ii][jj]);
       jj++;
       if (jj>=128){jj=0;ii++;}
       
    }
     fi.close();
     printf("EN_DSSD: Parameters file :\"%s\" |--> LOADED!!!.\n",filename); 
     return 0;
  }else{
     printf("EN_DSSD: Parameters file :\"%s\" cannot open |--> NOT load!!!\n",filename);
     goto def;
  }
l20:  printf("EN_DSSD: Parameters file :\"%s\" not true format |--> NOT load!!!\n",filename);

def:  return -1;
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