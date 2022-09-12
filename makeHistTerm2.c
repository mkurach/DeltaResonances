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
#include "events2chain.C"
#include "drawStyle.C"
#include <fstream>
//#include "makeHistComp.c"

//makro do robienia dodatkowych histogramów do sprawdzania poprawności rzeczy
//przyjmuje pliki rootowe z therminatora
//wypluwa gotowe histogramy

#define _N_HIST_ 4 // masa pary pi+p; masa pary pi-p; masa delty++; masa delty0; 
#define _N_PAIRS_ 2
#define _N_PARTICLES_  4 //

int colors[]={1, 600, 629, 414, 802, 880, 819, 922,433,618}; // kBlack, kBlue, kRed, kGreen-2, kOrange+2, kGray, kViolet, kSpring
int markers[]= {20,2,33,21,24,25,28,34,47,43}; 

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
void makePaveText(TCanvas *can, TString text, double x1, double y1, double x2, double y2) { //1 - lewy gorny, 2 - prawy dolny, x i y rosna normalnie, nie jak w javie 
    TPaveText *pt = setOPT_text2(text,x1,y1,x2,y2,kBlack,0.05);
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
            //entry[i] = TString::Format("(%i) %s ",i,entry[i].Data());
            //entry[i] += TString::Format(" 10^{%i}",i);
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
        histTab[0]->SetMaximum(1.15*max);
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

        histTab[i]->SetMarkerStyle(markers[i]);
        //histTab[i]->SetMarkerStyle(markers[0]);
        histTab[i]->SetMarkerSize(0.9);
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

void seekParticles2(Int_t entry, Int_t pid, Int_t fatherpid, vector<Int_t> *entriesArr) {
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
    else if(pid == 2224) { //delta++
        entriesArr[2].push_back(entry);
    }
    else if (pid == 2114) { //delta0
        entriesArr[3].push_back(entry);
    }


}

void seekParticles3(Int_t entry, Int_t pid, vector<Int_t> *entriesArr){
    if(pid == 2224) //delta ++
        entriesArr[0].push_back(entry);
    else if (pid == 2114)  //delta0
        entriesArr[1].push_back(entry);

}

void clearVectors(vector<Int_t> *entriesArr, vector<TLorentzVector> *pairsArr,vector<TLorentzVector> *deltasArr) {
	for(int i = 0; i < _N_PARTICLES_; i++) {
		entriesArr[i].clear();
        if(i<_N_PAIRS_) {
		    pairsArr[i].clear();
            deltasArr[i].clear();
        }
	}
}

void makeLorentzVectorsPairs2(vector<Int_t> *entriesArr, TChain *chain, vector<TLorentzVector> *pairsArr, ParticleCoor &particle ) {
	TLorentzVector v1,v2;
	for (int i = 0; i < _N_PAIRS_; i++) {
		for (size_t j = 0; j < entriesArr[i].size(); j+=2) {
			chain->GetEntry(entriesArr[i][j]);
            if(particle.fatherpid == 2224 || particle.fatherpid == 2114) {
			    v1.SetPxPyPzE(particle.px,particle.py,particle.pz,particle.e);
                /*cout<<"Particle pid: "<<particle.pid<<endl;
                cout<<"Particle father pid: "<<particle.fatherpid<<endl;
                cout<<"Particle root pid: "<<particle.rootpid<<endl;
                cout<<"Particle eid: "<<particle.eid<<endl;
                cout<<"Particle father eid: "<<particle.fathereid<<endl;
                cout<<"Particle event id : "<<particle.eventid<<endl;
                cout<<"Is decayed: "<<particle.decayed<<endl;
                cout<<endl;*/
            
			    chain->GetEntry(entriesArr[i][j+1]);
			    v2.SetPxPyPzE(particle.px,particle.py,particle.pz,particle.e);
                /*cout<<"Particle pid: "<<particle.pid<<endl;
                cout<<"Particle father pid: "<<particle.fatherpid<<endl;
                cout<<"Particle root pid: "<<particle.rootpid<<endl;
                cout<<"Particle eid: "<<particle.eid<<endl;
                cout<<"Particle father eid: "<<particle.fathereid<<endl;
                cout<<"Particle event id : "<<particle.eventid<<endl;
                cout<<"Is decayed: "<<particle.decayed<<endl;
                cout<<endl;
                cout<<"*****************"<<endl;*/
			    pairsArr[i].push_back(v1+v2);
            }
			

		}

	}
}


void makeLorentzVectorsDeltas2(vector<Int_t> *entriesArr, TChain *chain, vector<TLorentzVector> *deltasArr, ParticleCoor &particle ){
    TLorentzVector v;
    Int_t fathereid;
    for(int i = 0; i < entriesArr[0].size(); i++) { //go through found particles from delta ++ decay
        chain->GetEntry(entriesArr[0][i]);
        if (particle.pid == 2212) { //look only for protons to not double particles form pairs
            fathereid = particle.fathereid;
            for(int j = 0; j < entriesArr[2].size(); j++) {//go through found deltas ++
                chain->GetEntry(entriesArr[2][j]); //get the delta++
                if(particle.eid == fathereid) {//if you found father of the exact proton 
                    v.SetPxPyPzE(particle.px,particle.py,particle.pz,particle.e);
                    deltasArr[0].push_back(v);
                }
            }
        }

    }

    for(int i = 0; i < entriesArr[1].size(); i++) { //go through found particles from delta0 decay
        chain->GetEntry(entriesArr[1][i]);
        if (particle.pid == 2212) { //look only for protons to not double particles form pairs
            fathereid = particle.fathereid;
            for(int j = 0; j < entriesArr[3].size(); j++) {//go through found deltas0
                chain->GetEntry(entriesArr[3][j]); //get the delta0
                if(particle.eid == fathereid) {//if you found father of the exact proton 
                    v.SetPxPyPzE(particle.px,particle.py,particle.pz,particle.e);
                    deltasArr[1].push_back(v);
                }
            }
        }

    }




}



 //plotting mass od pairs and deltas

void createHistograms2(TString aEventDir, TString aOutDir, Int_t aEventFiles, TString Case) {
    TString histNames[_N_HIST_] = {"Pi+pMPairHist","Pi-pMPairHist","Pi+pMDeltaHist","Pi-pMDeltaHist"};
    Int_t XBins = 100;
    Float_t XMin = 1;
	Float_t XMax = 1.6;
    Float_t dX = (XMax-XMin)/XBins;
    TString XTitle = "M_{inv} (GeV/c^{2})";
    TString YTitle = "dN/dM (GeV/c^{2})^{-1}";

    vector<Int_t> entriesArr[_N_PARTICLES_];
	vector<TLorentzVector> pairsArr[_N_PAIRS_];
    vector<TLorentzVector> deltasArr[2];

    //ofstream txtOut;
    //txtOut.open("test.txt");

    
    //READING
    cout << "Reading events in folder: "<<aEventDir.Data()<< endl;
   	gSystem->MakeDirectory(aOutDir);

    static ParticleCoor Particle;
    Int_t   Events;
    TChain* Chain = events2chain(aEventDir, aEventFiles, &Particle, &Events);

    //HISTOGRAMS
    TH1D *hist[_N_HIST_];
    for (int i = 0; i < _N_HIST_; i++) {
        hist[i] = new TH1D(histNames[i].Data(),"",XBins,XMin,XMax);
        hist[i]->Sumw2();
        hist[i]->GetXaxis()->SetTitle(XTitle);
        hist[i]->GetYaxis()->SetTitle(YTitle);
    }
    
    Chain->GetEntry(0); 
	Int_t event_prev = Particle.eventid; //first event number
    Int_t event;

    int e = 0;

    for (Int_t i = 0; i < Chain->GetEntries() ; i++) { 
        Chain->GetEntry(i);
        event = Particle.eventid; 
        if (event == event_prev) {
            seekParticles2(i,Particle.pid,Particle.fatherpid,entriesArr);  //looking for particles

            /*txtOut<<"Particle pid: "<<Particle.pid<<endl;
            txtOut<<"Particle father pid: "<<Particle.fatherpid<<endl;
            txtOut<<"Particle root pid: "<<Particle.rootpid<<endl;
            txtOut<<"Particle eid: "<<Particle.eid<<endl;
            txtOut<<"Particle father eid: "<<Particle.fathereid<<endl;
            txtOut<<"Particle event id : "<<Particle.eventid<<endl;
            txtOut<<"Is decayed: "<<Particle.decayed<<endl;
            txtOut<<endl;*/

            //if(Particle.pid == 2224 || Particle.pid == 2114 ) //if delta (++ or 0)
                //seekDeltas(Particle.pid,Particle,hist);
        }

        else {
            e++;
            //txtOut<<"***************************************************************"<<endl;

            
            makeLorentzVectorsPairs2(entriesArr,Chain,pairsArr,Particle);

            makeLorentzVectorsDeltas2(entriesArr, Chain, deltasArr, Particle );

            //FILLING HISTOGRAMS

            for (int i = 0; i < _N_PAIRS_; i++) {
                //cout<<"Pary nr "<<i<<endl;
                //for(int j = 0; j < pairsArr[i].size(); j++)
                    //cout<<"Masa pary nr: "<<j<<" "<<pairsArr[i][j].M()<<endl;
                for(auto lorentz : pairsArr[i]) {
                    if(lorentz.Rapidity() > 0 && lorentz.Rapidity() < 1.8)
                        hist[i]->Fill(lorentz.M());
                }
            }

            for (int i = 0; i < 2; i++) {
                //cout<<"Delty nr "<<i<<endl;
                //for(int j = 0; j <deltasArr[i].size(); j++)
                    //cout<<"Masa delty nr: "<<j<<" "<<deltasArr[i][j].M()<<endl;
                for(auto lorentz : deltasArr[i]){
                    if(lorentz.Rapidity() > 0 && lorentz.Rapidity() < 1.8)
                        hist[i+2]->Fill(lorentz.M());

                }
            }

            

            clearVectors(entriesArr,pairsArr,deltasArr);
            event_prev = event;
            Chain->GetEntry(i);
            seekParticles2(i,Particle.pid,Particle.fatherpid,entriesArr); //at the end collect new particle
			if (e%10000==0)
				cout<<"Event: "<<e<<endl;


        }
        //if(e==1000)
            //break;
    }

    //Scaling

    for(int i = 0 ; i < _N_HIST_; i++)
       hist[i] ->Scale(1.0/Events*dX);
   

   //Plotting
    TCanvas * can1 = new TCanvas("can","can", 1000, 1000);
    TCanvas * can2 = new TCanvas("can2","can2",1000,1000);

    doublePlot(hist[0],hist[2],can1,histNames[0],histNames[2]);
    doublePlot(hist[1],hist[3],can2,histNames[1],histNames[3]);

    //can1->SaveAs("~/pairs/output2/1.png");
    //can2->SaveAs("~/pairs/output2/2.png");

    cout<<"Ilosc delt++: "<<hist[2]->GetEntries()<<endl;
    cout<<"Ilosvc par pi+p: "<<hist[0]->GetEntries()<<endl;

    cout<<"Ilosc delt0: "<<hist[3]->GetEntries()<<endl;
    cout<<"Ilosvc par pi-p: "<<hist[1]->GetEntries()<<endl;
}



void fillHist3(ParticleCoor &particle, TH1D *hist[], vector<Int_t> *ids) {
    TLorentzVector v;
    bool alreadyFound = false;
    if(particle.pid == 2224) { //delta++
        v.SetPxPyPzE(particle.px,particle.py,particle.pz,particle.e);
        hist[0]->Fill(v.M());
        if(particle.fatherpid == 2224) //if it primordial
            hist[1]->Fill(v.M());
        else {
            hist[2]->Fill(v.M()); //if it from decay
            if(ids[0].size()==0)
                ids[0].push_back(particle.fatherpid);
            else {
                for(int i = 0; i < ids[0].size(); i++) {//go through collected ids
                    if(ids[0][i] == particle.fatherpid)
                        alreadyFound = true;
                }

                if(!alreadyFound)
                    ids[0].push_back(particle.fatherpid);
            }
            
        }
        
    }
    else if (particle.pid == 2114) { //delta0
        v.SetPxPyPzE(particle.px,particle.py,particle.pz,particle.e);
        hist[3]->Fill(v.M());
        if(particle.fatherpid == 2114) //if it primordial
            hist[4]->Fill(v.M());
        else {
            hist[5]->Fill(v.M());

            if(ids[1].size()==0)
                ids[1].push_back(particle.fatherpid);
            else {
                for(int i = 0; i < ids[1].size(); i++) {//go through collected ids
                    if(ids[1][i] == particle.fatherpid)
                        alreadyFound = true;
                }

                if(!alreadyFound)
                    ids[1].push_back(particle.fatherpid);
            }

        }

    }
}


//mass of deltas primordial vs from decays
void createHistograms3(TString aEventDir, TString aOutDir, Int_t aEventFiles, TString Case) {

    int const nHist = 6;
    int const nDeltas = 2;

    TString histNames[nHist] = {"Delta++","Delta++Primordial","Delta++FromDecay","Delta0","Delta0Primordial","Delta0FromDecay"};
    Int_t XBins = 200;
    Float_t XMin = 1;
	Float_t XMax = 1.6;
    Float_t dX = (XMax-XMin)/XBins;
    TString XTitle = "M_{inv} (GeV/c^{2})";
    TString YTitle = "dN/dM (GeV/c^{2})^{-1}";


    vector<Int_t> ids[_N_PARTICLES_];
    
    //READING
    cout << "Reading events in folder: "<<aEventDir.Data()<< endl;
   	gSystem->MakeDirectory(aOutDir);

    static ParticleCoor Particle;
    Int_t   Events;
    TChain* Chain = events2chain(aEventDir, aEventFiles, &Particle, &Events);

    //HISTOGRAMS
    TH1D *hist[nHist];

    for (int i = 0; i < nHist; i++) {
        hist[i] = new TH1D(histNames[i].Data(),"",XBins,XMin,XMax);
        hist[i]->Sumw2();
        hist[i]->GetXaxis()->SetTitle(XTitle);
        hist[i]->GetYaxis()->SetTitle(YTitle);
    }
    
    ofstream txt;
    txt.open("test22.txt");


    //Int_t n = Chain->GetEntries();
    //int e = 1;

    //cout<<"ilosc czastek"<<Chain->GetEntries()<<endl;

    for (Int_t i = 0; i < Chain->GetEntries() ; i++) { 
        Chain->GetEntry(i);
        fillHist3(Particle,hist,ids);

        if (i%1000000==0)
            cout<<"i: "<<i<<endl;
           
        
			


        //if(i==100000)
            //break;

    }
    //SCALE
    for(int i = 0 ; i < nHist; i++)
       hist[i] ->Scale(1.0/Events*dX);



    //PLOTTING

    TCanvas * can1 = new TCanvas("can","can", 1000, 1000);
    TCanvas * can2 = new TCanvas("can2","can2",1000,1000);

    TH1D *hist2[3] = {hist[3],hist[4],hist[5]};
    TString names2[3] = {histNames[3],histNames[4],histNames[5]};

    multiplePlot(hist,can1,histNames,3);
    multiplePlot(hist2,can2,names2,3);

    cout<<endl;
    for(int i = 0; i < nHist; i++) 
        cout<<"Liczba delt w "<<histNames[i]<<": "<<hist[i]->GetEntries()<<endl;
    cout<<endl;

    cout<<"Procent primordial delt++ do wszystkich delt++: "<<(hist[1]->GetEntries())/(hist[0]->GetEntries())*100<<" %%"<<endl;
    cout<<"Procent primordial delt0 do wszystkich delt0: "<<(hist[4]->GetEntries())/(hist[3]->GetEntries())*100<<" %%"<<endl;

    cout<<endl;
    cout<<"Procent delt++ z rozpadów do wszystkich delt++: "<<(hist[2]->GetEntries())/(hist[0]->GetEntries())*100<<" %%"<<endl;
    cout<<"Procent delt0 z rozpadów do wszystkich delt0: "<<(hist[5]->GetEntries())/(hist[3]->GetEntries())*100<<" %%"<<endl;

    for(auto id : ids[0])
        txt<<"Znalezione id: "<<id<<endl;

    txt<<"*******************************************"<<endl;

    for(auto id : ids[1])
        txt<<"Znalezione id: "<<id<<endl;


}


void makeHistTerm2() {
createHistograms2("~/pairs/CaseB/","~/pairs/output2",10,"CaseB");
    //createHistograms("~/lustre/hades/user/kjedrzej/HubbDeltLowT/H100E0D2femto/","~/pairs/outputBig",100,"CaseA");

    //createHistograms3("~/pairs/CaseB/","~/pairs/output2",10,"CaseB");

}