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

void dxy_fitter_2 ()
{

	std::cout<<"------------ BEGIN OF MACRO ------------"<<std::endl;

	// INPUT file and tree
	//TFile* inputfile = TFile::Open("/afs/cern.ch/work/f/fbrivio/beamSpot/CMSSW_8_0_4/src/dxy_phi/dxy_phi/test/tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("bs_tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("results/full_tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("IPs_tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("results/MC_tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("event_tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("results/274971_tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("274971_dZ_tracksFile.root", "READ");
	TFile* inputfile = TFile::Open("274959_transient_tracksFile.root", "READ");

  	std::cout << "\t Input file: " << inputfile -> GetName() << std::endl;
  	if (!inputfile) 
	{
    	std::cout << " *** file not found *** " << std::endl;
    	return;
  	}

	// OUTPUT file
	//TFile* outfile = TFile::Open("bs_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("d0_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("IPs_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("MC_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("event_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("test_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("274971_graphs.root","RECREATE");
	//TFile* outfile = TFile::Open("274971_dZ_graphs.root","RECREATE");
	TFile* outfile = TFile::Open("274959_transient_graphs.root","RECREATE");
  	std::cout << "\t Output file: " << outfile->GetName() << std::endl;

	// TH2D histograms
	h_cos_plus = new TH2D("cos_plus","TH2D of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}+#phi_{2})",cos_bins,-1.,1.,dxy_bins,dxy_min,dxy_max);
	h_cos_plus->GetXaxis()->SetTitle("cos(#phi_{1}+#phi_{2})");
	h_cos_plus->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");
	h_cos_minus = new TH2D("cos_minus","TH2D of<d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}-#phi_{2})",cos_bins,-1.,1.,dxy_bins,dxy_min,dxy_max);
	h_cos_minus->GetXaxis()->SetTitle("cos(#phi_{1}-#phi_{2})");
	h_cos_minus->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");

	double pt_bins[63] = {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0 , 5.5, 6.0 , 6.5, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};
	//double pt_bins[6] = {0,1,2,3,4,5};
	//int nbins = sizeof(pt_bins)-1;
	TH2D *errIP_pt  = new TH2D("errIP_pt" ,"",62,pt_bins,100,0.,2.);
	TH2D *errIP_eta = new TH2D("errIP_eta","",40.,-2.5,2.5,100,0.,2.);
	TH2D *errIP_phi = new TH2D("errIP_phi","",50,-3.5,3.5,100,0.,2.);

	// TH1D per IP
	h_dxy 	 = new 	TH1D("h_dxy", 	"h_dxy", 100, -0.2, 0.2);
	h_d0 	 = new 	TH1D("h_d0", 	"h_d0", 100, -0.2, 0.2);
	h_bs 	 = new 	TH1D("h_bs", "h_d0_bs", 100, -0.2, 0.2);
	h_xyz    = new 	TH1D("h_xyz","h_d0_xyz", 100, -0.2, 0.2);
	h_deltaZ = new 	TH1D("h_deltaZ","h_deltaZ", 100, -1., 1.);

	// TProfiles
	prof_dZ = new TProfile("prof_dZ","Profile of <d_{xy}^{1} d_{xy}^{2} / cos(#delta#phi)> versus #phi_{1}",cos_bins,-4.,4.,dxy_min,dxy_max);
	prof_dZ->GetXaxis()->SetTitle("#phi_{1}");
	prof_dZ->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2} / cos(#delta#phi)>");

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

	prof_plus_tt_d0_bs = new TProfile("prof_plus_tt_d0_bs","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}+#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_plus_tt_d0_bs->GetXaxis()->SetTitle("cos(#phi_{1}+#phi_{2})");
	prof_plus_tt_d0_bs->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");
	prof_minus_tt_d0_bs = new TProfile("prof_minus_tt_d0_bs","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}+#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_minus_tt_d0_bs->GetXaxis()->SetTitle("cos(#phi_{1}#pm#phi_{2})");
	prof_minus_tt_d0_bs->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");

	// Check number of entries in ttree and the number of vertexes
	TTree *tree = (TTree*) inputfile->Get("demo/trackTree_");
	int nentries = tree->GetEntriesFast();
  	std::cout << "\t Number of entries  = " << nentries << std::endl;
	int nvtxs = tree->GetMaximum("VtxID");
	std::cout << "\t Number of vertexes = " << nvtxs << std::endl;

	// Declaration of variables
	double ipt, ieta, iphi, idxy, ichi2, id0, id0_bs, id0_xyz, idZ_bs, itt_d0_bs, itt_d0_err_bs;
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
	tree->SetBranchAddress("dZ_bs",&idZ_bs);
	tree->SetBranchAddress("tt_d0_bs",&itt_d0_bs);
	tree->SetBranchAddress("tt_d0_err_bs",&itt_d0_err_bs);

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

		errIP_pt->Fill(ipt,itt_d0_err_bs);
		errIP_eta->Fill(ieta,itt_d0_err_bs);
		errIP_phi->Fill(iphi,itt_d0_err_bs);

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
		double	tmp_d0_xyz = -id0_xyz;
		double 	tmp_dZ_bs = idZ_bs;
		double	tmp_tt_d0_bs = itt_d0_bs;

		//std::cout<<"\t tmp_dxy= "<<tmp_dxy<<std::endl;
		h_dxy->Fill(idxy);
		h_d0->Fill(id0);
		h_bs->Fill(id0_bs);
		h_xyz->Fill(id0_xyz);

		// Second loop on tracks
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

			// Fill deltaZ TH1
			h_deltaZ->Fill(tmp_dZ_bs - idZ_bs);

			// Fill TProfiles
			prof_plus_d0 	->Fill(std::cos(iphi + tmp_phi), id0*tmp_d0 		);
			prof_minus_d0	->Fill(std::cos(iphi - tmp_phi), id0*tmp_d0 		);
			prof_plus_bs 	->Fill(std::cos(iphi + tmp_phi), id0_bs*tmp_d0_bs 	);
			prof_minus_bs	->Fill(std::cos(iphi - tmp_phi), id0_bs*tmp_d0_bs 	);
			prof_plus_xyz 	->Fill(std::cos(iphi + tmp_phi), id0_xyz*tmp_d0_xyz 	);
			prof_minus_xyz	->Fill(std::cos(iphi - tmp_phi), id0_xyz*tmp_d0_xyz 	);
			prof_plus_tt_d0_bs ->Fill(std::cos(iphi + tmp_phi), itt_d0_bs*tmp_tt_d0_bs);
			prof_minus_tt_d0_bs->Fill(std::cos(iphi - tmp_phi), itt_d0_bs*tmp_tt_d0_bs);

			if(std::abs(tmp_dZ_bs - idZ_bs) > 0.05 && std::abs(std::cos(iphi - tmp_phi)) < 0.5 ) continue;
			prof_dZ 	->Fill(tmp_phi, idxy*tmp_dxy / std::cos(iphi - tmp_phi)	);
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
   	prof_minus_d0->Fit("pol1");
   	prof_plus_d0 ->Fit("pol1");
   	prof_minus_bs->Fit("pol1");
   	prof_plus_bs ->Fit("pol1");
   	prof_minus_xyz->Fit("pol1");
   	prof_plus_xyz ->Fit("pol1");
	prof_minus_tt_d0_bs->Fit("pol1");
	prof_plus_tt_d0_bs ->Fit("pol1");

	// Retrieve fit parameters
	std::cout<<"Retrieving fit parameters...\n";
	TF1 *f_m_d0 = prof_minus_d0->GetFunction("pol1");
	TF1 *f_p_d0 = prof_plus_d0->GetFunction("pol1");
	double m_d0 = f_m_d0->GetParameter(1);
	double p_d0 = f_p_d0->GetParameter(1);

	TF1 *f_m_bs = prof_minus_bs->GetFunction("pol1");
	TF1 *f_p_bs = prof_plus_bs->GetFunction("pol1");
	f_p_bs->SetLineColor(kBlue);
	f_p_bs->SetLineColor(kRed);
	double m_bs = f_m_bs->GetParameter(1);
	double m_bs_err = f_m_bs->GetParError(1);
	double m_chi2 = (f_m_bs->GetChisquare())/(f_m_bs->GetNDF());
	double p_bs = f_p_bs->GetParameter(1);
	double p_bs_err = f_p_bs->GetParError(1);
	double p_chi2 = (f_p_bs->GetChisquare())/(f_p_bs->GetNDF());
	double sigma_x_err = 0.5*sqrt( ((m_bs_err*m_bs_err) + (p_bs_err * p_bs_err))/(m_bs - p_bs) );
	double sigma_y_err = 0.5*sqrt( ((m_bs_err*m_bs_err) + (p_bs_err * p_bs_err))/(m_bs + p_bs) );

	TF1 *f_m_xyz = prof_minus_xyz->GetFunction("pol1");
	TF1 *f_p_xyz = prof_plus_xyz->GetFunction("pol1");
	double m_xyz = f_m_xyz->GetParameter(1);
	double p_xyz = f_p_xyz->GetParameter(1);

	TF1 *f_m_tt = prof_minus_tt_d0_bs->GetFunction("pol1");
	TF1 *f_p_tt = prof_plus_tt_d0_bs ->GetFunction("pol1");
	double m_tt = f_m_tt->GetParameter(1);
	double p_tt = f_p_tt->GetParameter(1);

	std::cout<<"\n*************** - FIT RESULTS - ***************"<<std::endl;
	//std::cout<<"	- dxy - "<<std::endl;
	//std::cout<<"Sigma_x^2 = "<<m_dxy + p_dxy<<std::endl;
	//std::cout<<"Sigma_y^2 = "<<m_dxy - p_dxy<<std::endl;
	//std::cout<<"Sigma_x = "<<sqrt(m_dxy + p_dxy) * 10000<<" um"<<std::endl;
	//std::cout<<"Sigma_y = "<<sqrt(m_dxy - p_dxy) * 10000<<" um"<<std::endl;
	//std::cout<<"\n";
	std::cout<<"	- d0 - "<<std::endl;
	std::cout<<"Sigma_x^2 = "<<m_d0 - p_d0<<std::endl;
	std::cout<<"Sigma_y^2 = "<<m_d0 + p_d0<<std::endl;
	std::cout<<"Sigma_x = "<<sqrt(m_d0 - p_d0) * 10000<<" um"<<std::endl;
	std::cout<<"Sigma_y = "<<sqrt(m_d0 + p_d0) * 10000<<" um"<<std::endl;
	std::cout<<"\n";
	std::cout<<"	- bs - "<<std::endl;
	std::cout<<"m_bs = "<<m_bs<<" +/- "<<m_bs_err<<std::endl;
	std::cout<<"m_chi2 = "<<f_m_bs->GetChisquare()<<"/"<<f_m_bs->GetNDF()<<" = "<<m_chi2<<std::endl;
	std::cout<<"p_bs = "<<p_bs<<" +/- "<<p_bs_err<<std::endl;
	std::cout<<"p_chi2 = "<<f_p_bs->GetChisquare()<<"/"<<f_p_bs->GetNDF()<<" = "<<p_chi2<<std::endl;
	std::cout<<"Sigma_x^2 = "<<m_bs - p_bs<<std::endl;
	std::cout<<"Sigma_y^2 = "<<m_bs + p_bs<<std::endl;
	std::cout<<"Sigma_x = "<<sqrt(m_bs - p_bs) * 10000<<" +/- "<<sigma_x_err * 10000<<" um"<<std::endl;
	std::cout<<"Sigma_y = "<<sqrt(m_bs + p_bs) * 10000<<" +/- "<<sigma_y_err * 10000<<" um"<<std::endl;
	std::cout<<"\n";
	std::cout<<"	- xyz - "<<std::endl;
	std::cout<<"Sigma_x^2 = "<<m_xyz - p_xyz<<std::endl;
	std::cout<<"Sigma_y^2 = "<<m_xyz + p_xyz<<std::endl;
	std::cout<<"Sigma_x = "<<sqrt(m_xyz - p_xyz) * 10000<<" um"<<std::endl;
	std::cout<<"Sigma_y = "<<sqrt(m_xyz + p_xyz) * 10000<<" um"<<std::endl;
	std::cout<<"\n";
	std::cout<<"	- tt_bs - "<<std::endl;
	std::cout<<"Sigma_x^2 = "<<m_tt - p_tt<<std::endl;
	std::cout<<"Sigma_y^2 = "<<m_tt + p_tt<<std::endl;
	std::cout<<"Sigma_x = "<<sqrt(m_tt - p_tt) * 10000<<" um"<<std::endl;
	std::cout<<"Sigma_y = "<<sqrt(m_tt + p_tt) * 10000<<" um"<<std::endl;
	std::cout<<"*************************************************"<<std::endl;

	// Projection of TH2D of errIP
	TH1D * proj_errIP_pt = errIP_pt->ProjectionX();
	TH1D * proj_errIP_phi = errIP_phi->ProjectionX();
	TH1D * proj_errIP_eta = errIP_eta->ProjectionX();

	// Close file and save the results
	outfile		-> cd();

  	h_cos_plus	-> Write();
  	h_cos_minus	-> Write();

	proj_errIP_pt	-> Write();
	proj_errIP_eta	-> Write();
	proj_errIP_phi
	-> Write();

	h_dxy		-> Write();
	h_d0		-> Write();
	h_bs		-> Write();
	h_xyz		-> Write();
	h_deltaZ	-> Write();

	prof_dZ	-> Write();

	prof_plus_d0	-> Write();
	prof_minus_d0	-> Write();
	prof_plus_bs	-> Write();
	prof_minus_bs	-> Write();
	prof_plus_xyz	-> Write();
	prof_minus_xyz	-> Write();
	prof_plus_tt_d0_bs ->Write();
	prof_minus_tt_d0_bs->Write();

  	outfile		-> Close();  
  
	std::cout<<"------------ END OF MACRO ------------"<<std::endl;
	return;
}




















