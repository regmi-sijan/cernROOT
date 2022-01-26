void write_to_file()
{
	TH1F h("my_histogram", "My Title; X-axis; Y-axis", 100, -5,5);		// first we made histgram
	h.FillRandom("gaus");												// fill it with random gaus values
	
	TFile out_file("my_rootfile.root", "RECREATE");						// RECREATE option creates the new file
	h.Write();															// wrote the histogram
	out_file.Close();													// finally close the file
}
