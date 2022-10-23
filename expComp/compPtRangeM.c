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
        //histTab[0]->GetYaxis()->SetRangeUser(0.05,0.25);
    
    histTab[0]->SetTitle("");
    //histTab[0]->GetXaxis()->SetRangeUser(0,1.8);

    TLegend* legend	= new TLegend(0.63,0.65,0.93,0.82, "",	"NDC");
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(0.03);
    legend->SetLineWidth(0);
    legend->SetName("legend");

    gPad->SetLeftMargin(0.13);  

    can->cd();
    for (int i = 0; i < n; i++) {
        histTab[i]->GetYaxis()->SetTitle("d^{2}N/dp_{T}dM (GeV/c)^{-1}");
        histTab[i]->GetYaxis()->SetTitleOffset(1.4);
        
       /* histTab[i]->GetXaxis()->SetTitleSize(0.04);
        histTab[i]->GetYaxis()->SetTitleSize(0.04);
        histTab[i]->GetXaxis()->SetTitleFont(42);
        histTab[i]->GetYaxis()->SetTitleFont(42);
        ;
        histTab[i]->GetXaxis()->SetTitleOffset(1.2);

        histTab[i]->GetXaxis()->SetLabelFont(42);
        histTab[i]->GetYaxis()->SetLabelFont(42);
        histTab[i]->GetXaxis()->SetLabelSize(0.035);
        histTab[i]->GetYaxis()->SetLabelSize(0.035);*/
        
        histTab[i]->GetFunction("fun")->SetLineColor(colors[i+1]);
        histTab[i]->GetFunction("funCop")->SetLineColor(colors[i+1]);
        
		histTab[i]->SetMarkerStyle(21);
        histTab[i]->SetMarkerSize(0.8);
        histTab[i]->SetLineWidth(2);
	
        histTab[i]->SetMarkerColor(colors[i+1]+1);
        histTab[i]->SetLineColor(colors[i+1]+1);

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
            histTab[i]->Draw();
        else
            histTab[i]->Draw("same");

        
    }
    legend->Draw("same");



}


void compPtRangeM() {
    TString fIn[_N_CASES_] ={"/u/mkurach/pairs/outputFit/outFitPtMCaseA.root","/u/mkurach/pairs/outputFit/outFitPtMCaseB.root","/u/mkurach/pairs/outputFit/outFitPtMCaseC.root"}; 
	TString Case[_N_CASES_] = {"CaseA","CaseB","CaseC"};
	TString outDir = "/u/mkurach/figures_with_data/ladne/";

    TString pairsTitle[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString pairsTitlesDiff[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString histNames = "PtMHist13";


    //READING MY HISTOGRAMS
    TH1D* H1D[_N_CASES_]; //tylko plusy
    TF1* fun[_N_CASES_];
    TF1* funCop[_N_CASES_];
        
    Double_t minRange = 0.4;
    Double_t maxRange = 1.4;

    Int_t rebin = 25;

    TFile* file[_N_CASES_];
	//TCanvas* can[_N_CASES_];
	for(int i = 0; i < _N_CASES_; i ++) {
        file[i] = new TFile(fIn[i].Data());
        //can[i] = new TCanvas(Form("%s%s",Case[i].Data(),pairsTitlesDiff[0].Data()),Form("%s%s",Case[i].Data(),pairsTitlesDiff[0].Data()),1000,1000);
        H1D[i] = (TH1D*)file[i]->Get(Form("%s%s",pairsTitlesDiff[0].Data(),histNames.Data()));

        
        fun[i] = (TF1*)H1D[i]->GetFunction("fun");
        fun[i]->SetRange(minRange,maxRange);
        fun[i]->SetLineColor(colors[i+1]);
        //H1D[i]->Fit("fun","Q","Q",0.4,1.4);


        funCop[i] = (TF1*) H1D[i]->GetFunction("funCop");
        //funCop[i]->SetLineColor(colors[i+1]);
        //H1D[i]->Sumw2();
        H1D[i]->Rebin(rebin);
        H1D[i]->Scale(1.0/rebin);
        //can[i]->cd();
        //H1D[i]->Draw();
        //fun[i]->Draw();
		
	}

    //PLOTTING

    TFile *fileOut = new TFile("ladne/ptRangeM.root","RECREATE");

	TCanvas* can = new TCanvas(Form("%srangeM",pairsTitlesDiff[0].Data()),Form("%srangeM",pairsTitlesDiff[0].Data()),715,700);
	setBasicStyle();
	setCanvas(can);
	TH1D* histTab[3] = {H1D[1],H1D[0],H1D[2]};
	TString entries[3] = {"caseB","caseA","caseC"};
    TString entriesLeg[3] = {"case B","case A","case C"};

    TCanvas* cans[3];
    for(int i = 0; i < 3; i ++) {
        cans[i] = new TCanvas(Form("niewiem%i",i),Form("niewiem%i",i),715,700);
        setCanvas(cans[i]);
        cans[i]->cd();
        histTab[i]->SetTitle("");
        histTab[i]->Draw();
        makePaveText(cans[i],"1.22 #leq M <1.24 Gev/c^{2}",0.58,0.63,0.78,0.8,0.03);
        makePaveText(cans[i],"0.24 #leq y <1.24",0.63,0.55,0.88,0.75,0.03);
        makePaveText(cans[i],"#pi^{+}p",0.7,0.4,0.88,0.6,0.05);
        makePaveText(cans[i],entriesLeg[i].Data(),0.65,0.7,0.88,0.9,0.05);
        //cans[i]->SaveAs(Form("/u/mkurach/figures_with_data/moje/ladne/%sptM.pdf",entries[i].Data()));
    }


	multiplePlot(histTab, can, entriesLeg, 3,"p_{T} (Gev/c)");
    makePaveText(can,"1.22 #leq M <1.24 Gev/c^{2}",0.55,0.53,0.88,0.7,0.03);
    makePaveText(can,"0.24 #leq y <1.24",0.63,0.45,0.88,0.65,0.03);
    makePaveText(can,"#pi^{+}p",0.7,0.35,0.88,0.55,0.05);
    //can->SaveAs("/u/mkurach/figures_with_data/moje/ladne/ptM.pdf");
    can->Write();
    fileOut->Close();
    fileOut->Save();






}