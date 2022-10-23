#include <iostream>
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
#include <TMath.h>
#include "TSystemDirectory.h"
#include "TList.h"
#include <TF1.h>
#include <vector>
#include "drawStyle.C"

#define _N_CASES_ 3
#define _N_PAIRS_ 2
#define _N_YRANGES_ 10

int colors[]={1, 600, 629, 414, 802, 880, 819, 922,433,618}; // kBlack, kBlue, kRed, kGreen-2, kOrange+2, kGray, kViolet, kSpring
int markers[]= {20,21,24,25,28,34,47,43}; 
int colorsCute[]={kBlue+2, kAzure-1, kAzure+2, kAzure+7, kAzure+10, kTeal+2, kOrange-3,kOrange+7,kRed,kRed+2};

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


void multiplePlot(TH1D *histTab[], TCanvas* can, TString* entry, size_t n, bool logy = false, bool scaling = false, TString XLabel = "", int rebin = 10) {
    styleSet();
    if(XLabel!="")
        histTab[0]->GetXaxis()->SetTitle(XLabel);

    Double_t max = 0;
    Double_t min = 0;
    TF1* fun[n];
    //TF1* funCop[n];

    for (int i = 0; i < n; i++) {
        if(scaling) {
            histTab[i]->Scale(pow(10,i));
            histTab[i]->GetFunction("fun")->SetParameter(1,histTab[i]->GetFunction("fun")->GetParameter(1)*pow(10,i));
            histTab[i]->GetFunction("fun")->SetLineColor(kRed+1);
            //histTab[i]->GetFunction("fun")->SetRange(0,1.5);
            
           // histTab[i]->GetFunction("funCop")->SetParameter(1,histTab[i]->GetFunction("funCop")->GetParameter(1)*pow(10,i));
            histTab[i]->GetFunction("fun")->Update();
            //histTab[i]->GetFunction("funCop")->SetParameter(1,histTab[i]->GetFunction("funCop")->GetParameter(1)*1000000);
            //histTab[i]->GetFunction("funCop")->SetLineColor(colorsCute[i]);
            fun[i] = (TF1*)histTab[i]->GetFunction("fun");
            /*funCop[i] = (TF1*)fun[i]->Clone("funCop");
            //funCop[i]->SetParameter(1,funCop[i]->GetParameter(1)*pow(10,i));
            funCop[i]->SetRange(0,1.5);
            funCop[i]->SetLineStyle(2);
            histTab[i]->GetListOfFunctions()->Add(funCop[i]);*/

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
        histTab[0]->SetMaximum(1.15*10*max*1e5);
    }
    else {
        //histTab[0]->SetMaximum(2*max);
        histTab[0]->GetYaxis()->SetRangeUser(min,max*1.15);
    }
    histTab[0]->SetTitle("");

    TLegend* legend	= new TLegend(0.15,0.7,0.55,0.9, "",	"NDC");
    legend->SetNColumns(2);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(0.025);
    legend->SetLineWidth(0);
    legend->SetName("legend");

    can->cd();
    for (int i = 0; i < n; i++) {
        
        histTab[i]->GetXaxis()->SetTitleSize(0.04);
        histTab[i]->GetYaxis()->SetTitleSize(0.04);
        histTab[i]->GetXaxis()->SetTitleFont(42);
        histTab[i]->GetYaxis()->SetTitleFont(42);
        histTab[i]->GetYaxis()->SetTitleOffset(1.38);

        histTab[i]->GetXaxis()->SetLabelFont(42);
        histTab[i]->GetYaxis()->SetLabelFont(42);
        histTab[i]->GetXaxis()->SetLabelSize(0.035);
        histTab[i]->GetYaxis()->SetLabelSize(0.035);

        //histTab[i]->SetMarkerStyle(markers[i]);
        histTab[i]->SetMarkerStyle(markers[0]);
        histTab[i]->SetMarkerSize(0.9);
        histTab[i]->SetMarkerColor(colorsCute[i]);
        histTab[i]->SetLineColor(colorsCute[i]);

        //if(scaling && i!=0)
               // legend->AddEntry(histTab[i],TString::Format("%s (x10^{%i})",entry[i].Data(),i));
       // else
            legend->AddEntry(histTab[i],entry[i],"AP");

        if(logy)
            gPad->SetLogy();
        //if(scaling)
            gPad->SetLeftMargin(0.13);        
        if (i == 0) {
            histTab[i]->Draw("hist p");

        }
        else {
            histTab[i]->Draw("same hist p");

        }
        fun[i]->Draw("same");

        
    }
    legend->Draw("same");
    //can->Write();


}

Double_t getXRange(int i) {
    Double_t x;
    switch (i) {
        case 0:  x = (0+0.14)/2;   break;
        case 1:  x = (0.14+0.34)/2;     break;
        case 2:  x = (0.34+0.49)/2;    break;
        case 3:  x = (0.49+0.64)/2;    break;
        case 4:  x = (0.64+0.74)/2;     break;
        case 5:  x = (0.74+0.84)/2;     break;
        case 6:  x = (0.84+0.99)/2;     break;
        case 7:  x = (0.99+1.14)/2;     break;
        case 8:  x = (1.14+1.34)/2;     break;
        case 9:  x = (1.34+1.8)/2;     break;
    }

    return x;

}

Double_t fitFunctionPtY(Double_t *x, Double_t *par) {
    Double_t M = 1.2;
    Double_t mT = TMath::Sqrt(TMath::Power(M,2)+TMath::Power(x[0],2));
    if(x[0] >= 0 && x[0] <= 1.5)
        return par[1]*x[0]*mT*TMath::BesselK1(mT/par[0]);
    else    
        return 0;
}



void createPtYFit(int caseInt) {

    TString Case;
    switch(caseInt) {
        case 0:
            Case = "CaseA";
            break;
        case 1:
            Case = "CaseB";
            break;
        case 2:
            Case = "CaseC";
            break;
    }


    TH1D* histPtY[_N_PAIRS_][_N_YRANGES_];
    TString pairsTitles[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString pairsNames[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString YRanges[_N_YRANGES_] = {"0 #leq y < 0.14", "0.14 #leq y < 0.34", "0.34 #leq y < 0.49","0.49 #leq y < 0.64", "0.64 #leq y < 0.74", "0.74 #leq y < 0.84", "0.84 #leq y < 0.99", "0.99 #leq y < 1.14", "1.14 #leq y 1.34", "1.34 #leq y #leq 1.8"};
    
    Int_t events = 10e6;
    Int_t XBins = 1000;
    Float_t XMin = 0;
	Float_t XMax = 1.5;
	Float_t dX = (XMax-XMin)/XBins;
    Float_t scale = 1.0/(events*dX);
    Int_t rebin = 10; 

    gROOT -> SetBatch(kTRUE); 

    
    //TCanvas * can[_N_PAIRS_][_N_YRANGES_];
    TFile* file = new TFile("outputBig/out"+Case+".root");
    for(int j = 0; j < _N_PAIRS_; j++){
        for(int k = 0; k < _N_YRANGES_; k++){
            //can[j][k] = new TCanvas(Form("%s%sPtYFitting%i",Case.Data(),pairsTitles[j].Data(),k),Form("%s%sPtYFitting%i",Case.Data(),pairsTitles[j].Data(),k),1000,1000);
            histPtY[j][k] = (TH1D*)file->Get(Form("%sPtYHist%i",pairsTitles[j].Data(),k)); 
            histPtY[j][k]->Sumw2();       
            //histPtY[j][k]->Rebin(rebin);
            //histPtY[j][k]->Scale(scale/rebin);
            //histPtY[j][k]->Scale(2.95/histPtY[j][k]->GetMaximum());
            //can[j][k]->cd();
            //histPtY[j][k]->Draw();
        }
    }

    //FUNCTION

    Int_t nparams = 2;
    TF1 *fun = new TF1("fun",fitFunctionPtY,0,1.5,nparams);
    //0 - Teff,  1 - normalizacja

    switch(caseInt){
        case 0:
            //fun->SetParLimits(0,1e-8,0.5);
            fun->SetParameter(0,0.15);

            //fun->SetParLimits(1,1,5e4);
            fun->SetParameter(1,4e4);
            break;
        case 1:
            //fun->SetParLimits(0,1e-8,1);
            fun->SetParameter(0,0.1);

            //fun->SetParLimits(1,1e-8,20e5);
            fun->SetParameter(1,5e5);
            
            break;
        case 2:
            //fun->SetParLimits(0,1e-8,1);
            fun->SetParameter(0,0.1);

            //fun->SetParLimits(1,1,7e5);
            fun->SetParameter(1,2e5);
            break;
    }

    //FITTING 

    Double_t fitMin[_N_CASES_] = {0.4,0.4,0.4};
    Double_t fitMax[_N_CASES_] = {1.4,1.4,1.4};

    TF1* funCop;

    Double_t minRange = 0;
    Double_t maxRange = 1.5;

    Double_t tEff[_N_PAIRS_][_N_YRANGES_];
    Double_t tEffEr[_N_PAIRS_][_N_YRANGES_];
    Double_t yXValues[_N_PAIRS_][_N_YRANGES_];
    Double_t XErr[_N_PAIRS_][_N_YRANGES_];

    TFile* fileOut = new TFile(Form("outputFit/outFitPtY%s.root",Case.Data()),"RECREATE");
	fileOut->cd();
    for(int j = 0; j < _N_PAIRS_; j++) {
        for(int k = 0; k < _N_YRANGES_; k++) {
            //can[j][k]->cd();
            //cout<<Case<<"  "<<pairsTitles[j].Data()<<" numer range'u:"<<k<<endl;
            histPtY[j][k]->Fit("fun","Q","Q",fitMin[caseInt],fitMax[caseInt]);

            funCop = (TF1*)fun->Clone("funCop");
            funCop->SetRange(minRange,maxRange);
            funCop->SetLineStyle(2);
            histPtY[j][k]->GetListOfFunctions()->Add(funCop);
            histPtY[j][k]->Write();

            tEff[j][k] = fun->GetParameter(0);
            tEffEr[j][k] = fun->GetParError(0);
            yXValues[j][k] = getXRange(k);
            XErr[j][k] = 0;
        }
    }
    gROOT -> SetBatch(kFALSE);
    fileOut->Save();
	fileOut->Close();

 
   //TEFF PRINTING
    for(int j = 0; j < _N_PAIRS_; j++) {
        for(int k = 0; k < _N_YRANGES_; k++) {
            cout<<Case<<"  "<<pairsTitles[j].Data()<<" numer range'u:"<<k<<endl;
            cout<<"\tTeff: "<<tEff[j][k]<<"\n"<<endl;
        }
        cout<<"******"<<endl;
    }
    
    







    //PLOTTING



    TCanvas* canAll[_N_PAIRS_];
    rebin = 50;

    //TFile *fileOut2 = new TFile(Form("/u/mkurach/figures_with_data/moje/ladne/%sPtYFit.root",Case.Data()),"RECREATE");

    for(int i = 0; i < _N_PAIRS_; i ++) {
        for(int j = 0; j < _N_YRANGES_; j++) {
            histPtY[i][j]->Rebin(rebin);
            histPtY[i][j]->Scale(scale/rebin);
            histPtY[i][j]->GetFunction("fun")->SetParameter(1,histPtY[i][j]->GetFunction("fun")->GetParameter(1)*scale);
            //histPtY[i][j]->GetFunction("funCop")->SetParameter(1,histPtY[i][j]->GetFunction("funCop")->GetParameter(1)*scale);

        }


        canAll[i] = new TCanvas(Form("%s%sPtYFitted", Case.Data(),pairsTitles[i].Data()),Form("%s%sPtYFitted", Case.Data(),pairsTitles[i].Data()),715,700);
        multiplePlot(histPtY[i],canAll[i],YRanges,10,true,true,"p_{T} (GeV/c)",rebin);
        makePaveText(canAll[i],Case.Data(),0.65,0.9,0.99,0.8,0.05);
        makePaveText(canAll[i],"1.1 < M < 1.4 GeV/c^{2}",0.6,0.7,0.8,0.9,0.03);
        makePaveText(canAll[i],pairsNames[i].Data(),0.7,0.65,0.99,0.75,0.05);
        canAll[i]->SaveAs(Form("outputFit/%s%sPtYFitted.png",Case.Data(),pairsTitles[i].Data()));
        canAll[i]->SaveAs(Form("/u/mkurach/figures_with_data/moje/ladne/%s%sPtYFit.pdf",Case.Data(),pairsTitles[i].Data()));
        //canAll[i]->Write();

    }

/*

    //TEFF(Y) PLOTS
    TGraphErrors *grTeff[_N_PAIRS_];
    TCanvas *can[_N_PAIRS_];
    TH1D* tEffYhist[_N_PAIRS_];
    Double_t edges[_N_YRANGES_+1] = {0,0.14,0.34,0.49,0.64,0.74,0.84,0.99,1.14,1.34,1.8}; 

    TFile *fileOut2 = new TFile(Form("outputFit/outFitTeffY%s.root",Case.Data()),"RECREATE");

    for (int i = 0; i < _N_PAIRS_; i++) {
        can[i] = new TCanvas(Form("%s%sTeffY",Case.Data(),pairsTitles[i].Data()),Form("%s%sTeffY",Case.Data(),pairsTitles[i].Data()),1000,1000);
        grTeff[i] = new TGraphErrors(_N_YRANGES_,yXValues[i],tEff[i],XErr[i],tEffEr[i]);
        //tEffYhist[i] = (TH1D*)grTeff[i]->GetHistogram();
        tEffYhist[i] = new TH1D(Form("%s%sTeffYHist",Case.Data(),pairsTitles[i].Data()),Form("%s%sTeffYHist",Case.Data(),pairsTitles[i].Data()),_N_YRANGES_,edges);

        for(int j = 0; j < _N_YRANGES_; j++) {
            tEffYhist[i]->SetBinContent(j+1,tEff[i][j]);
            tEffYhist[i]->SetBinError(j+1,tEffEr[i][j]);
        }

        grTeff[i]->GetYaxis()->SetTitle("T_{eff} (GeV)");
        grTeff[i]->GetXaxis()->SetTitle("Rapidity");
        //grTeff[i]->GetXaxis()->SetLimits(0,1.7);
        grTeff[i]->GetYaxis()->SetRangeUser(0.05,0.15);

        tEffYhist[i]->GetYaxis()->SetTitle("T_{eff} (GeV)");
        tEffYhist[i]->GetXaxis()->SetTitle("Rapidity");
        tEffYhist[i]->SetMarkerStyle(21);
        tEffYhist[i]->Write();
        //grTeff[i]->Write();

        //grTeff[i]->SetTitle(Form("%s%sTeffY",Case.Data(),pairsTitles[i].Data()));
        //grTeff[i]->SetMarkerStyle(20);
        //grTeff[i]->SetMarkerSize(1);
        //grTeff[i]->SetMarkerColor(kRed+2);

        can[i]->cd();
        //grTeff[i]->Draw("ap");
        tEffYhist[i]->Draw();

        //styleSet();
        makePaveText(can[i],Case.Data(),0.73,0.99,0.99,0.5,0.05);
        makePaveText(can[i],pairsNames[i].Data(),0.73,0.92,0.99,0.4,0.05);
        can[i]->SaveAs("outputFit/"+Case+pairsTitles[i].Data()+"TeffY.png");
    }

    fileOut2->Close();
    fileOut2->Save();

    

*/

}

void compPtYFit() {

    //createPtYFit(0);
    //createPtYFit(1);
    createPtYFit(2);
}