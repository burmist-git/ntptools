/***********************************************************************
* Copyright(C) 2019 - LBS - (Single person developer.)                 *
* Tue Apr 16 22:48:03 JST 2019                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLine.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TTree.h>
#include <TH2Poly.h>
#include <TH1D.h>
#include <TFile.h>
#include <TMath.h>
#include <TText.h>
#include <TSystem.h>

//c, c++
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>

using namespace std;

void readASCIIfiel(TString filePath, TString fileName, 
		   Int_t nnMax, Int_t &nn, Int_t n0,
		   Double_t *xa, Double_t *xb, Double_t *xc, 
		   Double_t *xd, Double_t *xe, Double_t *xf, 
		   Double_t *xg){
  string line;
  TString fileNameFull = filePath; fileNameFull +="/"; fileNameFull += fileName;
  cout<<"fileNameFull = "<<fileNameFull<<endl;
  ifstream myfile (fileNameFull.Data());
  Int_t i  = n0;
  Int_t ii = 0;
  Double_t a;
  Double_t b;
  Double_t c;
  Double_t d;
  Double_t e;
  Double_t f;
  Double_t g;
  if(myfile.is_open()){
    while(myfile>>a>>b>>c>>d>>e>>f>>g){
      xa[i] = a;
      xb[i] = b;
      xc[i] = c;
      xd[i] = d;
      xe[i] = e;
      xf[i] = f;
      xg[i] = g;
      i++;
      ii++;
      if(i>=nnMax){
	cout<<" ---> ERROR : i>=nnMax "<<endl
	    <<"              i = "<<i<<endl
	    <<"          nnMax = "<<nnMax<<endl;
	gSystem->Exit(-1);
      }
    }
    nn = ii;
    myfile.close();
  }
  else{
    cout << "Unable to open file"; 
  }
  for(i = 0;i<nn;i++){
    cout<<setw(15)<<xa[i]
	<<setw(15)<<xb[i]
	<<setw(15)<<xc[i]
	<<setw(15)<<xd[i]
	<<setw(15)<<xe[i]
	<<setw(15)<<xf[i]
	<<setw(15)<<xg[i]<<endl;
  }
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

TGraph *ntpLoopstatsOne(TString filePath = "/var/log/ntpstats/", TString fileName = "loopstats.20181125", TString pdfLogPath = "/home/hvala/ntptools/pdfLog_data/", TString pcname = "pcname"){

  Int_t i =0;
  const Int_t nnMax = 1000;
  //TString filePath = "/var/log/ntpstats/";
  //TString filePath = "./";
  //TString fileName = "loopstats.20181125";
  //---------------------------------------------------------
  //fileName = "ch1_x.txt";
  Double_t day[nnMax];
  Double_t second[nnMax];
  Double_t offset[nnMax];
  Double_t driftCompensation[nnMax];
  Double_t estimatedError[nnMax]; 
  Double_t stability[nnMax]; 
  Double_t pollingInterval[nnMax];  
  Double_t utMy[nnMax];  
  /////////////////////////////////////////////////////////
  Int_t nn1 = 0;
  Int_t n0 = 0;
  readASCIIfiel(filePath, fileName, nnMax, nn1, n0, 
		day, second, offset, driftCompensation, 
		estimatedError, stability, pollingInterval);  
  /////////////////////////////////////////////////////////
  //Int_t nn2 = 0;
  //n0 = nn1;
  //fileName = "loopstats.20181125";
  //readASCIIfiel(filePath, fileName, nnMax, nn2, n0, 
  //		day, second, offset, driftCompensation, 
  //		estimatedError, stability, pollingInterval);
  //////////////////////////////////////////////////////////
  //Int_t nnn = nn1+nn2;
  Int_t nnn = nn1;
  for(i = 0;i<nnn;i++){
    //utMy[i] = day[i]*24*3600 + second[i] - day[0]*24*3600;
    //utMy[i] = (day[i] + 2400000.5 - 2440587.5)*86400.0 + second[i] - 9.0*3600;
    utMy[i] = (day[i] + 2400000.5 - 2440587.5)*86400.0 + second[i];
    //1543122412.0 / 86400.0 + 2440587.5  - 2400000.5 = x
    cout<<i<<" "<<utMy[i]<<" "<<offset[i]<<endl;
  }
  TGraph *gr1 = new TGraph(nnn,utMy,offset);
  gr1->SetName("gr1");
  gr1->SetTitle(fileName.Data());
  gr1->SetMarkerStyle(21);
  gr1->SetMarkerColor(kBlack);
  gr1->SetLineColor(kBlack);
  gr1->SetLineWidth(3);

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);

  TCanvas *c1 = new TCanvas("c1","plots",10,10,1000,600);
  c1->Clear();
  c1->SetFillColor(kWhite);
  //c1->GetPad(0)->SetLeftMargin(0.12);
  //c1->GetPad(0)->SetRightMargin(0.02);
  //c1->GetPad(0)->SetTopMargin(0.07);
  //c1->GetPad(0)->SetBottomMargin(0.02);
  c1->SetRightMargin(0.05);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.1);
  c1->SetBottomMargin(0.08);
  c1->SetGridx();
  c1->SetGridy();
  
  // draw a frame to define the range
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr1);

  mg->SetMaximum(0.1);
  mg->SetMinimum(-0.1);
  TString mgTitle = pcname;
  mgTitle += " ";
  mgTitle +=fileName; 
  mgTitle += " ";
  TString currentDateTimeStr = currentDateTime();
  mgTitle +=currentDateTimeStr; 
  //cout<<"currentDateTime() "<<currentDateTime()<<endl;
  mg->SetTitle(mgTitle.Data());
  mg->Draw("APL");
  mg->GetYaxis()->SetTitle("Offset, s");
  mg->GetXaxis()->SetTimeDisplay(1);
  mg->GetXaxis()->SetTimeDisplay(1);
  mg->GetXaxis()->SetTimeFormat("#splitline{%m/%d}{%H:%M}%F1970-01-01 00:00:00");
  mg->GetXaxis()->SetLabelOffset(0.025);
  //mg->GetXaxis()->SetTitle("time, h");

  c1->Modified();
  c1->Update();
  
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr1, "offset","lp");
  //leg->Draw();

  if(pdfLogPath != ""){
    TString pdfLog = pdfLogPath;
    pdfLog += fileName;
    pdfLog += ".pdf";
    c1->SaveAs(pdfLog.Data());
  }

  return gr1;

}
