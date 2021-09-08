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

Int_t electroneffHCal()
{

TFile *file1 = TFile::Open("Epcut_G4EICDetector_out_hq2_e_0.5-1GeV.root");
TFile *file2 = TFile::Open("Epcut_G4EICDetector_out_hq2_e_1-2GeV.root");
TFile *file3 = TFile::Open("Epcut_G4EICDetector_out_hq2_e_2-5GeV.root");
TFile *file4 = TFile::Open("Epcut_G4EICDetector_out_hq2_e_5-10GeV.root");


       if (file1 && file2 && file3 && file4->IsZombie()) { cout << "Error opening a file" << endl;
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
        h2_HCal_Ep->SetLineColor(41);
        h2_HCal_Ep->SetLineWidth(6);  

  TH1F *h3_HCal_Ep = (TH1F*)file3->Get("h_tow_Ep");
        h3_HCal_Ep->GetXaxis()->SetTitle("HCal E/p");
        h3_HCal_Ep->GetYaxis()->SetTitle("Counts");
        h3_HCal_Ep->SetFillColor(0);    
        h3_HCal_Ep->SetLineColor(46);
        h3_HCal_Ep->SetLineWidth(6);  
   
  TH1F *h4_HCal_Ep = (TH1F*)file4->Get("h_tow_Ep");
        h4_HCal_Ep->GetXaxis()->SetTitle("HCal E/p");
        h4_HCal_Ep->GetYaxis()->SetTitle("Counts");
        h4_HCal_Ep->SetFillColor(0);    
        h4_HCal_Ep->SetLineColor(49);
        h4_HCal_Ep->SetLineWidth(6);  
     
        Int_t nbinsh1 = h1_HCal_Ep->Integral();
        Int_t nbinsh2 = h2_HCal_Ep->Integral();
        Int_t nbinsh3 = h3_HCal_Ep->Integral();
        Int_t nbinsh4 = h3_HCal_Ep->Integral();

       // Int_t nbintstotal = nbinsh1+nbinsh2+nbinsh3+nbinsh4;

      //h1_HCal_Ep->Scale(1./(h1_HCal_Ep)->Integral());
     // h2_HCal_Ep->Scale(1./(h2_HCal_Ep)->Integral());
     // h3_HCal_Ep->Scale(1./(h3_HCal_Ep)->Integral());

        float totalIntegral_e = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0), h1_HCal_Ep->FindFixBin(0.02));
        
        float rangeIntegral1_e = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0.018), h1_HCal_Ep->FindFixBin(2));
        float rangeIntegral2_e = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0.016), h1_HCal_Ep->FindFixBin(2));
        float rangeIntegral3_e = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0.014), h1_HCal_Ep->FindFixBin(2));
        float rangeIntegral4_e = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0.012), h1_HCal_Ep->FindFixBin(2));
        float rangeIntegral5_e = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0.010), h1_HCal_Ep->FindFixBin(2));
        float rangeIntegral6_e = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0.008), h1_HCal_Ep->FindFixBin(2));
        float rangeIntegral7_e = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0.006), h1_HCal_Ep->FindFixBin(2));
      /*  float rangeIntegral8_e = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0.3), h1_HCal_Ep->FindFixBin(2));
        float rangeIntegral9_e = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0.2), h1_HCal_Ep->FindFixBin(2));
        float rangeIntegral10_e = h1_HCal_Ep->Integral(h1_HCal_Ep->FindFixBin(0.1), h1_HCal_Ep->FindFixBin(2)); */

        float totalIntegral_e2 = h2_HCal_Ep->Integral(h2_HCal_Ep->FindFixBin(0), h2_HCal_Ep->FindFixBin(0.02));
        
        float rangeIntegral1_e2 = h2_HCal_Ep->Integral(h2_HCal_Ep->FindFixBin(0.018), h2_HCal_Ep->FindFixBin(2));
        float rangeIntegral2_e2 = h2_HCal_Ep->Integral(h2_HCal_Ep->FindFixBin(0.016), h2_HCal_Ep->FindFixBin(2));
        float rangeIntegral3_e2 = h2_HCal_Ep->Integral(h2_HCal_Ep->FindFixBin(0.014), h2_HCal_Ep->FindFixBin(2));
        float rangeIntegral4_e2 = h2_HCal_Ep->Integral(h2_HCal_Ep->FindFixBin(0.012), h2_HCal_Ep->FindFixBin(2));
        float rangeIntegral5_e2 = h2_HCal_Ep->Integral(h2_HCal_Ep->FindFixBin(0.010), h2_HCal_Ep->FindFixBin(2));
        float rangeIntegral6_e2 = h2_HCal_Ep->Integral(h2_HCal_Ep->FindFixBin(0.008), h2_HCal_Ep->FindFixBin(2));
        float rangeIntegral7_e2 = h2_HCal_Ep->Integral(h2_HCal_Ep->FindFixBin(0.006), h2_HCal_Ep->FindFixBin(2));

        float totalIntegral_e3 = h3_HCal_Ep->Integral(h3_HCal_Ep->FindFixBin(0), h3_HCal_Ep->FindFixBin(2));
        
        float rangeIntegral1_e3 = h3_HCal_Ep->Integral(h3_HCal_Ep->FindFixBin(0.018), h3_HCal_Ep->FindFixBin(2));
        float rangeIntegral2_e3 = h3_HCal_Ep->Integral(h3_HCal_Ep->FindFixBin(0.016), h3_HCal_Ep->FindFixBin(2));
        float rangeIntegral3_e3 = h3_HCal_Ep->Integral(h3_HCal_Ep->FindFixBin(0.014), h3_HCal_Ep->FindFixBin(2));
        float rangeIntegral4_e3 = h3_HCal_Ep->Integral(h3_HCal_Ep->FindFixBin(0.012), h3_HCal_Ep->FindFixBin(2));
        float rangeIntegral5_e3 = h3_HCal_Ep->Integral(h3_HCal_Ep->FindFixBin(0.010), h3_HCal_Ep->FindFixBin(2));
        float rangeIntegral6_e3 = h3_HCal_Ep->Integral(h3_HCal_Ep->FindFixBin(0.008), h3_HCal_Ep->FindFixBin(2));
        float rangeIntegral7_e3 = h3_HCal_Ep->Integral(h3_HCal_Ep->FindFixBin(0.006), h3_HCal_Ep->FindFixBin(2));

        float totalIntegral_e4 = h4_HCal_Ep->Integral(h4_HCal_Ep->FindFixBin(0), h3_HCal_Ep->FindFixBin(2));
        
        float rangeIntegral1_e4 = h4_HCal_Ep->Integral(h4_HCal_Ep->FindFixBin(0.018), h4_HCal_Ep->FindFixBin(2));
        float rangeIntegral2_e4 = h4_HCal_Ep->Integral(h4_HCal_Ep->FindFixBin(0.016), h4_HCal_Ep->FindFixBin(2));
        float rangeIntegral3_e4 = h4_HCal_Ep->Integral(h4_HCal_Ep->FindFixBin(0.014), h4_HCal_Ep->FindFixBin(2));
        float rangeIntegral4_e4 = h4_HCal_Ep->Integral(h4_HCal_Ep->FindFixBin(0.012), h4_HCal_Ep->FindFixBin(2));
        float rangeIntegral5_e4 = h4_HCal_Ep->Integral(h4_HCal_Ep->FindFixBin(0.010), h4_HCal_Ep->FindFixBin(2));
        float rangeIntegral6_e4 = h4_HCal_Ep->Integral(h4_HCal_Ep->FindFixBin(0.008), h4_HCal_Ep->FindFixBin(2));
        float rangeIntegral7_e4 = h4_HCal_Ep->Integral(h4_HCal_Ep->FindFixBin(0.006), h4_HCal_Ep->FindFixBin(2));

        float eff1_e= rangeIntegral1_e/(totalIntegral_e); 
        float eff2_e= rangeIntegral2_e/(totalIntegral_e); 
        float eff3_e= rangeIntegral3_e/(totalIntegral_e); 
        float eff4_e= rangeIntegral4_e/(totalIntegral_e); 
        float eff5_e= rangeIntegral5_e/(totalIntegral_e); 
        float eff6_e= rangeIntegral6_e/(totalIntegral_e); 
        float eff7_e= rangeIntegral7_e/(totalIntegral_e); 
      /*  float eff8_e= rangeIntegral8_e/(totalIntegral_e); 
        float eff9_e= rangeIntegral9_e/(totalIntegral_e); 
        float eff10_e= rangeIntegral10_e/(totalIntegral_e); */

        float eff1_e2= rangeIntegral1_e2/(totalIntegral_e2); 
        float eff2_e2= rangeIntegral2_e2/(totalIntegral_e2); 
        float eff3_e2= rangeIntegral3_e2/(totalIntegral_e2); 
        float eff4_e2= rangeIntegral4_e2/(totalIntegral_e2); 
        float eff5_e2= rangeIntegral5_e2/(totalIntegral_e2); 
        float eff6_e2= rangeIntegral6_e2/(totalIntegral_e2); 
        float eff7_e2= rangeIntegral7_e2/(totalIntegral_e2); 

        float eff1_e3= rangeIntegral1_e3/(totalIntegral_e3); 
        float eff2_e3= rangeIntegral2_e3/(totalIntegral_e3); 
        float eff3_e3= rangeIntegral3_e3/(totalIntegral_e3); 
        float eff4_e3= rangeIntegral4_e3/(totalIntegral_e3); 
        float eff5_e3= rangeIntegral5_e3/(totalIntegral_e3); 
        float eff6_e3= rangeIntegral6_e3/(totalIntegral_e3); 
        float eff7_e3= rangeIntegral7_e3/(totalIntegral_e3); 

        float eff1_e4= rangeIntegral1_e4/(totalIntegral_e4); 
        float eff2_e4= rangeIntegral2_e4/(totalIntegral_e4); 
        float eff3_e4= rangeIntegral3_e4/(totalIntegral_e4); 
        float eff4_e4= rangeIntegral4_e4/(totalIntegral_e4); 
        float eff5_e4= rangeIntegral5_e4/(totalIntegral_e4); 
        float eff6_e4= rangeIntegral6_e4/(totalIntegral_e4); 
        float eff7_e4= rangeIntegral7_e4/(totalIntegral_e4); 

        cout <<"nbinsh1 (number of electrons h1): " << nbinsh1 << endl;
        cout <<"nbinsh2 (number of electrons h2): " << nbinsh2 << endl;
        cout <<"nbinsh3 (number of electrons h3): " << nbinsh3 << endl;
        cout <<"nbinsh3 (number of electrons h4): " << nbinsh3 << endl;


      //  cout <<"Total bins: " << nbintstotal << endl;

       cout <<"rangeIntegral1_e: " << rangeIntegral1_e << endl;
       cout <<"rangeIntegral2_e: " << rangeIntegral2_e << endl;    
       cout <<"rangeIntegral3_e: " << rangeIntegral3_e << endl;
       cout <<"rangeIntegral4_e: " << rangeIntegral4_e << endl;
       cout <<"rangeIntegral5_e: " << rangeIntegral5_e << endl;
       cout <<"rangeIntegral6_e: " << rangeIntegral6_e << endl;
       cout <<"rangeIntegral7_e: " << rangeIntegral7_e << endl;
    /*   cout <<"rangeIntegral8_e: " << rangeIntegral8_e << endl;
       cout <<"rangeIntegral9_e: " << rangeIntegral9_e << endl;
       cout <<"rangeIntegral10_e: " << rangeIntegral10_e << endl;*/

       cout <<"efficiency1_e: " << eff1_e << endl;
       cout <<"efficiency2_e: " << eff2_e << endl;
       cout <<"efficiency3_e: " << eff3_e << endl;
       cout <<"efficiency4_e: " << eff4_e << endl;
       cout <<"efficiency5_e: " << eff5_e << endl;
       cout <<"efficiency6_e: " << eff6_e << endl;
       cout <<"efficiency7_e: " << eff7_e << endl;

        // h1_HCal_Ep->Scale(1./(nbintstotal));
        // h2_HCal_Ep->Scale(1./(nbintstotal));
        //   h1_HCal_Ep->Scale(1./(h1_HCal_Ep)->Integral());
        //   h2_HCal_Ep->Scale(1./(h2_HCal_Ep)->Integral());

  TCanvas *c1 = new TCanvas("c12","HCal E/p");
  gStyle->SetOptStat(false);
  c1->SetRightMargin(0.1);
  c1->SetTopMargin(0.1);
  c1->SetFillColor(0);

    h1_HCal_Ep->SetTitle("0.5 - 1.0 GeV");
    h2_HCal_Ep->SetTitle("1.0 - 2.0 GeV");
    h3_HCal_Ep->SetTitle("2.0 - 5.0 GeV");
    h4_HCal_Ep->SetTitle("5.0 - 10.0 GeV");

    h1_HCal_Ep->Draw();
    h2_HCal_Ep->Draw("same");
    h3_HCal_Ep->Draw("same");
    h4_HCal_Ep->Draw("same");

  c1->BuildLegend();
  c1->SaveAs("Ep_pie.pdf");
   

