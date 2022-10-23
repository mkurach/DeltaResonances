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
#include "TSystemDirectory.h"
#include "TList.h"
#include <vector>
#include "events2chain.C"
#include "drawStyle.C"

#define _N_PARTICLES_ 3

TChain* addMultEvents2Chain(TString commaSeparatedList, ParticleCoor* aParticle, Int_t* aEvents){

    static StructEvent tStructEvents;
    TChain* tChainParts = new TChain(_PARTICLES_TREE_); //particle chain
    TChain* tChainEvent = new TChain(_EVENTS_TREE_);  //event chain

    tChainParts->SetBranchAddress(_PARTICLE_BRANCH_, aParticle); //linking branch from tree to chain
    tChainEvent->SetBranchAddress(_EVENTS_BRANCH_, &tStructEvents);
  

    TObjArray* arr = commaSeparatedList.Tokenize(",");
    Int_t n = arr->GetEntries(); //number of files loaded

    if(n == 0) {
        cout<<"No files found! Are u blind? Check paths bro!"<<endl;
        delete arr;
        return nullptr; 
    } 
    else {
        for(Int_t i = 0; i < n; i ++){ //for every file...

            TString name = ((TObjString*)arr->At(i))->GetString(); //get it's name...
            
            cerr << "Adding file: " << name << endl;
            if (!tChainParts->Add(name) || !tChainEvent->Add(name)){ //if any of TChains doesn't get filled properlu (Add() method returns 0) -> kill it.
                cout<<"cannot open file "<<name<<"! It doesn't exist or might be broken. TChain gets killed. Whatcha starin' @ m8? Go fix it!"<<endl;
                delete arr;
                return nullptr;
            }
        }
        //if all files added correctly -> print some stuff
        (*aEvents) = tChainEvent->GetEntries();

        cerr<<"Total number of events: "<<(*aEvents)<<endl;
        return tChainParts;
    }
    delete arr;
    return nullptr;

}

void seekParticles(TH1D* H1D[], ParticleCoor particle) {
    Int_t pid = particle.pid;
    if(pid == TMath::Abs(2212) || pid == TMath::Abs(321) || pid == TMath::Abs(211)) {//proton kaon+- pion+-
        TLorentzVector vec;
        vec.SetPxPyPzE(particle.px,particle.py,particle.pz,particle.e);
        vec.Boost(0.,0.,0.629);
        if(vec.Rapidity() > 0.24 && vec.Rapidity() < 1.24){ //midrapidity


            if( pid == TMath::Abs(2212) ) //proton
                H1D[0]->Fill(vec.Pt());
            else if(pid == TMath::Abs(321)) //kaon
                H1D[1]->Fill(vec.Pt());
            else if(pid == TMath::Abs(211)) //pion
                H1D[2]->Fill(vec.Pt());
        }
        
    }

}

