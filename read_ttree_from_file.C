/* The purpose of the macro:
 * To read the data files that are similiarly named as is the
 * output of some analysis comes in this way as data files.
 *
 * After reading the chaining them all in one giant file; you read the TTree object from all
 * of them that are also "same" name of TTree
 *
 * Once you access the TTree, you just print the variables and their values in a nice
 * table looking format
 */

void read_ttree_from_file()
{
	// TChain takes name of the TTree (or TNtuple) as the argument
	TChain in_chain("cond_data"); // since our data file has "cond_data" TTree
	in_chain.Add("cond_exp_advanced*.root"); // read this data file
	// wild card means anything after that should be added as a single giant file
	

	// define TTree var and assign them the branches; defining the same name of braches
	// as with the original TTree is helpful
	float pot, cur, temp, pres;
	in_chain.SetBranchAddress("Potential", &pot);  // we can think TChain object itself is a TTree
	in_chain.SetBranchAddress("Current", &cur);
	in_chain.SetBranchAddress("Temperature", &temp);
	in_chain.SetBranchAddress("Pressure", &pres);

	cout << "Potential\tCurrent\tTemperature\tPressure\n";
	for (int i=0; i<in_chain.GetEntries(); i++)
	{
		if (i==20) break; // just to see first 50 rows
		in_chain.GetEntry(i);
		cout << pot << "\t" << cur << "\t" << temp <<
		"\t" << pres << endl;
	}


}
