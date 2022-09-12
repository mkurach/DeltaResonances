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

void makePaveText(TVirtualPad* can, TString text, double x1, double y1, double x2, double y2, double size) { //1 - lewy gorny, 2 - prawy dolny, x i y rosna normalnie, nie jak w javie 
    TPaveText *pt = setOPT_text2(text,x1,y1,x2,y2,kBlack,size);
    can->cd();
    pt->Draw("same");
}

void singlePlot(TH1D *h1, TCanvas* can, bool setRange = "false", TString XLabel = "",TString YLabel = "") {
    styleSet();
    if(XLabel!="")
        h1->GetXaxis()->SetTitle(XLabel);
    if(YLabel!="")
        h1->GetYaxis()->SetTitle(YLabel);
    
    if(setRange) {
        h1->GetYaxis()->SetRangeUser(-0.01,0.02);
    }

    h1->GetXaxis()->SetTitleSize(0.04);
    h1->GetYaxis()->SetTitleSize(0.04);
    h1->GetXaxis()->SetTitleFont(42);
    h1->GetYaxis()->SetTitleFont(42);
    h1->GetYaxis()->SetTitleOffset(1.2);

    h1->GetXaxis()->SetLabelFont(42);
    h1->GetYaxis()->SetLabelFont(42);
    h1->GetXaxis()->SetLabelSize(0.035);
    h1->GetYaxis()->SetLabelSize(0.035);

    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(0.8);
    h1->SetMarkerColor(kRed);
    h1->SetLineColor(kRed);

    can->cd();
    h1->Draw();
}

void multiplePlot(TH1D *histTab[], TCanvas* can, TString* entry, size_t n, bool logy = false, bool scaling = false, TString XLabel = "") {
    styleSet();
    if(XLabel!="")
        histTab[0]->GetXaxis()->SetTitle(XLabel);

    Double_t max = 0;
    Double_t min = 0;

    for (int i = 0; i < n; i++) {
        if(scaling) {
            histTab[i]->Scale(pow(10,i));
            //histTab[i]->Sumw2(kFALSE); //recalculate errors
            //histTab[i]->Sumw2();

            //entry[i] = TString::Format("(%i) %s ",i,entry[i].Data());
            //entry[i] += TString::Format(" 10^{%i}",i); //KRYPTYDA
        }
        if(histTab[i]->GetMaximum()>max)
            max = histTab[i]->GetMaximum();
        if(histTab[i]->GetMinimum()<min)
            min = histTab[i]->GetMinimum();
    }

    if (scaling) {
        histTab[0]->SetMaximum(1.15*10*max);
    }
    else {
        //histTab[0]->SetMaximum(2*max);
        histTab[0]->GetYaxis()->SetRangeUser(min,max*1.15);
    }
    histTab[0]->SetTitle("");

    TLegend* legend	= new TLegend(0.7,0.6,0.9,0.9, "",	"brNDC");
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(0.03);
    legend->SetLineWidth(0);
    legend->SetName("legend");

    can->cd();
    for (int i = 0; i < n; i++) {
        
        histTab[i]->GetXaxis()->SetTitleSize(0.04);
        histTab[i]->GetYaxis()->SetTitleSize(0.04);
        histTab[i]->GetXaxis()->SetTitleFont(42);
        histTab[i]->GetYaxis()->SetTitleFont(42);
        histTab[i]->GetYaxis()->SetTitleOffset(1.2);

        histTab[i]->GetXaxis()->SetLabelFont(42);
        histTab[i]->GetYaxis()->SetLabelFont(42);
        histTab[i]->GetXaxis()->SetLabelSize(0.035);
        histTab[i]->GetYaxis()->SetLabelSize(0.035);

        //histTab[i]->SetMarkerStyle(markers[i]);
        histTab[i]->SetMarkerStyle(markers[0]);
        histTab[i]->SetMarkerSize(0.8);
        histTab[i]->SetMarkerColor(colors[i]);
        histTab[i]->SetLineColor(colors[i]);

        if(scaling && i!=0)
                legend->AddEntry(histTab[i],TString::Format("%s (x10^{%i})",entry[i].Data(),i));
        else
            legend->AddEntry(histTab[i],entry[i]);

        if(logy)
            gPad->SetLogy();
        if(scaling)
            gPad->SetRightMargin(0.3);        
        if (i == 0)
            histTab[i]->Draw();
        else
            histTab[i]->Draw("same");

        
    }
    legend->Draw("same");



}

