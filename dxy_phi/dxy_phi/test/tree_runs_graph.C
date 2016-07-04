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

using namespace std;

// Global variables
double pt_cut = 1.;
double eta_cut = 1.;
int trk_hits_cut = 8;
int pix_hits_cut = 1;

int dxy_bins = 2000;
double dxy_min = -0.03;
double dxy_max = 0.03;

int cos_bins = 40;


/*vector<int> getRuns (TChain ch)
dichiari stringa

}*/

void tree_runs_graph ()
{

	std::cout<<"------------ BEGIN OF MACRO ------------"<<std::endl;

	// INPUT file and tree
	//TFile* inputfile = TFile::Open("/afs/cern.ch/work/f/fbrivio/beamSpot/CMSSW_8_0_10_patch1/src/dxy_phi/dxy_phi/crab/beamSpot/crab_Fill_5021/results/tracksFile.root", "READ");
	TFile* inputfile = TFile::Open("/afs/cern.ch/work/f/fbrivio/beamSpot/CMSSW_8_0_10_patch1/src/dxy_phi/dxy_phi/crab/beamSpot/crab_Fill_4990/results/tracksFile.root", "READ");
  	std::cout << "\t Input file: " << inputfile->GetName() << std::endl;

	// OUTPUT file
	//TFile* outfile = TFile::Open("Fill5021_graphs.root","RECREATE");
	TFile* outfile = TFile::Open("Fill4990_graphs.root","RECREATE");
  	std::cout << "\t Output file: " << outfile->GetName() << std::endl;

	// TH2D histograms
	double pt_bins[63] = {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0 , 5.5, 6.0 , 6.5, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};
	TH2D *errIP_pt  = new TH2D("errIP_pt" ,"",62,pt_bins,100,0.,2.);
	TH2D *errIP_eta = new TH2D("errIP_eta","",40.,-2.5,2.5,100,0.,2.);
	TH2D *errIP_phi = new TH2D("errIP_phi","",50,-3.5,3.5,100,0.,2.);

	// TH1D per IP
	h_bs 	 = new 	TH1D("h_bs", "h_d0_bs", 100, -0.05, 0.05);

	// TProfiles
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

	prof_plus_tt_d0_bs = new TProfile("prof_plus_tt_d0_bs","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}+#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_plus_tt_d0_bs->GetXaxis()->SetTitle("cos(#phi_{1}+#phi_{2})");
	prof_plus_tt_d0_bs->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");
	prof_minus_tt_d0_bs = new TProfile("prof_minus_tt_d0_bs","Profile of <d_{xy}^{1} d_{xy}^{2}> versus cos(#phi_{1}+#phi_{2})",cos_bins,-1.,1.,dxy_min,dxy_max);
	prof_minus_tt_d0_bs->GetXaxis()->SetTitle("cos(#phi_{1}#pm#phi_{2})");
	prof_minus_tt_d0_bs->GetYaxis()->SetTitle("<d_{xy}^{1} d_{xy}^{2}>");

	// TGraph
	run_graph_x = new TGraphErrors();
	run_graph_x->SetName("Sigma X");
	run_graph_x->SetTitle("#sigma_{x}");
	run_graph_y = new TGraphErrors();
	run_graph_y->SetName("Sigma Y");
	run_graph_y->SetTitle("#sigma_{y}");

	// Check number of entries in ttree and the number of vertexes
	TTree *tree = (TTree*) inputfile->Get("demo/trackTree_");
	int nentries = tree->GetEntriesFast();
  	std::cout << "\t Number of entries  = " << nentries << std::endl;
	//int nvtxs = tree->GetMaximum("VtxID");
	//std::cout << "\t Number of vertexes = " << nvtxs << std::endl;
	int min_run = tree->GetMinimum("Run");
	int max_run = tree->GetMaximum("Run");
	std::cout << "\t Run numbers: "<<min_run<<" - "<<max_run<<std::endl;

	int point = 0;
	int tmp_run = min_run;
	int Runi = 0;

	// Declaration of variables
	double ipt, ieta, iphi, id0_bs, itt_d0_bs, itt_d0_err_bs;
	int iPix_HITs, iTrack_HITs, iVtxID, iRun;

	// Access branches of ttree
	tree->SetBranchAddress("Run",&iRun);			// Branches for loops
	tree->SetBranchAddress("VtxID",&iVtxID);
	tree->SetBranchAddress("pt",&ipt);			// Branches for track selection
	tree->SetBranchAddress("eta",&ieta);
	tree->SetBranchAddress("Pix_HITs",&iPix_HITs);
	tree->SetBranchAddress("Track_HITs",&iTrack_HITs);
	tree->SetBranchAddress("phi",&iphi);			// Branches for measure
	tree->SetBranchAddress("d0_bs",&id0_bs);
	tree->SetBranchAddress("tt_d0_bs",&itt_d0_bs);
	tree->SetBranchAddress("tt_d0_err_bs",&itt_d0_err_bs);

	// Loop on tracks
	std::cout<<" - Begin of Track Loop - "<<std::endl;
	int after_cuts = 0;

	int first_run = 0;
	int last_run = 0;
	for (int i = 0; i < nentries; ++i)
	{
		tree->GetEntry(i);

		if(i%100000 == 0) std::cout<<"Track: "<<i<<" - run - tmp_run: "<<iRun<<" - "<<tmp_run<<"\n";

		errIP_pt->Fill(ipt,itt_d0_err_bs);
		errIP_eta->Fill(ieta,itt_d0_err_bs);
		errIP_phi->Fill(iphi,itt_d0_err_bs);
		
		// Track selection (pt>1 - |eta|<1 - 8Hits - 1PixHit)
		if( (ipt > pt_cut) && (std::abs(ieta) < eta_cut) && (iTrack_HITs >= trk_hits_cut) && (iPix_HITs >= pix_hits_cut) ) 
		{

		after_cuts += 1;

		// Temporary variables
		int 	tmp_vtx = iVtxID;
		double 	tmp_phi = iphi;
		double	tmp_d0_bs = id0_bs;
		double	tmp_tt_d0_bs = itt_d0_bs;
		Runi  = iRun;

		h_bs->Fill(id0_bs);

		// Second loop on tracks
		for (int j = i+1; j< nentries; ++j)
		{
			tree->GetEntry(j);

			// Check if the track is from same vertex
			if (iVtxID > tmp_vtx) break;

			// Track + vertex selection
			if ( (iVtxID == tmp_vtx) && (ipt > pt_cut) && (std::abs(ieta)< eta_cut) && (iTrack_HITs >= trk_hits_cut) && (iPix_HITs >= pix_hits_cut) )
			{

			// Fill TProfiles
			prof_plus_bs 	->Fill(std::cos(iphi + tmp_phi), id0_bs*tmp_d0_bs 	);
			prof_minus_bs	->Fill(std::cos(iphi - tmp_phi), id0_bs*tmp_d0_bs 	);
			prof_plus_tt_d0_bs ->Fill(std::cos(iphi + tmp_phi), itt_d0_bs*tmp_tt_d0_bs);
			prof_minus_tt_d0_bs->Fill(std::cos(iphi - tmp_phi), itt_d0_bs*tmp_tt_d0_bs);

			if (iRun == min_run) first_run += 1;
			else if (iRun == max_run) last_run += 1;

			} //conditions for second loop
			
		} //end of second loop on tracks

		} //coditions for first loop

		if (tmp_run == Runi)
		{
			tmp_vtx      = 0;
			tmp_phi      = 0.;
			tmp_d0_bs    = 0.;
			tmp_tt_d0_bs = 0.;
			continue;
		}	
		else
		{
			std::cout<<"\n - NEW POINT IN GRAPH, run - tmp_run: "<<Runi<<" - "<<tmp_run<<std::endl;
		        try{
			prof_minus_bs->Fit("pol1");
   			prof_plus_bs ->Fit("pol1");

			TF1 *f_m_bs = prof_minus_bs->GetFunction("pol1");
			TF1 *f_p_bs = prof_plus_bs->GetFunction("pol1");
			f_p_bs->SetLineColor(kBlue);
			f_p_bs->SetLineColor(kRed);
			double m_bs = f_m_bs->GetParameter(1);
			double m_bs_err = f_m_bs->GetParError(1);
			double p_bs = f_p_bs->GetParameter(1);
			double p_bs_err = f_p_bs->GetParError(1);
			double sigma_x_err = 0.5*sqrt( ((m_bs_err*m_bs_err) + (p_bs_err * p_bs_err))/(m_bs - p_bs) );
			double sigma_y_err = 0.5*sqrt( ((m_bs_err*m_bs_err) + (p_bs_err * p_bs_err))/(m_bs + p_bs) );

			std::cout<<"Sigma_x = "<<sqrt(m_bs - p_bs) * 10000<<" +/- "<<sigma_x_err * 10000<<" um"<<std::endl;
			std::cout<<"Sigma_y = "<<sqrt(m_bs + p_bs) * 10000<<" +/- "<<sigma_y_err * 10000<<" um"<<std::endl;

			std::cout<<"\t Run:"<<tmp_run<<std::endl;
			std::cout<<"\t x:"<<sqrt(m_bs - p_bs)*10000<<std::endl;
			std::cout<<"\t y:"<<sqrt(m_bs + p_bs)*10000<<std::endl;
			run_graph_x->SetPoint(point, tmp_run, sqrt(m_bs - p_bs)*10000);
			run_graph_x->SetPointError(point,0., sigma_x_err*10000);
			run_graph_y->SetPoint(point, tmp_run, sqrt(m_bs + p_bs)*10000);
			run_graph_y->SetPointError(point,0., sigma_y_err*10000);

			prof_minus_bs->Reset();
			prof_plus_bs ->Reset();

			tmp_run = Runi;
			point++;

			// Clear temporary variables
			tmp_vtx      = 0;
			tmp_phi      = 0.;
			tmp_d0_bs    = 0.;
			tmp_tt_d0_bs = 0.;
			}
			catch (std::exception& e)
			{
				std::cerr << "Exception catched : " << e.what() << std::endl;
				continue;
			}
		} //end of else to print beamspot to tgraph
		
	} //end of first loop on tracks

	std::cout<<" - End of Track Loop - \n";
	std::cout<<"\t Number of events after cuts = "<<after_cuts<<"\n";
	std::cout<<"\t \t First Run events : "<<first_run<<"\n";
	std::cout<<"\t \t Last Run events  : "<<last_run<<"\n";

	// Fit the TProfiles
	std::cout<<"Fitting...\n";
   	prof_minus_bs->Fit("pol1");
   	prof_plus_bs ->Fit("pol1");
	prof_minus_tt_d0_bs->Fit("pol1");
	prof_plus_tt_d0_bs ->Fit("pol1");

	// Retrieve fit parameters
	std::cout<<"Retrieving fit parameters...\n";
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

	std::cout<<"-------- LAST ONE ---------\n";
	std::cout<<"\n - NEW POINT IN GRAPH, run - tmp_run: "<<Runi<<" - "<<tmp_run<<std::endl;
	std::cout<<"Sigma_x = "<<sqrt(m_bs - p_bs) * 10000<<" +/- "<<sigma_x_err * 10000<<" um"<<std::endl;
	std::cout<<"Sigma_y = "<<sqrt(m_bs + p_bs) * 10000<<" +/- "<<sigma_y_err * 10000<<" um"<<std::endl;
	run_graph_x->SetPoint(point, tmp_run, sqrt(m_bs - p_bs)*10000);
	run_graph_x->SetPointError(point,0., sigma_x_err*10000);
	run_graph_y->SetPoint(point, tmp_run, sqrt(m_bs + p_bs)*10000);
	run_graph_y->SetPointError(point,0., sigma_y_err*10000);

	TF1 *f_m_tt = prof_minus_tt_d0_bs->GetFunction("pol1");
	TF1 *f_p_tt = prof_plus_tt_d0_bs ->GetFunction("pol1");
	double m_tt = f_m_tt->GetParameter(1);
	double p_tt = f_p_tt->GetParameter(1);

	std::cout<<"\n*************** - FIT RESULTS - ***************"<<std::endl;
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
	outfile			-> cd();

	proj_errIP_pt		-> Write();
	proj_errIP_eta		-> Write();
	proj_errIP_phi		-> Write();

	h_bs			-> Write();
	
	prof_plus_bs		-> Write();
	prof_minus_bs		-> Write();
	prof_plus_tt_d0_bs 	-> Write();
	prof_minus_tt_d0_bs	-> Write();

	run_graph_x		-> Write();
	run_graph_y		-> Write();
	
  	outfile			-> Close();  
  
	std::cout<<"------------ END OF MACRO ------------"<<std::endl;
	return;
}




















