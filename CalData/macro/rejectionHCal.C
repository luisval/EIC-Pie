// Description:
//       Analysis macro: this macro estimates the pion's rejection coefficient and it plots the coefficient 
//       as a function of the momentum.// Environment:
//      ROOT
//
// Author List:
//       Luis Valenzuela Cazares          (original author)
//   
//-----------------------------------------------------------
////////////////////////////////////////////////////////////////

Int_t rejectionHCal()
{

TFile *file1 = TFile::Open("Epcut_G4EICDetector_out_hq2_pi_0.5-1GeV.root");
TFile *file2 = TFile::Open("Epcut_G4EICDetector_out_hq2_pi_1-2GeV.root");
TFile *file3 = TFile::Open("Epcut_G4EICDetector_out_hq2_pi_2-5GeV.root");
TFile *file4 = TFile::Open("Epcut_G4EICDetector_out_hq2_pi_5-10GeV.root"); 


TFile *file01 = TFile::Open("G4EICDetector_out_hq2_pi_0.5-1GeV.root");
TFile *file02 = TFile::Open("G4EICDetector_out_hq2_pi_1-2GeV.root");
TFile *file03 = TFile::Open("G4EICDetector_out_hq2_pi_2-5GeV.root");
TFile *file04 = TFile::Open("G4EICDetector_out_hq2_pi_5-10GeV.root"); 

/*
TFile *file1 = TFile::Open("Epcut_G4EICDetector_out_hq2_k_0.5-1GeV.root");
TFile *file2 = TFile::Open("Epcut_G4EICDetector_out_hq2_k_1-2GeV.root");
TFile *file3 = TFile::Open("Epcut_G4EICDetector_out_hq2_k_2-5GeV.root");
TFile *file4 = TFile::Open("Epcut_G4EICDetector_out_hq2_k_5-10GeV.root"); 
*/

/*
TFile *file1 = TFile::Open("G4EICDetector_out_hp_pi_1_5GeV.root");
TFile *file2 = TFile::Open("G4EICDetector_out_hp_pi_5_10GeV.root");
TFile *file3 = TFile::Open("G4EICDetector_out_hp_pi_10_20GeV.root");
TFile *file4 = TFile::Open("G4EICDetector_out_hp_pi_1_20GeV.root"); 
*/

/*
TFile *file1 = TFile::Open("G4EICDetector_out_low_pi_1-5GeV.root");
TFile *file2 = TFile::Open("G4EICDetector_out_low_pi_5-10GeV.root");
TFile *file3 = TFile::Open("G4EICDetector_out_low_pi_10-20GeV.root");
TFile *file4 = TFile::Open("G4EICDetector_out_low_pi_1-20GeV.root"); 
*/
       if (file1 && file2 && file3 &&file4->IsZombie()) { cout << "Error opening a file" << endl;
              exit(-1);} 
       else {cout << "Files are okay" << endl;}
 
//  gStyle->SetOptTitle(0); //No title for histograms
 // gStyle->SetOptStat(0);
  
  TH1F *h1_HCal_Ep = (TH1F*)file1->Get("h_tow_Ep");
        h1_HCal_Ep->GetXaxis()->SetTitle("HCal E/p");
        h1_HCal_Ep->GetYaxis()->SetTitle("Counts");
        h1_HCal_Ep->SetFillColor(0); 
        h1_HCal_Ep->SetLineColor(1);
        h1_HCal_Ep->SetLineWidth(6);  

  TH1F *h2_HCal_Ep = (TH1F*)file2->Get("h_tow_Ep");
        h2_HCal_Ep->GetXaxis()->SetTitle("HCal E/p");
        h2_HCal_Ep->GetYaxis()->SetTitle("Counts");
        h2_HCal_Ep->SetFillColor(0); 
        h2_HCal_Ep->SetLineColor(1);
        h2_HCal_Ep->SetLineWidth(6);  

  TH1F *h3_HCal_Ep = (TH1F*)file3->Get("h_tow_Ep");
        h3_HCal_Ep->GetXaxis()->SetTitle("HCal E/p");
        h3_HCal_Ep->GetYaxis()->SetTitle("Counts");
        h3_HCal_Ep->SetFillColor(0); 
        h3_HCal_Ep->SetLineColor(1);
        h3_HCal_Ep->SetLineWidth(6);  
     
  TH1F *h4_HCal_Ep = (TH1F*)file4->Get("h_tow_Ep");
        h4_HCal_Ep->GetXaxis()->SetTitle("HCal E/p");
        h4_HCal_Ep->GetYaxis()->SetTitle("Counts");
        h4_HCal_Ep->SetFillColor(0); 
        h4_HCal_Ep->SetLineColor(1);
        h4_HCal_Ep->SetLineWidth(6);  

/////////////////////////////////////////////////////////
 TH1F *h1_HCal_Ep0 = (TH1F*)file01->Get("h_tow_Ep");
        h1_HCal_Ep0->GetXaxis()->SetTitle("HCal E/p");
        h1_HCal_Ep0->GetYaxis()->SetTitle("Counts");
        h1_HCal_Ep0->SetFillColor(0); 
        h1_HCal_Ep->SetLineColor(1);
        h1_HCal_Ep->SetLineWidth(6);  

  TH1F *h2_HCal_Ep0 = (TH1F*)file02->Get("h_tow_Ep");
        h2_HCal_Ep0->GetXaxis()->SetTitle("HCal E/p");
        h2_HCal_Ep0->GetYaxis()->SetTitle("Counts");
        h2_HCal_Ep0->SetFillColor(0); 
        h2_HCal_Ep0->SetLineColor(1);
        h2_HCal_Ep0->SetLineWidth(6);  

  TH1F *h3_HCal_Ep0 = (TH1F*)file03->Get("h_tow_Ep");
        h3_HCal_Ep0->GetXaxis()->SetTitle("HCal E/p");
        h3_HCal_Ep0->GetYaxis()->SetTitle("Counts");
        h3_HCal_Ep0->SetFillColor(0); 
        h3_HCal_Ep0->SetLineColor(1);
        h3_HCal_Ep0->SetLineWidth(6);  
     
  TH1F *h4_HCal_Ep0 = (TH1F*)file04->Get("h_tow_Ep");
        h4_HCal_Ep0->GetXaxis()->SetTitle("HCal E/p");
        h4_HCal_Ep0->GetYaxis()->SetTitle("Counts");
        h4_HCal_Ep0->SetFillColor(0); 
        h4_HCal_Ep0->SetLineColor(1);
        h4_HCal_Ep0->SetLineWidth(6);          

///////////////////////////////////////////////////////////////////
        Int_t nbinsh1 = h1_HCal_Ep->Integral();
        Int_t nbinsh2 = h2_HCal_Ep->Integral();
        Int_t nbinsh3 = h3_HCal_Ep->Integral();
        Int_t nbinsh4 = h4_HCal_Ep->Integral();

      //h1_HCal_Ep->Scale(1./(h1_HCal_Ep)->Integral());
 
        float totalIntegral_pi1 = h1_HCal_Ep0->Integral(h1_HCal_Ep->FindFixBin(0), h1_HCal_Ep->FindFixBin(2));
        float totalIntegral_pi2 = h2_HCal_Ep0->Integral(h2_HCal_Ep->FindFixBin(0), h2_HCal_Ep->FindFixBin(2));
        float totalIntegral_pi3 = h3_HCal_Ep0->Integral(h3_HCal_Ep->FindFixBin(0), h3_HCal_Ep->FindFixBin(2));
        float totalIntegral_pi4 = h4_HCal_Ep0->Integral(h4_HCal_Ep->FindFixBin(0), h4_HCal_Ep->FindFixBin(2));

       float pi_cut1 = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0.0), h1_HCal_Ep->FindFixBin(2));
       float pi_cut2 = h2_HCal_Ep->Integral(h2_HCal_Ep->FindFixBin(0.0), h2_HCal_Ep->FindFixBin(2));
       float pi_cut3 = h3_HCal_Ep->Integral(h3_HCal_Ep->FindFixBin(0.0), h3_HCal_Ep->FindFixBin(2));
       float pi_cut4 = h4_HCal_Ep->Integral(h4_HCal_Ep->FindFixBin(0.0), h4_HCal_Ep->FindFixBin(2));


        float rej1_pi= totalIntegral_pi1/pi_cut1; 
        float rej2_pi= totalIntegral_pi2/pi_cut2; 
        float rej3_pi= totalIntegral_pi3/pi_cut3; 
        float rej4_pi= totalIntegral_pi4/pi_cut4; 
        
        cout <<"Total pions: " << totalIntegral_pi1 << endl;
        cout <<"Total pions: " << totalIntegral_pi2 << endl;
        cout <<"Total pions: " << totalIntegral_pi3 << endl;
        cout <<"Total pions: " << totalIntegral_pi4 << endl;

        cout <<"Pions cut: " << pi_cut1 << endl;
        cout <<"Pions cut: " << pi_cut2 << endl;
        cout <<"Pions cut: " << pi_cut3 << endl;
        cout <<"Pions cut: " << pi_cut4 << endl;

        cout <<"rej1_pi: " << rej1_pi << endl;
        cout <<"rej2_pi: " << rej2_pi << endl;
        cout <<"rej3_pi: " << rej3_pi << endl;
        cout <<"rej4_pi: " << rej4_pi << endl;

        // h1_HCal_Ep->Scale(1./(nbintstotal));

