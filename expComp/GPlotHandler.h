#include "TStyle.h"
#include "TSystem.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TPaletteAxis.h"
#include "TLine.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TPaveText.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "GTLatexParser.h"

/*------------------------------------
quick note about good-looking (to me) visual aspects:

Good marker styles (keep in mind "opens" alre less visible!):
20,24 = circle (full/open)
21,25 = square (full/open)
29,30 = 5star (full/open)
43,42 = 4star (full/open)
33,27 = diamond (full/open)
47,46 = Xcross (full/open)
34,28 = +cross (full/open)

Good colors:
1 = Black (kBlack)
922 = Gray (kGray+2)
629 = Red (kRed)
631 = Dark Red (kRed+2)
802 = Oragne (kOrange+2)
797 = Yellow-ish (kOrange-3), only if REALLY running out of colors
819 = Light Green (kSpring-1)
414 = Green (kGreen+2)
867 = Light Blue (kAzure+7)
600 = Blue (kBlue)
603 = Dark Blue (kBlue+3)
880 = Violet (kViolet)
619 = Dark Violet (kMagenta+3)

------------------------------------*/
//=======================================================
// structures to make work a it easier
//=======================================================
struct Coordinates{
  double xMin, xMax;
  double yMin, yMax;

  Coordinates(){
    xMin=0.0; xMax=1.0;
    yMin=0.0; yMax=1.0;
  }
  Coordinates(double x1, double y1, double x2, double y2){
    xMin=x1; xMax=x2;
    yMin=y1; yMax=y2;
  }
};
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

struct GLine{
  int color, width, style;
  TLine* line; 

  GLine(double x1, double y1, double x2, double y2, int c=1, int w=2, int s=2){
    color=c; width=w; style=s;
    line = new TLine(x1,y1,x2,y2);
    line -> SetLineColor(color);
    line -> SetLineWidth(width);
    line -> SetLineStyle(style); 
  }
};

struct GFunction{
  int color, width, style;
  TF1* f1D=nullptr;
  TF2* f2D=nullptr;

  GFunction(TF1* f, double xMin, double xMax, int c=1, int w=2, int s=2){
    color=c; width=w; style=s;
    f1D = f;
    f1D -> SetRange(xMin, xMax);
    f1D -> SetLineColor(color);
    f1D -> SetLineWidth(width);
    f1D -> SetLineStyle(style); 
  }

  GFunction(TF2* f, double xMin, double xMax, double yMin, double yMax, int c=1, int w=2, int s=2){
    color=c; width=w; style=s;
    f2D = f;
    f2D -> SetRange(xMin, yMin, xMax, yMax);
    f2D -> SetLineColor(color);
    f2D -> SetLineWidth(width);
    f2D -> SetLineStyle(style); 
  }
  
};

//=======================================================
// default values of things
//=======================================================
const int CANVAS_X = 715;
const int CANVAS_WIDEX = 1800;
const int CANVAS_Y = 700;
const int DEFAULT_CANVAS_BCG = 0;

const int DEFAULT_COLOR = 1;
static int DEFAULT_2COLOR[] = {632, 600};
static int DEFAULT_3COLOR[] = {632, 600, 414};

const int DEFAULT_STYLE = 20;
static int DEFAULT_2STYLE[] = {20, 20};
static int DEFAULT_3STYLE[] = {20, 20, 20};

const double DEFAULT_SIZE = 0.8;

//=======================================================
//basic object's functions
//=======================================================

void setBasicStyle(){
  gStyle->SetPalette(kRainBow);
  gStyle->SetOptStat(0);
  //gStyle->SetCanvasPreferGL(true); //turn on transparency (use SetFillColorAlpha(color,0-1))
  gStyle->SetEndErrorSize(5);
  gStyle->SetErrorX(0);    
  gStyle->SetLineStyleString(22,"80 18 12 18 12 12"); // special style for the line
  gStyle->SetEndErrorSize(5);   // define end width of error bars
  gStyle->SetCanvasColor(DEFAULT_CANVAS_BCG);
  gStyle->SetPadColor(0);
  TGaxis::SetMaxDigits(3);
}

