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

   if (file1->IsZombie()) {
      cout << "Error opening file 1" << endl;
      exit(-1);
      } else {
            cout << "File 1 is okay" << endl;
   }

  gStyle->SetOptTitle(0); //No title for histograms
  gStyle->SetOptStat(0);

 TCanvas *c1 = new TCanvas("c1","EMCal");

  TH1F *h1_EMCal_Ep = (TH1F*)file1->Get("h_EMCal_Ep");
 // h_EMCal_Ep->GetXaxis()->SetRangeUser(0,3);
 // h_EMCal_Ep->SetStats(kFALSE);
  h1_EMCal_Ep->SetMarkerStyle(20);

   h1_EMCal_Ep->SetFillColorAlpha(40, 0.1);
   h1_EMCal_Ep->SetLineColorAlpha(kBlack, 0.35);
//h1_EMCal_Ep->SetFillColor(kViolet); 


  h1_EMCal_Ep->GetXaxis()->SetTitle("EMCal E/p");
  h1_EMCal_Ep->GetYaxis()->SetTitle("Counts");
  //c1->SetLogy();
  h1_EMCal_Ep->SetDirectory(0);
  file1->Close();
 // h_EMCal_Ep->Scale(1./h_EMCal_Ep->Integral());
  h1_EMCal_Ep->Draw("same");

    TH1F *h2_EMCal_Ep = (TH1F*)file2->Get("h_EMCal_Ep");
      h2_EMCal_Ep->SetMarkerStyle(21);


   h2_EMCal_Ep->SetFillColorAlpha(41, 0.1);
     h2_EMCal_Ep->SetLineColorAlpha(kBlue, 0.35);
   // h2_EMCal_Ep->SetFillColor(kBlue); 
   // h2_EMCal_Ep->SetFillColor(1);
   // h2_EMCal_Ep->SetFillStyle(3001);

  h2_EMCal_Ep->GetXaxis()->SetTitle("EMCal E/p");
  h2_EMCal_Ep->GetYaxis()->SetTitle("Counts");
  //c1->SetLogy();
  h2_EMCal_Ep->SetDirectory(0);
  file1->Close();
 // h_EMCal_Ep->Scale(1./h_EMCal_Ep->Integral());
  h2_EMCal_Ep->Draw("same");



   TLegend *leg = new TLegend(0.65,0.8,0.92,0.89);
   leg->SetTextFont(62);                                
   leg->SetLineColor(0);
   leg->SetLineStyle(0);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->AddEntry("","Particles","");
   leg->AddEntry("h1_EMCal_Ep","e^{-}","f");
   leg->AddEntry("h2_EMCal_Ep","#pi^{-}","f");
   leg->Draw();

     c1->SaveAs("Ep_pie.pdf");



///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // file1->Close();

  cout<<"End of the program. Gracias"<<endl;
  return 0;
   
}

