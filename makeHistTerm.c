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

//makro do robienia 4 rodzajów wykresów, odpowiadające tym z artykułu
//na wejście potrzebuje plików rootowych z therminatora
//wypluwa pliki rootowe z gotowymi histogramami (ale nie gotowymi ładnymi rysunkami, to robi makeHistComp)

//NIE UFAC TCHAINOWI ZOSTALAM OSZUKANA ZAPOMNIALAM O JEDNYM GET ENTRY !!!
//TO ZNACZY JEST SPOKO ALE BE CAREFUL
//BO GET ENTRY JEST TRICKY

//SCALE WYWOLUJE SUMW2, JESLI NIE CHCE SUMW2 TRZEBA DAC INNA OPCJE "nosw2"

#define _N_PAIRS_ 2 //2 pairs pi+p, pi-p
#define _N_FIGURES_ 5 //5 different types of figures to draw
#define _N_HIST_ 10 //maximum of 10 different histograms per figure
#define _N_PARTICLES_ 4 //collecting 4 things: 2 pairs, delta++ and delta0

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

void seekParticles(Int_t entry, Int_t pid, Int_t fatherpid, vector<Int_t> *entriesArr) {
	if (pid == 2212) { // p
		if(fatherpid == 2224)   //delta++ 
			entriesArr[0].push_back(entry);
			
	    else if (fatherpid == 2114) //delta0
	        entriesArr[1].push_back(entry);
    }
    else if (pid == 211) { // pi+
         if(fatherpid == 2224) 
			entriesArr[0].push_back(entry);
	}
	else if (pid == -211) { // pi-
	     if (fatherpid == 2114)
			entriesArr[1].push_back(entry);		
	}
	else if(pid == 2224) //delta++
		entriesArr[2].push_back(entry);
	else if(pid == 2114) //delta0
		entriesArr[3].push_back(entry);
}

void clearVectors(vector<Int_t> *entriesArr, vector<TLorentzVector> *pairsArr) {
	for(int i = 0; i < _N_PARTICLES_; i++) {
		entriesArr[i].clear();
		if (i < _N_PAIRS_)
			pairsArr[i].clear();
	}
}

void makeLorentzVectors(vector<Int_t> *entriesArr, TChain *chain, vector<TLorentzVector> *pairsArr, ParticleCoor &particle) {
	TLorentzVector v1,v2;
	Int_t fathereid;
	for (int i = 0; i < _N_PAIRS_; i++) {
		for (size_t j = 0; j < entriesArr[i].size(); j+=2) {
			chain->GetEntry(entriesArr[i][j]); //get first particle from the pair 
			fathereid = particle.fathereid; //get its father event id
			for(int k = 0; k < entriesArr[i+2].size(); k++){ //go through found deltas
				chain->GetEntry(entriesArr[i+2][k]); //get delta
				if(particle.eid == fathereid && particle.pid == particle.fatherpid) {//if you found father of the exact proton and it is primordial delta 
					chain->GetEntry(entriesArr[i][j]); //get the first particle from the pair once again
					v1.SetPxPyPzE(particle.px,particle.py,particle.pz,particle.e);
					v1.Boost(0.,0.,0.629); //changing to lab frame of reference
					chain->GetEntry(entriesArr[i][j+1]);
					v2.SetPxPyPzE(particle.px,particle.py,particle.pz,particle.e);
					v2.Boost(0.,0.,0.629);
					pairsArr[i].push_back(v1+v2);

				}
			}			
		}
	}
}

int histIndexPt(TLorentzVector vec) {
	Double_t pt = vec.Pt();
	Double_t y = vec.Rapidity();
	if (y > 0 && y < 1.8) {
		if (pt < 0.15)		return 0;
		else if (pt >= 0.15 && pt < 0.3)		return 1;
		else if (pt >= 0.3 && pt < 0.45)		return 2;
		else if (pt >= 0.45 && pt < 0.6)		return 3;
		else if (pt >= 0.6 && pt < 0.75)		return 4;
		else if (pt >= 0.75 && pt < 0.9)		return 5;
		else if (pt >= 0.9 && pt < 1.05)		return 6;
		else if (pt >= 1.05 && pt < 1.2)		return 7;
		else if (pt >= 1.2 && pt < 1.35)		return 8;
		else if (pt >= 1.35 && pt < 1.6)		return 9;
		else return -1;
	}
	else 		return -1;

}