void setCanvas(TCanvas *c){
  c->SetLeftMargin(0.1);
  c->SetRightMargin(0.12);
  c->SetTopMargin(0.125);
  c->SetBottomMargin(0.15);
  c->ToggleEventStatus();
  c->Range(-200,-10,1000,-2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetTickx();
  c->SetTicky();
  c->SetFrameLineWidth(2);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderSize(0);
}

void setCanvasWide(TCanvas *c){
  c->SetLeftMargin(0.1);
  c->SetRightMargin(0.35);
  c->SetTopMargin(0.125);
  c->SetBottomMargin(0.15);
  c->ToggleEventStatus();
  c->Range(-200,-10,1000,-2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetTickx();
  c->SetTicky();
  c->SetFrameLineWidth(2);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderSize(0);
}

void numberedBins(TH1D* h){
  for(int i=1; i<h->GetXaxis()->GetNbins(); i++){
    h->GetXaxis()->SetBinLabel(i,TString::Format("%d",i-1));
  }
}

void normToNEvents(TH1D* h, double nEvents, bool resetErrors=false){
  if(resetErrors){
    h -> Sumw2(kFALSE);
    h -> Sumw2();    
  }
  h->Scale(1./nEvents);  
}

void normToBinWidth(TH1D* h, int rebinFactor=1, bool resetErrors=false){
  if(resetErrors){
    h -> Sumw2(kFALSE);
    h -> Sumw2();    
  }
  h->Rebin(rebinFactor);
  double width = h->GetXaxis()->GetBinWidth(1);
  h->Scale(1./width);  
}


void normToNEventsBinWidth(TH1D* h, double nEvents, int rebinFactor=1, bool resetErrors=true){
  if(resetErrors){
    h -> Sumw2(kFALSE);
    h -> Sumw2();    
  }
  h->Rebin(rebinFactor);
  double width = h->GetXaxis()->GetBinWidth(1);
  h->Scale(1./(width*nEvents));
  
}

void normToNEvents(TH2D* h, double nEvents, bool resetErrors=false){
  if(resetErrors){
    h -> Sumw2(kFALSE);
    h -> Sumw2();    
  }
  h->Scale(1./nEvents);  
}

void normToBinWidth(TH2D* h, int rebinFactor=1, bool resetErrors=false){
  if(resetErrors){
    h -> Sumw2(kFALSE);
    h -> Sumw2();    
  }
  h->Rebin(rebinFactor);
  double widthX = h->GetXaxis()->GetBinWidth(1);
  double widthY = h->GetYaxis()->GetBinWidth(1);
  h->Scale(1./(widthX*widthY));  
}


void normToNEventsBinWidth(TH2D* h, double nEvents, int rebinFactor=1, bool resetErrors=true){
  if(resetErrors){
    h -> Sumw2(kFALSE);
    h -> Sumw2();    
  }
  h->Rebin(rebinFactor);
  double widthX = h->GetXaxis()->GetBinWidth(1);
  double widthY = h->GetYaxis()->GetBinWidth(1);
  h->Scale(1./(widthX*widthY*nEvents));  
  
}

void setTitlesStyle(TH1D* h){
  TGaxis::SetMaxDigits(3);
  h->SetTitleSize(0.04);
  h->GetXaxis()->SetTitleSize(0.04);
  h->GetYaxis()->SetTitleSize(0.04);
  h->GetXaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleOffset(1.2);
  h->GetXaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelSize(0.035);
  h->GetYaxis()->SetLabelSize(0.035);
  h->GetXaxis()->SetNdivisions(510);
}

void setTitlesStyle(TH2D* h){
  TGaxis::SetMaxDigits(3);
  h->SetTitleSize(0.04);
  h->GetXaxis()->SetTitleSize(0.04);
  h->GetYaxis()->SetTitleSize(0.04);
  h->GetZaxis()->SetTitleSize(0.04);
  h->GetXaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetZaxis()->SetTitleFont(42);
  h->GetYaxis() -> SetTitleOffset(1.2);
  h->GetXaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetZaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelSize(0.035);
  h->GetYaxis()->SetLabelSize(0.035);
  h->GetZaxis()->SetLabelSize(0.035);
  h->GetXaxis()->SetNdivisions(510);
  h->GetYaxis()->SetNdivisions(510);
}

void setlegendStyle(TLegend* legend){
  legend -> SetLineWidth(0);
  legend -> SetFillStyle(0);
  legend -> SetLineColorAlpha(kWhite,0);
  legend->SetTextFont(42);
  if(legend->GetTextSize()>0.035)legend->SetTextSize(0.035);
}

TString smartSplit(TString &title){

  TObjArray *toa = title.Tokenize(" ");//split to words
  int N = toa->GetEntries();

  TString splitted[N];
  int splittedLength[N]; //how long is line up to current word
  int wordLength=0;
  int lineLength = 0;
  int indexOfLastWord = -1;
  bool isCommaSeparated = title.Contains(",");

  //scan through line
  for (int i=0; i<N; i++){
    splitted[i] = ((TObjString *)(toa->At(i)))->String();
    wordLength = getTruelength(splitted[i]);
    lineLength += wordLength;
    splittedLength[i]=lineLength;
  }

  if(lineLength<30) return title; //30 seems to be a good ammount of characters to fit in 1 line, at least using my histograms format

  for(int i=0; i<N; i++){
    if(splittedLength[i]>lineLength/2){ //if longer than 50% of title...

      if(isCommaSeparated){ //if title is separated with comas
        if(splitted[i].EndsWith(",") && indexOfLastWord==-1 && splittedLength[i]>=30) indexOfLastWord=i;
      }
      else{ //if title is separated only with spaces
        if(indexOfLastWord==-1 && splittedLength[i]>=30) indexOfLastWord=i;
      }
    }
  }

  if(indexOfLastWord==-1) return title;

  TString twoLiner="#splitline{";
  for(int i=0; i<N; i++){
    if(i==indexOfLastWord) twoLiner += TString::Format("%s}{",splitted[i].Data());
    else twoLiner += TString::Format("%s ",splitted[i].Data());
  }
  twoLiner+="}";

  return twoLiner;
}

void saveAsGIF(TCanvas* c, TString name, TString path){
  int dirStatus = gSystem->Exec(TString::Format("[ -d %s ]",path.Data()));
  if(dirStatus==256) gSystem->Exec(TString::Format("mkdir %s",path.Data())); //if folder doesn't exist - create new
  else if(dirStatus!=0){ //in case of any issue - return error
    cout<<"#saveAsGIF - Unknown error while creating "<<path<<" dir. gSystem status:"<<dirStatus<<endl;
    return;
  }
  c->SaveAs(TString::Format("%s%s.gif",path.Data(),name.Data())); //if GL enabled only pdf & gif works unfortunatelly...
}

TPaveText* getNiceTPave(double xMin, double yMin, double xMax, double yMax, TString text, int color=1, double textSize=0.05){
  TPaveText *pave=new TPaveText(xMin,yMin,xMax,yMax,"NDC");

  pave->SetLineWidth(0);
  pave->SetBorderSize(0.0);
  pave->SetTextFont(42);
  pave->SetTextColor(color);
  pave->SetFillColor(0);
  pave->SetFillStyle(0);
  pave->SetTextAlign(13);
  pave->SetTextSize(textSize);

  if(text.Contains("\n")){
    TObjArray *toa = text.Tokenize("\n");//split to words
    int N = toa->GetEntries(); 
    for (int i=0; i<N; i++){
      pave->AddText(((TObjString *)(toa->At(i)))->String());
    }  
  }
  else pave->AddText(text);
  
  return pave;
}

//alternative option with Coordinates structure
TPaveText* getNiceTPave(Coordinates coords, TString text, int color=1, double textSize=0.05){
  TPaveText *pave=new TPaveText(coords.xMin,coords.yMin,coords.xMax,coords.yMax,"NDC");
 
  pave->SetLineWidth(0);
  pave->SetBorderSize(0.0);
  pave->SetTextFont(42);
  pave->SetTextColor(color);
  pave->SetFillColor(0);
  pave->SetFillStyle(0);
  pave->SetTextAlign(13);
  pave->SetTextSize(textSize);

  if(text.Contains("\n")){
    TObjArray *toa = text.Tokenize("\n");//split to words
    int N = toa->GetEntries(); 
    for (int i=0; i<N; i++){
      pave->AddText(((TObjString *)(toa->At(i)))->String()); 
    } 
  }
  else pave->AddText(text);
  return pave;
}

//bit nicer ploting of multiple lines, although more complex
vector<TPaveText*> getNiceTPaves(double xMin, double yMin, double xMax, double yMax, TString text, int color=1, double textSize=0.05){ 
  TObjArray *toa = text.Tokenize("\n");//split to words
  int N = toa->GetEntries();
  vector<TPaveText*> paves;
  double ySpacing=1.2;

  if(yMin>yMax-N*textSize) cout<<"#getNiceTPaves - too narrow Y range, bottom Paves may do some wierd shit..."<<endl;

  TString splitted[N];
  for (int i=0; i<N; i++){
    splitted[i] = ((TObjString *)(toa->At(i)))->String();
    paves.push_back(getNiceTPave(xMin, yMin+textSize*ySpacing*(N-i-1), xMax, yMax-textSize*ySpacing*i, splitted[i], color, textSize));
  }
  return paves;
}

vector<TPaveText*> getNiceTPaves(Coordinates coords, TString text, int color=1, double textSize=0.05){ // deliminator = \t
  TObjArray *toa = text.Tokenize("\t");//split to words
  int N = toa->GetEntries();
  vector<TPaveText*> paves;
  double ySpacing=1.2;

  if(coords.yMin>coords.yMax-N*textSize) cout<<"#getNiceTPaves - too narrow Y range, bottom Paves may do some wierd shit..."<<endl;

  TString splitted[N];
  for (int i=0; i<N; i++){
    splitted[i] = ((TObjString *)(toa->At(i)))->String();
    paves.push_back(getNiceTPave(coords.xMin, coords.yMin+textSize*ySpacing*(N-i-1), coords.xMax, coords.yMax-textSize*ySpacing*i, splitted[i], color, textSize));
  }
  return paves;
}

//=========================================================
// plot functions
//=========================================================

void setYrange(TH1D* h, double yMin, double yMax){
  h -> SetMinimum(yMin);
  h -> SetMaximum(yMax);
}

//1D plots
void singlePlotCanvas(TFile *f, TCanvas* c[], int &iterator, TH1D* h, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, double xMin, double xMax, int color=DEFAULT_COLOR, int markerStyle=DEFAULT_STYLE, double markerSize=DEFAULT_SIZE, bool log=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){
  setBasicStyle();
  c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
  setCanvas(c[iterator]);

  h -> GetXaxis() -> SetRangeUser(xMin,xMax);

  if(!histTitle.EqualTo(""))h -> SetTitle(smartSplit(histTitle));
  if(!xAxisLabel.EqualTo(""))h -> GetXaxis() -> SetTitle(xAxisLabel);
  if(!yAxisLabel.EqualTo(""))h -> GetYaxis() -> SetTitle(yAxisLabel);
  setTitlesStyle(h);
  
  if(binWithNorm) normToBinWidth(h,rebinFactor);
  else if(!binWithNorm && rebinFactor>1) h->Rebin(rebinFactor);

  h -> SetMarkerStyle(markerStyle);
  h -> SetMarkerSize(markerSize);
  h -> SetMarkerColor(color);
  h -> SetLineColor(color);
  
  f -> cd();
  c[iterator] -> cd();
  if(log)gPad -> SetLogy();
  h -> Draw();

  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }
  c[iterator] -> Write(); 

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);     
  } 

  f -> Save();
  iterator++;
}

