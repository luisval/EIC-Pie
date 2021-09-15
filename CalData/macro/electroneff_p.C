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

Int_t electroneff_p()
{

//Electrons
TFile *file1 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_e_0.5-1.0GeV.root");
TFile *file2 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_e_1-2GeV.root");
TFile *file3 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_e_2-5GeV.root");
TFile *file4 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_e_5-10GeV.root");

TFile *file12 = TFile::Open("revisited_G4EICDetector_out_hq2_e_0.5-1.0GeV.root");
TFile *file22 = TFile::Open("revisited_G4EICDetector_out_hq2_e_1-2GeV.root");
TFile *file32 = TFile::Open("revisited_G4EICDetector_out_hq2_e_2-5GeV.root");
TFile *file42 = TFile::Open("revisited_G4EICDetector_out_hq2_e_5-10GeV.root");

//Pions
/*TFile *file1 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_pi_0.5-1.0GeV.root");
TFile *file2 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_pi_1-2GeV.root");
TFile *file3 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_pi_2-5GeV.root");
TFile *file4 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_pi_5-10GeV.root"); */

//Kaons

/*
TFile *file1 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_k_0.5-1.0GeV.root");
TFile *file2 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_k_1-2GeV.root");
TFile *file3 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_k_2-5GeV.root");
TFile *file4 = TFile::Open("Ep_cut_revisited_G4EICDetector_out_hq2_k_5-10GeV.root");
*/

       if (file1 && file2 && file3 && file4->IsZombie()) { cout << "Error opening a file" << endl;
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
   
  TH1F *h4_EMCal_Ep = (TH1F*)file4->Get("h_EMCal_Ep");
        h4_EMCal_Ep->GetXaxis()->SetTitle("EMCal E/p");
        h4_EMCal_Ep->GetYaxis()->SetTitle("Counts");
        h4_EMCal_Ep->SetFillColor(0);    
        h4_EMCal_Ep->SetLineColor(49);
        h4_EMCal_Ep->SetLineWidth(6);  

///////////////////////////////////////////////////////////////
 TH1F *h1_EMCal_Ep_tot = (TH1F*)file12->Get("h_EMCal_Ep");
        h1_EMCal_Ep_tot->GetXaxis()->SetTitle("EMCal E/p");
        h1_EMCal_Ep_tot->GetYaxis()->SetTitle("Counts");
        h1_EMCal_Ep_tot->SetFillColor(0); 
        h1_EMCal_Ep_tot->SetLineColor(1);
        h1_EMCal_Ep_tot->SetLineWidth(6);  

  TH1F *h2_EMCal_Ep_tot = (TH1F*)file22->Get("h_EMCal_Ep");
        h2_EMCal_Ep_tot->GetXaxis()->SetTitle("EMCal E/p");
        h2_EMCal_Ep_tot->GetYaxis()->SetTitle("Counts");
        h2_EMCal_Ep_tot->SetFillColor(0); 
        h2_EMCal_Ep_tot->SetLineColor(41);
        h2_EMCal_Ep_tot->SetLineWidth(6);  

  TH1F *h3_EMCal_Ep_tot = (TH1F*)file32->Get("h_EMCal_Ep");
        h3_EMCal_Ep_tot->GetXaxis()->SetTitle("EMCal E/p");
        h3_EMCal_Ep_tot->GetYaxis()->SetTitle("Counts");
        h3_EMCal_Ep_tot->SetFillColor(0);    
        h3_EMCal_Ep_tot->SetLineColor(46);
        h3_EMCal_Ep_tot->SetLineWidth(6);  
   
  TH1F *h4_EMCal_Ep_tot = (TH1F*)file42->Get("h_EMCal_Ep");
        h4_EMCal_Ep_tot->GetXaxis()->SetTitle("EMCal E/p");
        h4_EMCal_Ep_tot->GetYaxis()->SetTitle("Counts");
        h4_EMCal_Ep_tot->SetFillColor(0);    
        h4_EMCal_Ep_tot->SetLineColor(49);
        h4_EMCal_Ep_tot->SetLineWidth(6);  
            
     
        Int_t nbinsh1 = h1_EMCal_Ep->Integral();
        Int_t nbinsh2 = h2_EMCal_Ep->Integral();
        Int_t nbinsh3 = h3_EMCal_Ep->Integral();
        Int_t nbinsh4 = h3_EMCal_Ep->Integral();

        Int_t nbintstotal = nbinsh1+nbinsh2+nbinsh3+nbinsh4;

        float totalIntegral1 = h1_EMCal_Ep_tot->Integral(h1_EMCal_Ep_tot->FindFixBin(0), h1_EMCal_Ep_tot->FindFixBin(2));    
        float rangeIntegral1 = h1_EMCal_Ep->Integral(h1_EMCal_Ep->FindFixBin(0), h1_EMCal_Ep->FindFixBin(2)); 

        float totalIntegral2 = h2_EMCal_Ep_tot->Integral(h2_EMCal_Ep_tot->FindFixBin(0), h2_EMCal_Ep_tot->FindFixBin(2));       
        float rangeIntegral2 = h2_EMCal_Ep->Integral(h2_EMCal_Ep->FindFixBin(0), h2_EMCal_Ep->FindFixBin(2));

        float totalIntegral3 = h3_EMCal_Ep_tot->Integral(h3_EMCal_Ep_tot->FindFixBin(0), h3_EMCal_Ep_tot->FindFixBin(2));
        float rangeIntegral3 = h3_EMCal_Ep->Integral(h3_EMCal_Ep->FindFixBin(0), h3_EMCal_Ep->FindFixBin(2));

        float totalIntegral4 = h4_EMCal_Ep_tot->Integral(h4_EMCal_Ep_tot->FindFixBin(0), h3_EMCal_Ep_tot->FindFixBin(2));
        float rangeIntegral4 = h4_EMCal_Ep->Integral(h4_EMCal_Ep->FindFixBin(0), h4_EMCal_Ep->FindFixBin(2));

        float eff1= rangeIntegral1/(totalIntegral1); 
        float eff2= rangeIntegral2/(totalIntegral2); 
        float eff3= rangeIntegral3/(totalIntegral3); 
        float eff4= rangeIntegral4/(totalIntegral4); 

      //  cout <<"nbinsh1 (number of electrons): " << nbinsh1 << endl;
      //  cout <<"nbinsh2 (number of pions): " << nbinsh2 << endl;
     //   cout <<"nbinsh3 (number of kaons): " << nbinsh3 << endl;

        cout <<"Total bins: " << nbintstotal << endl;

       cout <<"rangeIntegral1: " << rangeIntegral1 << endl;
       cout <<"rangeIntegral2: " << rangeIntegral2 << endl;    
       cout <<"rangeIntegral3: " << rangeIntegral3 << endl;
       cout <<"rangeIntegral4: " << rangeIntegral4 << endl;

       cout <<"efficiency1: " << eff1 << endl;
       cout <<"efficiency2: " << eff2 << endl;
       cout <<"efficiency3: " << eff3 << endl;
       cout <<"efficiency4: " << eff4 << endl;


  TCanvas *c1 = new TCanvas("c12","EMCal E/p");
  gStyle->SetOptStat(false);
  c1->SetRightMargin(0.1);
  c1->SetTopMargin(0.1);
  c1->SetFillColor(0);

    h1_EMCal_Ep->SetTitle("0.5 - 1.0 GeV");
    h2_EMCal_Ep->SetTitle("1.0 - 2.0 GeV");
    h3_EMCal_Ep->SetTitle("2.0 - 5.0 GeV");
    h4_EMCal_Ep->SetTitle("5.0 - 10.0 GeV");

    h1_EMCal_Ep->Draw();
    h2_EMCal_Ep->Draw("same");
    h3_EMCal_Ep->Draw("same");
    h4_EMCal_Ep->Draw("same");

  c1->BuildLegend();
  c1->SaveAs("Ep_pie.pdf");
   

TCanvas *c2 = new TCanvas("c5","Efficiency of #e^{-},  #pi^{-}, and #k^{-} ",200,10,500,300);

TGraph *gr = new TGraph();
   gr->SetTitle("e^{-} p vs efficiency;p_max (GeV); Efficiency");
   gr->SetPoint(0,1.0,eff1);
   gr->SetPoint(1,2.0,eff2);
   gr->SetPoint(2,5.0,eff3);
   gr->SetPoint(3,10.0,eff4);
   gr->SetMarkerStyle(20);
   gr->Draw("AP");

  c2->BuildLegend();
  
  c2->SaveAs("eff-1.pdf");

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  cout<<"End of the program. Gracias"<<endl;
  return 0;  
}

