void simple_graph()
{
	// total points
	const int nPoints = 10;

	// x-axis array and y-axi array
	double px[] = {-0.1, 0.05, 0.25, 0.35, 0.5, 0.61, 0.7, 0.85, 0.89, 0.95};	// let's say our data is these
	double py[] = {-1, 2.9, 5.6, 7.4, 9, 9.6, 8.7, 6.3, 4.5, 1};

	// x and y errors
	double ex[] = {.05, .1, .07, .07, .04, .05, .06, .07, .08, .05};
	double ey[] = {.8, .7, .6, .5, .4, .4, .5, .6, .7, .8};	// error in y

	// object created with obvious arguments
	TGraphErrors *gr = new TGraphErrors(nPoints, px, py, ex, ey);
	gr->Draw();
}
