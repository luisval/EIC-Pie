//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////This macro is an adaptation of AnaTutorial ( https://github.com/ECCE-EIC/tutorials/tree/master/AnaTutorial)
//////created to save the root files with the EMCal and HCal information.
//////Framework Fun4All G4
//////2nd Author: Luis Val
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CalData.h"

/// Cluster/Calorimeter includes
#include <calobase/RawCluster.h>
#include <calobase/RawClusterContainer.h>
#include <calobase/RawClusterUtility.h>
#include <calobase/RawTower.h>
#include <calobase/RawTowerContainer.h>
#include <calobase/RawTowerGeom.h>
#include <calobase/RawTowerGeomContainer.h>
#include <calotrigger/CaloTriggerInfo.h>

/// Tracking includes
#include <g4vertex/GlobalVertex.h>
#include <g4vertex/GlobalVertexMap.h>
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
#include <trackbase_historic/SvtxVertex.h>
#include <trackbase_historic/SvtxVertexMap.h>


/// Truth evaluation includes
#include <g4eval/SvtxEvalStack.h>

/// HEPMC truth includes
#include <HepMC/GenEvent.h>
#include <HepMC/GenVertex.h>
#include <phhepmc/PHHepMCGenEvent.h>
#include <phhepmc/PHHepMCGenEventMap.h>

/// Fun4All includes
#include <fun4all/Fun4AllHistoManager.h>
#include <fun4all/Fun4AllReturnCodes.h>
#include <g4main/PHG4Hit.h>
#include <g4main/PHG4Particle.h>
#include <g4main/PHG4TruthInfoContainer.h>
#include <phool/PHCompositeNode.h>
#include <phool/getClass.h>
#include <g4main/PHG4HitContainer.h>

/// ROOT includes
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TNtuple.h>
#include <TTree.h>

/// C++ includes
#include <cassert>
#include <sstream>
#include <string>

using namespace std;

/**
 * This class demonstrates the construction and use of an analysis module 
 * within the sPHENIX Fun4All framework. It is intended to show how to 
 * obtain physics objects from the analysis tree, and then write them out
 * to a ROOT tree and file for further offline analysis.  
 */

/**
 * Constructor of module
 */
CalData::CalData(const std::string &name, const std::string &filename)
  : SubsysReco(name)
  , m_outfilename(filename)
  , m_hm(nullptr)
  , m_mincluspt(0.25)
  , m_analyzeTracks(true)
  , m_analyzeClusters(true)
  , m_analyzeTruth(false)
{
  /// Initialize variables and trees so we don't accidentally access 
  /// memory that was never allocated
  initializeVariables();
  initializeTrees();
}

/**
 * Destructor of module
 */
CalData::~CalData()
{
  delete m_hm;
  delete m_hepmctree;
  delete m_tracktree;
}

/**
 * Initialize the module and prepare looping over events
 */
int CalData::Init(PHCompositeNode *topNode)
{
  if (Verbosity() > 5)
  {
    cout << "Beginning Init in CalData" << endl;
  }
 
  m_outfile = new TFile(m_outfilename.c_str(), "RECREATE");

  m_phi_h = new TH1D("phi_h", ";Counts;#phi [rad]", 50, -6, 6);
  m_eta_phi_h = new TH2F("phi_eta_h", ";#eta;#phi [rad]", 10, -1, 1, 50, -6, 6);

  return 0;
}

/**
 * Main workhorse function where each event is looped over and 
 * data from each event is collected from the node tree for analysis
 */
int CalData::process_event(PHCompositeNode *topNode)
{
  if (Verbosity() > 5)
  {
    cout << "Beginning process_event in CalData" << endl;
  }
  /// Get the truth information
  if (m_analyzeTruth)
  {
    getHEPMCTruth(topNode);
    getPHG4Truth(topNode);
  }

  /// Get the tracks
  if (m_analyzeTracks)
  {
    getTracks(topNode);
  }
  
  /// Get calorimeter information
  if (m_analyzeClusters)
  {
    getEMCalClusters(topNode);
  }

  return Fun4AllReturnCodes::EVENT_OK;
}

/**
 * End the module and finish any data collection. Clean up any remaining
 * loose ends
 */
