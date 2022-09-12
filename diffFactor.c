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
#define _N_FACTORS_ 4




void diffFactor() {

    //READ EVMIX HISTOGRAMS
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

    //FACTORS

    Double_t factors[_N_CASES_][_N_PAIRS_][_N_FACTORS_]; 
    Int_t minRange[_N_FACTORS_] = {histBack[0][0]->FindBin(1.3), histBack[0][0]->FindBin(1.6), histBack[0][0]->FindBin(1.1),histBack[0][0]->FindBin(1.24)};
    Int_t maxRange[_N_FACTORS_] = {histBack[0][0]->FindBin(1.4), histBack[0][0]->FindBin(1.7), histBack[0][0]->FindBin(1.2),histBack[0][0]->FindBin(1.34)};
    Double_t licznik; //sigback
    Double_t mianownik; //back   

    for(int i = 0; i < _N_CASES_; i++) {
        cout<<"case: "<<i<<endl;
        for(int j = 0; j < _N_PAIRS_; j++) {
            cout<<"para: "<<j<<endl;
            for(int k = 0; k < _N_FACTORS_; k ++) {
                licznik = histSigBack[i][j]->Integral(minRange[k],maxRange[k]);
                mianownik = histBack[i][j]->Integral(minRange[k],maxRange[k]);
                factors[i][j][k] = licznik/mianownik;
                cout<<"faktor: "<<factors[i][j][k]<<endl;    

            }
            cout<<"****"<<endl;
        }
    }

    TH1D* histDiffFac[_N_CASES_][_N_PAIRS_][_N_FACTORS_];
    TString factorsNames[_N_FACTORS_] = {"srodek","koncowka","maksimum","poDelcie"};

    TFile *file = new TFile("outputSig/diffFactor.root","RECREATE");
	file->cd();

    for(int i = 0; i < _N_CASES_; i++) {
        for(int j = 0; j < _N_PAIRS_; j++) {
            for(int k = 0; k < _N_FACTORS_; k ++) {
                histDiffFac[i][j][k] = (TH1D*) histBack[i][j]->Clone(Form("%s%s%s",casesNames[i].Data(),pairsTitles[j].Data(),factorsNames[k].Data()));
                histDiffFac[i][j][k]->Scale(-factors[i][j][k]);
                histDiffFac[i][j][k]->Add(histSigBack[i][j]);
                histDiffFac[i][j][k]->Write();


   

            }
        }
    }
    
    file->Save();
	file->Close();


}