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
#include "GPlotHandler.h"

#define _N_CASES_ 3
#define _N_PAIRS_ 2
#define _N_MRANGES_ 24

int colors[]={1, 600, 629, 414, 802, 880, 819, 922,433,618}; // kBlack, kBlue, kRed, kGreen-2, kOrange+2, kGray, kViolet, kSpring
int markers[]= {20,21,24,25,28,34,47,43}; 



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

void multiplePlot(TH1D *histTab[], TCanvas* can, TString* entry, size_t n, bool logy = false, bool scaling = false, TString XLabel = "") {
    if(XLabel!="")
        histTab[0]->GetXaxis()->SetTitle(XLabel);

    Double_t max = 0;
    Double_t min = 0;

    for (int i = 0; i < n; i++) {
        if(scaling) {
            histTab[i]->Scale(pow(10,i));
            histTab[i]->GetFunction("fun")->SetParameter(1,histTab[i]->GetFunction("fun")->GetParameter(1)*pow(10,i));
            histTab[i]->GetFunction("fun")->SetLineColor(kBlack);

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

    TLegend* legend	= new TLegend(0.7,0.5,0.9,0.9, "",	"NDC");
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(0.03);
    legend->SetLineWidth(0);
    legend->SetName("legend");

    can->cd();
    gPad->SetLeftMargin(0.3);
    for (int i = 0; i < n; i++) {
        
        /*histTab[i]->GetXaxis()->SetTitleSize(0.04);
        histTab[i]->GetYaxis()->SetTitleSize(0.04);
        histTab[i]->GetXaxis()->SetTitleFont(42);
        histTab[i]->GetYaxis()->SetTitleFont(42);
        histTab[i]->GetYaxis()->SetTitleOffset(1.2);

        histTab[i]->GetXaxis()->SetLabelFont(42);
        histTab[i]->GetYaxis()->SetLabelFont(42);
        histTab[i]->GetXaxis()->SetLabelSize(0.035);
        histTab[i]->GetYaxis()->SetLabelSize(0.035);*/

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
                    
        if (i == 0)
            histTab[i]->Draw();
        else
            histTab[i]->Draw("same");

        
    }
    legend->Draw("same");


}


Double_t getXRange(int i) {
    Double_t x;
    switch (i) {
        case 0:  x = (1.078+1.09)/2;   break;
        case 1:  x = (1.09+1.1)/2;     break;
        case 2:  x = (1.1+1.11)/2;    break;
        case 3:  x = (1.11+1.12)/2;    break;
        case 4:  x = (1.12+1.13)/2;     break;
        case 5:  x = (1.13+1.14)/2;     break;
        case 6:  x = (1.14+1.15)/2;     break;
        case 7:  x = (1.15+1.16)/2;     break;
        case 8:  x = (1.16+1.17)/2;     break;
        case 9:  x = (1.17+1.18)/2;     break;
        case 10:  x = (1.18+1.19)/2;    break;
        case 11:  x = (1.19+1.2)/2;     break;
        case 12:  x = (1.2+1.22)/2;     break;
        case 13:  x = (1.22+1.24)/2;     break;
        case 14:  x = (1.24+1.28)/2;    break;
        case 15:  x = (1.28+1.32)/2;     break;
        case 16:  x = (1.32+1.36)/2;    break;
        case 17:  x = (1.36+1.4)/2;     break;
        case 18:  x = (1.4+1.44)/2;     break;
        case 19:  x = (1.44+1.48)/2;     break;
        case 20:  x = (1.48+1.52)/2;     break;
        case 21:  x = (1.52+1.56)/2;     break;
        case 22:  x = (1.56+1.6)/2;     break;
        case 23:  x = (1.6+1.65)/2;     break;
        case 24:  x = (1.65+1.7)/2;     break;
    }

    return x;

}

Double_t fitFunctionPtM(Double_t *x, Double_t *par) {
    Double_t M = 1.2;
    Double_t mT = TMath::Sqrt(TMath::Power(M,2)+TMath::Power(x[0],2));
    if(x[0] >= 0 && x[0] <= 1.5)
        return par[1]*x[0]*mT*TMath::BesselK1(mT/par[0]);
    else    
        return 0;
}

Double_t fitFunctionTeffM(Double_t *x, Double_t *par) {
    if(x[0] >= 0 && x[0] <= 1.7)
        return TMath::Power(par[0],2)/2*x[0]+par[1];
    else    
        return 0;
}

void createPtMFit(int caseInt){
    
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
        
    //gROOT -> SetBatch(kTRUE); 

    TH1D* histPtM[_N_PAIRS_][_N_MRANGES_];
    TString pairsTitles[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString pairsNames[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    //TString MRanges[_N_MRANGES_] = {"1 #leq M < 1.1","1.1 #leq M < 1.15","1.15 #leq M < 1.2","1.2 #leq M < 1.25","1.25 #leq M < 1.3","1.3 #leq M < 1.35","1.35 #leq M < 1.4","1.4 #leq M < 1.45","1.45 #leq M < 1.5","1.5 #leq M < 1.6"};
    TString MRanges[_N_MRANGES_] = {"1.078 #leq M < 1.09","1.09 #leq M < 1.1","1.1 #leq M < 1.11","1.11 #leq M < 1.12","1.12 #leq M < 1.13",
                                "1.13 #leq M < 1.14","1.14 #leq M < 1.15","1.15 #leq M < 1.16","1.16 #leq M < 1.17","1.17 #leq M < 1.18",
                                "1.18 #leq M < 1.19","1.19 #leq M < 1.2","1.2 #leq M < 1.22","1.22 #leq M < 1.24","1.24 #leq M < 1.28",
                                "1.28 #leq M < 1.32","1.32 #leq M < 1.36","1.36 #leq M < 1.4","1.4 #leq M < 1.44","1.44 #leq M < 1.48",
                                "1.48 #leq M < 1.52","1.52 #leq M < 1.56","1.56 #leq M < 1.6","1.6 #leq M < 1.65"};//,"1.65 #leq M < 1.7"};
    Int_t events = 10e6;
    Int_t XBins = 1000;
    Float_t XMin = 0;
	Float_t XMax = 1.5;
	Float_t dX = (XMax-XMin)/XBins;
    Float_t scale = 1.0/(events*dX);
    Int_t rebin = 10; 

    //TCanvas * can[_N_PAIRS_][_N_MRANGES_];
    TFile* file = new TFile("outputBig/out"+Case+".root");
    for(int j = 0; j < _N_PAIRS_; j++){
        for(int k = 0; k < _N_MRANGES_; k++){
            //can[j][k] = new TCanvas(Form("%s%sPtMFitting%i",Case.Data(),pairsTitles[j].Data(),k),Form("%s%sPtMFitting%i",Case.Data(),pairsTitles[j].Data(),k),1000,1000);
            histPtM[j][k] = (TH1D*)file->Get(Form("%sPtMHist%i",pairsTitles[j].Data(),k)); 
            histPtM[j][k]->Sumw2();
            //histPtM[j][k]->Rebin(rebin);
            //histPtM[j][k]->Scale(scale/rebin);
            histPtM[j][k]->Scale(scale);
        }
    }

    //FUNCTION
    Int_t nparams = 2;
    TF1 *fun = new TF1("fun",fitFunctionPtM,0,1.5,nparams);
    //0 - Teff,  1 - normalizacja

    Double_t teffParameter[_N_CASES_] = {0.15,0.1,0.1};
    Double_t normParameter[_N_CASES_] = {2e3,5e5,2e5};

    fun->SetParameter(0,teffParameter[caseInt]);
    fun->SetParameter(1,normParameter[caseInt]);



    //FITTING

    gROOT -> SetBatch(kTRUE);

    Double_t fitMin[_N_CASES_] = {0.4,0.4,0.4};
    Double_t fitMax[_N_CASES_] = {1.4,1.4,1.4};

    Double_t minRange = 0;
    Double_t maxRange = 1.5;

    TF1* funCop;

    Double_t tEff[_N_PAIRS_][_N_MRANGES_];
    Double_t tEffEr[_N_PAIRS_][_N_MRANGES_];
    Double_t mXValues[_N_PAIRS_][_N_MRANGES_];
    Double_t XErr[_N_PAIRS_][_N_MRANGES_];

    TFile* fileOut = new TFile(Form("outputFit/outFitPtM%s.root",Case.Data()),"RECREATE");
    fileOut->cd();
    for(int j = 0; j < _N_PAIRS_; j++) {
        for(int k = 0; k < _N_MRANGES_; k++) {
            //cout<<Case<<"  "<<pairsTitles[j].Data()<<" numer range'u:"<<k<<endl;
            histPtM[j][k]->Fit("fun","Q","Q",fitMin[caseInt],fitMax[caseInt]);
            funCop = (TF1*)fun->Clone("funCop");
            funCop->SetRange(minRange,maxRange);
            funCop->SetLineStyle(2);
            histPtM[j][k]->GetListOfFunctions()->Add(funCop);
            histPtM[j][k]->Write();

            tEff[j][k] = fun->GetParameter(0);
            tEffEr[j][k] = fun->GetParError(0);
            mXValues[j][k] = getXRange(k);
            XErr[j][k] = 0;

        }
    }


    fileOut->Save();
	fileOut->Close();
    gROOT -> SetBatch(kFALSE);

    //TEFF PRINTING

    /*for(int j = 0; j < _N_PAIRS_; j++) {
        for(int k = 0; k < _N_MRANGES_; k++) {
            cout<<Case<<"  "<<pairsTitles[j].Data()<<" numer range'u:"<<k<<endl;
            cout<<"\tTeff: "<<tEff[j][k]<<"\n"<<endl;
        }
        cout<<"******"<<endl;
    }*/
    
    //TEFF(M) PLOTS

    //TCanvas* can[_N_PAIRS_];
    TGraphErrors *grTeff[_N_PAIRS_];
    for(int i = 0; i < _N_PAIRS_; i++) {
        grTeff[i] = new TGraphErrors(_N_MRANGES_,mXValues[i],tEff[i],XErr[i],tEffEr[i]);
        //can[i] = new TCanvas(Form("%i",i),Form("%i",i),1000,1000);
        grTeff[i]->GetYaxis()->SetTitle("T_{eff} (GeV)");
        grTeff[i]->GetXaxis()->SetTitle(Form("M_{%s} (GeV/c^{2})",pairsNames[i].Data()));

        //for(int j = 0; j < 3; j ++)
            //grTeff[i]->SetPoint(25+j,addPointsX[j],addPointsY[caseInt][j]);
        grTeff[i]->GetXaxis()->SetLimits(0,1.8);
        grTeff[i]->GetYaxis()->SetRangeUser(-0.13,1);
        grTeff[i]->GetYaxis()->SetTitleOffset(1.3);
        grTeff[i]->GetXaxis()->SetTitleOffset(1.3);
        grTeff[i]->SetTitle(Form("%s%sTeffM",Case.Data(),pairsTitles[i].Data()));
        grTeff[i]->SetMarkerStyle(20);
        grTeff[i]->SetMarkerSize(1);
        grTeff[i]->SetMarkerColor(kRed+2);
        //can[i]->cd();
        //grTeff[i]->Draw("ap");
        //grTeff[i]->Write();
    }


    //PLOTTING nie działa na ten moment

    /*TCanvas* canAll[_N_PAIRS_];
    
    for(int i = 0; i < _N_PAIRS_; i ++) {
        canAll[i] = new TCanvas(Form("%s%sPtMFitted", Case.Data(),pairsTitles[i].Data()),Form("%s%sPtMFitted", Case.Data(),pairsTitles[i].Data()),1000,1000);
        multiplePlot(histPtM[i],canAll[i],MRanges,10,true,true,"M (GeV/c^{2})");
        makePaveText(canAll[i],Case.Data(),0.73,0.4,0.99,0.5,0.05);
        makePaveText(canAll[i],pairsNames[i].Data(),0.73,0.35,0.99,0.4,0.05);
        //canAll[i]->SaveAs(Form("outputFit/%s%sPtMFitted.png",Case.Data(),pairsTitles[i].Data()));
    }*/

    //TCanvas* canTeff[_N_PAIRS_];
    //canTeff[i] = new TCanvas(Form("%s%sTeff",Case.Data(),pairsTitles[i].Data()),Form("%s%sTeff",Case.Data(),pairsTitles[i].Data()),1000,1000);
    //singlePlot(histTeff[i],canTeff[i],"Rapidity", "T_{eff} (GeV)");

    
    
    //FUNCTION

    nparams = 2;
    TF1 *fun2 = new TF1("fun2",fitFunctionTeffM,0,1.7,nparams);
    //0 - beta, 1 - T_
    TF1* fun2Cop;

    //fun2->SetParLimits(0,0,1);
    fun2->SetParameter(0,0.5);

    //fun2->SetParLimits(1,-0.1,0.2);
    fun2->SetParameter(1,0.1);

    
    

    //ADDING POINTS FROM PARTICLES

    Double_t addPointsX[3] = {0.9395653,0.4936770,0.1395699};
    Double_t addPointsY[_N_CASES_][3] = {{0.145643,0.105242,0.0762062},
                                        {0.11814,0.0991819,0.0716104},
                                        {0.113079,0.0952766,0.0752646}};

    TGraph* grPart = new TGraph(3,addPointsX,addPointsY[caseInt]);
    grPart->SetMarkerStyle(20);
    grPart->SetMarkerSize(1);
    grPart->SetMarkerColor(kBlue+2);
    grPart->GetXaxis()->SetLimits(0,1.7);
    grPart->GetYaxis()->SetRangeUser(-0.13,1);
    grPart->GetYaxis()->SetTitle("T_{eff} (GeV)");
    grPart->GetXaxis()->SetTitle("M (GeV/c^{2})");
    grPart->SetTitle("");
    grPart->GetYaxis()->SetTitleOffset(1.3);
    grPart->GetXaxis()->SetTitleOffset(1.3);


    fun2->SetLineColor(kBlue);
    grPart->Fit("fun2","","",0.1,1);
    Double_t betaPar = fun2->GetParameter(0);
    Double_t tPar = fun2->GetParameter(1);

    fun2Cop = (TF1*)fun2->Clone("fun2Cop");
    fun2Cop->SetRange(0,1.6);
    fun2Cop->SetLineStyle(2);
    fun2Cop->SetLineColor(kBlue);
    grPart->GetListOfFunctions()->Add(fun2Cop);
    




    //TEFF M FIT


    Double_t beta[_N_PAIRS_];
    Double_t t[_N_PAIRS_];

    Double_t betaTh[_N_CASES_] = {0.525672, 0.469742, 0.50362};
    Double_t tTh[_N_CASES_] = {49.6, 70.3, 63.1}; //(MeV)



    TCanvas* can[_N_PAIRS_];
    TCanvas* canParticles[_N_PAIRS_];
    TFile *fileOut2 = new TFile(Form("/u/mkurach/figures_with_data/moje/ladne/teffM%s.root",Case.Data()),"RECREATE");
    for(int j = 0; j < _N_PAIRS_; j++) {
        
        can[j] = new TCanvas(Form("%sTeffMFit",pairsTitles[j].Data()),Form("%sTeffMFit",pairsTitles[j].Data()),715,700);
        canParticles[j] = new TCanvas(Form("%sTeffMFitParticles",pairsTitles[j].Data()),Form("%sTeffMFitParticles",pairsTitles[j].Data()),715,700);
        setBasicStyle();
        setCanvas(can[j]);
        setCanvas(canParticles[j]);

        cout<<pairsTitles[j].Data()<<endl;
        fun2->SetLineColor(kRed);
        grTeff[j]->Fit("fun2","Q","Q",1.07,1.3);
        beta[j] = fun2->GetParameter(0);
        t[j] = fun2->GetParameter(1);

        fun2Cop = (TF1*)fun2->Clone(Form("fun2Cop%i",j));
        fun2Cop->SetRange(0,1.67);
        fun2Cop->SetLineStyle(2);
        fun2Cop->SetLineColor(kRed);
        grTeff[j]->GetListOfFunctions()->Add(fun2Cop);


        can[j]->cd();
        grTeff[j]->SetTitle("");
        grTeff[j]->GetXaxis()->SetRangeUser(0,1.7);
        grTeff[j]->Draw("ap");
        makePaveText(can[j],Case.Data(),0.6,0.6,0.99,0.99,0.04);
        makePaveText(can[j],Form("<#beta> = %.3f",beta[j]),0.15,0.6,0.3,0.7,0.04,kRed+3);
        makePaveText(can[j],Form("T = %.3f (MeV)",t[j]*1e3),0.15,0.55,0.3,0.65,0.04,kRed+3);
        can[j]->SaveAs(Form("outputFit/%s%sTeffM.png",Case.Data(),pairsTitles[j].Data()));
        can[j]->SaveAs(Form("/u/mkurach/figures_with_data/moje/ladne/%s%steffM.pdf",Case.Data(),pairsTitles[j].Data()));
        can[j]->Write();

        canParticles[j]->cd();
        
        grPart->Draw("ap ");
        grTeff[j]->Draw("p same");
        makePaveText(canParticles[j],Case.Data(),0.6,0.6,0.99,0.99,0.04);
        makePaveText(canParticles[j],Form("<#beta> = %.3f",betaPar),0.15,0.6,0.3,0.7,0.04,kBlue+3);
        makePaveText(canParticles[j],Form("T = %.3f (MeV)",tPar*1e3),0.15,0.55,0.3,0.65,0.04,kBlue+3);
        canParticles[j]->SaveAs(Form("/u/mkurach/figures_with_data/moje/ladne/%s%steffMParticles.pdf",Case.Data(),pairsTitles[j].Data()));
        canParticles[j]->Write();

    }

    fileOut2->Close();
    fileOut2->Save();
    




    
    

    //PRINTING
    cout<<Case<<endl;
    for(int j = 0; j < _N_PAIRS_; j++) {
        cout<<"\t"<<pairsTitles[j].Data()<<":\n"<<endl;
        cout<<"\t\tBeta: "<<beta[j];
        cout<<"\tT: "<<t[j]*1e3<<" (MeV)\n"<<endl;
    }
    cout<<"\tTheoretical:\n"<<endl;
    cout<<"\t\tBeta: "<<betaTh[caseInt];
    cout<<"\tT: "<<tTh[caseInt]<<" (MeV)\n"<<endl;

    cout<<"\tFrom 3 particles:\n"<<endl;
    cout<<"\t\tBeta: "<<betaPar;
    cout<<"\tT: "<<tPar*1e3<<" (MeV)\n"<<endl;

    //cout<<"chi2: "<<fun2->GetChisquare()<<endl;
    //cout<<"ndf: "<<fun2->GetNDF()<<endl;

}

void compPtMFit() {
    //TGraphErrors grTeff[_N_CASES_][_N_PAIRS_];
    for(int i = 0; i < _N_CASES_; i++)
        createPtMFit(i);
    //createPtMFit(0);    
    //createPtMFit(1);
    //createPtMFit(2);
}