int CalData::End(PHCompositeNode *topNode)
{
  if (Verbosity() > 1)
  {
    cout << "Ending CalData analysis package" << endl;
  }
  
  /// Change to the outfile
  m_outfile->cd();

  /// If we analyzed the tracks, write the tree out
  if (m_analyzeTracks)
    m_tracktree->Write();

  /// If we analyzed the truth particles, write them out
  if (m_analyzeTruth)
  {
    m_hepmctree->Write();
    m_truthtree->Write();
  }

  /// If we analyzed the clusters, write them out
  if (m_analyzeClusters)
  {
    m_clustertree->Write();
  }

  /// Write out any other histograms
  m_phi_h->Write();
  m_eta_phi_h->Write();
  
  /// Write and close the outfile
  m_outfile->Write();
  m_outfile->Close();

  /// Clean up pointers and associated histos/trees in TFile
  delete m_outfile;

  if (Verbosity() > 1)
  {
    cout << "Finished CalData analysis package" << endl;
  }

  return 0;
}

/**
 * This method gets all of the HEPMC truth particles from the node tree
 * and stores them in a ROOT TTree. The HEPMC truth particles are what, 
 * for example, directly comes out of PYTHIA and thus gives you all of
 * the associated parton information
 */
void CalData::getHEPMCTruth(PHCompositeNode *topNode)
{
  /// Get the node from the node tree
  PHHepMCGenEventMap *hepmceventmap = findNode::getClass<PHHepMCGenEventMap>(topNode, "PHHepMCGenEventMap");

  /// If the node was not properly put on the tree, return
  if (!hepmceventmap)
  {
    cout << PHWHERE
         << "HEPMC event map node is missing, can't collected HEPMC truth particles"
         << endl;
    return;
  }

  /// Could have some print statements for debugging with verbosity
  if (Verbosity() > 1)
  {
    cout << "Getting HEPMC truth particles " << endl;
  }

  /// You can iterate over the number of events in a hepmc event
  /// for pile up events where you have multiple hard scatterings per bunch crossing
  for (PHHepMCGenEventMap::ConstIter eventIter = hepmceventmap->begin();
       eventIter != hepmceventmap->end();
       ++eventIter)
  {
    /// Get the event
    PHHepMCGenEvent *hepmcevent = eventIter->second;

    if (hepmcevent)
    {
      /// Get the event characteristics, inherited from HepMC classes
      HepMC::GenEvent *truthevent = hepmcevent->getEvent();
      if (!truthevent)
      {
        cout << PHWHERE
             << "no evt pointer under phhepmvgeneventmap found "
             << endl;
        return;
      }

      /// Get the parton info
      HepMC::PdfInfo *pdfinfo = truthevent->pdf_info();

      /// Get the parton info as determined from HEPMC
      m_partid1 = pdfinfo->id1();
      m_partid2 = pdfinfo->id2();
      m_x1 = pdfinfo->x1();
      m_x2 = pdfinfo->x2();

      /// Are there multiple partonic intercations in a p+p event
      m_mpi = truthevent->mpi();

      /// Get the PYTHIA signal process id identifying the 2-to-2 hard process
      m_process_id = truthevent->signal_process_id();

      if (Verbosity() > 2)
      {
        cout << " Iterating over an event" << endl;
      }
      /// Loop over all the truth particles and get their information
      for (HepMC::GenEvent::particle_const_iterator iter = truthevent->particles_begin();
           iter != truthevent->particles_end();
           ++iter)
      {
        /// Get each pythia particle characteristics
        //m_truthenergy = (*iter)->momentum().e();
        //m_truthpid = (*iter)->pdg_id();

        //m_trutheta = (*iter)->momentum().pseudoRapidity();
        //m_truthphi = (*iter)->momentum().phi();
        //m_truthpx = (*iter)->momentum().px();
        //m_truthpy = (*iter)->momentum().py();
        //m_truthpz = (*iter)->momentum().pz();
        //m_truthpt = sqrt(m_truthpx * m_truthpx + m_truthpy * m_truthpy);

        /// Fill the truth tree
        m_hepmctree->Fill();
        m_numparticlesinevent++;
      }
    }
  }
}

/**
 * This function collects the truth PHG4 stable particles that
 * are produced from PYTHIA, or some other event generator. These
 * are the stable particles, e.g. there are not any (for example)
 * partons here.
 */