TCanvas *c2 = new TCanvas("c5","#pi^{-} rejection ",200,10,500,300);
  TGraph* gr1 = new TGraph();
  TGraph* gr2 = new TGraph();
  TGraph* gr3 = new TGraph();
  TGraph* gr4 = new TGraph();

  TMultiGraph *mg = new TMultiGraph();
      mg->SetTitle("E_{min} vs rejection;E_{min}(GeV); #pi^{-} rejection");
      mg->GetXaxis()->SetLimits(0.1, 1.02);
      mg->GetXaxis()->SetTitleOffset(1.2);
      mg->GetYaxis()->SetTitleOffset(1.2);
      mg->GetXaxis()->CenterTitle();
      mg->GetYaxis()->CenterTitle();      

   TAxis *axis1 = gr1->GetXaxis();
   axis1->SetLimits(0.2,10.0); // along X
  
   mg->Add(gr1,"");
   // mg->Add(gr1,"ALP");
    mg->Add(gr2,"");
    mg->Add(gr3,"");
    mg->Add(gr4,"");
    mg->Draw("ap");
     
   gr1->SetName("gr1");
   gr1->SetTitle("0.5-1 GeV");
   gr1->SetMarkerStyle(21);
   gr1->SetMarkerSize(2);
  // gr1->SetLineColor(1);
  // gr1->SetLineWidth(4);
   gr1->SetFillStyle(0);
 
   gr2->SetName("gr2");
   gr2->SetTitle("1-2 GeV");
   gr2->SetMarkerStyle(22);
   gr2->SetMarkerColor(41);
   gr2->SetMarkerSize(2);
  // gr2->SetLineColor(41);
  // gr2->SetLineWidth(4);
   gr2->SetFillStyle(0);

   gr3->SetName("gr3");
   gr3->SetTitle("2-5 GeV");
   gr3->SetMarkerStyle(23);
   gr3->SetMarkerColor(46);
   gr3->SetMarkerSize(2);
  // gr3->SetLineColor(46);
  // gr3->SetLineWidth(4);
   gr3->SetFillStyle(0);

   gr4->SetName("gr4");
   gr4->SetTitle("5-10 GeV");
   gr4->SetMarkerStyle(20);
   gr4->SetMarkerColor(47);
   gr4->SetMarkerSize(2);
  // gr4->SetLineColor(49);
  // gr4->SetLineWidth(4);
   gr4->SetFillStyle(0);

  gr1->SetPoint(1,0.001,rej1_pi);
  gr2->SetPoint(2,0.002,rej2_pi);
  gr3->SetPoint(3,0.004,rej3_pi);
  gr4->SetPoint(4,0.006,rej4_pi);

  c2->BuildLegend();

  c2->SaveAs("Rej.gif");

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  cout<<"End of the program. Gracias"<<endl;
  return 0;  
}

