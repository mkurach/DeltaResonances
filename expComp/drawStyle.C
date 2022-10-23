#ifndef DRAW_STYLE
#define DRAW_STYLE

using namespace std;
#include "TStyle.h"
#include "TSystem.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TObject.h"
#include "TString.h"
#include "TLine.h"
#include "TH2F.h"
#include "TLatex.h"
#include "TGraph.h"
#include "iostream"
#include "TF1.h"
#include "TAxis.h"
#include "TColor.h"
#include "TROOT.h"


static const Float_t titlesize = 0.06;
static const Float_t labelsize = 0.05;
static const Float_t titleoffsetx = 0.7;
static const Float_t titleoffsety = 1.2;
static const Float_t font = 42;


void  drawStyle()
{
    // root -l
    // .L drawStyle.C++

    // gSystem->Load("/misc/galatyuk/tools/drawStyle_C.so");
    // drawStyle();

    cout<<" -- SET DRAW OPTIONS LOADED --"<<endl;

    // defining canvas options ------------------------
    gStyle->SetCanvasColor(10);
    gStyle->SetPadColor(10);

    // defining size of pad ---------------------------
    gStyle->SetPadTopMargin(0.06);
    gStyle->SetPadBottomMargin(0.13);
    gStyle->SetPadRightMargin(0.07);
    gStyle->SetPadLeftMargin(0.17);
    gStyle->SetPadBorderMode(0);

    // switch options of the histogram ----------------
    gStyle->SetOptStat(0);         // switch off stat box
//    gStyle->SetErrorX(0);          // switch off error in x
    gStyle->SetTitleStyle(0);      // make title box transparent
    gStyle->SetTitleBorderSize(0); // make border of box disapear
}

void setPad(TVirtualPad *canvas)
{
    gStyle->SetLineStyleString(22,"80 18 12 18 12 12");
    canvas->SetFillColor(10);
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(0);
    canvas->SetTickx();
    canvas->SetTicky();
    canvas->SetFrameLineWidth(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameBorderSize(0);
    canvas->SetLeftMargin(0.17);
    canvas->SetRightMargin(0.07);
    canvas->SetTopMargin(0.074);
    canvas->SetBottomMargin(0.165);
    canvas->Range(-194.483,-10.3682,1041.38,-2.08469);
}

void setCanvas(TCanvas *canvas)
{
    gStyle->SetLineStyleString(22,"80 18 12 18 12 12");
    canvas->SetFillColor(10);
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(0);
    canvas->SetTickx();
    canvas->SetTicky();
    canvas->SetFrameLineWidth(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameBorderSize(0);
    canvas->SetLeftMargin(0.17);
    canvas->SetRightMargin(0.07);
    canvas->SetTopMargin(0.074);
    canvas->SetBottomMargin(0.165);
    canvas->ToggleEventStatus();
    canvas->Range(-194.483,-10.3682,1041.38,-2.08469);
}

// this function is setting the style of the plotting historgrams
// as an argument one should give name of the histogram, title of the X and Y axis
// Ndevision for the X axis, style, size and the color of the marker
// e.g for the official PRL plot for the RAW spectra of the NOV02 it was used in the following way:
// setOPT_hists(signal,20,1.3);
// setOPT_hists(background,24,1.3,2);
// setOPT_hists(unlikesign,22,1.3,4);
void setTH1(TH1 *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1.5, Int_t color=1)
{
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.06);
    hist->GetYaxis()->SetTitleSize(0.06);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.2);
    hist->GetXaxis()->SetTitleOffset(0.9);
//    hist->GetXaxis()->CenterTitle();
//    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.06);
    hist->GetYaxis()->SetLabelSize(0.06);
    //hist->GetXaxis()->SetRangeUser(0., 650.);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color);
    hist->SetLineColor(color);
    hist->SetLineWidth(2);
//    hist->SetMinimum(5e-5);
//    hist->SetMaximum(1e2);
}

void setTH1rap(TH1 *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1.5, Int_t color=1)
{
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.04);
    hist->GetYaxis()->SetTitleSize(0.04);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.9);
    hist->GetXaxis()->SetTitleOffset(0.9);
//    hist->GetXaxis()->CenterTitle();
//    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.04);
    hist->GetYaxis()->SetLabelSize(0.04);
    //hist->GetXaxis()->SetRangeUser(0., 650.);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color);
    hist->SetLineColor(color);
    hist->SetLineWidth(2);
//    hist->SetMinimum(5e-5);
//    hist->SetMaximum(1e2);
}

void setTH1broad(TH1 *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1.5, Int_t color=1)
{
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.06);
    hist->GetYaxis()->SetTitleSize(0.06);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.2/2.);
    hist->GetXaxis()->SetTitleOffset(0.9);
//    hist->GetXaxis()->CenterTitle();
//    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetYaxis()->SetLabelSize(0.05);
    //hist->GetXaxis()->SetRangeUser(0., 650.);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color);
    hist->SetLineColor(color);
    hist->SetLineWidth(2);
//    hist->SetMinimum(5e-5);
//    hist->SetMaximum(1e2);
}

void setTH2(TH2 *hist2, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510)
{
    //gStyle->SetPadRightMargin(0.15);
    hist2->GetXaxis()->SetTitle(xAxisTitle);
    hist2->GetYaxis()->SetTitle(yAxisTitle);
    hist2->GetXaxis()->SetTitleSize(0.06);
    hist2->GetYaxis()->SetTitleSize(0.06);
    hist2->GetZaxis()->SetTitleSize(0.06);
    hist2->GetXaxis()->SetTitleFont(42);
    hist2->GetYaxis()->SetTitleFont(42);
    hist2->GetZaxis()->SetTitleFont(42);
    hist2->GetXaxis()->SetNdivisions(Ndevision);
    hist2->GetXaxis()->SetLabelFont(42);
    hist2->GetYaxis()->SetLabelFont(42);
    hist2->GetZaxis()->SetLabelFont(42);
    hist2->GetXaxis()->SetLabelSize(0.05);
    hist2->GetYaxis()->SetLabelSize(0.05);
    hist2->GetZaxis()->SetLabelSize(0.04);
    hist2->GetYaxis()->SetTitleOffset(1.3);

    gStyle->SetPadLeftMargin(0.17);
    gStyle->SetPadRightMargin(0.13);

}

void setTF1(TF1 *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1.3, Int_t color=1, Int_t lineWidth=2)
{
    gStyle->SetPadRightMargin(0.05);
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.06);
    hist->GetYaxis()->SetTitleSize(0.06);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
//    hist->GetXaxis()->CenterTitle();
//    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetYaxis()->SetLabelSize(0.05);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color);
    hist->SetLineColor(color);
    hist->SetLineWidth(lineWidth);
}



void setGraph(TGraph *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1.3, Int_t color=1, Int_t lineWidth=2)
{
//////////////////
    //gStyle->SetPadRightMargin(0.05);
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(titlesize);
    hist->GetYaxis()->SetTitleSize(titlesize);
    hist->GetXaxis()->SetTitleFont(font);
    hist->GetYaxis()->SetTitleFont(font);
    hist->GetXaxis()->SetNdivisions(Ndevision);
//    hist->GetXaxis()->CenterTitle();
//    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetLabelFont(font);
    hist->GetYaxis()->SetLabelFont(font);
    hist->GetXaxis()->SetLabelSize(labelsize);
    hist->GetYaxis()->SetLabelSize(labelsize);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color);
    hist->SetLineColor(color);
    hist->SetLineWidth(lineWidth);
}