void CalData::getPHG4Truth(PHCompositeNode *topNode)
{
  /// G4 truth particle node
/*  PHG4TruthInfoContainer *truthinfo = findNode::getClass<PHG4TruthInfoContainer>(topNode, "G4TruthInfo");

  if (!truthinfo)
  {
    cout << PHWHERE
         << "PHG4TruthInfoContainer node is missing, can't collect G4 truth particles"
         << endl;
    return;
  }

  /// Get the primary particle range
  PHG4TruthInfoContainer::Range range = truthinfo->GetPrimaryParticleRange();

  /// Loop over the G4 truth (stable) particles
  for (PHG4TruthInfoContainer::ConstIterator iter = range.first;
       iter != range.second;
       ++iter)
  {
    /// Get this truth particle
    const PHG4Particle *truth = iter->second;

    /// Get this particles momentum, etc.
    m_truthpx = truth->get_px();
    m_truthpy = truth->get_py();
    m_truthpz = truth->get_pz();
    m_truthp = sqrt(m_truthpx * m_truthpx + m_truthpy * m_truthpy + m_truthpz * m_truthpz);
    m_truthenergy = truth->get_e();

    m_truthpt = sqrt(m_truthpx * m_truthpx + m_truthpy * m_truthpy);

    m_truthphi = atan(m_truthpy / m_truthpx);

    m_trutheta = atanh(m_truthpz / m_truthenergy);
    /// Check for nans
    if (m_trutheta != m_trutheta)
      m_trutheta = -99;
    m_truthpid = truth->get_pid();

    /// Fill the g4 truth tree
    m_truthtree->Fill();
  }*/
}

/**
 * This method gets the tracks as reconstructed from the tracker. It also
 * compares the reconstructed track to its truth track counterpart as determined
 * by the 
 */