TCanvas *c2 = new TCanvas("c5","HCal efficiency of #e^{-}",200,10,500,300);
  TGraph* gr1 = new TGraph();
  TGraph* gr2 = new TGraph();
  TGraph* gr3 = new TGraph();
  TGraph* gr4 = new TGraph();

  TMultiGraph *mg = new TMultiGraph();
      mg->SetTitle("e^{-} E_{min} vs efficiency;E_{min}; Efficiency");
      mg->GetXaxis()->SetLimits(0.001, 0.4);
      mg->GetXaxis()->SetTitleOffset(1.2);
      mg->GetYaxis()->SetTitleOffset(1.2);
      mg->GetXaxis()->CenterTitle();
      mg->GetYaxis()->CenterTitle();      

    mg->Add(gr1,"lp");
    mg->Add(gr2,"cp");
    mg->Add(gr3,"cp");
    mg->Add(gr4,"cp");
    mg->Draw("AC");
   
   gr1->SetName("gr1");
   gr1->SetTitle("0.5 - 1.0 GeV");
   gr1->SetMarkerStyle(21);
   gr1->SetLineColor(1);
   gr1->SetLineWidth(4);
   gr1->SetFillStyle(0);
 
   gr2->SetName("gr2");
   gr2->SetTitle("1.0 - 2.0 GeV");
   gr2->SetMarkerStyle(22);
   gr2->SetMarkerColor(41);
   gr2->SetLineColor(41);
   gr2->SetLineWidth(4);
   gr2->SetFillStyle(0);

   gr3->SetName("gr3");
   gr3->SetTitle("2.0 - 5.0 GeV");
   gr3->SetMarkerStyle(23);
   gr3->SetMarkerColor(46);
   gr3->SetLineColor(46);
   gr3->SetLineWidth(4);
   gr3->SetFillStyle(0);

   gr4->SetName("gr3");
   gr4->SetTitle("5.0 - 10.0 GeV");
   gr4->SetMarkerStyle(23);
   gr4->SetMarkerColor(49);
   gr4->SetLineColor(49);
   gr4->SetLineWidth(4);
   gr4->SetFillStyle(0);


