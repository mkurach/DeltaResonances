{
//=========Macro generated from canvas: can_tb_rap_all4_irc/can_tb_rap_all4_irc
//=========  (Tue Sep 13 17:07:06 2022) by ROOT version5.34/34
   TCanvas *can_tb_rap_all4_irc = new TCanvas("can_tb_rap_all4_irc", "can_tb_rap_all4_irc",0,0,600,500);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   can_tb_rap_all4_irc->ToggleEventStatus();
   can_tb_rap_all4_irc->Range(0,0,1,1);
   can_tb_rap_all4_irc->SetFillColor(0);
   can_tb_rap_all4_irc->SetBorderMode(0);
   can_tb_rap_all4_irc->SetBorderSize(0);
   can_tb_rap_all4_irc->SetTickx(1);
   can_tb_rap_all4_irc->SetTicky(1);
   can_tb_rap_all4_irc->SetLeftMargin(0.15);
   can_tb_rap_all4_irc->SetRightMargin(0.05);
   can_tb_rap_all4_irc->SetTopMargin(0.05);
   can_tb_rap_all4_irc->SetBottomMargin(0.165);
   can_tb_rap_all4_irc->SetFrameLineWidth(2);
   can_tb_rap_all4_irc->SetFrameBorderMode(0);
   can_tb_rap_all4_irc->SetFrameBorderSize(0);
   Double_t xAxis54[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *h_rap_temp_all_irc = new TH1D("h_rap_temp_all_irc","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis54);
   h_rap_temp_all_irc->SetMinimum(0.04);
   h_rap_temp_all_irc->SetMaximum(0.16);
   h_rap_temp_all_irc->SetStats(0);
   h_rap_temp_all_irc->SetFillStyle(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000082");
   h_rap_temp_all_irc->SetLineColor(ci);
   h_rap_temp_all_irc->SetLineWidth(2);

   ci = TColor::GetColor("#000082");
   h_rap_temp_all_irc->SetMarkerColor(ci);
   h_rap_temp_all_irc->SetMarkerStyle(20);
   h_rap_temp_all_irc->SetMarkerSize(1.4);
   h_rap_temp_all_irc->GetXaxis()->SetTitle("Rapidity");
   h_rap_temp_all_irc->GetXaxis()->SetRange(0,11);
   h_rap_temp_all_irc->GetXaxis()->SetNdivisions(505);
   h_rap_temp_all_irc->GetXaxis()->SetLabelFont(42);
   h_rap_temp_all_irc->GetXaxis()->SetLabelOffset(0.01);
   h_rap_temp_all_irc->GetXaxis()->SetLabelSize(0.05);
   h_rap_temp_all_irc->GetXaxis()->SetTitleSize(0.05);
   h_rap_temp_all_irc->GetXaxis()->SetTitleOffset(1.48);
   h_rap_temp_all_irc->GetXaxis()->SetTitleFont(42);
   h_rap_temp_all_irc->GetYaxis()->SetTitle("T_{eff} (GeV)");
   h_rap_temp_all_irc->GetYaxis()->SetNdivisions(505);
   h_rap_temp_all_irc->GetYaxis()->SetLabelFont(42);
   h_rap_temp_all_irc->GetYaxis()->SetLabelSize(0.05);
   h_rap_temp_all_irc->GetYaxis()->SetTitleSize(0.05);
   h_rap_temp_all_irc->GetYaxis()->SetTitleOffset(1.58);
   h_rap_temp_all_irc->GetYaxis()->SetTitleFont(42);
   h_rap_temp_all_irc->GetZaxis()->SetLabelFont(42);
   h_rap_temp_all_irc->GetZaxis()->SetLabelSize(0.035);
   h_rap_temp_all_irc->GetZaxis()->SetTitleSize(0.035);
   h_rap_temp_all_irc->GetZaxis()->SetTitleFont(42);
   h_rap_temp_all_irc->Draw("");
// moje rzeczy


   Double_t Graph0_fx1001[10] = {
   0.07,
   0.24,
   0.415,
   0.565,
   0.69,
   0.79,
   0.915,
   1.065,
   1.24,
   1.57};
   Double_t Graph0_fy1001[10] = {
   0.1014261,
   0.1178362,
   0.1268921,
   0.1317536,
   0.134034,
   0.1336915,
   0.131913,
   0.1266524,
   0.1178649,
   0.1021248};
   Double_t Graph0_fex1001[10] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1001[10] = {
   0.0001534449,
   0.0001588331,
   0.0001698962,
   0.0001639299,
   0.000201755,
   0.0001988446,
   0.0001642465,
   0.0001689684,
   0.0001587876,
   0.0001565801};
   TGraphErrors *gre = new TGraphErrors(10,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   
   TH1F *Graph_Graph1001 = new TH1F("Graph_Graph1001","Graph",100,0,1.72);
   Graph_Graph1001->SetMinimum(0.05);
   Graph_Graph1001->SetMaximum(0.15);
   Graph_Graph1001->SetDirectory(0);
   Graph_Graph1001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1001->SetLineColor(ci);
   Graph_Graph1001->GetXaxis()->SetTitle("Rapidity");
   Graph_Graph1001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetXaxis()->SetTitleFont(42);
   Graph_Graph1001->GetYaxis()->SetTitle("T_{eff} (GeV)");
   Graph_Graph1001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetYaxis()->SetTitleOffset(0);
   Graph_Graph1001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1001);

// ------------>Primitives in pad: t0
   TPad *t0 = new TPad("t0", "t0",0.06,0.76,0.97,0.97);
   t0->Draw();
   t0->cd();
   t0->Range(0,0,1,1);
   t0->SetFillColor(0);
   t0->SetBorderMode(0);
   t0->SetBorderSize(0);
   t0->SetTickx(1);
   t0->SetTicky(1);
   t0->SetRightMargin(0);
   t0->SetTopMargin(0);
   t0->SetBottomMargin(0);
   t0->SetFrameLineWidth(2);
   t0->SetFrameBorderMode(0);
   t0->SetFrameBorderSize(0);
   Double_t xAxis55[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *can_tb_rap_err_irc_mult0 = new TH1D("can_tb_rap_err_irc_mult0","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis55);
   can_tb_rap_err_irc_mult0->SetBinContent(1,0.1073549);
   can_tb_rap_err_irc_mult0->SetBinContent(2,0.1132524);
   can_tb_rap_err_irc_mult0->SetBinContent(3,0.1256401);
   can_tb_rap_err_irc_mult0->SetBinContent(4,0.1365404);
   can_tb_rap_err_irc_mult0->SetBinContent(5,0.1437346);
   can_tb_rap_err_irc_mult0->SetBinContent(6,0.1500039);
   can_tb_rap_err_irc_mult0->SetBinContent(7,0.1453654);
   can_tb_rap_err_irc_mult0->SetBinContent(8,0.1242513);
   can_tb_rap_err_irc_mult0->SetBinContent(9,0.1062985);
   can_tb_rap_err_irc_mult0->SetBinContent(10,0.0896508);
   can_tb_rap_err_irc_mult0->SetBinError(1,0.01558795);
   can_tb_rap_err_irc_mult0->SetBinError(2,0.01643531);
   can_tb_rap_err_irc_mult0->SetBinError(3,0.008898475);
   can_tb_rap_err_irc_mult0->SetBinError(4,0.0075);
   can_tb_rap_err_irc_mult0->SetBinError(5,0.0075);
   can_tb_rap_err_irc_mult0->SetBinError(6,0.0075);
   can_tb_rap_err_irc_mult0->SetBinError(7,0.0215442);
   can_tb_rap_err_irc_mult0->SetBinError(8,0.02569151);
   can_tb_rap_err_irc_mult0->SetBinError(9,0.01444621);
   can_tb_rap_err_irc_mult0->SetBinError(10,0.01535787);
   can_tb_rap_err_irc_mult0->SetMinimum(0.035);
   can_tb_rap_err_irc_mult0->SetMaximum(0.18);
   can_tb_rap_err_irc_mult0->SetEntries(30);
   can_tb_rap_err_irc_mult0->SetStats(0);
   can_tb_rap_err_irc_mult0->SetFillStyle(0);

   ci = TColor::GetColor("#000082");
   can_tb_rap_err_irc_mult0->SetLineColor(ci);
   can_tb_rap_err_irc_mult0->SetLineWidth(2);

   ci = TColor::GetColor("#000082");
   can_tb_rap_err_irc_mult0->SetMarkerColor(ci);
   can_tb_rap_err_irc_mult0->SetMarkerStyle(20);
   can_tb_rap_err_irc_mult0->SetMarkerSize(1.4);
   can_tb_rap_err_irc_mult0->GetXaxis()->SetTitle("Rapidity");
   can_tb_rap_err_irc_mult0->GetXaxis()->SetRange(0,11);
   can_tb_rap_err_irc_mult0->GetXaxis()->SetNdivisions(505);
   can_tb_rap_err_irc_mult0->GetXaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult0->GetXaxis()->SetLabelOffset(0.01);
   can_tb_rap_err_irc_mult0->GetXaxis()->SetLabelSize(0.19);
   can_tb_rap_err_irc_mult0->GetXaxis()->SetTitleSize(0.06);
   can_tb_rap_err_irc_mult0->GetXaxis()->SetTickLength(0.1);
   can_tb_rap_err_irc_mult0->GetXaxis()->SetTitleOffset(16);
   can_tb_rap_err_irc_mult0->GetXaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult0->GetYaxis()->SetTitle("T_{eff} (GeV)");
   can_tb_rap_err_irc_mult0->GetYaxis()->SetNdivisions(505);
   can_tb_rap_err_irc_mult0->GetYaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult0->GetYaxis()->SetLabelSize(0.19);
   can_tb_rap_err_irc_mult0->GetYaxis()->SetTitleSize(0.06);
   can_tb_rap_err_irc_mult0->GetYaxis()->SetTickLength(0.035);
   can_tb_rap_err_irc_mult0->GetYaxis()->SetTitleOffset(16);
   can_tb_rap_err_irc_mult0->GetYaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult0->GetZaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult0->GetZaxis()->SetLabelSize(0.035);
   can_tb_rap_err_irc_mult0->GetZaxis()->SetTitleSize(0.035);
   can_tb_rap_err_irc_mult0->GetZaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult0->Draw("E2");
   Double_t xAxis56[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *can_tb_rap_irc_mult0 = new TH1D("can_tb_rap_irc_mult0","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis56);
   can_tb_rap_irc_mult0->SetBinContent(1,0.1073549);
   can_tb_rap_irc_mult0->SetBinContent(2,0.1132524);
   can_tb_rap_irc_mult0->SetBinContent(3,0.1256401);
   can_tb_rap_irc_mult0->SetBinContent(4,0.1365404);
   can_tb_rap_irc_mult0->SetBinContent(5,0.1437346);
   can_tb_rap_irc_mult0->SetBinContent(6,0.1500039);
   can_tb_rap_irc_mult0->SetBinContent(7,0.1453654);
   can_tb_rap_irc_mult0->SetBinContent(8,0.1242513);
   can_tb_rap_irc_mult0->SetBinContent(9,0.1062985);
   can_tb_rap_irc_mult0->SetBinContent(10,0.0896508);
   can_tb_rap_irc_mult0->SetBinError(1,0.006851972);
   can_tb_rap_irc_mult0->SetBinError(2,0.00554295);
   can_tb_rap_irc_mult0->SetBinError(3,0.006194904);
   can_tb_rap_irc_mult0->SetBinError(4,0.006338105);
   can_tb_rap_irc_mult0->SetBinError(5,0.007130076);
   can_tb_rap_irc_mult0->SetBinError(6,0.008457514);
   can_tb_rap_irc_mult0->SetBinError(7,0.009219397);
   can_tb_rap_irc_mult0->SetBinError(8,0.007657557);
   can_tb_rap_irc_mult0->SetBinError(9,0.01036459);
   can_tb_rap_irc_mult0->SetBinError(10,0.009780112);
   can_tb_rap_irc_mult0->SetMinimum(0);
   can_tb_rap_irc_mult0->SetMaximum(0.2);
   can_tb_rap_irc_mult0->SetEntries(10);
   can_tb_rap_irc_mult0->SetStats(0);
   can_tb_rap_irc_mult0->SetFillStyle(0);

   ci = TColor::GetColor("#000082");
   can_tb_rap_irc_mult0->SetLineColor(ci);
   can_tb_rap_irc_mult0->SetLineWidth(2);

   ci = TColor::GetColor("#000082");
   can_tb_rap_irc_mult0->SetMarkerColor(ci);
   can_tb_rap_irc_mult0->SetMarkerStyle(20);
   can_tb_rap_irc_mult0->SetMarkerSize(1.4);
   can_tb_rap_irc_mult0->GetXaxis()->SetTitle("Rapidity");
   can_tb_rap_irc_mult0->GetXaxis()->SetRange(0,11);
   can_tb_rap_irc_mult0->GetXaxis()->SetNdivisions(505);
   can_tb_rap_irc_mult0->GetXaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult0->GetXaxis()->SetLabelOffset(0.01);
   can_tb_rap_irc_mult0->GetXaxis()->SetLabelSize(0.05);
   can_tb_rap_irc_mult0->GetXaxis()->SetTitleSize(0.06);
   can_tb_rap_irc_mult0->GetXaxis()->SetTitleOffset(1.14);
   can_tb_rap_irc_mult0->GetXaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult0->GetYaxis()->SetTitle("T_{eff} (GeV)");
   can_tb_rap_irc_mult0->GetYaxis()->SetNdivisions(505);
   can_tb_rap_irc_mult0->GetYaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult0->GetYaxis()->SetLabelSize(0.05);
   can_tb_rap_irc_mult0->GetYaxis()->SetTitleSize(0.06);
   can_tb_rap_irc_mult0->GetYaxis()->SetTitleOffset(1.14);
   can_tb_rap_irc_mult0->GetYaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult0->GetZaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult0->GetZaxis()->SetLabelSize(0.035);
   can_tb_rap_irc_mult0->GetZaxis()->SetTitleSize(0.035);
   can_tb_rap_irc_mult0->GetZaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult0->Draw("samehistP");
   Double_t xAxis57[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *h_tb_rap_circle_mult0__53 = new TH1D("h_tb_rap_circle_mult0__53","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis57);
   h_tb_rap_circle_mult0__53->SetBinContent(1,0.1073549);
   h_tb_rap_circle_mult0__53->SetBinContent(2,0.1132524);
   h_tb_rap_circle_mult0__53->SetBinContent(3,0.1256401);
   h_tb_rap_circle_mult0__53->SetBinContent(4,0.1365404);
   h_tb_rap_circle_mult0__53->SetBinContent(5,0.1437346);
   h_tb_rap_circle_mult0__53->SetBinContent(6,0.1500039);
   h_tb_rap_circle_mult0__53->SetBinContent(7,0.1453654);
   h_tb_rap_circle_mult0__53->SetBinContent(8,0.1242513);
   h_tb_rap_circle_mult0__53->SetBinContent(9,0.1062985);
   h_tb_rap_circle_mult0__53->SetBinContent(10,0.0896508);
   h_tb_rap_circle_mult0__53->SetBinError(1,0.006851972);
   h_tb_rap_circle_mult0__53->SetBinError(2,0.00554295);
   h_tb_rap_circle_mult0__53->SetBinError(3,0.006194904);
   h_tb_rap_circle_mult0__53->SetBinError(4,0.006338105);
   h_tb_rap_circle_mult0__53->SetBinError(5,0.007130076);
   h_tb_rap_circle_mult0__53->SetBinError(6,0.008457514);
   h_tb_rap_circle_mult0__53->SetBinError(7,0.009219397);
   h_tb_rap_circle_mult0__53->SetBinError(8,0.007657557);
   h_tb_rap_circle_mult0__53->SetBinError(9,0.01036459);
   h_tb_rap_circle_mult0__53->SetBinError(10,0.009780112);
   h_tb_rap_circle_mult0__53->SetMinimum(0);
   h_tb_rap_circle_mult0__53->SetMaximum(0.2);
   h_tb_rap_circle_mult0__53->SetEntries(10);
   h_tb_rap_circle_mult0__53->SetDirectory(0);
   h_tb_rap_circle_mult0__53->SetStats(0);
   h_tb_rap_circle_mult0__53->SetFillStyle(0);

   ci = TColor::GetColor("#666666");
   h_tb_rap_circle_mult0__53->SetLineColor(ci);
   h_tb_rap_circle_mult0__53->SetLineWidth(2);
   h_tb_rap_circle_mult0__53->SetMarkerStyle(4);
   h_tb_rap_circle_mult0__53->SetMarkerSize(1.4);
   h_tb_rap_circle_mult0__53->GetXaxis()->SetTitle("Rapidity");
   h_tb_rap_circle_mult0__53->GetXaxis()->SetRange(0,11);
   h_tb_rap_circle_mult0__53->GetXaxis()->SetNdivisions(505);
   h_tb_rap_circle_mult0__53->GetXaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult0__53->GetXaxis()->SetLabelOffset(0.01);
   h_tb_rap_circle_mult0__53->GetXaxis()->SetLabelSize(0.05);
   h_tb_rap_circle_mult0__53->GetXaxis()->SetTitleSize(0.06);
   h_tb_rap_circle_mult0__53->GetXaxis()->SetTitleOffset(1.14);
   h_tb_rap_circle_mult0__53->GetXaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult0__53->GetYaxis()->SetTitle("T_{eff} (GeV)");
   h_tb_rap_circle_mult0__53->GetYaxis()->SetNdivisions(505);
   h_tb_rap_circle_mult0__53->GetYaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult0__53->GetYaxis()->SetLabelSize(0.05);
   h_tb_rap_circle_mult0__53->GetYaxis()->SetTitleSize(0.06);
   h_tb_rap_circle_mult0__53->GetYaxis()->SetTitleOffset(1.14);
   h_tb_rap_circle_mult0__53->GetYaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult0__53->GetZaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult0__53->GetZaxis()->SetLabelSize(0.035);
   h_tb_rap_circle_mult0__53->GetZaxis()->SetTitleSize(0.035);
   h_tb_rap_circle_mult0__53->GetZaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult0__53->Draw("samehistP");

 // gre->Draw("ap same");
   TLine *line = new TLine(0.742432,0.035,0.742432,0.18);
   line->SetLineStyle(9);
   line->Draw();
   
   TPaveText *pt = new TPaveText(-2.353437e-185,-2.353437e-185,-2.353437e-185,-2.353437e-185,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillStyle(0);
   pt->SetLineWidth(0);
   pt->SetTextFont(42);
   text = pt->AddText("#scale[1.2]{HADES} Au+Au");
   text->SetTextAlign(12);
   text = pt->AddText("#sqrt{s_{NN}}=2.42 GeV");
   text->SetTextAlign(12);
   text = pt->AddText("");
   text->SetTextAlign(12);
   pt->Draw();
   text = new TText(0.135,0.77,"0-10%");
   text->SetNDC();
   text->SetTextFont(42);
   text->SetTextSize(0.19);
   text->Draw();
   t0->Modified();
   can_tb_rap_all4_irc->cd();
  
// ------------>Primitives in pad: t1
   /*TPad *t1 = new TPad("t1", "t1",0.06,0.55,0.97,0.76);
   t1->Draw();
   t1->cd();
   t1->Range(0,0,1,1);
   t1->SetFillColor(0);
   t1->SetBorderMode(0);
   t1->SetBorderSize(0);
   t1->SetTickx(1);
   t1->SetTicky(1);
   t1->SetRightMargin(0);
   t1->SetTopMargin(0);
   t1->SetBottomMargin(0);
   t1->SetFrameLineWidth(2);
   t1->SetFrameBorderMode(0);
   t1->SetFrameBorderSize(0);
   Double_t xAxis58[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *can_tb_rap_err_irc_mult1 = new TH1D("can_tb_rap_err_irc_mult1","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis58);
   can_tb_rap_err_irc_mult1->SetBinContent(1,0.08927922);
   can_tb_rap_err_irc_mult1->SetBinContent(2,0.09794216);
   can_tb_rap_err_irc_mult1->SetBinContent(3,0.1101586);
   can_tb_rap_err_irc_mult1->SetBinContent(4,0.1280933);
   can_tb_rap_err_irc_mult1->SetBinContent(5,0.1340747);
   can_tb_rap_err_irc_mult1->SetBinContent(6,0.1377316);
   can_tb_rap_err_irc_mult1->SetBinContent(7,0.1273912);
   can_tb_rap_err_irc_mult1->SetBinContent(8,0.1069121);
   can_tb_rap_err_irc_mult1->SetBinContent(9,0.08806996);
   can_tb_rap_err_irc_mult1->SetBinContent(10,0.07606905);
   can_tb_rap_err_irc_mult1->SetBinError(1,0.02447625);
   can_tb_rap_err_irc_mult1->SetBinError(2,0.009756642);
   can_tb_rap_err_irc_mult1->SetBinError(3,0.01781586);
   can_tb_rap_err_irc_mult1->SetBinError(4,0.01719597);
   can_tb_rap_err_irc_mult1->SetBinError(5,0.01840559);
   can_tb_rap_err_irc_mult1->SetBinError(6,0.007962589);
   can_tb_rap_err_irc_mult1->SetBinError(7,0.01107584);
   can_tb_rap_err_irc_mult1->SetBinError(8,0.01573182);
   can_tb_rap_err_irc_mult1->SetBinError(9,0.00898904);
   can_tb_rap_err_irc_mult1->SetBinError(10,0.0075);
   can_tb_rap_err_irc_mult1->SetMinimum(0.035);
   can_tb_rap_err_irc_mult1->SetMaximum(0.18);
   can_tb_rap_err_irc_mult1->SetEntries(30);
   can_tb_rap_err_irc_mult1->SetStats(0);
   can_tb_rap_err_irc_mult1->SetFillStyle(0);

   ci = TColor::GetColor("#0097dd");
   can_tb_rap_err_irc_mult1->SetLineColor(ci);
   can_tb_rap_err_irc_mult1->SetLineWidth(2);

   ci = TColor::GetColor("#0097dd");
   can_tb_rap_err_irc_mult1->SetMarkerColor(ci);
   can_tb_rap_err_irc_mult1->SetMarkerStyle(20);
   can_tb_rap_err_irc_mult1->SetMarkerSize(1.4);
   can_tb_rap_err_irc_mult1->GetXaxis()->SetTitle("Rapidity");
   can_tb_rap_err_irc_mult1->GetXaxis()->SetRange(0,11);
   can_tb_rap_err_irc_mult1->GetXaxis()->SetNdivisions(505);
   can_tb_rap_err_irc_mult1->GetXaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult1->GetXaxis()->SetLabelOffset(0.01);
   can_tb_rap_err_irc_mult1->GetXaxis()->SetLabelSize(0.19);
   can_tb_rap_err_irc_mult1->GetXaxis()->SetTitleSize(0.06);
   can_tb_rap_err_irc_mult1->GetXaxis()->SetTickLength(0.1);
   can_tb_rap_err_irc_mult1->GetXaxis()->SetTitleOffset(16);
   can_tb_rap_err_irc_mult1->GetXaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult1->GetYaxis()->SetTitle("T_{eff} (GeV)");
   can_tb_rap_err_irc_mult1->GetYaxis()->SetNdivisions(505);
   can_tb_rap_err_irc_mult1->GetYaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult1->GetYaxis()->SetLabelSize(0.19);
   can_tb_rap_err_irc_mult1->GetYaxis()->SetTitleSize(0.06);
   can_tb_rap_err_irc_mult1->GetYaxis()->SetTickLength(0.035);
   can_tb_rap_err_irc_mult1->GetYaxis()->SetTitleOffset(16);
   can_tb_rap_err_irc_mult1->GetYaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult1->GetZaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult1->GetZaxis()->SetLabelSize(0.035);
   can_tb_rap_err_irc_mult1->GetZaxis()->SetTitleSize(0.035);
   can_tb_rap_err_irc_mult1->GetZaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult1->Draw("E2");
   Double_t xAxis59[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *can_tb_rap_irc_mult1 = new TH1D("can_tb_rap_irc_mult1","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis59);
   can_tb_rap_irc_mult1->SetBinContent(1,0.08927922);
   can_tb_rap_irc_mult1->SetBinContent(2,0.09794216);
   can_tb_rap_irc_mult1->SetBinContent(3,0.1101586);
   can_tb_rap_irc_mult1->SetBinContent(4,0.1280933);
   can_tb_rap_irc_mult1->SetBinContent(5,0.1340747);
   can_tb_rap_irc_mult1->SetBinContent(6,0.1377316);
   can_tb_rap_irc_mult1->SetBinContent(7,0.1273912);
   can_tb_rap_irc_mult1->SetBinContent(8,0.1069121);
   can_tb_rap_irc_mult1->SetBinContent(9,0.08806996);
   can_tb_rap_irc_mult1->SetBinContent(10,0.07606905);
   can_tb_rap_irc_mult1->SetBinError(1,0.004473326);
   can_tb_rap_irc_mult1->SetBinError(2,0.004208386);
   can_tb_rap_irc_mult1->SetBinError(3,0.004812753);
   can_tb_rap_irc_mult1->SetBinError(4,0.005810815);
   can_tb_rap_irc_mult1->SetBinError(5,0.006613146);
   can_tb_rap_irc_mult1->SetBinError(6,0.007052334);
   can_tb_rap_irc_mult1->SetBinError(7,0.006502487);
   can_tb_rap_irc_mult1->SetBinError(8,0.005555167);
   can_tb_rap_irc_mult1->SetBinError(9,0.008836213);
   can_tb_rap_irc_mult1->SetBinError(10,0.006274408);
   can_tb_rap_irc_mult1->SetMinimum(0);
   can_tb_rap_irc_mult1->SetMaximum(0.2);
   can_tb_rap_irc_mult1->SetEntries(10);
   can_tb_rap_irc_mult1->SetStats(0);
   can_tb_rap_irc_mult1->SetFillStyle(0);

   ci = TColor::GetColor("#0097dd");
   can_tb_rap_irc_mult1->SetLineColor(ci);
   can_tb_rap_irc_mult1->SetLineWidth(2);

   ci = TColor::GetColor("#0097dd");
   can_tb_rap_irc_mult1->SetMarkerColor(ci);
   can_tb_rap_irc_mult1->SetMarkerStyle(20);
   can_tb_rap_irc_mult1->SetMarkerSize(1.4);
   can_tb_rap_irc_mult1->GetXaxis()->SetTitle("Rapidity");
   can_tb_rap_irc_mult1->GetXaxis()->SetRange(0,11);
   can_tb_rap_irc_mult1->GetXaxis()->SetNdivisions(505);
   can_tb_rap_irc_mult1->GetXaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult1->GetXaxis()->SetLabelOffset(0.01);
   can_tb_rap_irc_mult1->GetXaxis()->SetLabelSize(0.05);
   can_tb_rap_irc_mult1->GetXaxis()->SetTitleSize(0.06);
   can_tb_rap_irc_mult1->GetXaxis()->SetTitleOffset(1.14);
   can_tb_rap_irc_mult1->GetXaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult1->GetYaxis()->SetTitle("T_{eff} (GeV)");
   can_tb_rap_irc_mult1->GetYaxis()->SetNdivisions(505);
   can_tb_rap_irc_mult1->GetYaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult1->GetYaxis()->SetLabelSize(0.05);
   can_tb_rap_irc_mult1->GetYaxis()->SetTitleSize(0.06);
   can_tb_rap_irc_mult1->GetYaxis()->SetTitleOffset(1.14);
   can_tb_rap_irc_mult1->GetYaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult1->GetZaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult1->GetZaxis()->SetLabelSize(0.035);
   can_tb_rap_irc_mult1->GetZaxis()->SetTitleSize(0.035);
   can_tb_rap_irc_mult1->GetZaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult1->Draw("samehistP");
   Double_t xAxis60[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *h_tb_rap_circle_mult1__54 = new TH1D("h_tb_rap_circle_mult1__54","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis60);
   h_tb_rap_circle_mult1__54->SetBinContent(1,0.08927922);
   h_tb_rap_circle_mult1__54->SetBinContent(2,0.09794216);
   h_tb_rap_circle_mult1__54->SetBinContent(3,0.1101586);
   h_tb_rap_circle_mult1__54->SetBinContent(4,0.1280933);
   h_tb_rap_circle_mult1__54->SetBinContent(5,0.1340747);
   h_tb_rap_circle_mult1__54->SetBinContent(6,0.1377316);
   h_tb_rap_circle_mult1__54->SetBinContent(7,0.1273912);
   h_tb_rap_circle_mult1__54->SetBinContent(8,0.1069121);
   h_tb_rap_circle_mult1__54->SetBinContent(9,0.08806996);
   h_tb_rap_circle_mult1__54->SetBinContent(10,0.07606905);
   h_tb_rap_circle_mult1__54->SetBinError(1,0.004473326);
   h_tb_rap_circle_mult1__54->SetBinError(2,0.004208386);
   h_tb_rap_circle_mult1__54->SetBinError(3,0.004812753);
   h_tb_rap_circle_mult1__54->SetBinError(4,0.005810815);
   h_tb_rap_circle_mult1__54->SetBinError(5,0.006613146);
   h_tb_rap_circle_mult1__54->SetBinError(6,0.007052334);
   h_tb_rap_circle_mult1__54->SetBinError(7,0.006502487);
   h_tb_rap_circle_mult1__54->SetBinError(8,0.005555167);
   h_tb_rap_circle_mult1__54->SetBinError(9,0.008836213);
   h_tb_rap_circle_mult1__54->SetBinError(10,0.006274408);
   h_tb_rap_circle_mult1__54->SetMinimum(0);
   h_tb_rap_circle_mult1__54->SetMaximum(0.2);
   h_tb_rap_circle_mult1__54->SetEntries(10);
   h_tb_rap_circle_mult1__54->SetDirectory(0);
   h_tb_rap_circle_mult1__54->SetStats(0);
   h_tb_rap_circle_mult1__54->SetFillStyle(0);

   ci = TColor::GetColor("#666666");
   h_tb_rap_circle_mult1__54->SetLineColor(ci);
   h_tb_rap_circle_mult1__54->SetLineWidth(2);
   h_tb_rap_circle_mult1__54->SetMarkerStyle(4);
   h_tb_rap_circle_mult1__54->SetMarkerSize(1.4);
   h_tb_rap_circle_mult1__54->GetXaxis()->SetTitle("Rapidity");
   h_tb_rap_circle_mult1__54->GetXaxis()->SetRange(0,11);
   h_tb_rap_circle_mult1__54->GetXaxis()->SetNdivisions(505);
   h_tb_rap_circle_mult1__54->GetXaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult1__54->GetXaxis()->SetLabelOffset(0.01);
   h_tb_rap_circle_mult1__54->GetXaxis()->SetLabelSize(0.05);
   h_tb_rap_circle_mult1__54->GetXaxis()->SetTitleSize(0.06);
   h_tb_rap_circle_mult1__54->GetXaxis()->SetTitleOffset(1.14);
   h_tb_rap_circle_mult1__54->GetXaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult1__54->GetYaxis()->SetTitle("T_{eff} (GeV)");
   h_tb_rap_circle_mult1__54->GetYaxis()->SetNdivisions(505);
   h_tb_rap_circle_mult1__54->GetYaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult1__54->GetYaxis()->SetLabelSize(0.05);
   h_tb_rap_circle_mult1__54->GetYaxis()->SetTitleSize(0.06);
   h_tb_rap_circle_mult1__54->GetYaxis()->SetTitleOffset(1.14);
   h_tb_rap_circle_mult1__54->GetYaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult1__54->GetZaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult1__54->GetZaxis()->SetLabelSize(0.035);
   h_tb_rap_circle_mult1__54->GetZaxis()->SetTitleSize(0.035);
   h_tb_rap_circle_mult1__54->GetZaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult1__54->Draw("samehistP");
   line = new TLine(0.742432,0.035,0.742432,0.18);
   line->SetLineStyle(9);
   line->Draw();
      tex = new TLatex(0.68,0.68,"#pi^{+}p");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.29);
   tex->SetLineWidth(2);
   tex->Draw();
   text = new TText(0.135,0.77,"10-20%");
   text->SetNDC();
   text->SetTextFont(42);
   text->SetTextSize(0.19);
   text->Draw();
   t1->Modified();
   can_tb_rap_all4_irc->cd();
  
// ------------>Primitives in pad: t2
   TPad *t2 = new TPad("t2", "t2",0.06,0.34,0.97,0.55);
   t2->Draw();
   t2->cd();
   t2->Range(0,0,1,1);
   t2->SetFillColor(0);
   t2->SetBorderMode(0);
   t2->SetBorderSize(0);
   t2->SetTickx(1);
   t2->SetTicky(1);
   t2->SetRightMargin(0);
   t2->SetTopMargin(0);
   t2->SetBottomMargin(0);
   t2->SetFrameLineWidth(2);
   t2->SetFrameBorderMode(0);
   t2->SetFrameBorderSize(0);
   Double_t xAxis61[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *can_tb_rap_err_irc_mult2 = new TH1D("can_tb_rap_err_irc_mult2","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis61);
   can_tb_rap_err_irc_mult2->SetBinContent(1,0.07165867);
   can_tb_rap_err_irc_mult2->SetBinContent(2,0.0896982);
   can_tb_rap_err_irc_mult2->SetBinContent(3,0.1015895);
   can_tb_rap_err_irc_mult2->SetBinContent(4,0.1172975);
   can_tb_rap_err_irc_mult2->SetBinContent(5,0.1257718);
   can_tb_rap_err_irc_mult2->SetBinContent(6,0.1285805);
   can_tb_rap_err_irc_mult2->SetBinContent(7,0.1171486);
   can_tb_rap_err_irc_mult2->SetBinContent(8,0.09557329);
   can_tb_rap_err_irc_mult2->SetBinContent(9,0.07965313);
   can_tb_rap_err_irc_mult2->SetBinContent(10,0.06115339);
   can_tb_rap_err_irc_mult2->SetBinError(1,0.01089656);
   can_tb_rap_err_irc_mult2->SetBinError(2,0.01165844);
   can_tb_rap_err_irc_mult2->SetBinError(3,0.02083961);
   can_tb_rap_err_irc_mult2->SetBinError(4,0.017355);
   can_tb_rap_err_irc_mult2->SetBinError(5,0.0166882);
   can_tb_rap_err_irc_mult2->SetBinError(6,0.01044293);
   can_tb_rap_err_irc_mult2->SetBinError(7,0.01042326);
   can_tb_rap_err_irc_mult2->SetBinError(8,0.00972752);
   can_tb_rap_err_irc_mult2->SetBinError(9,0.0075);
   can_tb_rap_err_irc_mult2->SetBinError(10,0.0075);
   can_tb_rap_err_irc_mult2->SetMinimum(0.035);
   can_tb_rap_err_irc_mult2->SetMaximum(0.18);
   can_tb_rap_err_irc_mult2->SetEntries(30);
   can_tb_rap_err_irc_mult2->SetStats(0);
   can_tb_rap_err_irc_mult2->SetFillStyle(0);

   ci = TColor::GetColor("#80ea7c");
   can_tb_rap_err_irc_mult2->SetLineColor(ci);
   can_tb_rap_err_irc_mult2->SetLineWidth(2);

   ci = TColor::GetColor("#80ea7c");
   can_tb_rap_err_irc_mult2->SetMarkerColor(ci);
   can_tb_rap_err_irc_mult2->SetMarkerStyle(20);
   can_tb_rap_err_irc_mult2->SetMarkerSize(1.4);
   can_tb_rap_err_irc_mult2->GetXaxis()->SetTitle("Rapidity");
   can_tb_rap_err_irc_mult2->GetXaxis()->SetRange(0,11);
   can_tb_rap_err_irc_mult2->GetXaxis()->SetNdivisions(505);
   can_tb_rap_err_irc_mult2->GetXaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult2->GetXaxis()->SetLabelOffset(0.01);
   can_tb_rap_err_irc_mult2->GetXaxis()->SetLabelSize(0.19);
   can_tb_rap_err_irc_mult2->GetXaxis()->SetTitleSize(0.06);
   can_tb_rap_err_irc_mult2->GetXaxis()->SetTickLength(0.1);
   can_tb_rap_err_irc_mult2->GetXaxis()->SetTitleOffset(16);
   can_tb_rap_err_irc_mult2->GetXaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult2->GetYaxis()->SetTitle("T_{eff} (GeV)");
   can_tb_rap_err_irc_mult2->GetYaxis()->SetNdivisions(505);
   can_tb_rap_err_irc_mult2->GetYaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult2->GetYaxis()->SetLabelSize(0.19);
   can_tb_rap_err_irc_mult2->GetYaxis()->SetTitleSize(0.06);
   can_tb_rap_err_irc_mult2->GetYaxis()->SetTickLength(0.035);
   can_tb_rap_err_irc_mult2->GetYaxis()->SetTitleOffset(16);
   can_tb_rap_err_irc_mult2->GetYaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult2->GetZaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult2->GetZaxis()->SetLabelSize(0.035);
   can_tb_rap_err_irc_mult2->GetZaxis()->SetTitleSize(0.035);
   can_tb_rap_err_irc_mult2->GetZaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult2->Draw("E2");
   Double_t xAxis62[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *can_tb_rap_irc_mult2 = new TH1D("can_tb_rap_irc_mult2","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis62);
   can_tb_rap_irc_mult2->SetBinContent(1,0.07165867);
   can_tb_rap_irc_mult2->SetBinContent(2,0.0896982);
   can_tb_rap_irc_mult2->SetBinContent(3,0.1015895);
   can_tb_rap_irc_mult2->SetBinContent(4,0.1172975);
   can_tb_rap_irc_mult2->SetBinContent(5,0.1257718);
   can_tb_rap_irc_mult2->SetBinContent(6,0.1285805);
   can_tb_rap_irc_mult2->SetBinContent(7,0.1171486);
   can_tb_rap_irc_mult2->SetBinContent(8,0.09557329);
   can_tb_rap_irc_mult2->SetBinContent(9,0.07965313);
   can_tb_rap_irc_mult2->SetBinContent(10,0.06115339);
   can_tb_rap_irc_mult2->SetBinError(1,0.003230002);
   can_tb_rap_irc_mult2->SetBinError(2,0.003664292);
   can_tb_rap_irc_mult2->SetBinError(3,0.0042656);
   can_tb_rap_irc_mult2->SetBinError(4,0.005296972);
   can_tb_rap_irc_mult2->SetBinError(5,0.006229472);
   can_tb_rap_irc_mult2->SetBinError(6,0.006226855);
   can_tb_rap_irc_mult2->SetBinError(7,0.005549437);
   can_tb_rap_irc_mult2->SetBinError(8,0.00412818);
   can_tb_rap_irc_mult2->SetBinError(9,0.006242492);
   can_tb_rap_irc_mult2->SetBinError(10,0.003902903);
   can_tb_rap_irc_mult2->SetMinimum(0);
   can_tb_rap_irc_mult2->SetMaximum(0.2);
   can_tb_rap_irc_mult2->SetEntries(10);
   can_tb_rap_irc_mult2->SetStats(0);
   can_tb_rap_irc_mult2->SetFillStyle(0);

   ci = TColor::GetColor("#80ea7c");
   can_tb_rap_irc_mult2->SetLineColor(ci);
   can_tb_rap_irc_mult2->SetLineWidth(2);

   ci = TColor::GetColor("#80ea7c");
   can_tb_rap_irc_mult2->SetMarkerColor(ci);
   can_tb_rap_irc_mult2->SetMarkerStyle(20);
   can_tb_rap_irc_mult2->SetMarkerSize(1.4);
   can_tb_rap_irc_mult2->GetXaxis()->SetTitle("Rapidity");
   can_tb_rap_irc_mult2->GetXaxis()->SetRange(0,11);
   can_tb_rap_irc_mult2->GetXaxis()->SetNdivisions(505);
   can_tb_rap_irc_mult2->GetXaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult2->GetXaxis()->SetLabelOffset(0.01);
   can_tb_rap_irc_mult2->GetXaxis()->SetLabelSize(0.05);
   can_tb_rap_irc_mult2->GetXaxis()->SetTitleSize(0.06);
   can_tb_rap_irc_mult2->GetXaxis()->SetTitleOffset(1.14);
   can_tb_rap_irc_mult2->GetXaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult2->GetYaxis()->SetTitle("T_{eff} (GeV)");
   can_tb_rap_irc_mult2->GetYaxis()->SetNdivisions(505);
   can_tb_rap_irc_mult2->GetYaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult2->GetYaxis()->SetLabelSize(0.05);
   can_tb_rap_irc_mult2->GetYaxis()->SetTitleSize(0.06);
   can_tb_rap_irc_mult2->GetYaxis()->SetTitleOffset(1.14);
   can_tb_rap_irc_mult2->GetYaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult2->GetZaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult2->GetZaxis()->SetLabelSize(0.035);
   can_tb_rap_irc_mult2->GetZaxis()->SetTitleSize(0.035);
   can_tb_rap_irc_mult2->GetZaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult2->Draw("samehistP");
   Double_t xAxis63[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *h_tb_rap_circle_mult2__55 = new TH1D("h_tb_rap_circle_mult2__55","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis63);
   h_tb_rap_circle_mult2__55->SetBinContent(1,0.07165867);
   h_tb_rap_circle_mult2__55->SetBinContent(2,0.0896982);
   h_tb_rap_circle_mult2__55->SetBinContent(3,0.1015895);
   h_tb_rap_circle_mult2__55->SetBinContent(4,0.1172975);
   h_tb_rap_circle_mult2__55->SetBinContent(5,0.1257718);
   h_tb_rap_circle_mult2__55->SetBinContent(6,0.1285805);
   h_tb_rap_circle_mult2__55->SetBinContent(7,0.1171486);
   h_tb_rap_circle_mult2__55->SetBinContent(8,0.09557329);
   h_tb_rap_circle_mult2__55->SetBinContent(9,0.07965313);
   h_tb_rap_circle_mult2__55->SetBinContent(10,0.06115339);
   h_tb_rap_circle_mult2__55->SetBinError(1,0.003230002);
   h_tb_rap_circle_mult2__55->SetBinError(2,0.003664292);
   h_tb_rap_circle_mult2__55->SetBinError(3,0.0042656);
   h_tb_rap_circle_mult2__55->SetBinError(4,0.005296972);
   h_tb_rap_circle_mult2__55->SetBinError(5,0.006229472);
   h_tb_rap_circle_mult2__55->SetBinError(6,0.006226855);
   h_tb_rap_circle_mult2__55->SetBinError(7,0.005549437);
   h_tb_rap_circle_mult2__55->SetBinError(8,0.00412818);
   h_tb_rap_circle_mult2__55->SetBinError(9,0.006242492);
   h_tb_rap_circle_mult2__55->SetBinError(10,0.003902903);
   h_tb_rap_circle_mult2__55->SetMinimum(0);
   h_tb_rap_circle_mult2__55->SetMaximum(0.2);
   h_tb_rap_circle_mult2__55->SetEntries(10);
   h_tb_rap_circle_mult2__55->SetDirectory(0);
   h_tb_rap_circle_mult2__55->SetStats(0);
   h_tb_rap_circle_mult2__55->SetFillStyle(0);

   ci = TColor::GetColor("#666666");
   h_tb_rap_circle_mult2__55->SetLineColor(ci);
   h_tb_rap_circle_mult2__55->SetLineWidth(2);
   h_tb_rap_circle_mult2__55->SetMarkerStyle(4);
   h_tb_rap_circle_mult2__55->SetMarkerSize(1.4);
   h_tb_rap_circle_mult2__55->GetXaxis()->SetTitle("Rapidity");
   h_tb_rap_circle_mult2__55->GetXaxis()->SetRange(0,11);
   h_tb_rap_circle_mult2__55->GetXaxis()->SetNdivisions(505);
   h_tb_rap_circle_mult2__55->GetXaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult2__55->GetXaxis()->SetLabelOffset(0.01);
   h_tb_rap_circle_mult2__55->GetXaxis()->SetLabelSize(0.05);
   h_tb_rap_circle_mult2__55->GetXaxis()->SetTitleSize(0.06);
   h_tb_rap_circle_mult2__55->GetXaxis()->SetTitleOffset(1.14);
   h_tb_rap_circle_mult2__55->GetXaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult2__55->GetYaxis()->SetTitle("T_{eff} (GeV)");
   h_tb_rap_circle_mult2__55->GetYaxis()->SetNdivisions(505);
   h_tb_rap_circle_mult2__55->GetYaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult2__55->GetYaxis()->SetLabelSize(0.05);
   h_tb_rap_circle_mult2__55->GetYaxis()->SetTitleSize(0.06);
   h_tb_rap_circle_mult2__55->GetYaxis()->SetTitleOffset(1.14);
   h_tb_rap_circle_mult2__55->GetYaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult2__55->GetZaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult2__55->GetZaxis()->SetLabelSize(0.035);
   h_tb_rap_circle_mult2__55->GetZaxis()->SetTitleSize(0.035);
   h_tb_rap_circle_mult2__55->GetZaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult2__55->Draw("samehistP");
   line = new TLine(0.742432,0.035,0.742432,0.18);
   line->SetLineStyle(9);
   line->Draw();
   text = new TText(0.135,0.77,"20-30%");
   text->SetNDC();
   text->SetTextFont(42);
   text->SetTextSize(0.19);
   text->Draw();
   t2->Modified();
   can_tb_rap_all4_irc->cd();
  
// ------------>Primitives in pad: t3
   TPad *t3 = new TPad("t3", "t3",0.06,0.09,0.97,0.34);
   t3->Draw();
   t3->cd();
   t3->Range(0,0,1,1);
   t3->SetFillColor(0);
   t3->SetBorderMode(0);
   t3->SetBorderSize(0);
   t3->SetTickx(1);
   t3->SetTicky(1);
   t3->SetRightMargin(0);
   t3->SetTopMargin(0);
   t3->SetBottomMargin(0.16);
   t3->SetFrameLineWidth(2);
   t3->SetFrameBorderMode(0);
   t3->SetFrameBorderSize(0);
   Double_t xAxis64[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *can_tb_rap_err_irc_mult3 = new TH1D("can_tb_rap_err_irc_mult3","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis64);
   can_tb_rap_err_irc_mult3->SetBinContent(1,0.06562379);
   can_tb_rap_err_irc_mult3->SetBinContent(2,0.08373134);
   can_tb_rap_err_irc_mult3->SetBinContent(3,0.09786778);
   can_tb_rap_err_irc_mult3->SetBinContent(4,0.1142226);
   can_tb_rap_err_irc_mult3->SetBinContent(5,0.1212486);
   can_tb_rap_err_irc_mult3->SetBinContent(6,0.1194395);
   can_tb_rap_err_irc_mult3->SetBinContent(7,0.1087234);
   can_tb_rap_err_irc_mult3->SetBinContent(8,0.0891334);
   can_tb_rap_err_irc_mult3->SetBinContent(9,0.07500518);
   can_tb_rap_err_irc_mult3->SetBinContent(10,0.0540504);
   can_tb_rap_err_irc_mult3->SetBinError(1,0.01516552);
   can_tb_rap_err_irc_mult3->SetBinError(2,0.01346654);
   can_tb_rap_err_irc_mult3->SetBinError(3,0.01962389);
   can_tb_rap_err_irc_mult3->SetBinError(4,0.0194324);
   can_tb_rap_err_irc_mult3->SetBinError(5,0.01509538);
   can_tb_rap_err_irc_mult3->SetBinError(6,0.01305104);
   can_tb_rap_err_irc_mult3->SetBinError(7,0.009613802);
   can_tb_rap_err_irc_mult3->SetBinError(8,0.01170169);
   can_tb_rap_err_irc_mult3->SetBinError(9,0.0075);
   can_tb_rap_err_irc_mult3->SetBinError(10,0.0075);
   can_tb_rap_err_irc_mult3->SetMinimum(0.035);
   can_tb_rap_err_irc_mult3->SetMaximum(0.18);
   can_tb_rap_err_irc_mult3->SetEntries(30);
   can_tb_rap_err_irc_mult3->SetStats(0);
   can_tb_rap_err_irc_mult3->SetFillStyle(0);

   ci = TColor::GetColor("#f0890c");
   can_tb_rap_err_irc_mult3->SetLineColor(ci);
   can_tb_rap_err_irc_mult3->SetLineWidth(2);

   ci = TColor::GetColor("#f0890c");
   can_tb_rap_err_irc_mult3->SetMarkerColor(ci);
   can_tb_rap_err_irc_mult3->SetMarkerStyle(20);
   can_tb_rap_err_irc_mult3->SetMarkerSize(1.4);
   can_tb_rap_err_irc_mult3->GetXaxis()->SetTitle("Rapidity");
   can_tb_rap_err_irc_mult3->GetXaxis()->SetRange(0,11);
   can_tb_rap_err_irc_mult3->GetXaxis()->SetNdivisions(505);
   can_tb_rap_err_irc_mult3->GetXaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult3->GetXaxis()->SetLabelOffset(0.01);
   can_tb_rap_err_irc_mult3->GetXaxis()->SetLabelSize(0.16);
   can_tb_rap_err_irc_mult3->GetXaxis()->SetTitleSize(0.06);
   can_tb_rap_err_irc_mult3->GetXaxis()->SetTickLength(0.08);
   can_tb_rap_err_irc_mult3->GetXaxis()->SetTitleOffset(16);
   can_tb_rap_err_irc_mult3->GetXaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult3->GetYaxis()->SetTitle("T_{eff} (GeV)");
   can_tb_rap_err_irc_mult3->GetYaxis()->SetNdivisions(505);
   can_tb_rap_err_irc_mult3->GetYaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult3->GetYaxis()->SetLabelSize(0.16);
   can_tb_rap_err_irc_mult3->GetYaxis()->SetTitleSize(0.06);
   can_tb_rap_err_irc_mult3->GetYaxis()->SetTitleOffset(16);
   can_tb_rap_err_irc_mult3->GetYaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult3->GetZaxis()->SetLabelFont(42);
   can_tb_rap_err_irc_mult3->GetZaxis()->SetLabelSize(0.035);
   can_tb_rap_err_irc_mult3->GetZaxis()->SetTitleSize(0.035);
   can_tb_rap_err_irc_mult3->GetZaxis()->SetTitleFont(42);
   can_tb_rap_err_irc_mult3->Draw("E2");
   Double_t xAxis65[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *can_tb_rap_irc_mult3 = new TH1D("can_tb_rap_irc_mult3","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis65);
   can_tb_rap_irc_mult3->SetBinContent(1,0.06562379);
   can_tb_rap_irc_mult3->SetBinContent(2,0.08373134);
   can_tb_rap_irc_mult3->SetBinContent(3,0.09786778);
   can_tb_rap_irc_mult3->SetBinContent(4,0.1142226);
   can_tb_rap_irc_mult3->SetBinContent(5,0.1212486);
   can_tb_rap_irc_mult3->SetBinContent(6,0.1194395);
   can_tb_rap_irc_mult3->SetBinContent(7,0.1087234);
   can_tb_rap_irc_mult3->SetBinContent(8,0.0891334);
   can_tb_rap_irc_mult3->SetBinContent(9,0.07500518);
   can_tb_rap_irc_mult3->SetBinContent(10,0.0540504);
   can_tb_rap_irc_mult3->SetBinError(1,0.004446858);
   can_tb_rap_irc_mult3->SetBinError(2,0.003390489);
   can_tb_rap_irc_mult3->SetBinError(3,0.00413263);
   can_tb_rap_irc_mult3->SetBinError(4,0.005425548);
   can_tb_rap_irc_mult3->SetBinError(5,0.006097468);
   can_tb_rap_irc_mult3->SetBinError(6,0.006072146);
   can_tb_rap_irc_mult3->SetBinError(7,0.004972841);
   can_tb_rap_irc_mult3->SetBinError(8,0.003500576);
   can_tb_rap_irc_mult3->SetBinError(9,0.005808669);
   can_tb_rap_irc_mult3->SetBinError(10,0.005374908);
   can_tb_rap_irc_mult3->SetMinimum(0);
   can_tb_rap_irc_mult3->SetMaximum(0.2);
   can_tb_rap_irc_mult3->SetEntries(10);
   can_tb_rap_irc_mult3->SetStats(0);
   can_tb_rap_irc_mult3->SetFillStyle(0);

   ci = TColor::GetColor("#f0890c");
   can_tb_rap_irc_mult3->SetLineColor(ci);
   can_tb_rap_irc_mult3->SetLineWidth(2);

   ci = TColor::GetColor("#f0890c");
   can_tb_rap_irc_mult3->SetMarkerColor(ci);
   can_tb_rap_irc_mult3->SetMarkerStyle(20);
   can_tb_rap_irc_mult3->SetMarkerSize(1.4);
   can_tb_rap_irc_mult3->GetXaxis()->SetTitle("Rapidity");
   can_tb_rap_irc_mult3->GetXaxis()->SetRange(0,11);
   can_tb_rap_irc_mult3->GetXaxis()->SetNdivisions(505);
   can_tb_rap_irc_mult3->GetXaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult3->GetXaxis()->SetLabelOffset(0.01);
   can_tb_rap_irc_mult3->GetXaxis()->SetLabelSize(0.05);
   can_tb_rap_irc_mult3->GetXaxis()->SetTitleSize(0.06);
   can_tb_rap_irc_mult3->GetXaxis()->SetTitleOffset(1.14);
   can_tb_rap_irc_mult3->GetXaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult3->GetYaxis()->SetTitle("T_{eff} (GeV)");
   can_tb_rap_irc_mult3->GetYaxis()->SetNdivisions(505);
   can_tb_rap_irc_mult3->GetYaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult3->GetYaxis()->SetLabelSize(0.05);
   can_tb_rap_irc_mult3->GetYaxis()->SetTitleSize(0.06);
   can_tb_rap_irc_mult3->GetYaxis()->SetTitleOffset(1.14);
   can_tb_rap_irc_mult3->GetYaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult3->GetZaxis()->SetLabelFont(42);
   can_tb_rap_irc_mult3->GetZaxis()->SetLabelSize(0.035);
   can_tb_rap_irc_mult3->GetZaxis()->SetTitleSize(0.035);
   can_tb_rap_irc_mult3->GetZaxis()->SetTitleFont(42);
   can_tb_rap_irc_mult3->Draw("samehistP");
   Double_t xAxis66[11] = {0, 0.142432, 0.342432, 0.492432, 0.642432, 0.742432, 0.842432, 0.992432, 1.142432, 1.342432, 1.8}; 
   
   TH1D *h_tb_rap_circle_mult3__56 = new TH1D("h_tb_rap_circle_mult3__56","M_{#pi^{+}p} 1.1-1.4 GeV",10, xAxis66);
   h_tb_rap_circle_mult3__56->SetBinContent(1,0.06562379);
   h_tb_rap_circle_mult3__56->SetBinContent(2,0.08373134);
   h_tb_rap_circle_mult3__56->SetBinContent(3,0.09786778);
   h_tb_rap_circle_mult3__56->SetBinContent(4,0.1142226);
   h_tb_rap_circle_mult3__56->SetBinContent(5,0.1212486);
   h_tb_rap_circle_mult3__56->SetBinContent(6,0.1194395);
   h_tb_rap_circle_mult3__56->SetBinContent(7,0.1087234);
   h_tb_rap_circle_mult3__56->SetBinContent(8,0.0891334);
   h_tb_rap_circle_mult3__56->SetBinContent(9,0.07500518);
   h_tb_rap_circle_mult3__56->SetBinContent(10,0.0540504);
   h_tb_rap_circle_mult3__56->SetBinError(1,0.004446858);
   h_tb_rap_circle_mult3__56->SetBinError(2,0.003390489);
   h_tb_rap_circle_mult3__56->SetBinError(3,0.00413263);
   h_tb_rap_circle_mult3__56->SetBinError(4,0.005425548);
   h_tb_rap_circle_mult3__56->SetBinError(5,0.006097468);
   h_tb_rap_circle_mult3__56->SetBinError(6,0.006072146);
   h_tb_rap_circle_mult3__56->SetBinError(7,0.004972841);
   h_tb_rap_circle_mult3__56->SetBinError(8,0.003500576);
   h_tb_rap_circle_mult3__56->SetBinError(9,0.005808669);
   h_tb_rap_circle_mult3__56->SetBinError(10,0.005374908);
   h_tb_rap_circle_mult3__56->SetMinimum(0);
   h_tb_rap_circle_mult3__56->SetMaximum(0.2);
   h_tb_rap_circle_mult3__56->SetEntries(10);
   h_tb_rap_circle_mult3__56->SetDirectory(0);
   h_tb_rap_circle_mult3__56->SetStats(0);
   h_tb_rap_circle_mult3__56->SetFillStyle(0);

   ci = TColor::GetColor("#666666");
   h_tb_rap_circle_mult3__56->SetLineColor(ci);
   h_tb_rap_circle_mult3__56->SetLineWidth(2);
   h_tb_rap_circle_mult3__56->SetMarkerStyle(4);
   h_tb_rap_circle_mult3__56->SetMarkerSize(1.4);
   h_tb_rap_circle_mult3__56->GetXaxis()->SetTitle("Rapidity");
   h_tb_rap_circle_mult3__56->GetXaxis()->SetRange(0,11);
   h_tb_rap_circle_mult3__56->GetXaxis()->SetNdivisions(505);
   h_tb_rap_circle_mult3__56->GetXaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult3__56->GetXaxis()->SetLabelOffset(0.01);
   h_tb_rap_circle_mult3__56->GetXaxis()->SetLabelSize(0.05);
   h_tb_rap_circle_mult3__56->GetXaxis()->SetTitleSize(0.06);
   h_tb_rap_circle_mult3__56->GetXaxis()->SetTitleOffset(1.14);
   h_tb_rap_circle_mult3__56->GetXaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult3__56->GetYaxis()->SetTitle("T_{eff} (GeV)");
   h_tb_rap_circle_mult3__56->GetYaxis()->SetNdivisions(505);
   h_tb_rap_circle_mult3__56->GetYaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult3__56->GetYaxis()->SetLabelSize(0.05);
   h_tb_rap_circle_mult3__56->GetYaxis()->SetTitleSize(0.06);
   h_tb_rap_circle_mult3__56->GetYaxis()->SetTitleOffset(1.14);
   h_tb_rap_circle_mult3__56->GetYaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult3__56->GetZaxis()->SetLabelFont(42);
   h_tb_rap_circle_mult3__56->GetZaxis()->SetLabelSize(0.035);
   h_tb_rap_circle_mult3__56->GetZaxis()->SetTitleSize(0.035);
   h_tb_rap_circle_mult3__56->GetZaxis()->SetTitleFont(42);
   h_tb_rap_circle_mult3__56->Draw("samehistP");
   */
   line = new TLine(0.742432,0.035,0.742432,0.18);
   line->SetLineStyle(9);
   line->Draw();
   text = new TText(0.135,0.77,"30-40%");
   text->SetNDC();
   text->SetTextFont(42);
   text->SetTextSize(0.16);
   text->Draw();
      tex = new TLatex(0.765,0.048,"y_{cm}");
   tex->SetTextFont(42);
   tex->SetTextSize(0.16);
   tex->SetLineWidth(2);
   tex->Draw();
   //t3->Modified();
   can_tb_rap_all4_irc->cd();
   can_tb_rap_all4_irc->Modified();
   can_tb_rap_all4_irc->cd();
   can_tb_rap_all4_irc->SetSelected(can_tb_rap_all4_irc);
}
