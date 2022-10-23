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


void doublePlot(TH1D *h1, TH1D *h2, TCanvas* can, TString entry1, TString entry2, TString XLabel = "") {
    setBasicStyle(); //z headera
    setCanvas(can);
    if(XLabel!="")
        h1->GetXaxis()->SetTitle(XLabel);
    h1->SetTitle("");

    

    /*Double_t max = 0;
    if(h1->GetMaximum()>max) 
        max = h1->GetMaximum();
    if(h2->GetMaximum()>max)
        max = h2->GetMaximum();
    h1->SetMaximum(1.15*max);*/

    h1->GetXaxis()->SetTitleSize(0.04);
    h1->GetYaxis()->SetTitleSize(0.04);
    h1->GetXaxis()->SetTitleFont(42);
    h1->GetYaxis()->SetTitleFont(42);
    h1->GetYaxis()->SetTitleOffset(1.2);

    h1->GetXaxis()->SetLabelFont(42);
    h1->GetYaxis()->SetLabelFont(42);
    h1->GetXaxis()->SetLabelSize(0.035);
    h1->GetYaxis()->SetLabelSize(0.035);

    h1->GetYaxis()->SetRangeUser(0,30);

   //h1->SetErrorY(0);

    h1->SetMarkerStyle(21);
    //h1->SetMarkerSize(0.8);
    h1->SetMarkerColor(kBlue+3);
    //h1->SetDrawOption("H");
    //h1->SetLineColor(kBlue);
    //h1->SetLineStyle(1);
    //h1->SetLineWidth(3);


    h2->GetXaxis()->SetTitleSize(0.04);
    h2->GetYaxis()->SetTitleSize(0.04);
    h2->GetXaxis()->SetTitleFont(42);
    h2->GetYaxis()->SetTitleFont(42);

    h2 -> GetYaxis() -> SetTitleOffset(1.2);
    h2->GetXaxis()->SetLabelFont(42);
    h2->GetYaxis()->SetLabelFont(42);
    h2->GetXaxis()->SetLabelSize(0.035);
    h2->GetYaxis()->SetLabelSize(0.035);
    h2 -> SetMarkerStyle(20);
    h2 -> SetMarkerSize(1);
    h2 -> SetMarkerColor(kRed+1);
    h2 -> SetLineColor(kRed+1);
    //h2 ->SetLineStyle(2);
    h2 ->SetLineWidth(1);

    TLegend* legend	= new TLegend(0.55,0.7,0.9,0.83, "",	"NDC");
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetLineWidth(0);
    legend->SetTextSize(0.04);
    legend->SetName("legend");
    
    legend->AddEntry(h1,entry1,"AP");
    legend->AddEntry(h2,entry2,"AP");

    can->cd();

    h1->Draw("");
    h2->Draw("same");
    

    legend->Draw("same");

}


void compMassFit () {

	TString fIn ="/u/mkurach/pairs/outputFit/outFitM.root"; 
	TString Case[_N_CASES_] = {"CaseA","CaseB","CaseC"};
	TString outDir = "/u/mkurach/figures_with_data/ladne/";

    TString pairsTitle[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString pairsTitlesDiff[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString histNames = "MFitHist";
    
	//gROOT->SetBatch(kTRUE);

	//READING MY HISTOGRAMS
    TH1D* H1D[_N_CASES_]; //tylko plusy
    TF1* fun[_N_CASES_];
    TF1* funCop[_N_CASES_];
          
	Int_t events = 10e6;
    Int_t XBins = 1000;
    Float_t XMin = 1;
	Float_t XMax = 1.6;
	Float_t dX = (XMax-XMin)/XBins;
    Int_t rebin = 10;

    Double_t minRange = 1.125;
    Double_t maxRange = 1.250;
	TFile* file = new TFile(fIn.Data());
	//TCanvas* can[_N_CASES_];
	for(int i = 0; i < _N_CASES_; i ++) {

        //can[i] = new TCanvas(Form("%s%s",Case[i].Data(),pairsTitlesDiff[0].Data()),Form("%s%s",Case[i].Data(),pairsTitlesDiff[0].Data()),1000,1000);
        H1D[i] = (TH1D*)file->Get(Form("%s%s%s",Case[i].Data(),pairsTitlesDiff[0].Data(),histNames.Data()));
        
        fun[i] = (TF1*)H1D[i]->GetFunction("fun");
        fun[i]->SetRange(minRange,maxRange);

        funCop[i] = (TF1*) H1D[i]->GetFunction("funCop");
        //H1D[i]->Sumw2();
        //H1D[i]->Rebin(rebin);
        //H1D[i]->Scale(1.0/(events*dX*rebin));
        //can[i]->cd();
        //H1D[i]->Draw();
        //funCop[i]->Draw();
		
	}

	//READING EXP HISTOGRAMS AND FUNC


	TString fInExp[_N_PAIRS_] = {"exp/massPlus.root","exp/massMinus.root"};
	TString histNamesExp[_N_PAIRS_] = {"h_circ_int_mass_mult0_case1__289","h_circ_int_mass_mult0_case2__302"};
	TH1D* H1DExp;
    TF1* funExp;
    TF1* funCopExp;

	TFile* fileExp = new TFile(fInExp[0].Data());
    H1DExp = (TH1D*)fileExp->Get(histNamesExp[0].Data());
    //can[0]->cd();
    //H1DExp->Draw();

    TFile* fileFun = new TFile("exp/massFitPlus.root");
    funExp = (TF1*)fileFun->Get("fbwr3");
    funExp->SetRange(minRange+0.01,maxRange);
    funExp->SetLineColor(kBlue+1);
    //can[0]->cd();
   // funExp->Draw();


    TFile* fileFunCop = new TFile("exp/massFitExtraPlus.root");
    funCopExp = (TF1*)fileFunCop->Get("fbwr2");
    funCopExp->SetRange(1,1.6);
    funCopExp->SetLineColor(kBlue+1);
    funCopExp->SetLineStyle(2);
    //can[1]->cd();
    //funCopExp->Draw();

    H1DExp->GetListOfFunctions()->Add(funExp);
    H1DExp->GetListOfFunctions()->Add(funCopExp);


	//PLOTTING
	TCanvas* can[_N_CASES_];
    TFile *fileOut = new TFile("ladne/massFit.root","RECREATE");

    for(int i = 0; i < _N_CASES_; i++){
        can[i] = new TCanvas(Form("%sMassFit",Case[i].Data()),Form("%sMassFit",Case[i].Data()),715,700);

        doublePlot(H1DExp,H1D[i],can[i],"experiment",Case[i].Data(),"M_{#pi^{+}p} (GeV/c^{2})");
  	    makePaveText(can[i],pairsTitle[0].Data(),0.7,0.4,0.88,0.5,0.05);
		makePaveText(can[i],"HADES Au+Au",0.6,0.6,0.7,0.7,0.03);
		makePaveText(can[i],"#sqrt{s_{NN}} = 2.42 GeV",0.6,0.57,0.7,0.67,0.03);
        makePaveText(can[i],"0 < y #leq 1.8",0.62,0.5,0.7,0.6,0.03);
        can[i]->SaveAs(Form("/u/mkurach/figures_with_data/moje/ladne/%smassFit.pdf",Case[i].Data()));
        can[i]->Write();
    }

    fileOut->Close();
    fileOut->Save();

	






//gROOT->SetBatch(kFALSE);
}

