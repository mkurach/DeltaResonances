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


#define _N_PAIRS_ 2 
#define _N_CASES_ 3

void makePaveText(TVirtualPad* can, TString text, double x1, double y1, double x2, double y2, double size, Int_t color=kBlack) {
    TPaveText *description=new TPaveText(x1,y1,x2,y2,"NDC");
    description->SetLineWidth(0);
  description->AddText(text);
  description->SetTextSize(size);
  description->SetBorderSize(0.0);
  description->SetTextFont(42);
  description->SetTextColor(color);
  description->SetFillColor(0);
  description->SetFillStyle(0);
  description->SetTextAlign(13);
      can->cd();
    description->Draw("same");
}

void doublePlot(TH1D *h1, TH1D *h2, TCanvas* can, TString entry1, TString entry2, Double_t dX, int rebin,TString XLabel = "") {
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

    /*h1->GetXaxis()->SetTitleSize(0.04);
    h1->GetYaxis()->SetTitleSize(0.04);
    h1->GetXaxis()->SetTitleFont(42);
    h1->GetYaxis()->SetTitleFont(42);
    //

    h1->GetXaxis()->SetLabelFont(42);
    h1->GetYaxis()->SetLabelFont(42);
    h1->GetXaxis()->SetLabelSize(0.035);
    h1->GetYaxis()->SetLabelSize(0.035);*/

    //h1->GetYaxis()->SetRangeUser(0,1000);

   //h1->SetErrorY(0);
    h1->GetYaxis()->SetTitleOffset(0.8);
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

    //h2 -> GetYaxis() -> SetTitleOffset(1.2);
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

    //h2->GetFunction("fun")->SetParameter(1,h2->GetFunction("fun")->GetParameter(1)/(10e6*dX*rebin));
    //h2->GetFunction("fun")->SetLineColor(kViolet);

    TLegend* legend	= new TLegend(0.53,0.7,0.9,0.83, "",	"NDC");
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetLineWidth(0);
    legend->SetTextSize(0.04);
    legend->SetName("legend");

    legend->AddEntry(h2,entry2,"AP");
    legend->AddEntry(h1,entry1,"AP");


    can->cd();

    h1->Draw("");
    h2->Draw("same");
    

    legend->Draw("same");

}

void compPtRangeY() {

    TString fIn[_N_CASES_] ={"/u/mkurach/pairs/outputFit/outFitPtYCaseA.root","/u/mkurach/pairs/outputFit/outFitPtYCaseB.root","/u/mkurach/pairs/outputFit/outFitPtYCaseC.root"}; 
	TString Case[_N_CASES_] = {"CaseA","CaseB","CaseC"};
	TString outDir = "/u/mkurach/figures_with_data/ladne/";

    TString pairsTitle[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString pairsTitlesDiff[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString histNames = "PtYHist5";


    //READING MY HISTOGRAMS
    TH1D* H1D[_N_CASES_]; //tylko plusy
    TF1* fun[_N_CASES_];
    TF1* funCop[_N_CASES_];
        
    Double_t minRange = 0.4;
    Double_t maxRange = 1.4;

    Int_t events = 10e6;
    Int_t XBins = 1000;
    Float_t XMin = 1;
	Float_t XMax = 1.6;
	Float_t dX = (XMax-XMin)/XBins;
    Int_t rebin = 4;

    TFile* file[_N_CASES_];
	//TCanvas* can[_N_CASES_];
	for(int i = 0; i < _N_CASES_; i ++) {
        file[i] = new TFile(fIn[i].Data());
        //can[i] = new TCanvas(Form("%s%s",Case[i].Data(),pairsTitlesDiff[0].Data()),Form("%s%s",Case[i].Data(),pairsTitlesDiff[0].Data()),1000,1000);
        H1D[i] = (TH1D*)file[i]->Get(Form("%s%s",pairsTitlesDiff[0].Data(),histNames.Data()));
        //H1D[i]->GetFunction("fun")->SetParameter(1,H1D[i]->GetFunction("fun")->GetParameter(1)/(events*dX*rebin));

        
        fun[i] = (TF1*)H1D[i]->GetFunction("fun");
        fun[i]->SetRange(minRange,maxRange);
        //H1D[i]->Fit("fun","Q","Q",0.4,1.4);


        funCop[i] = (TF1*) H1D[i]->GetFunction("funCop");
        //H1D[i]->Sumw2();
        H1D[i]->Rebin(rebin);
        H1D[i]->Scale(1.0/rebin);
        //can[i]->cd();
        //H1D[i]->Draw("");
        //fun[i]->Draw();
		
	}

    //READING EXP HISTOGRAMS AND FUNC


	TString fInExp = "exp/ptRange.root";
	TString histNamesExp = "pj_pt_deltamass_circ_mult0_case0_rap5";
	TH1D* H1DExp;
    TF1* funExp;
    TF1* funCopExp;

	TFile* fileExp = new TFile(fInExp.Data());
    H1DExp = (TH1D*)fileExp->Get(histNamesExp.Data());
    H1DExp->Scale(1./1e5);
    H1DExp->GetYaxis()->SetRangeUser(0,3.2);
    //can[0]->cd();
    //H1DExp->Draw();

    TFile* fileFun = new TFile("exp/ptRangeFit.root");
    funExp = (TF1*)fileFun->Get("fB");
    funExp->SetParameter(0,funExp->GetParameter(0)/1e5);
    //funExp->SetRange(minRange+0.01,maxRange);
    funExp->SetLineColor(kBlue+1);
    //can[1]->cd();
    //funExp->Draw();


    TFile* fileFunCop = new TFile("exp/ptRangeFitExtra.root");
    funCopExp = (TF1*)fileFunCop->Get("fBFull");
    funCopExp->SetParameter(0,funCopExp->GetParameter(0)/1e5);
    //funCopExp->SetRange(1,1.6);
    funCopExp->SetLineColor(kBlue+1);
    //funCopExp->SetLineStyle(2);
    //can[2]->cd();
    //funCopExp->Draw();

    H1DExp->GetListOfFunctions()->Add(funExp);
    H1DExp->GetListOfFunctions()->Add(funCopExp);

    //PLOTTING
	TCanvas* can[_N_CASES_];
    TFile *fileOut = new TFile("ladne/ptRangeFit.root","RECREATE");

    for(int i = 0; i < _N_CASES_; i++){
        can[i] = new TCanvas(Form("%sPtOneRange",Case[i].Data()),Form("%sPtOneRange",Case[i].Data()),715,700);        
        doublePlot(H1DExp,H1D[i],can[i],"experiment",Form("%s (scaled)",Case[i].Data()),dX,rebin,"p_{T} (GeV/c)");
        makePaveText(can[i],"0.74#leq y<0.84",0.63,0.6,0.83,0.7,0.03);
        makePaveText(can[i],"1.1<M_{#pi^{+}p}<1.4 GeV/c^{2}",0.6,0.55,0.8,0.65,0.03);
        makePaveText(can[i],"#pi^{+}p",0.7,0.44,0.88,0.55,0.05);
        can[i]->SaveAs(Form("/u/mkurach/figures_with_data/moje/ladne/%sptRangeFit.png",Case[i].Data()));
        can[i]->SaveAs(Form("/u/mkurach/figures_with_data/moje/ladne/%sptRangeFit.pdf",Case[i].Data()));
        can[i]->Write();
    }

    fileOut->Close();
    fileOut->Save();

}