void doublePlotCanvas(TFile *f, TCanvas* c[], int &iterator, TH1D* h1, TString label1, TH1D* h2, TString label2, Coordinates coords, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, double xMin, double xMax, int color[]=DEFAULT_2COLOR, int markerStyle[]=DEFAULT_2STYLE, double markerSize=DEFAULT_SIZE, bool log=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){
  setBasicStyle();
  c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
  setCanvas(c[iterator]);

  TLegend *legend = new TLegend(coords.xMin,coords.yMin,coords.xMax,coords.yMax,"","NDC");
  setlegendStyle(legend);

  h1 -> GetXaxis() -> SetRangeUser(xMin,xMax);

  if(!histTitle.EqualTo(""))h1 -> SetTitle(smartSplit(histTitle));
  if(!xAxisLabel.EqualTo(""))h1 -> GetXaxis() -> SetTitle(xAxisLabel);
  if(!yAxisLabel.EqualTo(""))h1 -> GetYaxis() -> SetTitle(yAxisLabel);
  setTitlesStyle(h1);

  if(binWithNorm) normToBinWidth(h1,rebinFactor);
  else if(!binWithNorm && rebinFactor>1) h1->Rebin(rebinFactor);

  h1 -> SetMarkerStyle(markerStyle[0]);
  h1 -> SetMarkerSize(markerSize);
  h1 -> SetMarkerColor(color[0]);
  h1 -> SetLineColor(color[0]);
  
  if(binWithNorm) normToBinWidth(h2,rebinFactor);
  else if(!binWithNorm && rebinFactor>1) h2->Rebin(rebinFactor);

  h2 -> SetMarkerStyle(markerStyle[1]);
  h2 -> SetMarkerSize(markerSize);
  h2 -> SetMarkerColor(color[1]);
  h2 -> SetLineColor(color[1]);
  
  legend -> AddEntry(h1,label1,"AP");  
  legend -> AddEntry(h2,label2,"AP");

  if(h2->GetMaximum()>h1->GetMaximum()){
    if(log) h1->SetMaximum(h2->GetMaximum()*3);
    else h1->SetMaximum(h2->GetMaximum()*1.1);  
  }

  if(h2->GetMinimum()<h1->GetMinimum()){
    if(h2->GetMinimum()<=0 && log) h1 -> SetMinimum(h1->GetMinimum()*0.1);
    else h1 -> SetMinimum(h2->GetMinimum());
  } 
  
  f -> cd();
  c[iterator] -> cd();
  if(log)gPad -> SetLogy();

  h1 -> Draw();
  h2 -> Draw("same");
  legend -> Draw("same");

  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }
  c[iterator] -> Write(); 

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);      
  } 

  f -> Save();
  iterator++;
}

