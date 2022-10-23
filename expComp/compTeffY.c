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

int colors[]={1, 600, 629, 414, 802, 880, 819, 922,433,618};
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

void multiplePlot(TH1D *histTab[], TCanvas* can, TString* entry, size_t n,  TString XLabel = "", bool logy = false, bool scaling = false) {
    if(XLabel!="")
        histTab[0]->GetXaxis()->SetTitle(XLabel);
	
	//histTab[0]->GetXaxis()->SetTitle("M_{#pi^{+}p} (GeV/c^{2})");
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
    else 
        histTab[0]->GetYaxis()->SetRangeUser(0.05,0.25);
    
    histTab[0]->SetTitle("");
    //histTab[0]->GetXaxis()->SetRangeUser(0,1.8);

    TLegend* legend	= new TLegend(0.6,0.6,0.9,0.8, "",	"NDC");
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
        histTab[i]->GetXaxis()->SetTitleOffset(1.2);

        histTab[i]->GetXaxis()->SetLabelFont(42);
        histTab[i]->GetYaxis()->SetLabelFont(42);
        histTab[i]->GetXaxis()->SetLabelSize(0.035);
        histTab[i]->GetYaxis()->SetLabelSize(0.035);

        
		histTab[i]->SetMarkerStyle(21);
        histTab[i]->SetMarkerSize(0.8);
        histTab[i]->SetLineWidth(2);
	
        histTab[i]->SetMarkerColor(colors[i]);
        histTab[i]->SetLineColor(colors[i]);

        if(scaling && i!=0)
                legend->AddEntry(histTab[i],TString::Format("%s (x10^{%i})",entry[i].Data(),i));
        else {
			if(i == 0)
				legend->AddEntry(histTab[i],entry[i],"AP");
			else
				legend->AddEntry(histTab[i],entry[i],"AP");
		}
            

        if(logy)
            gPad->SetLogy();
        if(scaling)
            gPad->SetRightMargin(0.3);        
        if (i == 0)
            histTab[i]->Draw("E2");
        else
            histTab[i]->Draw("PL hist same");

        
    }
    legend->Draw("same");



}

void compTeffY () {

    TString fIn[_N_CASES_] ={"/u/mkurach/pairs/outputFit/outFitTeffYCaseA.root","/u/mkurach/pairs/outputFit/outFitTeffYCaseB.root","/u/mkurach/pairs/outputFit/outFitTeffYCaseC.root"}; 
	TString Case[_N_CASES_] = {"CaseA","CaseB","CaseC"};
	TString outDir = "/u/mkurach/figures_with_data/ladne/";

    TString pairsTitle[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString pairsTitlesDiff[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString histNames = "PiPlusPTeffYHist";


    //READING MY HISTOGRAMS
    TH1D* H1D[_N_CASES_];


	TFile* file[_N_CASES_];
	//TCanvas* can[_N_CASES_];
	for(int i = 0; i < _N_CASES_; i ++) {
		file[i] = new TFile(fIn[i].Data());
        //can[i] = new TCanvas(Form("%s%s%s",Case[i].Data(),pairsTitlesDiff[0].Data(),histNames.Data()),Form("%s%s%s",Case[i].Data(),pairsTitlesDiff[0].Data(),histNames.Data()),1000,1000);
        H1D[i] = (TH1D*)file[i]->Get(Form("%s%s",Case[i].Data(),histNames.Data()));
        //H1D[i][k]->Scale(1.0/(events));
        //can[i]->cd(); 
        //H1D[i]->Draw();
		
	}

    //READING EXP
    TString fInExp = "exp/teffY.root";
	TString histNamesExp = "h_tb_rap_circle_mult0__53";
	TFile* fileExp = new TFile(fInExp.Data());

	TH1D* H1DExp = (TH1D*)fileExp->Get(histNamesExp.Data());
    //can[0]->cd();
    //H1DExp->Draw();

    //PLOTTING

	TFile *fileOut = new TFile("ladne/teffY.root","RECREATE");

	TCanvas* can = new TCanvas(Form("%steffY",pairsTitlesDiff[0].Data()),Form("%sTeffY",pairsTitlesDiff[0].Data()),715,700);
	setBasicStyle();
    gStyle->SetErrorX(0.5); 
	setCanvas(can);
	TH1D* histTab[4] = {H1DExp,H1D[0],H1D[1],H1D[2]};
	TString entries[4] = {"experiment","caseA","caseB","caseC"};

    //gStyle->SetPadColor(kBlue);
	multiplePlot(histTab, can, entries, 4,"Rapidity");
    makePaveText(can,"#pi^{+}p",0.12,0.74,0.88,0.85,0.05);
    makePaveText(can,"HADES Au+Au",0.65,0.53,0.8,0.63,0.02);
    makePaveText(can,"#sqrt{s_{NN}} = 2.42 GeV",0.65,0.5,0.8,0.6,0.02);
    can->SaveAs("/u/mkurach/figures_with_data/moje/ladne/teffY.png");
    can->SaveAs("/u/mkurach/figures_with_data/moje/ladne/teffY.pdf");
    can->Write();
    fileOut->Close();
    fileOut->Save();
  




}