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

Double_t fitFunctionM(Double_t *x, Double_t *par) {

    /*Double_t Ecm = 2.42; //GeV
    Double_t mN = 0.93;
    Double_t q = TMath::Sqrt(2*Ecm*mN+TMath::Power(Ecm,2));
    Double_t mu = 0.18;*/
    if(x[0] >= 1 && x[0] <= 1.6)
        //return TMath::Power(q,3)/(TMath::Power(q,3)+TMath::Power(mu,3))*par[0]/(1+4*TMath::Power((x[0]-par[1])/par[2],2));
        return par[0]/(1+4*TMath::Power((x[0]-par[1])/par[2],2));
    else    
        return 0;
}


void compMFit() {

    TH1D* histM[_N_CASES_][_N_PAIRS_];

    TFile* file[_N_CASES_];
    TString fileNames[_N_CASES_]= {"outputBig/outCaseA.root","outputBig/outCaseB.root","outputBig/outCaseC.root"};
    TString pairsTitles[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString pairsNames[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString casesNames[_N_CASES_] = {"CaseA","CaseB","CaseC"};

    Int_t events = 10e6;
    Int_t XBins = 1000;
    Float_t XMin = 1;
	Float_t XMax = 1.6;
	Float_t dX = (XMax-XMin)/XBins;
    Float_t scale = 1.0/(events*dX);
    Int_t rebin = 10; 

    TCanvas * can[_N_CASES_][_N_PAIRS_];
    for(int i = 0; i < _N_CASES_; i++){
        file[i] = new TFile(fileNames[i].Data());
        for(int j = 0; j < _N_PAIRS_; j++){
            can[i][j] = new TCanvas(Form("%s%sMFitting",casesNames[i].Data(),pairsTitles[j].Data()),Form("%s%sMFitting",casesNames[i].Data(),pairsTitles[j].Data()),1000,1000);
            histM[i][j] = (TH1D*)file[i]->Get(Form("%sMHist",pairsTitles[j].Data()))->Clone(Form("%s%sMFitHist",casesNames[i].Data(),pairsTitles[j].Data()));
            //histM[i][j] = histM[i][j]->Clone(Form("%s%sMFitHist",casesNames[i].Data(),pairsTitles[j].Data()));        
            histM[i][j]->Rebin(rebin);
            histM[i][j]->Scale(scale/rebin);
            //can[i][j]->cd();
            //histM[i][j]->Draw();
        }
    }

    gROOT -> SetBatch(kTRUE); 
    
    //FUNCTION

    Int_t nparams = 3;
    TF1 *fun = new TF1("fun",fitFunctionM,XMin,XMax,nparams);
    //0 - sigma0 - normalizacja , 1 - m0, 2 -gamma0 
    fun->SetParLimits(0,3,27);
    fun->SetParLimits(1,1.125,1.25);
    fun->SetParLimits(2,1e-10,1);

    fun->SetParameters(1,1.232,0.117);


    //DRAWING AND SAVING
    TFile* fileOut = new TFile("outputFit/outFitM.root","RECREATE");
	fileOut->cd();

    Double_t m[_N_CASES_][_N_PAIRS_];
    Double_t gamma[_N_CASES_][_N_PAIRS_];

    for(int i = 0; i < _N_CASES_; i++){   
        for(int j = 0; j < _N_PAIRS_; j++) {
            can[i][j]->cd();
            cout<<casesNames[i].Data()<<"  "<<pairsTitles[j].Data()<<endl;
            histM[i][j]->Fit("fun","","",1.15,1.250);
            m[i][j] = fun->GetParameter(1);
            gamma[i][j] = fun->GetParameter(2);
            histM[i][j]->Write();
            //can[i][j]->SaveAs(Form("outputFit/%s%sMFitted.png",casesNames[i].Data(),pairsTitles[j].Data()));
        }
    }

    //PRINTIG PARAMETERS   
    for(int i = 0; i < _N_CASES_; i++){   
        cout<<casesNames[i].Data()<<":"<<endl;
        for(int j = 0; j < _N_PAIRS_; j++) {
            cout<<"\t"<<pairsTitles[j].Data()<<":\n"<<endl;
            cout<<"\t\tMass: "<<m[i][j]<<" (GeV/c^{2})";
            cout<<"\tGamma: "<<gamma[i][j]<<" (GeV/c^{2})"<<endl;

            
        }
    }

    fileOut->Save();
    fileOut->Close();

    gROOT -> SetBatch(kFALSE); 

}