void tripplePlotCanvas(TFile *f, TCanvas* c[], int &iterator, TH1D* h1, TString label1, TH1D* h2, TString label2, TH1D* h3, TString label3, Coordinates coords, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, double xMin, double xMax, int color[]=DEFAULT_3COLOR, int markerStyle[]=DEFAULT_3STYLE, double markerSize=DEFAULT_SIZE, bool log=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){
  setBasicStyle();
  c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
  setCanvas(c[iterator]);

  f -> cd();
  TLegend *legend = new TLegend(coords.xMin,coords.yMin,coords.xMax,coords.yMax,"","NDC");
  setlegendStyle(legend);


  h1 -> GetXaxis() -> SetRangeUser(xMin,xMax);
  if(!histTitle.EqualTo(""))h1 -> SetTitle(smartSplit(histTitle));
  if(!xAxisLabel.EqualTo(""))h1 -> GetXaxis() -> SetTitle(xAxisLabel);
  if(!yAxisLabel.EqualTo(""))h1 -> GetYaxis() -> SetTitle(yAxisLabel);
  setTitlesStyle(h1);

  if(binWithNorm) normToBinWidth(h1,rebinFactor);
  else if(!binWithNorm && rebinFactor>1) h1->Rebin(rebinFactor);

  h1 -> SetMarkerStyle(markerStyle[0]);
  h1 -> SetMarkerSize(markerSize);
  h1 -> SetMarkerColor(color[0]);
  h1 -> SetLineColor(color[0]);
  
  if(binWithNorm) normToBinWidth(h2,rebinFactor);
  else if(!binWithNorm && rebinFactor>1) h2->Rebin(rebinFactor);

  h2 -> SetMarkerStyle(markerStyle[1]);
  h2 -> SetMarkerSize(markerSize);
  h2 -> SetMarkerColor(color[1]);
  h2 -> SetLineColor(color[1]);

  if(binWithNorm) normToBinWidth(h3,rebinFactor);
  else if(!binWithNorm && rebinFactor>1) h3->Rebin(rebinFactor);

  h3 -> SetMarkerStyle(markerStyle[2]);
  h3 -> SetMarkerSize(markerSize);
  h3 -> SetMarkerColor(color[2]);
  h3 -> SetLineColor(color[2]);
 
  legend -> AddEntry(h1,label1,"AP");  
  legend -> AddEntry(h2,label2,"AP");
  legend -> AddEntry(h3,label3,"AP");

  if(h2->GetMaximum()>h1->GetMaximum()) h1->SetMaximum(h2->GetMaximum());
  if(h2->GetMinimum()<h1->GetMinimum()){
    if(h2->GetMinimum()<=0 && log) h1 -> SetMinimum(h1->GetMinimum()*0.1);
    else h1 -> SetMinimum(h2->GetMinimum());
  } 

  if(h3->GetMaximum()>h1->GetMaximum()){
    if(log) h1->SetMaximum(h3->GetMaximum()*3);
    else h1->SetMaximum(h3->GetMaximum()*1.1);  
  }
  if(h3->GetMinimum()<h1->GetMinimum()){
    if(h3->GetMinimum()<=0 && log) h1 -> SetMinimum(h1->GetMinimum()*0.1);
    else h1 -> SetMinimum(h3->GetMinimum());
  }
  
  c[iterator] -> cd();
  if(log)gPad -> SetLogy();

  h1 -> Draw();
  h2 -> Draw("same");
  h3 -> Draw("same");
  legend -> Draw("same");

  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }
  c[iterator] -> Write(); 

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);      
  } 

  f -> Save();
  iterator++;
}

void multiPlotCanvas(TFile *f, TCanvas* c[], int &iterator, TH1D* h[], TString label[], int N, Coordinates coords, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, double xMin, double xMax, int color[], int markerStyle[], double markerSize=DEFAULT_SIZE, bool log=false, bool wideCanvas=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){
  setBasicStyle();
  if(wideCanvas){
    c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_WIDEX,CANVAS_Y);
    setCanvasWide(c[iterator]);
  }
  else{
    c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
    setCanvas(c[iterator]);
  }

  f -> cd();
  TLegend *legend = new TLegend(coords.xMin,coords.yMin,coords.xMax,coords.yMax,"","NDC");
  setlegendStyle(legend);

  double minimum=1e20, maximum=0.0, minimumTmp, maximumTmp, minimumh0=h[0]->GetMinimum(), maximumh0=h[0]->GetMaximum();

  for(int i=0; i<N; i++){
    h[i]-> GetXaxis() -> SetRangeUser(xMin,xMax);
    if(!histTitle.EqualTo(""))h[i] -> SetTitle(smartSplit(histTitle));
    if(!xAxisLabel.EqualTo(""))h[i] -> GetXaxis() -> SetTitle(xAxisLabel);
    if(!yAxisLabel.EqualTo(""))h[i] -> GetYaxis() -> SetTitle(yAxisLabel);
    setTitlesStyle(h[i]);

    minimumTmp=h[i]->GetMinimum();
    maximumTmp=h[i]->GetMaximum();


    if(binWithNorm){
      normToBinWidth(h[i],rebinFactor);
      minimumTmp*=1./h[i]->GetXaxis()->GetBinWidth(1);
      maximumTmp*=1./h[i]->GetXaxis()->GetBinWidth(1);
      if(i==0){
        minimumh0*=1./h[0]->GetXaxis()->GetBinWidth(1);
        maximumh0*=1./h[0]->GetXaxis()->GetBinWidth(1);      
      }
    }
    else if(!binWithNorm && rebinFactor>1) h[i]->Rebin(rebinFactor);

    h[i] -> SetMarkerStyle(markerStyle[i]);
    h[i] -> SetMarkerSize(markerSize);
    h[i] -> SetMarkerColor(color[i]);
    h[i] -> SetLineColor(color[i]);

    if(minimumTmp < minimum){
      if(minimumTmp <=0 && log) minimum*=0.1;
      else minimum = minimumTmp;
    }
    if(maximumTmp > maximum) maximum = maximumTmp;

    legend -> AddEntry(h[i],label[i],"AP");
  }

  c[iterator] -> cd();
  if(log){
    gPad -> SetLogy();
    h[0]->SetMaximum(maximum*3);
  }
  else h[0]->SetMaximum(maximum*1.1);  

  h[0] -> SetMinimum(minimum);
  h[0] -> Draw();
  for(int i=1; i<N; i++){
    h[i] -> Draw("same");
  }
  legend -> Draw("same"); 

  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }
  c[iterator] -> Write(); 

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);      
  } 

  f -> Save();
  iterator++;

  gPad -> SetLogy(0);
  h[0] -> SetMaximum(maximumh0);
  h[0] -> SetMinimum(minimumh0);
}

