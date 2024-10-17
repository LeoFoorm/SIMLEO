//in order to get Bethe Bloch using Edep and dE/dx

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TH2.h"

void SIMPLE_ANALYSIS()
{
    TFile *ROOTfile = TFile::Open("Output0.root"); //Open the root file to analyze. It depends of the name, so please change it...

    TTree *edep = (TTree*)ROOTfile->Get("Edep"); //simple analysis

     
    edep->SetMarkerSize(0.5);
    edep->SetMarkerStyle(20);
    edep->SetMarkerColor(kBlue);
    edep->Draw("Energy_Deposition_MeV:Particle_Momentum_MeV");
    edep->Draw("EnergyDep_MeVmm:Particle_Momentum_MeV");
    
    

     //TH2D *Histo2D = new TH2D("Histo2D", "Energy Deposition [GeV] vs Muon Momentum [GeV]",3000, 0, 2, 3000, 1, 20);

    //In the Histo2D you should change the X-bins (the first after the title) and the y-bins (the fourth)

    //Filling the histogram 
     //EDEP_PRO->Draw("Energy_Deposition_MeV:Muon_Momentum_MeV>>Histo2D", "", "COLZ");
     //Histo2D->GetXaxis()->SetTitle("Muon Momentum [MeV]");
     //Histo2D->GetYaxis()->SetTitle("Energy Deposition [MeV]");


    //Draw the histograms
     //TCanvas *canvas_edep_pro = new TCanvas("canvas_edep_pro", "Histogram for edep ", 1600, 1200);
    
     //canvas_edep_pro->SetGrid();
     //canvas_edep_pro->SetLogx();  // Set X axis to logarithmic scale
     //canvas_edep_pro->SetLogy();  // Set Y axis to logarithmic scale
    // Histo2D->Draw("COLZ"); // Fourth pad for 2D histogram (with color scale)
    //canvas_edep_pro->Update();
    
}
