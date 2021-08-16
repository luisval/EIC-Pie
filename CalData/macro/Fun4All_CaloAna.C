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

void Fun4All_CaloAna(const char *fname = "/home/luis/software/nuclearexp/EIC/clean/macros/detectors/EICDetector/DST_SIDIS_pythia6_ep_18x100lowq2_004_1518000_02000.root")
{
  gSystem->Load("libg4dst");
  gSystem->Load("libcaloana");
  Fun4AllServer *se = Fun4AllServer::instance();

  ////////////CalData////////////////////////////////////////////////////////////
  CalData *calData = new CalData("calData","calData.root");
  calData->setMinJetPt(3.);
  calData->Verbosity(0);
  calData->analyzeTracks(true);
  calData->analyzeClusters(true);
  calData->analyzeJets(true);
  calData->analyzeTruth(false);
  se->registerSubsystem(calData);
  //////////////////////////////////////////////////////////////////////////////

  Fun4AllInputManager *in = new Fun4AllDstInputManager("in");
  in->fileopen(fname);
  se->registerInputManager(in);
  se->run();
  se->End();
}
