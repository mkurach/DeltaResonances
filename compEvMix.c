#include <iostream>
#include <fstream>
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
#include "events2chain.C"
#include "drawStyle.C"

#define _N_PAIRS_ 2
#define _N_CASES_ 3

void styleSet(){ //od Mateusza
  gStyle->SetPalette(kRainBow);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(5);
  gStyle->SetErrorX(0);     
  gStyle->SetLineStyleString(22,"80 18 12 18 12 12"); // special style for the line
  gStyle->SetEndErrorSize(5);   // define end width of error bars
  gStyle->SetCanvasColor(0);
  gStyle->SetPadColor(0);
}


void doublePlot(TH1D *gr1, TH1D *gr2, TCanvas* can, TString entry1, TString entry2, TString XLabel = "") {
    styleSet();
    if(XLabel!="")
        gr1->GetXaxis()->SetTitle(XLabel);

    /*Double_t max = 0;
    if(gr1->GetMaximum()>max) 
        max = gr1->GetMaximum();
    if(gr2->GetMaximum()>max)
        max = gr2->GetMaximum();
    gr1->SetMaximum(1.15*max);*/

    gr1->GetXaxis()->SetTitleSize(0.04);
    gr1->GetYaxis()->SetTitleSize(0.04);
    gr1->GetXaxis()->SetTitleFont(42);
    gr1->GetYaxis()->SetTitleFont(42);
    gr1->GetYaxis()->SetTitleOffset(1.2);

    gr1->GetXaxis()->SetLabelFont(42);
    gr1->GetYaxis()->SetLabelFont(42);
    gr1->GetXaxis()->SetLabelSize(0.035);
    gr1->GetYaxis()->SetLabelSize(0.035);

   //gr1->SetErrorY(0);

    //gr1->SetMarkerStyle(20);
    //gr1->SetMarkerSize(0.8);
    //gr1->SetMarkerColor(kBlue);
    //gr1->SetDrawOption("H");
    gr1->SetLineColor(kBlue);
    gr1->SetLineStyle(1);
    gr1->SetLineWidth(3);


    gr2->GetXaxis()->SetTitleSize(0.04);
    gr2->GetYaxis()->SetTitleSize(0.04);
    gr2->GetXaxis()->SetTitleFont(42);
    gr2->GetYaxis()->SetTitleFont(42);

    gr2 -> GetYaxis() -> SetTitleOffset(1.2);
    gr2->GetXaxis()->SetLabelFont(42);
    gr2->GetYaxis()->SetLabelFont(42);
    gr2->GetXaxis()->SetLabelSize(0.035);
    gr2->GetYaxis()->SetLabelSize(0.035);
    gr2 -> SetMarkerStyle(20);
    gr2 -> SetMarkerSize(1);
    gr2 -> SetMarkerColor(kRed);
    gr2 -> SetLineColor(kRed);
    //gr2 ->SetLineStyle(2);
    gr2 ->SetLineWidth(1);

    TLegend* legend	= new TLegend(0.5,0.65,0.9,0.9, "",	"brNDC");
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetLineWidth(0);
    legend->SetTextSize(0.04);
    legend->SetName("legend");
    
    legend->AddEntry(gr1,entry1);
    legend->AddEntry(gr2,entry2);

    can->cd();

    gr1->Draw("C hist");
    gr2->Draw("same");
    

    legend->Draw("same");

}
void makePaveText(TCanvas *can, TString text, double x1, double y1, double x2, double y2, double f = 0.05) { //1 - lewy gorny, 2 - prawy dolny, x i y rosna normalnie, nie jak w javie 
    TPaveText *pt = setOPT_text2(text,x1,y1,x2,y2,kBlack,f);
    can->cd();
    pt->Draw("same");

}

