#pragma once

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include "TXMLEngine.h"
#include "TH2Poly.h"
#include "TLine.h"
#include "TObject.h"

//c, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <vector>

using namespace std;

//ntpLoopstatsOne.C
void readASCIIfiel(TString filePath, TString fileName, 
                   Int_t nnMax, Int_t &nn, Int_t n0,
                   Double_t *xa, Double_t *xb, Double_t *xc, 
                   Double_t *xd, Double_t *xe, Double_t *xf, 
                   Double_t *xg);
const std::string currentDateTime();
TGraph *ntpLoopstatsOne(TString filePath, TString fileName, TString pdfLogPath, TString pcname);
