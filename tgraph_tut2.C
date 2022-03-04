#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"

#include <iostream>

void tgraph_tut2() {
    TGraphErrors* graph = new TGraphErrors(5); // 5 points will be there
    graph->SetPoint(0, 1., 2.1);
    graph->SetPoint(1, 2., 2.9);
    graph->SetPoint(2, 3., 4.05);
    graph->SetPoint(3, 4., 5.2);
    graph->SetPoint(4, 5., 5.95);
    graph->SetPointError(0, 0., 0.1);
    graph->SetPointError(1, 0., 0.1);
    graph->SetPointError(2, 0., 0.1);
    graph->SetPointError(3, 0., 0.1);
    graph->SetPointError(4, 0., 0.1);
    TCanvas* c1 = new TCanvas("c1", "fitting graphs");
    graph->Draw("APE");
    TF1* f = new TF1("f", "[0]*x+[1]", 0., 6.);
    graph->Fit("f");
    double m = f->GetParameter(0);
    double merr = f->GetParError(0);
    double b = f->GetParameter(1);
    double berr = f->GetParError(1);
    std::cout << "m = " << m << " +- " << merr << std::endl;
    std::cout << "b = " << b << " +- " << berr << std::endl;
}