void sigOnly(TH1D* histSig[][_N_PAIRS_],TString* pairsTitles, TString* casesNames,TString* pairsNames) {
    TCanvas* canSig[_N_CASES_][_N_PAIRS_];
    for(int i = 0; i < _N_CASES_; i++){
        for(int j = 0; j < _N_PAIRS_; j++){
            canSig[i][j] = new TCanvas(Form("%s%sSig",casesNames[i].Data(),pairsTitles[j].Data()),Form("%s%sSig",casesNames[i].Data(),pairsTitles[j].Data()),1000,1000);
            singlePlot(histSig[i][j],canSig[i][j],false);
            makePaveText(canSig[i][j],casesNames[i].Data(),0.6,0.9,0.8,0.8,0.05);
            makePaveText(canSig[i][j],pairsNames[j].Data(),0.6,0.75,0.8,0.8,0.05); 
            makePaveText(canSig[i][j],"signal from mixed events",0.6,0.6,0.8,0.8,0.03);
            canSig[i][j]->SaveAs(Form("outputSig/%s%sSig.png",casesNames[i].Data(),pairsTitles[j].Data()));
        }
    }

}

void makeRatio(TH1D* histSig[][_N_PAIRS_],TH1D* histBack[][_N_PAIRS_], TString* pairsTitles, TString* casesNames,TString* pairsNames) {
    TH1D* ratioHist[_N_CASES_][_N_PAIRS_];
    TCanvas* canRatio[_N_CASES_][_N_PAIRS_];
    for(int i = 0; i < _N_CASES_; i++) {
        for(int j = 0; j < _N_PAIRS_; j++) {
            canRatio[i][j] = new TCanvas(Form("%s%sRatio",casesNames[i].Data(),pairsTitles[j].Data()),Form("%s%sRatio",casesNames[i].Data(),pairsTitles[j].Data()),1000,1000);
            ratioHist[i][j] = (TH1D*) histSig[i][j]->Clone();
            ratioHist[i][j]->Divide(histBack[i][j]);
            singlePlot(ratioHist[i][j],canRatio[i][j],true,ratioHist[i][j]->GetXaxis()->GetTitle(),"S/B");
            makePaveText(canRatio[i][j],casesNames[i].Data(),0.7,0.9,0.8,0.8,0.05);
            makePaveText(canRatio[i][j],pairsNames[j].Data(),0.7,0.75,0.8,0.8,0.05); 
            canRatio[i][j]->SaveAs(Form("outputSig/%s%sRatio.png",casesNames[i].Data(),pairsTitles[j].Data()));

        }
    }
}

void compSigBack(TH1D* histSig[][_N_PAIRS_],TH1D* histSigBack[][_N_PAIRS_],TH1D* histBack[][_N_PAIRS_], TString* pairsTitles, TString* casesNames,TString* pairsNames){
    
    TH1D* tmpTab[3]; //0 - back, 1 - sig+back, 2 - sig 
    TString entries[3] = {"background","all pairs","signal #times 50"};
    TCanvas* canComp[_N_CASES_][_N_PAIRS_];
    for(int i = 0; i < _N_CASES_; i++){
        for(int j = 0; j < _N_PAIRS_; j++){
            canComp[i][j] = new TCanvas(Form("%s%sComp",casesNames[i].Data(),pairsTitles[j].Data()),Form("%s%sComp",casesNames[i].Data(),pairsTitles[j].Data()),1000,1000);
            histSig[i][j]->Scale(50);
            tmpTab[0] = (TH1D*) histBack[i][j]->Clone();
            tmpTab[1] = (TH1D*) histSigBack[i][j]->Clone();
            tmpTab[2] = (TH1D*) histSig[i][j]->Clone();
            multiplePlot(tmpTab,canComp[i][j],entries,3);
            makePaveText(canComp[i][j],casesNames[i].Data(),0.73,0.5,0.99,0.6,0.05);
            makePaveText(canComp[i][j],pairsNames[j].Data(),0.73,0.45,0.99,0.5,0.05);
            canComp[i][j]->SaveAs(Form("outputSig/%s%sComp.png",casesNames[i].Data(),pairsTitles[j].Data()));
            
        }
    }
}