//special version using vectors
void multiPlotCanvas(TFile *f, TCanvas* c[], int &iterator, vector<TH1D*> h, vector<TString> label, Coordinates coords, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, double xMin, double xMax, vector<int> color, vector<int> markerStyle, double markerSize=DEFAULT_SIZE, bool log=false, bool wideCanvas=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){
  setBasicStyle();
  if(wideCanvas){
    c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_WIDEX,CANVAS_Y);
    setCanvasWide(c[iterator]);
  }
  else{
    c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
    setCanvas(c[iterator]);
  }

  f -> cd();
  TLegend *legend = new TLegend(coords.xMin,coords.yMin,coords.xMax,coords.yMax,"","NDC");
  setlegendStyle(legend);

  double minimum=1e20, maximum=0.0, minimumTmp, maximumTmp, minimumh0=h[0]->GetMinimum(), maximumh0=h[0]->GetMaximum();

  if(h.size()>label.size()){
    cout<<"#multiPlotCanvas - for "<<canvasName<<" label's size is too small!"<<endl;
    return;
  }
  else if(h.size()>color.size()){
    cout<<"#multiPlotCanvas - for "<<canvasName<<" color's size is too small!"<<endl;
    return;
  }
  else if(h.size()>markerStyle.size()){
    cout<<"#multiPlotCanvas - for "<<canvasName<<" markerStyle's size is too small!"<<endl;
    return;
  }

  for(uint i=0; i<h.size(); i++){
    h[i]-> GetXaxis() -> SetRangeUser(xMin,xMax);
    if(!histTitle.EqualTo(""))h[i] -> SetTitle(smartSplit(histTitle));
    if(!xAxisLabel.EqualTo(""))h[i] -> GetXaxis() -> SetTitle(xAxisLabel);
    if(!yAxisLabel.EqualTo(""))h[i] -> GetYaxis() -> SetTitle(yAxisLabel);
    setTitlesStyle(h[i]);

    minimumTmp=h[i]->GetMinimum();
    maximumTmp=h[i]->GetMaximum();


    if(binWithNorm){
      normToBinWidth(h[i],rebinFactor);
      minimumTmp*=1./h[i]->GetXaxis()->GetBinWidth(1);
      maximumTmp*=1./h[i]->GetXaxis()->GetBinWidth(1);
      if(i==0){
        minimumh0*=1./h[0]->GetXaxis()->GetBinWidth(1);
        maximumh0*=1./h[0]->GetXaxis()->GetBinWidth(1);      
      }
    }
    else if(!binWithNorm && rebinFactor>1) h[i]->Rebin(rebinFactor);

    h[i] -> SetMarkerStyle(markerStyle[i]);
    h[i] -> SetMarkerSize(markerSize);
    h[i] -> SetMarkerColor(color[i]);
    h[i] -> SetLineColor(color[i]);

    if(minimumTmp < minimum){
      if(minimumTmp <=0 && log) minimum*=0.1;
      else minimum = minimumTmp;
    }
    if(maximumTmp > maximum) maximum = maximumTmp;

    if (i == 0)
      legend -> AddEntry(h[i],label[i],"AP");
    else {
      h[i]->SetLineWidth(3);
      legend -> AddEntry(h[i],label[i],"AL");

    }
  }

  c[iterator] -> cd();
  if(log){
    gPad -> SetLogy();
    h[0]->SetMaximum(maximum*3);
  }
  else h[0]->GetYaxis()->SetRangeUser(0,30);
  //else h[0]->SetMaximum(maximum*1.1);


  //h[0] -> SetMinimum(minimum);
  //h[0] -> GetYaxis()->SetRangeUser(0,0.02);
  h[0] -> Draw();
  for(uint i=1; i<h.size(); i++){
    h[i] -> Draw("same hist C");
  }
  legend -> Draw("same"); 

  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }

  /*TString pairsTitle[2] = {"#pi^{+}p","#pi^{-}p"};
  TString pairsTitlesDiff[2] = {"PiPlusP","PiMinusP"};

  	makePaveText(c[iterator],pairsTitle[iterator].Data(),0.7,0.4,0.88,0.5,0.05);
		makePaveText(c[iterator],"HADES Au+Au",0.4,0.75,0.7,0.85,0.03);
		makePaveText(c[iterator],"#sqrt{s_{NN}} = 2.42 GeV",0.4,0.72,0.8,0.82,0.03);
    makePaveText(c[iterator],"0 < y #leq 1.8",0.67,0.75,0.92,0.85,0.03);

		c[iterator]->SaveAs(Form("/u/mkurach/figures_with_data/moje/ladne/%smass.pdf",pairsTitlesDiff[iterator].Data()));*/
  c[iterator] -> Write(); 

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);     
  } 
  
  f -> Save();
  iterator++;

  gPad -> SetLogy(0);
  h[0] -> SetMaximum(maximumh0);
  h[0] -> SetMinimum(minimumh0);
}

//2D plots
void singlePlot2DCanvas(TFile* f, TCanvas* c[], int &iterator, TH2D* h, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, TString zAxisLabel, double xMin, double xMax,double yMin, double yMax, bool log=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){
  
  setBasicStyle();
  c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
  setCanvas(c[iterator]);

  f -> cd();

  h -> GetXaxis() -> SetRangeUser(xMin,xMax);
  h -> GetYaxis() -> SetRangeUser(yMin,yMax);
  if(!histTitle.EqualTo(""))h -> SetTitle(smartSplit(histTitle));
  if(!xAxisLabel.EqualTo(""))h -> GetXaxis() -> SetTitle(xAxisLabel);
  if(!yAxisLabel.EqualTo(""))h -> GetYaxis() -> SetTitle(yAxisLabel);
  if(!zAxisLabel.EqualTo(""))h -> GetZaxis() -> SetTitle(zAxisLabel);
  setTitlesStyle(h);

  if(binWithNorm) normToBinWidth(h,rebinFactor);
  else if(!binWithNorm && rebinFactor>1) h->Rebin2D(rebinFactor);

  c[iterator] -> cd();
  if(log)gPad -> SetLogz();
  
  h -> Draw("colz");
  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }
  c[iterator]->Update();

  //shrink color bar a little
  TPaletteAxis *palette = (TPaletteAxis*)h->GetListOfFunctions()->FindObject("palette");
  palette->SetX1NDC(0.885);
  palette->SetX2NDC(0.905);
  palette->SetY1NDC(0.2);
  palette->SetY2NDC(0.85);
  c[iterator]->Modified();
  c[iterator] -> Write();

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);      
  } 

  f -> Save();
  iterator++;
}

//=========================================================
// plot functions with line overlays
//=========================================================

