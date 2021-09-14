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

Int_t track_truth_p()
{

TFile *file1 = TFile::Open("G4EICDetector_out.root");

      
       if (file1->IsZombie()) { cout << "Error opening a file" << endl;
       exit(-1);} 
       else {cout << "File is okay" << endl;}
 
//  gStyle->SetOptTitle(0); //No title for histograms
 // gStyle->SetOptStat(0);
  
  TH1F *h_truth_p = (TH1F*)file1->Get("h_truth_p");
        h_truth_p->GetXaxis()->SetTitle("truth_p (GeV)");
        h_truth_p->GetYaxis()->SetTitle("Counts");
        h_truth_p->SetFillColor(0); 
        h_truth_p->SetLineColor(1);
        h_truth_p->SetLineColor(1);
       h_truth_p->SetLineWidth(6);  
      //h_truth_p->Scale(1./(h_truth_p)->Integral());


  TH2D *h_truth_p_track_p = (TH2D*)file1->Get("h_truth_p_track_p");
      //  h_truth_p_track_p->SetXTitle("track_p (GeV)");
      //  h_truth_p_track_p->SetYTitle("truth_p  (GeV)");
       

  TCanvas *c1 = new TCanvas("c1","truth_p");
  gStyle->SetOptStat(false);
  c1->SetRightMargin(0.1);
  c1->SetTopMargin(0.1);
  c1->SetFillColor(0);
  h_truth_p->Draw();

  //c1->BuildLegend();
 // c1->SaveAs("truth_p.pdf");
   
  TCanvas *c2 = new TCanvas("c2","track_p vs truth_p",0,20,0,20);
 /* gStyle->SetOptStat(false);
  c2->SetRightMargin(0.1);
  c2->SetTopMargin(0.1);
  c2->SetFillColor(0); */
  
  h_truth_p_track_p->Draw();
 // h_truth_p_track_p->Draw("colz,1");
 //  c2->Update();
  

//  h_truth_p_track_p->Draw("z same"); // draw the "color palette"
 // c2->BuildLegend();
  c2->SaveAs("truth_p.pdf");


///////////////////////////////////////////////////////////////////////////
  cout<<"End of the program. Gracias"<<endl;
  return 0;  
}

