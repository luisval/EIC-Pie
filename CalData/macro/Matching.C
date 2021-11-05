////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// This macro finds the closest cluster to a given track and the closest tower to a given cluster. 
////// Besides, it plots the coefficient of the deposited energy by the track momentum.
////// Authors: Luis Valenzuela Cazares
//////          Sebastian Tapia
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define Matching_cxx
#include "Matching.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Matching::Loop(){

  cout << "---Start of the program-----" << endl;
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
   
        TFile* fout = new TFile(Form("G4EICDetector_out_test.root"),"RECREATE");

   //  TFile* fout = new TFile(Form("G4EICDetector_out_e_1-5GeV.root"),"RECREATE");

 //  TFile *fout = new TFile("Ep_cut_revisited_G4EICDetector_out_hq2_e_5-10GeV.root","RECREATE");

  TH1F *h_dRmin = new TH1F("h_dRmin","dRmin",400,0,4);
        h_dRmin->SetFillColorAlpha(40, 0.35);
        h_dRmin->SetXTitle("dRmin");
        h_dRmin->SetYTitle("Counts");
        h_dRmin->GetXaxis()->CenterTitle(true);
        h_dRmin->GetYaxis()->CenterTitle(true);
        h_dRmin->GetYaxis()->SetTitleOffset(1.2);     

  TH1F *h_EMCal_E = new TH1F("h_EMCal_E","CEMC Cluster energy",40,0,20);
        h_EMCal_E->SetFillColorAlpha(40, 0.35);
        h_EMCal_E->SetXTitle("E");
        h_EMCal_E->SetYTitle("Counts");
        h_EMCal_E->GetXaxis()->CenterTitle(true);
        h_EMCal_E->GetYaxis()->CenterTitle(true);
        h_EMCal_E->GetYaxis()->SetTitleOffset(1.2);

  TH1F *h_truth_p = new TH1F("h_truth_p","truth p",40,0,20);
        h_truth_p->SetFillColorAlpha(40, 0.35);
        h_truth_p->SetXTitle("truth_p");
        h_truth_p->SetYTitle("Counts");
        h_truth_p->GetXaxis()->CenterTitle(true);
        h_truth_p->GetYaxis()->CenterTitle(true);
        h_truth_p->GetYaxis()->SetTitleOffset(1.2);

  TH1F *h_track_p = new TH1F("h_track_p","Track p",40,0,20);
        h_track_p->SetFillColorAlpha(40, 0.35);
        h_track_p->SetXTitle("track_p");
        h_track_p->SetYTitle("Counts");
        h_track_p->GetXaxis()->CenterTitle(true);
        h_track_p->GetYaxis()->CenterTitle(true);
        h_track_p->GetYaxis()->SetTitleOffset(1.2);

  TH1F *h_track_pt = new TH1F("h_track_pt","Track pt",40,0,20);
        h_track_pt->SetFillColorAlpha(40, 0.35);
        h_track_pt->SetXTitle("track_pt");
        h_track_pt->SetYTitle("Counts");
        h_track_pt->GetXaxis()->CenterTitle(true);
        h_track_pt->GetYaxis()->CenterTitle(true);
        h_track_pt->GetYaxis()->SetTitleOffset(1.2);    

  TH1F *h_track_eta = new TH1F("h_track_eta","#eta",40,-5,5);
        h_track_eta->SetFillColorAlpha(40, 0.35);
        h_track_eta->SetXTitle("#eta");
        h_track_eta->SetYTitle("Counts");
        h_track_eta->GetXaxis()->CenterTitle(true);
        h_track_eta->GetYaxis()->CenterTitle(true);
        h_track_eta->GetYaxis()->SetTitleOffset(1.2);     
 

  TH1F *h_EMCal_Ep = new TH1F("h_EMCal_Ep","EMCal E/track_p",200,0,2);
        h_EMCal_Ep->SetFillColorAlpha(40, 0.35);
        h_EMCal_Ep->SetXTitle("E/p");
        h_EMCal_Ep->SetYTitle("Counts");
        h_EMCal_Ep->GetXaxis()->CenterTitle(true);
        h_EMCal_Ep->GetYaxis()->CenterTitle(true);
        h_EMCal_Ep->GetYaxis()->SetTitleOffset(1.2);

  TH1F *h_tow_E = new TH1F("h_tow_E","Tower energy",50,0,1);
        h_tow_E->SetFillColorAlpha(40, 0.35);
        h_tow_E->SetXTitle("Tower E");
        h_tow_E->SetYTitle("Counts");
        h_tow_E->GetXaxis()->CenterTitle(true);
        h_tow_E->GetYaxis()->CenterTitle(true);
        h_tow_E->GetYaxis()->SetTitleOffset(1.2);

  TH1F *h_tow_Ep = new TH1F("h_tow_Ep","Tower E/p",50,0.0,0.02);
        h_tow_Ep->SetFillColorAlpha(40, 0.35);
        h_tow_Ep->SetXTitle("E/p");
        h_tow_Ep->SetYTitle("Counts");
        h_tow_Ep->GetXaxis()->CenterTitle(true);
        h_tow_Ep->GetYaxis()->CenterTitle(true);
        h_tow_Ep->GetYaxis()->SetTitleOffset(1.2);

  TH1F *h_towclus_E = new TH1F("h_towclus_E","Tower/cluster energy",100,0.0,0.1);
        h_towclus_E->SetFillColorAlpha(40, 0.35);
        h_towclus_E->SetXTitle("Tower/cluster ");
        h_towclus_E->SetYTitle("Counts");
        h_towclus_E->GetXaxis()->CenterTitle(true);
        h_towclus_E->GetYaxis()->CenterTitle(true);
        h_towclus_E->GetYaxis()->SetTitleOffset(1.2);   

  TH1F *h_dRmin_tow = new TH1F("h_dRmin_tow","dRmin",40,0,4);
        h_dRmin_tow->SetFillColorAlpha(40, 0.35);
        h_dRmin_tow->SetXTitle("dRmin");
        h_dRmin_tow->SetYTitle("Counts");
        h_dRmin_tow->GetXaxis()->CenterTitle(true);
        h_dRmin_tow->GetYaxis()->CenterTitle(true);
        h_dRmin_tow->GetYaxis()->SetTitleOffset(1.2);    

         
  TH2D *h_truth_p_track_p  = new TH2D("track_truth_p","track_p vs truth_p",100,0,20,100,0,20);
        h_truth_p_track_p->SetXTitle("track_p (GeV)");
        h_truth_p_track_p->SetYTitle("truth_p (GeV)");      
              
   Long64_t nbytes = 0, nb = 0;

   cout << "Total number of events:  " << nentries << endl;
    int m_eventCounter = 0;
   //Events Loop
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // if( (m_eventCounter % 1000) ==0 ) cout << "Event number = "<< m_eventCounter << endl;
       m_eventCounter++;

       if(track_p->empty()) continue;
       if(clus_energy->empty()) continue;
       if(towenergy->empty()) continue;
       if (track_eta->empty()) continue;
       if (tr_CEMC_phi->empty()) continue;
       if (truth_eta->empty()) continue;

       //Tracks loop
       for (int j = 0; j < track_p->size(); ++j){

        if(abs(track_eta->at(j))>1.0) continue; //cut pseudorapidity 
         //  cout << "track eta:  " << track_eta->at(j)<< endl;
        
           if(abs(track_p->at(j))<0.1) continue;
           if(abs(track_p->at(j))>20.0) continue;
         // if(abs(track_p->at(j))<10) continue;
      //    cout << "track p:  " << track_p->at(j)<< endl;

         // dR and resolutions
         int idx_dR, idx_dEta, idx_dPhi, dummy, idx_dR_tow, idx_dR_track;
        
        if (tr_CEMC_eta->at(j)==9999.) continue;

          
           if (track_id->at(j)!=11) continue; //Turn on for electrons
        // if (track_id->at(j)!=-211) continue; //Turn on for pions
        //  if (track_id->at(j)!=-321) continue; //Turn on for kaons

       //   if ( track_id->at(j)!=11 && track_id->at(j)!=-211 && track_id->at(j)!=-321 ) continue;     

         // cout << "truth id:  " << truth_pid->at(j) << endl;
           cout << "pid:  " << track_id->at(j) << endl;

        h_truth_p_track_p->Fill(track_p->at(j),truth_p->at(j));       

         idx_dR  =0;
         h_dRmin->Fill( dRmin(tr_CEMC_eta->at(j), tr_CEMC_phi->at(j), idx_dR) ); //Tracks-clusters
    

        if( dRmin(tr_CEMC_eta->at(j), tr_CEMC_phi->at(j), idx_dR) > 0.1) continue; //dR cut clusters_tracks
      //  cout << "dR:  " << dRmin(tr_CEMC_eta->at(j), tr_CEMC_phi->at(j), idx_dR) << endl;

                   cout << "pid:  " << track_id->at(j) << endl;

       //  idx_dR  =0;
       //  h_dRmin->Fill( dRmin(tr_CEMC_eta->at(j), tr_CEMC_phi->at(j), idx_dR) ); //Tracks-clusters
     
         float scaleE = 0.8;
         float Ep0 = clus_energy->at(idx_dR)/track_p->at(j);
         float Ep = Ep0/scaleE;

      //  if (Ep<0.8) continue; //Turn on for 0.5-1 GeV
      //   if (Ep<0.3) continue; //Turn on for 1-2 GeV
      //  if (Ep<0.1) continue; //Turn on for 2-5 GeV
      //   if (Ep<0.1) continue; //Turn on for 5-10 GeV

        // cout << "Ep:  " << Ep << endl;

         h_EMCal_Ep->Fill(Ep);
         h_EMCal_E->Fill(clus_energy->at(idx_dR));

       //  if(Ep < 0.2){ 

          h_track_eta->Fill(track_eta->at(j));
          h_track_p->Fill(track_p->at(j)); 
          h_truth_p->Fill(truth_p->at(j)); 
      //    h_truth_p_track_p->Fill(track_p->at(j),truth_p->at(j));       
       //  }
         dRmin_tow(clus_eta->at(idx_dR), clus_phi->at(idx_dR), idx_dR_tow );

         float E_tow = towenergy->at(idx_dR_tow);
         float  Ep_tow = towenergy->at(idx_dR_tow)/track_p->at(j);
         float tow_clus_E = towenergy->at(idx_dR_tow)/clus_energy->at(idx_dR);
       //  cout << "E tow:" << E_tow << endl;
          
          h_tow_E->Fill(E_tow);     
          h_tow_Ep->Fill(Ep_tow);
          h_towclus_E->Fill(tow_clus_E); 
      //    h_track_p->Fill(track_p->at(j)); 
          h_track_pt->Fill(track_pt->at(j)); 
     //     h_track_eta->Fill(track_eta->at(j)); 
            
       } //End of tracks loop
                              
} //End of the events loop