void CalData::getTracks(PHCompositeNode *topNode)
{
  /// SVTX tracks node
  //SvtxTrackMap *trackmap = findNode::getClass<SvtxTrackMap>(topNode, "SvtxTrackMap");
  m_tr_px.clear();
  m_tr_py.clear();
  m_tr_pz.clear();
  m_tr_p.clear();
  m_tr_pt.clear();
  m_tr_phi.clear();
  m_tr_eta.clear();
  m_charge.clear();
  m_chisq.clear();
  m_ndf.clear();
  m_dca.clear();
  m_tr_x.clear();
  m_tr_y.clear();
  m_tr_z.clear();
  m_truthpx.clear();
  m_truthpy.clear();
  m_truthpz.clear();
  m_truthp.clear();
  m_truthenergy.clear();
  m_truthpt.clear();
  m_truthphi.clear();
  m_trutheta.clear();
  m_truthpid.clear();

//EMCal
  m_clusenergy.clear();
  m_cluseta.clear();
  m_clustheta.clear();
  m_cluspt.clear();
  m_clusphi.clear();
  m_cluspx.clear();
  m_cluspy.clear();
  m_cluspz.clear();

  //HCal
m_clusenergy_HCal.clear(); 
m_cluseta_HCal.clear();
m_clusphi_HCal.clear(); 
m_cluspt_HCal.clear();

m_clusenergy_HCalOUT.clear(); 
m_cluseta_HCalOUT.clear();
m_clusphi_HCalOUT.clear(); 
m_cluspt_HCalOUT.clear();

/////////////////

  PHG4TruthInfoContainer *truthinfo = findNode::getClass<PHG4TruthInfoContainer>(topNode, "G4TruthInfo");
  PHG4TruthInfoContainer::Range range = truthinfo->GetPrimaryParticleRange();

  for (PHG4TruthInfoContainer::ConstIterator iter = range.first; iter != range.second; ++iter){

	const PHG4Particle *truth = iter->second;

	float px = truth->get_px();	
	float py = truth->get_py();
	float pz = truth->get_pz();
	float pe = truth->get_e();

	m_truthpx .push_back(truth->get_px());
  	m_truthpy .push_back(truth->get_py());
  	m_truthpz .push_back(truth->get_pz());
  	m_truthp  .push_back(sqrt(px * px + py * py + pz * pz));
  	m_truthenergy .push_back(truth->get_e());

  	m_truthpt .push_back(sqrt(px * px + py * py));

  	m_truthphi .push_back(atan(py / px));

  	m_trutheta .push_back(atanh(pz / pe));
  	if (m_trutheta != m_trutheta)
    		m_trutheta .push_back(-99);
  	m_truthpid .push_back(truth->get_pid());
 
 }
    
  SvtxTrackMap *trackmap = findNode::getClass<SvtxTrackMap>(topNode, "TrackMap");

  if (!trackmap){
     cout << PHWHERE
          << "SvtxTrackMap node is missing, can't collect tracks"
          << endl;
     return;
   }

  if(trackmap) cout << "trackmap size" << trackmap->size() << endl;

  /// EvalStack for truth track matching
  if(!m_svtxEvalStack)
    {
      m_svtxEvalStack = new SvtxEvalStack(topNode);
      m_svtxEvalStack->set_verbosity(Verbosity());
    }
  
  m_svtxEvalStack->next_event(topNode);

  /// Get the track evaluator
  //SvtxTrackEval *trackeval = m_svtxEvalStack->get_track_eval();

  /// Get the range for primary tracks
  //PHG4TruthInfoContainer *truthinfo = findNode::getClass<PHG4TruthInfoContainer>(topNode, "G4TruthInfo");

  if (Verbosity() > 1)
  {
    cout << "Get the SVTX tracks" << endl;
  }
  for (SvtxTrackMap::Iter iter = trackmap->begin(); iter != trackmap->end(); ++iter){

    SvtxTrack *track = iter->second;
    
    if(track) cout << "track px " << track->get_px() << endl; 
    /*for (SvtxTrack::ConstStateIter trkstates = track->begin_states(); trkstates != track->end_states(); ++trkstates){
    	cout << __PRETTY_FUNCTION__ << " checking " << trkstates->second->get_name() << endl;
	map<string, unsigned int>::const_iterator iter = m_ProjectionNameMap.find(trkstates->second->get_name());
	if (iter != m_ProjectionNameMap.end()){
		cout << __PRETTY_FUNCTION__ << " found " << trkstates->second->get_name() << endl;
	}	
    }*/ 

    /// Get the reconstructed track info
    float px = track->get_px();
    float py = track->get_py();
    float pz = track->get_pz();	
    m_tr_px .push_back(track->get_px());
    m_tr_py .push_back(track->get_py());
    m_tr_pz .push_back(track->get_pz());
    m_tr_p  .push_back(sqrt(px * px + py * py + pz * pz));
    m_tr_pt .push_back(sqrt(px * px + py * py));

    m_tr_phi .push_back(track->get_phi());
    m_tr_eta .push_back(track->get_eta());

    m_charge .push_back(track->get_charge());
    m_chisq  .push_back(track->get_chisq());
    m_ndf    .push_back(track->get_ndf());
    m_dca    .push_back(track->get_dca());
    m_tr_x   .push_back(track->get_x());
    m_tr_y   .push_back(track->get_y());
    m_tr_z   .push_back(track->get_z());

  }

////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Calorimeters//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////EMCal//////////////////////////////////////////

 /// Get the raw cluster container
  /// Note: other cluster containers exist as well. Check out the node tree when
  /// you run a simulation
  RawClusterContainer *clusters = findNode::getClass<RawClusterContainer>(topNode, "CLUSTER_CEMC");

  if (!clusters)
  {
    cout << PHWHERE
         << "EMCal cluster node is missing, can't collect EMCal clusters"
         << endl;
    return;
  }

 // if(clusters) cout << "clusters size" << clusters->size() << endl;



  /// Get the global vertex to determine the appropriate pseudorapidity of the clusters
  GlobalVertexMap *vertexmap = findNode::getClass<GlobalVertexMap>(topNode, "GlobalVertexMap");
  if (!vertexmap)
  {
    cout << "CalData::getEmcalClusters - Fatal Error - GlobalVertexMap node is missing. Please turn on the do_global flag in the main macro in order to reconstruct the global vertex." << endl;
    assert(vertexmap);  // force quit

    return;
  }

  if (vertexmap->empty())
  {
    cout << "CalData::getEmcalClusters - Fatal Error - GlobalVertexMap node is empty. Please turn on the do_global flag in the main macro in order to reconstruct the global vertex." << endl;
    return;
  }

  GlobalVertex *vtx = vertexmap->begin()->second;
  if (vtx == nullptr)
    return;


  RawClusterContainer::ConstRange begin_end = clusters->getClusters();
  RawClusterContainer::ConstIterator clusIter;
 
  /// Loop over the EMCal clusters
  for (clusIter = begin_end.first;
       clusIter != begin_end.second;
       ++clusIter)
  {
    /// Get this cluster
    const RawCluster *cluster = clusIter->second;

    /// Get cluster characteristics
    /// This helper class determines the photon characteristics
    /// depending on the vertex position
    /// This is important for e.g. eta determination and E_T determination
    CLHEP::Hep3Vector vertex(vtx->get_x(), vtx->get_y(), vtx->get_z());
    CLHEP::Hep3Vector E_vec_cluster = RawClusterUtility::GetECoreVec(*cluster, vertex);

   if (E_vec_cluster.perp() < m_mincluspt) continue; //cut in pt, skip lower than 0.25 GeV ~ stupid noise
    //cout << "pt:" << E_vec_cluster.perp() << endl;

   m_clusenergy .push_back(E_vec_cluster.mag());
   m_cluseta .push_back(E_vec_cluster.pseudoRapidity());
   m_clustheta .push_back(E_vec_cluster.getTheta());
   m_cluspt .push_back(E_vec_cluster.perp());
   m_clusphi .push_back(E_vec_cluster.getPhi());

  }

//////////////////////////////////////EMCal//////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////HCal/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////HCalIN///////////////////////////////////////

  RawClusterContainer *clusters_hcal = findNode::getClass<RawClusterContainer>(topNode, "CLUSTER_HCALIN");

 if (!clusters_hcal)
  {
    cout << PHWHERE
         << "HCal cluster node is missing, can't collect HCal clusters"
         << endl;
    return;
  }
    //if(clusters_hcal) cout << "clusters HCal size" << clusters_hcal->size() << endl;

/////////////////////// Vertex stuff/////////////////////////////////////////////////////////////
// Get the global vertex to determine the appropriate pseudorapidity of the clusters
  GlobalVertexMap *vertexmap_hcal = findNode::getClass<GlobalVertexMap>(topNode, "GlobalVertexMap");
  if (!vertexmap)
  {
    cout << "CalData::getHCalINClusters - Fatal Error - GlobalVertexMap node is missing. Please turn on the do_global flag in the main macro in order to reconstruct the global vertex." << endl;
    assert(vertexmap);  // force quit

    return;
  }

  if (vertexmap->empty())
  {
    cout << "CalData::getHCalINClusters - Fatal Error - GlobalVertexMap node is empty. Please turn on the do_global flag in the main macro in order to reconstruct the global vertex." << endl;
    return;
  }

  GlobalVertex *vtxh = vertexmap_hcal->begin()->second;
  if (vtxh == nullptr)
    return;

////////////////////////////////////////////////////////////////////////////////////////////////
  
  RawClusterContainer::ConstRange begin_end_h = clusters_hcal->getClusters();
  RawClusterContainer::ConstIterator clusIter_h;
 
/// Loop over the HCal clusters
  for (clusIter_h = begin_end_h.first;
       clusIter_h != begin_end_h.second;
       ++clusIter_h)
{
  /// Get this cluster
    const RawCluster *cluster_HCal = clusIter_h->second;

  /// Get cluster characteristics
    CLHEP::Hep3Vector vertex(vtxh->get_x(), vtxh->get_y(), vtxh->get_z());
    CLHEP::Hep3Vector E_vec_cluster_H = RawClusterUtility::GetECoreVec(*cluster_HCal, vertex);

     m_clusenergy_HCal .push_back(E_vec_cluster_H.mag());
     m_cluseta_HCal .push_back(E_vec_cluster_H.pseudoRapidity());
     m_clusphi_HCal .push_back(E_vec_cluster_H.getPhi());
     m_cluspt_HCal .push_back(E_vec_cluster_H.perp());
  }
                   
//////////////////////////////////////////HCalIN end///////////////////////////////////////////////


//////////////////////////////////////////HCalOut//////////////////////////////////////////////////

RawClusterContainer *clusters_hcalout = findNode::getClass<RawClusterContainer>(topNode, "CLUSTER_HCALOUT");


 if (!clusters_hcalout)
  {
    cout << PHWHERE
         << "HCalOUT cluster node is missing, can't collect HCalOUT clusters"
         << endl;
    return;
  }
    //if(clusters_hcalout) cout << "clusters HCal size" << clusters_hcal->size() << endl;


/////////////////////// Vertex stuff/////////////////////////////////////////////////////////////
// Get the global vertex to determine the appropriate pseudorapidity of the clusters
  GlobalVertexMap *vertexmap_hcalout = findNode::getClass<GlobalVertexMap>(topNode, "GlobalVertexMap");
  if (!vertexmap)
  {
    cout << "CalData::getHCalcalClusters - Fatal Error - GlobalVertexMap node is missing. Please turn on the do_global flag in the main macro in order to reconstruct the global vertex." << endl;
    assert(vertexmap);  // force quit

    return;
  }

  GlobalVertex *vtxhcout = vertexmap_hcalout->begin()->second;
  if (vtxhcout == nullptr)
    return;
////////////////////////////////////////////////////////////////////////////////////////////////
  
  RawClusterContainer::ConstRange begin_end_hcout = clusters_hcalout->getClusters();
  RawClusterContainer::ConstIterator clusIter_hout;

/// Loop over the HCal clusters
  for (clusIter_hout = begin_end_hcout.first;
       clusIter_hout != begin_end_hcout.second;
       ++clusIter_hout)
{
  /// Get this cluster
    const RawCluster *cluster_HCalOUT = clusIter_hout->second;

  /// Get cluster characteristics
    CLHEP::Hep3Vector vertex(vtxhcout->get_x(), vtxhcout->get_y(), vtxhcout->get_z());
    CLHEP::Hep3Vector E_vec_cluster_HCOUT = RawClusterUtility::GetECoreVec(*cluster_HCalOUT, vertex);

     m_clusenergy_HCalOUT .push_back(E_vec_cluster_HCOUT.mag());
     m_cluseta_HCalOUT .push_back(E_vec_cluster_HCOUT.pseudoRapidity());
     m_clusphi_HCalOUT .push_back(E_vec_cluster_HCOUT.getPhi());
     m_cluspt_HCalOUT .push_back(E_vec_cluster_HCOUT.perp());
  }


///////////////////////////////////////////HCalOut end/////////////////////////////////////////////////


////////////////////////////////////////////HCalend/////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////




m_clustertree->Fill();
m_tracktree->Fill();

m_tr_px.clear();
m_tr_py.clear();
m_tr_pz.clear();
m_tr_p.clear();
m_tr_pt.clear();
m_tr_phi.clear();
m_tr_eta.clear();
m_charge.clear();
m_chisq.clear();
m_ndf.clear();
m_dca.clear();
m_tr_x.clear();
m_tr_y.clear();
m_tr_z.clear();
m_truthpx.clear();
m_truthpy.clear();
m_truthpz.clear();
m_truthp.clear();
m_truthenergy.clear();
m_truthpt.clear();
m_truthphi.clear();
m_trutheta.clear();
m_truthpid.clear();

//EMCal
m_clusenergy.clear();
m_cluseta.clear();
m_clustheta.clear();
m_cluspt.clear();
m_clusphi.clear();
m_cluspx.clear();
m_cluspy.clear();
m_cluspz.clear();

//HCal
m_clusenergy_HCal.clear(); 
m_cluseta_HCal.clear();
m_clusphi_HCal.clear(); 
m_cluspt_HCal.clear();

m_clusenergy_HCalOUT.clear(); 
m_cluseta_HCalOUT.clear();
m_clusphi_HCalOUT.clear(); 
m_cluspt_HCalOUT.clear();

}

