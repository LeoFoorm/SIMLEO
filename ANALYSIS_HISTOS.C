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

void ANALYSIS_HISTOS()
{
    //Open the root file to analyze
    TFile *mu_data = TFile::Open("merge_2partes.root"); 

    TFile *mu_p = TFile::Open("Output0_3mu_positive.root");     //to get the "good" one
   

    //getting each Ntuple
    TTree *photons = (TTree*)mu_data->Get("Photons");
    //TTree *hits = (TTree*)file->Get("hits");
    TTree *edep = (TTree*)mu_data->Get("Edep");
    //TTree *times = (TTree*)mu_data->Get("Times");
   
    TTree *Emu_p = (TTree*)mu_p->Get("Edep");

    //create histograms
    TH1D *Histo_Edep = new TH1D("Histo_Edep", "Energy Deposition [MeV] vs events ", 20000, 0, 7);
    Histo_Edep->SetLineColor(kOrange); // Line color for histogram
    Histo_Edep->SetFillColor(kOrange); // Fill color for bars
    Histo_Edep->SetFillStyle(3002); 
    TH1D *Histo_dEdx = new TH1D("Histo_dEdx", "Energy Deposition per Distance [MeV] vs entries", 20000, 0, 2.5);
    Histo_dEdx->SetLineColor(kViolet);
    Histo_dEdx->SetFillColor(kViolet);
    Histo_dEdx->SetFillStyle(3003); // Set fill style
    TH1D *Histo_Wlen= new TH1D("Histo_Wlen", "Wavelenght of Photons vs entries", 10000, 375, 505);
    Histo_Wlen->SetLineColor(kTeal);
    Histo_Wlen->SetFillColor(kTeal);
    Histo_Wlen->SetFillStyle(3004); 

    //TH2D *Histo2D = new TH2D("Histo2D", "Energy Deposition [MeV/mm] vs Muon Momentum [GeV]", 20000, , 1500, 20000, 0, 2.2);
    //Histo2D->SetLineColor(kRed);  <.... the original 

    TH2D *Histo2D = new TH2D("Histo2D", "Energy Deposition [MeV/mm] vs Muon Momentum [GeV]", 10000, 0.03, 5, 10000, 1, 20);
    Histo2D->SetMarkerSize(0.5);
    Histo2D->SetMarkerStyle(20);
    Histo2D->SetMarkerColor(kBlue);

    //Filling the histogram 
    photons->Draw("fwlen>>Histo_Wlen");
    edep->Draw("Energy_Deposition_MeV>>Histo_Edep");
    edep->Draw("EnergyDep_MeVmm>>Histo_dEdx");
    
   // edep->Draw("EnergyDep_MeVmm:Muon_Momentum_MeV>>Histo2D", "", "COLZ");    <.... the original 
    Emu_p->Draw("Energy_Deposition:Muon_Momentum>>Histo2D", "", "COLZ");

    Histo_Wlen->GetXaxis()->SetTitle("Wavelength [nm]");
    Histo_Wlen->GetYaxis()->SetTitle("Entries");

    Histo_Edep->GetXaxis()->SetTitle("Energy Deposition [MeV]");
    Histo_Edep->GetYaxis()->SetTitle("Events");

    Histo_dEdx->GetXaxis()->SetTitle("Energy Deposition [MeV/mm]");
    Histo_dEdx->GetYaxis()->SetTitle("Entries");

    Histo2D->GetXaxis()->SetTitle("Muon Momentum [MeV]");
    Histo2D->GetYaxis()->SetTitle("Energy Deposition [MeV/mm]");

    

    //Histo_Edep->SetFillColorAlpha(kMagenta, 0.35);  // Fill color with transparency for mu-
    //Histo_dEdx->SetFillColorAlpha(kCyan, 0.35);   // Fill color with transparency for mu+
    //Histo_Wlen->SetFillColorAlpha(kYellow, 0.35); // Fill color with transparency for pion


    //Draw the histograms
    TCanvas *canvas_histo = new TCanvas("canvas_histo", "Histograms", 1600, 1200);
    canvas_histo->Divide(2, 2); // Divide into 4 pads
    canvas_histo->SetGrid();

     canvas_histo->cd(1); 
     gPad->SetGrid();  // Enable grid for this pad
     Histo_Wlen->Draw();  // First pad for Wavelength histogram

     canvas_histo->cd(2); 
     gPad->SetGrid();  // Enable grid for this pad
     Histo_Edep->Draw();  // Second pad for Energy deposition

     canvas_histo->cd(3); 
     gPad->SetGrid();  // Enable grid for this pad
     Histo_dEdx->Draw();  // Third pad for Energy Deposition per Distance

     canvas_histo->cd(4); 
     gPad->SetGrid();  // Enable grid for this pad
     Histo2D->Draw("P"); // Fourth pad for 2D histogram (with color scale)
     canvas_histo->SetLogx();  // Set X axis to logarithmic scale
     canvas_histo->SetLogy();  // Set Y axis to logarithmic scale


// Clean up (optional)
    //delete Histo_Edep;
    //delete Histo_dEdx;
    //delete Histo_Wlen;
    //delete Histo2D;
    //delete canvas_histo;
    
canvas_histo->Update();

}


