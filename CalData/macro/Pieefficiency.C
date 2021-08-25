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

TFile *file1 = TFile::Open("G4EICDetector_out_hp_e_1_20GeV.root");
TFile *file2 = TFile::Open("G4EICDetector_out_hp_pi_1_20GeV.root");
TFile *file3 = TFile::Open("G4EICDetector_out_hp_k_1_20GeV.root");


       if (file1 && file2 && file3->IsZombie()) { cout << "Error opening a file" << endl;
       exit(-1);} 
       else {cout << "Files are okay" << endl;}
 
//  gStyle->SetOptTitle(0); //No title for histograms
 // gStyle->SetOptStat(0);
  
  TH1F *h1_EMCal_Ep = (TH1F*)file1->Get("h_EMCal_Ep");
        h1_EMCal_Ep->GetXaxis()->SetTitle("EMCal E/p");
        h1_EMCal_Ep->GetYaxis()->SetTitle("Counts");
        h1_EMCal_Ep->SetFillColor(0); 
        h1_EMCal_Ep->SetLineColor(1);
        h1_EMCal_Ep->SetLineWidth(6);  

  TH1F *h2_EMCal_Ep = (TH1F*)file2->Get("h_EMCal_Ep");
        h2_EMCal_Ep->GetXaxis()->SetTitle("EMCal E/p");
        h2_EMCal_Ep->GetYaxis()->SetTitle("Counts");
        h2_EMCal_Ep->SetFillColor(0); 
        h2_EMCal_Ep->SetLineColor(41);
        h2_EMCal_Ep->SetLineWidth(6);  

  TH1F *h3_EMCal_Ep = (TH1F*)file3->Get("h_EMCal_Ep");
        h3_EMCal_Ep->GetXaxis()->SetTitle("EMCal E/p");
        h3_EMCal_Ep->GetYaxis()->SetTitle("Counts");
        h3_EMCal_Ep->SetFillColor(0);    
        h3_EMCal_Ep->SetLineColor(46);
        h3_EMCal_Ep->SetLineWidth(6);  
   
     
        Int_t nbinsh1 = h1_EMCal_Ep->Integral();
        Int_t nbinsh2 = h2_EMCal_Ep->Integral();
        Int_t nbinsh3 = h3_EMCal_Ep->Integral();

        Int_t nbintstotal = nbinsh1+nbinsh2+nbinsh3;

      //h1_EMCal_Ep->Scale(1./(h1_EMCal_Ep)->Integral());
     // h2_EMCal_Ep->Scale(1./(h2_EMCal_Ep)->Integral());
     // h3_EMCal_Ep->Scale(1./(h3_EMCal_Ep)->Integral());


        float totalIntegral_e = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(0), h1_EMCal_Ep->FindFixBin(2));
        
        float rangeIntegral1_e = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(1), h1_EMCal_Ep->FindFixBin(2));
        float rangeIntegral2_e = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(0.9), h1_EMCal_Ep->FindFixBin(2));
        float rangeIntegral3_e = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(0.8), h1_EMCal_Ep->FindFixBin(2));
        float rangeIntegral4_e = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(0.7), h1_EMCal_Ep->FindFixBin(2));
        float rangeIntegral5_e = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(0.6), h1_EMCal_Ep->FindFixBin(2));
        float rangeIntegral6_e = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(0.5), h1_EMCal_Ep->FindFixBin(2));
        float rangeIntegral7_e = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(0.4), h1_EMCal_Ep->FindFixBin(2));
        float rangeIntegral8_e = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(0.3), h1_EMCal_Ep->FindFixBin(2));
        float rangeIntegral9_e = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(0.2), h1_EMCal_Ep->FindFixBin(2));
        float rangeIntegral10_e = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(0.1), h1_EMCal_Ep->FindFixBin(2));


        float totalIntegral_pi = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(0), h2_EMCal_Ep->FindFixBin(2));
        
        float rangeIntegral1_pi = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(1), h2_EMCal_Ep->FindFixBin(2));
        float rangeIntegral2_pi = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(0.9), h2_EMCal_Ep->FindFixBin(2));
        float rangeIntegral3_pi = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(0.8), h2_EMCal_Ep->FindFixBin(2));
        float rangeIntegral4_pi = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(0.7), h2_EMCal_Ep->FindFixBin(2));
        float rangeIntegral5_pi = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(0.6), h2_EMCal_Ep->FindFixBin(2));
        float rangeIntegral6_pi = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(0.5), h2_EMCal_Ep->FindFixBin(2));
        float rangeIntegral7_pi = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(0.4), h2_EMCal_Ep->FindFixBin(2));
        float rangeIntegral8_pi = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(0.3), h2_EMCal_Ep->FindFixBin(2));
        float rangeIntegral9_pi = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(0.2), h2_EMCal_Ep->FindFixBin(2));
        float rangeIntegral10_pi = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(0.1), h2_EMCal_Ep->FindFixBin(2));


        float totalIntegral_k = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(0), h3_EMCal_Ep->FindFixBin(2));
        
        float rangeIntegral1_k = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(1), h3_EMCal_Ep->FindFixBin(2));
        float rangeIntegral2_k = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(0.9), h3_EMCal_Ep->FindFixBin(2));
        float rangeIntegral3_k = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(0.8), h3_EMCal_Ep->FindFixBin(2));
        float rangeIntegral4_k = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(0.7), h3_EMCal_Ep->FindFixBin(2));
        float rangeIntegral5_k = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(0.6), h3_EMCal_Ep->FindFixBin(2));
        float rangeIntegral6_k = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(0.5), h3_EMCal_Ep->FindFixBin(2));
        float rangeIntegral7_k = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(0.4), h3_EMCal_Ep->FindFixBin(2));
        float rangeIntegral8_k = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(0.3), h3_EMCal_Ep->FindFixBin(2));
        float rangeIntegral9_k = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(0.2), h3_EMCal_Ep->FindFixBin(2));
        float rangeIntegral10_k = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(0.1), h3_EMCal_Ep->FindFixBin(2));

        float eff1_e= rangeIntegral1_e/(totalIntegral_e); 
        float eff2_e= rangeIntegral2_e/(totalIntegral_e); 
        float eff3_e= rangeIntegral3_e/(totalIntegral_e); 
        float eff4_e= rangeIntegral4_e/(totalIntegral_e); 
        float eff5_e= rangeIntegral5_e/(totalIntegral_e); 
        float eff6_e= rangeIntegral6_e/(totalIntegral_e); 
        float eff7_e= rangeIntegral7_e/(totalIntegral_e); 
        float eff8_e= rangeIntegral8_e/(totalIntegral_e); 
        float eff9_e= rangeIntegral9_e/(totalIntegral_e); 
        float eff10_e= rangeIntegral10_e/(totalIntegral_e); 

        float eff1_pi= rangeIntegral1_pi/(totalIntegral_pi); 
        float eff2_pi= rangeIntegral2_pi/(totalIntegral_pi); 
        float eff3_pi= rangeIntegral3_pi/(totalIntegral_pi); 
        float eff4_pi= rangeIntegral4_pi/(totalIntegral_pi); 
        float eff5_pi= rangeIntegral5_pi/(totalIntegral_pi); 
        float eff6_pi= rangeIntegral6_pi/(totalIntegral_pi); 
        float eff7_pi= rangeIntegral7_pi/(totalIntegral_pi); 
        float eff8_pi= rangeIntegral8_pi/(totalIntegral_pi); 
        float eff9_pi= rangeIntegral9_pi/(totalIntegral_pi); 
        float eff10_pi= rangeIntegral10_pi/(totalIntegral_pi); 

        float eff1_k= rangeIntegral1_k/(totalIntegral_k); 
        float eff2_k= rangeIntegral2_k/(totalIntegral_k); 
        float eff3_k= rangeIntegral3_k/(totalIntegral_k); 
        float eff4_k= rangeIntegral4_k/(totalIntegral_k); 
        float eff5_k= rangeIntegral5_k/(totalIntegral_k); 
        float eff6_k= rangeIntegral6_k/(totalIntegral_k); 
        float eff7_k= rangeIntegral7_k/(totalIntegral_k); 
        float eff8_k= rangeIntegral8_k/(totalIntegral_k); 
        float eff9_k= rangeIntegral9_k/(totalIntegral_k); 
        float eff10_k= rangeIntegral10_k/(totalIntegral_k); 



        cout <<"nbinsh1 (number of electrons): " << nbinsh1 << endl;
        cout <<"nbinsh2 (number of pions): " << nbinsh2 << endl;
        cout <<"nbinsh3 (number of kaons): " << nbinsh3 << endl;

        cout <<"Total bins: " << nbintstotal << endl;

       cout <<"rangeIntegral1_e: " << rangeIntegral1_e << endl;
       cout <<"rangeIntegral2_e: " << rangeIntegral2_e << endl;    
       cout <<"rangeIntegral3_e: " << rangeIntegral3_e << endl;
       cout <<"rangeIntegral4_e: " << rangeIntegral4_e << endl;
       cout <<"rangeIntegral5_e: " << rangeIntegral5_e << endl;
       cout <<"rangeIntegral6_e: " << rangeIntegral6_e << endl;
       cout <<"rangeIntegral7_e: " << rangeIntegral7_e << endl;
       cout <<"rangeIntegral8_e: " << rangeIntegral8_e << endl;
       cout <<"rangeIntegral9_e: " << rangeIntegral9_e << endl;
       cout <<"rangeIntegral10_e: " << rangeIntegral10_e << endl;

       cout <<"rangeIntegral1_pi: " << rangeIntegral1_pi << endl;
       cout <<"rangeIntegral2_pi: " << rangeIntegral2_pi << endl;    
       cout <<"rangeIntegral3_pi: " << rangeIntegral3_pi << endl;
       cout <<"rangeIntegral4_pi: " << rangeIntegral4_pi << endl;
       cout <<"rangeIntegral5_pi: " << rangeIntegral5_pi << endl;       

       cout <<"efficiency1_e: " << eff1_e << endl;
       cout <<"efficiency2_e: " << eff2_e << endl;
       cout <<"efficiency3_e: " << eff3_e << endl;
       cout <<"efficiency4_e: " << eff4_e << endl;
       cout <<"efficiency5_e: " << eff5_e << endl;
       cout <<"efficiency6_e: " << eff6_e << endl;
       cout <<"efficiency7_e: " << eff7_e << endl;
       cout <<"efficiency8_e: " << eff8_e << endl;
       cout <<"efficiency9_e: " << eff9_e << endl;
       cout <<"efficiency10_e: " << eff10_e << endl;

        // h1_EMCal_Ep->Scale(1./(nbintstotal));
        // h2_EMCal_Ep->Scale(1./(nbintstotal));
        //   h1_EMCal_Ep->Scale(1./(h1_EMCal_Ep)->Integral());
        //   h2_EMCal_Ep->Scale(1./(h2_EMCal_Ep)->Integral());

  TCanvas *c1 = new TCanvas("c12","EMCal E/p");
  gStyle->SetOptStat(false);
  c1->SetRightMargin(0.1);
  c1->SetTopMargin(0.1);
  c1->SetFillColor(0);

    h1_EMCal_Ep->SetTitle(" e^{-}");
    h2_EMCal_Ep->SetTitle("#pi^{-}");
    h3_EMCal_Ep->SetTitle("k^{-}");
   
    h1_EMCal_Ep->Draw();
    h2_EMCal_Ep->Draw("same");
    h3_EMCal_Ep->Draw("same");

  c1->BuildLegend();
  c1->SaveAs("Ep_pie.pdf");
   

