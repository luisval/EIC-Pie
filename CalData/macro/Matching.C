////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// This macro finds the closest cluster to a given track and the closest tower to a given cluster. 
////// Besides, it plots the coefficient of the deposited energy by the track momentum.
////// Authors: Sebastian Tapia
//////          Luis Valenzuela Cazares
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
   
  TFile* fout = new TFile(Form("G4EICDetector_out.root"),"RECREATE");

  TH1F *h_dRmin = new TH1F("h_dRmin","dRmin",40,0,4);
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

  TH1F *h_EMCal_Ep = new TH1F("h_EMCal_Ep","EMCal E/track_p",20,0,2);
        h_EMCal_Ep->SetFillColorAlpha(40, 0.35);
        h_EMCal_Ep->SetXTitle("E");
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
         
   Long64_t nbytes = 0, nb = 0;

   cout << "Total number of events:  " << nentries << endl;
    int m_eventCounter = 0;
   //Events Loop
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

       if( (m_eventCounter % 100) ==0 ) cout << "Event number = "<< m_eventCounter << endl;
       m_eventCounter++;


       if(track_p->empty()) continue;
       if(track_pt->empty()) continue;
       if(clus_energy->empty()) continue;
       if(towenergy->empty()) continue;
       if(tr_CEMC_eta->empty()) continue;

       //Tracks loop
       for (int j = 0; j < track_pt->size(); ++j){

          //   cout << "track size:  " << track_pt->size() << endl;

          
         if(abs(track_eta->at(j))>1.5) continue;
         // dR and resolutions
         int idx_dR, idx_dEta, idx_dPhi, dummy, idx_dR_tow;
         h_dRmin->Fill( dRmin(tr_CEMC_eta->at(j), tr_CEMC_phi->at(j), idx_dR) );

         float Ep = clus_energy->at(idx_dR)/track_p->at(j);
         h_EMCal_Ep->Fill(Ep);

         h_EMCal_E->Fill(clus_energy->at(idx_dR));


         dRmin_tow(clus_eta->at(idx_dR), clus_phi->at(idx_dR), idx_dR_tow );

         float E_tow = towenergy->at(idx_dR_tow);

         float  Ep_tow = towenergy->at(idx_dR_tow)/track_p->at(j);

         float tow_clus_E = towenergy->at(idx_dR_tow)/clus_energy->at(idx_dR);


       //  cout << "E tow:" << E_tow << endl;
          
          h_tow_E->Fill(E_tow);     

          h_tow_Ep->Fill(Ep_tow);

          h_towclus_E->Fill(tow_clus_E); 
     
          h_track_p->Fill(track_p->at(j)); 
          h_track_pt->Fill(track_pt->at(j)); 

       } //End of tracks loop

                               
} //End of the events loop