void createHistograms(TString aEventDir, TString aOutDir, Int_t aEventFiles, TString inputList) {

    TString particlesTitles[_N_PARTICLES_] = {"proton","kaons","pions"};

    TString histNames[_N_PARTICLES_]= {"PtHistProton","PtHistKaons","PtHistPions"};
    Int_t XBins = 1000;
    Float_t XMin = 0;
    Float_t XMax[_N_PARTICLES_] = {2, 1.2,0.8};

    TString YTitle = "d^{2}N/dp_{T}dy (GeV/c)^{-1}";
    TString XTitles[_N_PARTICLES_] = {"p_{T p} (GeV/c)","p_{T K} (GeV/c)","p_{T #pi} (GeV/c)"};

    //READING

    cout << "Reading events in folder: "<<aEventDir.Data()<< endl;
   	gSystem->MakeDirectory(aOutDir);
   	gROOT->SetBatch(kTRUE);
	
	static ParticleCoor Particle;
	static StructEvent tStructEvents;
    Int_t   Events;
	TChain* Chain;

    if (aEventFiles == -1){ //use this to ruch on a batch farm (slurm)
        Chain = addMultEvents2Chain(inputList,&Particle,&Events);

        if(Chain==nullptr){
            cout<<"No TChain created! Killing analysis"<<endl;
            gROOT -> SetBatch(kFALSE);
            exit(1);
        }
    }
    else { //use for testing purposes, number of files you specify by changing maxFiles default value
        Int_t nFiles = 0;

        Chain = new TChain(_PARTICLES_TREE_);
        TChain* tChainEvent = new TChain(_EVENTS_TREE_); 

        Chain->SetBranchAddress(_PARTICLE_BRANCH_, &Particle); //linking branch from tree to chain
        tChainEvent->SetBranchAddress(_EVENTS_BRANCH_, &tStructEvents);

        TString inputFolder = aEventDir; //path to your data directory

        TSystemDirectory* inputDir = new TSystemDirectory("inputDir", inputFolder);
        TList* files = inputDir->GetListOfFiles(); //gets list of files in designated location

        cout<<"Files loaded:"<<endl;

        if(files==nullptr){
            cout<<"co jest kurwa"<<endl;
            exit(1);
        }

        for (Int_t i = 0; i <= files->LastIndex() && nFiles < aEventFiles; i++){           
            if (((TSystemFile*) files->At(i))->IsDirectory()) continue; //if one of the "files" is directory (directory inside directory) -> skip it.
           
            if(TString(((TSystemFile*)files->At(i))->GetName())){
                TString fileName = inputFolder + "/" + ((TSystemFile*) files->At(i))->GetName(); //get file name
                if(!fileName.Contains("root") || !fileName.Contains("event")) continue; //if non-root file or some other bullshit -> skip it

                Chain->Add(fileName);
                tChainEvent->Add(fileName);

                cout<<fileName<<endl;
                nFiles++;
            }
        }

        Events = tChainEvent->GetEntries();
        cerr << "Total number of events: " << Events << endl;
        delete tChainEvent;
    }

    //HISTOGRAMS

    TH1D* H1D[_N_PARTICLES_];

    for(int i = 0; i < _N_PARTICLES_; i++) {
        H1D[i] = new TH1D(histNames[i].Data(),histNames[i].Data(),XBins,XMin,XMax[i]);
        H1D[i]->GetXaxis()->SetTitle(XTitles[i].Data());
        H1D[i]->GetYaxis()->SetTitle(YTitle);      
    }

    //FILLING HISTOGRAMS

    int e = 0;
    Chain->GetEntry(0); 
	Int_t event_prev = Particle.eventid; //first event number
    Int_t event;

    for (Int_t i = 0; i < Chain->GetEntries() ; i++) {
        Chain->GetEntry(i);
        event = Particle.eventid; 
        seekParticles(H1D,Particle);

        if (event != event_prev) {
            e++;
            event_prev = event;
            if (e%10000==0)
                cout<<"Event: "<<e<<endl;
        }
    }

    //SAVING

    TFile *file = new TFile(aOutDir.Data(),"RECREATE");
	file->cd();

    for(int i = 0; i < _N_PARTICLES_; i++) {
        H1D[i]->Write();
    }

    file->Save();
	file->Close();

    
}

int makeParticles(TString inputlist = "", TString outfile = "", Long64_t nDesEvents = -1, Int_t maxFiles = -1) {
	
	gROOT -> SetBatch(kTRUE); 

    createHistograms("/u/mkurach/lustre/hades/user/kjedrzej/HubbDeltLowT/H100E0D2femto",outfile,maxFiles,inputlist);
    //createHistograms("/u/mkurach/lustre/hades/user/kjedrzej/HubbDeltMotornenko/H225E4D4femto",outfile,maxFiles,inputlist);
    //createHistograms("/u/mkurach/lustre/hades/user/kjedrzej/HubbDeltMotoMoto/H165E6D4femto",outfile,maxFiles,inputlist);

	gROOT -> SetBatch(kFALSE);
	return 0;
}