void singlePlotCanvasLines(TFile *f, TCanvas* c[], int &iterator, TH1D* h, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, double xMin, double xMax, vector<GLine> linesToDraw, int color=DEFAULT_COLOR, int markerStyle=DEFAULT_STYLE, double markerSize=DEFAULT_SIZE, bool log=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){

  setBasicStyle();
  c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
  setCanvas(c[iterator]);

  h -> GetXaxis() -> SetRangeUser(xMin,xMax);

  if(!histTitle.EqualTo(""))h -> SetTitle(smartSplit(histTitle));
  if(!xAxisLabel.EqualTo(""))h -> GetXaxis() -> SetTitle(xAxisLabel);
  if(!yAxisLabel.EqualTo(""))h -> GetYaxis() -> SetTitle(yAxisLabel);
  setTitlesStyle(h);
  
  if(binWithNorm) normToBinWidth(h,rebinFactor);
  else if(!binWithNorm && rebinFactor>1) h->Rebin(rebinFactor);

  h -> SetMarkerStyle(markerStyle);
  h -> SetMarkerSize(markerSize);
  h -> SetMarkerColor(color);
  h -> SetLineColor(color);
  
  f -> cd();
  c[iterator] -> cd();
  if(log)gPad -> SetLogy();
  h -> Draw();

  //hidden option how to draw line at 1 for correlation functions "behind" the plot
  if((canvasName.Contains("CF") || canvasName.Contains("CorrFun") || canvasName.Contains("Correlation") || canvasName.Contains("CorrFun")) && 
    linesToDraw[0].line->GetY1()==linesToDraw[0].line->GetY2() && linesToDraw[0].line->GetY1()==1){

    linesToDraw[0].line -> SetX1(xMin); //just to make sure it'll draw properly
    linesToDraw[0].line -> SetX2(xMax);
    linesToDraw[0].line -> Draw("same");
    h -> Draw("same");
    for(uint i=1; i<linesToDraw.size(); i++){
      linesToDraw[i].line -> Draw("same");
    }

  }
  else{ //else draw it normally
    for(uint i=0; i<linesToDraw.size(); i++){
      linesToDraw[i].line -> Draw("same");
    }
  }

  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }
  c[iterator] -> Write(); 

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);     
  } 

  f -> Save();
  iterator++;
}

//no double/tripple option, im too lazy to do them
void multiPlotCanvasLines(TFile *f, TCanvas* c[], int &iterator, TH1D* h[], TString label[], int N, Coordinates coords, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, double xMin, double xMax, vector<GLine> linesToDraw, int color[], int markerStyle[], double markerSize=DEFAULT_SIZE, bool log=false, bool wideCanvas=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){
  setBasicStyle();
  if(wideCanvas){
    c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_WIDEX,CANVAS_Y);
    setCanvasWide(c[iterator]);
  }
  else{
    c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
    setCanvas(c[iterator]);
  }

  f -> cd();
  TLegend *legend = new TLegend(coords.xMin,coords.yMin,coords.xMax,coords.yMax,"","NDC");
  setlegendStyle(legend);

  double minimum=1e20, maximum=0.0, minimumTmp, maximumTmp, minimumh0=h[0]->GetMinimum(), maximumh0=h[0]->GetMaximum();

  for(int i=0; i<N; i++){
    h[i]-> GetXaxis() -> SetRangeUser(xMin,xMax);
    if(!histTitle.EqualTo(""))h[i] -> SetTitle(smartSplit(histTitle));
    if(!xAxisLabel.EqualTo(""))h[i] -> GetXaxis() -> SetTitle(xAxisLabel);
    if(!yAxisLabel.EqualTo(""))h[i] -> GetYaxis() -> SetTitle(yAxisLabel);
    setTitlesStyle(h[i]);

    minimumTmp=h[i]->GetMinimum();
    maximumTmp=h[i]->GetMaximum();


    if(binWithNorm){
      normToBinWidth(h[i],rebinFactor);
      minimumTmp*=1./h[i]->GetXaxis()->GetBinWidth(1);
      maximumTmp*=1./h[i]->GetXaxis()->GetBinWidth(1);
      if(i==0){
        minimumh0*=1./h[0]->GetXaxis()->GetBinWidth(1);
        maximumh0*=1./h[0]->GetXaxis()->GetBinWidth(1);      
      }
    }
    else if(!binWithNorm && rebinFactor>1) h[i]->Rebin(rebinFactor);

    h[i] -> SetMarkerStyle(markerStyle[i]);
    h[i] -> SetMarkerSize(markerSize);
    h[i] -> SetMarkerColor(color[i]);
    h[i] -> SetLineColor(color[i]);

    if(minimumTmp < minimum){
      if(minimumTmp <=0 && log) minimum*=0.1;
      else minimum = minimumTmp;
    }
    if(maximumTmp > maximum) maximum = maximumTmp;

    legend -> AddEntry(h[i],label[i],"AP");
  }

  c[iterator] -> cd();
  if(log){
    gPad -> SetLogy();
    h[0]->SetMaximum(maximum*3);
  }
  else h[0]->SetMaximum(maximum*1.1);  

  h[0] -> SetMinimum(minimum);
  h[0] -> Draw();

  //hidden option how to draw line at 1 for correlation functions "behind" the plot
  if((canvasName.Contains("CF") || canvasName.Contains("CorrFun") || canvasName.Contains("Correlation") || canvasName.Contains("CorrFun")) && 
    linesToDraw[0].line->GetY1()==linesToDraw[0].line->GetY2() && linesToDraw[0].line->GetY1()==1){

    linesToDraw[0].line -> SetX1(xMin); //just to make sure it'll draw properly
    linesToDraw[0].line -> SetX2(xMax);
    linesToDraw[0].line -> Draw("same");
    for(int i=0; i<N; i++){
      h[i] -> Draw("same");
    }
    for(uint i=1; i<linesToDraw.size(); i++){
      linesToDraw[i].line -> Draw("same");
    }

  }
  else{ //else draw it normally
    for(int i=1; i<N; i++){
      h[i] -> Draw("same");
    }
    for(uint i=0; i<linesToDraw.size(); i++){
      linesToDraw[i].line -> Draw("same");
    }
  }

  legend -> Draw("same"); 

  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }
  c[iterator] -> Write(); 

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);      
  } 

  f -> Save();
  iterator++;

  gPad -> SetLogy(0);
  h[0] -> SetMaximum(maximumh0);
  h[0] -> SetMinimum(minimumh0);
}

