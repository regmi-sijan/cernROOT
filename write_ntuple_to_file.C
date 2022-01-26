void write_ntuple_to_file()
{
	TFile ofile("conductivity_exp.root", "RECREATE");

	TNtuple cond_data("cond_data",
						"Example N-Tuple",
						"Potential:Current:Temperature:Pressure");

	// fill it randomly
	TRandom3 rndm;
	float pot, cur, temp, pres;
	for (int i=0; i<10000; i++)
	{
		pot = rndm.Uniform(0., 10.);
		temp = rndm.Uniform(250., 350.);
		pres = rndm.Uniform(0.5, 1.5);
		cur = pot/(10.+0.05*(temp-300.)-0.2*(pres-1.));

		// add some random errors also
		pot*=rndm.Gaus(1., 0.01); // 1% error on voltage let's say
		temp+=rndm.Gaus(0., 0.3);
		pres*=rndm.Gaus(1., 0.01);
		cur*= rndm.Gaus(1., 0.01);

		// write these var to N-tuple
		cond_data.Fill(pot,cur,temp,pres); //notice the order of variable to fill
	}

	// save the ntuple
	cond_data.Write();
	ofile.Close();

}
