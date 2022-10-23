#include <iostream>
#include <string>
#include <TFile.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TMath.h>
#include <TStyle.h>
#include <TObjArray.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TString.h>
#include <TObjString.h>
#include <TSystem.h>
#include <TLorentzVector.h>
#include <vector>
#include <cmath>
//#include "events2chain.C"
//#include "drawStyle.C"
#include "GPlotHandler.h"

//SCALE WYWOLUJE SUMW2, JESLI NIE CHCE SUMW2 TRZEBA DAC INNA OPCJE "nosw2"
//JESLI SIE CHEC NA KONIEC NAPRAWIC SUMW2 TRZEBA DAC Z OPCJA kFALSE

#define _N_PAIRS_ 2 
#define _N_CASES_ 3

void compMass () {

	TString fIn[_N_CASES_] ={"/u/mkurach/pairs/outputBig/outCaseA.root","/u/mkurach/pairs/outputBig/outCaseB.root","/u/mkurach/pairs/outputBig/outCaseC.root"}; 
	TString Case[_N_CASES_] = {"CaseA","CaseB","CaseC"};
	TString outDir = "/u/mkurach/figures_with_data/ladne/";

    TString pairsTitle[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString pairsTitlesDiff[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString histNames = "MHist";
    
	gROOT->SetBatch(kTRUE);

	//READING MY HISTOGRAMS
    TH1D* H1D[_N_CASES_][_N_PAIRS_];
          
	Int_t events = 10e6;
    Int_t XBins = 1000;
    Float_t XMin = 1;
	Float_t XMax = 1.6;
	Float_t dX = (XMax-XMin)/XBins;
    Int_t rebin = 10;

	TFile* file[_N_CASES_];
	//TCanvas* can[_N_CASES_][_N_PAIRS_];
	for(int i = 0; i < _N_CASES_; i ++) {
		file[i] = new TFile(fIn[i].Data());
		for(int j = 0; j < _N_PAIRS_; j++) {
			//can[i][j] = new TCanvas(Form("%s%s",Case[i].Data(),pairsTitlesDiff[j].Data()),Form("%s%s",Case[i].Data(),pairsTitlesDiff[j].Data()),1000,1000);
			H1D[i][j] = (TH1D*)file[i]->Get(Form("%s%s",pairsTitlesDiff[j].Data(),histNames.Data()));
			H1D[i][j]->Sumw2();
			H1D[i][j]->Rebin(rebin);
			H1D[i][j]->Scale(1.0/(events*dX*rebin));
			//can[i][j]->cd();
			//H1D[i][j]->Draw();
		}
	}

	//READING EXP HISTOGRAMS

	TFile* fileExp[_N_PAIRS_];
	TString fInExp[_N_PAIRS_] = {"exp/massPlus.root","exp/massMinus.root"};
	TString histNamesExp[_N_PAIRS_] = {"h_circ_int_mass_mult0_case1__289","h_circ_int_mass_mult0_case2__302"};
	TH1D* H1DExp[_N_PAIRS_];
	for(int i = 0; i < _N_PAIRS_; i ++){
		fileExp[i] = new TFile(fInExp[i].Data());
		H1DExp[i] = (TH1D*)fileExp[i]->Get(histNamesExp[i].Data());
	}

	//PLOTTING
	TCanvas* can[_N_PAIRS_];
	int it = 0;
	TFile *fileOut = new TFile("ladne/mass.root","RECREATE");
	Coordinates legenda{0.65,0.55,0.85,0.78};
	TString xLabels[_N_PAIRS_] = {"M_{#pi^{+}p} (GeV/c^{2})","M_{#pi^{-}p} (GeV/c^{2})"};


	for(int i = 0; i < _N_PAIRS_; i ++) {
		multiPlotCanvas(fileOut, can, it, {H1DExp[i],H1D[0][i],H1D[1][i],H1D[2][i]}, {"experiment","caseA","caseB","caseC"}, legenda, Form("%sMass",pairsTitlesDiff[i].Data()), " ", xLabels[i].Data(), "dN/dM (GeV/c^{2})^{-1}", 1, 1.6, {1, 600, 629, 414}, {21,20,20,20});


	
	}


	






gROOT->SetBatch(kFALSE);
}

