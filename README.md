# Let's learn ROOT

## Graphs

We will see in here how to explore the data using `TGraphErrors`



## File I/O
well you can simply first open a file with "RECREATE" option and then start making al the histograms or trees that you intend to save into
the file that you have created earlier. Finally, do `outFileName.Write()` it should write all the objects that you have created since
opening the outfile at the beginning. Now you can close the outfile as `outFileName.Close()`

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

