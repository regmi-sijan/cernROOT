#include "TH1.h"
#include "TF1.h"

void multifit()
{
	gStyle->SetOptFit(1111); // this helps to see the Fit parameters in our plot


	const int np = 49;		// no. of points
	float x[np] = {1.913521,  1.953769,  2.347435,  2.883654,  3.493567,  4.047560,  4.337210,  4.364347,  4.563004,
               5.054247,  5.194183,  5.380521,  5.303213,  5.384578,  5.563983,  5.728500,  5.685752,  5.080029,
               4.251809,  3.372246,  2.207432,  1.227541,  0.8597788, 0.8220503, 0.8046592, 0.7684097, 0.7469761,
               0.8019787, 0.8362375, 0.8744895, 0.9143721, 0.9462768, 0.9285364, 0.8954604, 0.8410891, 0.7853871,
               0.7100883, 0.6938808, 0.7363682, 0.7032954, 0.6029015, 0.5600163, 0.7477068, 1.188785,  1.938228,
               2.602717,  3.472962,  4.465014,  5.177035};
	
	// construct your histogram
	TH1F *h = new TH1F("h", "Example of several fits in subranges", np, 85, 134);
	h->SetMaximum(7);		// sets the maximum value for y-axis to look plot nicer and compact
	for (int i=0; i<np; i++)
	{
		h->SetBinContent(i+1, x[i]);	// filling the bin contents with the value defined above in array
	}
	// h->Draw(); // we could draw to check how the plot looks like
	// Next we will Fit this histogram with multiple sub-range functions
	
	double par[9];  // parameter array to store parameters for the total fit function

	// define the functions. Three different function that will fit different ranges
	TF1 *g1 = new TF1("g1", "gaus", 85, 95); // fname, fn, low_limit, high_limit
	g1->SetLineColor(1);
	TF1 *g2 = new TF1("g2", "gaus", 98, 108);  // notice, we still using default "gaus" fn
	g2->SetLineColor(3);
	TF1 *g3 = new TF1("g3", "gaus", 110, 121);	// this covers almost all the ranges
	g3->SetLineColor(6);

	// now let's add all three and define total function to plot as well
	TF1 *total = new TF1("total", "gaus(0)+gaus(3)+gaus(6)", 85, 125);
	total->SetLineColor(2);		// making the total fit function little different than other fits
	// here gaus(0) meaning its parameters starts from 0th index and so on
	// we didn't fit the part from 125 to 134 (maybe that's not our region of interest)
	
	// Let's do fittings. Remeber we need to add the fitting function continuously after we fit first
	// function. using the option "R+" during the fit will allow the fit in the histogram to take the 
	// range defined in the function plus means that the fitting function is added to the previous plots
	h->Fit(g1, "R");
	h->Fit(g2, "R+");
	h->Fit(g3, "R+");

	// after fitting get the parameters
	g1->GetParameters(&par[0]); // and put it into the par array
	g2->GetParameters(&par[3]);
	g3->GetParameters(&par[6]);

	// now set these parameters to the total function
	total->SetParameters(par);

	// Finally fit the total function
//	h->Fit("total", "R+");
	h->Fit("total", "R");
}
