//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul  6 14:26:16 2021 by ROOT version 6.22/02
// from TTree tracktree/A tree with svtx tracks
// found on file: G4EICDetector_calData.root
//////////////////////////////////////////////////////////

#ifndef Matching_h
#define Matching_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class TH1;

class Matching {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<double>  *track_px;
   vector<double>  *track_py;
   vector<double>  *track_pz;
   vector<double>  *track_p;
   vector<double>  *track_pt;
   vector<double>  *track_phi;
   vector<double>  *track_eta;
   vector<double>  *track_charge;
   vector<double>  *track_chisq;
   vector<double>  *track_ndf;
   vector<double>  *track_dca;
   vector<double>  *track_x;
   vector<double>  *track_y;
   vector<double>  *track_z;
   vector<double>  *truth_px;
   vector<double>  *truth_py;
   vector<double>  *truth_pz;
   vector<double>  *truth_p;
   vector<double>  *truth_energy;
   vector<double>  *truth_pt;
   vector<double>  *truth_phi;
   vector<double>  *truth_eta;
   vector<int>     *truth_pid;
   vector<double>  *clus_energy;
   vector<double>  *clus_eta;
   vector<double>  *clus_theta;
   vector<double>  *clus_pt;
   vector<double>  *clus_phi;
   vector<double>  *clus_px;
   vector<double>  *clus_py;
   vector<double>  *clus_pz;
   vector<double>  *clusEnergy_HCal;
   vector<double>  *cluseta_HCal;
   vector<double>  *clusphi_HCal;
   vector<double>  *cluspt_HCal;
   vector<double>  *clusEnergy_HCalOUT;
   vector<double>  *cluseta_HCalOUT;
   vector<double>  *clusphi_HCalOUT;
   vector<double>  *cluspt_HCalOUT;
   vector<double>  *tr_CEMC_eta;
   vector<double>  *tr_CEMC_phi;
   vector<double>  *tr_CEMC_x;
   vector<double>  *tr_CEMC_y;
   vector<double>  *tr_CEMC_z;
   vector<double>  *tr_CEMC_px;
   vector<double>  *tr_CEMC_py;
   vector<double>  *tr_CEMC_pz;

       /// Tower variables
  vector<double> *towenergy;
  vector<double> *toweta;
  vector<double> *towphi;


   // List of branches
   TBranch        *b_track_px;   //!
   TBranch        *b_track_py;   //!
   TBranch        *b_track_pz;   //!
   TBranch        *b_track_p;   //!
   TBranch        *b_track_pt;   //!
   TBranch        *b_track_phi;   //!
   TBranch        *b_track_eta;   //!
   TBranch        *b_track_charge;   //!
   TBranch        *b_track_chisq;   //!
   TBranch        *b_track_ndf;   //!
   TBranch        *b_track_dca;   //!
   TBranch        *b_track_x;   //!
   TBranch        *b_track_y;   //!
   TBranch        *b_track_z;   //!
   TBranch        *b_truth_px;   //!
   TBranch        *b_truth_py;   //!
   TBranch        *b_truth_pz;   //!
   TBranch        *b_truth_p;   //!
   TBranch        *b_truth_energy;   //!
   TBranch        *b_truth_pt;   //!
   TBranch        *b_truth_phi;   //!
   TBranch        *b_truth_eta;   //!
   TBranch        *b_truth_pid;   //!
   TBranch        *b_clus_energy;   //!
   TBranch        *b_clus_eta;   //!
   TBranch        *b_clus_theta;   //!
   TBranch        *b_clus_pt;   //!
   TBranch        *b_clus_phi;   //!
   TBranch        *b_clus_px;   //!
   TBranch        *b_clus_py;   //!
   TBranch        *b_clus_pz;   //!
   TBranch        *b_clusEnergy_HCal;   //!
   TBranch        *b_cluseta_HCal;   //!
   TBranch        *b_clusphi_HCal;   //!
   TBranch        *b_cluspt_HCal;   //!
   TBranch        *b_clusEnergy_HCalOUT;   //!
   TBranch        *b_cluseta_HCalOUT;   //!
   TBranch        *b_clusphi_HCalOUT;   //!
   TBranch        *b_cluspt_HCalOUT;   //!
   TBranch        *b_tr_CEMC_eta;   //!
   TBranch        *b_tr_CEMC_phi;   //!
   TBranch        *b_tr_CEMC_x;   //!
   TBranch        *b_tr_CEMC_y;   //!
   TBranch        *b_tr_CEMC_z;   //!
   TBranch        *b_tr_CEMC_px;   //!
   TBranch        *b_tr_CEMC_py;   //!
   TBranch        *b_tr_CEMC_pz;   //!