void createGraphs() {

    //READING MY HISTOGRAMS
    TH1D* hist[_N_CASES_][_N_PAIRS_];//3 cases, 2 pairs per case
    TGraph* grHist[_N_CASES_][_N_PAIRS_];

    Int_t events = 10e6;
    Int_t XBins = 1000;
    Float_t XMin = 1;
	Float_t XMax = 1.6;
	Float_t dX = (XMax-XMin)/XBins;
    Float_t scale = 1.0/(events*dX);
    Int_t rebin = 10;

    TFile* files[_N_CASES_];
    TString fileNames[_N_CASES_]= {"outputBig/outCaseA.root","outputBig/outCaseB.root","outputBig/outCaseC.root"};
    TString pairsTitles[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString pairsNames[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString casesNames[_N_CASES_] = {"CaseA","CaseB","CaseC"};

    for(int i = 0; i < _N_CASES_; i++){
        files[i] = new TFile(fileNames[i].Data());
        for(int j = 0; j < _N_PAIRS_; j++){
            hist[i][j] = (TH1D*)files[i]->Get(Form("%sMHist",pairsTitles[j].Data()));
            hist[i][j]->Rebin(rebin);
            hist[i][j]->Scale(scale/rebin);
            //hist[i][j]->Scale(scale);
           //hist[i][j]->Rebin(rebin);

            grHist[i][j] = new TGraph(hist[i][j]);
            grHist[i][j]->GetYaxis()->SetTitle("dN/dM (GeV/c^{2})^{-1}");

        }
    } 
    
    
    //READING FROM MIXED EVENTS

    TFile* filesEvMix[_N_CASES_];
    TString filesEvMixNames[_N_CASES_] = {"outputEvMix/outCaseAEvMix.root","outputEvMix/outCaseBEvMix.root","outputEvMix/outCaseCEvMix.root"};

    TH1D* histBack[_N_CASES_][_N_PAIRS_];
    TH1D* histSigBack[_N_CASES_][_N_PAIRS_];



    for(int i = 0; i < _N_CASES_; i++) {
        filesEvMix[i] = new TFile(filesEvMixNames[i]);
        for(int j = 0; j < _N_PAIRS_; j++) {
            histBack[i][j] = (TH1D*)filesEvMix[i]->Get(Form("%sBack",pairsTitles[j].Data()));
            histSigBack[i][j] = (TH1D*)filesEvMix[i]->Get(Form("%sSigBack",pairsTitles[j].Data()));

            //histEvMix[i][j] = (TH1D*)filesEvMix[i]->Get(Form("%sDiffHist",pairsTitles[j].Data()));
           //hist[i][j]->Rebin(rebin);
            //hist[i][j]->Scale(scale/rebin);

            //grEvMix[i][j] = new TGraph(histEvMix[i][j]);
        }
    }

    //SCALING AND CREATING SIG
    
    TH1D* histEvMix[_N_CASES_][_N_PAIRS_];
    TGraph* grEvMix[_N_CASES_][_N_PAIRS_];
    Int_t minRange = histBack[0][0]->FindBin(1.3);
    Int_t maxRange = histBack[0][0]->FindBin(1.4);

    XMax = 1.7;
    dX = (XMax-XMin)/XBins;
    scale = 1.0/(events*dX);
   
    for(int i = 0; i < _N_CASES_; i++) {
        for(int j = 0; j < _N_PAIRS_; j++) {
            histEvMix[i][j] = (TH1D*) histBack[i][j]->Clone(Form("%s%sSig",casesNames[i].Data(),pairsTitles[j].Data()));
            histEvMix[i][j]->Scale(-histSigBack[i][j]->Integral(minRange,maxRange) / histBack[i][j]->Integral(minRange,maxRange));
            histEvMix[i][j]->Add(histSigBack[i][j]);

            histEvMix[i][j]->Rebin(rebin);
            histEvMix[i][j]->Scale(scale/rebin);
            //histEvMix[i][j]->Scale(scale);
            //histEvMix[i][j]->Rebin(rebin);
            grEvMix[i][j] = new TGraph(histEvMix[i][j]);

        }
    }

    
    //COMPARING AND PLOTTING
    TCanvas* can[_N_CASES_][_N_PAIRS_];

    for (int i = 0; i < _N_CASES_; i ++){ //for each case
        for(int j = 0; j < _N_PAIRS_; j++){ //for each pair
            can[i][j] = new TCanvas(Form("%s%s",casesNames[i].Data(),pairsTitles[j].Data()),Form("%s%s",casesNames[i].Data(),pairsTitles[j].Data()),1000,1000);
            doublePlot(hist[i][j],histEvMix[i][j],can[i][j],"pairs from pid matching ","pairs from events mixing","M (GeV/c^{2})");
            makePaveText(can[i][j],casesNames[i].Data(),0.73,0.5,0.99,0.6);
            makePaveText(can[i][j],pairsNames[j].Data(),0.73,0.45,0.99,0.5);
            can[i][j]->SaveAs(Form("outputEvMix/%s%sEvMix.png",casesNames[i].Data(),pairsTitles[j].Data()));
        }
    }





}

void compEvMix() {
    createGraphs();
}