TCanvas *c2 = new TCanvas("c5","Efficiency of #e^{-},  #pi^{-}, and #k^{-} ",200,10,500,300);
  TGraph* gr1 = new TGraph();
  TGraph* gr2 = new TGraph();
  TGraph* gr3 = new TGraph();


  TMultiGraph *mg = new TMultiGraph();
      mg->SetTitle("E/p vs efficiency;(E/p)_{min}; Efficiency");
      mg->GetXaxis()->SetLimits(0.1, 1.02);
      mg->GetXaxis()->SetTitleOffset(1.2);
      mg->GetYaxis()->SetTitleOffset(1.2);
      mg->GetXaxis()->CenterTitle();
      mg->GetYaxis()->CenterTitle();      

    mg->Add(gr1,"lp");
    mg->Add(gr2,"cp");
    mg->Add(gr3,"cp");
    mg->Draw("AC");
 
  
   gr1->SetName("gr1");
   gr1->SetTitle("e^{-}");
   gr1->SetMarkerStyle(21);
  // gr1->SetDrawOption("AP");
   gr1->SetLineColor(1);
   gr1->SetLineWidth(4);
   gr1->SetFillStyle(0);
 
   gr2->SetName("gr2");
   gr2->SetTitle("#pi^{-}");
   gr2->SetMarkerStyle(22);
   gr2->SetMarkerColor(41);
 //  gr2->SetDrawOption("P");
   gr2->SetLineColor(41);
   gr2->SetLineWidth(4);
   gr2->SetFillStyle(0);

   gr3->SetName("gr3");
   gr3->SetTitle("k^{-}");
   gr3->SetMarkerStyle(23);
   gr3->SetMarkerColor(46);
  // gr3->SetDrawOption("P");
   gr3->SetLineColor(46);
   gr3->SetLineWidth(4);
   gr3->SetFillStyle(0);


  gr1->SetPoint(1,0.1,eff10_e);
  gr1->SetPoint(2,0.2,eff9_e);
  gr1->SetPoint(3,0.3,eff8_e);
  gr1->SetPoint(4,0.4,eff7_e);
  gr1->SetPoint(5,0.5,eff6_e); 
  gr1->SetPoint(6,0.6,eff5_e);
  gr1->SetPoint(7,0.7,eff4_e);
  gr1->SetPoint(8,0.8,eff3_e);
  gr1->SetPoint(9,0.9,eff2_e);
  gr1->SetPoint(10,1.0,eff1_e);

  gr2->SetPoint(1,0.1,eff10_pi);
  gr2->SetPoint(2,0.2,eff9_pi);
  gr2->SetPoint(3,0.3,eff8_pi);
  gr2->SetPoint(4,0.4,eff7_pi);
  gr2->SetPoint(5,0.5,eff6_pi); 
  gr2->SetPoint(6,0.6,eff5_pi);
  gr2->SetPoint(7,0.7,eff4_pi);
  gr2->SetPoint(8,0.8,eff3_pi);
  gr2->SetPoint(9,0.9,eff2_pi);
  gr2->SetPoint(10,1.0,eff1_pi);

  gr3->SetPoint(1,0.1,eff10_k);
  gr3->SetPoint(2,0.2,eff9_k);
  gr3->SetPoint(3,0.3,eff8_k);
  gr3->SetPoint(4,0.4,eff7_k);
  gr3->SetPoint(5,0.5,eff6_k); 
  gr3->SetPoint(6,0.6,eff5_k);
  gr3->SetPoint(7,0.7,eff4_k);
  gr3->SetPoint(8,0.8,eff3_k);
  gr3->SetPoint(9,0.9,eff2_k);
  gr3->SetPoint(10,1.0,eff1_k);


  c2->BuildLegend();

  // c2->SetRightMargin(0.0465116);
  // c2->SetTopMargin(0.1);
  // c2->SetFillColor(0);
  c2->SaveAs("Ep_eff.gif");


 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  cout<<"End of the program. Gracias"<<endl;
  return 0;  
}

