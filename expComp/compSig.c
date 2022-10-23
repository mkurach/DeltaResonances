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
#include "GPlotHandler.h"

#define _N_PAIRS_ 2 
#define _N_CASES_ 3
#define _N_HIST_ 3

int colors[]={1, 600, 629, 414, 802, 880, 819, 922,433,618};

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
        histTab[0]->GetYaxis()->SetRangeUser(-0.001,max*1.15);
    
    histTab[0]->SetTitle("");

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
		if(i == 0)
        	histTab[i]->SetMarkerSize(0.8);
		else {
			histTab[i]->SetMarkerSize(0);
			histTab[i]->SetLineWidth(2);
		}
        histTab[i]->SetMarkerColor(colors[i]);
        histTab[i]->SetLineColor(colors[i]);

        if(scaling && i!=0)
                legend->AddEntry(histTab[i],TString::Format("%s (x10^{%i})",entry[i].Data(),i));
        else {
			if(i == 0)
				legend->AddEntry(histTab[i],entry[i],"AP");
			else
				legend->AddEntry(histTab[i],entry[i]);
		}
            

        if(logy)
            gPad->SetLogy();
        if(scaling)
            gPad->SetRightMargin(0.3);        
        if (i == 0)
            histTab[i]->Draw();
        else
            histTab[i]->Draw("C hist same");

        
    }
    legend->Draw("same");



}

void compSig () {

	TString fIn[_N_CASES_] ={"/u/mkurach/pairs/outputEvMix/outCaseAEvMix.root","/u/mkurach/pairs/outputEvMix/outCaseBEvMix.root","/u/mkurach/pairs/outputEvMix/outCaseCEvMix.root"}; 
	TString Case[_N_CASES_] = {"CaseA","CaseB","CaseC"};
	TString outDir = "/u/mkurach/figures_with_data/ladne/";

    TString pairsTitle[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString pairsTitlesDiff[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString histNames[_N_HIST_] = {"Back","SigBack","DiffHist"};
    
	//gROOT->SetBatch(kTRUE);


	//CREATING SIG2BACK
	TH1D* ratioHist[_N_CASES_];
	for(int i = 0; i < _N_CASES_; i++) {
		ratioHist[i] = (TH1D*) H1D[i][2]->Clone(Form("%sS2b",Case[i].Data())); //sig
		ratioHist[i]->Divide(H1D[i][0]);
		//ratioHist[i]->GetYaxis()->SetRangeUser(-0.01,0.02);
		//can[i][0]->cd();
		//ratioHist[i]->Draw();
    }


	//READING EXP HISTOGRAMS

	TString fInExp = "exp/s2b.root";
	TString histNamesExp = "h_mass_raw_int";
	TFile* fileExp = new TFile(fInExp.Data());

	TH1D* H1DExp = (TH1D*)fileExp->Get(histNamesExp.Data());
	//H1DExp->GetYaxis()->SetRangeUser(-0.01,0.02);
	//H1DExp->GetXaxis()->SetTitle("M_{#pi^{+}p} (GeV/c^{2})");

	//PLOTTING

	TFile *fileOut = new TFile("ladne/s2b.root","RECREATE");

	TCanvas* can = new TCanvas(Form("%sS2B",pairsTitlesDiff[0].Data()),Form("%sS2B",pairsTitlesDiff[0].Data()),715,700);
	setBasicStyle();
	setCanvas(can);
	TH1D* histTab[4] = {H1DExp,ratioHist[0],ratioHist[1],ratioHist[2]};
	TString entries[4] = {"exp","caseA","caseB","caseC"};


	multiplePlot(histTab, can, entries, 4,"M_{#pi^{+}p} (GeV/c^{2})");
    can->Write();
    fileOut->Close();
    fileOut->Save();

	






//gROOT->SetBatch(kFALSE);
}