/**
 * This method gets clusters from the EMCal and stores them in a tree. It
 * also demonstrates how to get trigger emulator information. Clusters from
 * other containers can be obtained in a similar way (e.g. clusters from
 * the IHCal, etc.)
 */
void CalData::getEMCalClusters(PHCompositeNode *topNode)
{
  /// Get the raw cluster container
  /// Note: other cluster containers exist as well. Check out the node tree when
  /// you run a simulation
  RawClusterContainer *clusters = findNode::getClass<RawClusterContainer>(topNode, "CLUSTER_CEMC");

  if (!clusters)
  {
    cout << PHWHERE
         << "EMCal cluster node is missing, can't collect EMCal clusters"
         << endl;
    return;
  }

  /// Get the global vertex to determine the appropriate pseudorapidity of the clusters
  GlobalVertexMap *vertexmap = findNode::getClass<GlobalVertexMap>(topNode, "GlobalVertexMap");
  if (!vertexmap)
  {
    cout << "CalData::getEmcalClusters - Fatal Error - GlobalVertexMap node is missing. Please turn on the do_global flag in the main macro in order to reconstruct the global vertex." << endl;
    assert(vertexmap);  // force quit

    return;
  }

  if (vertexmap->empty())
  {
    cout << "CalData::getEmcalClusters - Fatal Error - GlobalVertexMap node is empty. Please turn on the do_global flag in the main macro in order to reconstruct the global vertex." << endl;
    return;
  }

  GlobalVertex *vtx = vertexmap->begin()->second;
  if (vtx == nullptr)
    return;

  /// Trigger emulator
  CaloTriggerInfo *trigger = findNode::getClass<CaloTriggerInfo>(topNode, "CaloTriggerInfo");
  
  /// Can obtain some trigger information if desired
  if(trigger)
    {
     // m_E_4x4 = trigger->get_best_EMCal_4x4_E(); 
    }
  RawClusterContainer::ConstRange begin_end = clusters->getClusters();
  RawClusterContainer::ConstIterator clusIter;
 
  /// Loop over the EMCal clusters
  for (clusIter = begin_end.first;
       clusIter != begin_end.second;
       ++clusIter)
  {
    /*

    /// Get this cluster
    const RawCluster *cluster = clusIter->second;

    /// Get cluster characteristics
    /// This helper class determines the photon characteristics
    /// depending on the vertex position
    /// This is important for e.g. eta determination and E_T determination
  //  CLHEP::Hep3Vector vertex(vtx->get_x(), vtx->get_y(), vtx->get_z());
 //   CLHEP::Hep3Vector E_vec_cluster = RawClusterUtility::GetECoreVec(*cluster, vertex);
   

    m_clusenergy = E_vec_cluster.mag();
    m_cluseta = E_vec_cluster.pseudoRapidity();
    m_clustheta = E_vec_cluster.getTheta();
    m_cluspt = E_vec_cluster.perp();
    m_clusphi = E_vec_cluster.getPhi();

    if (m_cluspt < m_mincluspt)
      continue;

    m_cluspx = m_cluspt * cos(m_clusphi);
    m_cluspy = m_cluspt * sin(m_clusphi);
    m_cluspz = sqrt(m_clusenergy * m_clusenergy - m_cluspx * m_cluspx - m_cluspy * m_cluspy);

    //fill the cluster tree with all emcal clusters
    m_clustertree->Fill();
  
   */

  }
}



