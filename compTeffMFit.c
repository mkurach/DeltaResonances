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
#define _N_MRANGES_ 10

Double_t fitFunctionTeffM(Double_t *x, Double_t *par) {
    if(x[0] >= 1 && x[0] <= 1.6)
        return TMath::Power(par[0],2)/2*x[0]+par[1];
    else    
        return 0;
}

void compTeffMFit() {

    TGraphErrors* grTeff[_N_CASES_][_N_PAIRS_];

    gROOT -> SetBatch(kTRUE);

    TFile* file[_N_CASES_];
    TString fileNames[_N_CASES_]= {"outputFit/outFitPtMCaseA.root","outputFit/outFitPtMCaseB.root","outputFit/outFitPtMCaseC.root"};
    TString pairsTitles[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString pairsNames[_N_PAIRS_] = {"#pi^{+}p","#pi^{-}p"};
    TString casesNames[_N_CASES_] = {"CaseA","CaseB","CaseC"};

    TCanvas * can[_N_CASES_][_N_PAIRS_];
    for(int i = 0; i < _N_CASES_; i++){
        file[i] = new TFile(fileNames[i].Data());
        for(int j = 0; j < _N_PAIRS_; j++) {
            grTeff[i][j] = (TGraphErrors*)file[i]->Get("Graph");
            can[i][j] = new TCanvas(Form("%s%s",casesNames[i].Data(),pairsTitles[j].Data()),Form("%s%s",casesNames[i].Data(),pairsTitles[j].Data()),1000,1000);
            can[i][j]->cd();
            grTeff[i][j]->Draw("apl");
        }
    }

    //FUNCTION

    Int_t nparams = 2;
    TF1 *fun = new TF1("fun",fitFunctionTeffM,1,1.6,nparams);
    //0 - beta, 1 - T_

    fun->SetParLimits(0,0,1);
    fun->SetParameter(0,0.5);

    fun->SetParLimits(1,0,0.2);
    fun->SetParameter(1,0.1);

    //FITTING

    /*Double_t beta[_N_CASES_][_N_PAIRS_];
    Double_t t[_N_CASES_][_N_PAIRS_];

    TFile* fileOut = new TFile("outputFit/outFitTeffM.root","RECREATE");
	fileOut->cd();
    for(int i = 0; i < _N_CASES_; i++) {
        for(int j = 0; j < _N_PAIRS_; j++) {
            cout<<casesNames[i].Data()<<"  "<<pairsTitles[j].Data()<<endl;
            grTeff[i][j]->Fit("fun","","",1,1.3); 
            grTeff[i][j]->Write();
            beta[i][j] = fun->GetParameter(0);
            t[i][j] = fun->GetParameter(1);
        }
    }
    fileOut->Save();
	fileOut->Close();
    gROOT -> SetBatch(kFALSE);

    //PRINTING
    //TEORETICAL VALUES
    Double_t betaTh[_N_CASES_] = {0.525672, 0.469742, 0.50362};
    Double_t tTh[_N_CASES_] = {49.6, 70.3, 63.1}; //(MeV)

    for(int i = 0; i < _N_CASES_; i++){   
        cout<<casesNames[i].Data()<<":"<<endl;
        for(int j = 0; j < _N_PAIRS_; j++) {
            cout<<"\t"<<pairsTitles[j].Data()<<":\n"<<endl;
            cout<<"\t\tBeta: "<<beta[i][j];
            cout<<"\tT: "<<t[i][j]*1e3<<" (MeV)"<<endl;
        }
        cout<<"\tReal parameters:\n"<<endl;
        cout<<"\t\tBeta: "<<betaTh[i];
        cout<<"\tT: "<<tTh[i]<<" (MeV)"<<endl;
    }
*/









}