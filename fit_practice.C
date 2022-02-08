#include <iostream>
using namespace std;
#include "TH1.h"
#include "TF1.h"

void fit_practice()
{
	gStyle->SetOptFit(kTRUE);
	TH1F *hist = new TH1F("hist", "example histogram", 100, -2, 2);
	hist->FillRandom("gaus", 10000);
	hist->Fit("gaus", "V", "E1", -1,1.5); // second and third are fit options
										  // we could just leave blank like: ("gau", "", "", -1,1.5)
	// How to obtain the values of the fit parameters?
	// Get the fitted function and Get its parameters - It's that simple.
	
	TF1 *gfit = (TF1 *)hist->GetFunction("gaus");  // we are now getting previously plotted gaus function
	gfit->GetParameter(0);
	gfit->GetParameter(1);
	gfit->GetParameter(2);
	double par[3];   // or we can save the parameters into an array
	gfit->GetParameters(par);

	for (int i=0; i<3; i++)
		cout << par[i] << endl;

}
