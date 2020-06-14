#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

void readASCIIfiel(TString filePath, TString fileName, 
		   Int_t nnMax, Int_t &nn, Int_t n0, 
		   Double_t *day, Double_t *second, Double_t *offset, 
		   Double_t *driftCompensation, Double_t *estimatedError, Double_t *stability, 
		   Double_t *pollingInterval);
TGraph* getGraph(TString filePath);

Int_t ntpLoopstats(TString filePath1 = "/home/gred/corto_ntp/data/pc-corto1/",
		   TString filePath2 = "/home/gred/corto_ntp/data/pc-corto2/",
		   TString filePath3 = "/home/gred/corto_ntp/data/pc-serdi6/"){

  ///////////////////////////////////
  TGraph *gr1 = getGraph(filePath1);
  gr1->SetName("gr1");
  //gr1->SetTitle("Current vs position");
  gr1->SetMarkerStyle(21);
  gr1->SetMarkerColor(kBlack);
  gr1->SetLineColor(kBlack);
  gr1->SetLineWidth(3);
  ///////////////////////////////////
  TGraph *gr2 = getGraph(filePath2);
  gr2->SetName("gr2");
  //gr2->SetTitle("Current vs position");
  gr2->SetMarkerStyle(21);
  gr2->SetMarkerColor(kRed);
  gr2->SetLineColor(kRed);
  gr2->SetLineWidth(3);
  ///////////////////////////////////
  TGraph *gr3 = getGraph(filePath3);
  gr3->SetName("gr3");
  //gr3->SetTitle("Current vs position");
  gr3->SetMarkerStyle(21);
  gr3->SetMarkerColor(kBlue);
  gr3->SetLineColor(kBlue);
  gr3->SetLineWidth(3);

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);

  TCanvas *c1 = new TCanvas("c1","plots",10,10,1200,600);
  c1->Clear();
  c1->SetFillColor(kWhite);
  c1->GetPad(0)->SetLeftMargin(0.1);
  c1->GetPad(0)->SetRightMargin(0.05);
  c1->GetPad(0)->SetTopMargin(0.05);
  c1->GetPad(0)->SetBottomMargin(0.1);
  
  // draw a frame to define the range
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr1);
  mg->Add(gr2);
  mg->Add(gr3);
  mg->Draw("APL");

  mg->GetXaxis()->SetTitle("time, s");
  mg->GetYaxis()->SetTitle("offset, s");

  mg->SetMaximum(0.1);
  mg->SetMinimum(-0.1);

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr1, "pc-corto1","lp");
  leg->AddEntry(gr2, "pc-corto2","lp");
  leg->AddEntry(gr3, "pc-serdi6","lp");
  leg->Draw();

  return 0;
}

TGraph* getGraph(TString filePath){
  Int_t i = 0;
  Int_t j = 0;
  const Int_t nnMax = 100000;
  const Int_t nnMaxFiles = 100000;
  //TString filePath = "/var/log/ntpstats/";
  //TString filePath = "/home/gred/corto_ntp/data/pc-corto2/";
  TString fileName;
  TString fileNameArr[nnMaxFiles];
  Int_t nnFiles = 0;
  ///////////////////////////////////////////////////////////
  string mot;
  TString inListFileN = filePath; inListFileN += "fileList";
  ifstream myfile (inListFileN.Data());
  if(myfile.is_open()){
    while(myfile>>mot ){
      //cout<<mot<<'\n';
      fileNameArr[i] = mot;
      i++;
    }
    myfile.close();
  }
  else{
    cout<<"Unable to open file : "<<inListFileN.Data()<<endl;
  }
  nnFiles = i;

  //---------------------------------------------------------
  Int_t nnn = 0;
  Int_t nn0 = 0;
  Int_t nn1 = 0;
  Int_t nni[nnMaxFiles];
  Double_t day[nnMax];
  Double_t second[nnMax];
  Double_t offset[nnMax];
  Double_t driftCompensation[nnMax];
  Double_t estimatedError[nnMax]; 
  Double_t stability[nnMax]; 
  Double_t pollingInterval[nnMax];  
  Double_t utMy[nnMax];
  for(i=0;i<nnFiles;i++){
    if(i == 0)
      nn0 = 0;
    else
      nn0 = nn0 + nni[i-1];
    fileName = fileNameArr[i];
    readASCIIfiel(filePath, fileName, nnMax, nn1, nn0, 
		  day, second, offset, driftCompensation, 
		  estimatedError, stability, pollingInterval);  
    nni[i] = nn1;
  }
  for(i=0;i<nnFiles;i++){
    nnn = nnn + nni[i];
  }
  //////////////////////////////////////////////////////////
  for(i = 0;i<nnn;i++){
    //utMy[i] = day[i]*24*3600 + second[i] - day[0]*24*3600;
    //utMy[i] = day[i]*24*3600 + second[i] - 57600*24*3600;
    utMy[i] = day[i]*24.0*3600.0 + second[i] - 57600.0*24*3600;
    //cout<<i<<" "<<utMy[i]<<" "<<offset[i]<<endl;
  }
  TGraph *gr1 = new TGraph(nnn,utMy,offset);

  return gr1;
}

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
  for(i = n0;i<(n0+nn);i++){
    /*
    cout<<setw(7)<<i
	<<setw(15)<<xa[i]
	<<setw(15)<<xb[i]
	<<setw(15)<<xc[i]
	<<setw(15)<<xd[i]
	<<setw(15)<<xe[i]
	<<setw(15)<<xf[i]
	<<setw(15)<<xg[i]<<endl;
    */
  }
  //cout<<"nn1 = "<<nn<<endl
  //  <<"nn0 = "<<n0<<endl;
}
