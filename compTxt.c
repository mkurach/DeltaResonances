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

//makro for reading txt file and comparing article figure with my histograms

int colors[]={1, 600, 629, 414, 802, 880, 819, 922,433,618}; // kBlack, kBlue, kRed, kGreen-2, kOrange+2, kGray, kViolet, kSpring
int markers[]= {20,21,24,25,28,34,47,43}; 

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
void doublePlot(TGraph *gr1, TGraph *gr2, TCanvas* can, TString entry1, TString entry2, TString XLabel = "") {
    styleSet();
    if(XLabel!="")
        gr1->GetXaxis()->SetTitle(XLabel);

    Double_t max = gr2->GetHistogram()->GetMaximum();
    cout<<max<<endl;
    //if(gr1->GetMaximum()>max) 
        //max = gr1->GetMaximum();
    //if(gr2->GetMaximum()>max)
        //max = gr2->GetMaximum();
    //gr1->GetYaxis()->SetRangeUser(0,max);

    gr1->GetXaxis()->SetTitleSize(0.04);
    gr1->GetYaxis()->SetTitleSize(0.04);
    gr1->GetXaxis()->SetTitleFont(42);
    gr1->GetYaxis()->SetTitleFont(42);
    gr1->GetYaxis()->SetTitleOffset(1.2);

    gr1->GetXaxis()->SetLabelFont(42);
    gr1->GetYaxis()->SetLabelFont(42);
    gr1->GetXaxis()->SetLabelSize(0.035);
    gr1->GetYaxis()->SetLabelSize(0.035);

    gr1->SetMarkerStyle(20);
    gr1->SetMarkerSize(0.8);
    gr1->SetMarkerColor(kBlue);
    gr1->SetLineColor(kBlue);


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
    gr2 -> SetMarkerSize(0.8);
    gr2 -> SetMarkerColor(kRed);
    gr2 -> SetLineColor(kRed);

    TLegend* legend	= new TLegend(0.5,0.65,0.9,0.9, "",	"brNDC");
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetLineWidth(0);
    legend->SetTextSize(0.05);
    legend->SetName("legend");
    
    legend->AddEntry(gr1,entry1);
    legend->AddEntry(gr2,entry2);

    can->cd();
    gr1->Draw();
    gr2->Draw("same");
    legend->Draw("same");

}
void makePaveText(TCanvas *can, TString text, double x1, double y1, double x2, double y2, double f = 0.05) { //1 - lewy gorny, 2 - prawy dolny, x i y rosna normalnie, nie jak w javie 
    TPaveText *pt = setOPT_text2(text,x1,y1,x2,y2,kBlack,f);
    can->cd();
    pt->Draw("same");

}


