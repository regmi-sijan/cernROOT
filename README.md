# Let's learn ROOT

Always remember the master of all the tutorials for the ROOT is the [root's official website page](https://root.cern/). Inside this page go to the **Reference**, and search your class name is top right search box. Then the result will display on the left panel. Now, click on the very beginning of the class name from the result to see it from the start and see its basic functionality and definitions.

## Graphs

We will see in here how to explore the data using `TGraphErrors`



## File I/O
Well you can simply first open a file with "RECREATE" option and then start making all the histograms or trees that you intend to save into
the file that you have created earlier. Finally, do `outFileName.Write()` it should write all the objects that you have created since
opening the outfile at the beginning. Now you can close the outfile as `outFileName.Close()`.

## N-tuples in ROOT
A ROOT TNtuple object can store rows of **float** entries. From the documentation I can see that TNtuple can be created via
`TNtuple(name, title, varlist)` and filled via `TNtuple::Fill(*x) or ::Fill(v1,v2,v3,...)`
Let's see we make `write_ntuple_to_file.C` to practice this. What you have done in this file here is that you tried to mimick the real data
kind of simulating the real data with three independent variables; and one dependent variable `cur`. This data mimics the measurements of
an electrical resistance while varying pressure and temperature.

Imagin now your task is to find the relations among the varialbe - of course the data file is only you know and not the relations inside the
code that you saw.  You should now open the `data-file` and start doing your analyis.
Some of the commands that you could do:
```
> root cond-exp.root
[] .ls   // should show you quickly what objects this fil have
[] cond_data->Print();		// checking what are variables names and dtypes
[] cond_data->Scan();
[] cond_data->Draw("Current:Potential);  // doing some action/analysis
[] cond_data->Draw("Current:Potential", "Temperature<270") // plotting with some conditions
```
Once you have the `outputfile.root` you can either use above method from command lines to interact with the file or you can make
another macro to interact with it like the ones here: `read_ntuple_from_file.C`

## TTree way to save and read data
Because Ntuple has very limited use (it can only store **float** variables); we need similar class that should store almost any
ROOT objects. We achieve this with the help of `TTree` class where variables are stored in their separate `branch`. Let's write one such
program named `write_ntuple_to_file_advanced.C`
This way of writing a code is much better using TTree.
Next we can now again use the above code to interact with the data files using command lines or make another macro to interact with the data.
Let's make one `read_ttree_from_file.C` this one here will have the concept of `TChain` to add all the data files (if it were, we only have
one data file) which are produced by the data file, they should have very similar data file names with only differing slightly by the 
numeric at the end. Please look into this file `read_ttree_from_file.C` for more detail.

But for the advanced user: you can do `TTree::MakeSelector` it will also open up the **data file** as previous but it will create the 
header file and a template to insert you own analysis code as well as in the form of `init()`, `process()`, `end()` methods; where `init()`
area consists of the initializations of the histograms if you want, `process()` area is where the meat of code should be all the calculations
your analysis that you want goes into here, and finally at the end in `end()` area you could wrap-up and `Write()` and `Close()` tasks.

## ROOT Workshop from nevis.columbia.edu website

