#include "TColor.h"
#include "TStyle.h"
#include "TMath.h"
#include "TFile.h"
#include "TF2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TTree.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TPolyLine.h"
#include "TROOT.h"
#include "TF1.h"
#include "TGaxis.h"


#include <iomanip>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <utility>


#include "smooth.C"


using namespace std;
void rootlogon();


TString savedir = "~/www/";


void plot_limit(TString dir, TString Exp){

 
  gStyle->SetCanvasColor(0);
  gStyle->SetPadColor(0);
  gStyle->SetMarkerStyle(15);
  gStyle->SetMarkerSize(0.25);
  gStyle->SetPalette(1);
  gStyle->SetTextFont(42);
  gStyle->SetMarkerColor(37);


  //palette settings - completely independent
  const Int_t NRGBs = 6;
  const Int_t NCont = 999;

  Double_t stops[NRGBs] = { 0.00, 0.1, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.99, 0.0, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.0, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.99, 0.0, 1.00, 0.12, 0.00, 0.00 };


  //TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  //gStyle->SetNumberContours(NCont);

  gStyle->SetOptStat(0);


  double shell;

   if (dir == "T2bw025") {dataset_name = "T2bw025_CUT0"; shell = 80. / 0.25;}
   if (dir == "T2bw050") {dataset_name = "T2bw050_CUT0"; shell = 80. / 0.50;}
   if (dir == "T2bw075") {dataset_name = "T2bw075_CUT0"; shell = 80. / 0.75;}
   //if (dir == "T2tt")    {dataset_name = "T2tt_CUT0";    shell = 173.;}
   if (dir == "T2tt")    {dataset_name = "T2tt";    shell = 173.;}


   TFile *fout = new TFile(TString(dir)+"_"+Exp+"_BDT.root","recreate");

   TH2D *hist_limit =  new TH2D(TString(dir)+"_"+Exp,"",29,87.5, 812.5, 17, -12.5,412.5); 


              for(int x=100; x<=800; x+=25){


                      for(int y=0; y<=400; y+=25){


  		  char shortfilename[500];
  		  char filename[500];

                  
  					sprintf(filename,"/afs/cern.ch/work/s/sigamani/public/CMSSW_6_1_1/src/HiggsAnalysis/CombinedLimit/LimitsBDT_22_noSCnoPDFnoSTAT/%s/ASYMPTOTIC_CLS_RESULT_S%d-N%d.root", dataset_name, x, y);  

                 ifstream ifile(filename);
				 if (!ifile.good()) continue; 
	         
	    TFile* file  = new TFile(filename, "READ");  
	    char* name = (char*)file->GetName();

		TTree *limittree = (TTree*)file->Get("limit");

		double high_val = 100.;

		TH1F* obs = new TH1F("obs","",100,0,high_val);
		limittree->Draw("limit>>obs", "quantileExpected==-1");
		TH1F* exp = new TH1F("exp","",100,0,high_val);
		limittree->Draw("limit>>exp", "quantileExpected==0.5");
		TH1F* expM = new TH1F("expM","",100,0,high_val);
		limittree->Draw("limit>>expM", "quantileExpected>0.15 && quantileExpected<0.16");
		TH1F* expP = new TH1F("expP","",100,0,high_val);
        limittree->Draw("limit>>expP", "quantileExpected>0.83 && quantileExpected<0.84");

		double limit;

        if ( Exp == "Obs" )  limit =  obs->GetMean();
        if ( Exp == "Exp" )  limit =  exp->GetMean();
        if ( Exp == "ExpM" ) limit =  expM->GetMean();
        if ( Exp == "ExpP" ) limit =  expP->GetMean();

		//double limit_cleaned = ReturnCleanedLimit( x, y, limit, dir, true, Exp);

		        //if (limit_cleaned < 1.0){
		        if (limit < 1.0){
		        //hist_limit->Fill(x,y,1./limit_cleaned);
		        hist_limit->Fill(x,y,limit);
			    file->Close();

		 }
	  }

	}


      TAxis *data_yaxis = hist_limit->GetYaxis();
      TAxis *data_zaxis = hist_limit->GetZaxis();
      TAxis *data_xaxis = hist_limit->GetXaxis();


      data_xaxis->SetTitle("m_{#tilde{t}} (GeV)");
      data_yaxis->SetTitle("m_{#tilde{#chi}^{0}_{1}} (GeV)");
//              data_zaxis->SetTitle("Signal strength R");


      TCanvas c1("c1","c1",800,600);
      c1.SetLeftMargin(0.1706731);
      c1.SetRightMargin(0.1983173);
      c1.SetTopMargin(0.04895105);
      c1.SetBottomMargin(0.1416084);
      c1.Range(-289.7381,-191.8196,1334.643,1074.487);


/*
          double level = 1.0;
          double contours[1];
          contours[0] = level;
          hist_limit->SetContour(1,contours);
          hist_limit->Draw("cont3c");
          hist_limit->SetLineColor(4);
          hist_limit->SetLineWidth(2);
 */ 

	  TLegendEntry *legge;
	  TLegend *leg;
	  leg = new TLegend(0.4,0.55,0.7,0.85);
	  leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.043);
//	  legge = leg->AddEntry(hist_limit,   "#color[4]{Expected U.L. @95\% CL}", "");
	  leg->SetFillColor(0);
	  hist_limit->Draw("colz");
	  leg->Draw();


      TLatex l1;
      l1.SetTextAlign(12);
      l1.SetTextSize(0.04);
      l1.SetNDC();
      l1.DrawLatex(0.155, 0.98, "CMS Preliminary");
      l1.DrawLatex(0.7, 0.98, "20 fb^{-1} (8 TeV)");

	  c1.SaveAs("~/www/test.png");
//      c1.SaveAs("~/www/STOP/Limits/V12_BDT2/"+dir+"_"+Exp+".png");

      fout->cd();
      fout->Write();
      fout->Close();

}