void createSig(){

    //READ HISTOGRAMS

    TH1D* histBack[_N_CASES_][_N_PAIRS_];
    TH1D* histSigBack[_N_CASES_][_N_PAIRS_];


    TFile* files[_N_CASES_];
    TString fileNames[_N_CASES_]= {"outputEvMix/outCaseAEvMix.root","outputEvMix/outCaseBEvMix.root","outputEvMix/outCaseCEvMix.root"};
    TString pairsTitles[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString pairsNames[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString casesNames[_N_CASES_] = {"CaseA","CaseB","CaseC"};

    for(int i = 0; i < _N_CASES_; i++){
        files[i] = new TFile(fileNames[i].Data());
        for(int j = 0; j < _N_PAIRS_; j++){
            histBack[i][j] = (TH1D*)files[i]->Get(Form("%sBack",pairsTitles[j].Data()));
            histSigBack[i][j] = (TH1D*)files[i]->Get(Form("%sSigBack",pairsTitles[j].Data()));
        }
    }


    //CREATE SIG
    TH1D* histSig[_N_CASES_][_N_PAIRS_];
    Int_t minRange = histBack[0][0]->FindBin(1.3);
    Int_t maxRange = histBack[0][0]->FindBin(1.4);
    /*TFile *file = new TFile("outputSig/outSig.root","RECREATE");
	file->cd();*/
    //jak  zapisuje to potem nie moge korzystac z tych histogramow ?? idk


    for(int i = 0; i < _N_CASES_; i++) {
        for(int j = 0; j < _N_PAIRS_; j++) {
            histBack[i][j]->Scale(histSigBack[i][j]->Integral(minRange,maxRange) / histBack[i][j]->Integral(minRange,maxRange));
            histSig[i][j] = (TH1D*) histSigBack[i][j]->Clone(Form("%s%sSig",casesNames[i].Data(),pairsTitles[j].Data()));
            histSig[i][j]->Add(histBack[i][j],-1);
            //histSig[i][j]->Write();

        }
    }

	//file->Save();
	//file->Close();



    //SCALE
    Int_t events = 10e6;
    Int_t XBins = 1000;
    Float_t XMin = 1;
	Float_t XMax = 1.7;
	Float_t dX = (XMax-XMin)/XBins;
    Float_t scale = 1.0/(events*dX);
    Int_t rebin = 10;

    for(int i = 0; i < _N_CASES_; i++) {
        for(int j = 0; j < _N_PAIRS_; j++) {
            histSig[i][j]->Rebin(rebin);
            histSig[i][j]->Scale(scale/rebin);

            histBack[i][j]->Rebin(rebin);
            histBack[i][j]->Scale(scale/rebin);

            histSigBack[i][j]->Rebin(rebin);
            histSigBack[i][j]->Scale(scale/rebin);
        }
    }

    //signal only
    //sigOnly(histSig,pairsTitles,casesNames,pairsNames);

    //ratio
    //makeRatio(histSig,histBack,pairsTitles,casesNames,pairsNames);


    //signal x 50 and background
    compSigBack(histSig,histSigBack,histBack,pairsTitles,casesNames,pairsNames);


}

void compHistSig(){
    createSig();
}