//  gr1->SetPoint(1,0.1,eff10_e);
//  gr1->SetPoint(2,0.2,eff9_e);
//  gr1->SetPoint(3,0.3,eff8_e);
  gr1->SetPoint(4,0.05,eff7_e);
  gr1->SetPoint(5,0.10,eff6_e); 
  gr1->SetPoint(6,0.15,eff5_e);
  gr1->SetPoint(7,0.20,eff4_e);
  gr1->SetPoint(8,0.25,eff3_e);
  gr1->SetPoint(9,0.30,eff2_e);
  gr1->SetPoint(10,0.35,eff1_e);

  gr2->SetPoint(4,0.05,eff7_e2);
  gr2->SetPoint(5,0.10,eff6_e2); 
  gr2->SetPoint(6,0.15,eff5_e2);
  gr2->SetPoint(7,0.20,eff4_e2);
  gr2->SetPoint(8,0.25,eff3_e2);
  gr2->SetPoint(9,0.30,eff2_e2);
  gr2->SetPoint(10,0.35,eff1_e2);

  gr3->SetPoint(4,0.05,eff7_e3);
  gr3->SetPoint(5,0.10,eff6_e3); 
  gr3->SetPoint(6,0.15,eff5_e3);
  gr3->SetPoint(7,0.20,eff4_e3);
  gr3->SetPoint(8,0.25,eff3_e3);
  gr3->SetPoint(9,0.30,eff2_e3);
  gr3->SetPoint(10,0.35,eff1_e3);

  gr4->SetPoint(4,0.05,eff7_e4);
  gr4->SetPoint(5,0.10,eff6_e4); 
  gr4->SetPoint(6,0.15,eff5_e4);
  gr4->SetPoint(7,0.20,eff4_e4);
  gr4->SetPoint(8,0.25,eff3_e4);
  gr4->SetPoint(9,0.30,eff2_e4);
  gr4->SetPoint(10,0.35,eff1_e4);

  c2->BuildLegend();

  // c2->SetRightMargin(0.0465116);
  // c2->SetTopMargin(0.1);
  // c2->SetFillColor(0);
  c2->SaveAs("effHCal.GeV.pdf");

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  cout<<"End of the program. Gracias"<<endl;
  return 0;  
}

