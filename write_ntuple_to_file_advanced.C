void write_ntuple_to_file_advanced(const std::string& outputFileName="cond_exp_advanced.root",
									int numDataPoints=1000000)
{
	TFile ofile(outputFileName.c_str(), "RECREATE");					// open a file to write inside it the data

	TTree cond_data("cond_data", "Example - TTree");				// define a TTree

	float pot, cur, temp, pres;										// still using float but we could use any root object

	cond_data.Branch("Potential", &pot, "Potential/F");				// ready-up the Branches of the TTree
	cond_data.Branch("Current", &cur, "Current/F");					// we now just need to calculate/feed the variables value
	cond_data.Branch("Temperature", &temp, "Temperature/F");
	cond_data.Branch("Pressure", &pres, "Pressure/F");

	// calculating the values of the variables
	for (int i=0; i<numDataPoints; i++)
	{
		// fake the uniform data
		pot = gRandom->Uniform(0.,10.)*gRandom->Gaus(1., 0.01);		// we took random but uniform value bet 0 and 10; also added small gaus noise
		temp = gRandom->Uniform(250., 350.)+gRandom->Gaus(0., 0.3);
		pres = gRandom->Uniform(0.5, 1.5)*gRandom->Gaus(1., 0.02);
		cur = pot/(10.+0.05*(temp-300.)-0.2*(pres-1.))*gRandom->Gaus(1., 0.01);

		// write the above calculated values in each loop for each row of TTree to be filled
		cond_data.Fill();
	}
		// after filling your tree save it to the file
		cond_data.Write();
		ofile.Close();
}
