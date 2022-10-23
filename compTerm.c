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
#include <stdbool.h>
#include <cmath>
#include "events2chain.C"
#include "drawStyle.C"

//SCALE WYWOLUJE SUMW2, JESLI NIE CHCE SUMW2 TRZEBA DAC INNA OPCJE "nosw2"
//JESLI SIE CHEC NA KONIEC NAPRAWIC SUMW2 TRZEBA DAC Z OPCJA kFALSE

#define _N_PAIRS_ 2 
#define _N_FIGURES_ 5 
#define _N_HIST_ 10 
#define _N_MRANGES_ 25

int colors[]={1, 600, 629, 414, 802, 880, 819, 922,433,618}; // kBlack, kBlue, kRed, kGreen-2, kOrange+2, kGray, kViolet, kSpring
int markers[]= {20,21,24,25,28,34,47,43}; 
//int colorsCute[]={kRed+2, kRed, kOrange+7, kOrange-3, kTeal+2, kAzure+10, kAzure+7, kAzure+2,kAzure-1,kBlue+2};
int colorsCute[]={kBlue+2, kAzure-1, kAzure+2, kAzure+7, kAzure+10, kTeal+2, kOrange-3,kOrange+7,kRed,kRed+2};

TVirtualPad*** GetGridPad(Int_t x_pads, Int_t y_pads, Float_t x_margin, Float_t y_margin) {
	gStyle->SetCanvasColor(0);
	gStyle->SetPadColor(kWhite);
    TPad* padsav = (TPad*) gPad;
	if (gPad == NULL) {
		TCanvas* c = new TCanvas();
		c->cd();
		padsav = (TPad*) gPad;
	}
	TVirtualPad*** array2d = new TVirtualPad**[x_pads];
	for (int i = 0; i < x_pads; i++) {
  		array2d[i] = new TVirtualPad*[y_pads];
	}
	Double_t colls   = x_pads;
	Double_t rows    = y_pads;
	Double_t x_shift = 1.0 / (colls - 1 + 1 / (1 - TMath::Abs(x_margin)));
	Double_t y_shift = 1.0 / (rows - 1 + 1 / (1 - TMath::Abs(y_margin)));
	Double_t x_pad   = x_shift / (1.0 - TMath::Abs(x_margin));
	Double_t y_pad   = y_shift / (1.0 - TMath::Abs(y_margin));
	int glob         = 0;
	if (x_margin >= 0 && y_margin >= 0) {  // OK
  		for (int i = x_pads - 1; i >= 0; i--) {
    		for (int j = 0; j < y_pads; j++) {
				Double_t x1 = i * x_shift;
				Double_t x2 = x1 + x_pad;
				Double_t y1 = 1 - j * y_shift;
				Double_t y2 = y1 - y_pad;
				if (x1 < 0) x1 = 0;
				if (x1 > 1) x1 = 1;
				if (x2 < 0) x2 = 0;
				if (x2 > 1) x2 = 1;
				if (y1 < 0) y1 = 0;
				if (y1 > 1) y1 = 1;
				if (y2 < 0) y2 = 0;
				if (y2 > 1) y2 = 1;

				TPad* pad = new TPad(Form("pad_%i_%i", i, j), Form("pad_%i_%i", i, j), x1, y1, x2, y2);
				pad->SetTopMargin(0);
				pad->SetRightMargin(0);
				pad->SetBottomMargin(y_margin);
				pad->SetLeftMargin(x_margin);
				pad->SetNumber(glob);
				pad->Draw();
				array2d[i][j] = pad;
				glob++;
				padsav->cd();
    		}
  		}
	}
	if (x_margin >= 0 && y_margin < 0) {  // ok
 		y_margin = TMath::Abs(y_margin);
  		for (int i = x_pads - 1; i >= 0; i--) {
    		for (int j = y_pads - 1; j >= 0; j--) {
				Double_t x1 = i * x_shift;
				Double_t x2 = x1 + x_pad;
				Double_t y1 = 1 - j * y_shift;
				Double_t y2 = y1 - y_pad;
				if (x1 < 0) x1 = 0;
				if (x1 > 1) x1 = 1;
				if (x2 < 0) x2 = 0;
				if (x2 > 1) x2 = 1;
				if (y1 < 0) y1 = 0;
				if (y1 > 1) y1 = 1;
				if (y2 < 0) y2 = 0;
				if (y2 > 1) y2 = 1;
				TPad* pad = new TPad(Form("pad_%i_%i", i, j), Form("pad_%i_%i", i, j), x1, y1, x2, y2);
				pad->SetTopMargin(y_margin);
				pad->SetRightMargin(0);
				pad->SetBottomMargin(0);
				pad->SetLeftMargin(x_margin);
				pad->Draw();
				array2d[i][j] = pad;
				glob++;
				padsav->cd();
    		}
  		}
	}

	if (x_margin < 0 && y_margin < 0) {  // ok
		y_margin = TMath::Abs(y_margin);
		x_margin = TMath::Abs(x_margin);
		for (int i = 0; i < x_pads; i++) {
    		for (int j = y_pads - 1; j >= 0; j--) {
				Double_t x1 = i * x_shift;
				Double_t x2 = x1 + x_pad;
				Double_t y1 = 1 - j * y_shift;
				Double_t y2 = y1 - y_pad;
				if (x1 < 0) x1 = 0;
				if (x1 > 1) x1 = 1;
				if (x2 < 0) x2 = 0;
				if (x2 > 1) x2 = 1;
				if (y1 < 0) y1 = 0;
				if (y1 > 1) y1 = 1;
				if (y2 < 0) y2 = 0;
				if (y2 > 1) y2 = 1;
				TPad* pad = new TPad(Form("pad_%i_%i", i, j), Form("pad_%i_%i", i, j), x1, y1, x2, y2);
				pad->SetTopMargin(y_margin);
				pad->SetRightMargin(x_margin);
				pad->SetBottomMargin(0);
				pad->SetLeftMargin(0);
				pad->Draw();
				array2d[i][j] = pad;
				glob++;
				padsav->cd();
    		}
  		}		
	}

	if (x_margin < 0 && y_margin >= 0) {  // OK
		x_margin = TMath::Abs(x_margin);
		for (int i = 0; i < x_pads; i++) {
			for (int j = 0; j < y_pads; j++) {
				Double_t x1 = i * x_shift;
				Double_t x2 = x1 + x_pad;
				Double_t y1 = 1 - j * y_shift;
				Double_t y2 = y1 - y_pad;
				if (x1 < 0) x1 = 0;
				if (x1 > 1) x1 = 1;
				if (x2 < 0) x2 = 0;
				if (x2 > 1) x2 = 1;
				if (y1 < 0) y1 = 0;
				if (y1 > 1) y1 = 1;
				if (y2 < 0) y2 = 0;
				if (y2 > 1) y2 = 1;
				TPad* pad = new TPad(Form("pad_%i_%i", i, j), Form("pad_%i_%i", i, j), x1, y1, x2, y2);
				pad->SetTopMargin(0);
				pad->SetRightMargin(x_margin);
				pad->SetBottomMargin(y_margin);
				pad->SetLeftMargin(0);
				pad->Draw();
				array2d[i][j] = pad;
				glob++;
				padsav->cd();
			}
		}
	}

	return array2d;
}

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

