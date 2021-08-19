#pragma once
#if ROOT_VERSION_CODE >= ROOT_VERSION(6,00,0)
#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllDstInputManager.h>

#include </home/luis/software/nuclearexp/EIC/clean/macros/src/install/include/caldata/CalData.h>

R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(/home/luis/software/nuclearexp/EIC/clean/macros/src/install/lib/libcaldata.so)
#endif

//void Fun4All_CaloAna(const char *fname = "/home/luis/software/nuclearexp/data/ep_18x100lowq2/DST_SIDIS_pythia6_ep_18x100lowq2_0.root")

 char fname[100];
 //char fileList[100];


void Fun4All_CaloAna()
{

/*
for (Int_t nf = 0; nf <2; nf++){      // files name DST_SIDIS_pythia6_ep_18x100lowq2_#.root, from nf to nf++

       sprintf(fname,"/home/luis/software/nuclearexp/data/ep_18x100lowq2/DST_SIDIS_pythia6_ep_18x100lowq2_%d.root",nf);

        cout <<" Openning file " << fname << endl;
        TString inputFile=fname;
*/

  //  TFile fileInput(inputFile.Data());
  //  if (fileInput.IsZombie()) continue;


  gSystem->Load("libg4dst");
 // gSystem->Load("libcaloana");
  Fun4AllServer *se = Fun4AllServer::instance();
  
  ////////////CalData////////////////////////////////////////////////////////////
  CalData *calData = new CalData("calData","DISepcalData.root");
  calData->setMinJetPt(3.);
  calData->Verbosity(0);
  calData->analyzeTracks(true);
  calData->analyzeClusters(true);
  calData->analyzeJets(true);
  calData->analyzeTruth(false);
  se->registerSubsystem(calData);
  //////////////////////////////////////////////////////////////////////////////

  Fun4AllInputManager *in = new Fun4AllDstInputManager("DSTin");
 // in->fileopen(fname);
  in->AddListFile("fileList.txt");
  se->registerInputManager(in);
  se->run();
  se->End();


/*
  Fun4AllInputManager *hitsin = new Fun4AllDstInputManager("DSTin");
  hitsin->AddListFile("fileList_bs2jpsiphi.txt");
  se->registerInputManager(hitsin);
  */


/*
  Fun4AllInputManager *in = new Fun4AllDstInputManager("in");
  in->fileopen(fname);
  se->registerInputManager(in);
  se->run();
  se->End();
  */
}

//}