void createGraphs() {
    
    TString graphNames[_N_PAIRS_] = {"MGraphPi+p","MGraphPi-p"};
    TGraph* gr[_N_PAIRS_];

    for(int i = 0; i < _N_PAIRS_; i++) {
        gr[i] = new TGraph();
        gr[i]->SetTitle("");
        gr[i]->SetLineWidth(0);
        gr[i]->GetYaxis()->SetTitle("dN/dM (GeV/c^{2})^{-1}");
        gr[i]->SetMinimum(0);
    }

    //FILLING FROM TXT FILE
    ifstream filePlus, fileMinus;
    filePlus.open("pi+p.txt");
    fileMinus.open("pi-p.txt");

    Float_t xPlus,yPlus,xMinus,yMinus;

    int i = 0;
    while(filePlus>>xPlus && filePlus>>yPlus && fileMinus>>xMinus && fileMinus>>yMinus){
        gr[0]->SetPoint(i,xPlus,yPlus);
        gr[1]->SetPoint(i,xMinus,yMinus);
        i++;  
    }

    //READING MY HISTOGRAMS
    TH1D* hist[_N_CASES_][_N_PAIRS_];//3 cases, 2 pairs per case
    TGraph* grHist[_N_CASES_][_N_PAIRS_];
    
    Int_t events = 10e6;
    Int_t XBins = 1000;
    Float_t XMin = 1;
	Float_t XMax = 1.6;
	Float_t dX = (XMax-XMin)/XBins;
    Float_t scale = 1.0/(events*dX);
    Int_t rebin = 20; //50 binow jak w eksperymencie

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

            grHist[i][j] = new TGraph(hist[i][j]);
            grHist[i][j]->SetLineStyle(2);
            grHist[i][j]->SetLineWidth(3);

        }
    }   

    

    //COMPARING AND PLOTTING BASIC ONES
    TCanvas* canBasic[_N_CASES_][_N_PAIRS_];

    /*TGraph* tmpTab[3]; //for multiplot
    TString entries[3] = {"experiment","simulation", "mixing events"};*/

    for (int i = 0; i < _N_CASES_; i ++){ //for each case
        for(int j = 0; j < _N_PAIRS_; j++){ //for each pair
            canBasic[i][j] = new TCanvas(Form("%s%s%s",casesNames[i].Data(),pairsTitles[j].Data(),"Basic"),Form("%s%s%s",casesNames[i].Data(),pairsTitles[j].Data(),"Basic"),1000,1000);
            doublePlot(gr[j],grHist[i][j],canBasic[i][j],"experiment","simulation","M (GeV/c^{2})");
            //for multiplot
            /*tmpTab[0] = gr[j];
            tmpTab[1] = grHist[j];
            tmpTab[2] = grEvMix[j];
            multiplot(tmpTab,canBasic[i][j],entries,3);*/
            makePaveText(canBasic[i][j],casesNames[i].Data(),0.73,0.5,0.99,0.6);
            makePaveText(canBasic[i][j],pairsNames[j].Data(),0.73,0.45,0.99,0.5);
            makePaveText(canBasic[i][j],"HADES Au+Au",0.73,0.4,0.99,0.4,0.03);
            makePaveText(canBasic[i][j],"#sqrt{s_{NN}} = 2.42 GeV",0.73,0.38,0.99,0.35,0.03);
            canBasic[i][j]->SaveAs(Form("outputTxt/%s%s%s.png",casesNames[i].Data(),pairsTitles[j].Data(),"Basic"));
        }
    }

    //SCALING
    Float_t maxPlus = 22.077;
    Float_t maxMinus = 20.918;
    TGraph* grMax[_N_CASES_][2];

    
    for(int i = 0; i < _N_CASES_; i++) {
        hist[i][0]->Scale(maxPlus/hist[i][0]->GetMaximum());
        hist[i][1]->Scale(maxMinus/hist[i][1]->GetMaximum());
        for(int j = 0; j < 2; j++ ) {
            grMax[i][j] = new TGraph(hist[i][j]);
            grMax[i][j]->SetMinimum(0);
            grMax[i][j]->SetLineStyle(2);
            grMax[i][j]->SetLineWidth(_N_CASES_);
        }

    }
    //COMPARING AND PLOTTING SCALED ONES
    TCanvas* canMax[_N_CASES_][_N_PAIRS_];

    for (int i = 0; i < _N_CASES_; i ++){ //for each case
        for(int j = 0; j < _N_PAIRS_; j++){ //for each pair
            canMax[i][j] = new TCanvas(Form("%s%s%s",casesNames[i].Data(),pairsTitles[j].Data(),"Scaled"),Form("%s%s%s",casesNames[i].Data(),pairsTitles[j].Data(),"Scaled"),1000,1000);
            doublePlot(gr[j],grMax[i][j],canMax[i][j],"experiment","simulation (scaled)","M (GeV/c^{2})");
            makePaveText(canMax[i][j],casesNames[i].Data(),0.73,0.5,0.99,0.6);
            makePaveText(canMax[i][j],pairsNames[j].Data(),0.73,0.45,0.99,0.5);
            makePaveText(canMax[i][j],"HADES Au+Au",0.73,0.4,0.99,0.4,0.03);
            makePaveText(canMax[i][j],"#sqrt{s_{NN}} = 2.42 GeV",0.73,0.38,0.99,0.35,0.03);
            canMax[i][j]->SaveAs(Form("outputTxt/%s%s%s.png",casesNames[i].Data(),pairsTitles[j].Data(),"Scaled"));
        }
    }

}


void compTxt() {
    createGraphs();
}