void doublePlot(TH1D *h1, TH1D *h2, TCanvas* can, TString entry1, TString entry2, TString XLabel = "") {
    styleSet();
    if(XLabel!="")
        h1->GetXaxis()->SetTitle(XLabel);

    Double_t max = 0;
    if(h1->GetMaximum()>max) 
        max = h1->GetMaximum();
    if(h2->GetMaximum()>max)
        max = h2->GetMaximum();
    h1->SetMaximum(1.15*max);
    //h1->GetYaxis()->SetRangeUser(0,max*1.4);

   	//h1->Sumw2(kFALSE); //recalculate errors
    //h1->Sumw2();

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
    h1->SetMarkerColor(kBlue);
    h1->SetLineColor(kBlue);


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
    h2 -> SetMarkerSize(0.8);
    h2 -> SetMarkerColor(kRed);
    h2 -> SetLineColor(kRed);

    TLegend* legend	= new TLegend(0.65,0.65,0.9,0.9, "",	"brNDC");
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetLineWidth(0);
    legend->SetTextSize(0.05);
    legend->SetName("legend");
    
    legend->AddEntry(h1,entry1);
    legend->AddEntry(h2,entry2);

    can->cd();
    h1->Draw();
    h2->Draw("same");
    legend->Draw("same");



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

    TLegend* legend	= new TLegend(0.7,0.5,0.9,0.9, "",	"brNDC");
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
        //histTab[i]->SetMarkerColor(colorsCute[i]);
        //histTab[i]->SetLineColor(colorsCute[i]);
		histTab[i]->SetMarkerColor(kBlue+3);
        histTab[i]->SetLineColor(kBlue+3);

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

void readingHist(TH1D* H1D[][_N_FIGURES_][_N_HIST_], TFile* file, TString pairsTitlesDiff[],TString histNames[]){
	Int_t events = 10e6;

    Int_t XBins[_N_FIGURES_] = {1000, 1000, 1000, 1000, 1000};
    Float_t XMin[_N_FIGURES_] = {1, 1, 0, -2.2, 0};
	Float_t XMax[_N_FIGURES_] = {1.6, 1.6, 1.5, 2.2, 1.5};
	Float_t dX[_N_FIGURES_];
	for (int i = 0; i < _N_FIGURES_; i++) 
		dX[i] = (XMax[i]-XMin[i])/XBins[i];

	for (int i = 0 ; i < _N_PAIRS_; i++) { 
		for(int j = 0; j < _N_FIGURES_; j++) {
			if (j == 0 || j == 3) {
				H1D[i][j][0] = (TH1D*)file->Get(Form("%s%s",pairsTitlesDiff[i].Data(),histNames[j].Data()));
				
				
				H1D[i][j][0]->Rebin(10);
				H1D[i][j][0]->Scale(1.0/(events*dX[j]*10));

				//H1D[i][j][0]->Sumw2(kFALSE);
				//H1D[i][j][0]->Sumw2();		
			}
			else if (j== 1 || j == 2) {
				for (int k = 0; k < _N_HIST_; k++) {
					H1D[i][j][k] = (TH1D*)file->Get(Form("%s%s%i",pairsTitlesDiff[i].Data(),histNames[j].Data(),k));
					

					H1D[i][j][k]->Rebin(10);
					H1D[i][j][k]->Scale(1.0/(events*dX[j]*10));
					
					//H1D[i][j][k]->Sumw2(kFALSE);
					//H1D[i][j][k]->Sumw2();
				}
			}
			else {
				for (int k = 0; k < _N_MRANGES_; k++) {
					H1D[i][j][k] = (TH1D*)file->Get(Form("%s%s%i",pairsTitlesDiff[i].Data(),histNames[j].Data(),k));
					

					H1D[i][j][k]->Rebin(10);
					H1D[i][j][k]->Scale(1.0/(events*dX[j]*10));
					
					//H1D[i][j][k]->Sumw2(kFALSE);
					//H1D[i][j][k]->Sumw2();
				}

			}

		}
	}
}

void firstFiveHist(TH1D* H1D[][_N_FIGURES_][_N_HIST_], TString Case, TString outDir, TString PtRanges[], TString YRanges[], TString MRanges[]) {
    
    //gROOT->SetBatch(kTRUE);
    
    TCanvas *can = new TCanvas("M","M",1000,1000);
    doublePlot(H1D[0][0][0],H1D[1][0][0],can,"#pi^{+}p","#pi^{-}p", "M_{#pi^{#pm}p} (GeV/c^{2})");
    makePaveText(can,Case,0.13,0.9,0.5,0.8,0.05);
    makePaveText(can,"0 < y < 1.8", 0.13,0.87,0.5,0.7,0.035);
    can->SaveAs(outDir+Case+"_M.png");

    TCanvas *can2 = new TCanvas("Y","Y",1000,1000);
	//moving the rapidity
	H1D[0][3][0]->GetXaxis()->SetRangeUser(-0.76,2.24);
	H1D[1][3][0]->GetXaxis()->SetRangeUser(-0.76,2.24);
	//cout<<H1D[1][3][0]->GetBinContent(H1D[1][3][0]->FindBin(-0.75))<<endl;
    doublePlot(H1D[0][3][0],H1D[1][3][0],can2,"#pi^{+}p","#pi^{-}p","Rapidity");
    makePaveText(can2,Case,0.13,0.9,0.5,0.8,0.05);
    makePaveText(can2,"1.1 < M_{inv} < 1.4 GeV/c^{2}", 0.13,0.87,0.5,0.7,0.035);
    can2->SaveAs(outDir+Case+"_Y.png");

    TCanvas *can3 = new TCanvas("MPt+","MPt+",2000,2000);
    multiplePlot(H1D[0][1],can3,PtRanges,10);
    makePaveText(can3,Case,0.73,0.4,0.99,0.5,0.05);
    makePaveText(can3,"#pi^{+}p",0.73,0.35,0.99,0.4,0.05);
    makePaveText(can3,"0 < y < 1.8",0.73,0.32,0.99,0.3,0.04);
    can3->SaveAs(outDir+Case+"_MPt+.png");


    TCanvas *can4 = new TCanvas("PtY+","PtY+",2000,2000);
    multiplePlot(H1D[0][2],can4,YRanges,10,true,true); 
    makePaveText(can4,Case,0.73,0.4,0.99,0.5,0.05);
    makePaveText(can4,"#pi^{+}p",0.73,0.35,0.99,0.4,0.05);
    makePaveText(can4,"1.1 < M_{inv} < 1.4 GeV/c^{2}",0.73,0.32,0.99,0.3,0.04);
    can4->SaveAs(outDir+Case+"_PtY+.png");

    TCanvas *can5 = new TCanvas("MPt-","MPt-",2000,2000);
    multiplePlot(H1D[1][1],can5,PtRanges,10);
    makePaveText(can5,Case,0.73,0.4,0.99,0.5,0.05);
    makePaveText(can5,"#pi^{-}p",0.73,0.35,0.99,0.4,0.05);
    makePaveText(can5,"0 < y < 1.8",0.73,0.32,0.99,0.3,0.04);
    can5->SaveAs(outDir+Case+"_MPt-.png");

    TCanvas *can6 = new TCanvas("PtY-","PtY-",2000,2000);
    multiplePlot(H1D[1][2],can6,YRanges,10,true,true);
    makePaveText(can6,Case,0.73,0.4,0.99,0.5,0.05);
    makePaveText(can6,"#pi^{-}p",0.73,0.35,0.99,0.4,0.05);
    makePaveText(can6,"1.1 < M_{inv} < 1.4 GeV/c^{2}",0.73,0.32,0.99,0.3,0.04);
    can6->SaveAs(outDir+Case+"_PtY-.png");



	TCanvas *can7 = new TCanvas("PtM+","PtM+",2000,2000);
    multiplePlot(H1D[0][4],can7,MRanges,25); 
    makePaveText(can7,Case,0.73,0.4,0.99,0.5,0.05);
    makePaveText(can7,"#pi^{+}p",0.73,0.35,0.99,0.4,0.05);
    //makePaveText(can7,"1.1 < M_{inv} < 1.4 GeV/c^{2}",0.73,0.32,0.99,0.3,0.04);
    can7->SaveAs(outDir+Case+"_PtM+.png");

	TCanvas *can8 = new TCanvas("PtM-","PtM-",2000,2000);
    multiplePlot(H1D[1][4],can8,MRanges,10);
    makePaveText(can8,Case,0.73,0.4,0.99,0.5,0.05);
    makePaveText(can8,"#pi^{-}p",0.73,0.35,0.99,0.4,0.05);
    //makePaveText(can8,"1.1 < M_{inv} < 1.4 GeV/c^{2}",0.73,0.32,0.99,0.3,0.04);
    can8->SaveAs(outDir+Case+"_PtM-.png");



    //gROOT->SetBatch(kFALSE);
}

void newPtPlots(TH1D* H1D[][_N_FIGURES_][_N_HIST_],TString Case, TString outDir,TString pairsTitle[],TString PtRanges[]) {
    TCanvas *can7 = new TCanvas("MPt+Diff","MPt+Diff",500,700);
    TCanvas *can8 = new TCanvas("MPt-Diff","MPt-Diff",500,700);

    //can7->Divide(1,10);
    //can7->SetFrameLineColor(0);
    //can7->GetFrame()->SetLineColor(0);
    for (int j = 0; j < _N_PAIRS_; j++) {
		if (j == 0)
			can7->cd();
		else  
			can8->cd();
		TVirtualPad ***xpad = GetGridPad(1,10,0.05,0.4);

		for(int i = 0; i < 10; i++) {
			xpad[0][i]->cd();
			xpad[0][i]->SetBottomMargin(0.46);
			xpad[0][i]->SetRightMargin(0.05);

			H1D[j][1][10-(i+1)]->SetTitle("");
			H1D[j][1][10-(i+1)]->GetYaxis()->SetNdivisions(3);
			H1D[j][1][10-(i+1)]->GetYaxis()->SetLabelSize(0.16);
			H1D[j][1][10-(i+1)]->Draw();
			makePaveText(xpad[0][i],PtRanges[10-(i+1)],0.7,0.8,0.8,0.9,0.12);
			if(i==0){
				//makePaveText(xpad[0][i],"dN/dM (GeV/c^{2})^{-1}",0.8,0.99,0.03,0.9,0.16);
				makePaveText(xpad[0][i],Case,0.07,0.8,0.3,0.9,0.16);
				makePaveText(xpad[0][i],pairsTitle[j],0.8,0.8,0.58,0.9,0.16);
			}
			if(i == 9) {
				H1D[j][1][10-(i+1)]->GetXaxis()->SetTitleSize(0.16);
				H1D[j][1][10-(i+1)]->GetXaxis()->SetLabelSize(0.16);
			}
			else 
				H1D[j][1][10-(i+1)]->GetXaxis()->SetTitleSize(0);
		}
    } 

    can7->SaveAs(outDir+Case+"_MPt+Diff.png");
    can8->SaveAs(outDir+Case+"_MPt-Diff.png");

	can7->SaveAs("/u/mkurach/figures_with_data/moje/ladne/"+Case+"MPt+Diff.pdf");
    can8->SaveAs("/u/mkurach/figures_with_data/moje/ladne/"+Case+"MPt-Diff.pdf");

}


void createHistogramsComp (TString fIn, TString Case, TString outDir) {

    TFile *file = new TFile(fIn);
    TString pairsTitle[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString pairsTitlesDiff[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString histNames[_N_FIGURES_] = {"MHist","MPtHist","PtYHist", "YHist", "PtMHist"};
    TString PtRanges[_N_HIST_] = {"p_{T} < 0.15 GeV/c", "0.15 #leq p_{T} < 0.3 GeV/c", "0.3 #leq p_{T} < 0.45 GeV/c","0.45 #leq p_{T} < 0.6 GeV/c","0.6 #leq p_{T} < 0.75 GeV/c","0.75 #leq p_{T} < 0.9 GeV/c","0.9 #leq p_{T} < 1.05 GeV/c","1.05 #leq p_{T} < 1.2 GeV/c","1.2 #leq p_{T} < 1.35 GeV/c","1.35 #leq p_{T} < 1.6 GeV/c"};   
	TString YRanges[_N_HIST_] = {"0 #leq y < 0.14", "0.14 #leq y < 0.34", "0.34 #leq y < 0.49","0.49 #leq y < 0.64", "0.64 #leq y < 0.74", "0.74 #leq y < 0.84", "0.84 #leq y < 0.99", "0.99 #leq y < 1.14", "1.14 #leq y 1.34", "1.34 #leq y #leq 1.8"};
	//TString MRanges[_N_HIST_] = {"1 #leq M < 1.1","1.1 #leq M < 1.15","1.15 #leq M < 1.2","1.2 #leq M < 1.25","1.25 #leq M < 1.3","1.3 #leq M < 1.35","1.35 #leq M < 1.4","1.4 #leq M < 1.45","1.45 #leq M < 1.5","1.5 #leq M < 1.6"};
        TString MRanges[_N_MRANGES_] = {"1.078 #leq M < 1.09","1.09 #leq M < 1.1","1.1 #leq M < 1.11","1.11 #leq M < 1.12","1.12 #leq M < 1.13",
                                "1.13 #leq M < 1.14","1.14 #leq M < 1.15","1.15 #leq M < 1.16","1.16 #leq M < 1.17","1.17 #leq M < 1.18",
                                "1.18 #leq M < 1.19","1.19 #leq M < 1.2","1.2 #leq M < 1.22","1.22 #leq M < 1.24","1.24 #leq M < 1.28",
                                "1.28 #leq M < 1.32","1.32 #leq M < 1.36","1.36 #leq M < 1.4","1.4 #leq M < 1.44","1.44 #leq M < 1.48",
                                "1.48 #leq M < 1.52","1.52 #leq M < 1.56","1.56 #leq M < 1.6","1.6 #leq M < 1.65","1.65 #leq M < 1.7"};
    
	//gROOT->SetBatch(kTRUE);

//READING HISTOGRAMS

    cout<<"Reading file: "<<fIn<<endl;
    TH1D* H1D[_N_PAIRS_][_N_FIGURES_][_N_HIST_];
    readingHist(H1D,file,pairsTitlesDiff,histNames);   

//BASIC 4 FIGURES FROM ARTICLE

    firstFiveHist(H1D,Case,outDir,PtRanges,YRanges,MRanges);

//NEW PT  WAY OF SHOWING

    newPtPlots(H1D,Case,outDir,pairsTitle,PtRanges);

   // gROOT->SetBatch(kFALSE);
}


void compTerm() {

  	//createHistogramsComp("~/pairs/outputBig/outCaseA.root","CaseA","~/pairs/outputBig/");
	//createHistogramsComp("~/pairs/outputBig/outCaseB.root","CaseB","~/pairs/outputBig/");
	createHistogramsComp("~/pairs/outputBig/outCaseC.root","CaseC","~/pairs/outputBig/");


}