//special version using vectors
void multiPlotCanvasLines(TFile *f, TCanvas* c[], int &iterator, vector<TH1D*> h, vector<TString> label, Coordinates coords, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, double xMin, double xMax, vector<GLine> linesToDraw, vector<int> color, vector<int> markerStyle, double markerSize=DEFAULT_SIZE, bool log=false, bool wideCanvas=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){
  setBasicStyle();
  if(wideCanvas){
    c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_WIDEX,CANVAS_Y);
    setCanvasWide(c[iterator]);
  }
  else{
    c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
    setCanvas(c[iterator]);
  }

  f -> cd();
  TLegend *legend = new TLegend(coords.xMin,coords.yMin,coords.xMax,coords.yMax,"","NDC");
  setlegendStyle(legend);

  double minimum=1e20, maximum=0.0, minimumTmp, maximumTmp, minimumh0=h[0]->GetMinimum(), maximumh0=h[0]->GetMaximum();

  if(h.size()>label.size()){
    cout<<"#multiPlotCanvas - for "<<canvasName<<" label's size is too small!"<<endl;
    return;
  }
  else if(h.size()>color.size()){
    cout<<"#multiPlotCanvas - for "<<canvasName<<" color's size is too small!"<<endl;
    return;
  }
  else if(h.size()>markerStyle.size()){
    cout<<"#multiPlotCanvas - for "<<canvasName<<" markerStyle's size is too small!"<<endl;
    return;
  }

  for(uint i=0; i<h.size(); i++){
    h[i]-> GetXaxis() -> SetRangeUser(xMin,xMax);
    if(!histTitle.EqualTo(""))h[i] -> SetTitle(smartSplit(histTitle));
    if(!xAxisLabel.EqualTo(""))h[i] -> GetXaxis() -> SetTitle(xAxisLabel);
    if(!yAxisLabel.EqualTo(""))h[i] -> GetYaxis() -> SetTitle(yAxisLabel);
    setTitlesStyle(h[i]);

    minimumTmp=h[i]->GetMinimum();
    maximumTmp=h[i]->GetMaximum();

    if(binWithNorm){
      normToBinWidth(h[i],rebinFactor);
      minimumTmp*=1./h[i]->GetXaxis()->GetBinWidth(1);
      maximumTmp*=1./h[i]->GetXaxis()->GetBinWidth(1);
      if(i==0){
        minimumh0*=1./h[0]->GetXaxis()->GetBinWidth(1);
        maximumh0*=1./h[0]->GetXaxis()->GetBinWidth(1);      
      }
    }

    else if(!binWithNorm && rebinFactor>1) h[i]->Rebin(rebinFactor);

    h[i] -> SetMarkerStyle(markerStyle[i]);
    h[i] -> SetMarkerSize(markerSize);
    h[i] -> SetMarkerColor(color[i]);
    h[i] -> SetLineColor(color[i]);

    if(minimumTmp < minimum){
      if(minimumTmp <=0 && log) minimum*=0.1;
      else minimum = minimumTmp;
    }
    if(maximumTmp > maximum) maximum = maximumTmp;

    legend -> AddEntry(h[i],label[i],"AP");
  }

  c[iterator] -> cd();
  if(log){
    gPad -> SetLogy();
    h[0]->SetMaximum(maximum*3);
  }
  else h[0]->SetMaximum(maximum*1.1);  

  h[0] -> SetMinimum(minimum);

  h[0] -> Draw();
  //hidden option how to draw line at 1 for correlation functions "behind" the plot
  if((canvasName.Contains("CF") || canvasName.Contains("CorrFun") || canvasName.Contains("Correlation") || canvasName.Contains("CorrFun")) && 
    linesToDraw[0].line->GetY1()==linesToDraw[0].line->GetY2() && linesToDraw[0].line->GetY1()==1){

    linesToDraw[0].line -> SetX1(xMin); //just to make sure it'll draw properly
    linesToDraw[0].line -> SetX2(xMax);
    linesToDraw[0].line -> Draw("same");
    for(uint i=0; i<h.size(); i++){
      h[i] -> Draw("same");
    }
    for(uint i=1; i<linesToDraw.size(); i++){
      linesToDraw[i].line -> Draw("same");
    }

  }
  else{ //else draw it normally
    for(uint i=1; i<h.size(); i++){
      h[i] -> Draw("same");
    }
    for(uint i=0; i<linesToDraw.size(); i++){
      linesToDraw[i].line -> Draw("same");
    }
  }
  legend -> Draw("same"); 

  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }
  c[iterator] -> Write(); 

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);     
  } 
  
  f -> Save();
  iterator++;

  gPad -> SetLogy(0);
  h[0] -> SetMaximum(maximumh0);
  h[0] -> SetMinimum(minimumh0);
}

//2D
void singlePlot2DCanvasLines(TFile* f, TCanvas* c[], int &iterator, TH2D* h, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, TString zAxisLabel, double xMin, double xMax, double yMin, double yMax, vector<GLine> linesToDraw, bool log=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){
  
  setBasicStyle();
  c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
  setCanvas(c[iterator]);

  f -> cd();

  h -> GetXaxis() -> SetRangeUser(xMin,xMax);
  h -> GetYaxis() -> SetRangeUser(yMin,yMax);
  if(!histTitle.EqualTo(""))h -> SetTitle(smartSplit(histTitle));
  if(!xAxisLabel.EqualTo(""))h -> GetXaxis() -> SetTitle(xAxisLabel);
  if(!yAxisLabel.EqualTo(""))h -> GetYaxis() -> SetTitle(yAxisLabel);
  if(!zAxisLabel.EqualTo(""))h -> GetYaxis() -> SetTitle(zAxisLabel);
  setTitlesStyle(h);

  if(binWithNorm) normToBinWidth(h,rebinFactor);
  else if(!binWithNorm && rebinFactor>1) h->Rebin2D(rebinFactor);

  c[iterator] -> cd();
  if(log)gPad -> SetLogz();
  
  h -> Draw("colz");

  for(uint i=0; i<linesToDraw.size(); i++){
    linesToDraw[i].line -> Draw("same");
  }  

  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }
  c[iterator]->Update();

  //shrink color bar a little
  TPaletteAxis *palette = (TPaletteAxis*)h->GetListOfFunctions()->FindObject("palette");
  palette->SetX1NDC(0.885);
  palette->SetX2NDC(0.905);
  palette->SetY1NDC(0.2);
  palette->SetY2NDC(0.85);
  c[iterator]->Modified();
  c[iterator] -> Write();

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);      
  } 

  f -> Save();
  iterator++;
}

//=========================================================
// plot functions with function overlays
//=========================================================


//todo later, not needed asap

