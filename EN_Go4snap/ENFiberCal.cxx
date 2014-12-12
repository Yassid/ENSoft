#include "ENFiberCal.h"

ENFiberCal::ENFiberCal()
{
  char fn[20];
  sprintf(fn,"prm/fiber.prm");
  flagprm = ReadParameters(fn);
  analyser=1;
  printf("ENFiberCal:   Initializing - %d\n", analyser);
}
// ***********************************************************************
ENFiberCal::ENFiberCal(char* filename)
{
  flagprm = ReadParameters(filename);
  analyser=1; 
  printf("ENFiberCal:   Initializing - %d\n", analyser);
}
// ***********************************************************************
ENFiberCal::~ENFiberCal(){}
// ***********************************************************************
void ENFiberCal::ENcode(int raw[10][10][256], double val[10][10][256], int nval ){
   nfire=0;
   for (int i=0;i<128;i++){
     traw[i] = raw[analyser][1][i];
     trawt[i]= raw[analyser][2][i];
   }
  DYQ[0] = raw[analyser][3][0];
  DYQ[1] = raw[analyser][3][1];  
  SetPosition();
 // printf("F1 af  %d  %f   %f  %f\n",nfire,width,posX,posY1);
  val[analyser][1][1] = posX;
  val[analyser][1][2] = posY1;
  val[analyser][1][3] = nfire;
  val[analyser][1][4] = width;
  SetPosition1();
 // printf("F1 af  %d  %f   %f  %f\n",nfire,width,posX,posY1);
  val[analyser][1][5] = posX;
  val[analyser][1][6] = posY1;
  val[analyser][1][7] = nfire;
  val[analyser][1][8] = width;
  val[analyser][2][1] = DYQ[0];
  val[analyser][2][2] = DYQ[1];
  val[analyser][1][9] = width;
  val[analyser][1][10] = width; 
}
// ***********************************************************************
void  ENFiberCal::SetPosition(int start, int *rawin){
  //if (flagprm<0) printf("ENFiber:   Khong doc dc prm file\n");
  for (int i=0;i<128;i++){
     traw[i] = rawin[start+i];
  }
  SetPosition();
}
// ***********************************************************************
void  ENFiberCal::SetPosition1(){
  //if (flagprm<0) printf("ENFiber:   Khong doc dc prm file\n");
  for (int i=0;i<128;i++){
    tcal[i][0] = traw[i]*ch2ns[i];
    tcal[i][1] = (trawt[i]-traw[i])*ch2ns[i]; 
  }
  for (int i=0;i<300;i++){
	pos_fire[i] = -1;ch_L[i] = -1;ch_R[i]=-1;
      	width_L[i] =-100000;width_R[i] =-100000;
  }
	// 20141024 changed to NEW map 
   	if(tcal[8][0]>threshold_t){  // MA2 1
	 
	  if(tcal[105][0]>threshold_t) {nfire++;pos_fire[nfire] = 1;ch_L[nfire] = 8;ch_R[nfire] = 105;}
	  if(tcal[116][0]>threshold_t) {nfire++;pos_fire[nfire] = 2;ch_L[nfire] = 8;ch_R[nfire] = 116; }  
	  if(tcal[71][0]>threshold_t)  {nfire++;pos_fire[nfire] = 3;ch_L[nfire] = 8;ch_R[nfire] = 71; } 
	  if(tcal[81][0]>threshold_t)  {nfire++;pos_fire[nfire] = 4;ch_L[nfire] = 8;ch_R[nfire] = 81; }   
	  if(tcal[107][0]>threshold_t) {nfire++;pos_fire[nfire] = 5;ch_L[nfire] = 8;ch_R[nfire] = 107; }   
	  if(tcal[118][0]>threshold_t) {nfire++;pos_fire[nfire] = 6;ch_L[nfire] = 8;ch_R[nfire] = 118; }  
	  if(tcal[97][0]>threshold_t)  {nfire++;pos_fire[nfire] = 7;ch_L[nfire] = 8;ch_R[nfire] = 97; }  
	  if(tcal[83][0]>threshold_t)  {nfire++;pos_fire[nfire] = 8;ch_L[nfire] = 8;ch_R[nfire] = 83; } 

	}
	
	
	if(tcal[9][0]>threshold_t){ //MA2 2
	
	  if(tcal[104][0]>threshold_t) {nfire++;pos_fire[nfire] = 257;ch_L[nfire] = 9;ch_R[nfire] = 104; }  
	  if(tcal[115][0]>threshold_t) {nfire++;pos_fire[nfire] = 258;ch_L[nfire] = 9;ch_R[nfire] = 115; } 
	  if(tcal[70][0]>threshold_t)  {nfire++;pos_fire[nfire] = 259;ch_L[nfire] = 9;ch_R[nfire] = 70; }  
	  if(tcal[80][0]>threshold_t)  {nfire++;pos_fire[nfire] = 260;ch_L[nfire] = 9;ch_R[nfire] = 80; }  
	  if(tcal[106][0]>threshold_t) {nfire++;pos_fire[nfire] = 261;ch_L[nfire] = 9;ch_R[nfire] = 106; }  
	  if(tcal[117][0]>threshold_t) {nfire++;pos_fire[nfire] = 262;ch_L[nfire] = 9;ch_R[nfire] = 117; }  
	  if(tcal[96][0]>threshold_t)  {nfire++;pos_fire[nfire] = 263;ch_L[nfire] = 9;ch_R[nfire] = 96; }   
	  if(tcal[82][0]>threshold_t)  {nfire++;pos_fire[nfire] = 264;ch_L[nfire] = 9;ch_R[nfire] = 82; }   
	  
	}
	
	if(tcal[19][0]>threshold_t){ //MA2 3
	
	  if(tcal[105][0]>threshold_t) {nfire++;pos_fire[nfire] = 9; ch_L[nfire] = 19;ch_R[nfire] = 105; }    
	  if(tcal[116][0]>threshold_t) {nfire++;pos_fire[nfire] = 10;ch_L[nfire] = 19;ch_R[nfire] = 116; }  
	  if(tcal[71][0]>threshold_t)  {nfire++;pos_fire[nfire] = 11;ch_L[nfire] = 19;ch_R[nfire] = 71; }   
	  if(tcal[81][0]>threshold_t)  {nfire++;pos_fire[nfire] = 12;ch_L[nfire] = 19;ch_R[nfire] = 81; }    
	  if(tcal[107][0]>threshold_t) {nfire++;pos_fire[nfire] = 13;ch_L[nfire] = 19;ch_R[nfire] = 107; }   
	  if(tcal[118][0]>threshold_t) {nfire++;pos_fire[nfire] = 14;ch_L[nfire] = 19;ch_R[nfire] = 118; }    
	  if(tcal[97][0]>threshold_t)  {nfire++;pos_fire[nfire] = 15;ch_L[nfire] = 19;ch_R[nfire] = 97; }  
	  if(tcal[83][0]>threshold_t)  {nfire++;pos_fire[nfire] = 16;ch_L[nfire] = 19;ch_R[nfire] = 83; }   
	
	}
	
	if(tcal[20][0]>threshold_t){ //MA2 4
	
	  if(tcal[104][0]>threshold_t) {nfire++;pos_fire[nfire] = 265;ch_L[nfire] = 20;ch_R[nfire] = 104; }  
	  if(tcal[115][0]>threshold_t) {nfire++;pos_fire[nfire] = 266;ch_L[nfire] = 20;ch_R[nfire] = 115; }   
	  if(tcal[70][0]>threshold_t)  {nfire++;pos_fire[nfire] = 267;ch_L[nfire] = 20;ch_R[nfire] = 70; }     
	  if(tcal[80][0]>threshold_t)  {nfire++;pos_fire[nfire] = 268;ch_L[nfire] = 20;ch_R[nfire] = 80; }      
	  if(tcal[106][0]>threshold_t) {nfire++;pos_fire[nfire] = 269;ch_L[nfire] = 20;ch_R[nfire] = 106; }  
	  if(tcal[117][0]>threshold_t) {nfire++;pos_fire[nfire] = 270;ch_L[nfire] = 20;ch_R[nfire] = 117; }  
	  if(tcal[96][0]>threshold_t)  {nfire++;pos_fire[nfire] = 271;ch_L[nfire] = 20;ch_R[nfire] = 96; }    
	  if(tcal[82][0]>threshold_t)  {nfire++;pos_fire[nfire] = 272;ch_L[nfire] = 20;ch_R[nfire] = 82; }     
	
	}
	
	
	if(tcal[6][0]>threshold_t){  //MA2 5
	
	  if(tcal[105][0]>threshold_t) {nfire++;pos_fire[nfire] = 17;ch_L[nfire] = 6;ch_R[nfire] = 105; }  
	  if(tcal[116][0]>threshold_t) {nfire++;pos_fire[nfire] = 18;ch_L[nfire] = 6;ch_R[nfire] = 116; }   
	  if(tcal[71][0]>threshold_t)  {nfire++;pos_fire[nfire] = 19;ch_L[nfire] = 6;ch_R[nfire] = 71; }     
	  if(tcal[81][0]>threshold_t)  {nfire++;pos_fire[nfire] = 20;ch_L[nfire] = 6;ch_R[nfire] = 81; }      
	  if(tcal[107][0]>threshold_t) {nfire++;pos_fire[nfire] = 21;ch_L[nfire] = 6;ch_R[nfire] = 107; }      
	  if(tcal[118][0]>threshold_t) {nfire++;pos_fire[nfire] = 22;ch_L[nfire] = 6;ch_R[nfire] = 118; }  
	  if(tcal[97][0]>threshold_t)  {nfire++;pos_fire[nfire] = 23;ch_L[nfire] = 6;ch_R[nfire] = 97; }    
	  if(tcal[83][0]>threshold_t)  {nfire++;pos_fire[nfire] = 24;ch_L[nfire] = 6;ch_R[nfire] = 83; }     
	
	}
	
	
	if(tcal[7][0]>threshold_t){ //MA2 6
	
	  if(tcal[104][0]>threshold_t) {nfire++;pos_fire[nfire] = 273;ch_L[nfire] = 7;ch_R[nfire] = 104; } 
	  if(tcal[115][0]>threshold_t) {nfire++;pos_fire[nfire] = 274;ch_L[nfire] = 7;ch_R[nfire] = 115; }  
	  if(tcal[70][0]>threshold_t)  {nfire++;pos_fire[nfire] = 275;ch_L[nfire] = 7;ch_R[nfire] = 70; }  
	  if(tcal[80][0]>threshold_t)  {nfire++;pos_fire[nfire] = 276;ch_L[nfire] = 7;ch_R[nfire] = 80; }   
	  if(tcal[106][0]>threshold_t) {nfire++;pos_fire[nfire] = 277;ch_L[nfire] = 7;ch_R[nfire] = 106; }   
	  if(tcal[117][0]>threshold_t) {nfire++;pos_fire[nfire] = 278;ch_L[nfire] = 7;ch_R[nfire] = 117; }    
	  if(tcal[96][0]>threshold_t)  {nfire++;pos_fire[nfire] = 279;ch_L[nfire] = 7;ch_R[nfire] = 96; }      
	  if(tcal[82][0]>threshold_t)  {nfire++;pos_fire[nfire] = 280;ch_L[nfire] = 7;ch_R[nfire] = 82; }  
	
	}
	
	
	if(tcal[48][0]>threshold_t){  //MA2 7
	
	  if(tcal[105][0]>threshold_t) {nfire++;pos_fire[nfire] = 25;ch_L[nfire] = 48;ch_R[nfire] = 105; } 
	  if(tcal[116][0]>threshold_t) {nfire++;pos_fire[nfire] = 26;ch_L[nfire] = 48;ch_R[nfire] = 116; }  
	  if(tcal[71][0]>threshold_t)  {nfire++;pos_fire[nfire] = 27;ch_L[nfire] = 48;ch_R[nfire] = 71; }    
	  if(tcal[81][0]>threshold_t)  {nfire++;pos_fire[nfire] = 28;ch_L[nfire] = 48;ch_R[nfire] = 81; }     
	  if(tcal[107][0]>threshold_t) {nfire++;pos_fire[nfire] = 29;ch_L[nfire] = 48;ch_R[nfire] = 107; }     
	  if(tcal[118][0]>threshold_t) {nfire++;pos_fire[nfire] = 30;ch_L[nfire] = 48;ch_R[nfire] = 118; }      
	  if(tcal[97][0]>threshold_t)  {nfire++;pos_fire[nfire] = 31;ch_L[nfire] = 48;ch_R[nfire] = 97; }  
	  if(tcal[83][0]>threshold_t)  {nfire++;pos_fire[nfire] = 32;ch_L[nfire] = 48;ch_R[nfire] = 83; }   
	
	}
	
	
	if(tcal[49][0]>threshold_t){ //MA2 8
	
	  if(tcal[104][0]>threshold_t) {nfire++;pos_fire[nfire] = 281;ch_L[nfire] = 49;ch_R[nfire] = 104; }  
	  if(tcal[115][0]>threshold_t) {nfire++;pos_fire[nfire] = 282;ch_L[nfire] = 49;ch_R[nfire] = 115; }   
	  if(tcal[70][0]>threshold_t)  {nfire++;pos_fire[nfire] = 283;ch_L[nfire] = 49;ch_R[nfire] = 70; }  
	  if(tcal[80][0]>threshold_t)  {nfire++;pos_fire[nfire] = 284;ch_L[nfire] = 49;ch_R[nfire] = 80; }   
	  if(tcal[106][0]>threshold_t) {nfire++;pos_fire[nfire] = 285;ch_L[nfire] = 49;ch_R[nfire] = 106; }   
	  if(tcal[117][0]>threshold_t) {nfire++;pos_fire[nfire] = 286;ch_L[nfire] = 49;ch_R[nfire] = 117; } 
	  if(tcal[96][0]>threshold_t)  {nfire++;pos_fire[nfire] = 287;ch_L[nfire] = 49;ch_R[nfire] = 96; }   
	  if(tcal[82][0]>threshold_t)  {nfire++;pos_fire[nfire] = 288;ch_L[nfire] = 49;ch_R[nfire] = 82; }    
	
	}
	
	
	if(tcal[10][0]>threshold_t){  //MA2 9
	
	  if(tcal[105][0]>threshold_t) {nfire++;pos_fire[nfire] = 33;ch_L[nfire] = 10;ch_R[nfire] = 105; } 
	  if(tcal[116][0]>threshold_t) {nfire++;pos_fire[nfire] = 34;ch_L[nfire] = 10;ch_R[nfire] = 116; }  
	  if(tcal[71][0]>threshold_t)  {nfire++;pos_fire[nfire] = 35;ch_L[nfire] = 10;ch_R[nfire] = 71; }    
	  if(tcal[81][0]>threshold_t)  {nfire++;pos_fire[nfire] = 36;ch_L[nfire] = 10;ch_R[nfire] = 81; }     
	  if(tcal[107][0]>threshold_t) {nfire++;pos_fire[nfire] = 37;ch_L[nfire] = 10;ch_R[nfire] = 107; }     
	  if(tcal[118][0]>threshold_t) {nfire++;pos_fire[nfire] = 38;ch_L[nfire] = 10;ch_R[nfire] = 118; }      
	  if(tcal[97][0]>threshold_t)  {nfire++;pos_fire[nfire] = 39;ch_L[nfire] = 10;ch_R[nfire] = 97; }  
	  if(tcal[83][0]>threshold_t)  {nfire++;pos_fire[nfire] = 40;ch_L[nfire] = 10;ch_R[nfire] = 83; }   
	
	}
	
	
	if(tcal[11][0]>threshold_t){  //MA2 10
	
	  if(tcal[104][0]>threshold_t) {nfire++;pos_fire[nfire] = 289;ch_L[nfire] = 11;ch_R[nfire] = 104; }  
	  if(tcal[115][0]>threshold_t) {nfire++;pos_fire[nfire] = 290;ch_L[nfire] = 11;ch_R[nfire] = 115; }   
	  if(tcal[70][0]>threshold_t)  {nfire++;pos_fire[nfire] = 291;ch_L[nfire] = 11;ch_R[nfire] = 70; }     
	  if(tcal[80][0]>threshold_t)  {nfire++;pos_fire[nfire] = 292;ch_L[nfire] = 11;ch_R[nfire] = 80; }      
	  if(tcal[106][0]>threshold_t) {nfire++;pos_fire[nfire] = 293;ch_L[nfire] = 11;ch_R[nfire] = 106; }      
	  if(tcal[117][0]>threshold_t) {nfire++;pos_fire[nfire] = 294;ch_L[nfire] = 11;ch_R[nfire] = 117; }   
	  if(tcal[96][0]>threshold_t)  {nfire++;pos_fire[nfire] = 295;ch_L[nfire] = 11;ch_R[nfire] = 96; }     
	  if(tcal[82][0]>threshold_t)  {nfire++;pos_fire[nfire] = 296;ch_L[nfire] = 11;ch_R[nfire] = 82; }      
	
	}
	
	
	
	if(tcal[21][0]>threshold_t){  //MA2 11
	
	  if(tcal[105][0]>threshold_t) {nfire++;pos_fire[nfire] = 41;ch_L[nfire] = 21;ch_R[nfire] = 105; }  
	  if(tcal[116][0]>threshold_t) {nfire++;pos_fire[nfire] = 42;ch_L[nfire] = 21;ch_R[nfire] = 116; }   
	  if(tcal[71][0]>threshold_t)  {nfire++;pos_fire[nfire] = 43;ch_L[nfire] = 21;ch_R[nfire] = 71; }     
	  if(tcal[81][0]>threshold_t)  {nfire++;pos_fire[nfire] = 44;ch_L[nfire] = 21;ch_R[nfire] = 81; }      
	  if(tcal[107][0]>threshold_t) {nfire++;pos_fire[nfire] = 45;ch_L[nfire] = 21;ch_R[nfire] = 107; }      
	  if(tcal[118][0]>threshold_t) {nfire++;pos_fire[nfire] = 46;ch_L[nfire] = 21;ch_R[nfire] = 118; }  
	  if(tcal[97][0]>threshold_t)  {nfire++;pos_fire[nfire] = 47;ch_L[nfire] = 21;ch_R[nfire] = 97; }    
	  if(tcal[83][0]>threshold_t)  {nfire++;pos_fire[nfire] = 48;ch_L[nfire] = 21;ch_R[nfire] = 83; }     
	
	}
	
	
	if(tcal[22][0]>threshold_t){ //MA2 12
 	
	  if(tcal[104][0]>threshold_t) {nfire++;pos_fire[nfire] = 297;ch_L[nfire] = 22;ch_R[nfire] = 104; } 
	  if(tcal[115][0]>threshold_t) {nfire++;pos_fire[nfire] = 298;ch_L[nfire] = 22;ch_R[nfire] = 115; }  
	  if(tcal[70][0]>threshold_t)  {nfire++;pos_fire[nfire] = 299;ch_L[nfire] = 22;ch_R[nfire] = 70; }    
	  if(tcal[80][0]>threshold_t)  {nfire++;pos_fire[nfire] = 300;ch_L[nfire] = 22;ch_R[nfire] = 80; }     
	  if(tcal[106][0]>threshold_t) {nfire++;pos_fire[nfire] = 301;ch_L[nfire] = 22;ch_R[nfire] = 106; }     
	  if(tcal[117][0]>threshold_t) {nfire++;pos_fire[nfire] = 302;ch_L[nfire] = 22;ch_R[nfire] = 117; }      
	  if(tcal[96][0]>threshold_t)  {nfire++;pos_fire[nfire] = 303;ch_L[nfire] = 22;ch_R[nfire] = 96; }     
		
	
	}
	
	
	if(tcal[32][0]>threshold_t){ //MA2 13
	
	  if(tcal[105][0]>threshold_t) {nfire++;pos_fire[nfire] = 49;ch_L[nfire] = 32;ch_R[nfire] = 105; } 
	  if(tcal[116][0]>threshold_t) {nfire++;pos_fire[nfire] = 50;ch_L[nfire] = 32;ch_R[nfire] = 116; }  
	  if(tcal[71][0]>threshold_t)  {nfire++;pos_fire[nfire] = 51;ch_L[nfire] = 32;ch_R[nfire] = 71; }    
	  if(tcal[81][0]>threshold_t)  {nfire++;pos_fire[nfire] = 52;ch_L[nfire] = 32;ch_R[nfire] = 81; }     
	  if(tcal[107][0]>threshold_t) {nfire++;pos_fire[nfire] = 53;ch_L[nfire] = 32;ch_R[nfire] = 107; }     
	  if(tcal[118][0]>threshold_t) {nfire++;pos_fire[nfire] = 54;ch_L[nfire] = 32;ch_R[nfire] = 118; }      
	  if(tcal[97][0]>threshold_t)  {nfire++;pos_fire[nfire] = 55;ch_L[nfire] = 32;ch_R[nfire] = 97; }       
	  if(tcal[83][0]>threshold_t)  {nfire++;pos_fire[nfire] = 56;ch_L[nfire] = 32;ch_R[nfire] = 83; }       
	
	}
	
	
	
	if(tcal[50][0]>threshold_t){ //MA2 15
	
	  if(tcal[105][0]>threshold_t) {nfire++;pos_fire[nfire] = 57;ch_L[nfire] = 50;ch_R[nfire] = 105; } 
	  if(tcal[116][0]>threshold_t) {nfire++;pos_fire[nfire] = 58;ch_L[nfire] = 50;ch_R[nfire] = 116; } 
	  if(tcal[71][0]>threshold_t)  {nfire++;pos_fire[nfire] = 59;ch_L[nfire] = 50;ch_R[nfire] = 71; }   
	  if(tcal[81][0]>threshold_t)  {nfire++;pos_fire[nfire] = 60;ch_L[nfire] = 50;ch_R[nfire] = 81; }    
	  if(tcal[107][0]>threshold_t) {nfire++;pos_fire[nfire] = 61;ch_L[nfire] = 50;ch_R[nfire] = 107; }    
	  if(tcal[118][0]>threshold_t) {nfire++;pos_fire[nfire] = 62;ch_L[nfire] = 50;ch_R[nfire] = 118; }     
	  if(tcal[97][0]>threshold_t)  {nfire++;pos_fire[nfire] = 63;ch_L[nfire] = 50;ch_R[nfire] = 97; }       
	  if(tcal[83][0]>threshold_t)  {nfire++;pos_fire[nfire] = 64;ch_L[nfire] = 50;ch_R[nfire] = 83; }       
	  
	}

     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	if(tcal[12][0]>threshold_t){ //MA2 17
	
	  if(tcal[108][0]>threshold_t) {nfire++;pos_fire[nfire] = 65;ch_L[nfire] = 12;ch_R[nfire] = 108; } 
	  if(tcal[119][0]>threshold_t) {nfire++;pos_fire[nfire] = 66;ch_L[nfire] = 12;ch_R[nfire] = 119; } 
	  if(tcal[98][0]>threshold_t)  {nfire++;pos_fire[nfire] = 67;ch_L[nfire] = 12;ch_R[nfire] = 98; }   
	  if(tcal[85][0]>threshold_t)  {nfire++;pos_fire[nfire] = 68;ch_L[nfire] = 12;ch_R[nfire] = 85; }    
	  if(tcal[109][0]>threshold_t) {nfire++;pos_fire[nfire] = 69;ch_L[nfire] = 12;ch_R[nfire] = 109; }    
	  if(tcal[64][0]>threshold_t)  {nfire++;pos_fire[nfire] = 70;ch_L[nfire] = 12;ch_R[nfire] = 64; }      
	  if(tcal[99][0]>threshold_t)  {nfire++;pos_fire[nfire] = 71;ch_L[nfire] = 12;ch_R[nfire] = 99; }       
	  if(tcal[87][0]>threshold_t)  {nfire++;pos_fire[nfire] = 72;ch_L[nfire] = 12;ch_R[nfire] = 87; }   
	  
	}
	
	
	if(tcal[23][0]>threshold_t){ //MA2 19
	
	  if(tcal[108][0]>threshold_t) {nfire++;pos_fire[nfire] = 73;ch_L[nfire] = 23;ch_R[nfire] = 108; }  
	  if(tcal[119][0]>threshold_t) {nfire++;pos_fire[nfire] = 74;ch_L[nfire] = 23;ch_R[nfire] = 119; }   
	  if(tcal[98][0]>threshold_t)  {nfire++;pos_fire[nfire] = 75;ch_L[nfire] = 23;ch_R[nfire] = 98; }     
	  if(tcal[85][0]>threshold_t)  {nfire++;pos_fire[nfire] = 76;ch_L[nfire] = 23;ch_R[nfire] = 85; }      
	  if(tcal[109][0]>threshold_t) {nfire++;pos_fire[nfire] = 77;ch_L[nfire] = 23;ch_R[nfire] = 109; }      
	  if(tcal[64][0]>threshold_t)  {nfire++;pos_fire[nfire] = 78;ch_L[nfire] = 23;ch_R[nfire] = 64; }       
	  if(tcal[99][0]>threshold_t)  {nfire++;pos_fire[nfire] = 79;ch_L[nfire] = 23;ch_R[nfire] = 99; }       
	  if(tcal[87][0]>threshold_t)  {nfire++;pos_fire[nfire] = 80;ch_L[nfire] = 23;ch_R[nfire] = 87; }       
	
	}
	
	
	if(tcal[34][0]>threshold_t){//MA2 21
	
	  if(tcal[108][0]>threshold_t) {nfire++;pos_fire[nfire] = 81;ch_L[nfire] = 34;ch_R[nfire] = 108; }   
	  if(tcal[119][0]>threshold_t) {nfire++;pos_fire[nfire] = 82;ch_L[nfire] = 34;ch_R[nfire] = 119; }    
	  if(tcal[98][0]>threshold_t)  {nfire++;pos_fire[nfire] = 83;ch_L[nfire] = 34;ch_R[nfire] = 98; }      
	  if(tcal[85][0]>threshold_t)  {nfire++;pos_fire[nfire] = 84;ch_L[nfire] = 34;ch_R[nfire] = 85; }     
	  if(tcal[109][0]>threshold_t) {nfire++;pos_fire[nfire] = 85;ch_L[nfire] = 34;ch_R[nfire] = 109; }  
	  if(tcal[64][0]>threshold_t)  {nfire++;pos_fire[nfire] = 86;ch_L[nfire] = 34;ch_R[nfire] = 64; }    
	  if(tcal[99][0]>threshold_t)  {nfire++;pos_fire[nfire] = 87;ch_L[nfire] = 34;ch_R[nfire] = 99; }  
	  if(tcal[87][0]>threshold_t)  {nfire++;pos_fire[nfire] = 88;ch_L[nfire] = 34;ch_R[nfire] = 87; }   
	
	}
	
	
	if(tcal[52][0]>threshold_t){//MA2 23
	
	  if(tcal[108][0]>threshold_t) {nfire++;pos_fire[nfire] = 89;ch_L[nfire] = 52;ch_R[nfire] = 108; }    
	  if(tcal[119][0]>threshold_t) {nfire++;pos_fire[nfire] = 90;ch_L[nfire] = 52;ch_R[nfire] = 119; }  
	  if(tcal[98][0]>threshold_t)  {nfire++;pos_fire[nfire] = 91;ch_L[nfire] = 52;ch_R[nfire] = 98; }  
	  if(tcal[85][0]>threshold_t)  {nfire++;pos_fire[nfire] = 92;ch_L[nfire] = 52;ch_R[nfire] = 85; }  
	  if(tcal[109][0]>threshold_t) {nfire++;pos_fire[nfire] = 93;ch_L[nfire] = 52;ch_R[nfire] = 109; }    
	  if(tcal[64][0]>threshold_t)  {nfire++;pos_fire[nfire] = 94;ch_L[nfire] = 52;ch_R[nfire] = 64; }    
	  if(tcal[99][0]>threshold_t)  {nfire++;pos_fire[nfire] = 95;ch_L[nfire] = 52;ch_R[nfire] = 99; }     
	  if(tcal[87][0]>threshold_t)  {nfire++;pos_fire[nfire] = 96;ch_L[nfire] = 52;ch_R[nfire] = 87; }   
	
	}
	
	
		
	if(tcal[13][0]>threshold_t){//MA2 25
	
	  if(tcal[108][0]>threshold_t) {nfire++;pos_fire[nfire] = 97;ch_L[nfire] = 13;ch_R[nfire] = 108; }  
	  if(tcal[119][0]>threshold_t) {nfire++;pos_fire[nfire] = 98;ch_L[nfire] = 13;ch_R[nfire] = 119; }   
	  if(tcal[98][0]>threshold_t)  {nfire++;pos_fire[nfire] = 99;ch_L[nfire] = 13;ch_R[nfire] = 98; }   
	  if(tcal[85][0]>threshold_t)  {nfire++;pos_fire[nfire] = 100;ch_L[nfire] = 13;ch_R[nfire] = 85; }   
	  if(tcal[109][0]>threshold_t) {nfire++;pos_fire[nfire] = 101;ch_L[nfire] = 13;ch_R[nfire] = 109; } 
	  if(tcal[64][0]>threshold_t)  {nfire++;pos_fire[nfire] = 102;ch_L[nfire] = 13;ch_R[nfire] = 64; }   
	  if(tcal[99][0]>threshold_t)  {nfire++;pos_fire[nfire] = 103;ch_L[nfire] = 13;ch_R[nfire] = 99; }  
	  if(tcal[87][0]>threshold_t)  {nfire++;pos_fire[nfire] = 104;ch_L[nfire] = 13;ch_R[nfire] = 87; }  
	
	}
	
	
	if(tcal[0][0]>threshold_t){//MA2 27
	
	  if(tcal[108][0]>threshold_t) {nfire++;pos_fire[nfire] = 105;ch_L[nfire] = 0;ch_R[nfire] = 108; }   
	  if(tcal[119][0]>threshold_t) {nfire++;pos_fire[nfire] = 106;ch_L[nfire] = 0;ch_R[nfire] = 119; }  
	  if(tcal[98][0]>threshold_t)  {nfire++;pos_fire[nfire] = 107;ch_L[nfire] = 0;ch_R[nfire] = 98; }   
	  if(tcal[85][0]>threshold_t)  {nfire++;pos_fire[nfire] = 108;ch_L[nfire] = 0;ch_R[nfire] = 85; }  
	  if(tcal[109][0]>threshold_t) {nfire++;pos_fire[nfire] = 109;ch_L[nfire] = 0;ch_R[nfire] = 109; } 
	  if(tcal[64][0]>threshold_t)  {nfire++;pos_fire[nfire] = 110;ch_L[nfire] = 0;ch_R[nfire] = 64; }  
	  if(tcal[99][0]>threshold_t)  {nfire++;pos_fire[nfire] = 111;ch_L[nfire] = 0;ch_R[nfire] = 99; }  
	  if(tcal[87][0]>threshold_t)  {nfire++;pos_fire[nfire] = 112;ch_L[nfire] = 0;ch_R[nfire] = 87; }  
	
	}
	
	
	if(tcal[35][0]>threshold_t){//MA2 29
	
	  if(tcal[108][0]>threshold_t) {nfire++;pos_fire[nfire] = 113;ch_L[nfire] = 35;ch_R[nfire] = 108; }  
	  if(tcal[119][0]>threshold_t) {nfire++;pos_fire[nfire] = 114;ch_L[nfire] = 35;ch_R[nfire] = 119; }  
	  if(tcal[98][0]>threshold_t)  {nfire++;pos_fire[nfire] = 115;ch_L[nfire] = 35;ch_R[nfire] = 98; }    
	  if(tcal[85][0]>threshold_t)  {nfire++;pos_fire[nfire] = 116;ch_L[nfire] = 35;ch_R[nfire] = 85; }     
	  if(tcal[109][0]>threshold_t) {nfire++;pos_fire[nfire] = 117;ch_L[nfire] = 35;ch_R[nfire] = 109; }     
	  if(tcal[64][0]>threshold_t)  {nfire++;pos_fire[nfire] = 118;ch_L[nfire] = 35;ch_R[nfire] = 64; }       
	  if(tcal[99][0]>threshold_t)  {nfire++;pos_fire[nfire] = 119;ch_L[nfire] = 35;ch_R[nfire] = 99; } 
	  if(tcal[87][0]>threshold_t)  {nfire++;pos_fire[nfire] = 120;ch_L[nfire] = 35;ch_R[nfire] = 87; }  
	
	}
	
	if(tcal[54][0]>threshold_t){//MA2 31
	
	  if(tcal[108][0]>threshold_t) {nfire++;pos_fire[nfire] = 121;ch_L[nfire] = 54;ch_R[nfire] = 108; }  
	  if(tcal[119][0]>threshold_t) {nfire++;pos_fire[nfire] = 122;ch_L[nfire] = 54;ch_R[nfire] = 119; }   
	  if(tcal[98][0]>threshold_t)  {nfire++;pos_fire[nfire] = 123;ch_L[nfire] = 54;ch_R[nfire] = 98; }     
	  if(tcal[85][0]>threshold_t)  {nfire++;pos_fire[nfire] = 124;ch_L[nfire] = 54;ch_R[nfire] = 85; }      
	  if(tcal[109][0]>threshold_t) {nfire++;pos_fire[nfire] = 125;ch_L[nfire] = 54;ch_R[nfire] = 109; }      
	  if(tcal[64][0]>threshold_t)  {nfire++;pos_fire[nfire] = 126;ch_L[nfire] = 54;ch_R[nfire] = 64; }   
	  if(tcal[99][0]>threshold_t)  {nfire++;pos_fire[nfire] = 127;ch_L[nfire] = 54;ch_R[nfire] = 99; }    
	  if(tcal[87][0]>threshold_t)  {nfire++;pos_fire[nfire] = 128;ch_L[nfire] = 54;ch_R[nfire] = 87; }     
	
	}

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if(tcal[14][0]>threshold_t){//MA2 33
	
	  if(tcal[110][0]>threshold_t) {nfire++;pos_fire[nfire] = 129;ch_L[nfire] = 14;ch_R[nfire] = 110; }  
	  if(tcal[65][0]>threshold_t)  {nfire++;pos_fire[nfire] = 130;ch_L[nfire] = 14;ch_R[nfire] = 65; }    
	  if(tcal[100][0]>threshold_t) {nfire++;pos_fire[nfire] = 131;ch_L[nfire] = 14;ch_R[nfire] = 100; }    
	  if(tcal[89][0]>threshold_t)  {nfire++;pos_fire[nfire] = 132;ch_L[nfire] = 14;ch_R[nfire] = 89; }      
	  if(tcal[111][0]>threshold_t) {nfire++;pos_fire[nfire] = 133;ch_L[nfire] = 14;ch_R[nfire] = 111; }   
	  if(tcal[66][0]>threshold_t)  {nfire++;pos_fire[nfire] = 134;ch_L[nfire] = 14;ch_R[nfire] = 66; }     
	  if(tcal[101][0]>threshold_t) {nfire++;pos_fire[nfire] = 135;ch_L[nfire] = 14;ch_R[nfire] = 101; }     
	  if(tcal[91][0]>threshold_t)  {nfire++;pos_fire[nfire] = 136;ch_L[nfire] = 14;ch_R[nfire] = 91; }       
	  
	}
	
	
	if(tcal[1][0]>threshold_t){//MA2 35
	
	  if(tcal[110][0]>threshold_t) {nfire++;pos_fire[nfire] = 137;ch_L[nfire] = 1;ch_R[nfire] = 110; }   
	  if(tcal[65][0]>threshold_t)  {nfire++;pos_fire[nfire] = 138;ch_L[nfire] = 1;ch_R[nfire] = 65; }     
	  if(tcal[100][0]>threshold_t) {nfire++;pos_fire[nfire] = 139;ch_L[nfire] = 1;ch_R[nfire] = 100; }     
	  if(tcal[89][0]>threshold_t)  {nfire++;pos_fire[nfire] = 140;ch_L[nfire] = 1;ch_R[nfire] = 89; }       
	  if(tcal[111][0]>threshold_t) {nfire++;pos_fire[nfire] = 141;ch_L[nfire] = 1;ch_R[nfire] = 111; } 
	  if(tcal[66][0]>threshold_t)  {nfire++;pos_fire[nfire] = 142;ch_L[nfire] = 1;ch_R[nfire] = 66; }   
	  if(tcal[101][0]>threshold_t) {nfire++;pos_fire[nfire] = 143;ch_L[nfire] = 1;ch_R[nfire] = 101; }   
	  if(tcal[91][0]>threshold_t)  {nfire++;pos_fire[nfire] = 144;ch_L[nfire] = 1;ch_R[nfire] = 91; }     
	
	}
	
	
	if(tcal[36][0]>threshold_t){//MA2 37
	
	  if(tcal[110][0]>threshold_t) {nfire++;pos_fire[nfire] = 145;ch_L[nfire] = 36;ch_R[nfire] = 110; }  
	  if(tcal[65][0]>threshold_t)  {nfire++;pos_fire[nfire] = 146;ch_L[nfire] = 36;ch_R[nfire] = 65; }    
	  if(tcal[100][0]>threshold_t) {nfire++;pos_fire[nfire] = 147;ch_L[nfire] = 36;ch_R[nfire] = 100; }    
	  if(tcal[89][0]>threshold_t)  {nfire++;pos_fire[nfire] = 148;ch_L[nfire] = 36;ch_R[nfire] = 89; }      
	  if(tcal[111][0]>threshold_t) {nfire++;pos_fire[nfire] = 149;ch_L[nfire] = 36;ch_R[nfire] = 111; }      
	  if(tcal[66][0]>threshold_t)  {nfire++;pos_fire[nfire] = 150;ch_L[nfire] = 36;ch_R[nfire] = 66; }    
	  if(tcal[101][0]>threshold_t) {nfire++;pos_fire[nfire] = 151;ch_L[nfire] = 36;ch_R[nfire] = 101; }  
	  if(tcal[91][0]>threshold_t)  {nfire++;pos_fire[nfire] = 152;ch_L[nfire] = 36;ch_R[nfire] = 91; }    
	  
	}
	
	
	
	if(tcal[56][0]>threshold_t){//MA2 39
	  
	  if(tcal[110][0]>threshold_t) {nfire++;pos_fire[nfire] = 153;ch_L[nfire] = 56;ch_R[nfire] = 110; } 
	  if(tcal[65][0]>threshold_t)  {nfire++;pos_fire[nfire] = 154;ch_L[nfire] = 56;ch_R[nfire] = 65; }   
	  if(tcal[100][0]>threshold_t) {nfire++;pos_fire[nfire] = 155;ch_L[nfire] = 56;ch_R[nfire] = 100; }   
	  if(tcal[89][0]>threshold_t)  {nfire++;pos_fire[nfire] = 156;ch_L[nfire] = 56;ch_R[nfire] = 89; }     
	  if(tcal[111][0]>threshold_t) {nfire++;pos_fire[nfire] = 157;ch_L[nfire] = 56;ch_R[nfire] = 111; }     
	  if(tcal[66][0]>threshold_t)  {nfire++;pos_fire[nfire] = 158;ch_L[nfire] = 56;ch_R[nfire] = 66; }       
	  if(tcal[101][0]>threshold_t) {nfire++;pos_fire[nfire] = 159;ch_L[nfire] = 56;ch_R[nfire] = 101; }   
	  if(tcal[91][0]>threshold_t)  {nfire++;pos_fire[nfire] = 160;ch_L[nfire] = 56;ch_R[nfire] = 91; }     
	  
	}
	
	
	
	if(tcal[16][0]>threshold_t){//MA2 41
	  
	  if(tcal[110][0]>threshold_t) {nfire++;pos_fire[nfire] = 161;ch_L[nfire] = 16;ch_R[nfire] = 110; } 
	  if(tcal[65][0]>threshold_t)  {nfire++;pos_fire[nfire] = 162;ch_L[nfire] = 16;ch_R[nfire] = 65; }   
	  if(tcal[100][0]>threshold_t) {nfire++;pos_fire[nfire] = 163;ch_L[nfire] = 16;ch_R[nfire] = 100; }   
	  if(tcal[89][0]>threshold_t)  {nfire++;pos_fire[nfire] = 164;ch_L[nfire] = 16;ch_R[nfire] = 89; }     
	  if(tcal[111][0]>threshold_t) {nfire++;pos_fire[nfire] = 165;ch_L[nfire] = 16;ch_R[nfire] = 111; }     
	  if(tcal[66][0]>threshold_t)  {nfire++;pos_fire[nfire] = 166;ch_L[nfire] = 16;ch_R[nfire] = 66; }       
	  if(tcal[101][0]>threshold_t) {nfire++;pos_fire[nfire] = 167;ch_L[nfire] = 16;ch_R[nfire] = 101; } 
	  if(tcal[91][0]>threshold_t)  {nfire++;pos_fire[nfire] = 168;ch_L[nfire] = 16;ch_R[nfire] = 91; }   
	  
	}
	
	if(tcal[2][0]>threshold_t){//MA2 43
	  
	  if(tcal[110][0]>threshold_t) {nfire++;pos_fire[nfire] = 169;ch_L[nfire] = 2;ch_R[nfire] = 110; } 
	  if(tcal[65][0]>threshold_t)  {nfire++;pos_fire[nfire] = 170;ch_L[nfire] = 2;ch_R[nfire] = 65; }   
	  if(tcal[100][0]>threshold_t) {nfire++;pos_fire[nfire] = 171;ch_L[nfire] = 2;ch_R[nfire] = 100; }   
	  if(tcal[89][0]>threshold_t)  {nfire++;pos_fire[nfire] = 172;ch_L[nfire] = 2;ch_R[nfire] = 89; }     
	  if(tcal[111][0]>threshold_t) {nfire++;pos_fire[nfire] = 173;ch_L[nfire] = 2;ch_R[nfire] = 111; }     
	  if(tcal[66][0]>threshold_t)  {nfire++;pos_fire[nfire] = 174;ch_L[nfire] = 2;ch_R[nfire] = 66; }   
	  if(tcal[101][0]>threshold_t) {nfire++;pos_fire[nfire] = 175;ch_L[nfire] = 2;ch_R[nfire] = 101; }   
	  if(tcal[91][0]>threshold_t)  {nfire++;pos_fire[nfire] = 176;ch_L[nfire] = 2;ch_R[nfire] = 91; }     
	  
	}
	
	
	if(tcal[37][0]>threshold_t){//MA2 45
	  
	  if(tcal[110][0]>threshold_t) {nfire++;pos_fire[nfire] = 177;ch_L[nfire] = 37;ch_R[nfire] = 110; } 
	  if(tcal[65][0]>threshold_t)  {nfire++;pos_fire[nfire] = 178;ch_L[nfire] = 37;ch_R[nfire] = 65; }   
	  if(tcal[100][0]>threshold_t) {nfire++;pos_fire[nfire] = 179;ch_L[nfire] = 37;ch_R[nfire] = 100; }   
	  if(tcal[89][0]>threshold_t)  {nfire++;pos_fire[nfire] = 180;ch_L[nfire] = 37;ch_R[nfire] = 89; }     
	  if(tcal[111][0]>threshold_t) {nfire++;pos_fire[nfire] = 181;ch_L[nfire] = 37;ch_R[nfire] = 111; }     
	  if(tcal[66][0]>threshold_t)  {nfire++;pos_fire[nfire] = 182;ch_L[nfire] = 37;ch_R[nfire] = 66; }  
	  if(tcal[101][0]>threshold_t) {nfire++;pos_fire[nfire] = 183;ch_L[nfire] = 37;ch_R[nfire] = 101; }  
	  if(tcal[91][0]>threshold_t)  {nfire++;pos_fire[nfire] = 184;ch_L[nfire] = 37;ch_R[nfire] = 91; }    
	  
	}
	
	
	
	if(tcal[58][0]>threshold_t){//MA2 47
	   
	  if(tcal[110][0]>threshold_t) {nfire++;pos_fire[nfire] = 185;ch_L[nfire] = 58;ch_R[nfire] = 110; } 
	  if(tcal[65][0]>threshold_t)  {nfire++;pos_fire[nfire] = 186;ch_L[nfire] = 58;ch_R[nfire] = 65; }   
	  if(tcal[100][0]>threshold_t) {nfire++;pos_fire[nfire] = 187;ch_L[nfire] = 58;ch_R[nfire] = 100; }   
	  if(tcal[89][0]>threshold_t)  {nfire++;pos_fire[nfire] = 188;ch_L[nfire] = 58;ch_R[nfire] = 89; }     
	  if(tcal[111][0]>threshold_t) {nfire++;pos_fire[nfire] = 189;ch_L[nfire] = 58;ch_R[nfire] = 111; }     
	  if(tcal[66][0]>threshold_t)  {nfire++;pos_fire[nfire] = 190;ch_L[nfire] = 58;ch_R[nfire] = 66; }       
	  if(tcal[101][0]>threshold_t) {nfire++;pos_fire[nfire] = 191;ch_L[nfire] = 58;ch_R[nfire] = 101; }  
	  if(tcal[91][0]>threshold_t)  {nfire++;pos_fire[nfire] = 192;ch_L[nfire] = 58;ch_R[nfire] = 91; }    
	
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if(tcal[15][0]>threshold_t){ //MA2 49
	
	  if(tcal[112][0]>threshold_t) {nfire++;pos_fire[nfire] = 193;ch_L[nfire] = 15;ch_R[nfire] = 112; } 
	  if(tcal[67][0]>threshold_t)  {nfire++;pos_fire[nfire] = 194;ch_L[nfire] = 15;ch_R[nfire] = 67; }   
	  if(tcal[102][0]>threshold_t) {nfire++;pos_fire[nfire] = 195;ch_L[nfire] = 15;ch_R[nfire] = 102; }   
	  if(tcal[93][0]>threshold_t)  {nfire++;pos_fire[nfire] = 196;ch_L[nfire] = 15;ch_R[nfire] = 93; }     
	  if(tcal[113][0]>threshold_t) {nfire++;pos_fire[nfire] = 197;ch_L[nfire] = 15;ch_R[nfire] = 113; }    
	  if(tcal[68][0]>threshold_t)  {nfire++;pos_fire[nfire] = 198;ch_L[nfire] = 15;ch_R[nfire] = 68; }     
	  if(tcal[103][0]>threshold_t) {nfire++;pos_fire[nfire] = 199;ch_L[nfire] = 15;ch_R[nfire] = 103; }   
	  if(tcal[95][0]>threshold_t)  {nfire++;pos_fire[nfire] = 200;ch_L[nfire] = 15;ch_R[nfire] = 95; }    
	  
	}
	
	
	if(tcal[3][0]>threshold_t){ //MA2 51
	
	  if(tcal[112][0]>threshold_t) {nfire++;pos_fire[nfire] = 201;ch_L[nfire] = 3;ch_R[nfire] = 112; }    
	  if(tcal[67][0]>threshold_t)  {nfire++;pos_fire[nfire] = 202;ch_L[nfire] = 3;ch_R[nfire] = 67; }     
	  if(tcal[102][0]>threshold_t) {nfire++;pos_fire[nfire] = 203;ch_L[nfire] = 3;ch_R[nfire] = 102; }    
	  if(tcal[93][0]>threshold_t)  {nfire++;pos_fire[nfire] = 204;ch_L[nfire] = 3;ch_R[nfire] = 93; }     
	  if(tcal[113][0]>threshold_t) {nfire++;pos_fire[nfire] = 205;ch_L[nfire] = 3;ch_R[nfire] = 113; }    
	  if(tcal[68][0]>threshold_t)  {nfire++;pos_fire[nfire] = 206;ch_L[nfire] = 3;ch_R[nfire] = 68; }     
	  if(tcal[103][0]>threshold_t) {nfire++;pos_fire[nfire] = 207;ch_L[nfire] = 3;ch_R[nfire] = 103; }    
	  if(tcal[95][0]>threshold_t)  {nfire++;pos_fire[nfire] = 208;ch_L[nfire] = 3;ch_R[nfire] = 95; }     
	  
	}
	
	
	if(tcal[38][0]>threshold_t){ //MA2 53
	
	  if(tcal[112][0]>threshold_t) {nfire++;pos_fire[nfire] = 209;ch_L[nfire] = 38;ch_R[nfire] = 112; }   
	  if(tcal[67][0]>threshold_t)  {nfire++;pos_fire[nfire] = 210;ch_L[nfire] = 38;ch_R[nfire] = 67; }    
	  if(tcal[102][0]>threshold_t) {nfire++;pos_fire[nfire] = 211;ch_L[nfire] = 38;ch_R[nfire] = 102; }   
	  if(tcal[93][0]>threshold_t)  {nfire++;pos_fire[nfire] = 212;ch_L[nfire] = 38;ch_R[nfire] = 93; }    
	  if(tcal[113][0]>threshold_t) {nfire++;pos_fire[nfire] = 213;ch_L[nfire] = 38;ch_R[nfire] = 113; }   
	  if(tcal[68][0]>threshold_t)  {nfire++;pos_fire[nfire] = 214;ch_L[nfire] = 38;ch_R[nfire] = 68; }   
	  if(tcal[103][0]>threshold_t) {nfire++;pos_fire[nfire] = 215;ch_L[nfire] = 38;ch_R[nfire] = 103; }  
	  if(tcal[95][0]>threshold_t)  {nfire++;pos_fire[nfire] = 216;ch_L[nfire] = 38;ch_R[nfire] = 95; }   
	
	}
	
	
	if(tcal[60][0]>threshold_t){ //MA2 55
	   
	  if(tcal[112][0]>threshold_t) {nfire++;pos_fire[nfire] = 217;ch_L[nfire] = 60;ch_R[nfire] = 112; } 
	  if(tcal[67][0]>threshold_t)  {nfire++;pos_fire[nfire] = 218;ch_L[nfire] = 60;ch_R[nfire] = 67; }  
	  if(tcal[102][0]>threshold_t) {nfire++;pos_fire[nfire] = 219;ch_L[nfire] = 60;ch_R[nfire] = 102; } 
	  if(tcal[93][0]>threshold_t)  {nfire++;pos_fire[nfire] = 220;ch_L[nfire] = 60;ch_R[nfire] = 93; }  
	  if(tcal[113][0]>threshold_t) {nfire++;pos_fire[nfire] = 221;ch_L[nfire] = 60;ch_R[nfire] = 113; } 
	  if(tcal[68][0]>threshold_t)  {nfire++;pos_fire[nfire] = 222;ch_L[nfire] = 60;ch_R[nfire] = 68; }  
	  if(tcal[103][0]>threshold_t) {nfire++;pos_fire[nfire] = 223;ch_L[nfire] = 60;ch_R[nfire] = 103; } 
	  if(tcal[95][0]>threshold_t)  {nfire++;pos_fire[nfire] = 224;ch_L[nfire] = 60;ch_R[nfire] = 95; }  
	  
	}
	
	
	if(tcal[17][0]>threshold_t){ //MA2 57
	
	  if(tcal[112][0]>threshold_t) {nfire++;pos_fire[nfire] = 225;ch_L[nfire] = 17;ch_R[nfire] = 112; } 
	  if(tcal[67][0]>threshold_t)  {nfire++;pos_fire[nfire] = 226;ch_L[nfire] = 17;ch_R[nfire] = 67; }  
	  if(tcal[102][0]>threshold_t) {nfire++;pos_fire[nfire] = 227;ch_L[nfire] = 17;ch_R[nfire] = 102; } 
	  if(tcal[93][0]>threshold_t)  {nfire++;pos_fire[nfire] = 228;ch_L[nfire] = 17;ch_R[nfire] = 93; }  
	  if(tcal[113][0]>threshold_t) {nfire++;pos_fire[nfire] = 229;ch_L[nfire] = 17;ch_R[nfire] = 113; } 
	  if(tcal[68][0]>threshold_t)  {nfire++;pos_fire[nfire] = 230;ch_L[nfire] = 17;ch_R[nfire] = 68; }  
	  if(tcal[103][0]>threshold_t) {nfire++;pos_fire[nfire] = 231;ch_L[nfire] = 17;ch_R[nfire] = 103; } 
	  if(tcal[95][0]>threshold_t)  {nfire++;pos_fire[nfire] = 232;ch_L[nfire] = 17;ch_R[nfire] = 95; }  
	
	}
	
	
	if(tcal[4][0]>threshold_t){ //MA2 59
	
	  if(tcal[112][0]>threshold_t) {nfire++;pos_fire[nfire] = 233;ch_L[nfire] = 4;ch_R[nfire] = 112; }  
	  if(tcal[67][0]>threshold_t)  {nfire++;pos_fire[nfire] = 234;ch_L[nfire] = 4;ch_R[nfire] = 67; }   
	  if(tcal[102][0]>threshold_t) {nfire++;pos_fire[nfire] = 235;ch_L[nfire] = 4;ch_R[nfire] = 102; }  
	  if(tcal[93][0]>threshold_t)  {nfire++;pos_fire[nfire] = 236;ch_L[nfire] = 4;ch_R[nfire] = 93; }   
	  if(tcal[113][0]>threshold_t) {nfire++;pos_fire[nfire] = 237;ch_L[nfire] = 4;ch_R[nfire] = 113; }  
	  if(tcal[68][0]>threshold_t)  {nfire++;pos_fire[nfire] = 238;ch_L[nfire] = 4;ch_R[nfire] = 68; }   
	  if(tcal[103][0]>threshold_t) {nfire++;pos_fire[nfire] = 239;ch_L[nfire] = 4;ch_R[nfire] = 103; }  
	  if(tcal[95][0]>threshold_t)  {nfire++;pos_fire[nfire] = 240;ch_L[nfire] = 4;ch_R[nfire] = 95; }   
	  
	}
	
	
	if(tcal[39][0]>threshold_t){ //MA2 61
	
	  if(tcal[112][0]>threshold_t) {nfire++;pos_fire[nfire] = 241;ch_L[nfire] = 39;ch_R[nfire] = 112; } 
	  if(tcal[67][0]>threshold_t)  {nfire++;pos_fire[nfire] = 242;ch_L[nfire] = 39;ch_R[nfire] = 67; }  
	  if(tcal[102][0]>threshold_t) {nfire++;pos_fire[nfire] = 243;ch_L[nfire] = 39;ch_R[nfire] = 102; } 
	  if(tcal[93][0]>threshold_t)  {nfire++;pos_fire[nfire] = 244;ch_L[nfire] = 39;ch_R[nfire] = 93; }  
	  if(tcal[113][0]>threshold_t) {nfire++;pos_fire[nfire] = 245;ch_L[nfire] = 39;ch_R[nfire] = 113; } 
	  if(tcal[68][0]>threshold_t)  {nfire++;pos_fire[nfire] = 246;ch_L[nfire] = 39;ch_R[nfire] = 68; }  
	  if(tcal[103][0]>threshold_t) {nfire++;pos_fire[nfire] = 247;ch_L[nfire] = 39;ch_R[nfire] = 103; } 
	  if(tcal[95][0]>threshold_t)  {nfire++;pos_fire[nfire] = 248;ch_L[nfire] = 39;ch_R[nfire] = 95; }  
	  
	}
	
	
	if(tcal[62][0]>threshold_t){ //MA2 63
	  
	  if(tcal[112][0]>threshold_t) {nfire++;pos_fire[nfire] = 249;ch_L[nfire] = 62;ch_R[nfire] = 112; } 
	  if(tcal[67][0]>threshold_t)  {nfire++;pos_fire[nfire] = 250;ch_L[nfire] = 62;ch_R[nfire] = 67; }  
	  if(tcal[102][0]>threshold_t) {nfire++;pos_fire[nfire] = 251;ch_L[nfire] = 62;ch_R[nfire] = 102; } 
	  if(tcal[93][0]>threshold_t)  {nfire++;pos_fire[nfire] = 252;ch_L[nfire] = 62;ch_R[nfire] = 93; }  
	  if(tcal[113][0]>threshold_t) {nfire++;pos_fire[nfire] = 253;ch_L[nfire] = 62;ch_R[nfire] = 113; } 
	  if(tcal[68][0]>threshold_t)  {nfire++;pos_fire[nfire] = 254;ch_L[nfire] = 62;ch_R[nfire] = 68; }  
	  if(tcal[103][0]>threshold_t) {nfire++;pos_fire[nfire] = 255;ch_L[nfire] = 62;ch_R[nfire] = 103; } 
	  if(tcal[95][0]>threshold_t)  {nfire++;pos_fire[nfire] = 256;ch_L[nfire] = 62;ch_R[nfire] = 95; }  
	  
	}

	posX = -1000;posY1=-1000;
        double weimax = -1E38;
        int npos = 0;
        width = -100000;
	for(int i=1;i<nfire+1;i++){
            posY[i] = tcal[ch_L[i]][0] - tcal[ch_R[i]][0];
            weiY[i] = tcal[ch_L[i]][1] + tcal[ch_R[i]][1];
            width_L[i] = tcal[ch_L[i]][1];
	    width_R[i] = tcal[ch_R[i]][1];

            if (abs(posY[i]) < threshold_Y && tcal[ch_L[i]][1]>0 && tcal[ch_R[i]][1]>0){// && weiY[i]>weimax) {
	      if (abs(weiY[i]-2*tcal[121][0]+16800) < 300) {
		//if (abs(weiY[i]-2*tcal[121][0]+18100) < 500) {
		//cout<<i<<":"<<tcal[121][0]<<":"<<weiY[i]<<":"<<
		//weiY[i]-2*tcal[121][0]+16800<<endl;
                posX = (pos_fire[i] - 150)*ns2mm[0] - offset[0];
		posY1=posY[i]*ns2mm[1] - offset[1];
                weimax=weiY[i];
   		width = weimax;
                npos++;
  //              printf("F1  be  %d %f  %f  %f \n",npos,posX,posY1,weiY[i]);
	    }//ST
	    } 
        }
        nfire=npos;
//       if (npos>1) 
 //       printf("F1 in  %d  %f   %f  %f\n",nfire,width,posX,posY1);
}
// ***********************************************************************
void  ENFiberCal::SetPosition(){
  //if (flagprm<0) printf("ENFiber:   Khong doc dc prm file\n");
  for (int i=0;i<128;i++){
     tcal[i][0] = traw[i]*ch2ns[i];
     tcal[i][1] = (trawt[i]-traw[i])*ch2ns[i]; 
  }
     //  memset(F1FIBER_time,0,sizeof(F1FIBER_time));
     //  memset(posY,-50000.,sizeof(posY));
       for(int i=0;i<305;i++) {posY[i]=-50000.;weiY[i]=-1E38;}
     // 20141021 changed from sva02 to v7768 by S. Tera   
	// 20141024 changed to NEW map 
   	if(tcal[8][0]>threshold_t){  // MA2 1
	
	  if(tcal[105][0]>threshold_t) {posY[1]=tcal[8][0]-tcal[105][0]; weiY[1]=tcal[8][1]+tcal[105][1];}
	  if(tcal[116][0]>threshold_t) {posY[2]=tcal[8][0]-tcal[116][0]; weiY[2]=tcal[8][1]+tcal[116][1];}
	  if(tcal[71][0]>threshold_t)  {posY[3]=tcal[8][0]-tcal[71][0];  weiY[3]=tcal[8][1]+tcal[71][1];}
	  if(tcal[81][0]>threshold_t)  {posY[4]=tcal[8][0]-tcal[81][0];  weiY[4]=tcal[8][1]+tcal[81][1];}
	  if(tcal[107][0]>threshold_t) {posY[5]=tcal[8][0]-tcal[107][0]; weiY[5]=tcal[8][1]+tcal[107][1];}
	  if(tcal[118][0]>threshold_t) {posY[6]=tcal[8][0]-tcal[118][0]; weiY[6]=tcal[8][1]+tcal[118][1];}
	  if(tcal[97][0]>threshold_t)  {posY[7]=tcal[8][0]-tcal[97][0];  weiY[7]=tcal[8][1]+tcal[97][1];}
	  if(tcal[83][0]>threshold_t)  {posY[8]=tcal[8][0]-tcal[83][0];  weiY[8]=tcal[8][1]+tcal[83][1];}

	}
	
	
	if(tcal[9][0]>threshold_t){ //MA2 2
	
	  if(tcal[104][0]>threshold_t) {posY[257]=tcal[9][0]-tcal[104][0]; weiY[257]=tcal[9][1]+tcal[104][1];}
	  if(tcal[115][0]>threshold_t) {posY[258]=tcal[9][0]-tcal[115][0]; weiY[258]=tcal[9][1]+tcal[115][1];}
	  if(tcal[70][0]>threshold_t)  {posY[259]=tcal[9][0]-tcal[70][0];  weiY[259]=tcal[9][1]+tcal[70][1];}
	  if(tcal[80][0]>threshold_t)  {posY[260]=tcal[9][0]-tcal[80][0];  weiY[260]=tcal[9][1]+tcal[80][1];}
	  if(tcal[106][0]>threshold_t) {posY[261]=tcal[9][0]-tcal[106][0]; weiY[261]=tcal[9][1]+tcal[106][1];}
	  if(tcal[117][0]>threshold_t) {posY[262]=tcal[9][0]-tcal[117][0]; weiY[262]=tcal[9][1]+tcal[117][1];}
	  if(tcal[96][0]>threshold_t)  {posY[263]=tcal[9][0]-tcal[96][0];  weiY[263]=tcal[9][1]+tcal[96][1];}
	  if(tcal[82][0]>threshold_t)  {posY[264]=tcal[9][0]-tcal[82][0];  weiY[264]=tcal[9][1]+tcal[82][1];}
	  
	}
	
	if(tcal[19][0]>threshold_t){ //MA2 3
	
	  if(tcal[105][0]>threshold_t) {posY[9] =tcal[19][0]-tcal[105][0]; weiY[9] =tcal[19][1]+tcal[105][1];}
	  if(tcal[116][0]>threshold_t) {posY[10]=tcal[19][0]-tcal[116][0]; weiY[10]=tcal[19][1]+tcal[116][1];}
	  if(tcal[71][0]>threshold_t)  {posY[11]=tcal[19][0]-tcal[71][0];  weiY[11]=tcal[19][1]+tcal[71][1];}
	  if(tcal[81][0]>threshold_t)  {posY[12]=tcal[19][0]-tcal[81][0];  weiY[12]=tcal[19][1]+tcal[81][1];}
	  if(tcal[107][0]>threshold_t) {posY[13]=tcal[19][0]-tcal[107][0]; weiY[13]=tcal[19][1]+tcal[107][1];}
	  if(tcal[118][0]>threshold_t) {posY[14]=tcal[19][0]-tcal[118][0]; weiY[14]=tcal[19][1]+tcal[118][1];}
	  if(tcal[97][0]>threshold_t)  {posY[15]=tcal[19][0]-tcal[97][0];  weiY[15]=tcal[19][1]+tcal[97][1];}
	  if(tcal[83][0]>threshold_t)  {posY[16]=tcal[19][0]-tcal[83][0];  weiY[16]=tcal[19][1]+tcal[83][1];}
	
	}
	
	if(tcal[20][0]>threshold_t){ //MA2 4
	
	  if(tcal[104][0]>threshold_t) {posY[265]=tcal[20][0]-tcal[104][0]; weiY[265]=tcal[20][1]+tcal[104][1];}
	  if(tcal[115][0]>threshold_t) {posY[266]=tcal[20][0]-tcal[115][0]; weiY[266]=tcal[20][1]+tcal[115][1];}
	  if(tcal[70][0]>threshold_t)  {posY[267]=tcal[20][0]-tcal[70][0];  weiY[267]=tcal[20][1]+tcal[70][1];}
	  if(tcal[80][0]>threshold_t)  {posY[268]=tcal[20][0]-tcal[80][0];  weiY[268]=tcal[20][1]+tcal[80][1];}
	  if(tcal[106][0]>threshold_t) {posY[269]=tcal[20][0]-tcal[106][0]; weiY[269]=tcal[20][1]+tcal[106][1];}
	  if(tcal[117][0]>threshold_t) {posY[270]=tcal[20][0]-tcal[117][0]; weiY[270]=tcal[20][1]+tcal[117][1];}
	  if(tcal[96][0]>threshold_t)  {posY[271]=tcal[20][0]-tcal[96][0];  weiY[271]=tcal[20][1]+tcal[96][1];}
	  if(tcal[82][0]>threshold_t)  {posY[272]=tcal[20][0]-tcal[82][0];  weiY[272]=tcal[20][1]+tcal[82][1];}
	
	}
	
	
	if(tcal[6][0]>threshold_t){  //MA2 5
	
	  if(tcal[105][0]>threshold_t) {posY[17]=tcal[6][0]-tcal[105][0]; weiY[17]=tcal[6][1]+tcal[105][1];}
	  if(tcal[116][0]>threshold_t) {posY[18]=tcal[6][0]-tcal[116][0]; weiY[18]=tcal[6][1]+tcal[116][1];}
	  if(tcal[71][0]>threshold_t)  {posY[19]=tcal[6][0]-tcal[71][0];  weiY[19]=tcal[6][1]+tcal[71][1];}
	  if(tcal[81][0]>threshold_t)  {posY[20]=tcal[6][0]-tcal[81][0];  weiY[20]=tcal[6][1]+tcal[81][1];}
	  if(tcal[107][0]>threshold_t) {posY[21]=tcal[6][0]-tcal[107][0]; weiY[21]=tcal[6][1]+tcal[107][1];}
	  if(tcal[118][0]>threshold_t) {posY[22]=tcal[6][0]-tcal[118][0]; weiY[22]=tcal[6][1]+tcal[118][1];}
	  if(tcal[97][0]>threshold_t)  {posY[23]=tcal[6][0]-tcal[97][0];  weiY[23]=tcal[6][1]+tcal[97][1];}
	  if(tcal[83][0]>threshold_t)  {posY[24]=tcal[6][0]-tcal[83][0];  weiY[24]=tcal[6][1]+tcal[83][1];}
	
	}
	
	
	if(tcal[7][0]>threshold_t){ //MA2 6
	
	  if(tcal[104][0]>threshold_t) {posY[273]=tcal[7][0]-tcal[104][0]; weiY[273]=tcal[7][1]+tcal[104][1];}
	  if(tcal[115][0]>threshold_t) {posY[274]=tcal[7][0]-tcal[115][0]; weiY[274]=tcal[7][1]+tcal[115][1];}
	  if(tcal[70][0]>threshold_t)  {posY[275]=tcal[7][0]-tcal[70][0];  weiY[275]=tcal[7][1]+tcal[70][1];}
	  if(tcal[80][0]>threshold_t)  {posY[276]=tcal[7][0]-tcal[80][0];  weiY[276]=tcal[7][1]+tcal[80][1];}
	  if(tcal[106][0]>threshold_t) {posY[277]=tcal[7][0]-tcal[106][0]; weiY[277]=tcal[7][1]+tcal[106][1];}
	  if(tcal[117][0]>threshold_t) {posY[278]=tcal[7][0]-tcal[117][0]; weiY[278]=tcal[7][1]+tcal[117][1];}
	  if(tcal[96][0]>threshold_t)  {posY[279]=tcal[7][0]-tcal[96][0];  weiY[279]=tcal[7][1]+tcal[96][1];}
	  if(tcal[82][0]>threshold_t)  {posY[280]=tcal[7][0]-tcal[82][0];  weiY[280]=tcal[7][1]+tcal[82][1];}
	
	}
	
	
	if(tcal[48][0]>threshold_t){  //MA2 7
	
	  if(tcal[105][0]>threshold_t) {posY[25]=tcal[48][0]-tcal[105][0]; weiY[25]=tcal[48][1]+tcal[105][1];}
	  if(tcal[116][0]>threshold_t) {posY[26]=tcal[48][0]-tcal[116][0]; weiY[26]=tcal[48][1]+tcal[116][1];}
	  if(tcal[71][0]>threshold_t)  {posY[27]=tcal[48][0]-tcal[71][0];  weiY[27]=tcal[48][1]+tcal[71][1];}
	  if(tcal[81][0]>threshold_t)  {posY[28]=tcal[48][0]-tcal[81][0];  weiY[28]=tcal[48][1]+tcal[81][1];}
	  if(tcal[107][0]>threshold_t) {posY[29]=tcal[48][0]-tcal[107][0]; weiY[29]=tcal[48][1]+tcal[107][1];}
	  if(tcal[118][0]>threshold_t) {posY[30]=tcal[48][0]-tcal[118][0]; weiY[30]=tcal[48][1]+tcal[118][1];}
	  if(tcal[97][0]>threshold_t)  {posY[31]=tcal[48][0]-tcal[97][0];  weiY[31]=tcal[48][1]+tcal[97][1];}
	  if(tcal[83][0]>threshold_t)  {posY[32]=tcal[48][0]-tcal[83][0];  weiY[32]=tcal[48][1]+tcal[83][1];}
	
	}
	
	
	if(tcal[49][0]>threshold_t){ //MA2 8
	
	  if(tcal[104][0]>threshold_t) {posY[281]=tcal[49][0]-tcal[104][0]; weiY[281]=tcal[49][1]+tcal[104][1];}
	  if(tcal[115][0]>threshold_t) {posY[282]=tcal[49][0]-tcal[115][0]; weiY[282]=tcal[49][1]+tcal[115][1];}
	  if(tcal[70][0]>threshold_t)  {posY[283]=tcal[49][0]-tcal[70][0];  weiY[283]=tcal[49][1]+tcal[70][1];}
	  if(tcal[80][0]>threshold_t)  {posY[284]=tcal[49][0]-tcal[80][0];  weiY[284]=tcal[49][1]+tcal[80][1];}
	  if(tcal[106][0]>threshold_t) {posY[285]=tcal[49][0]-tcal[106][0]; weiY[285]=tcal[49][1]+tcal[106][1];}
	  if(tcal[117][0]>threshold_t) {posY[286]=tcal[49][0]-tcal[117][0]; weiY[286]=tcal[49][1]+tcal[117][1];}
	  if(tcal[96][0]>threshold_t)  {posY[287]=tcal[49][0]-tcal[96][0];  weiY[287]=tcal[49][1]+tcal[96][1];}
	  if(tcal[82][0]>threshold_t)  {posY[288]=tcal[49][0]-tcal[82][0];  weiY[288]=tcal[49][1]+tcal[82][1];}
	
	}
	
	
	if(tcal[10][0]>threshold_t){  //MA2 9
	
	  if(tcal[105][0]>threshold_t) {posY[33]=tcal[10][0]-tcal[105][0]; weiY[33]=tcal[10][1]+tcal[105][1];}
	  if(tcal[116][0]>threshold_t) {posY[34]=tcal[10][0]-tcal[116][0]; weiY[34]=tcal[10][1]+tcal[116][1];}
	  if(tcal[71][0]>threshold_t)  {posY[35]=tcal[10][0]-tcal[71][0];  weiY[35]=tcal[10][1]+tcal[71][1];}
	  if(tcal[81][0]>threshold_t)  {posY[36]=tcal[10][0]-tcal[81][0];  weiY[36]=tcal[10][1]+tcal[81][1];}
	  if(tcal[107][0]>threshold_t) {posY[37]=tcal[10][0]-tcal[107][0]; weiY[37]=tcal[10][1]+tcal[107][1];}
	  if(tcal[118][0]>threshold_t) {posY[38]=tcal[10][0]-tcal[118][0]; weiY[38]=tcal[10][1]+tcal[118][1];}
	  if(tcal[97][0]>threshold_t)  {posY[39]=tcal[10][0]-tcal[97][0];  weiY[39]=tcal[10][1]+tcal[97][1];}
	  if(tcal[83][0]>threshold_t)  {posY[40]=tcal[10][0]-tcal[83][0];  weiY[40]=tcal[10][1]+tcal[83][1];}
	
	}
	
	
	if(tcal[11][0]>threshold_t){  //MA2 10
	
	  if(tcal[104][0]>threshold_t) {posY[289]=tcal[11][0]-tcal[104][0]; weiY[289]=tcal[11][1]+tcal[104][1];}
	  if(tcal[115][0]>threshold_t) {posY[290]=tcal[11][0]-tcal[115][0]; weiY[290]=tcal[11][1]+tcal[115][1];}
	  if(tcal[70][0]>threshold_t)  {posY[291]=tcal[11][0]-tcal[70][0];  weiY[291]=tcal[11][1]+tcal[70][1];}
	  if(tcal[80][0]>threshold_t)  {posY[292]=tcal[11][0]-tcal[80][0];  weiY[292]=tcal[11][1]+tcal[80][1];}
	  if(tcal[106][0]>threshold_t) {posY[293]=tcal[11][0]-tcal[106][0]; weiY[293]=tcal[11][1]+tcal[106][1];}
	  if(tcal[117][0]>threshold_t) {posY[294]=tcal[11][0]-tcal[117][0]; weiY[294]=tcal[11][1]+tcal[117][1];}
	  if(tcal[96][0]>threshold_t)  {posY[295]=tcal[11][0]-tcal[96][0];  weiY[295]=tcal[11][1]+tcal[96][1];}
	  if(tcal[82][0]>threshold_t)  {posY[296]=tcal[11][0]-tcal[82][0];  weiY[296]=tcal[11][1]+tcal[82][1];}
	
	}
	
	
	
	if(tcal[21][0]>threshold_t){  //MA2 11
	
	  if(tcal[105][0]>threshold_t) {posY[41]=tcal[21][0]-tcal[105][0]; weiY[41]=tcal[21][1]+tcal[105][1];}
	  if(tcal[116][0]>threshold_t) {posY[42]=tcal[21][0]-tcal[116][0]; weiY[42]=tcal[21][1]+tcal[116][1];}
	  if(tcal[71][0]>threshold_t)  {posY[43]=tcal[21][0]-tcal[71][0];  weiY[43]=tcal[21][1]+tcal[71][1];}
	  if(tcal[81][0]>threshold_t)  {posY[44]=tcal[21][0]-tcal[81][0];  weiY[44]=tcal[21][1]+tcal[81][1];}
	  if(tcal[107][0]>threshold_t) {posY[45]=tcal[21][0]-tcal[107][0]; weiY[45]=tcal[21][1]+tcal[107][1];}
	  if(tcal[118][0]>threshold_t) {posY[46]=tcal[21][0]-tcal[118][0]; weiY[46]=tcal[21][1]+tcal[118][1];}
	  if(tcal[97][0]>threshold_t)  {posY[47]=tcal[21][0]-tcal[97][0];  weiY[47]=tcal[21][1]+tcal[97][1];}
	  if(tcal[83][0]>threshold_t)  {posY[48]=tcal[21][0]-tcal[83][0];  weiY[48]=tcal[21][1]+tcal[83][1];}
	
	}
	
	
	if(tcal[22][0]>threshold_t){ //MA2 12
 	
	  if(tcal[104][0]>threshold_t) {posY[297]=tcal[22][0]-tcal[104][0]; weiY[297]=tcal[22][1]+tcal[104][1];}
	  if(tcal[115][0]>threshold_t) {posY[298]=tcal[22][0]-tcal[115][0]; weiY[298]=tcal[22][1]+tcal[115][1];}
	  if(tcal[70][0]>threshold_t)  {posY[299]=tcal[22][0]-tcal[70][0];  weiY[299]=tcal[22][1]+tcal[70][1];}
	  if(tcal[80][0]>threshold_t)  {posY[300]=tcal[22][0]-tcal[80][0];  weiY[300]=tcal[22][1]+tcal[80][1];}
	  if(tcal[106][0]>threshold_t) {posY[301]=tcal[22][0]-tcal[106][0]; weiY[301]=tcal[22][1]+tcal[106][1];}
	  if(tcal[117][0]>threshold_t) {posY[302]=tcal[22][0]-tcal[117][0]; weiY[302]=tcal[22][1]+tcal[117][1];}
	  if(tcal[96][0]>threshold_t)  {posY[303]=tcal[22][0]-tcal[96][0];  weiY[303]=tcal[22][1]+tcal[96][1];}
		
	
	}
	
	
	if(tcal[32][0]>threshold_t){ //MA2 13
	
	  if(tcal[105][0]>threshold_t) {posY[49]=tcal[32][0]-tcal[105][0]; weiY[49]=tcal[32][1]+tcal[105][1];}
	  if(tcal[116][0]>threshold_t) {posY[50]=tcal[32][0]-tcal[116][0]; weiY[50]=tcal[32][1]+tcal[116][1];}
	  if(tcal[71][0]>threshold_t)  {posY[51]=tcal[32][0]-tcal[71][0];  weiY[51]=tcal[32][1]+tcal[71][1];}
	  if(tcal[81][0]>threshold_t)  {posY[52]=tcal[32][0]-tcal[81][0];  weiY[52]=tcal[32][1]+tcal[81][1];}
	  if(tcal[107][0]>threshold_t) {posY[53]=tcal[32][0]-tcal[107][0]; weiY[53]=tcal[32][1]+tcal[107][1];}
	  if(tcal[118][0]>threshold_t) {posY[54]=tcal[32][0]-tcal[118][0]; weiY[54]=tcal[32][1]+tcal[118][1];}
	  if(tcal[97][0]>threshold_t)  {posY[55]=tcal[32][0]-tcal[97][0];  weiY[55]=tcal[32][1]+tcal[97][1];}
	  if(tcal[83][0]>threshold_t)  {posY[56]=tcal[32][0]-tcal[83][0];  weiY[56]=tcal[32][1]+tcal[83][1];}
	
	}
	
	
	
	if(tcal[50][0]>threshold_t){ //MA2 15
	
	  if(tcal[105][0]>threshold_t) {posY[57]=tcal[50][0]-tcal[105][0]; weiY[57]=tcal[50][1]+tcal[105][1];}
	  if(tcal[116][0]>threshold_t) {posY[58]=tcal[50][0]-tcal[116][0]; weiY[58]=tcal[50][1]+tcal[116][1];}
	  if(tcal[71][0]>threshold_t)  {posY[59]=tcal[50][0]-tcal[71][0];  weiY[59]=tcal[50][1]+tcal[71][1];}
	  if(tcal[81][0]>threshold_t)  {posY[60]=tcal[50][0]-tcal[81][0];  weiY[60]=tcal[50][1]+tcal[81][1];}
	  if(tcal[107][0]>threshold_t) {posY[61]=tcal[50][0]-tcal[107][0]; weiY[61]=tcal[50][1]+tcal[107][1];}
	  if(tcal[118][0]>threshold_t) {posY[62]=tcal[50][0]-tcal[118][0]; weiY[62]=tcal[50][1]+tcal[118][1];}
	  if(tcal[97][0]>threshold_t)  {posY[63]=tcal[50][0]-tcal[97][0];  weiY[63]=tcal[50][1]+tcal[97][1];}
	  if(tcal[83][0]>threshold_t)  {posY[64]=tcal[50][0]-tcal[83][0];  weiY[64]=tcal[50][1]+tcal[83][1];}
	  
	}

     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	if(tcal[12][0]>threshold_t){ //MA2 17
	
	  if(tcal[108][0]>threshold_t) {posY[65]=tcal[12][0]-tcal[108][0]; weiY[65]=tcal[12][1]+tcal[108][1];}
	  if(tcal[119][0]>threshold_t) {posY[66]=tcal[12][0]-tcal[119][0]; weiY[66]=tcal[12][1]+tcal[119][1];}
	  if(tcal[98][0]>threshold_t)  {posY[67]=tcal[12][0]-tcal[98][0];  weiY[67]=tcal[12][1]+tcal[98][1];}
	  if(tcal[85][0]>threshold_t)  {posY[68]=tcal[12][0]-tcal[85][0];  weiY[68]=tcal[12][1]+tcal[85][1];}
	  if(tcal[109][0]>threshold_t) {posY[69]=tcal[12][0]-tcal[109][0]; weiY[69]=tcal[12][1]+tcal[109][1];}
	  if(tcal[64][0]>threshold_t)  {posY[70]=tcal[12][0]-tcal[64][0];  weiY[70]=tcal[12][1]+tcal[64][1];}
	  if(tcal[99][0]>threshold_t)  {posY[71]=tcal[12][0]-tcal[99][0];  weiY[71]=tcal[12][1]+tcal[99][1];}
	  if(tcal[87][0]>threshold_t)  {posY[72]=tcal[12][0]-tcal[87][0];  weiY[72]=tcal[12][1]+tcal[87][1];}
	  
	}
	
	
	if(tcal[23][0]>threshold_t){ //MA2 19
	
	  if(tcal[108][0]>threshold_t) {posY[73]=tcal[23][0]-tcal[108][0]; weiY[73]=tcal[23][1]+tcal[108][1];}
	  if(tcal[119][0]>threshold_t) {posY[74]=tcal[23][0]-tcal[119][0]; weiY[74]=tcal[23][1]+tcal[119][1];}
	  if(tcal[98][0]>threshold_t)  {posY[75]=tcal[23][0]-tcal[98][0];  weiY[75]=tcal[23][1]+tcal[98][1];}
	  if(tcal[85][0]>threshold_t)  {posY[76]=tcal[23][0]-tcal[85][0];  weiY[76]=tcal[23][1]+tcal[85][1];}
	  if(tcal[109][0]>threshold_t) {posY[77]=tcal[23][0]-tcal[109][0]; weiY[77]=tcal[23][1]+tcal[109][1];}
	  if(tcal[64][0]>threshold_t)  {posY[78]=tcal[23][0]-tcal[64][0];  weiY[78]=tcal[23][1]+tcal[64][1];}
	  if(tcal[99][0]>threshold_t)  {posY[79]=tcal[23][0]-tcal[99][0];  weiY[79]=tcal[23][1]+tcal[99][1];}
	  if(tcal[87][0]>threshold_t)  {posY[80]=tcal[23][0]-tcal[87][0];  weiY[80]=tcal[23][1]+tcal[87][1];}
	
	}
	
	
	if(tcal[34][0]>threshold_t){//MA2 21
	
	  if(tcal[108][0]>threshold_t) {posY[81]=tcal[34][0]-tcal[108][0]; weiY[81]=tcal[34][1]+tcal[108][1];}
	  if(tcal[119][0]>threshold_t) {posY[82]=tcal[34][0]-tcal[119][0]; weiY[82]=tcal[34][1]+tcal[119][1];}
	  if(tcal[98][0]>threshold_t)  {posY[83]=tcal[34][0]-tcal[98][0];  weiY[83]=tcal[34][1]+tcal[98][1];}
	  if(tcal[85][0]>threshold_t)  {posY[84]=tcal[34][0]-tcal[85][0];  weiY[84]=tcal[34][1]+tcal[85][1];}
	  if(tcal[109][0]>threshold_t) {posY[85]=tcal[34][0]-tcal[109][0]; weiY[85]=tcal[34][1]+tcal[109][1];} 
	  if(tcal[64][0]>threshold_t)  {posY[86]=tcal[34][0]-tcal[64][0];  weiY[86]=tcal[34][1]+tcal[64][1];}
	  if(tcal[99][0]>threshold_t)  {posY[87]=tcal[34][0]-tcal[99][0];  weiY[87]=tcal[34][1]+tcal[99][1];}
	  if(tcal[87][0]>threshold_t)  {posY[88]=tcal[34][0]-tcal[87][0];  weiY[88]=tcal[34][1]+tcal[87][1];}
	
	}
	
	
	if(tcal[52][0]>threshold_t){//MA2 23
	
	  if(tcal[108][0]>threshold_t) {posY[89]=tcal[52][0]-tcal[108][0]; weiY[89]=tcal[52][1]+tcal[108][1];}
	  if(tcal[119][0]>threshold_t) {posY[90]=tcal[52][0]-tcal[119][0]; weiY[90]=tcal[52][1]+tcal[119][1];}
	  if(tcal[98][0]>threshold_t)  {posY[91]=tcal[52][0]-tcal[98][0];  weiY[91]=tcal[52][1]+tcal[98][1];}
	  if(tcal[85][0]>threshold_t)  {posY[92]=tcal[52][0]-tcal[85][0];  weiY[92]=tcal[52][1]+tcal[85][1];}
	  if(tcal[109][0]>threshold_t) {posY[93]=tcal[52][0]-tcal[109][0]; weiY[93]=tcal[52][1]+tcal[109][1];}
	  if(tcal[64][0]>threshold_t)  {posY[94]=tcal[52][0]-tcal[64][0];  weiY[94]=tcal[52][1]+tcal[64][1];}
	  if(tcal[99][0]>threshold_t)  {posY[95]=tcal[52][0]-tcal[99][0];  weiY[95]=tcal[52][1]+tcal[99][1];}
	  if(tcal[87][0]>threshold_t)  {posY[96]=tcal[52][0]-tcal[87][0];  weiY[96]=tcal[52][1]+tcal[87][1];}
	
	}
	
	
		
	if(tcal[13][0]>threshold_t){//MA2 25
	
	  if(tcal[108][0]>threshold_t) {posY[97]=tcal[13][0]-tcal[108][0]; weiY[97]=tcal[13][1]+tcal[108][1];}
	  if(tcal[119][0]>threshold_t) {posY[98]=tcal[13][0]-tcal[119][0]; weiY[98]=tcal[13][1]+tcal[119][1];}
	  if(tcal[98][0]>threshold_t)  {posY[99]=tcal[13][0]-tcal[98][0];  weiY[99]=tcal[13][1]+tcal[98][1];}
	  if(tcal[85][0]>threshold_t)  {posY[100]=tcal[13][0]-tcal[85][0]; weiY[100]=tcal[13][1]+tcal[85][1];}
	  if(tcal[109][0]>threshold_t) {posY[101]=tcal[13][0]-tcal[109][0]; weiY[101]=tcal[13][1]+tcal[109][1];}
	  if(tcal[64][0]>threshold_t)  {posY[102]=tcal[13][0]-tcal[64][0]; weiY[102]=tcal[13][1]+tcal[64][1];}
	  if(tcal[99][0]>threshold_t)  {posY[103]=tcal[13][0]-tcal[99][0]; weiY[103]=tcal[13][1]+tcal[99][1];}
	  if(tcal[87][0]>threshold_t)  {posY[104]=tcal[13][0]-tcal[87][0]; weiY[104]=tcal[13][1]+tcal[87][1];}
	
	}
	
	
	if(tcal[0][0]>threshold_t){//MA2 27
	
	  if(tcal[108][0]>threshold_t) {posY[105]=tcal[0][0]-tcal[108][0]; weiY[105]=tcal[0][1]+tcal[108][1];}
	  if(tcal[119][0]>threshold_t) {posY[106]=tcal[0][0]-tcal[119][0]; weiY[106]=tcal[0][1]+tcal[119][1];}
	  if(tcal[98][0]>threshold_t)  {posY[107]=tcal[0][0]-tcal[98][0];  weiY[107]=tcal[0][1]+tcal[98][1];}
	  if(tcal[85][0]>threshold_t)  {posY[108]=tcal[0][0]-tcal[85][0];  weiY[108]=tcal[0][1]+tcal[85][1];}
	  if(tcal[109][0]>threshold_t) {posY[109]=tcal[0][0]-tcal[109][0]; weiY[109]=tcal[0][1]+tcal[109][1];}
	  if(tcal[64][0]>threshold_t)  {posY[110]=tcal[0][0]-tcal[64][0];  weiY[110]=tcal[0][1]+tcal[64][1];}
	  if(tcal[99][0]>threshold_t)  {posY[111]=tcal[0][0]-tcal[99][0];  weiY[111]=tcal[0][1]+tcal[99][1];}
	  if(tcal[87][0]>threshold_t)  {posY[112]=tcal[0][0]-tcal[87][0];  weiY[112]=tcal[0][1]+tcal[87][1];}
	
	}
	
	
	if(tcal[35][0]>threshold_t){//MA2 29
	
	  if(tcal[108][0]>threshold_t) {posY[113]=tcal[35][0]-tcal[108][0]; weiY[113]=tcal[35][1]+tcal[108][1];}
	  if(tcal[119][0]>threshold_t) {posY[114]=tcal[35][0]-tcal[119][0]; weiY[114]=tcal[35][1]+tcal[119][1];}
	  if(tcal[98][0]>threshold_t)  {posY[115]=tcal[35][0]-tcal[98][0];  weiY[115]=tcal[35][1]+tcal[98][1];}
	  if(tcal[85][0]>threshold_t)  {posY[116]=tcal[35][0]-tcal[85][0];  weiY[116]=tcal[35][1]+tcal[85][1];}
	  if(tcal[109][0]>threshold_t) {posY[117]=tcal[35][0]-tcal[109][0]; weiY[117]=tcal[35][1]+tcal[109][1];}
	  if(tcal[64][0]>threshold_t)  {posY[118]=tcal[35][0]-tcal[64][0];  weiY[118]=tcal[35][1]+tcal[64][1];}
	  if(tcal[99][0]>threshold_t)  {posY[119]=tcal[35][0]-tcal[99][0];  weiY[119]=tcal[35][1]+tcal[99][1];}
	  if(tcal[87][0]>threshold_t)  {posY[120]=tcal[35][0]-tcal[87][0];  weiY[120]=tcal[35][1]+tcal[87][1];}
	
	}
	
	if(tcal[54][0]>threshold_t){//MA2 31
	
	  if(tcal[108][0]>threshold_t) {posY[121]=tcal[54][0]-tcal[108][0]; weiY[121]=tcal[54][1]+tcal[108][1];}
	  if(tcal[119][0]>threshold_t) {posY[122]=tcal[54][0]-tcal[119][0]; weiY[122]=tcal[54][1]+tcal[119][1];}
	  if(tcal[98][0]>threshold_t)  {posY[123]=tcal[54][0]-tcal[98][0];  weiY[123]=tcal[54][1]+tcal[98][1];}
	  if(tcal[85][0]>threshold_t)  {posY[124]=tcal[54][0]-tcal[85][0];  weiY[124]=tcal[54][1]+tcal[85][1];}
	  if(tcal[109][0]>threshold_t) {posY[125]=tcal[54][0]-tcal[109][0]; weiY[125]=tcal[54][1]+tcal[109][1];}
	  if(tcal[64][0]>threshold_t)  {posY[126]=tcal[54][0]-tcal[64][0];  weiY[126]=tcal[54][1]+tcal[64][1];}
	  if(tcal[99][0]>threshold_t)  {posY[127]=tcal[54][0]-tcal[99][0];  weiY[127]=tcal[54][1]+tcal[99][1];}
	  if(tcal[87][0]>threshold_t)  {posY[128]=tcal[54][0]-tcal[87][0];  weiY[128]=tcal[54][1]+tcal[87][1];}
	
	}

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if(tcal[14][0]>threshold_t){//MA2 33
	
	  if(tcal[110][0]>threshold_t) {posY[129]=tcal[14][0]-tcal[110][0]; weiY[129]=tcal[14][1]+tcal[110][1];}
	  if(tcal[65][0]>threshold_t)  {posY[130]=tcal[14][0]-tcal[65][0];  weiY[130]=tcal[14][1]+tcal[65][1];}
	  if(tcal[100][0]>threshold_t) {posY[131]=tcal[14][0]-tcal[100][0]; weiY[131]=tcal[14][1]+tcal[100][1];}
	  if(tcal[89][0]>threshold_t)  {posY[132]=tcal[14][0]-tcal[89][0];  weiY[132]=tcal[14][1]+tcal[89][1];}
	  if(tcal[111][0]>threshold_t) {posY[133]=tcal[14][0]-tcal[111][0]; weiY[133]=tcal[14][1]+tcal[111][1];}
	  if(tcal[66][0]>threshold_t)  {posY[134]=tcal[14][0]-tcal[66][0];  weiY[134]=tcal[14][1]+tcal[66][1];}
	  if(tcal[101][0]>threshold_t) {posY[135]=tcal[14][0]-tcal[101][0]; weiY[135]=tcal[14][1]+tcal[101][1];}
	  if(tcal[91][0]>threshold_t)  {posY[136]=tcal[14][0]-tcal[91][0];  weiY[136]=tcal[14][1]+tcal[91][1];}
	  
	}
	
	
	if(tcal[1][0]>threshold_t){//MA2 35
	
	  if(tcal[110][0]>threshold_t) {posY[137]=tcal[1][0]-tcal[110][0]; weiY[137]=tcal[1][1]+tcal[110][1];}
	  if(tcal[65][0]>threshold_t)  {posY[138]=tcal[1][0]-tcal[65][0];  weiY[138]=tcal[1][1]+tcal[65][1];}
	  if(tcal[100][0]>threshold_t) {posY[139]=tcal[1][0]-tcal[100][0]; weiY[139]=tcal[1][1]+tcal[100][1];}
	  if(tcal[89][0]>threshold_t)  {posY[140]=tcal[1][0]-tcal[89][0];  weiY[140]=tcal[1][1]+tcal[89][1];}
	  if(tcal[111][0]>threshold_t) {posY[141]=tcal[1][0]-tcal[111][0]; weiY[141]=tcal[1][1]+tcal[111][1];}
	  if(tcal[66][0]>threshold_t)  {posY[142]=tcal[1][0]-tcal[66][0];  weiY[142]=tcal[1][1]+tcal[66][1];}
	  if(tcal[101][0]>threshold_t) {posY[143]=tcal[1][0]-tcal[101][0]; weiY[143]=tcal[1][1]+tcal[101][1];}
	  if(tcal[91][0]>threshold_t)  {posY[144]=tcal[1][0]-tcal[91][0];  weiY[144]=tcal[1][1]+tcal[91][1];}
	
	}
	
	
	if(tcal[36][0]>threshold_t){//MA2 37
	
	  if(tcal[110][0]>threshold_t) {posY[145]=tcal[36][0]-tcal[110][0]; weiY[145]=tcal[36][1]+tcal[110][1];}
	  if(tcal[65][0]>threshold_t)  {posY[146]=tcal[36][0]-tcal[65][0];  weiY[146]=tcal[36][1]+tcal[65][1];}
	  if(tcal[100][0]>threshold_t) {posY[147]=tcal[36][0]-tcal[100][0]; weiY[147]=tcal[36][1]+tcal[100][1];}
	  if(tcal[89][0]>threshold_t)  {posY[148]=tcal[36][0]-tcal[89][0];  weiY[148]=tcal[36][1]+tcal[89][1];}
	  if(tcal[111][0]>threshold_t) {posY[149]=tcal[36][0]-tcal[111][0]; weiY[149]=tcal[36][1]+tcal[111][1];}
	  if(tcal[66][0]>threshold_t)  {posY[150]=tcal[36][0]-tcal[66][0];  weiY[150]=tcal[36][1]+tcal[66][1];}
	  if(tcal[101][0]>threshold_t) {posY[151]=tcal[36][0]-tcal[101][0]; weiY[151]=tcal[36][1]+tcal[101][1];}
	  if(tcal[91][0]>threshold_t)  {posY[152]=tcal[36][0]-tcal[91][0];  weiY[152]=tcal[36][1]+tcal[91][1];}
	  
	}
	
	
	
	if(tcal[56][0]>threshold_t){//MA2 39
	  
	  if(tcal[110][0]>threshold_t) {posY[153]=tcal[56][0]-tcal[110][0]; weiY[153]=tcal[56][1]+tcal[110][1];}
	  if(tcal[65][0]>threshold_t)  {posY[154]=tcal[56][0]-tcal[65][0];  weiY[154]=tcal[56][1]+tcal[65][1];}
	  if(tcal[100][0]>threshold_t) {posY[155]=tcal[56][0]-tcal[100][0]; weiY[155]=tcal[56][1]+tcal[100][1];}
	  if(tcal[89][0]>threshold_t)  {posY[156]=tcal[56][0]-tcal[89][0];  weiY[156]=tcal[56][1]+tcal[89][1];}
	  if(tcal[111][0]>threshold_t) {posY[157]=tcal[56][0]-tcal[111][0]; weiY[157]=tcal[56][1]+tcal[111][1];}
	  if(tcal[66][0]>threshold_t)  {posY[158]=tcal[56][0]-tcal[66][0];  weiY[158]=tcal[56][1]+tcal[66][1];}
	  if(tcal[101][0]>threshold_t) {posY[159]=tcal[56][0]-tcal[101][0]; weiY[159]=tcal[56][1]+tcal[101][1];}
	  if(tcal[91][0]>threshold_t)  {posY[160]=tcal[56][0]-tcal[91][0];  weiY[160]=tcal[56][1]+tcal[91][1];}
	  
	}
	
	
	
	if(tcal[16][0]>threshold_t){//MA2 41
	  
	  if(tcal[110][0]>threshold_t) {posY[161]=tcal[16][0]-tcal[110][0]; weiY[161]=tcal[16][1]+tcal[110][1];}
	  if(tcal[65][0]>threshold_t)  {posY[162]=tcal[16][0]-tcal[65][0];  weiY[162]=tcal[16][1]+tcal[65][1];}
	  if(tcal[100][0]>threshold_t) {posY[163]=tcal[16][0]-tcal[100][0]; weiY[163]=tcal[16][1]+tcal[100][1];}
	  if(tcal[89][0]>threshold_t)  {posY[164]=tcal[16][0]-tcal[89][0];  weiY[164]=tcal[16][1]+tcal[89][1];}
	  if(tcal[111][0]>threshold_t) {posY[165]=tcal[16][0]-tcal[111][0]; weiY[165]=tcal[16][1]+tcal[111][1];}
	  if(tcal[66][0]>threshold_t)  {posY[166]=tcal[16][0]-tcal[66][0];  weiY[166]=tcal[16][1]+tcal[66][1];}
	  if(tcal[101][0]>threshold_t) {posY[167]=tcal[16][0]-tcal[101][0]; weiY[167]=tcal[16][1]+tcal[101][1];}
	  if(tcal[91][0]>threshold_t)  {posY[168]=tcal[16][0]-tcal[91][0];  weiY[168]=tcal[16][1]+tcal[91][1];}
	  
	}
	
	if(tcal[2][0]>threshold_t){//MA2 43
	  
	  if(tcal[110][0]>threshold_t) {posY[169]=tcal[2][0]-tcal[110][0]; weiY[169]=tcal[2][1]+tcal[110][1];}
	  if(tcal[65][0]>threshold_t)  {posY[170]=tcal[2][0]-tcal[65][0];  weiY[170]=tcal[2][1]+tcal[65][1];}
	  if(tcal[100][0]>threshold_t) {posY[171]=tcal[2][0]-tcal[100][0]; weiY[171]=tcal[2][1]+tcal[100][1];}
	  if(tcal[89][0]>threshold_t)  {posY[172]=tcal[2][0]-tcal[89][0];  weiY[172]=tcal[2][1]+tcal[89][1];}
	  if(tcal[111][0]>threshold_t) {posY[173]=tcal[2][0]-tcal[111][0]; weiY[173]=tcal[2][1]+tcal[111][1];}
	  if(tcal[66][0]>threshold_t)  {posY[174]=tcal[2][0]-tcal[66][0];  weiY[174]=tcal[2][1]+tcal[66][1];}
	  if(tcal[101][0]>threshold_t) {posY[175]=tcal[2][0]-tcal[101][0]; weiY[175]=tcal[2][1]+tcal[101][1];}
	  if(tcal[91][0]>threshold_t)  {posY[176]=tcal[2][0]-tcal[91][0];  weiY[176]=tcal[2][1]+tcal[91][1];}
	  
	}
	
	
	if(tcal[37][0]>threshold_t){//MA2 45
	  
	  if(tcal[110][0]>threshold_t) {posY[177]=tcal[37][0]-tcal[110][0]; weiY[177]=tcal[37][1]+tcal[110][1];}
	  if(tcal[65][0]>threshold_t)  {posY[178]=tcal[37][0]-tcal[65][0];  weiY[178]=tcal[37][1]+tcal[65][1];}
	  if(tcal[100][0]>threshold_t) {posY[179]=tcal[37][0]-tcal[100][0]; weiY[179]=tcal[37][1]+tcal[100][1];}
	  if(tcal[89][0]>threshold_t)  {posY[180]=tcal[37][0]-tcal[89][0];  weiY[180]=tcal[37][1]+tcal[89][1];}
	  if(tcal[111][0]>threshold_t) {posY[181]=tcal[37][0]-tcal[111][0]; weiY[181]=tcal[37][1]+tcal[111][1];}
	  if(tcal[66][0]>threshold_t)  {posY[182]=tcal[37][0]-tcal[66][0];  weiY[182]=tcal[37][1]+tcal[66][1];}
	  if(tcal[101][0]>threshold_t) {posY[183]=tcal[37][0]-tcal[101][0]; weiY[183]=tcal[37][1]+tcal[101][1];}
	  if(tcal[91][0]>threshold_t)  {posY[184]=tcal[37][0]-tcal[91][0];  weiY[184]=tcal[37][1]+tcal[91][1];}
	  
	}
	
	
	
	if(tcal[58][0]>threshold_t){//MA2 47
	   
	  if(tcal[110][0]>threshold_t) {posY[185]=tcal[58][0]-tcal[110][0]; weiY[185]=tcal[58][1]+tcal[110][1];}
	  if(tcal[65][0]>threshold_t)  {posY[186]=tcal[58][0]-tcal[65][0];  weiY[186]=tcal[58][1]+tcal[65][1];}
	  if(tcal[100][0]>threshold_t) {posY[187]=tcal[58][0]-tcal[100][0]; weiY[187]=tcal[58][1]+tcal[100][1];}
	  if(tcal[89][0]>threshold_t)  {posY[188]=tcal[58][0]-tcal[89][0];  weiY[188]=tcal[58][1]+tcal[89][1];}
	  if(tcal[111][0]>threshold_t) {posY[189]=tcal[58][0]-tcal[111][0]; weiY[189]=tcal[58][1]+tcal[111][1];}
	  if(tcal[66][0]>threshold_t)  {posY[190]=tcal[58][0]-tcal[66][0];  weiY[190]=tcal[58][1]+tcal[66][1];}
	  if(tcal[101][0]>threshold_t) {posY[191]=tcal[58][0]-tcal[101][0]; weiY[191]=tcal[58][1]+tcal[101][1];}
	  if(tcal[91][0]>threshold_t)  {posY[192]=tcal[58][0]-tcal[91][0];  weiY[192]=tcal[58][1]+tcal[91][1];}
	
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if(tcal[15][0]>threshold_t){ //MA2 49
	
	  if(tcal[112][0]>threshold_t) {posY[193]=tcal[15][0]-tcal[112][0]; weiY[193]=tcal[15][1]+tcal[112][1];}
	  if(tcal[67][0]>threshold_t)  {posY[194]=tcal[15][0]-tcal[67][0];  weiY[194]=tcal[15][1]+tcal[67][1];}
	  if(tcal[102][0]>threshold_t) {posY[195]=tcal[15][0]-tcal[102][0]; weiY[195]=tcal[15][1]+tcal[102][1];}
	  if(tcal[93][0]>threshold_t)  {posY[196]=tcal[15][0]-tcal[93][0];  weiY[196]=tcal[15][1]+tcal[93][1];}
	  if(tcal[113][0]>threshold_t) {posY[197]=tcal[15][0]-tcal[113][0]; weiY[197]=tcal[15][1]+tcal[113][1];}
	  if(tcal[68][0]>threshold_t)  {posY[198]=tcal[15][0]-tcal[68][0];  weiY[198]=tcal[15][1]+tcal[68][1];}
	  if(tcal[103][0]>threshold_t) {posY[199]=tcal[15][0]-tcal[103][0]; weiY[199]=tcal[15][1]+tcal[103][1];}
	  if(tcal[95][0]>threshold_t)  {posY[200]=tcal[15][0]-tcal[95][0];  weiY[200]=tcal[15][1]+tcal[95][1];}
	  
	}
	
	
	if(tcal[3][0]>threshold_t){ //MA2 51
	
	  if(tcal[112][0]>threshold_t) {posY[201]=tcal[3][0]-tcal[112][0]; weiY[201]=tcal[3][1]+tcal[112][1];}
	  if(tcal[67][0]>threshold_t)  {posY[202]=tcal[3][0]-tcal[67][0];  weiY[202]=tcal[3][1]+tcal[67][1];}
	  if(tcal[102][0]>threshold_t) {posY[203]=tcal[3][0]-tcal[102][0]; weiY[203]=tcal[3][1]+tcal[102][1];}
	  if(tcal[93][0]>threshold_t)  {posY[204]=tcal[3][0]-tcal[93][0];  weiY[204]=tcal[3][1]+tcal[93][1];}
	  if(tcal[113][0]>threshold_t) {posY[205]=tcal[3][0]-tcal[113][0]; weiY[205]=tcal[3][1]+tcal[113][1];}
	  if(tcal[68][0]>threshold_t)  {posY[206]=tcal[3][0]-tcal[68][0];  weiY[206]=tcal[3][1]+tcal[68][1];}
	  if(tcal[103][0]>threshold_t) {posY[207]=tcal[3][0]-tcal[103][0]; weiY[207]=tcal[3][1]+tcal[103][1];}
	  if(tcal[95][0]>threshold_t)  {posY[208]=tcal[3][0]-tcal[95][0];  weiY[208]=tcal[3][1]+tcal[95][1];}
	  
	}
	
	
	if(tcal[38][0]>threshold_t){ //MA2 53
	
	  if(tcal[112][0]>threshold_t) {posY[209]=tcal[38][0]-tcal[112][0]; weiY[209]=tcal[38][1]+tcal[112][1];}
	  if(tcal[67][0]>threshold_t)  {posY[210]=tcal[38][0]-tcal[67][0];  weiY[210]=tcal[38][1]+tcal[67][1];}
	  if(tcal[102][0]>threshold_t) {posY[211]=tcal[38][0]-tcal[102][0]; weiY[211]=tcal[38][1]+tcal[102][1];}
	  if(tcal[93][0]>threshold_t)  {posY[212]=tcal[38][0]-tcal[93][0];  weiY[212]=tcal[38][1]+tcal[93][1];}
	  if(tcal[113][0]>threshold_t) {posY[213]=tcal[38][0]-tcal[113][0]; weiY[213]=tcal[38][1]+tcal[113][1];}
	  if(tcal[68][0]>threshold_t)  {posY[214]=tcal[38][0]-tcal[68][0];  weiY[214]=tcal[38][1]+tcal[68][1];}
	  if(tcal[103][0]>threshold_t) {posY[215]=tcal[38][0]-tcal[103][0]; weiY[215]=tcal[38][1]+tcal[103][1];}
	  if(tcal[95][0]>threshold_t)  {posY[216]=tcal[38][0]-tcal[95][0];  weiY[216]=tcal[38][1]+tcal[95][1];}
	
	}
	
	
	if(tcal[60][0]>threshold_t){ //MA2 55
	   
	  if(tcal[112][0]>threshold_t) {posY[217]=tcal[60][0]-tcal[112][0]; weiY[217]=tcal[60][1]+tcal[112][1];}
	  if(tcal[67][0]>threshold_t)  {posY[218]=tcal[60][0]-tcal[67][0];  weiY[218]=tcal[60][1]+tcal[67][1];}
	  if(tcal[102][0]>threshold_t) {posY[219]=tcal[60][0]-tcal[102][0]; weiY[219]=tcal[60][1]+tcal[102][1];}
	  if(tcal[93][0]>threshold_t)  {posY[220]=tcal[60][0]-tcal[93][0];  weiY[220]=tcal[60][1]+tcal[93][1];}
	  if(tcal[113][0]>threshold_t) {posY[221]=tcal[60][0]-tcal[113][0]; weiY[221]=tcal[60][1]+tcal[113][1];}
	  if(tcal[68][0]>threshold_t)  {posY[222]=tcal[60][0]-tcal[68][0];  weiY[222]=tcal[60][1]+tcal[68][1];}
	  if(tcal[103][0]>threshold_t) {posY[223]=tcal[60][0]-tcal[103][0]; weiY[223]=tcal[60][1]+tcal[103][1];}
	  if(tcal[95][0]>threshold_t)  {posY[224]=tcal[60][0]-tcal[95][0];  weiY[224]=tcal[60][1]+tcal[95][1];}
	  
	}
	
	
	if(tcal[17][0]>threshold_t){ //MA2 57
	
	  if(tcal[112][0]>threshold_t) {posY[225]=tcal[17][0]-tcal[112][0]; weiY[225]=tcal[17][1]+tcal[112][1];}
	  if(tcal[67][0]>threshold_t)  {posY[226]=tcal[17][0]-tcal[67][0];  weiY[226]=tcal[17][1]+tcal[67][1];}
	  if(tcal[102][0]>threshold_t) {posY[227]=tcal[17][0]-tcal[102][0]; weiY[227]=tcal[17][1]+tcal[102][1];}
	  if(tcal[93][0]>threshold_t)  {posY[228]=tcal[17][0]-tcal[93][0];  weiY[228]=tcal[17][1]+tcal[93][1];}
	  if(tcal[113][0]>threshold_t) {posY[229]=tcal[17][0]-tcal[113][0]; weiY[229]=tcal[17][1]+tcal[113][1];}
	  if(tcal[68][0]>threshold_t)  {posY[230]=tcal[17][0]-tcal[68][0];  weiY[230]=tcal[17][1]+tcal[68][1];}
	  if(tcal[103][0]>threshold_t) {posY[231]=tcal[17][0]-tcal[103][0]; weiY[231]=tcal[17][1]+tcal[103][1];}
	  if(tcal[95][0]>threshold_t)  {posY[232]=tcal[17][0]-tcal[95][0];  weiY[232]=tcal[17][1]+tcal[95][1];}
	
	}
	
	
	if(tcal[4][0]>threshold_t){ //MA2 59
	
	  if(tcal[112][0]>threshold_t) {posY[233]=tcal[4][0]-tcal[112][0];  weiY[233]=tcal[4][1]+tcal[112][1];} 
	  if(tcal[67][0]>threshold_t)  {posY[234]=tcal[4][0]-tcal[67][0];   weiY[234]=tcal[4][1]+tcal[67][1];}
	  if(tcal[102][0]>threshold_t) {posY[235]=tcal[4][0]-tcal[102][0];  weiY[235]=tcal[4][1]+tcal[102][1];}
	  if(tcal[93][0]>threshold_t)  {posY[236]=tcal[4][0]-tcal[93][0];   weiY[236]=tcal[4][1]+tcal[93][1];}
	  if(tcal[113][0]>threshold_t) {posY[237]=tcal[4][0]-tcal[113][0]; weiY[237]=tcal[4][1]+tcal[113][1];}
	  if(tcal[68][0]>threshold_t)  {posY[238]=tcal[4][0]-tcal[68][0];   weiY[238]=tcal[4][1]+tcal[68][1];}
	  if(tcal[103][0]>threshold_t) {posY[239]=tcal[4][0]-tcal[103][0];  weiY[239]=tcal[4][1]+tcal[103][1];}
	  if(tcal[95][0]>threshold_t)  {posY[240]=tcal[4][0]-tcal[95][0];   weiY[240]=tcal[4][1]+tcal[95][1];}
	  
	}
	
	
	if(tcal[39][0]>threshold_t){ //MA2 61
	
	  if(tcal[112][0]>threshold_t) {posY[241]=tcal[39][0]-tcal[112][0]; weiY[241]=tcal[39][1]+tcal[112][1];}
	  if(tcal[67][0]>threshold_t)  {posY[242]=tcal[39][0]-tcal[67][0];  weiY[242]=tcal[39][1]+tcal[67][1];}
	  if(tcal[102][0]>threshold_t) {posY[243]=tcal[39][0]-tcal[102][0]; weiY[243]=tcal[39][1]+tcal[102][1];}
	  if(tcal[93][0]>threshold_t)  {posY[244]=tcal[39][0]-tcal[93][0];  weiY[244]=tcal[39][1]+tcal[93][1];}
	  if(tcal[113][0]>threshold_t) {posY[245]=tcal[39][0]-tcal[113][0]; weiY[245]=tcal[39][1]+tcal[113][1];}
	  if(tcal[68][0]>threshold_t)  {posY[246]=tcal[39][0]-tcal[68][0];  weiY[246]=tcal[39][1]+tcal[68][1];}
	  if(tcal[103][0]>threshold_t) {posY[247]=tcal[39][0]-tcal[103][0]; weiY[247]=tcal[39][1]+tcal[103][1];}
	  if(tcal[95][0]>threshold_t)  {posY[248]=tcal[39][0]-tcal[95][0];  weiY[248]=tcal[39][1]+tcal[95][1];}
	  
	}
	
	
	if(tcal[62][0]>threshold_t){ //MA2 63
	  
	  if(tcal[112][0]>threshold_t) {posY[249]=tcal[62][0]-tcal[112][0]; weiY[249]=tcal[62][1]+tcal[112][1];}
	  if(tcal[67][0]>threshold_t)  {posY[250]=tcal[62][0]-tcal[67][0];  weiY[250]=tcal[62][1]+tcal[67][1];}
	  if(tcal[102][0]>threshold_t) {posY[251]=tcal[62][0]-tcal[102][0]; weiY[251]=tcal[62][1]+tcal[102][1];}
	  if(tcal[93][0]>threshold_t)  {posY[252]=tcal[62][0]-tcal[93][0];  weiY[252]=tcal[62][1]+tcal[93][1];}
	  if(tcal[113][0]>threshold_t) {posY[253]=tcal[62][0]-tcal[113][0]; weiY[253]=tcal[62][1]+tcal[113][1];}
	  if(tcal[68][0]>threshold_t)  {posY[254]=tcal[62][0]-tcal[68][0];  weiY[254]=tcal[62][1]+tcal[68][1];}
	  if(tcal[103][0]>threshold_t) {posY[255]=tcal[62][0]-tcal[103][0]; weiY[255]=tcal[62][1]+tcal[103][1];}
	  if(tcal[95][0]>threshold_t)  {posY[256]=tcal[62][0]-tcal[95][0];  weiY[256]=tcal[62][1]+tcal[95][1];}
	  
	}

	posX = -1000;posY1=-1000;
        double weimax = -1E38;
        int npos = 0;
        width = -100000;
	for(int i=0;i<304;i++){
            if (abs(posY[i]) < threshold_Y && weiY[i]>weimax) {
                posX = (i - 150)*ns2mm[0] - offset[0];
		posY1=posY[i]*ns2mm[1] - offset[1];
                weimax=weiY[i];
   		width = weimax;
                npos++;
  //              printf("F1  be  %d %f  %f  %f \n",npos,posX,posY1,weiY[i]);
	    } 
        }
        nfire=npos;
//       if (npos>1) 
 //       printf("F1 in  %d  %f   %f  %f\n",nfire,width,posX,posY1);
}
// ***********************************************************************
int ENFiberCal::ReadParameters(char* filename){
  
  fi.open(filename,ios::in);
  if (fi.is_open()){
     int valread[5];
     char* buff;
     // read map data
     buff = GetNextLine('#');if (buff ==NULL) goto l20;
     if (Put2Array(buff,valread,3) == -1) goto l20;
     segid = valread[0];
     detid = valread[1];
     modid = valread[2];
      // read threshold data
     buff = GetNextLine('#');if (buff ==NULL) goto l20;
     if (Put2Array(buff,valread,2) == -1) goto l20;
     threshold_t = valread[0];
     threshold_Y = valread[1];
      // read calib ns2mm data
     buff = GetNextLine('#');if (buff ==NULL) goto l20;
     if (Put2Array(buff,ns2mm,2) == -1) goto l20;
      // read offsetval data
     buff = GetNextLine('#');if (buff ==NULL) goto l20;
     if (Put2Array(buff,offset,2) == -1) goto l20;
     for (int i=0;i<128;i++) ch2ns[i]=1;
     fi.close();
     printf("ENFiberCal: Parameters file :\"%s\" |--> LOADED!!!.\n",filename); 
     return 0;
  }else{
     printf("ENFiberCal: Parameters file :\"%s\" cannot open |--> NOT load!!!\n",filename);
     goto def;
  }
l20:  printf("ENFiberCal: Parameters file :\"%s\" not true format |--> NOT load!!!\n",filename);
def:
  for (int i=0;i<128;i++) ch2ns[i]=1; 
   threshold_t = 100;
   threshold_Y = 1000;
   ns2mm[0] = 0.5;ns2mm[1]=1;
   offset[0] = 0;offset[1] = 0;
  return -1;
}

// ***********************************************************************
char* ENFiberCal::ltrim (char s[])
{
    while (*s == 32) s++;
    return s;
}
// *********************************************************************** 
char* ENFiberCal::rtrim (char s[])
{
    int i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
// ***********************************************************************
char * ENFiberCal::trim (char s[])
{
    return ltrim(rtrim(s));  
}
// ***********************************************************************
int ENFiberCal::Put2Array(char*s,double* val,int nval){
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
int ENFiberCal::Put2Array(char* s,int* val,int nval){
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
char* ENFiberCal::GetNextLine(char s){
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
