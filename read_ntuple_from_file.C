void read_ntuple_from_file()
{
	// steps are: open a file, save the ntuple and close the file
	TFile in_file("conductivity_exp.root");

	TNtuple *my_ntuple;
	in_file.GetObject("cond_data", my_ntuple);

	// start making varibles to read (make same as before)
	float pot, cur, temp, pres;
	float *row_content;

	cout << "Potential\tCurrent\tTemperature\tPressure" << endl;
	for (int irow=0; irow<my_ntuple->GetEntries(); irow++)
	{
		my_ntuple->GetEntry(irow);
		row_content = my_ntuple->GetArgs();
		pot = row_content[0];
		cur = row_content[1];
		temp = row_content[2];
		pres = row_content[3];
		cout << pot << "\t" << cur << "\t" << temp
		<< "\t" << pres << endl;
	}
}
