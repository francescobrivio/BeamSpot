/*
    Macro to: 
	- read the tracFile.root,
	- select the tracks,
	- create the possible pairs of tracks per vertex (combinatorial)
	- create tgraphs of <dxy1*dxy2> vs cos(phi1-phi2) and vs cos(phi1+phi2)	
	- fit the graphs
*/

#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TTree.h"
#include "TBranch.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TProfile.h"
#include "TF1.h"

#include <string>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

// Global variables
double pt_cut = 1.;
double eta_cut = 1.;
int trk_hits_cut = 8;
int pix_hits_cut = 1;

int dxy_bins = 2000;
double dxy_min = -0.03;
double dxy_max = 0.03;

int cos_bins = 40;

void dxy_fitter ()
{

	std::cout<<"------------ BEGIN OF MACRO ------------"<<std::endl;

	// INPUT file and tree
	//TFile* inputfile = TFile::Open("/afs/cern.ch/work/f/fbrivio/beamSpot/CMSSW_8_0_4/src/dxy_phi/dxy_phi/test/tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("TT_tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("bs_tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("d0_tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("IPs_tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("MC_tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("event_tracksFile.root", "READ");
	TFile* inputfile = TFile::Open("259388_tracksFile.root", "READ");
  	std::cout << "\t Input file: " << inputfile -> GetName() << std::endl;
  	if (!inputfile) 
	{
    	std::cout << " *** file not found *** " << std::endl;
    	return;
  	}

	// OUTPUT file
	//TFile* outfile = TFile::Open("TT_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("bs_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("d0_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("IPs_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("MC_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("event_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("test_graphs.root","RECREATE");
	TFile* outfile = TFile::Open("259388_graphs.root","RECREATE");
  	std::cout << "\t Output file: " << outfile->GetName() << std::endl;

	// TH2D histograms
	h_cos_plus = new TH2D("cos_plus","TH2D of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}+#phi_{2})",cos_bins,-1.,1.,dxy_bins,dxy_min,dxy_max);
	h_cos_plus->GetXaxis()->SetTitle("cos(#phi_{1}+#phi_{2})");
	h_cos_plus->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");
	h_cos_minus = new TH2D("cos_minus","TH2D of<d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}-#phi_{2})",cos_bins,-1.,1.,dxy_bins,dxy_min,dxy_max);
	h_cos_minus->GetXaxis()->SetTitle("cos(#phi_{1}-#phi_{2})");
	h_cos_minus->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");

	// TH1D per IP
	h_dxy 	= new 	TH1D("h_dxy", 	"h_dxy", 100, -0.2, 0.2);
	h_d0 	= new 	TH1D("h_d0", 	"h_d0", 100, -0.2, 0.2);
	h_bs = new 	TH1D("h_bs", "h_d0_bs", 100, -0.2, 0.2);
	h_xyz = new 	TH1D("h_xyz","h_d0_xyz", 100, -0.2, 0.2);

	// TProfiles
	prof_plus_dxy = new TProfile("prof_plus_dxy","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}+#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_plus_dxy->GetXaxis()->SetTitle("cos(#phi_{1}+#phi_{2})");
	prof_plus_dxy->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");
	prof_minus_dxy = new TProfile("prof_minus_dxy","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}-#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_minus_dxy->GetXaxis()->SetTitle("cos(#phi_{1}-#phi_{2})");
	prof_minus_dxy->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");

	prof_plus_d0 = new TProfile("prof_plus_d0","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}+#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_plus_d0->GetXaxis()->SetTitle("cos(#phi_{1}+#phi_{2})");
	prof_plus_d0->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");
	prof_minus_d0 = new TProfile("prof_minus_d0","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}-#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_minus_d0->GetXaxis()->SetTitle("cos(#phi_{1}-#phi_{2})");
	prof_minus_d0->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");

	prof_plus_bs = new TProfile("prof_plus_bs","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}+#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_plus_bs->GetXaxis()->SetTitle("cos(#phi_{1}+#phi_{2})");
	prof_plus_bs->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");
	prof_plus_bs->SetMarkerStyle(22);
	prof_plus_bs->SetMarkerColor(kBlue);
	prof_minus_bs = new TProfile("prof_minus_bs","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}-#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_minus_bs->GetXaxis()->SetTitle("cos(#phi_{1}#pm#phi_{2})");
	prof_minus_bs->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");
	prof_minus_bs->SetMarkerStyle(20);
	prof_minus_bs->SetMarkerColor(kRed);

	prof_plus_xyz = new TProfile("prof_plus_xyz","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}+#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_plus_xyz->GetXaxis()->SetTitle("cos(#phi_{1}+#phi_{2})");
	prof_plus_xyz->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");
	prof_minus_xyz = new TProfile("prof_minus_xyz","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}-#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_minus_xyz->GetXaxis()->SetTitle("cos(#phi_{1}-#phi_{2})");
	prof_minus_xyz->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");

	// Check number of entries in ttree and the number of vertexes
	TTree *tree = (TTree*) inputfile->Get("demo/trackTree_");
	int nentries = tree->GetEntriesFast();
  	std::cout << "\t Number of entries  = " << nentries << std::endl;
	int nvtxs = tree->GetMaximum("VtxID");
	std::cout << "\t Number of vertexes = " << nvtxs << std::endl;

	// Declaration of variables
	double ipt, ieta, iphi, idxy, ichi2, id0, id0_bs, id0_xyz;
	int iPix_HITs, iTrack_HITs, iVtxID, iCollision;
	bool iQuality;

	// Access branches of ttree
	tree->SetBranchAddress("pt",&ipt);
	tree->SetBranchAddress("eta",&ieta);
	tree->SetBranchAddress("Pix_HITs",&iPix_HITs);
	tree->SetBranchAddress("Track_HITs",&iTrack_HITs);
	tree->SetBranchAddress("high_quality", &iQuality);
	tree->SetBranchAddress("chi2", &ichi2);

	tree->SetBranchAddress("phi",&iphi);
	tree->SetBranchAddress("dxy",&idxy);
	tree->SetBranchAddress("d0",&id0);
	tree->SetBranchAddress("d0_bs",&id0_bs);
	tree->SetBranchAddress("d0_xyz",&id0_xyz);
	tree->SetBranchAddress("VtxID",&iVtxID);
	tree->SetBranchAddress("Collision",&iCollision);
	tree->SetBranchAddress("Event",&iCollision);

	// Loop on tracks
	std::cout<<" - Begin of loop - "<<std::endl;
	int after_cuts = 0;
	for (int i = 0; i < nentries; ++i) 
	//for (int i = 0; i < 10000; ++i) 
	{
		tree->GetEntry(i);

		//std::cout<<"New track from vertex: "<<iVtxID<<std::endl;

		// Track selection (pt>1 - |eta|<1 - 8Hits - 1PixHit)
		if( (ipt < pt_cut) || (std::abs(ieta) > eta_cut) || (iTrack_HITs < trk_hits_cut) || (iPix_HITs < pix_hits_cut) ) continue;
			//|| (iQuality != 1) || (ichi2 > 10.) || (ichi2 < 0.) ) continue;

		after_cuts += 1;

		//std::cout<<"First track: "<<i<<" - Vertex: "<<iVtxID<<std::endl;

		// Temporary variables
		int 	tmp_vtx = iVtxID;
		int	tmp_coll = iCollision;
		double 	tmp_phi = iphi;
		double 	tmp_dxy = idxy;
		double 	tmp_d0 = id0;
		double	tmp_d0_bs = id0_bs;
		double	tmp_d0_xyz = id0_xyz;

		//std::cout<<"\t tmp_dxy= "<<tmp_dxy<<std::endl;
		h_dxy->Fill(idxy);
		h_d0->Fill(id0);
		h_bs->Fill(id0_bs);
		h_xyz->Fill(id0_xyz);

		// Another loop on tracks
		for (int j = i+1; j< nentries; ++j)
		{
			tree->GetEntry(j);

			// Print the number of event
			if (j % 1000 == 0) std::cout<<"Analysing event: "<<j<<std::endl;

			// Check if the track is from same vertex
			if (iVtxID > tmp_vtx) break;
			//if (iCollision > tmp_coll) break;

			// Track + vertex selection
			if ( (iVtxID != tmp_vtx) || (ipt < pt_cut) || (std::abs(ieta)> eta_cut) || (iTrack_HITs < trk_hits_cut) || (iPix_HITs < pix_hits_cut) ) continue; 
			//if ( (iCollision != tmp_coll) || (ipt < pt_cut) || (std::abs(ieta)> eta_cut) || (iTrack_HITs < trk_hits_cut) || (iPix_HITs < pix_hits_cut) ) continue; 

			// Fill TH2D
			h_cos_plus ->Fill(std::cos(iphi + tmp_phi), idxy*tmp_dxy );
			h_cos_minus->Fill(std::cos(iphi - tmp_phi), idxy*tmp_dxy );

			// Fill TProfiles
			prof_plus_dxy 	->Fill(std::cos(iphi + tmp_phi), idxy*tmp_dxy 		);
			prof_minus_dxy	->Fill(std::cos(iphi - tmp_phi), idxy*tmp_dxy 		);
			prof_plus_d0 	->Fill(std::cos(iphi + tmp_phi), id0*tmp_d0 		);
			prof_minus_d0	->Fill(std::cos(iphi - tmp_phi), id0*tmp_d0 		);
			prof_plus_bs 	->Fill(std::cos(iphi + tmp_phi), id0_bs*tmp_d0_bs 	);
			prof_minus_bs	->Fill(std::cos(iphi - tmp_phi), id0_bs*tmp_d0_bs 	);
			prof_plus_xyz 	->Fill(std::cos(iphi + tmp_phi), id0_xyz*tmp_d0_xyz 	);
			prof_minus_xyz	->Fill(std::cos(iphi - tmp_phi), id0_xyz*tmp_d0_xyz 	);
		}
	
		// Clear temporary variables
		tmp_vtx    = 0;
		tmp_coll   = 0;
		tmp_phi    = 0.;
		tmp_dxy    = 0.;
		tmp_d0	   = 0.;
		tmp_d0_bs  = 0.;
		tmp_d0_xyz = 0.;
		
	}

	std::cout<<" - End of loop - "<<std::endl;
	std::cout<<"\t Number of events after cuts = "<<after_cuts<<std::endl;

	// Fit the TProfiles
	std::cout<<"Fitting...\n";
   	prof_minus_dxy->Fit("pol1");
   	prof_plus_dxy ->Fit("pol1");
   	prof_minus_d0->Fit("pol1");
   	prof_plus_d0 ->Fit("pol1");
   	prof_minus_bs->Fit("pol1");
   	prof_plus_bs ->Fit("pol1");
   	prof_minus_xyz->Fit("pol1");
   	prof_plus_xyz ->Fit("pol1");

	// Retrieve fit parameters
	std::cout<<"Retrieving parameters...\n";
	TF1 *f_m_dxy = prof_minus_dxy->GetFunction("pol1");
	TF1 *f_p_dxy = prof_plus_dxy->GetFunction("pol1");
	double m_dxy = f_m_dxy->GetParameter(1);
	double p_dxy = f_p_dxy->GetParameter(1);

	TF1 *f_m_d0 = prof_minus_d0->GetFunction("pol1");
	TF1 *f_p_d0 = prof_plus_d0->GetFunction("pol1");
	double m_d0 = f_m_d0->GetParameter(1);
	double p_d0 = f_p_d0->GetParameter(1);

	TF1 *f_m_bs = prof_minus_bs->GetFunction("pol1");
	TF1 *f_p_bs = prof_plus_bs->GetFunction("pol1");
	double m_bs = f_m_bs->GetParameter(1);
	double p_bs = f_p_bs->GetParameter(1);
	f_p_bs->SetLineColor(kBlue);
	f_p_bs->SetLineColor(kRed);

	TF1 *f_m_xyz = prof_minus_xyz->GetFunction("pol1");
	TF1 *f_p_xyz = prof_plus_xyz->GetFunction("pol1");
	double m_xyz = f_m_xyz->GetParameter(1);
	double p_xyz = f_p_xyz->GetParameter(1);

	std::cout<<"\n*************** - FIT RESULTS - ***************"<<std::endl;
	std::cout<<"	- dxy - "<<std::endl;
	std::cout<<"Sigma_x^2 = "<<m_dxy + p_dxy<<std::endl;
	std::cout<<"Sigma_y^2 = "<<m_dxy - p_dxy<<std::endl;
	std::cout<<"Sigma_x = "<<sqrt(m_dxy + p_dxy) * 10000<<" um"<<std::endl;
	std::cout<<"Sigma_y = "<<sqrt(m_dxy - p_dxy) * 10000<<" um"<<std::endl;
	std::cout<<"\n";
	std::cout<<"	- d0 - "<<std::endl;
	std::cout<<"Sigma_x^2 = "<<m_d0 + p_d0<<std::endl;
	std::cout<<"Sigma_y^2 = "<<m_d0 - p_d0<<std::endl;
	std::cout<<"Sigma_x = "<<sqrt(m_d0 + p_d0) * 10000<<" um"<<std::endl;
	std::cout<<"Sigma_y = "<<sqrt(m_d0 - p_d0) * 10000<<" um"<<std::endl;
	std::cout<<"\n";
	std::cout<<"	- bs - "<<std::endl;
	std::cout<<"Sigma_x^2 = "<<m_bs + p_bs<<std::endl;
	std::cout<<"Sigma_y^2 = "<<m_bs - p_bs<<std::endl;
	std::cout<<"Sigma_x = "<<sqrt(m_bs + p_bs) * 10000<<" um"<<std::endl;
	std::cout<<"Sigma_y = "<<sqrt(m_bs - p_bs) * 10000<<" um"<<std::endl;
	std::cout<<"\n";
	std::cout<<"	- xyz - "<<std::endl;
	std::cout<<"m_xyz = "<<m_xyz<<std::endl;
	std::cout<<"p_xyz = "<<p_xyz<<std::endl;
	std::cout<<"Sigma_x^2 = "<<m_xyz + p_xyz<<std::endl;
	std::cout<<"Sigma_y^2 = "<<m_xyz - p_xyz<<std::endl;
	std::cout<<"Sigma_x = "<<sqrt(m_xyz + p_xyz) * 10000<<" um"<<std::endl;
	std::cout<<"Sigma_y = "<<sqrt(m_xyz - p_xyz) * 10000<<" um"<<std::endl;
	std::cout<<"*************************************************"<<std::endl;

	// Close file and save the results
	outfile		-> cd();

  	h_cos_plus	-> Write();
  	h_cos_minus	-> Write();

	h_dxy		-> Write();
	h_d0		-> Write();
	h_bs		-> Write();
	h_xyz		-> Write();

	prof_plus_dxy	-> Write();
	prof_minus_dxy	-> Write();
	prof_plus_d0	-> Write();
	prof_minus_d0	-> Write();
	prof_plus_bs	-> Write();
	prof_minus_bs	-> Write();
	prof_plus_xyz	-> Write();
	prof_minus_xyz	-> Write();

  	outfile		-> Close();  
  
	std::cout<<"------------ END OF MACRO ------------"<<std::endl;
	return;
}




















