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

void dxy_fitter_2 ()
{

	std::cout<<"------------ BEGIN OF MACRO ------------"<<std::endl;

	// Output file
	//TFile* outfile = TFile::Open("TT_graphs.root","RECREATE");
	TFile* outfile = TFile::Open("graphs.root","RECREATE");
  	std::cout << "\t Output file: " << outfile->GetName() << std::endl;

	// TH2D histograms
	h_cos_plus = new TH2D("cos_plus","TH2D of <dxy_{1}*dxy_{2}> versus cos(#phi_{1}+#phi_{2})",40,-1.,1.,dxy_bins,dxy_min,dxy_max);
	h_cos_plus->GetXaxis()->SetTitle("cos(#phi_{1}+#phi_{2})");
	h_cos_plus->GetYaxis()->SetTitle("<dxy_{1}*dxy_{2}>");
	h_cos_minus = new TH2D("cos_minus","TH2D of <dxy_{1}*dxy_{2}> versus cos(#phi_{1}-#phi_{2})",40,-1.,1.,dxy_bins,dxy_min,dxy_max);
	h_cos_minus->GetXaxis()->SetTitle("cos(#phi_{1}-#phi_{2})");
	h_cos_minus->GetYaxis()->SetTitle("<dxy_{1}*dxy_{2}>");

	// TProfiles
	prof_plus = new TProfile("prof_plus","Profile of <dxy_{1}*dxy_{2}> versus cos(#phi_{1}+#phi_{2})",40,-1.,1.,dxy_min,dxy_max);
	prof_plus->GetXaxis()->SetTitle("cos(#phi_{1}+#phi_{2})");
	prof_plus->GetYaxis()->SetTitle("<dxy_{1}*dxy_{2}>");
	prof_minus = new TProfile("prof_minus","Profile of <dxy_{1}*dxy_{2}> versus cos(#phi_{1}-#phi_{2})",40,-1.,1.,dxy_min,dxy_max);
	prof_minus->GetXaxis()->SetTitle("cos(#phi_{1}-#phi_{2})");
	prof_minus->GetYaxis()->SetTitle("<dxy_{1}*dxy_{2}>");

	// Input file and tree
	//TFile* inputfile = TFile::Open("/afs/cern.ch/work/f/fbrivio/beamSpot/CMSSW_8_0_4/src/dxy_phi/dxy_phi/test/tracksFile.root", "READ");
	//TFile* inputfile = TFile::Open("TT_tracksFile.root", "READ");
	TFile* inputfile = TFile::Open("tracksFile.root", "READ");
  	std::cout << "\t Input file: " << inputfile -> GetName() << std::endl;
  	if (!inputfile) 
	{
    	std::cout << " *** file not found *** " << std::endl;
    	return;
  	}

	// Check number of entries in ttree and the number of vertexes
	TTree *tree = (TTree*) inputfile->Get("demo/trackTree_");
	int nentries = tree->GetEntriesFast();
  	std::cout << "\t Number of entries  = " << nentries << std::endl;
	int nvtxs = tree->GetMaximum("VtxID");
	std::cout << "\t Number of vertexes = " << nvtxs << std::endl;

	// Declaration of variables
	double ipt, ieta, iphi, idxy, ichi2;
	int iPix_HITs, iTrack_HITs, iVtxID;
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
	tree->SetBranchAddress("VtxID",&iVtxID);

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
		//if (ipt>= 1. && std::abs(ieta) <= 1. && iTrack_HITs >= 8 && iPix_HITs >= 1)
		//{
		after_cuts += 1;

		//std::cout<<"First track: "<<i<<" - Vertex: "<<iVtxID<<std::endl;

		// Temporary variables
		int 	tmp_vtx = iVtxID;
		double 	tmp_phi = iphi;
		double 	tmp_dxy = idxy;

		// Another loop on tracks
		for (int j = i+1; j< nentries; ++j)
		{
			tree->GetEntry(j);
			//std::cout<<"\tSecond track: "<<j<<" - Vertex: "<<iVtxID<<" - tmpvtx: "<<tmp_vtx<<std::endl;
			if (j % 1000 == 0) std::cout<<"Analysing event: "<<j<<std::endl;

			// Check if the track is from same vertex
			if (iVtxID > tmp_vtx) break;
			//{std::cout<<"\t \t \t BREAKING"<<std::endl; break;}

			// Track + vertex selection
			if ( (iVtxID != tmp_vtx) || (ipt < pt_cut) || (std::abs(ieta)> eta_cut) || (iTrack_HITs < trk_hits_cut) || (iPix_HITs < pix_hits_cut) ) continue; 
				//|| (iQuality != 1) || (ichi2 > 10.) || (ichi2 < 0.) ) continue;
			
			//std::cout<<"\t \t \t ACCEPTED"<<std::endl;

			h_cos_plus ->Fill(std::cos(iphi + tmp_phi), idxy*tmp_dxy );
			h_cos_minus->Fill(std::cos(iphi - tmp_phi), idxy*tmp_dxy );

			prof_plus ->Fill(std::cos(iphi + tmp_phi), idxy*tmp_dxy );
			prof_minus->Fill(std::cos(iphi - tmp_phi), idxy*tmp_dxy );
		}
		tmp_vtx = 0;
		tmp_phi = 0.;
		tmp_dxy = 0.;

		//}
		
	}

	std::cout<<"\t Number of events after cuts = "<<after_cuts<<std::endl;

	// TProfile from the TH2Ds
	std::cout<<"Profiling...\n";
	TProfile *prof_cos_minus = h_cos_minus->ProfileX();
	TProfile *prof_cos_plus  = h_cos_plus ->ProfileX();

	// Fit the TProfiles
	std::cout<<"Fitting...\n";
   	prof_minus->Fit("pol1");
   	prof_plus ->Fit("pol1");

	// Retrieve fit parameters
	/*root[] TF1 *fit = hist->GetFunction(function_name);
	root[] Double_t chi2 = fit->GetChisquare();
	// value of the first parameter
	root[] Double_t p1 = fit->GetParameter(0);
	// error of the first parameter
	root[] Double_t e1 = fit->GetParError(0);*/

	TF1 *fit_minus = prof_minus->GetFunction("pol1");
	fit_minus->SetLineColor(kBlue);
	double q_minus = fit_minus->GetParameter(0);
	double m_minus = fit_minus->GetParameter(1);

	TF1 *fit_plus = prof_plus->GetFunction("pol1");
	double q_plus = fit_plus->GetParameter(0);
	double m_plus = fit_plus->GetParameter(1);

	std::cout<<"\n*************** - FIT RESULTS - ***************"<<std::endl;
	std::cout<<"Cos minus fit: y = "<<m_minus<<" x + "<<q_minus<<std::endl;
	std::cout<<"Cos plus fit:  y = "<<m_plus<<" x + "<<q_plus<<std::endl;
	std::cout<<"\n";
	std::cout<<"Sigma_x^2 = "<<m_minus + m_plus<<std::endl;
	std::cout<<"Sigma_y^2 = "<<m_minus - m_plus<<std::endl;
	std::cout<<"\n";
	std::cout<<"Sigma_x = "<<sqrt(m_minus + m_plus)<<std::endl;
	std::cout<<"Sigma_y = "<<sqrt(m_minus - m_plus)<<std::endl;
	std::cout<<"*************************************************"<<std::endl;

	// Close file and save the results
	outfile		-> cd();
  	h_cos_plus	-> Write();
  	h_cos_minus	-> Write();
	prof_cos_plus	-> Write();
	prof_cos_minus	-> Write();
	prof_plus	-> Write();
	prof_minus	-> Write();
  	outfile		-> Close();  
  
	std::cout<<"------------ END OF MACRO ------------"<<std::endl;
	return;
}




