TCanvas *c0 = new TCanvas();
   c0->SetLogy();  
   h_dRmin->SetXTitle("dRmin");
   h_dRmin->SetYTitle("Counts");
   h_dRmin->GetXaxis()->CenterTitle(true);
   h_dRmin->GetYaxis()->CenterTitle(true);
   h_dRmin->GetYaxis()->SetTitleOffset(1.2);
   h_dRmin->Draw();
   c0->SaveAs("plots/dRmin.svg");

 TCanvas *c1 = new TCanvas();
   //c1->SetLogy();  
   h_EMCal_E->SetXTitle("E");
   h_EMCal_E->SetYTitle("Counts");
   h_EMCal_E->GetXaxis()->CenterTitle(true);
   h_EMCal_E->GetYaxis()->CenterTitle(true);
   h_EMCal_E->GetYaxis()->SetTitleOffset(1.2);
   h_EMCal_E->Draw();
   c1->SaveAs("plots/EMCal_E.svg");

 TCanvas *c2 = new TCanvas();
   //c1->SetLogy();  
   h_EMCal_Ep->SetXTitle("E/p");
   h_EMCal_Ep->SetYTitle("Counts");
   h_EMCal_Ep->GetXaxis()->CenterTitle(true);
   h_EMCal_Ep->GetYaxis()->CenterTitle(true);
   h_EMCal_Ep->GetYaxis()->SetTitleOffset(1.2);
   h_EMCal_Ep->Draw();
   c2->SaveAs("plots/EMCal_Ep.svg");

 TCanvas *c3 = new TCanvas();
   c3->SetLogy();  
   h_tow_E->SetXTitle("Tower energy");
   h_tow_E->SetYTitle("Counts");
   h_tow_E->GetXaxis()->CenterTitle(true);
   h_tow_E->GetYaxis()->CenterTitle(true);
   h_tow_E->GetYaxis()->SetTitleOffset(1.2);
   h_tow_E->Draw();
   c3->SaveAs("plots/tow_E.svg");

 TCanvas *c4 = new TCanvas();
   c4->SetLogy();  
   h_towclus_E->SetXTitle("tower/cluster");
   h_towclus_E->SetYTitle("Counts");
   h_towclus_E->GetXaxis()->CenterTitle(true);
   h_towclus_E->GetYaxis()->CenterTitle(true);
   h_towclus_E->GetYaxis()->SetTitleOffset(1.2);
   h_towclus_E->Draw();
   c4->SaveAs("plots/towclus_E.svg");

 TCanvas *c5 = new TCanvas();
   c5->SetLogy();  
   h_tow_Ep->SetXTitle("E/p");
   h_tow_Ep->SetYTitle("Counts");
   h_tow_Ep->GetXaxis()->CenterTitle(true);
   h_tow_Ep->GetYaxis()->CenterTitle(true);
   h_tow_Ep->GetYaxis()->SetTitleOffset(1.2);
   h_tow_Ep->Draw();
   c5->SaveAs("plots/tow_Ep.svg");



  TCanvas *c6 = new TCanvas();
   //c6->SetLogy();  
   h_track_p->SetXTitle("track_p");
   h_track_p->SetYTitle("Counts");
   h_track_p->GetXaxis()->CenterTitle(true);
   h_track_p->GetYaxis()->CenterTitle(true);
   h_track_p->GetYaxis()->SetTitleOffset(1.2);
   h_track_p->Draw();
   c6->SaveAs("plots/track_p.svg");
   
 TCanvas *c7 = new TCanvas();
   //c6->SetLogy();  
   h_track_pt->SetXTitle("track_pt");
   h_track_pt->SetYTitle("Counts");
   h_track_pt->GetXaxis()->CenterTitle(true);
   h_track_pt->GetYaxis()->CenterTitle(true);
   h_track_pt->GetYaxis()->SetTitleOffset(1.2);
   h_track_pt->Draw();
   c7->SaveAs("plots/track_pt.svg");

TCanvas *c80 = new TCanvas();
   c0->SetLogy();  
   h_dRmin_tow->SetXTitle("dRmin");
   h_dRmin_tow->SetYTitle("Counts");
   h_dRmin_tow->GetXaxis()->CenterTitle(true);
   h_dRmin_tow->GetYaxis()->CenterTitle(true);
   h_dRmin_tow->GetYaxis()->SetTitleOffset(1.2);
   h_dRmin_tow->Draw();
   c0->SaveAs("plots/dRmin.svg");
     

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

     if(clus_pt->empty()) return dRmin;
     for (int j = 0; j < clus_pt->size(); ++j){
       // cout << "clus size:  " << clus_pt->size() << endl;

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
       // cout << "clus size:  " << clus_pt->size() << endl;

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
     if(clus_pt->empty()) return dEtamin;
     for (int i = 0; i < clus_pt->size(); ++i){
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
     if(clus_pt->empty()) return dPhimin;
     for (int i = 0; i < clus_pt->size(); ++i){
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