void setText(TPaveText *p, Int_t color=1)
{
    p->SetFillColor(10);
    p->SetTextColor(color);
    p->SetBorderSize(-1);
    p->SetTextFont(42);
}



void setLabel(TPaveLabel *p)
{
    p->SetFillColor(10);
    p->SetBorderSize(-1);
    p->SetTextFont(42);
}



void setLegend(TLegend *p)
{
    p->SetFillColor(10);
    p->SetBorderSize(-1);
    p->SetTextFont(42);
}



TLegend* plotLegend(TString pos="right_top",TString Title="No Title",Float_t scaleX=0.9,Float_t scaleY=0.9,Float_t offsetX=0.0,Float_t offsetY=0.0,TString Comment="",Int_t commentcolor=1)
{
    // pos places the Legend and can be
    // right_top, mid_top, left_top, right_bottom,mid_bottom,left_bottom
    // Title gives you the Title of the legend
    // scaleX,scaleY defines the size (=1 means 1/3 pad with,1/3 pad height (according to pos))
    // offsetX , offsetY (NDC coordinates of pad -> 0.1) shift by 10% of pad with) shifts the legend by the value in x and y
    // comment is optional text below title before legend entris will start
    // commentcolor defines the text color of the comment

    Float_t left  =gPad->GetLeftMargin()*1.15;
    Float_t right =1-gPad->GetRightMargin();
    Float_t top   =1-gPad->GetTopMargin();
    Float_t bottom=gPad->GetBottomMargin()*1.15;
    Float_t mid   =gPad->GetLeftMargin() + (1-(gPad->GetRightMargin()+gPad->GetLeftMargin()))/2;
    Float_t width =(right-left)/2;
    Float_t heith =(top-bottom)/2;
    TLegend* legend;
    TLine* dummy=new TLine();
    dummy->SetLineColor(10);

    if(pos.CompareTo("left_top")==0)    legend=new TLegend(left+offsetX,top+offsetY-(scaleY*heith),left+offsetX+(scaleX*width),top+offsetY,Title.Data());                           // left top
    if(pos.CompareTo("mid_top")==0)     legend=new TLegend(mid+offsetX-((scaleX*width)/2),top+offsetY-(scaleY*heith),mid+offsetX+((scaleX*width)/2),top+offsetY,Title.Data());      // mid up
    if(pos.CompareTo("right_top")==0)   legend=new TLegend(right+offsetX-(scaleX*width),top+offsetY-(scaleY*heith),right+offsetX,top+offsetY,Title.Data());                         // right top
    if(pos.CompareTo("left_bottom")==0) legend=new TLegend(left+offsetX,bottom+offsetY,left+offsetX+(scaleX*width),bottom+offsetY+(scaleY*heith),Title.Data());                     // left bottom
    if(pos.CompareTo("mid_bottom")==0)  legend=new TLegend(mid+offsetX-((scaleX*width)/2),bottom+offsetY,mid+offsetX+((scaleX*width)/2),bottom+offsetY+(scaleY*heith),Title.Data());// mid down
    if(pos.CompareTo("right_bottom")==0)legend=new TLegend(right+offsetX-(scaleX*width),bottom+offsetY,right+offsetX,bottom+offsetY+(scaleY*heith),Title.Data());                   // right bottom

    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetMargin(0.15);



    if(Comment.CompareTo("")!=0)
    {   // comment below header
        TLegendEntry* entry=legend->AddEntry(dummy,Comment.Data());
        entry->SetTextColor(commentcolor);
        entry->SetTextFont(62);
        entry->SetOption("l");
    }
    return legend;
}
void setLegendEntry(TLegend* legend,TObject* object,char* label,Int_t col,TString opt,Float_t size=0.05)
{
    // add entry for object with label and color and option to legend
    // legend is thge pointer to the legend where you want to add the entry
    // object ist the histogram or graph which will be added
    // label is the text which will appear in the entry
    // col is th color of the text
    // opt is the option ("pL"(marker and line), "p"(marker),"l"(line))
    TLegendEntry* entry=legend->AddEntry((TObject*)object,label);
    entry->SetTextColor(col);
    entry->SetTextSize(size);
    entry->SetOption(opt.Data());
}
TLatex* plotTopLegend(char* label,Float_t x=-1,Float_t y=-1,Float_t size=0.05,Int_t color=1)
{
    // coordinates in NDC!
    // plots the string label in position x and y in NDC coordinates
    // size is the text size
    // color is the text color

    if(x<0||y<0)
    {   // defaults
        x=gPad->GetLeftMargin()*1.15;
        y=(1-gPad->GetTopMargin())*1.02;
    }
    TLatex* text=new TLatex(x,y,label);
    text->SetTextSize(size);
    text->SetNDC();
    text->SetTextColor(color);
    text->Draw();
    return text;
}
/*
void saveToPdf(TCanvas* canvas,Char_t* path,Char_t* filename,Bool_t separate=kFALSE)
{
    // saves a canvas to pdf file by storing it as ps and calling
    // ps2pdf to convert it to pdf. The ps file will be removed.
    // canvas is the pointer of the canvas which you want to save
    // path is the path to the directory where you want to store the pdf
    // filename is the name of the pdf which wou create
    // separate=kTRUE will loop over all pads and save the pictures single (path/filename_i)
    // separate=kFALSE as the canvas in one pdf.
    TString File    =filename;
    TString Path    =path;
    Path            =Path + "/";
    TString command ="";
    TString totalin ="";
    TString totalout="";

    File.ReplaceAll(".ps","");
    File.ReplaceAll(".pdf","");

    if(!separate)
    {
        totalin = Path + File + ".ps";
        totalout= Path + File + ".pdf";
        canvas->SaveAs(totalin.Data());
        command= "ps2pdf " + totalin + " " + totalout;
        gSystem->Exec(command.Data());
        command= "rm " + totalin;
        gSystem->Exec(command.Data());
    }else{
        TString subpad="";
        Int_t npads= canvas->GetListOfPrimitives()->GetSize();
        for(Int_t i=1;i<=npads;i++)
        {
            subpad=i;
            totalin = Path + File + "_" + subpad + ".ps";
            totalout= Path + File + "_" + subpad + ".pdf";
            canvas->cd(i);
            gPad->SaveAs(totalin.Data());
            command= "ps2pdf " + totalin + " " + totalout;
            gSystem->Exec(command.Data());
            command= "rm " + totalin;
            gSystem->Exec(command.Data());
        }
    }
}
void saveToPng(TCanvas* canvas,Char_t* path,Char_t* filename,Bool_t separate=kFALSE)
{
    // saves a canvas to png file by storing it as gif and calling
    // convert to convert it to png. The gif file will be removed.
    // canvas is the pointer of the canvas which you want to save
    // path is the path to the directory where you want to store the png
    // filename is the name of the png which wou create
    // separate=kTRUE will loop over all pads and save the pictures single (path/filename_i)
    // separate=kFALSE as the canvas in one png.
    TString File    =filename;
    TString Path    =path;
    Path            =Path + "/";
    TString command ="";
    TString totalin ="";
    TString totalout="";


    File.ReplaceAll(".ps","");
    if(!separate)
    {
        totalin = Path + File + ".ps";
        totalout= Path + File + ".png";
        canvas->SaveAs(totalin.Data());
        command= "convert " + totalin + " " + totalout;
        gSystem->Exec(command.Data());
        command= "rm " + totalin;
        gSystem->Exec(command.Data());
    }else{
        TString subpad="";
        Int_t npads= canvas->GetListOfPrimitives()->GetSize();
        for(Int_t i=1;i<=npads;i++)
        {
            subpad=i;
            totalin = Path + File + "_" + subpad + ".ps";
            totalout= Path + File + "_" + subpad + ".png";
            canvas->cd(i);
            gPad->SaveAs(totalin.Data());
            command= "convert " + totalin + " " + totalout;
            gSystem->Exec(command.Data());
            command= "rm " + totalin;
            gSystem->Exec(command.Data());
        }
    }
}

void saveToC(TCanvas* canvas,Char_t* path,Char_t* filename,Bool_t separate=kFALSE)
{
    // saves a canvas to png file by storing it as gif and calling
    // convert to convert it to png. The gif file will be removed.
    // canvas is the pointer of the canvas which you want to save
    // path is the path to the directory where you want to store the png
    // filename is the name of the png which wou create
    // separate=kTRUE will loop over all pads and save the pictures single (path/filename_i)
    // separate=kFALSE as the canvas in one png.
    TString File    =filename;
    TString Path    =path;
    Path            =Path + "/";
    TString command ="";
    TString totalin ="";
    TString totalout="";

    File.ReplaceAll(".C","");
    if(!separate)
    {
        totalin = Path + File + ".C";
        canvas->SaveAs(totalin.Data());
    }else{
        TString subpad="";
        Int_t npads= canvas->GetListOfPrimitives()->GetSize();
        for(Int_t i=1;i<=npads;i++)
        {
            subpad=i;
            totalin = Path + File + "_" + subpad + ".C";
            canvas->cd(i);
            gPad->SaveAs(totalin.Data());
        }
    }
}

void saveGifToPdf(TCanvas* canvas,Char_t* path,Char_t* filename,Bool_t separate=kFALSE)
{
    // saves a canvas to pdf file by storing it as gif and calling
    // convert to convert it to pdf. The gif file will be removed.
    // canvas is the pointer of the canvas which you want to save
    // path is the path to the directory where you want to store the pdf
    // filename is the name of the pdf which wou create
    // separate=kTRUE will loop over all pads and save the pictures single (path/filename_i)
    // separate=kFALSE as the canvas in one pdf.
    TString File    =filename;
    TString Path    =path;
    Path            =Path + "/";
    TString command ="";
    TString totalin ="";
    TString totalout="";

    File.ReplaceAll(".pdf","");
    if(!separate)
    {
        totalin = Path + File + ".gif";
        totalout= Path + File + ".pdf";
        canvas->SaveAs(totalin.Data());
        command= "convert " + totalin + " " + totalout;
        gSystem->Exec(command.Data());
        command= "rm " + totalin;
        gSystem->Exec(command.Data());
    }else{
        TString subpad="";
        Int_t npads= canvas->GetListOfPrimitives()->GetSize();
        for(Int_t i=1;i<=npads;i++)
        {
            subpad=i;
            totalin = Path + File + "_" + subpad + ".gif";
            totalout= Path + File + "_" + subpad + ".pdf";
            canvas->cd(i);
            gPad->SaveAs(totalin.Data());
            command= "convert " + totalin + " " + totalout;
            gSystem->Exec(command.Data());
            command= "rm " + totalin;
            gSystem->Exec(command.Data());
        }
    }
    }
    */