h_EMCal_Ep->Write();
h_tow_Ep->Write();

h_EMCal_E->Write();
h_tow_E->Write();
h_towclus_E->Write();

h_dRmin->Write();
h_dRmin_tow->Write();
h_track_p->Write();
h_track_pt->Write();
h_track_eta->Write();

h_truth_p->Write();
h_truth_p_track_p->Write();

//////////////////////////////////////////////////////////////////////////////////////
 cout << "---End of the program. Gracias-----" << endl;

 ////////////////////////////////////////////////////////////////////////////////////
 cout << "                               /~\\                       "<< endl;                                                                                                                                        
   cout << "                              |oo )     This is typical!"<< endl;                                                                                                                                      
   cout << "                               \\=/_                  "<< endl;                                                                                                                                         
   cout << "              ___         #  /  _  \\   #  "<<endl;                                                                                                                                                     
   cout << "             /() \\       \\//|/.\\|\\//  "<<endl;                                                                                                                                                      
   cout << "           _|_____|_       \\/  \\_/ \\  "<<endl;                                                                                                                                                       
   cout << "          | | === | |         |\\ /|     "<<endl;                                                                                                                                                       
   cout << "          |_|  O  |_|         \\_ _/     "<<endl;                                                                                                                                                       
   cout << "           ||  O  ||          | | |       "<<endl;                                                                                                                                                         
   cout <<"          ||__*__||          | | |      "<<endl;                                                                                                                                                       
   cout <<"          |~ \\___// ~|        []|[]     "<<endl;                                                                                                                                                        
   cout <<"         /=\\ //=\\ /=\\       | | |   "<<endl;                                                                                                                                                          
    cout <<"__________[_]_[_]_[_]________/_]_[_\\____"<<endl;   
 ////////////////////From telnet towel.blinkenlights.nl///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

} //End of the code

