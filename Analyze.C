#define Analyze_cxx
#include "Analyze.h"
#include <TH2.h>
#include <TStyle.h>

// **** Definition section ****
void Analyze::Begin(TTree * /*tree*/)
{
  

   TString option = GetOption();
   TH1 *chi2Hist = NULL;
   chi2Hist = new TH1D("chi2", "Histogram of chi2", 100, 0,20);
}

// *** Initialization section ****
void Analyze::SlaveBegin(TTree * /*tree*/)
{
}

Bool_t Analyze::Process(Long64_t entry)
{

   fReader.SetLocalEntry(entry);

   // ** Loop section **
   // You probably want GetEntry(entry) here.
	GetEntry(entry);
	chi2Hist->Fill(*chi2);

   return kTRUE;
}

void Analyze::SlaveTerminate(){}

void Analyze::Terminate()
{
  // ** wrap-up section *** 
  chi2Hist->Draw();
}
