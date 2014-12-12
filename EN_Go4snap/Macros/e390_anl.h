//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct  8 13:17:40 2013 by ROOT version 5.34/07
// from TTree SortxTree/Go4FileStore
// found on file: data0353.root
//////////////////////////////////////////////////////////

#ifndef e390_anl_h
#define e390_anl_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxSortEvent = 1;

class e390_anl {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //TArtSortEvent   *SortEvent_;
 //TArtSortEvent   *SortEvent_TGo4EventElement;
   Int_t           SortEvent_F2UPPAC_L;
   Int_t           SortEvent_F2UPPAC_D;
   Int_t           SortEvent_F2UPPAC_R;
   Int_t           SortEvent_F2UPPAC_U;
   Int_t           SortEvent_F2UPPAC_A;
   Int_t           SortEvent_F2DPPAC_L;
   Int_t           SortEvent_F2DPPAC_D;
   Int_t           SortEvent_F2DPPAC_R;
   Int_t           SortEvent_F2DPPAC_U;
   Int_t           SortEvent_F2DPPAC_A;
   Int_t           SortEvent_HODO_dE_UT[13];
   Int_t           SortEvent_HODO_dE_DT[13];
   Int_t           SortEvent_HODO_dE_UQ[13];
   Int_t           SortEvent_HODO_dE_DQ[13];
   Int_t           SortEvent_HODO_E1_LT[16];
   Int_t           SortEvent_HODO_E1_RT[16];
   Int_t           SortEvent_HODO_E1_LQ[16];
   Int_t           SortEvent_HODO_E1_RQ[16];
   Int_t           SortEvent_HODO_E2_LT[13];
   Int_t           SortEvent_HODO_E2_RT[13];
   Int_t           SortEvent_HODO_E2_LQ[13];
   Int_t           SortEvent_HODO_E2_RQ[13];
   Int_t           SortEvent_F2_Silicon;
   Int_t           SortEvent_F2_Scint_Q;
   Int_t           SortEvent_F2_Scint_T;
   Int_t           SortEvent_F2_RF;
   Int_t           SortEvent_F2_Tref;
   Int_t           SortEvent_PPAC_Trg;
   Int_t           SortEvent_HODO_RF;
   Int_t           SortEvent_HODO_RF_Del;
   Int_t           SortEvent_DSSD_1_b[32];
   Int_t           SortEvent_DSSD_1_g[32];
   Int_t           SortEvent_DSSD_2_b[32];
   Int_t           SortEvent_DSSD_2_g[32];
   Int_t           SortEvent_DSSD_3_b[32];
   Int_t           SortEvent_DSSD_3_g[32];
   Int_t           SortEvent_DSSD_4_b[32];
   Int_t           SortEvent_DSSD_4_g[32];
   Int_t           SortEvent_DSSD_5_b[32];
   Int_t           SortEvent_DSSD_5_g[32];
   Int_t           SortEvent_DSSD_6_b[32];
   Int_t           SortEvent_DSSD_6_g[32];
   Int_t           SortEvent_CsI_1[4];
   Int_t           SortEvent_CsI_2[4];
   Int_t           SortEvent_CsI_3[4];
   Int_t           SortEvent_CsI_4[4];
   Int_t           SortEvent_CsI_5[4];
   Int_t           SortEvent_CsI_6[4];
   Int_t           SortEvent_SSD[6];

   // List of branches
   TBranch        *b_SortEvent_F2UPPAC_L;   //!
   TBranch        *b_SortEvent_F2UPPAC_D;   //!
   TBranch        *b_SortEvent_F2UPPAC_R;   //!
   TBranch        *b_SortEvent_F2UPPAC_U;   //!
   TBranch        *b_SortEvent_F2UPPAC_A;   //!
   TBranch        *b_SortEvent_F2DPPAC_L;   //!
   TBranch        *b_SortEvent_F2DPPAC_D;   //!
   TBranch        *b_SortEvent_F2DPPAC_R;   //!
   TBranch        *b_SortEvent_F2DPPAC_U;   //!
   TBranch        *b_SortEvent_F2DPPAC_A;   //!
   TBranch        *b_SortEvent_HODO_dE_UT;   //!
   TBranch        *b_SortEvent_HODO_dE_DT;   //!
   TBranch        *b_SortEvent_HODO_dE_UQ;   //!
   TBranch        *b_SortEvent_HODO_dE_DQ;   //!
   TBranch        *b_SortEvent_HODO_E1_LT;   //!
   TBranch        *b_SortEvent_HODO_E1_RT;   //!
   TBranch        *b_SortEvent_HODO_E1_LQ;   //!
   TBranch        *b_SortEvent_HODO_E1_RQ;   //!
   TBranch        *b_SortEvent_HODO_E2_LT;   //!
   TBranch        *b_SortEvent_HODO_E2_RT;   //!
   TBranch        *b_SortEvent_HODO_E2_LQ;   //!
   TBranch        *b_SortEvent_HODO_E2_RQ;   //!
   TBranch        *b_SortEvent_F2_Silicon;   //!
   TBranch        *b_SortEvent_F2_Scint_Q;   //!
   TBranch        *b_SortEvent_F2_Scint_T;   //!
   TBranch        *b_SortEvent_F2_RF;   //!
   TBranch        *b_SortEvent_F2_Tref;   //!
   TBranch        *b_SortEvent_PPAC_Trg;   //!
   TBranch        *b_SortEvent_HODO_RF;   //!
   TBranch        *b_SortEvent_HODO_RF_Del;   //!
   TBranch        *b_SortEvent_DSSD_1_b;   //!
   TBranch        *b_SortEvent_DSSD_1_g;   //!
   TBranch        *b_SortEvent_DSSD_2_b;   //!
   TBranch        *b_SortEvent_DSSD_2_g;   //!
   TBranch        *b_SortEvent_DSSD_3_b;   //!
   TBranch        *b_SortEvent_DSSD_3_g;   //!
   TBranch        *b_SortEvent_DSSD_4_b;   //!
   TBranch        *b_SortEvent_DSSD_4_g;   //!
   TBranch        *b_SortEvent_DSSD_5_b;   //!
   TBranch        *b_SortEvent_DSSD_5_g;   //!
   TBranch        *b_SortEvent_DSSD_6_b;   //!
   TBranch        *b_SortEvent_DSSD_6_g;   //!
   TBranch        *b_SortEvent_CsI_1;   //!
   TBranch        *b_SortEvent_CsI_2;   //!
   TBranch        *b_SortEvent_CsI_3;   //!
   TBranch        *b_SortEvent_CsI_4;   //!
   TBranch        *b_SortEvent_CsI_5;   //!
   TBranch        *b_SortEvent_CsI_6;   //!
   TBranch        *b_SortEvent_SSD;   //!