/////////////////////////////////Functions//////////////////////////////////////////////////

   float Matching::dR(float Eta1, float Phi1, float Eta2, float Phi2){

     float etaDiff = fabs(Eta1 - Eta2);
     float phiDiff = fabs(Phi1 - Phi2) < TMath::Pi() ? fabs(Phi1 - Phi2) : 2*TMath::Pi() - fabs(Phi1 - Phi2);
     float dr = sqrt(etaDiff*etaDiff + phiDiff*phiDiff);

   return dr;
   }   

   float Matching::dRmin(float Eta1, float Phi1, int &index){
     float dRmin = 99;
   //cout << "clus size:  " << clus_energy->size() << endl;
     if(clus_energy->empty()) return dRmin;
     for (int j = 0; j < clus_energy->size(); ++j){

       float dr = dR( Eta1,  Phi1, clus_eta->at(j), clus_phi->at(j) );

       if(dr < dRmin){
         dRmin = dr;
         index = j;
      } 
   }
 
   return dRmin;
   }

  float Matching::dRmin_tow(float Eta1, float Phi1, int &index){
     float dRmin = 99;

     if(towenergy->empty()) return dRmin;
     for (int j = 0; j < towenergy->size(); ++j){
       // cout << "tower size:  " << towenergy->size() << endl;

       float dr = dR( Eta1,  Phi1, toweta->at(j), towphi->at(j) );

       if(dr < dRmin){
         dRmin = dr;
         index = j;
      } 
   }
 
   return dRmin;
   }

   float Matching::dEtamin(float Eta1, int &index){
     float dEtamin = 99;
     if(clus_eta->empty()) return dEtamin;
     for (int i = 0; i < clus_eta->size(); ++i){
        float etaDiff = fabs(Eta1 - clus_eta->at(i));
        if(etaDiff < dEtamin){
        dEtamin = etaDiff;
        index = i;
        }
     }
   return dEtamin;
   }

   float Matching::dPhimin(float Phi1, int &index){
     float dPhimin = 99;
     if(clus_phi->empty()) return dPhimin;
     for (int i = 0; i < clus_phi->size(); ++i){
      float phiDiff = fabs(Phi1 - clus_phi->at(i)) < TMath::Pi() ? fabs(Phi1 - clus_phi->at(i)) : 2*TMath::Pi() - fabs(Phi1 - clus_phi->at(i));
      if(phiDiff < dPhimin){
      dPhimin = phiDiff;
      index = i;
      } 
      }
   return dPhimin;
   }

   int Matching::Get_charge(int par_ID){
     bool is_neutral = false;
     int charge = 0;
 
      for (int i = 0; i < 7; ++i){
       // if(m_neutral[i] == par_ID) is_neutral = true;
      } 

      charge = is_neutral ? 0 : (par_ID > 0) - (par_ID < 0);

   return charge;
   }

