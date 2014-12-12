//#include "macros/Anl_class.C"
//This function returns a Chain
//#include "Chain.h"
TChain * chain(Int_t file_0,Int_t file_f){  
  Char_t tree_name[]="SortxTree";
  Char_t file_name[256];
  TChain *theChain = new TChain(tree_name);
  for(Int_t i=file_0;i<=file_f;i++){

			if(i<10){
			sprintf(file_name,"data000%d.root",i);
			theChain->Add(file_name);
			}
			
			else if(i<100){
			sprintf(file_name,"data00%d.root",i);
			theChain->Add(file_name);
			}
				
			else if(i<1000){
			sprintf(file_name,"data0%d.root",i);
			theChain->Add(file_name);
			}

		cout<<file_name<<endl;			

  }
  //theChain->Merge("beam_profile_040408.root");
  return theChain;
}