Int_t getColor(Int_t i)
{
    // pre defined set of 10 colors
    // i is larger 9 it will start from the first color again
    Int_t colors[10]   ={2,4,6,8,38,46,14,1,30,43};
    return colors[i%10];
}
Int_t getMarker(Int_t i)
{
    // pre defined set of 10 marker styles
    // i is larger 9 it will start from the first marker style again
    Int_t style[10]   ={20,21,22,23,24,25,26,27,28,29};
    return style[i%10];
}
void setGraph(TGraph* graph,Int_t i,Int_t markerstyle=20,Int_t markercolor=1,Float_t markersize=1.,Int_t linecolor=1)
{
    // sets the graphics of graph (use full in a loop)
    // graph is the pointer of the graph
    //
    // i switches to modes:
    // (if i>0) i the number of the color of the marker and the markert style (getColor(),getMarker())
    // (if i<0) marker color and style will be  markercolor, markerstyle
    //
    // markersize, and linecolor defines the size of the marker and the line color
    // can be use in two ways:
    // values >=0 the style and color will be set via getColor(i),getMarker(i)
    // values < 0 the style and color will be set -markercolor -markerstyle

    if(i<0)
    {
        graph->SetMarkerColor(markercolor);
        graph->SetMarkerSize(markersize);
        graph->SetMarkerStyle(markerstyle);
        graph->SetLineColor(linecolor);
    }else{
        if     (markercolor>=0)graph->SetMarkerColor(getColor(i));
        else if(markercolor<0) graph->SetMarkerColor(getColor(-markercolor));
        graph->SetMarkerSize(markersize);
        if     (markerstyle>=0)graph->SetMarkerStyle(getMarker(i));
        else if(markerstyle<0) graph->SetMarkerStyle(getMarker(-markerstyle));
        graph->SetLineColor(linecolor);
    }
}
void setHist(TH1* hist,Int_t i,Int_t markerstyle=20,Int_t markercolor=1,Float_t markersize=1.,Int_t linecolor=1)
{
    // sets the graphics of histogram (use full in a loop)
    // hist is the pointer of the hiistogram
    //
    // i switches to modes:
    // (if i>0) i the number of the color of the marker and the markert style (getColor(),getMarker())
    // (if i<0) marker color and style will be  markercolor, markerstyle
    //
    // markersize, and linecolor defines the size of the marker and the line color
    // can be use in two ways:
    // values >=0 the style and color will be set via getColor(i),getMarker(i)
    // values < 0 the style and color will be set -markercolor -markerstyle
    if(i==-99)
    {
        hist->SetMarkerColor(markercolor);
        hist->SetMarkerSize(markersize);
        hist->SetMarkerStyle(markerstyle);
        hist->SetLineColor(linecolor);
    }else{
        if     (markercolor>=0)hist->SetMarkerColor(getColor(i));
        else if(markercolor<0) hist->SetMarkerColor(getMarker(-markercolor));
        hist->SetMarkerSize(markersize);
        if     (markerstyle>=0)hist->SetMarkerStyle(getMarker(i));
        else if(markerstyle<0) hist->SetMarkerStyle(getMarker(-markerstyle));
        hist->SetLineColor(linecolor);
      }
}

TPaveText *setOPT_text(TString cut_desc ,  Double_t x1, Double_t y1, Double_t x2, Double_t y2,Int_t color=1, Double_t textSize=0.2)
{
  TPaveText *description=new TPaveText(x1,y1,x2,y2,"NDC");
  //TPaveText *description=new TPaveText(x1,y1,x2,y2,"blNDC");
 
  description->SetLineWidth(0);
  description->AddText(cut_desc);
//   description->SetTextSize(0.046);
  description->SetTextSize(textSize);
  description->SetBorderSize(0.0);
  description->SetTextFont(62);
  description->SetTextColor(color);
  description->SetFillColor(0);
  description->SetFillStyle(0);
  description->Draw();
  return description;
}

