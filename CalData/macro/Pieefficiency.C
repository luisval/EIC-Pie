// Description:
//      
//       Analysis macro: this macro plots the coefficient of Energy/momentum distributions 
//       of both electrons and pions.
// Environment:
//      ROOT
//
// Author List:
//       Luis Valenzuela Cazares          (original author)
//   
//-----------------------------------------------------------
////////////////////////////////////////////////////////////////

Int_t Pieefficiency()
{

TFile *file1 = TFile::Open("G4EICDetector_out_e.root");
TFile *file2 = TFile::Open("G4EICDetector_out_pi.root");

   if (file1 && file2->IsZombie()) { cout << "Error opening a file" << endl;
       exit(-1);} 
   else {cout << "Files are okay" << endl;}
 
//  gStyle->SetOptTitle(0); //No title for histograms
 // gStyle->SetOptStat(0);
  
  TH1F *h1_EMCal_Ep = (TH1F*)file1->Get("h_EMCal_Ep");
        h1_EMCal_Ep->GetXaxis()->SetTitle("EMCal E/p");
        h1_EMCal_Ep->GetYaxis()->SetTitle("Counts");

  TH1F *h2_EMCal_Ep = (TH1F*)file2->Get("h_EMCal_Ep");
        h2_EMCal_Ep->GetXaxis()->SetTitle("EMCal E/p");
        h2_EMCal_Ep->GetYaxis()->SetTitle("Counts");

        Int_t nbinsh1 = h1_EMCal_Ep->Integral();
        Int_t nbinsh2 = h2_EMCal_Ep->Integral();
        Int_t nbintstotal = nbinsh1+nbinsh2;

        cout <<"nbinsh1: " << nbinsh1 << endl;
        cout <<"nbinsh2: " << nbinsh2 << endl;
        cout <<"Total bins: " << nbintstotal << endl;

        h1_EMCal_Ep->Scale(1./(nbintstotal));
        h2_EMCal_Ep->Scale(1./(nbintstotal));

           //h1_EMCal_Ep->Scale(1./(h1_EMCal_Ep)->Integral());
           //h2_EMCal_Ep->Scale(1./(h2_EMCal_Ep)->Integral());

          h1_EMCal_Ep->SetMarkerStyle(20);
          h2_EMCal_Ep->SetMarkerStyle(24);


  TCanvas *c1 = new TCanvas("c12","EMCal E/p");
//  gStyle->SetOptStat(false);
  c1->SetRightMargin(0.0465116);
  c1->SetTopMargin(0.1);
  c1->SetFillColor(0);
  
        h1_EMCal_Ep->Draw("same");
        h2_EMCal_Ep->Draw("same");

  TLegend *leg = new TLegend(0.7,0.6,0.92,0.89);
  leg->SetTextFont(62);
  leg->SetLineColor(0);
  leg->SetLineStyle(0);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->AddEntry("","Particle","");
  leg->AddEntry("h1_EMCal_Ep","e^{-}","p");
  leg->AddEntry("h2_EMCal_Ep","#pi^{-}","p");
  leg->Draw();
  c1->SaveAs("Ep_pie.pdf");
  
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // file1->Close();
 // file2->Close();

  cout<<"End of the program. Gracias"<<endl;
  return 0;  
}

