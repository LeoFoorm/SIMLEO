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

void ANALYSISOVERLAP()
{
    //Open the root file to analyze
    TFile *mu_n = TFile::Open("Output0_1mu_negative.root"); 
    TFile *mu_p = TFile::Open("Output0_3mu_positive.root");
    TFile *pion = TFile::Open("Output0_2pi.root");

    //getting each Ntuple
    //TTree *photons = (TTree*)file->Get("Photons");
    //TTree *hits = (TTree*)file->Get("hits");
    //TTree *edep = (TTree*)file->Get("Edep");
    //TTree *times = (TTree*)file->Get("Times");

    //Retrievem the data
    TTree *Emu_n = (TTree*)mu_n->Get("Edep"); //before put correctly the units
    TTree *Emu_p = (TTree*)mu_p->Get("Edep");
    TTree *Epion = (TTree*)pion->Get("Edep");

    //create histograms
    TH1D *Histo_mu_n = new TH1D("Histo_mu_n", "Energy Deposition [MeV] vs events ", 10000, 0, 45);
    Histo_mu_n->SetLineColor(kMagenta); // Line color for histogram
    Histo_mu_n->SetFillColor(kMagenta); // Fill color for bars
    Histo_mu_n->SetFillStyle(3002); 
    TH1D *Histo_mu_p = new TH1D("Histo_mu_p", "Energy Deposition [MeV] vs events from mu+", 10000, 0, 45);
    Histo_mu_p->SetLineColor(kCyan);
    Histo_mu_p->SetFillColor(kCyan);
    Histo_mu_p->SetFillStyle(3003); // Set fill style
    TH1D *Histo_pion = new TH1D("Histo_pion", "Energy Deposition [MeV] vs events from pion", 10000, 0, 45);
    Histo_pion->SetLineColor(kYellow);
    Histo_pion->SetFillColor(kYellow);
    Histo_pion->SetFillStyle(3004); 

    //Filling the histogram 
    Emu_n->Draw("Energy_Deposition>>Histo_mu_n");
    Emu_p->Draw("Energy_Deposition>>Histo_mu_p");
    Epion->Draw("Energy_Deposition>>Histo_pion");

    Histo_mu_n->SetFillColorAlpha(kMagenta, 0.35);  // Fill color with transparency for mu-
    Histo_mu_p->SetFillColorAlpha(kCyan, 0.35);   // Fill color with transparency for mu+
    Histo_pion->SetFillColorAlpha(kYellow, 0.35); // Fill color with transparency for pion


    //Draw the histograms
    TCanvas *canvaOverlaping = new TCanvas("canvaOverlaping","Overlaping of the histograms");

    //set colors for every histo
    //Histo_mu_n->SetLineColor(kBlue); 
    //Histo_mu_p->SetLineColor(kRed); 
    //Histo_pion->SetLineColor(kGreen);

    //Draw each histogram
    Histo_mu_n->Draw("HIST"); 
    Histo_mu_p->Draw("HIST SAME"); 
    Histo_pion->Draw("HIST SAME");

    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(Histo_mu_n, "Output_muon_Negative", "f");
    legend->AddEntry(Histo_mu_p, "Output_muon_Positive", "f");
    legend->AddEntry(Histo_pion, "Output_Pion", "f");
    legend->Draw();

    //update the canvas to show the plots
    canvaOverlaping->Update();

    // Optionally, save the canvas as an image (PNG, PDF, etc.)
    //c->SaveAs("compareThreeEnergy.png");

}
