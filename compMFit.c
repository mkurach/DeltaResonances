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

    gROOT -> SetBatch(kTRUE);
    gStyle->SetOptStat(0);

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

    
    
    //FUNCTION

    Int_t nparams = 3;
    TF1 *fun = new TF1("fun",fitFunctionM,XMin,XMax,nparams);
    //0 - sigma0 - normalizacja , 1 - m0, 2 -gamma0 
    fun->SetParLimits(0,3,27);
    fun->SetParLimits(1,1.125,1.25);
    fun->SetParLimits(2,1e-10,1);

    fun->SetParameters(1,1.232,0.117);


    //SAVING AND GETTING VALUES OF PARAMETERS
    TFile* fileOut = new TFile("outputFit/outFitM.root","RECREATE");
	fileOut->cd();

    Double_t mFit[_N_CASES_][_N_PAIRS_];
    Double_t gammaFit[_N_CASES_][_N_PAIRS_];
    Double_t mFitError[_N_CASES_][_N_PAIRS_];
    Double_t gammaFitError[_N_CASES_][_N_PAIRS_];

    TF1* funCop;

    for(int i = 0; i < _N_CASES_; i++){   
        for(int j = 0; j < _N_PAIRS_; j++) {
            can[i][j]->cd();
            cout<<casesNames[i].Data()<<"  "<<pairsTitles[j].Data()<<endl;
            histM[i][j]->Fit("fun","","",1.125,1.250); //like in experiment

            funCop = (TF1*)fun->Clone("funCop");
            funCop->SetRange(1.1,1.6);
            funCop->SetLineStyle(2);
            histM[i][j]->GetListOfFunctions()->Add(funCop);

            mFit[i][j] = fun->GetParameter(1);
            gammaFit[i][j] = fun->GetParameter(2);
            mFitError[i][j] = fun->GetParError(1);
            gammaFitError[i][j] = fun->GetParError(2);
            histM[i][j]->Write();

            makePaveText(can[i][j],casesNames[i].Data(),0.7,0.95,0.99,0.5,0.05);
            makePaveText(can[i][j],pairsNames[j].Data(),0.7,0.9,0.99,0.4,0.05);
            can[i][j]->SaveAs(Form("outputFit/%s%sMFitted.png",casesNames[i].Data(),pairsTitles[j].Data()));
        }
    }

    //PRINTING PARAMETERS   
    for(int i = 0; i < _N_CASES_; i++){   
        cout<<casesNames[i].Data()<<":"<<endl;
        for(int j = 0; j < _N_PAIRS_; j++) {
            cout<<"\t"<<pairsTitles[j].Data()<<":\n"<<endl;
            cout<<"\t\tMass: "<<mFit[i][j]<<" (GeV/c^{2})";
            cout<<"\tGamma: "<<gammaFit[i][j]<<" (GeV/c^{2})"<<endl;
        }
    }

    fileOut->Save();
    fileOut->Close();

    gROOT -> SetBatch(kFALSE); 

    //GETTING MAXIMUM

    Double_t mMax[_N_CASES_][_N_PAIRS_];

    for(int i = 0; i < _N_CASES_; i++) { 
        for(int j = 0; j < _N_PAIRS_; j++) {
            mMax[i][j] = histM[i][j]->GetXaxis()->GetBinCenter(histM[i][j]->GetMaximumBin()); 
        }
    }

    //EXPERIMENT MASS
    Double_t mExp = 1.132;

    //EXPERIMENT GAMMA
    Double_t gammaExp = 0.108;

    //GRAPH MASS COMPARING

    TGraphErrors* mGr = new TGraphErrors();

    mGr->SetPoint(0,1,mExp); //exp
    mGr->SetPoint(1,2,(mFit[0][0]+mFit[0][1])/2); //fit
    mGr->SetPointError(1,0,(mFitError[0][0]+mFitError[0][1])/2);
    cout<<"blad na pierwszym punkcie: "<<(mFitError[0][0]+mFitError[0][1])/2<<endl;
    mGr->SetPoint(2,3,(mFit[2][0]+mFit[2][1])/2); 
    mGr->SetPointError(2,0,(mFitError[2][0]+mFitError[2][1])/2);
    mGr->SetPoint(3,4,(mFit[1][0]+mFit[1][1])/2); 
    mGr->SetPointError(3,0,(mFitError[1][0]+mFitError[1][1])/2);

    TGraphErrors* mMaxGr = new TGraphErrors();

    mMaxGr->SetPoint(0,2,(mMax[0][0]+mMax[0][1])/2); //maximum
    mMaxGr->SetPoint(1,3,(mMax[2][0]+mMax[2][1])/2); 
    mMaxGr->SetPoint(2,4,(mMax[1][0]+mMax[1][1])/2);
    mMaxGr->SetMarkerColor(kBlue+1);
    mMaxGr->SetMarkerStyle(20);


    TString labelNames[7] = {"Experiment", "CaseA","CaseB","CaseC"};
    for(int i = 0; i < 4; i++) 
            mGr->GetXaxis()->SetBinLabel(mGr->GetXaxis()->FindBin(i+1),labelNames[i].Data());        
    
    mGr->GetXaxis()->LabelsOption("h");
    mGr->GetXaxis()->SetLabelSize(0.05);

    mGr->GetYaxis()->SetRangeUser(1.12,1.25);
    mGr->GetYaxis()->SetTitle("M_{0} (GeV/c^{2})");


    TGraph* lineGr = new TGraph();
    lineGr->SetPoint(0,0,1.232);
    lineGr->SetPoint(1,8,1.232);
    lineGr->SetLineWidth(4);


    TCanvas* canGr = new TCanvas("massFit","massFit",715,700);
    setBasicStyle();
    setCanvas(canGr);
    canGr->cd();
    canGr->SetLeftMargin(0.13);
    mGr->SetMarkerColor(kRed+1);
    mGr->SetMarkerStyle(21);

    mGr->Draw("ap");
    lineGr->Draw("same");
    mMaxGr->Draw("psame");
    makePaveText(canGr,"maximum",0.39,0.46,0.99,0.5,0.03,kBlue+1);
    makePaveText(canGr,"from fit",0.39,0.36,0.99,0.5,0.03,kRed+1);

    makePaveText(canGr,"#Delta(1232)", 0.67, 0.92, 0.8, 0.6, 0.05);

    //SEEING MAXIMUM FOR PML
    Double_t y5[] = {
        0.487868830660434  ,  0.974036309173992  ,   1.48796409314226  ,   1.88297294151952  ,   2.28387966214487  ,   2.69710433117348  ,   3.06126905224752  ,   3.48369820687455  ,   3.94681509541577  ,   4.40057706566204  ,
        4.93936605645115  ,   5.48283889953534  ,   6.11314163074160  ,   6.81950751171442  ,   7.55858848427632  ,   8.39291146773919  ,   9.34237968621590  ,   10.3691236214243  ,   11.4890241422109  ,   12.6864224931698  ,
        13.9961542566581  ,   15.3159690791888  ,   16.5829494782608  ,   17.8292131736408  ,   18.9152955911726  ,   19.7159202944624  ,   20.2343075893699  ,   20.3069956416159  ,   20.0125696007672  ,   19.4358933652416  ,
        18.4928474508350  ,   17.3823315861657  ,   16.1716157278873  ,   14.9038674730610  ,   13.6447991751455  ,   12.5056812406078  ,   11.4205163366001  ,   10.4059676207370  ,   9.56824474209078  ,   8.71912443140713  ,
        8.01315763782008  ,   7.39793576023726  ,   6.80293967011530  ,   6.32923543881047  ,   5.89510052808095  ,   5.48821214622965  ,   5.13744465308651  ,   4.85174031833841  ,   4.57035038945562  ,   4.30429423098407  ,
        4.07695313297681  ,   3.89130969244800  ,   3.71215490911060  ,   3.56308036882298  ,   3.40112470196175  ,   3.25304206818625  ,   3.16482535139844  ,   3.04715152970495  ,   2.96881716587616  ,   2.88140869791066  ,
        2.78585022621101  ,   2.72700023847186  ,   2.64608188068563  ,   2.60279320128658  ,   2.54784690812262  ,   2.49439864564337  ,   2.44898753815908  ,   2.37474004226641  ,   2.38889146786364  ,   2.32064636249309  ,
        2.25598151655673  ,   2.26163499621386  ,   2.21317590725296  ,   2.18258711838417  ,   2.14657132226298  ,   2.11184984790125  ,   2.07710318841325  ,   2.04127250297028  ,   2.00975961369809  ,   1.96467048836692  ,
        1.96033089737522  ,   1.92523920165693  ,   1.86071345511037  ,   1.83261799374429  ,   1.80431223657368  ,   1.74073722854448  ,   1.70206527339233  ,   1.70885460224525  ,   1.62966568770821  ,   1.60909660760260  ,
        1.57063349526692  ,   1.53328104700055  ,   1.50929453898890  ,   1.44028961773135  ,   1.41651195253619  ,   1.37802510806219  ,   1.34406780855180  ,   1.30897465984558  ,   1.27409180694395  ,   1.23918522190402  ,
        1.20425635771394  ,   1.16951260420208  ,   1.13384329729916  ,   1.10156913915201  ,   1.05909016156322  ,   1.04733955656242  ,   1.03466485115872  ,  0.994816847474634  ,  0.955153954468695  ,  0.941716527201837  ,
        0.932576069943827  ,  0.882687531334134  ,  0.872806631363069  ,  0.862001630988857  ,  0.814744066283836  ,  0.798214874167238  ,  0.807009326536368  ,  0.792949729784183  ,  0.738143504668653  ,  0.750470752195434  ,
        0.762983110400590  ,  0.707412710433718  ,  0.695986993562356  ,  0.697185321244401  ,  0.703998672833197  ,  0.678025155222950  ,  0.665835263500309  ,  0.640255699384825  ,  0.644986822224574  ,  0.654246037039566  ,
        0.617376174539702  ,  0.639099508356292  ,  0.603315124799318  ,  0.608256543443586  , 
    };
    
    TH1F *h5 = new TH1F("hBform","B(m)",134,1.078,1.743);
    for (int b = 1; b <= h5->GetNbinsX(); ++b) 
        h5->SetBinContent(b,y5[b-1]);

    Double_t maxPML = h5->GetXaxis()->GetBinCenter(h5->GetMaximumBin()); 
    cout<<"Maximum for PML: "<<maxPML<<endl;
    
    TLine* pmlLine = new TLine(mGr->GetXaxis()->GetBinLowEdge(1),maxPML,mGr->GetXaxis()->GetBinLowEdge(mGr->GetXaxis()->GetNbins()+1),maxPML);
    pmlLine->SetLineWidth(4);
    pmlLine->SetLineStyle(2);
    pmlLine->SetLineColor(kPink-4);
    makePaveText(canGr,"PML", 0.67, 0.73, 0.8, 0.6, 0.05);
    pmlLine->Draw();
    
    
    
    canGr->SaveAs("outputFit/M0Comp.png");
    canGr->SaveAs("/u/mkurach/figures_with_data/moje/ladne/M0Comp.pdf");


    //GRAPH GAMMA COMPARING

    TGraphErrors* gammaGr = new TGraphErrors();

    gammaGr->SetPoint(0,1,gammaExp);
    gammaGr->SetPoint(1,2,(gammaFit[0][0]+gammaFit[0][1])/2); //fit
    gammaGr->SetPointError(1,0,(gammaFitError[0][0]+gammaFitError[0][1])/2);
    gammaGr->SetPoint(2,3,(gammaFit[2][0]+gammaFit[2][1])/2); 
    gammaGr->SetPointError(2,0,(gammaFitError[2][0]+gammaFitError[2][1])/2);
    gammaGr->SetPoint(3,4,(gammaFit[1][0]+gammaFit[1][1])/2);
    gammaGr->SetPointError(3,0,(gammaFitError[1][0]+gammaFitError[1][1])/2);

    for(int i = 0; i < 4; i++) 
            gammaGr->GetXaxis()->SetBinLabel(gammaGr->GetXaxis()->FindBin(i+1),labelNames[i].Data());        
    

    gammaGr->GetXaxis()->LabelsOption("h");
    gammaGr->GetXaxis()->SetLabelSize(0.05);
    gammaGr->GetYaxis()->SetRangeUser(0.1,0.13);
    gammaGr->GetYaxis()->SetTitle("#Gamma_{0} (GeV/c^{2})");

    TGraph* lineGamma = new TGraph();
    lineGamma->SetPoint(0,0,0.117);
    lineGamma->SetPoint(1,5,0.117);
    lineGamma->SetLineWidth(4);

    TCanvas* canGamma = new TCanvas("gamma","gamma",715,700);
    setBasicStyle();
    setCanvas(canGamma);
    canGamma->SetLeftMargin(0.14);
    canGamma->cd();
    gammaGr->SetMarkerColor(kRed+1);
    gammaGr->SetMarkerStyle(21);

    gammaGr->Draw("ap");
    lineGamma->Draw("same");
    makePaveText(canGamma,"#Delta(1232)", 0.67, 0.47, 0.8, 0.6, 0.05);

    canGamma->SaveAs("outputFit/Gamma0Comp.png");
    canGamma->SaveAs("/u/mkurach/figures_with_data/moje/ladne/Gamma0Comp.pdf");
    
    TFile* fileOut2 = new TFile("/u/mkurach/figures_with_data/moje/ladne/massGamma.root","RECREATE");
    fileOut2->cd();
    canGr->Write();
    canGamma->Write();
    fileOut2->Close();
    fileOut2->Save();



}
