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
#include "FWCore/ParameterSet/interface/ParameterSet.h"

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

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"

#include <map>
#include <string>
#include <iomanip>
#include <vector>

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
	int Collision_ = 0;

	double pt_;
	double eta_;
	double phi_;
	double chi2_;
	//double ndof_;
	double IP_;
	double d0_;
	double d0_bs_;
	double d0_xyz_;
	double dZ_bs_;
	double tt_d0_bs_;
	double tt_d0_err_bs_;
	double tt_z0_bs_;
	//double tt_z0_err_bs_;
	int Pix_HITs_; 
	int Strip_HITs_;
	int Track_HITs_;
	bool high_quality_;

	int VtxID_ = 0;
	double x_PV_;
	double y_PV_;
	double z_PV_;

	reco::BeamSpot beamSpot;

	// Input Tags and Tokens
	edm::InputTag offlinePVTag_;
	edm::EDGetTokenT<reco::VertexCollection> offlinePVToken_;

	edm::InputTag trackTag_;
	edm::EDGetTokenT<reco::TrackCollection> trackToken_;

	edm::InputTag beamSpotTag_;
	edm::EDGetTokenT<reco::BeamSpot> beamSpotToken_;

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

	trackTag_		(iConfig.getParameter<edm::InputTag>("tracks")),
	trackToken_		(consumes<reco::TrackCollection>(trackTag_)),

	beamSpotTag_		(iConfig.getParameter<edm::InputTag>("beamSpot")),
	beamSpotToken_		(consumes<reco::BeamSpot>(beamSpotTag_))
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
	trackTree_->Branch("Collision"		,&Collision_	);

	trackTree_->Branch("pt"	   		,&pt_		);
	trackTree_->Branch("eta"	   	,&eta_		);
	trackTree_->Branch("phi"		,&phi_);
	trackTree_->Branch("chi2"	   	,&chi2_		);
	//trackTree_->Branch("ndof"	   	,&ndof_		);
	trackTree_->Branch("dxy"       		,&IP_		);
	trackTree_->Branch("d0"			,&d0_		);
	trackTree_->Branch("d0_bs"		,&d0_bs_	);
	trackTree_->Branch("d0_xyz"		,&d0_xyz_	);
	trackTree_->Branch("dZ_bs"		,&dZ_bs_	);
	trackTree_->Branch("tt_d0_bs"		,&tt_d0_bs_	);
	trackTree_->Branch("tt_d0_err_bs"	,&tt_d0_err_bs_	);
	trackTree_->Branch("tt_z0_bs"		,&tt_z0_bs_	);
	//trackTree_->Branch("tt_z0_err_bs"	,&tt_z0_err_bs_	);

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
	//std::cout<<"\t   ~~~ NEW EVENT ~~~"<<std::endl;
	Collision_ += 1;

	// Clear all the variables
	beginEvent();

	// Handles to get trk and PV collections
	edm::Handle<reco::TrackCollection> trkHandle;
	iEvent.getByToken(trackToken_, trkHandle);
	//iEvent.getByLabel(trackTag_,trkHandle);
	//iEvent.getByLabel(edm::InputTag("ALCARECOTkAlMinBias","","RECO"), trkHandle);

        edm::Handle<reco::VertexCollection> pvHandle;
	iEvent.getByToken(offlinePVToken_, pvHandle);
  	const reco::VertexCollection primvtx  = *(pvHandle.product());
  	//iEvent.getByLabel("offlinePrimaryVertices", pvHandle)       ;

	edm::Handle<reco::BeamSpot> beamSpotHandle;
	iEvent.getByToken(beamSpotToken_, beamSpotHandle);

	edm::ESHandle<TransientTrackBuilder> theB;
    	iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);
	//std::vector<reco::TransientTrack> t_tks = (*theB).build(trkHandle);


	// Loop on PV (no need for iPV.isValid() ad all vtxs are valid)
	for (reco::VertexCollection::const_iterator pvIt = primvtx.begin(); pvIt!=primvtx.end(); pvIt++)        
        {
        	reco::Vertex iPV = *pvIt;
	
		// Counter for vertex indices
		VtxID_ += 1;
		//std::cout<<"Vertex n: "<<VtxID_<<" - trackSize:   "<<iPV.tracksSize()<<std::endl;

		// Set the coordinates of the current vertex
	    	x_PV_ 	 	= iPV.x();
	    	y_PV_ 	 	= iPV.y();
	    	z_PV_		= iPV.z();

		int n_tracks = 0;
          	// Loop on Tracks
          	for (reco::Vertex::trackRef_iterator trki = iPV.tracks_begin(); trki != iPV.tracks_end(); ++trki)  
          	{
	  	  	// Get the courrent track
          	  	reco::TrackRef trk_now(trkHandle, (*trki).key());

          	  	//reco::Track iTrack = trkHandle->at(tracksIt);                                            	   
          	  	//reco::Track iTrack = iPV.refittedTracks().at(tracksIt);   // non trkHandle ma collez tr da vertice                                             	   

	  	  	// Get the informations
			//if (trk_now->numberOfValidHits()>6 && trk_now->pt()>0.5 && trk_now->normalizedChi2()<10. 
			//	&& trk_now->normalizedChi2()>0. && trk_now->quality(reco::TrackBase::highPurity))
			if (trk_now->numberOfValidHits()>=8 && trk_now->pt()>=1. && trk_now->normalizedChi2()<10. 
				&& trk_now->normalizedChi2()>0. && trk_now->quality(reco::TrackBase::highPurity) && (std::abs(trk_now->eta()) < 1.)
				&& trk_now->hitPattern().numberOfValidPixelHits() >=1 )
			{
			    	/*Run_		= iEvent.id().run();
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
			    	z_PV_		= iTrack.vz();*/	

				Run_		= iEvent.id().run();
			    	Lumi_		= iEvent.id().luminosityBlock();
			    	Event_		= iEvent.id().event();
				pt_ 	 	= trk_now->pt();
				eta_ 	 	= trk_now->eta();
			    	chi2_ 	 	= trk_now->normalizedChi2();
				phi_		= trk_now->phi();
			    	IP_ 	 	= trk_now->dxy();
			    	Pix_HITs_	= trk_now->hitPattern().numberOfValidPixelHits();
			    	Strip_HITs_	= trk_now->hitPattern().numberOfValidStripHits();
			    	Track_HITs_	= trk_now->numberOfValidHits();
			    	high_quality_	= trk_now->quality(reco::TrackBase::highPurity);


				// Impact parameters
				math::XYZPoint zero_point(0.,0.,0.);
				d0_ = -1.* trk_now->dxy(zero_point);
				
				math::XYZPoint PV_point(x_PV_, y_PV_, z_PV_);
				d0_xyz_ = -1.* trk_now->dxy(PV_point);

				beamSpot = *beamSpotHandle;
				math::XYZPoint BSpoint(beamSpot.x0(),beamSpot.y0(), beamSpot.z0());
				d0_bs_ = -1.* trk_now->dxy(BSpoint);
				dZ_bs_ = -1 * trk_now->dz(BSpoint);

				const reco::TransientTrack trans_track = (*theB).build(trk_now);
				GlobalPoint BSvert(beamSpot.x0(),beamSpot.y0(), beamSpot.z0());
				TrajectoryStateClosestToPoint  traj = trans_track.trajectoryStateClosestToPoint(BSvert);
				tt_d0_bs_ = traj.perigeeParameters().transverseImpactParameter();
				tt_d0_err_bs_ = traj.perigeeError().transverseImpactParameterError();
				tt_z0_bs_ = traj.perigeeParameters().longitudinalImpactParameter();
				//tt_z0_err_bs_ = traj.perigeeParameters().longitudinalImpactParameterError();

			    	// Fill the TTree
			    	trackTree_->Fill(); 

				n_tracks +=1;
	
			} //if track conditions
	
	  	} //loop on tracks
		//std::cout<<"\t  \t   - n_tracks: "<<n_tracks<<std::endl;
	} //loop on vertex
	//std::cout<<"Total number of vtxs until now: "<<VtxID_<<std::endl;
	//std::cout<<"Event number:                   "<<Collision_<<std::endl;

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
	phi_		= 0.;
	IP_ 		= 0.;
	d0_		= 0.;
	d0_bs_		= 0.;
	d0_xyz_		= 0.;
	dZ_bs_		= 0.;
	tt_d0_bs_	= 0.;
	tt_d0_err_bs_	= 0.;
	tt_z0_bs_	= 0.;
	//tt_z0_err_bs_	= 0.;
	Pix_HITs_ 	= 0;
	Strip_HITs_	= 0;
	Track_HITs_ 	= 0;
	high_quality_ 	= false;

	x_PV_ 	= 0.;
	y_PV_ 	= 0.;
	z_PV_ 	= 0.;
}

//define this as a plug-in
DEFINE_FWK_MODULE(dxy_phi);