/**
 * This function puts all of the tree branch assignments in one place so as to not
 * clutter up the CalData::Init function.
 */
void CalData::initializeTrees()
{
  m_tracktree = new TTree("tracktree", "A tree with svtx tracks");
  m_tracktree->Branch("track_px", &m_tr_px);
  m_tracktree->Branch("track_py", &m_tr_py);
  m_tracktree->Branch("track_pz", &m_tr_pz);
  m_tracktree->Branch("track_p", &m_tr_p);
  m_tracktree->Branch("track_pt", &m_tr_pt);
  m_tracktree->Branch("track_phi", &m_tr_phi);
  m_tracktree->Branch("track_eta", &m_tr_eta);
  m_tracktree->Branch("track_charge", &m_charge);
  m_tracktree->Branch("track_chisq", &m_chisq);
  m_tracktree->Branch("track_ndf", &m_ndf);
  m_tracktree->Branch("track_dca", &m_dca);
  m_tracktree->Branch("track_x", &m_tr_x);
  m_tracktree->Branch("track_y", &m_tr_y);
  m_tracktree->Branch("track_z", &m_tr_z);
  m_tracktree->Branch("truth_px", &m_truthpx);
  m_tracktree->Branch("truth_py", &m_truthpy);
  m_tracktree->Branch("truth_pz", &m_truthpz);
  m_tracktree->Branch("truth_p", &m_truthp);
  m_tracktree->Branch("truth_energy", &m_truthenergy);
  m_tracktree->Branch("truth_pt", &m_truthpt);
  m_tracktree->Branch("truth_phi", &m_truthphi);
  m_tracktree->Branch("truth_eta", &m_trutheta);
  m_tracktree->Branch("truth_pid", &m_truthpid);

  //////////////EMCal/////////////////////////////
  m_tracktree->Branch("clus_energy", &m_clusenergy);
  m_tracktree->Branch("clus_eta", &m_cluseta);
  m_tracktree->Branch("clus_theta", &m_clustheta);
  m_tracktree->Branch("clus_pt", &m_cluspt);
  m_tracktree->Branch("clus_phi", &m_clusphi);
  m_tracktree->Branch("clus_px", &m_cluspx);
  m_tracktree->Branch("clus_py", &m_cluspy);
  m_tracktree->Branch("clus_pz", &m_cluspz);

    //////////////HCal/////////////////////////////
  m_tracktree->Branch("clusEnergy_HCal", &m_clusenergy_HCal); 
  m_tracktree->Branch("cluseta_HCal", &m_cluseta_HCal);
  //m_tracktree->Branch("clustheta_HCal", &m_clustheta_HCal);
  m_tracktree->Branch("clusphi_HCal", &m_clusphi_HCal);
  m_tracktree->Branch("cluspt_HCal", &m_cluspt_HCal);

  m_tracktree->Branch("clusEnergy_HCalOUT", &m_clusenergy_HCalOUT); 
  m_tracktree->Branch("cluseta_HCalOUT", &m_cluseta_HCalOUT);
  //m_tracktree->Branch("clustheta_HCalOUT", &m_clustheta_HCalOUT);
  m_tracktree->Branch("clusphi_HCalOUT", &m_clusphi_HCalOUT);
  m_tracktree->Branch("cluspt_HCalOUT", &m_cluspt_HCalOUT);

  m_hepmctree = new TTree("hepmctree", "A tree with hepmc truth particles");
  m_hepmctree->Branch("m_partid1", &m_partid1, "m_partid1/I");
  m_hepmctree->Branch("m_partid2", &m_partid2, "m_partid2/I");
  m_hepmctree->Branch("m_x1", &m_x1, "m_x1/D");
  m_hepmctree->Branch("m_x2", &m_x2, "m_x2/D");
  m_hepmctree->Branch("m_mpi", &m_mpi, "m_mpi/I");
  m_hepmctree->Branch("m_process_id", &m_process_id, "m_process_id/I");
  m_hepmctree->Branch("m_truthenergy", &m_truthenergy, "m_truthenergy/D");
  m_hepmctree->Branch("m_trutheta", &m_trutheta, "m_trutheta/D");
  m_hepmctree->Branch("m_truthphi", &m_truthphi, "m_truthphi/D");
  m_hepmctree->Branch("m_truthpx", &m_truthpx, "m_truthpx/D");
  m_hepmctree->Branch("m_truthpy", &m_truthpy, "m_truthpy/D");
  m_hepmctree->Branch("m_truthpz", &m_truthpz, "m_truthpz/D");
  m_hepmctree->Branch("m_truthpt", &m_truthpt, "m_truthpt/D");
  m_hepmctree->Branch("m_numparticlesinevent", &m_numparticlesinevent, "m_numparticlesinevent/I");
  m_hepmctree->Branch("m_truthpid", &m_truthpid, "m_truthpid/I");

  m_truthtree = new TTree("truthg4tree", "A tree with truth g4 particles");
  m_truthtree->Branch("m_truthenergy", &m_truthenergy, "m_truthenergy/D");
  m_truthtree->Branch("m_truthp", &m_truthp, "m_truthp/D");
  m_truthtree->Branch("m_truthpx", &m_truthpx, "m_truthpx/D");
  m_truthtree->Branch("m_truthpy", &m_truthpy, "m_truthpy/D");
  m_truthtree->Branch("m_truthpz", &m_truthpz, "m_truthpz/D");
  m_truthtree->Branch("m_truthpt", &m_truthpt, "m_truthpt/D");
  m_truthtree->Branch("m_truthphi", &m_truthphi, "m_truthphi/D");
  m_truthtree->Branch("m_trutheta", &m_trutheta, "m_trutheta/D");
  m_truthtree->Branch("m_truthpid", &m_truthpid, "m_truthpid/I");

  m_clustertree = new TTree("clustertree", "A tree with emcal clusters");
  m_clustertree->Branch("m_clusenergy", &m_clusenergy, "m_clusenergy/D");
  m_clustertree->Branch("m_cluseta", &m_cluseta, "m_cluseta/D");
  m_clustertree->Branch("m_clustheta", &m_clustheta, "m_clustheta/D");
  m_clustertree->Branch("m_cluspt", &m_cluspt, "m_cluspt/D");
  m_clustertree->Branch("m_clusphi", &m_clusphi, "m_clusphi/D");
  m_clustertree->Branch("m_cluspx", &m_cluspx, "m_cluspx/D");
  m_clustertree->Branch("m_cluspy", &m_cluspy, "m_cluspy/D");
  m_clustertree->Branch("m_cluspz", &m_cluspz, "m_cluspz/D");
  m_clustertree->Branch("m_E_4x4", &m_E_4x4, "m_E_4x4/D");
}