int histIndexY(TLorentzVector vec) {
	Double_t y = vec.Rapidity();
	Double_t m = vec.M();
	if (m > 1.1 && m < 1.4) {
		if (y < 0.14)		return 0;
		else if (y >= 0.14 && y < 0.34)		return 1;
		else if (y >= 0.34 && y < 0.49)		return 2;
		else if (y >= 0.49 && y < 0.64)		return 3;
		else if (y >= 0.64 && y < 0.74)		return 4;
		else if (y >= 0.74 && y < 0.84)		return 5;
		else if (y >= 0.84 && y < 0.99)		return 6;
		else if (y >= 0.99 && y < 1.14)		return 7;
		else if (y >= 1.14 && y < 1.34)		return 8;
		else if (y >= 1.34 && y < 1.8)		return 9;
		else return -1;
	}
	else 		return -1;
	

}

int histIndexM(TLorentzVector vec) {
	Double_t y = vec.Rapidity();
	Double_t m = vec.M();
	if(y >= 0.24 && y <= 1.24) {
		if (m >= 1 && m < 1.1)		return 0;
		else if (m >= 1.1 && m < 1.15)		return 1;
		else if (m >= 1.15 && m < 1.2)		return 2;
		else if (m >= 1.2 && m < 1.25)		return 3;
		else if (m >= 1.25 && m < 1.3)		return 4;
		else if (m >= 1.3 && m < 1.35)		return 5;
		else if (m >= 1.35 && m < 1.4)		return 6;
		else if (m >= 1.4 && m < 1.45)		return 7;
		else if (m >= 1.45 && m < 1.5)		return 8;
		else if (m >= 1.5 && m < 1.6)		return 9;
		else return -1;
	}
	else return -1;

}




