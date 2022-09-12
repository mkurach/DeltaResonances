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
#include <vector>
#include "TSystemDirectory.h"
#include "TList.h"
#include "events2chain.C"
#include "drawStyle.C"
#include <stdlib.h>
#include "ParticleCoor.h"
#include "StructEvent.h"

#define _N_PAIRS_ 2 
#define _N_HIST_ 3 
// 0 - back: (p + every prev pion) + (pion + every prev proton)
// 1 - sig + back: p + every this pion
// 2 - sig: difference between 2 last ones

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

int colors[]={1, 600, 629, 414, 802, 880, 819, 922,433,618}; // kBlack, kBlue, kRed, kGreen-2, kOrange+2, kGray, kViolet, kSpring
int markers[]= {20,21,24,25,28,34,47,43}; 

void styleSet(){ //od Mateusza
  gStyle->SetPalette(kRainBow);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(5);
  gStyle->SetErrorX(0);     
  gStyle->SetLineStyleString(22,"80 18 12 18 12 12"); // special style for the line
  gStyle->SetEndErrorSize(5);   // define end width of error bars
  gStyle->SetCanvasColor(10);
  gStyle->SetPadColor(10);
}

void makePaveText(TCanvas *can, TString text, double x1, double y1, double x2, double y2, double f = 0.05) { //1 - lewy gorny, 2 - prawy dolny, x i y rosna normalnie, nie jak w javie 
    TPaveText *pt = setOPT_text2(text,x1,y1,x2,y2,kBlack,f);
    can->cd();
    pt->Draw("same");

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

    TLegend* legend	= new TLegend(0.6,0.5,0.9,0.9, "",	"brNDC");
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
        histTab[i]->SetMarkerColor(colors[i]);
        histTab[i]->SetLineColor(colors[i]);

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

void seekParticles(vector<ParticleCoor> &protonsThisEv, vector<ParticleCoor> *piThisEv, ParticleCoor &particle) {
    if(particle.pid == 2212 ) //proton
        protonsThisEv.push_back(particle);
    else if(particle.pid == 211) //pi+
        piThisEv[0].push_back(particle);
    else if (particle.pid == -211) //pi-
        piThisEv[1].push_back(particle);

}

void switchEv(vector<ParticleCoor> &protonsThisEv, vector<ParticleCoor> &protonsPrevEv,vector<ParticleCoor> *piThisEv, vector<ParticleCoor> *piPrevEv) {
    protonsPrevEv.clear();
    for(auto prot : protonsThisEv )
        protonsPrevEv.push_back(prot);
    protonsThisEv.clear(); //throw away protons


    for(int i = 0; i < _N_PAIRS_; i ++) {
        piPrevEv[i].clear();
        for(auto pi : piThisEv[i]) //throw every pi to the previous event, clean current one
            piPrevEv[i].push_back(pi); 
        piThisEv[i].clear();
                
    }
    
}

void mixPairs(vector<ParticleCoor> &protonsThisEv, vector<ParticleCoor> &protonsPrevEv, vector<ParticleCoor> *piThisEv, vector<ParticleCoor> *piPrevEv, TH1D* H1D[][_N_HIST_],int e) {
    
    //FILLING THE HISTOGRAMS

    TLorentzVector v1,v2,v3,v4,v5;

    if(piPrevEv[0].size()!=0 && piThisEv[0].size()!=0 && piPrevEv[1].size()!=0 && piThisEv[1].size()!=0) {

        for(auto prot : protonsThisEv){ //for every found proton
            v1.SetPxPyPzE(prot.px,prot.py,prot.pz,prot.e);
            v1.Boost(0.,0.,0.629);
            for(int i = 0; i < _N_PAIRS_; i++){ //for pi+ and pi-   
                //every pion from this event
                for (auto pion : piThisEv[i]) {
                    v2.SetPxPyPzE(pion.px,pion.py,pion.pz,pion.e);
                    v2.Boost(0.,0.,0.629);
                    H1D[i][1]->Fill((v1+v2).M()); //fill sig + back
                }

                //every pion from prev event
                for(auto pion : piPrevEv[i]){
                    v3.SetPxPyPzE(pion.px,pion.py,pion.pz,pion.e);
                    v3.Boost(0.,0.,0.629);
                    H1D[i][0]->Fill((v1+v3).M()); //fill back
                }
            
            }
        }
        
        //pion this ev with every proton from prev event
        for (int i = 0; i < _N_PAIRS_; i ++){
            for (auto pion : piThisEv[i]) {
                v4.SetPxPyPzE(pion.px,pion.py,pion.pz,pion.e);
                v4.Boost(0.,0.,0.629);   
                for (auto prot : protonsPrevEv) {
                    v5.SetPxPyPzE(prot.px,prot.py,prot.pz,prot.e);
                    v5.Boost(0.,0.,0.629);
                    H1D[i][0]->Fill((v4+v5).M()); //fill back
                }


            }
        }
    
    }

    switchEv(protonsThisEv, protonsPrevEv, piThisEv,piPrevEv);
}


void createHistograms(TString aEventDir, TString OutDir, Int_t aEventFiles, TString inputList) {
// 0 - back: (p + every prev pion) + (pion + every prev proton)
// 1 - sig + back: p + every this pion
// 2 - sig: difference between 2 last ones

    TString pairsTitlesDiff[_N_PAIRS_] = {"PiPlusP","PiMinusP"};
    TString histNames[_N_HIST_] = {"Back","SigBack","DiffHist"};

    Int_t XBins = 1000;
    Float_t XMin = 1;
    Float_t XMax = 1.7;
    Float_t dX = (XMax - XMin)/XBins;
    TString XTitles[_N_PAIRS_] = {"M_{#pi^{+} p} (GeV/c^{2})","M_{#pi^{-} p} (GeV/c^{2})"};
    TString YTitle = "dN/dM (GeV/c^{2})^{-1}";

    //READING
    cout << "Reading events in folder: "<<aEventDir.Data()<< endl;
   	gSystem->MakeDirectory(OutDir);
	
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



    TH1D* H1D[_N_PAIRS_][_N_HIST_];
    for(int i = 0; i < _N_PAIRS_; i++) {
        for (int j = 0; j < _N_HIST_; j++) {
            H1D[i][j] = new TH1D(Form("%s%s",pairsTitlesDiff[i].Data(),histNames[j].Data()),"",XBins,XMin,XMax);
            H1D[i][j]->Sumw2();
            H1D[i][j]->GetXaxis()->SetTitle(XTitles[i]);
			H1D[i][j]->GetYaxis()->SetTitle(YTitle);
        }
    }

    Chain->GetEntry(0); 
	Int_t event_prev = Particle.eventid; //first event number
    Int_t event;
    bool firstEv = true; 

    vector<ParticleCoor> protonsThisEv;
    vector<ParticleCoor> protonsPrevEv;
    vector<ParticleCoor> piThisEv[_N_PAIRS_];
    vector<ParticleCoor> piPrevEv[_N_PAIRS_];
    int e = 0;

    for(Int_t i = 0; i < Chain->GetEntries(); i++) {
        Chain->GetEntry(i);
        event = Particle.eventid;
        if (event == event_prev)
            seekParticles(protonsThisEv,piThisEv,Particle);
        else {//when one event ends
            e++;
            if(firstEv) {
                switchEv(protonsThisEv,protonsPrevEv, piThisEv, piPrevEv);
                firstEv = false;
            }
            else
                mixPairs(protonsThisEv, protonsPrevEv, piThisEv, piPrevEv,H1D,e); //filling  histograms
            

            event_prev = event;
            Chain->GetEntry(i);
            seekParticles(protonsThisEv,piThisEv,Particle);
            if(e%10000==0)  
                cout<<"Event: "<<e<<endl;
        }
        //if(e==100)
           // break;

    }    
    
    TFile *file = new TFile(OutDir.Data(),"RECREATE");
	file->cd();

    for(int i = 0; i < _N_PAIRS_; i++) {
        for(int j = 0; j < 2; j++){ //save first 2 ones
            H1D[i][j]->Write();
        }
    }   

    //FILLING [2] HISTOGRAM
    
    
    Int_t minRange = H1D[0][0]->FindBin(1.3);
    Int_t maxRange = H1D[0][0]->FindBin(1.4);
    for (int i = 0; i < _N_PAIRS_; i++) {
        H1D[i][0]->Scale( H1D[i][1]->Integral(minRange,maxRange) / H1D[i][0]->Integral(minRange,maxRange) ); //signal+backgronud/background 

    }

    for(int i = 0; i < _N_PAIRS_; i++) {
        H1D[i][2] = (TH1D*) H1D[i][1]->Clone(Form("%s%s",pairsTitlesDiff[i].Data(),histNames[2].Data())); //2 = 1 - 0
        H1D[i][2]->Add(H1D[i][0],-1);    
        H1D[i][2]->Write();    
        
    }

    //SCALING
    /*for (int i = 0; i < _N_PAIRS_; i++) {
		for(int j = 0; j < _N_HIST_; j++)
			H1D[i][j]->Scale(1.0/(Events*dX));
	}*/
   	 
	file->Save();
	file->Close();

    //PLOTTING
    /*TString entries[3] = {"combinatorial background","signal + background","signal"};
    TCanvas* can[_N_PAIRS_];

    for(int i = 0; i < _N_PAIRS_; i++) {
        can[i] = new TCanvas(pairsTitlesDiff[i].Data(),pairsTitlesDiff[i].Data(),1000,1000);
        multiplePlot(H1D[i],can[i],entries,3);
        makePaveText(can[i],Case,0.73,0.4,0.99,0.5,0.05);
    }*/
     


}


int makeHistEvMix(TString inputlist = "", TString outfile = "", Long64_t nDesEvents = -1, Int_t maxFiles = -1) {
    
    gROOT -> SetBatch(kTRUE);      

    //createHistograms("/u/mkurach/lustre/hades/user/kjedrzej/HubbDeltLowT/H100E0D2femto",outfile,maxFiles,inputlist);
    //createHistograms("/u/mkurach/lustre/hades/user/kjedrzej/HubbDeltMotornenko/H225E4D4femto",outfile,maxFiles,inputlist);
    createHistograms("/u/mkurach/lustre/hades/user/kjedrzej/HubbDeltMotoMoto/H165E6D4femto",outfile,maxFiles,inputlist);

    gROOT -> SetBatch(kFALSE);
 
    return 0;
}

//jak lokalnie: zmieniam w argumencie funkcji outfile i max files (na inny niż -1 bo -1 to na kostke)