TPaveText *setOPT_text2(TString cut_desc ,  Double_t x1, Double_t y1, Double_t x2, Double_t y2,Int_t color=1, Double_t
textSize=0.2)
{
  TPaveText *description=new TPaveText(x1,y1,x2,y2,"NDC");
  //TPaveText *description=new TPaveText(x1,y1,x2,y2,"blNDC");
 
  description->SetLineWidth(0);
  description->AddText(cut_desc);
//   description->SetTextSize(0.046);
  description->SetTextSize(textSize);
  description->SetBorderSize(0.0);
  description->SetTextFont(42);
  description->SetTextColor(color);
  description->SetFillColor(0);
  description->SetFillStyle(0);
  description->SetTextAlign(13);
  description->Draw();
  return description;
}

namespace {
/*
   static Bool_t& TColor__GrayScaleMode() {
      static Bool_t grayScaleMode;
      return grayScaleMode;
   }
*/
   static TArrayI& TColor__Palette() {
      static TArrayI globalPalette(0);
      return globalPalette;
   }
   static TArrayD& TColor__PalettesList() {
      static TArrayD globalPalettesList(0);
      return globalPalettesList;
   }
}

//#define fgGrayscaleMode TColor__GrayScaleMode()
#define fgPalette TColor__Palette()
#define fgPalettesList TColor__PalettesList()
/*    //redefinicja EColorPalette z TColor.h
enum MyColorPalette {kDeepSea=51,          kGreyScale=52,    kDarkBodyRadiator=53,
    kBlueYellow= 54,      kRainBow=55,      kInvertedDarkBodyRadiator=56,
    kBird=57,             kCubehelix=58,    kGreenRedViolet=59,
    kBlueRedYellow=60,    kOcean=61,        kColorPrintableOnGrey=62,
    kAlpine=63,           kAquamarine=64,   kArmy=65,
    kAtlantic=66,         kAurora=67,       kAvocado=68,
    kBeach=69,            kBlackBody=70,    kBlueGreenYellow=71,
    kBrownCyan=72,        kCMYK=73,         kCandy=74,
    kCherry=75,           kCoffee=76,       kDarkRainBow=77,
    kDarkTerrain=78,      kFall=79,         kFruitPunch=80,
    kFuchsia=81,          kGreyYellow=82,   kGreenBrownTerrain=83,
    kGreenPink=84,        kIsland=85,       kLake=86,
    kLightTemperature=87, kLightTerrain=88, kMint=89,
    kNeon=90,             kPastel=91,       kPearl=92,
    kPigeon=93,           kPlum=94,         kRedBlue=95,
    kRose=96,             kRust=97,         kSandyTerrain=98,
    kSienna=99,           kSolar=100,       kSouthWest=101,
    kStarryNight=102,     kSunset=103,      kTemperatureMap=104,
    kThermometer=105,     kValentine=106,   kVisibleSpectrum=107,
    kWaterMelon=108,      kCool=109,        kCopper=110,
    kGistEarth=111,       kViridis=112};
*/
void NewSetPalette(Int_t ncolors, Int_t *colors=0, Float_t alpha=1)
{
   Int_t i;

   static Int_t paletteType = 0;

   Int_t palette[50] = {19,18,17,16,15,14,13,12,11,20,
                        21,22,23,24,25,26,27,28,29,30, 8,
                        31,32,33,34,35,36,37,38,39,40, 9,
                        41,42,43,44,45,47,48,49,46,50, 2,
                         7, 6, 5, 4, 3, 2,1};

   // set default palette (pad type)
   if (ncolors <= 0) {
      ncolors = 50;
      fgPalette.Set(ncolors);
      for (i=0;i<ncolors;i++) fgPalette.fArray[i] = palette[i];
      paletteType = 1;
      return;
   }

   // set Rainbow Color map. Kept for backward compatibility.
   if (ncolors == 1 && colors == 0) {
      ncolors = 50;
      fgPalette.Set(ncolors);
      for (i=0;i<ncolors;i++) fgPalette.fArray[i] = 51+i;
      paletteType = 2;
      return;
   }

   // High quality palettes (255 levels)
   if (colors == 0 && ncolors>50) {

      if (!fgPalettesList.fN) fgPalettesList.Set(62);        // Right now 62 high quality palettes
      Int_t Idx = (Int_t)fgPalettesList.fArray[ncolors-51];  // High quality palettes indices start at 51

      // This high quality palette has already been created. Reuse it.
      if (Idx > 0) {
         Double_t alphas = 10*(fgPalettesList.fArray[ncolors-51]-Idx);
         Bool_t same_alpha = TMath::Abs(alpha-alphas) < 0.0001;
         if (paletteType == ncolors && same_alpha) return; // The current palette is already this one.
         fgPalette.Set(255); // High quality palettes have 255 entries
         for (i=0;i<255;i++) fgPalette.fArray[i] = Idx+i;
         paletteType = ncolors;

         // restore the palette transparency if needed
          if (alphas>0 && !same_alpha) {
             TColor *ca;
             for (i=0;i<255;i++) {
                ca = gROOT->GetColor(Idx+i);
                ca->SetAlpha(alpha);
             }
             fgPalettesList.fArray[paletteType-51] = (Double_t)Idx+alpha/10.;
          }
         return;
      }

      TColor::InitializeColors();
      Double_t stops[9] = { 0.0000, 0.1250, 0.2500, 0.3750, 0.5000, 0.6250, 0.7500, 0.8750, 1.0000};

      switch (ncolors) {
      // Deep Sea
      case 51:
         {
            Double_t red[9]   = {  0./255.,  9./255., 13./255., 17./255., 24./255.,  32./255.,  27./255.,  25./255.,  29./255.};
            Double_t green[9] = {  0./255.,  0./255.,  0./255.,  2./255., 37./255.,  74./255., 113./255., 160./255., 221./255.};
            Double_t blue[9]  = { 28./255., 42./255., 59./255., 78./255., 98./255., 129./255., 154./255., 184./255., 221./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Grey Scale
      case 52:
         {
            Double_t red[9]   = { 0./255., 32./255., 64./255., 96./255., 128./255., 160./255., 192./255., 224./255., 255./255.};
            Double_t green[9] = { 0./255., 32./255., 64./255., 96./255., 128./255., 160./255., 192./255., 224./255., 255./255.};
            Double_t blue[9]  = { 0./255., 32./255., 64./255., 96./255., 128./255., 160./255., 192./255., 224./255., 255./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Dark Body Radiator
      case 53:
         {
            Double_t red[9]   = { 0./255., 45./255., 99./255., 156./255., 212./255., 230./255., 237./255., 234./255., 242./255.};
            Double_t green[9] = { 0./255.,  0./255.,  0./255.,  45./255., 101./255., 168./255., 238./255., 238./255., 243./255.};
            Double_t blue[9]  = { 0./255.,  1./255.,  1./255.,   3./255.,   9./255.,   8./255.,  11./255.,  95./255., 230./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Two-color hue (dark blue through neutral gray to bright yellow)
      case 54:
         {
            Double_t red[9]   = {  0./255.,  22./255., 44./255., 68./255., 93./255., 124./255., 160./255., 192./255., 237./255.};
            Double_t green[9] = {  0./255.,  16./255., 41./255., 67./255., 93./255., 125./255., 162./255., 194./255., 241./255.};
            Double_t blue[9]  = { 97./255., 100./255., 99./255., 99./255., 93./255.,  68./255.,  44./255.,  26./255.,  74./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Rain Bow
      case 55:
         {
            Double_t red[9]   = {  0./255.,   5./255.,  15./255.,  35./255., 102./255., 196./255., 208./255., 199./255., 110./255.};
            Double_t green[9] = {  0./255.,  48./255., 124./255., 192./255., 206./255., 226./255.,  97./255.,  16./255.,   0./255.};
            Double_t blue[9]  = { 99./255., 142./255., 198./255., 201./255.,  90./255.,  22./255.,  13./255.,   8./255.,   2./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Inverted Dark Body Radiator
      case 56:
         {
            Double_t red[9]   = { 242./255., 234./255., 237./255., 230./255., 212./255., 156./255., 99./255., 45./255., 0./255.};
            Double_t green[9] = { 243./255., 238./255., 238./255., 168./255., 101./255.,  45./255.,  0./255.,  0./255., 0./255.};
            Double_t blue[9]  = { 230./255.,  95./255.,  11./255.,   8./255.,   9./255.,   3./255.,  1./255.,  1./255., 0./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Bird
      case 57:
         {
            Double_t red[9]   = { 0.2082, 0.0592, 0.0780, 0.0232, 0.1802, 0.5301, 0.8186, 0.9956, 0.9764};
            Double_t green[9] = { 0.1664, 0.3599, 0.5041, 0.6419, 0.7178, 0.7492, 0.7328, 0.7862, 0.9832};
            Double_t blue[9]  = { 0.5293, 0.8684, 0.8385, 0.7914, 0.6425, 0.4662, 0.3499, 0.1968, 0.0539};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Cubehelix
      case 58:
         {
            Double_t red[9]   = { 0.0000, 0.0956, 0.0098, 0.2124, 0.6905, 0.9242, 0.7914, 0.7596, 1.0000};
            Double_t green[9] = { 0.0000, 0.1147, 0.3616, 0.5041, 0.4577, 0.4691, 0.6905, 0.9237, 1.0000};
            Double_t blue[9]  = { 0.0000, 0.2669, 0.3121, 0.1318, 0.2236, 0.6741, 0.9882, 0.9593, 1.0000};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Green Red Violet
      case 59:
         {
            Double_t red[9]   = {13./255., 23./255., 25./255., 63./255., 76./255., 104./255., 137./255., 161./255., 206./255.};
            Double_t green[9] = {95./255., 67./255., 37./255., 21./255.,  0./255.,  12./255.,  35./255.,  52./255.,  79./255.};
            Double_t blue[9]  = { 4./255.,  3./255.,  2./255.,  6./255., 11./255.,  22./255.,  49./255.,  98./255., 208./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Blue Red Yellow
      case 60:
         {
            Double_t red[9]   = {0./255.,  61./255.,  89./255., 122./255., 143./255., 160./255., 185./255., 204./255., 231./255.};
            Double_t green[9] = {0./255.,   0./255.,   0./255.,   0./255.,  14./255.,  37./255.,  72./255., 132./255., 235./255.};
            Double_t blue[9]  = {0./255., 140./255., 224./255., 144./255.,   4./255.,   5./255.,   6./255.,   9./255.,  13./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Ocean
      case 61:
         {
            Double_t red[9]   = { 14./255.,  7./255.,  2./255.,  0./255.,  5./255.,  11./255.,  55./255., 131./255., 229./255.};
            Double_t green[9] = {105./255., 56./255., 26./255.,  1./255., 42./255.,  74./255., 131./255., 171./255., 229./255.};
            Double_t blue[9]  = {  2./255., 21./255., 35./255., 60./255., 92./255., 113./255., 160./255., 185./255., 229./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Color Printable On Grey
      case 62:
         {
            Double_t red[9]   = { 0./255.,   0./255.,   0./255.,  70./255., 148./255., 231./255., 235./255., 237./255., 244./255.};
            Double_t green[9] = { 0./255.,   0./255.,   0./255.,   0./255.,   0./255.,  69./255.,  67./255., 216./255., 244./255.};
            Double_t blue[9]  = { 0./255., 102./255., 228./255., 231./255., 177./255., 124./255., 137./255.,  20./255., 244./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Alpine
      case 63:
         {
            Double_t red[9]   = { 50./255., 56./255., 63./255., 68./255.,  93./255., 121./255., 165./255., 192./255., 241./255.};
            Double_t green[9] = { 66./255., 81./255., 91./255., 96./255., 111./255., 128./255., 155./255., 189./255., 241./255.};
            Double_t blue[9]  = { 97./255., 91./255., 75./255., 65./255.,  77./255., 103./255., 143./255., 167./255., 217./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Aquamarine
      case 64:
         {
            Double_t red[9]   = { 145./255., 166./255., 167./255., 156./255., 131./255., 114./255., 101./255., 112./255., 132./255.};
            Double_t green[9] = { 158./255., 178./255., 179./255., 181./255., 163./255., 154./255., 144./255., 152./255., 159./255.};
            Double_t blue[9]  = { 190./255., 199./255., 201./255., 192./255., 176./255., 169./255., 160./255., 166./255., 190./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Army
      case 65:
         {
            Double_t red[9]   = { 93./255.,   91./255.,  99./255., 108./255., 130./255., 125./255., 132./255., 155./255., 174./255.};
            Double_t green[9] = { 126./255., 124./255., 128./255., 129./255., 131./255., 121./255., 119./255., 153./255., 173./255.};
            Double_t blue[9]  = { 103./255.,  94./255.,  87./255.,  85./255.,  80./255.,  85./255., 107./255., 120./255., 146./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Atlantic
      case 66:
         {
            Double_t red[9]   = { 24./255., 40./255., 69./255.,  90./255., 104./255., 114./255., 120./255., 132./255., 103./255.};
            Double_t green[9] = { 29./255., 52./255., 94./255., 127./255., 150./255., 162./255., 159./255., 151./255., 101./255.};
            Double_t blue[9]  = { 29./255., 52./255., 96./255., 132./255., 162./255., 181./255., 184./255., 186./255., 131./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Aurora
      case 67:
         {
            Double_t red[9]   = { 46./255., 38./255., 61./255., 92./255., 113./255., 121./255., 132./255., 150./255., 191./255.};
            Double_t green[9] = { 46./255., 36./255., 40./255., 69./255., 110./255., 135./255., 131./255.,  92./255.,  34./255.};
            Double_t blue[9]  = { 46./255., 80./255., 74./255., 70./255.,  81./255., 105./255., 165./255., 211./255., 225./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Avocado
      case 68:
         {
            Double_t red[9]   = { 0./255.,  4./255., 12./255.,  30./255.,  52./255., 101./255., 142./255., 190./255., 237./255.};
            Double_t green[9] = { 0./255., 40./255., 86./255., 121./255., 140./255., 172./255., 187./255., 213./255., 240./255.};
            Double_t blue[9]  = { 0./255.,  9./255., 14./255.,  18./255.,  21./255.,  23./255.,  27./255.,  35./255., 101./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Beach
      case 69:
         {
            Double_t red[9]   = { 198./255., 206./255., 206./255., 211./255., 198./255., 181./255., 161./255., 171./255., 244./255.};
            Double_t green[9] = { 103./255., 133./255., 150./255., 172./255., 178./255., 174./255., 163./255., 175./255., 244./255.};
            Double_t blue[9]  = {  49./255.,  54./255.,  55./255.,  66./255.,  91./255., 130./255., 184./255., 224./255., 244./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Black Body
      case 70:
         {
            Double_t red[9]   = { 243./255., 243./255., 240./255., 240./255., 241./255., 239./255., 186./255., 151./255., 129./255.};
            Double_t green[9] = {   0./255.,  46./255.,  99./255., 149./255., 194./255., 220./255., 183./255., 166./255., 147./255.};
            Double_t blue[9]  = {   6./255.,   8./255.,  36./255.,  91./255., 169./255., 235./255., 246./255., 240./255., 233./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Blue Green Yellow
      case 71:
         {
            Double_t red[9]   = { 22./255., 19./255.,  19./255.,  25./255.,  35./255.,  53./255.,  88./255., 139./255., 210./255.};
            Double_t green[9] = {  0./255., 32./255.,  69./255., 108./255., 135./255., 159./255., 183./255., 198./255., 215./255.};
            Double_t blue[9]  = { 77./255., 96./255., 110./255., 116./255., 110./255., 100./255.,  90./255.,  78./255.,  70./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Brown Cyan
      case 72:
         {
            Double_t red[9]   = { 68./255., 116./255., 165./255., 182./255., 189./255., 180./255., 145./255., 111./255.,  71./255.};
            Double_t green[9] = { 37./255.,  82./255., 135./255., 178./255., 204./255., 225./255., 221./255., 202./255., 147./255.};
            Double_t blue[9]  = { 16./255.,  55./255., 105./255., 147./255., 196./255., 226./255., 232./255., 224./255., 178./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // CMYK
      case 73:
         {
            Double_t red[9]   = {  61./255.,  99./255., 136./255., 181./255., 213./255., 225./255., 198./255., 136./255., 24./255.};
            Double_t green[9] = { 149./255., 140./255.,  96./255.,  83./255., 132./255., 178./255., 190./255., 135./255., 22./255.};
            Double_t blue[9]  = { 214./255., 203./255., 168./255., 135./255., 110./255., 100./255., 111./255., 113./255., 22./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Candy
      case 74:
         {
            Double_t red[9]   = { 76./255., 120./255., 156./255., 183./255., 197./255., 180./255., 162./255., 154./255., 140./255.};
            Double_t green[9] = { 34./255.,  35./255.,  42./255.,  69./255., 102./255., 137./255., 164./255., 188./255., 197./255.};
            Double_t blue[9]  = { 64./255.,  69./255.,  78./255., 105./255., 142./255., 177./255., 205./255., 217./255., 198./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Cherry
      case 75:
         {
            Double_t red[9]   = { 37./255., 102./255., 157./255., 188./255., 196./255., 214./255., 223./255., 235./255., 251./255.};
            Double_t green[9] = { 37./255.,  29./255.,  25./255.,  37./255.,  67./255.,  91./255., 132./255., 185./255., 251./255.};
            Double_t blue[9]  = { 37./255.,  32./255.,  33./255.,  45./255.,  66./255.,  98./255., 137./255., 187./255., 251./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Coffee
      case 76:
         {
            Double_t red[9]   = { 79./255., 100./255., 119./255., 137./255., 153./255., 172./255., 192./255., 205./255., 250./255.};
            Double_t green[9] = { 63./255.,  79./255.,  93./255., 103./255., 115./255., 135./255., 167./255., 196./255., 250./255.};
            Double_t blue[9]  = { 51./255.,  59./255.,  66./255.,  61./255.,  62./255.,  70./255., 110./255., 160./255., 250./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Dark Rain Bow
      case 77:
         {
            Double_t red[9]   = {  43./255.,  44./255., 50./255.,  66./255., 125./255., 172./255., 178./255., 155./255., 157./255.};
            Double_t green[9] = {  63./255.,  63./255., 85./255., 101./255., 138./255., 163./255., 122./255.,  51./255.,  39./255.};
            Double_t blue[9]  = { 121./255., 101./255., 58./255.,  44./255.,  47./255.,  55./255.,  57./255.,  44./255.,  43./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Dark Terrain
      case 78:
         {
            Double_t red[9]   = {  0./255., 41./255., 62./255., 79./255., 90./255., 87./255., 99./255., 140./255., 228./255.};
            Double_t green[9] = {  0./255., 57./255., 81./255., 93./255., 85./255., 70./255., 71./255., 125./255., 228./255.};
            Double_t blue[9]  = { 95./255., 91./255., 91./255., 82./255., 60./255., 43./255., 44./255., 112./255., 228./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Fall
      case 79:
         {
            Double_t red[9]   = { 49./255., 59./255., 72./255., 88./255., 114./255., 141./255., 176./255., 205./255., 222./255.};
            Double_t green[9] = { 78./255., 72./255., 66./255., 57./255.,  59./255.,  75./255., 106./255., 142./255., 173./255.};
            Double_t blue[9]  = { 78./255., 55./255., 46./255., 40./255.,  39./255.,  39./255.,  40./255.,  41./255.,  47./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Fruit Punch
      case 80:
         {
            Double_t red[9]   = { 243./255., 222./255., 201./255., 185./255., 165./255., 158./255., 166./255., 187./255., 219./255.};
            Double_t green[9] = {  94./255., 108./255., 132./255., 135./255., 125./255.,  96./255.,  68./255.,  51./255.,  61./255.};
            Double_t blue[9]  = {   7./255.,  9./255.,   12./255.,  19./255.,  45./255.,  89./255., 118./255., 146./255., 118./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Fuchsia
      case 81:
         {
            Double_t red[9]   = { 19./255., 44./255., 74./255., 105./255., 137./255., 166./255., 194./255., 206./255., 220./255.};
            Double_t green[9] = { 19./255., 28./255., 40./255.,  55./255.,  82./255., 110./255., 159./255., 181./255., 220./255.};
            Double_t blue[9]  = { 19./255., 42./255., 68./255.,  96./255., 129./255., 157./255., 188./255., 203./255., 220./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Grey Yellow
      case 82:
         {
            Double_t red[9]   = { 33./255., 44./255., 70./255.,  99./255., 140./255., 165./255., 199./255., 211./255., 216./255.};
            Double_t green[9] = { 38./255., 50./255., 76./255., 105./255., 140./255., 165./255., 191./255., 189./255., 167./255.};
            Double_t blue[9]  = { 55./255., 67./255., 97./255., 124./255., 140./255., 166./255., 163./255., 129./255.,  52./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Green Brown Terrain
      case 83:
         {
            Double_t red[9]   = { 0./255., 33./255., 73./255., 124./255., 136./255., 152./255., 159./255., 171./255., 223./255.};
            Double_t green[9] = { 0./255., 43./255., 92./255., 124./255., 134./255., 126./255., 121./255., 144./255., 223./255.};
            Double_t blue[9]  = { 0./255., 43./255., 68./255.,  76./255.,  73./255.,  64./255.,  72./255., 114./255., 223./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Green Pink
      case 84:
         {
            Double_t red[9]   = {  5./255.,  18./255.,  45./255., 124./255., 193./255., 223./255., 205./255., 128./255., 49./255.};
            Double_t green[9] = { 48./255., 134./255., 207./255., 230./255., 193./255., 113./255.,  28./255.,   0./255.,  7./255.};
            Double_t blue[9]  = {  6./255.,  15./255.,  41./255., 121./255., 193./255., 226./255., 208./255., 130./255., 49./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Island
      case 85:
         {
            Double_t red[9]   = { 180./255., 106./255., 104./255., 135./255., 164./255., 188./255., 189./255., 165./255., 144./255.};
            Double_t green[9] = {  72./255., 126./255., 154./255., 184./255., 198./255., 207./255., 205./255., 190./255., 179./255.};
            Double_t blue[9]  = {  41./255., 120./255., 158./255., 188./255., 194./255., 181./255., 145./255., 100./255.,  62./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Lake
      case 86:
         {
            Double_t red[9]   = {  57./255.,  72./255.,  94./255., 117./255., 136./255., 154./255., 174./255., 192./255., 215./255.};
            Double_t green[9] = {   0./255.,  33./255.,  68./255., 109./255., 140./255., 171./255., 192./255., 196./255., 209./255.};
            Double_t blue[9]  = { 116./255., 137./255., 173./255., 201./255., 200./255., 201./255., 203./255., 190./255., 187./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Light Temperature
      case 87:
         {
            Double_t red[9]   = {  31./255.,  71./255., 123./255., 160./255., 210./255., 222./255., 214./255., 199./255., 183./255.};
            Double_t green[9] = {  40./255., 117./255., 171./255., 211./255., 231./255., 220./255., 190./255., 132./255.,  65./255.};
            Double_t blue[9]  = { 234./255., 214./255., 228./255., 222./255., 210./255., 160./255., 105./255.,  60./255.,  34./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Light Terrain
      case 88:
         {
            Double_t red[9]   = { 123./255., 108./255., 109./255., 126./255., 154./255., 172./255., 188./255., 196./255., 218./255.};
            Double_t green[9] = { 184./255., 138./255., 130./255., 133./255., 154./255., 175./255., 188./255., 196./255., 218./255.};
            Double_t blue[9]  = { 208./255., 130./255., 109./255.,  99./255., 110./255., 122./255., 150./255., 171./255., 218./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Mint
      case 89:
         {
            Double_t red[9]   = { 105./255., 106./255., 122./255., 143./255., 159./255., 172./255., 176./255., 181./255., 207./255.};
            Double_t green[9] = { 252./255., 197./255., 194./255., 187./255., 174./255., 162./255., 153./255., 136./255., 125./255.};
            Double_t blue[9]  = { 146./255., 133./255., 144./255., 155./255., 163./255., 167./255., 166./255., 162./255., 174./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Neon
      case 90:
         {
            Double_t red[9]   = { 171./255., 141./255., 145./255., 152./255., 154./255., 159./255., 163./255., 158./255., 177./255.};
            Double_t green[9] = { 236./255., 143./255., 100./255.,  63./255.,  53./255.,  55./255.,  44./255.,  31./255.,   6./255.};
            Double_t blue[9]  = {  59./255.,  48./255.,  46./255.,  44./255.,  42./255.,  54./255.,  82./255., 112./255., 179./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Pastel
      case 91:
         {
            Double_t red[9]   = { 180./255., 190./255., 209./255., 223./255., 204./255., 228./255., 205./255., 152./255.,  91./255.};
            Double_t green[9] = {  93./255., 125./255., 147./255., 172./255., 181./255., 224./255., 233./255., 198./255., 158./255.};
            Double_t blue[9]  = { 236./255., 218./255., 160./255., 133./255., 114./255., 132./255., 162./255., 220./255., 218./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Pearl
      case 92:
         {
            Double_t red[9]   = { 225./255., 183./255., 162./255., 135./255., 115./255., 111./255., 119./255., 145./255., 211./255.};
            Double_t green[9] = { 205./255., 177./255., 166./255., 135./255., 124./255., 117./255., 117./255., 132./255., 172./255.};
            Double_t blue[9]  = { 186./255., 165./255., 155./255., 135./255., 126./255., 130./255., 150./255., 178./255., 226./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Pigeon
      case 93:
         {
            Double_t red[9]   = { 39./255., 43./255., 59./255., 63./255., 80./255., 116./255., 153./255., 177./255., 223./255.};
            Double_t green[9] = { 39./255., 43./255., 59./255., 74./255., 91./255., 114./255., 139./255., 165./255., 223./255.};
            Double_t blue[9]  = { 39./255., 50./255., 59./255., 70./255., 85./255., 115./255., 151./255., 176./255., 223./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Plum
      case 94:
         {
            Double_t red[9]   = { 0./255., 38./255., 60./255., 76./255., 84./255., 89./255., 101./255., 128./255., 204./255.};
            Double_t green[9] = { 0./255., 10./255., 15./255., 23./255., 35./255., 57./255.,  83./255., 123./255., 199./255.};
            Double_t blue[9]  = { 0./255., 11./255., 22./255., 40./255., 63./255., 86./255.,  97./255.,  94./255.,  85./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Red Blue
      case 95:
         {
            Double_t red[9]   = { 94./255., 112./255., 141./255., 165./255., 167./255., 140./255.,  91./255.,  49./255.,  27./255.};
            Double_t green[9] = { 27./255.,  46./255.,  88./255., 135./255., 166./255., 161./255., 135./255.,  97./255.,  58./255.};
            Double_t blue[9]  = { 42./255.,  52./255.,  81./255., 106./255., 139./255., 158./255., 155./255., 137./255., 116./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Rose
      case 96:
         {
            Double_t red[9]   = { 30./255., 49./255., 79./255., 117./255., 135./255., 151./255., 146./255., 138./255., 147./255.};
            Double_t green[9] = { 63./255., 60./255., 72./255.,  90./255.,  94./255.,  94./255.,  68./255.,  46./255.,  16./255.};
            Double_t blue[9]  = { 18./255., 28./255., 41./255.,  56./255.,  62./255.,  63./255.,  50./255.,  36./255.,  21./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Rust
      case 97:
         {
            Double_t red[9]   = {  0./255., 30./255., 63./255., 101./255., 143./255., 152./255., 169./255., 187./255., 230./255.};
            Double_t green[9] = {  0./255., 14./255., 28./255.,  42./255.,  58./255.,  61./255.,  67./255.,  74./255.,  91./255.};
            Double_t blue[9]  = { 39./255., 26./255., 21./255.,  18./255.,  15./255.,  14./255.,  14./255.,  13./255.,  13./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Sandy Terrain
      case 98:
         {
            Double_t red[9]   = { 149./255., 140./255., 164./255., 179./255., 182./255., 181./255., 131./255., 87./255., 61./255.};
            Double_t green[9] = {  62./255.,  70./255., 107./255., 136./255., 144./255., 138./255., 117./255., 87./255., 74./255.};
            Double_t blue[9]  = {  40./255.,  38./255.,  45./255.,  49./255.,  49./255.,  49./255.,  38./255., 32./255., 34./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Sienna
      case 99:
         {
            Double_t red[9]   = { 99./255., 112./255., 148./255., 165./255., 179./255., 182./255., 183./255., 183./255., 208./255.};
            Double_t green[9] = { 39./255.,  40./255.,  57./255.,  79./255., 104./255., 127./255., 148./255., 161./255., 198./255.};
            Double_t blue[9]  = { 15./255.,  16./255.,  18./255.,  33./255.,  51./255.,  79./255., 103./255., 129./255., 177./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Solar
      case 100:
         {
            Double_t red[9]   = { 99./255., 116./255., 154./255., 174./255., 200./255., 196./255., 201./255., 201./255., 230./255.};
            Double_t green[9] = {  0./255.,   0./255.,   8./255.,  32./255.,  58./255.,  83./255., 119./255., 136./255., 173./255.};
            Double_t blue[9]  = {  5./255.,   6./255.,   7./255.,   9./255.,   9./255.,  14./255.,  17./255.,  19./255.,  24./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // South West
      case 101:
         {
            Double_t red[9]   = { 82./255., 106./255., 126./255., 141./255., 155./255., 163./255., 142./255., 107./255.,  66./255.};
            Double_t green[9] = { 62./255.,  44./255.,  69./255., 107./255., 135./255., 152./255., 149./255., 132./255., 119./255.};
            Double_t blue[9]  = { 39./255.,  25./255.,  31./255.,  60./255.,  73./255.,  68./255.,  49./255.,  72./255., 188./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Starry Night
      case 102:
         {
            Double_t red[9]   = { 18./255., 29./255., 44./255.,  72./255., 116./255., 158./255., 184./255., 208./255., 221./255.};
            Double_t green[9] = { 27./255., 46./255., 71./255., 105./255., 146./255., 177./255., 189./255., 190./255., 183./255.};
            Double_t blue[9]  = { 39./255., 55./255., 80./255., 108./255., 130./255., 133./255., 124./255., 100./255.,  76./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Sunset
      case 103:
         {
            Double_t red[9]   = { 0./255., 48./255., 119./255., 173./255., 212./255., 224./255., 228./255., 228./255., 245./255.};
            Double_t green[9] = { 0./255., 13./255.,  30./255.,  47./255.,  79./255., 127./255., 167./255., 205./255., 245./255.};
            Double_t blue[9]  = { 0./255., 68./255.,  75./255.,  43./255.,  16./255.,  22./255.,  55./255., 128./255., 245./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Temperature Map
      case 104:
         {
            Double_t red[9]   = {  34./255.,  70./255., 129./255., 187./255., 225./255., 226./255., 216./255., 193./255., 179./255.};
            Double_t green[9] = {  48./255.,  91./255., 147./255., 194./255., 226./255., 229./255., 196./255., 110./255.,  12./255.};
            Double_t blue[9]  = { 234./255., 212./255., 216./255., 224./255., 206./255., 110./255.,  53./255.,  40./255.,  29./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Thermometer
      case 105:
         {
            Double_t red[9]   = {  30./255.,  55./255., 103./255., 147./255., 174./255., 203./255., 188./255., 151./255., 105./255.};
            Double_t green[9] = {   0./255.,  65./255., 138./255., 182./255., 187./255., 175./255., 121./255.,  53./255.,   9./255.};
            Double_t blue[9]  = { 191./255., 202./255., 212./255., 208./255., 171./255., 140./255.,  97./255.,  57./255.,  30./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Valentine
      case 106:
         {
            Double_t red[9]   = { 112./255., 97./255., 113./255., 125./255., 138./255., 159./255., 178./255., 188./255., 225./255.};
            Double_t green[9] = {  16./255., 17./255.,  24./255.,  37./255.,  56./255.,  81./255., 110./255., 136./255., 189./255.};
            Double_t blue[9]  = {  38./255., 35./255.,  46./255.,  59./255.,  78./255., 103./255., 130./255., 152./255., 201./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Visible Spectrum
      case 107:
         {
            Double_t red[9]   = { 18./255.,  72./255.,   5./255.,  23./255.,  29./255., 201./255., 200./255., 98./255., 29./255.};
            Double_t green[9] = {  0./255.,   0./255.,  43./255., 167./255., 211./255., 117./255.,   0./255.,  0./255.,  0./255.};
            Double_t blue[9]  = { 51./255., 203./255., 177./255.,  26./255.,  10./255.,   9./255.,   8./255.,  3./255.,  0./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Water Melon
      case 108:
         {
            Double_t red[9]   = { 19./255., 42./255., 64./255.,  88./255., 118./255., 147./255., 175./255., 187./255., 205./255.};
            Double_t green[9] = { 19./255., 55./255., 89./255., 125./255., 154./255., 169./255., 161./255., 129./255.,  70./255.};
            Double_t blue[9]  = { 19./255., 32./255., 47./255.,  70./255., 100./255., 128./255., 145./255., 130./255.,  75./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Cool
      case 109:
         {
            Double_t red[9]   = {  33./255.,  31./255.,  42./255.,  68./255.,  86./255., 111./255., 141./255., 172./255., 227./255.};
            Double_t green[9] = { 255./255., 175./255., 145./255., 106./255.,  88./255.,  55./255.,  15./255.,   0./255.,   0./255.};
            Double_t blue[9]  = { 255./255., 205./255., 202./255., 203./255., 208./255., 205./255., 203./255., 206./255., 231./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Copper
      case 110:
         {
            Double_t red[9]   = { 0./255., 25./255., 50./255., 79./255., 110./255., 145./255., 181./255., 201./255., 254./255.};
            Double_t green[9] = { 0./255., 16./255., 30./255., 46./255.,  63./255.,  82./255., 101./255., 124./255., 179./255.};
            Double_t blue[9]  = { 0./255., 12./255., 21./255., 29./255.,  39./255.,  49./255.,  61./255.,  74./255., 103./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Gist Earth
      case 111:
         {
            Double_t red[9]   = { 0./255., 13./255.,  30./255.,  44./255.,  72./255., 120./255., 156./255., 200./255., 247./255.};
            Double_t green[9] = { 0./255., 36./255.,  84./255., 117./255., 141./255., 153./255., 151./255., 158./255., 247./255.};
            Double_t blue[9]  = { 0./255., 94./255., 100./255.,  82./255.,  56./255.,  66./255.,  76./255., 131./255., 247./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      // Viridis
      case 112:
         {
            Double_t red[9]   = { 26./255., 51./255.,  43./255.,  33./255.,  28./255.,  35./255.,  74./255., 144./255., 246./255.};
            Double_t green[9] = {  9./255., 24./255.,  55./255.,  87./255., 118./255., 150./255., 180./255., 200./255., 222./255.};
            Double_t blue[9]  = { 30./255., 96./255., 112./255., 114./255., 112./255., 101./255.,  72./255.,  35./255.,   0./255.};
            Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, alpha);
         }
         break;

      default:
         cout << Form("SetPalette, Unknown palette number %d", ncolors) << endl;
         return;
      }
      paletteType = ncolors;
      if (Idx>0) fgPalettesList.fArray[paletteType-51] = (Double_t)Idx;
      else       fgPalettesList.fArray[paletteType-51] = 0.;
      if (alpha > 0.) fgPalettesList.fArray[paletteType-51] += alpha/10.;
      return;
   }

   // set user defined palette
   if (colors)  {
      fgPalette.Set(ncolors);
      for (i=0;i<ncolors;i++) fgPalette.fArray[i] = colors[i];
   } else {
      fgPalette.Set(TMath::Min(50,ncolors));
      for (i=0;i<TMath::Min(50,ncolors);i++) fgPalette.fArray[i] = palette[i];
   }
   paletteType = 3;
}

#endif