void createHistograms(TString aEventDir, TString aOutDir, Int_t aEventFiles, TString inputList) {
	
	TString pairsTitles[_N_PAIRS_] = { "#pi^{+}p", "#pi^{-}p"};
	TString pairsTitlesDiff[_N_PAIRS_] = {"PiPlusP","PiMinusP"};

	vector<Int_t> entriesArr[_N_PARTICLES_];
	vector<TLorentzVector> pairsArr[_N_PAIRS_];

    TString histNames[_N_FIGURES_] = {"MHist","MPtHist","PtYHist", "YHist","PtMHist"};
    Int_t XBins[_N_FIGURES_] = {1000, 1000, 1000, 1000,1000};
    Float_t XMin[_N_FIGURES_] = {1, 1, 0, -2.2, 0};
	Float_t XMax[_N_FIGURES_] = {1.6, 1.6, 1.5, 2.2, 1.5};
    TString YTitles[_N_FIGURES_] = {"dN/dM (GeV/c^{2})^{-1}","dN/dM (GeV/c^{2})^{-1}","d^{2}N/dp_{T}dy (GeV/c)^{-1}", "dN/dy", "d^{2}N/dp_{T}dM"};
	TString XTitles[_N_FIGURES_] = {"M_{#pi^{+} p} (GeV/c^{2})","M_{#pi^{-} p} (GeV/c^{2})","p_{T} (GeV/c)","rapidity","p_{T} (GeV/c)"};
	
	TString PtRanges[_N_HIST_] = {"p_{T} < 0.15 GeV/c", "0.15 #leq p_{T} < 0.3 GeV/c", "0.3 #leq p_{T} < 0.45 GeV/c","0.45 #leq p_{T} < 0.6 GeV/c","0.6 #leq p_{T} < 0.75 GeV/c","0.75 #leq p_{T} < 0.9 GeV/c","0.9 #leq p_{T} < 1.05 GeV/c","1.05 #leq p_{T} < 1.2 GeV/c","1.2 #leq p_{T} < 1.35 GeV/c","1.35 #leq p_{T} < 1.6 GeV/c"};   
	TString YRanges[_N_HIST_] = {"0 #leq y < 0.14", "0.14 #leq y < 0.34", "0.34 #leq y < 0.49","0.49 #leq y < 0.64", "0.64 #leq y < 0.74", "0.74 #leq y < 0.84", "0.84 #leq y < 0.99", "0.99 #leq y < 1.14", "1.14 #leq y 1.34", "1.34 #leq y #leq 1.8"};
	TString MRanges[_N_HIST_] = {"1 #leq M < 1.1","1.1 #leq M < 1.15","1.15 #leq M < 1.2","1.2 #leq M < 1.25","1.25 #leq M < 1.3","1.3 #leq M < 1.35","1.35 #leq M < 1.4","1.4 #leq M < 1.45","1.45 #leq M < 1.5","1.5 #leq M < 1.6"};
    string colorHex[] = {gROOT->GetColor(15)->AsHexString(),"#ff6666","#0099cc","#ffcc00","#6666ff","#669966","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff","#ffffff"};
     
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
    
    //HISTOGRAMS - INITILIZE
    
    TH1D* H1D[_N_PAIRS_][_N_FIGURES_][_N_HIST_];


    for (int i = 0; i < _N_PAIRS_; i++ ){ //for every pair
		for (int j = 0; j < _N_FIGURES_ ; j++) { //for every figure
			H1D[i][j][0] = new TH1D(Form("%s%s",pairsTitlesDiff[i].Data(),histNames[j].Data()),"", XBins[j], XMin[j], XMax[j]);
			//H1D[i][j][0]->Sumw2(); //NIE CHCE TUTAJ BO ROBIE TO NA KONIEC bo scale psuje
			if (j == 0 || j == 1)
				H1D[i][j][0]->GetXaxis()->SetTitle(XTitles[i]);
			else
				H1D[i][j][0]->GetXaxis()->SetTitle(XTitles[j]);
			H1D[i][j][0]->GetYaxis()->SetTitle(YTitles[j]);
			
			
			if(j == 1 || j == 2 || j == 4) { //if it is figure with multiple histograms on it
				for (int k = 0; k < _N_HIST_; k++) {
					if (j == 1 ) {
					    H1D[i][j][k] = (TH1D*)  H1D[i][j][0]->Clone(Form("%s%s%i",pairsTitlesDiff[i].Data(),histNames[j].Data(),k));
						H1D[i][j][k]->SetTitle(Form("%s",PtRanges[k].Data()));
					}
					else if (j == 2) {
						H1D[i][j][k] = (TH1D*)  H1D[i][j][0]->Clone(Form("%s%s%i",pairsTitlesDiff[i].Data(),histNames[j].Data(),k));
						H1D[i][j][k]->SetTitle(Form("%s",YRanges[k].Data()));
					}
					else {
						H1D[i][j][k] = (TH1D*)  H1D[i][j][0]->Clone(Form("%s%s%i",pairsTitlesDiff[i].Data(),histNames[j].Data(),k));
						H1D[i][j][k]->SetTitle(Form("%s",MRanges[k].Data()));

					}
				}		    
			}
		}
	}
	

	Chain->GetEntry(0); 
	Int_t event_prev = Particle.eventid; //first event number
    Int_t event;

    int e = 0;

	int indPt;
	int indY;
	int indM;
    
    for (Int_t i = 0; i < Chain->GetEntries() ; i++) { 
		Chain->GetEntry(i);
        event = Particle.eventid; 
        //LOOKING FOR PAIRS 
        if (event == event_prev)
             seekParticles(i,Particle.pid,Particle.fatherpid,entriesArr); //collecting indexes of entry for particles
        else { //when one event ends
			e++; 
			makeLorentzVectors(entriesArr,Chain,pairsArr,Particle);



			//FILLING HISTOGRAMS
			for(int j = 0; j < _N_PAIRS_; j++) { //for every pair
				for (auto lorentz : pairsArr[j])  {

					indPt = histIndexPt(lorentz);
					indY = histIndexY(lorentz);
					indM = histIndexM(lorentz);

					if(lorentz.Rapidity() > 0 && lorentz.Rapidity() < 1.8)
						H1D[j][0][0]->Fill(lorentz.M()); 

					if(indPt >= 0) 
						H1D[j][1][indPt]->Fill(lorentz.M());

					if(indY >= 0)
						H1D[j][2][indY]->Fill(lorentz.Pt());

					if(lorentz.M() > 1.1 && lorentz.M() < 1.4)
						H1D[j][3][0]->Fill(lorentz.Rapidity()); 

					if(indM >= 0)	
						H1D[j][4][indM]->Fill(lorentz.Pt());
				}
			}
			
			
			clearVectors(entriesArr,pairsArr);		
			event_prev = event;
			
			Chain->GetEntry(i);
			seekParticles(i,Particle.pid,Particle.fatherpid,entriesArr); //at the end collect new particle
			if (e%10000==0)
				cout<<"Event: "<<e<<endl;
		}
        //if (e==100)
			//break;
	
	}
	

	//SCALING
	/*for (int i = 0; i < _N_PAIRS_; i++) {
		for(int j = 0; j < _N_FIGURES_; j++) {
			H1D[i][j][0]->Scale(1.0/(Events*dX[j])); //turning off the sumw2: option"nosw2"
			if (j == 1 || j == 2) {
				for (int k = 1; k < _N_HIST_; k++)
					H1D[i][j][k]->Scale(1.0/(Events*dX[j])); 

			}
		}
	}*/

	//PLOTTING

	//TCanvas* Canvases[_N_FIGURES_][_N_HIST_];
	TFile *file = new TFile(aOutDir.Data(),"RECREATE");
	file->cd();

	for (int i = 0; i < _N_FIGURES_; i++) {

		//Canvases[i][0] = new TCanvas(Form("%s %i",histNames[i].Data(),0),Form("%s %i",histNames[i].Data(),0),1000,1000);
		//Canvases[i][0]->Divide(2);
		for (int k = 0; k < _N_PAIRS_; k++) {
			//Canvases[i][0]->cd(k+1);
			//H1D[k][i][0]->Draw();
			H1D[k][i][0]->Write();
		}
		//Canvases[i][0]->Write();


		if (i == 1 || i == 2 || i == 4) {
			for (int j = 1; j < _N_HIST_; j++) {
				//Canvases[i][j] = new TCanvas(Form("%s %i",histNames[i].Data(),j),Form("%s %i",histNames[i].Data(),j),1000,1000);	
				//Canvases[i][j]->Divide(2);
				for (int k = 0; k < _N_PAIRS_; k++) {
					//Canvases[i][j]->cd(k+1);
					//H1D[k][i][j]->Draw();
					H1D[k][i][j]->Write();
				}
				//Canvases[i][j]->Write();
			}
		}
	}
	 
	file->Save();
	file->Close();
	gROOT->SetBatch(kFALSE);	
	
}


int makeHistTerm(TString inputlist = "", TString outfile = "", Long64_t nDesEvents = -1, Int_t maxFiles = -1) {
	
	gROOT -> SetBatch(kTRUE); 

    //createHistograms("/u/mkurach/lustre/hades/user/kjedrzej/HubbDeltLowT/H100E0D2femto",outfile,maxFiles,inputlist);
    //createHistograms("/u/mkurach/lustre/hades/user/kjedrzej/HubbDeltMotornenko/H225E4D4femto",outfile,maxFiles,inputlist);
    createHistograms("/u/mkurach/lustre/hades/user/kjedrzej/HubbDeltMotoMoto/H165E6D4femto",outfile,maxFiles,inputlist);

	gROOT -> SetBatch(kFALSE);
	return 0;
}

//jak lokalnie: zmieniam w argumencie funkcji outfile "np. ~/test.root" i max files (na inny niż -1 bo -1 to na kostke)
//jak kostka: outfile = "" i maxFiles = -1