   TBranch        *b_towenergy;   //!
   TBranch        *b_toweta;   //!
   TBranch        *b_towphi;   //!

   Matching(TTree *tree=0);
   virtual ~Matching();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   float dR(float Eta1, float Phi1, float Eta2, float Phi2);
   float dRmin(float Eta1, float Phi1, int &index);

   float dEtamin(float Eta1, int &index);
   float dPhimin(float Phi1, int &index);
   int Get_charge(int par_ID);

   float dRmin_tow(float Eta1, float Phi1, int &index);

  // TH1 *th1[12];
 //  TH1 *th1_dist[12];
};

#endif

#ifdef Matching_cxx
Matching::Matching(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("G4EICDetector_calData-100Pi.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("G4EICDetector_calData-100Pi.root");
      }
      f->GetObject("tracktree",tree);

   }
   Init(tree);
}

Matching::~Matching()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Matching::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Matching::LoadTree(Long64_t entry)
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

void Matching::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   track_px = 0;
   track_py = 0;
   track_pz = 0;
   track_p = 0;
   track_pt = 0;
   track_phi = 0;
   track_eta = 0;
   track_charge = 0;
   track_chisq = 0;
   track_ndf = 0;
   track_dca = 0;
   track_x = 0;
   track_y = 0;
   track_z = 0;
   truth_px = 0;
   truth_py = 0;
   truth_pz = 0;
   truth_p = 0;
   truth_energy = 0;
   truth_pt = 0;
   truth_phi = 0;
   truth_eta = 0;
   truth_pid = 0;
   clus_energy = 0;
   clus_eta = 0;
   clus_theta = 0;
   clus_pt = 0;
   clus_phi = 0;
   clus_px = 0;
   clus_py = 0;
   clus_pz = 0;
   clusEnergy_HCal = 0;
   cluseta_HCal = 0;
   clusphi_HCal = 0;
   cluspt_HCal = 0;
   clusEnergy_HCalOUT = 0;
   cluseta_HCalOUT = 0;
   clusphi_HCalOUT = 0;
   cluspt_HCalOUT = 0;
   tr_CEMC_eta = 0;
   tr_CEMC_phi = 0;
   tr_CEMC_x = 0;
   tr_CEMC_y = 0;
   tr_CEMC_z = 0;
   tr_CEMC_px = 0;
   tr_CEMC_py = 0;
   tr_CEMC_pz = 0;
   towenergy=0;
   toweta=0;
   towphi=0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("track_px", &track_px, &b_track_px);
   fChain->SetBranchAddress("track_py", &track_py, &b_track_py);
   fChain->SetBranchAddress("track_pz", &track_pz, &b_track_pz);
   fChain->SetBranchAddress("track_p", &track_p, &b_track_p);
   fChain->SetBranchAddress("track_pt", &track_pt, &b_track_pt);
   fChain->SetBranchAddress("track_phi", &track_phi, &b_track_phi);
   fChain->SetBranchAddress("track_eta", &track_eta, &b_track_eta);
   fChain->SetBranchAddress("track_charge", &track_charge, &b_track_charge);
   fChain->SetBranchAddress("track_chisq", &track_chisq, &b_track_chisq);
   fChain->SetBranchAddress("track_ndf", &track_ndf, &b_track_ndf);
   fChain->SetBranchAddress("track_dca", &track_dca, &b_track_dca);
   fChain->SetBranchAddress("track_x", &track_x, &b_track_x);
   fChain->SetBranchAddress("track_y", &track_y, &b_track_y);
   fChain->SetBranchAddress("track_z", &track_z, &b_track_z);
   fChain->SetBranchAddress("truth_px", &truth_px, &b_truth_px);
   fChain->SetBranchAddress("truth_py", &truth_py, &b_truth_py);
   fChain->SetBranchAddress("truth_pz", &truth_pz, &b_truth_pz);
   fChain->SetBranchAddress("truth_p", &truth_p, &b_truth_p);
   fChain->SetBranchAddress("truth_energy", &truth_energy, &b_truth_energy);
   fChain->SetBranchAddress("truth_pt", &truth_pt, &b_truth_pt);
   fChain->SetBranchAddress("truth_phi", &truth_phi, &b_truth_phi);
   fChain->SetBranchAddress("truth_eta", &truth_eta, &b_truth_eta);
   fChain->SetBranchAddress("truth_pid", &truth_pid, &b_truth_pid);
   fChain->SetBranchAddress("clus_energy", &clus_energy, &b_clus_energy);
   fChain->SetBranchAddress("clus_eta", &clus_eta, &b_clus_eta);
   fChain->SetBranchAddress("clus_theta", &clus_theta, &b_clus_theta);
   fChain->SetBranchAddress("clus_pt", &clus_pt, &b_clus_pt);
   fChain->SetBranchAddress("clus_phi", &clus_phi, &b_clus_phi);
   fChain->SetBranchAddress("clus_px", &clus_px, &b_clus_px);
   fChain->SetBranchAddress("clus_py", &clus_py, &b_clus_py);
   fChain->SetBranchAddress("clus_pz", &clus_pz, &b_clus_pz);
   fChain->SetBranchAddress("clusEnergy_HCal", &clusEnergy_HCal, &b_clusEnergy_HCal);
   fChain->SetBranchAddress("cluseta_HCal", &cluseta_HCal, &b_cluseta_HCal);
   fChain->SetBranchAddress("clusphi_HCal", &clusphi_HCal, &b_clusphi_HCal);
   fChain->SetBranchAddress("cluspt_HCal", &cluspt_HCal, &b_cluspt_HCal);
   fChain->SetBranchAddress("clusEnergy_HCalOUT", &clusEnergy_HCalOUT, &b_clusEnergy_HCalOUT);
   fChain->SetBranchAddress("cluseta_HCalOUT", &cluseta_HCalOUT, &b_cluseta_HCalOUT);
   fChain->SetBranchAddress("clusphi_HCalOUT", &clusphi_HCalOUT, &b_clusphi_HCalOUT);
   fChain->SetBranchAddress("cluspt_HCalOUT", &cluspt_HCalOUT, &b_cluspt_HCalOUT);
   fChain->SetBranchAddress("tr_CEMC_eta", &tr_CEMC_eta, &b_tr_CEMC_eta);
   fChain->SetBranchAddress("tr_CEMC_phi", &tr_CEMC_phi, &b_tr_CEMC_phi);
   fChain->SetBranchAddress("tr_CEMC_x", &tr_CEMC_x, &b_tr_CEMC_x);
   fChain->SetBranchAddress("tr_CEMC_y", &tr_CEMC_y, &b_tr_CEMC_y);
   fChain->SetBranchAddress("tr_CEMC_z", &tr_CEMC_z, &b_tr_CEMC_z);
   fChain->SetBranchAddress("tr_CEMC_px", &tr_CEMC_px, &b_tr_CEMC_px);
   fChain->SetBranchAddress("tr_CEMC_py", &tr_CEMC_py, &b_tr_CEMC_py);
   fChain->SetBranchAddress("tr_CEMC_pz", &tr_CEMC_pz, &b_tr_CEMC_pz);

   fChain->SetBranchAddress("towenergy", &towenergy, &b_towenergy);
   fChain->SetBranchAddress("toweta", &toweta, &b_toweta);
   fChain->SetBranchAddress("towphi", &towphi, &b_towphi);
   Notify();
}

Bool_t Matching::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Matching::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Matching::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

#endif // #ifdef Matching_cxx