   e390_anl(TTree *tree=0);
   virtual ~e390_anl();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef e390_anl_cxx
e390_anl::e390_anl(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("data0361.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("data0361.root");
      }
      f->GetObject("SortxTree",tree);

   }
   Init(tree);
}

e390_anl::~e390_anl()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t e390_anl::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t e390_anl::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void e390_anl::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("SortEvent.F2UPPAC_L", &SortEvent_F2UPPAC_L, &b_SortEvent_F2UPPAC_L);
   fChain->SetBranchAddress("SortEvent.F2UPPAC_D", &SortEvent_F2UPPAC_D, &b_SortEvent_F2UPPAC_D);
   fChain->SetBranchAddress("SortEvent.F2UPPAC_R", &SortEvent_F2UPPAC_R, &b_SortEvent_F2UPPAC_R);
   fChain->SetBranchAddress("SortEvent.F2UPPAC_U", &SortEvent_F2UPPAC_U, &b_SortEvent_F2UPPAC_U);
   fChain->SetBranchAddress("SortEvent.F2UPPAC_A", &SortEvent_F2UPPAC_A, &b_SortEvent_F2UPPAC_A);
   fChain->SetBranchAddress("SortEvent.F2DPPAC_L", &SortEvent_F2DPPAC_L, &b_SortEvent_F2DPPAC_L);
   fChain->SetBranchAddress("SortEvent.F2DPPAC_D", &SortEvent_F2DPPAC_D, &b_SortEvent_F2DPPAC_D);
   fChain->SetBranchAddress("SortEvent.F2DPPAC_R", &SortEvent_F2DPPAC_R, &b_SortEvent_F2DPPAC_R);
   fChain->SetBranchAddress("SortEvent.F2DPPAC_U", &SortEvent_F2DPPAC_U, &b_SortEvent_F2DPPAC_U);
   fChain->SetBranchAddress("SortEvent.F2DPPAC_A", &SortEvent_F2DPPAC_A, &b_SortEvent_F2DPPAC_A);
   fChain->SetBranchAddress("SortEvent.HODO_dE_UT[13]", SortEvent_HODO_dE_UT, &b_SortEvent_HODO_dE_UT);
   fChain->SetBranchAddress("SortEvent.HODO_dE_DT[13]", SortEvent_HODO_dE_DT, &b_SortEvent_HODO_dE_DT);
   fChain->SetBranchAddress("SortEvent.HODO_dE_UQ[13]", SortEvent_HODO_dE_UQ, &b_SortEvent_HODO_dE_UQ);
   fChain->SetBranchAddress("SortEvent.HODO_dE_DQ[13]", SortEvent_HODO_dE_DQ, &b_SortEvent_HODO_dE_DQ);
   fChain->SetBranchAddress("SortEvent.HODO_E1_LT[16]", SortEvent_HODO_E1_LT, &b_SortEvent_HODO_E1_LT);
   fChain->SetBranchAddress("SortEvent.HODO_E1_RT[16]", SortEvent_HODO_E1_RT, &b_SortEvent_HODO_E1_RT);
   fChain->SetBranchAddress("SortEvent.HODO_E1_LQ[16]", SortEvent_HODO_E1_LQ, &b_SortEvent_HODO_E1_LQ);
   fChain->SetBranchAddress("SortEvent.HODO_E1_RQ[16]", SortEvent_HODO_E1_RQ, &b_SortEvent_HODO_E1_RQ);
   fChain->SetBranchAddress("SortEvent.HODO_E2_LT[13]", SortEvent_HODO_E2_LT, &b_SortEvent_HODO_E2_LT);
   fChain->SetBranchAddress("SortEvent.HODO_E2_RT[13]", SortEvent_HODO_E2_RT, &b_SortEvent_HODO_E2_RT);
   fChain->SetBranchAddress("SortEvent.HODO_E2_LQ[13]", SortEvent_HODO_E2_LQ, &b_SortEvent_HODO_E2_LQ);
   fChain->SetBranchAddress("SortEvent.HODO_E2_RQ[13]", SortEvent_HODO_E2_RQ, &b_SortEvent_HODO_E2_RQ);
   fChain->SetBranchAddress("SortEvent.F2_Silicon", &SortEvent_F2_Silicon, &b_SortEvent_F2_Silicon);
   fChain->SetBranchAddress("SortEvent.F2_Scint_Q", &SortEvent_F2_Scint_Q, &b_SortEvent_F2_Scint_Q);
   fChain->SetBranchAddress("SortEvent.F2_Scint_T", &SortEvent_F2_Scint_T, &b_SortEvent_F2_Scint_T);
   fChain->SetBranchAddress("SortEvent.F2_RF", &SortEvent_F2_RF, &b_SortEvent_F2_RF);
   fChain->SetBranchAddress("SortEvent.F2_Tref", &SortEvent_F2_Tref, &b_SortEvent_F2_Tref);
   fChain->SetBranchAddress("SortEvent.PPAC_Trg", &SortEvent_PPAC_Trg, &b_SortEvent_PPAC_Trg);
   fChain->SetBranchAddress("SortEvent.HODO_RF", &SortEvent_HODO_RF, &b_SortEvent_HODO_RF);
   fChain->SetBranchAddress("SortEvent.HODO_RF_Del", &SortEvent_HODO_RF_Del, &b_SortEvent_HODO_RF_Del);
   fChain->SetBranchAddress("SortEvent.DSSD_1_b[32]", SortEvent_DSSD_1_b, &b_SortEvent_DSSD_1_b);
   fChain->SetBranchAddress("SortEvent.DSSD_1_g[32]", SortEvent_DSSD_1_g, &b_SortEvent_DSSD_1_g);
   fChain->SetBranchAddress("SortEvent.DSSD_2_b[32]", SortEvent_DSSD_2_b, &b_SortEvent_DSSD_2_b);
   fChain->SetBranchAddress("SortEvent.DSSD_2_g[32]", SortEvent_DSSD_2_g, &b_SortEvent_DSSD_2_g);
   fChain->SetBranchAddress("SortEvent.DSSD_3_b[32]", SortEvent_DSSD_3_b, &b_SortEvent_DSSD_3_b);
   fChain->SetBranchAddress("SortEvent.DSSD_3_g[32]", SortEvent_DSSD_3_g, &b_SortEvent_DSSD_3_g);
   fChain->SetBranchAddress("SortEvent.DSSD_4_b[32]", SortEvent_DSSD_4_b, &b_SortEvent_DSSD_4_b);
   fChain->SetBranchAddress("SortEvent.DSSD_4_g[32]", SortEvent_DSSD_4_g, &b_SortEvent_DSSD_4_g);
   fChain->SetBranchAddress("SortEvent.DSSD_5_b[32]", SortEvent_DSSD_5_b, &b_SortEvent_DSSD_5_b);
   fChain->SetBranchAddress("SortEvent.DSSD_5_g[32]", SortEvent_DSSD_5_g, &b_SortEvent_DSSD_5_g);
   fChain->SetBranchAddress("SortEvent.DSSD_6_b[32]", SortEvent_DSSD_6_b, &b_SortEvent_DSSD_6_b);
   fChain->SetBranchAddress("SortEvent.DSSD_6_g[32]", SortEvent_DSSD_6_g, &b_SortEvent_DSSD_6_g);
   fChain->SetBranchAddress("SortEvent.CsI_1[4]", SortEvent_CsI_1, &b_SortEvent_CsI_1);
   fChain->SetBranchAddress("SortEvent.CsI_2[4]", SortEvent_CsI_2, &b_SortEvent_CsI_2);
   fChain->SetBranchAddress("SortEvent.CsI_3[4]", SortEvent_CsI_3, &b_SortEvent_CsI_3);
   fChain->SetBranchAddress("SortEvent.CsI_4[4]", SortEvent_CsI_4, &b_SortEvent_CsI_4);
   fChain->SetBranchAddress("SortEvent.CsI_5[4]", SortEvent_CsI_5, &b_SortEvent_CsI_5);
   fChain->SetBranchAddress("SortEvent.CsI_6[4]", SortEvent_CsI_6, &b_SortEvent_CsI_6);
   fChain->SetBranchAddress("SortEvent.SSD[6]", SortEvent_SSD, &b_SortEvent_SSD);
   Notify();
}

Bool_t e390_anl::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void e390_anl::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t e390_anl::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef e390_anl_cxx
