#define Matching_cxx
#include "Matching.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Matching::Loop(){

    cout << "---Start of the program-----" << endl;


   if (fChain == 0) return;

   float m_pi = 3.14159265359;

   Long64_t nentries = fChain->GetEntriesFast();

   TH1F* th1[12]; 
   TH1F* th1_dist[12];
   TH2F* th2[10];

   TFile* fout = new TFile(Form("G4EICDetector_out.root"),"RECREATE");

   for (int i = 0; i < 2; ++i) th1[i] = new TH1F(Form("th1%i",i),Form("th1%i",i),100,0,20);
   for (int i = 2; i < 4; ++i) th1[i] = new TH1F(Form("th1%i",i),Form("th1%i",i),30,-4,4);
   for (int i = 4; i < 6; ++i) th1[i] = new TH1F(Form("th1%i",i),Form("th1%i",i),30,-m_pi,m_pi);
   for (int i = 6; i < 8; ++i) th1[i] = new TH1F(Form("th1%i",i),Form("th1%i",i),30,-4,4);
   for (int i = 9; i < 12; ++i) th1[i] = new TH1F(Form("th1%i",i),Form("th1%i",i),100,0,0.5);   
   
   th1_dist[0] = new TH1F(Form("th1_dist%i",0),Form("th1_dist%i",0),100,0,20);//tracks
   th1_dist[1] = new TH1F(Form("th1_dist%i",1),Form("th1_dist%i",1),100,0,20);//truth charged
   th1_dist[2] = new TH1F(Form("th1_dist%i",2),Form("th1_dist%i",2),100,0,20);//reco

   th1_dist[3] = new TH1F(Form("th1_dist%i",3),Form("th1_dist%i",3),60,-7,7);//all truth
   th1_dist[4] = new TH1F(Form("th1_dist%i",4),Form("th1_dist%i",4),60,-7,7);//truth charged
   th1_dist[5] = new TH1F(Form("th1_dist%i",5),Form("th1_dist%i",5),60,-7,7);//truth charged time charge
   th1_dist[6] = new TH1F(Form("th1_dist%i",6),Form("th1_dist%i",6),60,-7,7);//reco
   th1_dist[7] = new TH1F(Form("th1_dist%i",7),Form("th1_dist%i",7),60,0,5);//reco time charge

   th1_dist[8] = new TH1F(Form("th1_dist%i",8),Form("th1_dist%i",8),200,0,1);//all truth
   th1_dist[9] = new TH1F(Form("th1_dist%i",9),Form("th1_dist%i",9),60,-m_pi,m_pi);//truth charged
   th1_dist[10] = new TH1F(Form("th1_dist%i",10),Form("th1_dist%i",10),60,-m_pi,m_pi);//reco

   for (int i = 0; i < 3; ++i) th2[i] = new TH2F(Form("th2%i",i),Form("th2%i",i),50,0,20,100,-2,2);

   th2[6] = new TH2F(Form("th2%i",6),Form("th2%i",6),100,0,20,100,0,0.5);
   th2[7] = new TH2F(Form("th2%i",7),Form("th2%i",7),30,-4,4,100,0,0.5);
   th2[8] = new TH2F(Form("th2%i",8),Form("th2%i",8),30,-m_pi,m_pi,100,0,0.5);

   th2[3] = new TH2F(Form("th2%i",3),Form("th2%i",3),100,0,20,100,0,20);
   th2[4] = new TH2F(Form("th2%i",4),Form("th2%i",4),100,-4,4,100,-4,4);
   th2[5] = new TH2F(Form("th2%i",5),Form("th2%i",5),100,-m_pi,m_pi,100,-m_pi,m_pi);

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

      // TProfile * prof_dr_pt = th2[6]->ProfileX();

       if(track_pt->empty()) continue;
       if(clus_energy->empty()) continue;

       //Tracks loop
       for (int j = 0; j < track_pt->size(); ++j){

          //   cout << "track size:  " << track_pt->size() << endl;
          
         if(abs(track_eta->at(j))>1.5) continue;
         // dR and resolutions
         int idx_dR, idx_dEta, idx_dPhi, dummy, idx_dR_tow;
         th1[9]->Fill(  dEtamin(tr_CEMC_eta->at(j), idx_dEta) );
         th1[10]->Fill( dPhimin(tr_CEMC_phi->at(j), idx_dPhi) );
         th1[11]->Fill( dRmin(tr_CEMC_eta->at(j), tr_CEMC_phi->at(j), idx_dR) );

         float Ep = clus_energy->at(idx_dR)/track_p->at(j);

         th1_dist[7]->Fill(Ep);

         dRmin_tow(clus_eta->at(idx_dR), clus_phi->at(idx_dR), idx_dR_tow );

         float E_tow = towenergy->at(idx_dR_tow);

       //  cout << "E tow:" << E_tow << endl;
          
          th1_dist[8]->Fill(E_tow);          


       } //End of tracks loop

                for (int j = 0; j < track_pt->size(); ++j){
                    th1_dist[2]->Fill(track_pt->at(j));
                    th1_dist[6]->Fill(track_eta->at(j));
                 //   th1_dist[7]->Fill(track_charge->at(j)*track_eta->at(j));
                    th1_dist[10]->Fill(track_phi->at(j));
                 //   th1_dist[7]->Fill(Ep);

                 }// End truth events  
                 
} //End of the events loop


th1[9]->SetName("dEtamin"); th1[9]->Write();
th1[10]->SetName("dPhimin"); th1[10]->Write();
th1[11]->SetName("dRmin"); th1[11]->Write();


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