The above [website](https://www.nevis.columbia.edu/~seligman/root-class/) has tons of other links [Unix](http://www.ee.surrey.ac.uk/Teaching/Unix/), [another UNIX](https://www.tutorialspoint.com/unix/index.htm).

## Plotting a Function:

```
[] TF1 f1("f1", "sin(x)/x", 0., 10.);    // here "f1" I kept same for root object as well as object name
[] f1.Draw();
```
The canvas will pop up with the function plotted with default settings. You can always edit the plots from GUI once the
figure pops up. Play with all the features available and learn from it. It is pretty straight-forward. There is no simple **undo** button but you can select the object you want removed and **delete** it.

## Histograms
One of the most important objects in ROOT for us. Simple construction --
```
[] TH1F h1("h1", "My histogram", 100, -3., 3.); //100 bins from -3 to 3
[] h1.FillRandom("gaus", 10000);   // filling histogram with 10000 random (default) gaussian entries
[] h1.Draw();  // h1.Draw("e") would draw histogram with simple error bars: sqrt(no. of entries in each bins)
```

**Own Function**: many times you want to fill your histograms with the function that you defined or your theoritical model found this function.
```
[] TF1 myfunc("myfunc", "gaus", 0, 3);
[] myfunc.SetParameters(10., 1., 0.5); // you must initialize the parameters in order to plot
[] myfunc.Draw();
[] TH1F h2("h2", "Histo from my function", 100, -3,3);
[] h2.FillRandom("myfunc", 10000); // filling histo with user function entries
[] h2.Draw();
```
Gaussian has the following form ![equation](https://latex.codecogs.com/svg.image?P_0e%5E%7B%20%5Cleft(%20%20%20%5Cfrac%7Bx-P_1%7D%7BP_2%7D%20%20%20%20%20%20%5Cright)%5E2%20%20%20%7D). wher P0, P1, and P2 are the parameters that you need to initialize or it would have taken
the default values in "gaus" cases; in other type of non-standard functions; parameters are not even initialized at first.

## Saving the doc
You could save your work in several formats from the canvas pop-up menu and save. If you save it in `.C` format then it will save your plot
the way in code and how you could generate the plot with the C++ code. If you save in `.pdf` format you save it and later use it to print or
put it on your other docs. Finally if you save in `.root` format it will save your object in the file which you can see with `TBrowser` or
just from the command line.

## TBrowser
`[] new TBrowser` is another useful code to type in root sessions to easily navigate the files in your directories especially if the files
are in `.root` format. You can easily visualize what objects are stored in this file. You can play around with this `TBrowser` thing as well
double-clicking objects and drawing the plots right there is the nice ability then to come back to command line to do it. `TBrowser` gives
power to quickly double-check the things before actually hard-coding into the command-lines.

## Fitting Histograms
One of another the most important tasks any physicists do in their careers. The file we will work here is `histogram.root` file. Open your
`TBrowser` and double click the file and view there are two histogram already created for this tutuorial `hist1:1` and `hist2:1`.

**First** histogram x-axis is "gaussian" but if it was not and you need to fit this histogram what parameters will you use?
Now if you right-click on the histgram and go to `Fit Panel` and fit with basic **Predef-1D, gaus, Chi-squared method** then you will
see the fit line and the values of the parameters printed in the command line. Of course you could also print these parameters values in
you plot itself using the **Options and then Fit Parameters** option settings. The fit paramters tells you if your theory (often your function) is fitting the data correctly or not? If in case you did **Landau** fit to your data, your fit would not match at all, You can try it!

In you fit parameter box if your `Chi2/ndf` is close to 1 then it is getting a good fit. `Fit Panel` that we used to trying to fit the 
histogram is okay for now; but for more complex functions you will want to always use the command line method to do this task. To do this
similar fit using command line you could just do: `[] hist1->Fit("gaus");`

**Second** histogram **hist2** is pretty interesting here. The label on x-axis already says **double gaussian** this means this histogram
has to be fit from our custom made **function** since it won't fit very good with any of the default available functions **(gaus, expo, landau, etc)**.

```
[] TF1 func("mydoublegaus", "gaus(0)+gaus(3)");
  \\ gaus(0) means the same default "gaus" function whose parameters starts from 0th index
  \\ gaus(3) means this "gaus"'s parameters starts with 3rd index; since gaus has 3 parameters

[] func.SetParameters(5., 5., 1., 1., 10., 1.);  // initialize the parameters
[] hist2->Fit("mydoublegaus");		// fit the histogram with custom function
	\\ the above fit won't be good since the choice of parameters were deliberately chosen so

[] func.SetParameters(5., 2., 1., 1., 10., 1.);
[] hist2->Fit("mydoublegaus");  \\ should do good fit
```

Internal ROOT name of the function is "mydoublegaus" and TF1 object name is "func".
If you ever wondered how that **histogram.root** file was created in the first place; you can see the `CreateHist.C` file. Be warned you 
won't always have the access to this kind of file in real-world; only you will get the data root files and you need to figure out the
fitting parameters on your own.

One neat trick you can do is you can save the **fitted histograms** into the same `histogram.root` file so that it would be easier for you
to find all the histos associated with each other in the same-place. But you need command line to do this

```
[] TFile file1("histogram.root", "UPDATE");  // UPDATE option played the role to change the file
[] hist2->Draw();
[] TF1 func("user", "gaus(0)+gaus(3)");  //  remember these are values from before so maybe use up-array keys to access them
[] func.SetParameters(5., 2., 1., 1., 10., 1.);
[] hist2->Fit("user");
[] hist2->Write();
[] func->Write();  // why we need this to be saved? I am not sure
[] file1.Close();
```

At the end you will see (`TBrowser`) to see; that your **hist2** has another histogram made which has the fitted curve now as well as the
old hist2 is there. We didn't overwrite but added new histogram as well as new function into the same `histogram.root` file.

### Fitting Sub Ranges:
By default, `TH1::Fit` will fit the function to the defined whole histogram range. We can do the option `"R"` as second parameter of the `Fit`
to restrict the fit range and to just fit the range defined in `TF1` constructor. Lets see one example
```
[] TF1 *f1 = new TF1("f1", "[0]*x*sin([1]*x)", -3, 3);		// this function extends from -3 to 3, also do setparameters
[] hist->Fit("f1", "R")  		// option R restricts the fit range
```
Either you could have done above way to restrict the fit range or you could do the following:
```
[] hist->Fit("f1", "", "", -3., 3.);   // this should fit the histogram to range -3, 3
```

# Variables in ROOT NTuple/Trees
The file we will be working is `experiment.root`. Open `TBrowser` and see inside of it. It has one object `tree1` with 100,000 simulated
physics events. Obviously you can play with the file using `TBrowser` and `TreeViewer` and do interactive analysis; but you will almost 
always required to work using **command line** and **macros** approach. I will list some of the commands you can type in command line
to interact with this file that contains `tree` in it (macros work in same approach with little variations):
```
[] TFile myFile("experiment.root");		// will associate the experiment.root file to myFile root object
[] myFile.ls();							// list what objects are inside this file
[] tree1->Scan();						// displays a nice table of data with columns as each variables, row as each instance
[] tree1->Print();						// will just display the branch (variable) and its data size in it
			// we saw this tree has variables named:  event, ebeam, px, py, pz, zv, and chi2
[] tree1->Draw("ebeam");			// to draw histogram out of any one variable (ebeam, energy of beam)
[] tree1->Draw("ebeam:px);			// instead of plotting just one variable; try plotting two
		// this is a scatter plot to see the correlations between two varialbes
		// Draw() variable uses (y:x) to decide axis
[] tree1->Draw("zv", "zv<20");			// making some cuts
[] tree1->Draw("ebeam", "zv<20");		// cuts and plot variables can be different
[] tree1->Draw("ebeam", "px>10 && zv<10");	// cuts using logical conditions
```

# Using C++ to analyze a Tree (using **MakeSelector**)
This `MakeSelector` will create skeleton of an analysis class for your ntuple. First open the file `[] TFile myFile("experiment.root");`.
Now we create an analysis macro for `tree1` with `MakeSelector`:
```
[] tree1->MakeSelector("tree1Analyze");		// this will create tree1Analyze.C and tree1Analyze.h files
```
You can look into these two files using `$ less tree1Analyze.h` and `$ less tree1Analyze.C`. If we take a closer look into this analysis code,
it has at least following **methods**. 
- **Definition**: defines the variables we are going to use
- **Initialization**: open files to save the analysis work, create histograms, etc
- **Loop**: for each event in ntuple or tree perform some tasks: calculate values, apply cuts, fill histogram, etc
- **wrap-up**: display results, save histograms, etc
You can see `Analyze.C` and `Analyze.h` files created after we did `MakeSelector` thing on *tree1* object. These files has been trimmed
a little to see it more clearly and comments are there where to put the relevant pieces of codes that we discussed earlier.

To run this analysis macro, you could do the following:
```
[] TFile myFile("experiment.root");		// loading up the experiment.root file
[] tree1->Process("Analyze.C");		// load Analyze.C and run it analysis code on the contents of the tree
```
`Process` will basically do the following:
- load your definitions
- execute your initializations
- execute the loop code for each entry in the tree
- execute your wrap-up code

Let's see how we can edit the skeleton created by `MakeSelector` to use as per our analysis job. I will list the steps you can edit the
`Analyze.C` file and save it as `newAnalyze.C` maybe:

In the **definiton** section; `TH1 *chi2Hist = NULL;`

In the **initialization** section:  ` chi2Hist = new TH1D("chi2", "Histogram of Chi2", 100, 0, 20);`

In the **loop** section:  `GetEntry(entry);` and `chi2Hist->Fill(*chi2);`
	// the first code says "get an entry from the tree (get each row)". This line will assign values to variables defined in ntuple:
	*ebeam, *chi2, and so on. The variables extracted (using MakeSelector) from ntuple are pointer and so they need to have prefix 
	of * to access their values. In second code, it says in the histogram `chi2Hist` add 1 to a bin that correspond to the value of 
	`*chi2`.

In the **wrap-up** section:   `chi2Hist->Draw();`

Once you saved this file and now to run it:
```
[] TFile myFile("experiment.root");
[] tree1->Process("newAnalyze.C");
```

This is how we make histogram with a C++ analysis macro. In the initialization section, we defined a histogram; in the loop section, we
filled the histogram with values; in the wrap-up section, we drew the histogram.

To put the x-axis, y-axis and title label for the histogram:
```
chi2Hist->GetXaxis()->SetTitle("chi2");
chi2Hist->GetYaxis()->SetTitle("number of events");
```

## Calculate your own variable
Sometime you might want to calculate your own variables like `pt`. Let's see the steps:
```
[] tree1->MakeSelector("AnalyzeVariables");		// start frest analysis skeleton
	// In Process section put this
Double_t pt = TMath::Sqrt( (*px)*(*px) + (*py)*(*py)  );
```
The nexts steps are to now create the histogram tha can save this variable and and save it. To see the bin range you can "cheat" by typying
the following in interactive mode `tree1->Draw("sqrt(px*px + py*py));`
You could also make another histogram of `theta`. using `TMath::ATan2(y,x);` which will compute the arctangent of y/x.

## applying cuts in your analysis macro
if we needed to find the number of events when `pz` is less than 145 GeV, then we could do the following:
```
Int_t pzCount = 0;				// in the definition section
if ( (*pz) < 145  )				// in process section
{
	pzCount = pzCount + 1;
}

std::cout << "The number of events with pz < 145 is " << pzCount << std::endl;			// in wrap-up section
```

# Some useful programming clips (for me):

## To make a histograms array using the for loop
1D-array of histograms:
```cpp
TH1F *eta_hist[96];	// histogram array defined ususally in class header file
for (int i=0; i<96; i++)
{
  TString a;
  a.Form("%d", i);	// a=i
  TString b = "eta_"+ a; // b=eta_i
  eta_hist[i] = new TH1F(b.Data(), "eta histogram", 70, 0.0, 0.7);  // array instantiated
}
```

2D-array of histograms: histo is still 1D, but array is 2D:
```cpp
TH1F *hist_eta_and_phi[96][258]; // ususally in class header file
for(int i=0; i<96; i++)
{
  for(int j=0; j<258; j++)
  {
    TString i1;	// i1 counts eta rows
    TString j1; // j1 counts phi cols
    i1.Form("%d", i);	// i1=i
    j1.Form("%d", j);	// j1=j
    TString hist_name = "emc_ieta" + i1 + "_phi" + j1;
    hist_eta_and_phi[i][j] = new TH1F(hist_name.Data(), "Histo of eta and phi", 70, 0.0, 0.7);
  }
}
```
