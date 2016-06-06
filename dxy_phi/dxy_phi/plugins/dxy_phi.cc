// -*- C++ -*-
//
// Package:    dxy_phi/dxy_phi
// Class:      dxy_phi
// 
/**\class dxy_phi dxy_phi.cc dxy_phi/dxy_phi/plugins/dxy_phi.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Francesco Brivio
//         Created:  Fri, 27 May 2016 13:48:35 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include <map>
#include <string>
#include <iomanip>

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"

#include <typeinfo>

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class dxy_phi : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit dxy_phi(const edm::ParameterSet&);
      ~dxy_phi();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      virtual void beginEvent();

      // ----------member data ---------------------------

	// TFile & TTree
	edm::Service<TFileService> outfile_;
	TTree* trackTree_;

	// Variables for branches
	int Run_;
	int Lumi_;
	int Event_;

	double pt_;
	double eta_;
	double phi_;
	double chi2_;
	//double ndof_;
	double IP_;
	int Pix_HITs_; 
	int Strip_HITs_;
	int Track_HITs_;
	bool high_quality_;

	int VtxID_ = 0;
	double x_PV_;
	double y_PV_;
	double z_PV_;

	// Input Tags and Tokens
	edm::InputTag offlinePVTag_;
	edm::EDGetTokenT<reco::VertexCollection> offlinePVToken_;

	edm::InputTag trackTag_;
	edm::EDGetTokenT<reco::TrackCollection> trackToken_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
dxy_phi::dxy_phi(const edm::ParameterSet& iConfig):
	offlinePVTag_		(iConfig.getParameter<edm::InputTag>("offlineVtx")),
	offlinePVToken_         (consumes<reco::VertexCollection>(offlinePVTag_)),
	//offlinePVToken_         ("offlinePrimaryVertices");

	trackTag_		(iConfig.getParameter<edm::InputTag>("tracks")),
	trackToken_		(consumes<reco::TrackCollection>(trackTag_))
	//trackToken_		("ALCARECOTkAlMinBias");
{
   	//now do what ever initialization is needed
   	usesResource("TFileService");
}


dxy_phi::~dxy_phi()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called once each job just before starting event loop  ------------
void 
dxy_phi::beginJob()
{
	// TFile and TTree declaration
	//TFile *f = new TFile("tracks_file.root");
	//TTree *tree = (TTree*)f->Get("tree");
	trackTree_ = outfile_->make<TTree>("trackTree_", "trackTree_");

	// TTree branches
	trackTree_->Branch("Run"       		,&Run_		);
	trackTree_->Branch("Lumi"	   	,&Lumi_		);
	trackTree_->Branch("Event"	   	,&Event_	);

	trackTree_->Branch("pt"	   		,&pt_		);
	trackTree_->Branch("eta"	   	,&eta_		);
	trackTree_->Branch("phi"		,&phi_);
	trackTree_->Branch("chi2"	   	,&chi2_		);
	//trackTree_->Branch("ndof"	   	,&ndof_		);
	trackTree_->Branch("dxy"       		,&IP_		);
	trackTree_->Branch("Pix_HITs"		,&Pix_HITs_	);
	trackTree_->Branch("Strip_HITs"		,&Pix_HITs_	);
	trackTree_->Branch("Track_HITs"		,&Track_HITs_	);
	trackTree_->Branch("high_quality"	,&high_quality_	);

	trackTree_->Branch("VtxID"		,&VtxID_	);
	trackTree_->Branch("x_PV"	   	,&x_PV_		);
	trackTree_->Branch("y_PV"	   	,&y_PV_		);
	trackTree_->Branch("z_PV"	   	,&z_PV_		);

}

// ------------ method called once each job just after ending the event loop  ------------
void dxy_phi::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void dxy_phi::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// ------------ method called for each event  ------------
void
dxy_phi::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	//using namespace edm;
	std::cout<<"\t   ~~~ NEW EVENT ~~~"<<std::endl;

	// Clear all the variables
	beginEvent();

	// Handles to get trk and PV collections
	edm::Handle<reco::TrackCollection> trkHandle;
	iEvent.getByToken(trackToken_, trkHandle);
	//iEvent.getByLabel(edm::InputTag("ALCARECOTkAlMinBias","","RECO"), trkHandle);

        edm::Handle<reco::VertexCollection> pvHandle;
	iEvent.getByToken(offlinePVToken_, pvHandle);
  	//iEvent.getByLabel("offlinePrimaryVertices", pvHandle)       ;
  	const reco::VertexCollection primvtx  = *(pvHandle.product())  ;

	// Loop on PV (no need for iPV.isValid() ad all vtxs are valid)
	for (reco::VertexCollection::const_iterator pvIt = primvtx.begin(); pvIt!=primvtx.end(); pvIt++)        
        {
        	reco::Vertex iPV = *pvIt;
	
		// Counter for vertex indices
		VtxID_ += 1;
		//std::cout<<"Vertex n: "<<VtxID_<<" - nTracks: "<<iPV.nTracks()<<std::endl;

          	// Loop on Tracks
          	//for (reco::Vertex::trackRef_iterator trki = iPV.tracks_begin(); trki != iPV.tracks_end(); ++trki) 
          	//{
          	for (unsigned tracksIt =0 ;  tracksIt < trkHandle->size(); tracksIt++)
          	{
	  	  	// Get the courrent track
          	  	//reco::TrackRef trk_now(trkHandle, (*trki).key());
			//std::cout<<"\t Traccia:"<<typeid(trk_now).name()<<std::endl;
          	  	reco::Track iTrack = trkHandle->at(tracksIt);                                                	   
 	
	  	  	// Get the informations
			//if (trk_now->numberOfValidHits() > 6 ) // && && trk_now->normalizedChi2() < 10. && trk_now->normalizedChi2() > 0.)
			if (iTrack.numberOfValidHits() > 6 && iTrack.chi2() <= 10.)
			{
			    	Run_		= iEvent.id().run();
			    	Lumi_		= iEvent.id().luminosityBlock();
			    	Event_		= iEvent.id().event();
			
				pt_		= iTrack.pt();
				eta_		= iTrack.eta();
				chi2_		= iTrack.normalizedChi2();
				phi_		= iTrack.phi();
			    	IP_ 	 	= iTrack.dxy();
			    	Pix_HITs_	= iTrack.hitPattern().numberOfValidPixelHits();
			    	Strip_HITs_	= iTrack.hitPattern().numberOfValidStripHits();
			    	Track_HITs_	= iTrack.numberOfValidHits();
			    	high_quality_	= iTrack.quality(reco::TrackBase::highPurity);
		
			    	x_PV_ 	 	= iTrack.vx();
			    	y_PV_ 	 	= iTrack.vy();
			    	z_PV_		= iTrack.vz();
	
				/*pt_ 	 	= trk_now->pt();
				eta_ 	 	= trk_now->eta();
				phi_		= trk_now->phi();
			    	chi2_ 	 	= trk_now->normalizedChi2();
			    	ndof_ 	 	= trk_now->ndof();
			    	IP_ 	 	= trk_now->dxy();
			    	Pix_HITs_	= trk_now->hitPattern().numberOfValidPixelHits();
			    	Strip_HITs_	= trk_now->hitPattern().numberOfValidStripHits();
			    	Track_HITs_	= trk_now->numberOfValidHits();
			    	//std::cout<<"\t \t hits: "<<Pix_HITs_<<" - "<<Strip_HITs_<<" - "<<Track_HITs_<<std::endl;
			    	high_quality_	= trk_now->quality(reco::TrackBase::highPurity);
			    	x_PV_ 	 	= trk_now->vx();
			    	y_PV_ 	 	= trk_now->vy();
			    	z_PV_		= trk_now->vz();*/
		
			    	// Fill the TTree
			    	trackTree_->Fill();
	
			} //if track conditions
	
	  	} //loop on tracks
	
	} //loop on vertex
	std::cout<<"Total number of vtxs until now: "<<VtxID_<<std::endl;

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif

} // end of function analyze


void dxy_phi::beginEvent()
{
	Run_ 	= 0.;
	Lumi_ 	= 0.;
	Event_ 	= 0.;

	pt_ 		= 0.;
	eta_ 		= 0.;
	chi2_ 		= 0.;
	IP_ 		= 0.;
	Pix_HITs_ 	= 0;
	Strip_HITs_	= 0;
	Track_HITs_ 	= 0;
	high_quality_ 	= false;


	//VtxID_	= 0;
	x_PV_ 	= 0.;
	y_PV_ 	= 0.;
	z_PV_ 	= 0.;
}

//define this as a plug-in
DEFINE_FWK_MODULE(dxy_phi);