/**
 * This function initializes all of the member variables in this class so that there
 * are no variables that might not be set before e.g. writing them to the output
 * trees. 
 */
void CalData::initializeVariables()
{
  m_outfile = new TFile();
  m_phi_h = new TH1F();
  m_eta_phi_h = new TH2F();

  m_partid1 = -99;
  m_partid2 = -99;
  m_x1 = -99;
  m_x2 = -99;
  m_mpi = -99;
  m_process_id = -99;
  /*m_truthenergy = -99;
  m_trutheta = -99;
  m_truthphi = -99;
  m_truthp = -99;
  m_truthpx = -99;
  m_truthpy = -99;
  m_truthpz = -99;
  m_truthpt = -99;*/
  m_numparticlesinevent = -99;
  //m_truthpid = -99;

  /*m_tr_px = -99;
  m_tr_py = -99;
  m_tr_pz = -99;
  m_tr_p = -99;
  m_tr_pt = -99;
  m_tr_phi = -99;
  m_tr_eta = -99;
  m_charge = -99;
  m_chisq = -99;
  m_ndf = -99;
  m_dca = -99;
  m_tr_x = -99;
  m_tr_y = -99;
  m_tr_z = -99;
  m_truth_is_primary = -99;
  m_truthtrackpx = -99;
  m_truthtrackpy = -99;
  m_truthtrackpz = -99;
  m_truthtrackp = -99;
  m_truthtracke = -99;
  m_truthtrackpt = -99;
  m_truthtrackphi = -99;
  m_truthtracketa = -99;
  m_truthtrackpid = -99;*/


}