//===================================================================
// plot functions with lines AND function overlays (YEY, more stuff!)
//===================================================================

void singlePlotCanvasLinesAndFunctions(TFile *f, TCanvas* c[], int &iterator, TH1D* h, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, double xMin, double xMax, vector<GLine> linesToDraw, vector<GFunction> funsToDraw, int color=DEFAULT_COLOR, int markerStyle=DEFAULT_STYLE, double markerSize=DEFAULT_SIZE, bool log=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){
  setBasicStyle();
  c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
  setCanvas(c[iterator]);

  h -> GetXaxis() -> SetRangeUser(xMin,xMax);

  if(!histTitle.EqualTo(""))h -> SetTitle(smartSplit(histTitle));
  if(!xAxisLabel.EqualTo(""))h -> GetXaxis() -> SetTitle(xAxisLabel);
  if(!yAxisLabel.EqualTo(""))h -> GetYaxis() -> SetTitle(yAxisLabel);
  setTitlesStyle(h);
  
  if(binWithNorm) normToBinWidth(h,rebinFactor);
  else if(!binWithNorm && rebinFactor>1) h->Rebin(rebinFactor);

  h -> SetMarkerStyle(markerStyle);
  h -> SetMarkerSize(markerSize);
  h -> SetMarkerColor(color);
  h -> SetLineColor(color);
  
  f -> cd();
  c[iterator] -> cd();
  if(log)gPad -> SetLogy();
  h -> Draw();

  //hidden option how to draw line at 1 for correlation functions "behind" the plot
  if((canvasName.Contains("CF") || canvasName.Contains("CorrFun") || canvasName.Contains("Correlation") || canvasName.Contains("CorrFun")) && 
    linesToDraw[0].line->GetY1()==linesToDraw[0].line->GetY2() && linesToDraw[0].line->GetY1()==1){

    linesToDraw[0].line -> SetX1(xMin); //just to make sure it'll draw properly
    linesToDraw[0].line -> SetX2(xMax);
    linesToDraw[0].line -> Draw("same");
    h -> Draw("same");
    for(uint i=1; i<linesToDraw.size(); i++){
      linesToDraw[i].line -> Draw("same");
    }

  }
  else{ //else draw it normally
    for(uint i=0; i<linesToDraw.size(); i++){
      linesToDraw[i].line -> Draw("same");
    }
  }

  //drawing functions;
  for(uint i=0; i<funsToDraw.size(); i++){
    if(funsToDraw[i].f1D!=nullptr) funsToDraw[i].f1D -> Draw("same");
    if(funsToDraw[i].f2D!=nullptr) funsToDraw[i].f2D -> Draw("same"); //dunno why you would want to do it... but you can!
  }

  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }
  c[iterator] -> Write(); 

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);     
  } 

  f -> Save();
  iterator++;
}

//version with legend added
void singlePlotCanvasLinesAndFunctions(TFile *f, TCanvas* c[], int &iterator, TH1D* h, vector<TString> label, Coordinates coords, TString canvasName, TString histTitle, TString xAxisLabel, TString yAxisLabel, double xMin, double xMax, vector<GLine> linesToDraw, vector<GFunction> funsToDraw, int color=DEFAULT_COLOR, int markerStyle=DEFAULT_STYLE, double markerSize=DEFAULT_SIZE, bool log=false, int rebinFactor=1, bool binWithNorm=false, vector <TPaveText*> paves = {}, TString pathToSaveGIF=""){
  setBasicStyle();
  c[iterator] = new TCanvas(canvasName,canvasName,CANVAS_X,CANVAS_Y);
  setCanvas(c[iterator]);

  TLegend *legend = new TLegend(coords.xMin,coords.yMin,coords.xMax,coords.yMax,"","NDC");
  setlegendStyle(legend);

  h -> GetXaxis() -> SetRangeUser(xMin,xMax);

  if(!histTitle.EqualTo(""))h -> SetTitle(smartSplit(histTitle));
  if(!xAxisLabel.EqualTo(""))h -> GetXaxis() -> SetTitle(xAxisLabel);
  if(!yAxisLabel.EqualTo(""))h -> GetYaxis() -> SetTitle(yAxisLabel);
  setTitlesStyle(h);
  
  if(binWithNorm) normToBinWidth(h,rebinFactor);
  else if(!binWithNorm && rebinFactor>1) h->Rebin(rebinFactor);

  h -> SetMarkerStyle(markerStyle);
  h -> SetMarkerSize(markerSize);
  h -> SetMarkerColor(color);
  h -> SetLineColor(color);
  
  f -> cd();
  c[iterator] -> cd();
  if(log)gPad -> SetLogy();
  h -> Draw();

  //hidden option how to draw line at 1 for correlation functions "behind" the plot
  if((canvasName.Contains("CF") || canvasName.Contains("CorrFun") || canvasName.Contains("Correlation") || canvasName.Contains("CorrFun")) && 
    linesToDraw[0].line->GetY1()==linesToDraw[0].line->GetY2() && linesToDraw[0].line->GetY1()==1){

    linesToDraw[0].line -> SetX1(xMin); //just to make sure it'll draw properly
    linesToDraw[0].line -> SetX2(xMax);
    linesToDraw[0].line -> Draw("same");
    h -> Draw("same");
    for(uint i=1; i<linesToDraw.size(); i++){
      linesToDraw[i].line -> Draw("same");
    }

  }
  else{ //else draw it normally
    for(uint i=0; i<linesToDraw.size(); i++){
      linesToDraw[i].line -> Draw("same");
    }
  }

  //drawing functions;
  for(uint i=0; i<funsToDraw.size(); i++){
    if(funsToDraw[i].f1D!=nullptr){
      funsToDraw[i].f1D -> Draw("same");
      legend -> AddEntry(funsToDraw[i].f1D, label[i], "AL");
    }
    if(funsToDraw[i].f2D!=nullptr){ //dunno why you would want to do it... but you can!
      funsToDraw[i].f2D -> Draw("same"); 
      legend -> AddEntry(funsToDraw[i].f2D, label[i], "AL");
    }
  }
  legend -> Draw("SAME");
  
  for(uint i=0; i<paves.size(); i++){ //drawing optional TPaves
    paves[i]->Draw();
  }

  c[iterator] -> Write(); 

  if(!pathToSaveGIF.EqualTo("")){ //if saving option is active
    saveAsGIF(c[iterator], canvasName, pathToSaveGIF);     
  } 

  f -> Save();
  iterator++;
}

