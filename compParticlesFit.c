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

#define _N_PARTICLES_ 3
#define _N_CASES_ 3

Double_t fitFunctionPtProt(Double_t *x, Double_t *par) { // 0 - Teff, 1 - normalization
    Double_t M = 0.9395653;
    Double_t mT = TMath::Sqrt(TMath::Power(M,2)+TMath::Power(x[0],2));
    if(x[0] >= 0 && x[0] <= 2)
        return par[1]*x[0]*mT*TMath::BesselK1(mT/par[0]);
    else    
        return 0;
}

Double_t fitFunctionPtKaon(Double_t *x, Double_t *par) { // 0 - Teff, 1 - normalization
    Double_t M = 0.4936770;
    Double_t mT = TMath::Sqrt(TMath::Power(M,2)+TMath::Power(x[0],2));
    if(x[0] >= 0 && x[0] <= 2)
        return par[1]*x[0]*mT*TMath::BesselK1(mT/par[0]);
    else    
        return 0;
}

Double_t fitFunctionPtPion(Double_t *x, Double_t *par) { // 0 - Teff, 1 - normalization
    Double_t M = 0.1395699;
    Double_t mT = TMath::Sqrt(TMath::Power(M,2)+TMath::Power(x[0],2));
    if(x[0] >= 0 && x[0] <= 2)
        return par[1]*x[0]*mT*TMath::BesselK1(mT/par[0]);
    else    
        return 0;
}


void createHistograms(int i) {

    TH1D* histPt[_N_PARTICLES_];
    TString histNames[_N_PARTICLES_]= {"PtHistProton","PtHistKaons","PtHistPions"};
    TString particlesTitles[_N_PARTICLES_] = {"proton","kaons","pions"};
    TString filesNames[_N_CASES_] = {"outputPart/outCaseAPart.root","outputPart/outCaseBPart.root","outputPart/outCaseCPart.root"};
    TString casesNames[_N_CASES_] = {"CaseA","CaseB","CaseC"};

    TFile* file;

    //for(int i = 0; i < _N_CASES_; i++) {
    //for(int i = 0; i < 1; i++){
        file = new TFile(filesNames[i].Data());
        for(int j = 0; j < _N_PARTICLES_; j++) {
            
            histPt[j] = (TH1D*)file->Get(histNames[j].Data());
            histPt[j]->Sumw2();
            histPt[j] = (TH1D*)histPt[j]->Clone(Form("%s%s",histNames[j].Data(),casesNames[i].Data()));
            //can[i][j]->cd();
            //histPt[i][j]->Draw();
        }
    //} 


    //FUNCTIONS

    Int_t nparams = 2;
    TF1* fun[_N_PARTICLES_];
    Double_t teffParameter[_N_PARTICLES_] = {0.129759,0.101,0.076};
    //Double_t normParameter[_N_PARTICLES_] = {2.2e6,1e3,1.4e5};
    Double_t normParameter[_N_PARTICLES_] = {4.76e10,3.7e6,8e7};

    
    fun[0] = new TF1("fun0",fitFunctionPtProt,0,2,nparams);
    fun[1] = new TF1("fun1",fitFunctionPtKaon,0,2,nparams);
    fun[2] = new TF1("fun2",fitFunctionPtPion,0,2,nparams);

    for(int j = 0; j < _N_PARTICLES_; j++) {
        fun[j]->SetParameter(0,teffParameter[j]);
        fun[j]->SetParameter(1,normParameter[j]);
    }
   

    //FIITING

    Double_t fitMin[_N_CASES_][_N_PARTICLES_] = {{0.25,0.3,0.15},
                                                {0.4,0.3,0.15},
                                                {0.4,0.3,0.15}};

    Double_t fitMax[_N_CASES_][_N_PARTICLES_] = {{1.8,1,0.7},
                                                {1.8,1,0.7},
                                                {1.8,1,0.7}};

    TF1* funCop[_N_PARTICLES_];
    Double_t minRange[_N_PARTICLES_] ={0,0,0};
    Double_t maxRange[_N_PARTICLES_] ={2,1.2,0.8};

    Double_t tEff[_N_PARTICLES_];
    Double_t tEffEr[_N_PARTICLES_];
    Double_t mXValues[_N_PARTICLES_] = {0.9395653,0.4936770,0.1395699};
    Double_t XErr[_N_PARTICLES_] = {0,0,0};

    //gROOT -> SetBatch(kTRUE);
    
    TFile* fileOut = new TFile(Form("outputPart/outFitPtPart%s.root",casesNames[i].Data()),"RECREATE");
	fileOut->cd();

    TCanvas* can[_N_PARTICLES_];
    //for(int i = 0; i < _N_CASES_; i++) {
    //for(int i = 0; i < 1; i++) {
        for(int j = 0; j < _N_PARTICLES_; j++) {
            can[j] = new TCanvas(Form("%s%s",casesNames[i].Data(),particlesTitles[j].Data()),Form("%s%s",casesNames[i].Data(),particlesTitles[j].Data()),1000,1000);
            histPt[j]->Fit(fun[j],"Q","Q",fitMin[i][j],fitMax[i][j]);

            funCop[j] = (TF1*)fun[j]->Clone(Form("funCop%i",j));
            funCop[j]->SetRange(minRange[j],maxRange[j]);
            funCop[j]->SetLineStyle(2);
            histPt[j]->GetListOfFunctions()->Add(funCop[j]);

            can[j]->cd();
            histPt[j]->Draw();
            histPt[j]->GetFunction(Form("fun%i",j))->Draw("same");
            funCop[j]->Draw("same");
            histPt[j]->Write();

            tEff[j] = fun[j]->GetParameter(0);
            tEffEr[j] = fun[j]->GetParError(0);
        }
    //}

    //TEFF(M) PLOTS
    for(int j = 0; j < _N_PARTICLES_; j ++) {
        cout<<particlesTitles[j].Data()<<endl;
        cout<<"M: "<<mXValues[j]<<endl;
        cout<<"Teff: "<<tEff[j]<<endl;
        cout<<endl;
    }
    TGraphErrors *grTeff = new TGraphErrors(_N_PARTICLES_,mXValues,tEff,XErr,tEffEr);
    TCanvas* can2 = new TCanvas("chuj","chuj",1000,1000);
    can2->cd();
    //grTeff->SetMarkerStyle(20);
    grTeff->SetMarkerSize(1);
    grTeff->Draw("ap");





    fileOut->Save();
	fileOut->Close();
    //gROOT -> SetBatch(kFALSE);

}

void compParticlesFit() {

    //createHistograms(0);
    //createHistograms(1);
    createHistograms(2);

}

