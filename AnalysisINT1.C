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

void AnalysisINT1()
{
TFile *ROOTfile = TFile::Open("1-Output0.root"); //Open the root file to analyze. It depends of the name, so please change it...


TTree *EDEP_PRO = (TTree*)ROOTfile->Get("Edep"); 

    
    TH2D *Histo2D = new TH2D("Histo2D", "Energy Deposition [MeV] vs Muon Momentum [GeV]",3000, 0, 2, 3000, 1, 20);
    //In the Histo2D you should change the X-bins (the first after the title) and the y-bins (the fourth)


    TH2D *MeVHisto2D = new TH2D("MeVHisto2D", "Energy Deposition [MeV] vs Muon Momentum [MeV]",3000, 0, 2000, 3000, 1, 20);


    TH2D *dEdxHisto2D = new TH2D("dEdxHisto2D", "Energy Deposition [MeV/mm] vs Muon Momentum [GeV]",3000, 0, 2, 3000, 1, 20); //change


    TH2D *MeVdEdxHisto2D = new TH2D("MeVdEdxHisto2D", "Energy Deposition [MeV/mm] vs Muon Momentum [MeV]",3000, 0, 2, 3000, 1, 20); //change


    TH1D *Histo_Edep = new TH1D("Histo_Edep", "Energy Deposition [MeV] vs events ", 20000, 0, 45);
    Histo_Edep->SetLineColor(kOrange); // Line color for histogram
    Histo_Edep->SetFillColor(kOrange); // Fill color for bars
    Histo_Edep->SetFillStyle(3002); 


    TH1D *Histo_dEdx = new TH1D("Histo_dEdx", "Energy Deposition per Distance [MeV/mm] vs entries", 20000, 0, 45);
    Histo_dEdx->SetLineColor(kViolet);
    Histo_dEdx->SetFillColor(kViolet);
    Histo_dEdx->SetFillStyle(3003); // Set fill style


    TH1D *Histo_MOM= new TH1D("Histo_MOM", "Muon momentum [GeV] vs entries", 20000, 0, 2);
    Histo_MOM->SetLineColor(kTeal);
    Histo_MOM->SetFillColor(kTeal);
    Histo_MOM->SetFillStyle(3004); 


    TH1D *Histo_mom= new TH1D("Histo_mom", "Muon momentum [MeV] vs entries", 20000, 0, 2000);
    Histo_mom->SetLineColor(kTeal);
    Histo_mom->SetFillColor(kTeal);
    Histo_mom->SetFillStyle(3004); 


    //Filling the histogram 
    EDEP_PRO->Draw("Energy_Deposition_MeV:Muon_Momentum_GeV>>Histo2D", "", "COLZ");
    Histo2D->GetXaxis()->SetTitle("Muon Momentum [GeV]");
    Histo2D->GetYaxis()->SetTitle("Energy Deposition [MeV]");

    EDEP_PRO->Draw("Energy_Deposition_MeV:Muon_Momentum_MeV>>MeVHisto2D", "", "COLZ");
    MeVHisto2D->GetXaxis()->SetTitle("Muon Momentum [MeV]");
    MeVHisto2D->GetYaxis()->SetTitle("Energy Deposition [MeV]");

    EDEP_PRO->Draw("EnergyDep_MeVmm:Muon_Momentum_GeV>>dEdxHisto2D", "", "COLZ");
    dEdxHisto2D->GetXaxis()->SetTitle("Muon Momentum [GeV]");
    dEdxHisto2D->GetYaxis()->SetTitle("Energy Deposition per distance [MeV/mm]");

    EDEP_PRO->Draw("EnergyDep_MeVmm:Muon_Momentum_MeV>>MeVdEdxHisto2D", "", "COLZ");
    MeVdEdxHisto2D->GetXaxis()->SetTitle("Muon Momentum [MeV]");
    MeVdEdxHisto2D->GetYaxis()->SetTitle("Energy Deposition per distance [MeV/mm]");
    // --------------------------------------------------------------------------------
    EDEP_PRO->Draw("Energy_Deposition_MeV>>Histo_Edep");
    Histo_Edep->GetXaxis()->SetTitle("Energy Deposition [MeV]");
    Histo_Edep->GetYaxis()->SetTitle("Entries");

    EDEP_PRO->Draw("EnergyDep_MeVmm>>Histo_dEdx");
    Histo_dEdx->GetXaxis()->SetTitle("Energy Deposition [MeV/mm]");
    Histo_dEdx->GetYaxis()->SetTitle("Entries");

    EDEP_PRO->Draw("Muon_Momentum_GeV>>Histo_MOM");
    Histo_MOM->GetXaxis()->SetTitle("Muon Momentum [GeV]");
    Histo_MOM->GetYaxis()->SetTitle("Entries");

    EDEP_PRO->Draw("Muon_Momentum_MeV>>Histo_mom");
    Histo_mom->GetXaxis()->SetTitle("Muon Momentum [MeV]");
    Histo_mom->GetYaxis()->SetTitle("Entries");



    //Draw the histograms
    TCanvas *canvas_edep_pro = new TCanvas("canvas_edep_pro", "Histogram for edep ", 1600, 1200);
    canvas_edep_pro->SetGrid();
    canvas_edep_pro->SetLogx();  // Set X axis to logarithmic scale
    canvas_edep_pro->SetLogy();  // Set Y axis to logarithmic scale
    Histo2D->Draw("COLZ"); // Fourth pad for 2D histogram (with color scale)
    canvas_edep_pro->Update();


    TCanvas *canvas_edep_mev = new TCanvas("canvas_edep_mev", "Histogram for edep in right units ", 1600, 1200);
    canvas_edep_mev->SetGrid();
    canvas_edep_mev->SetLogx();  // Set X axis to logarithmic scale
    canvas_edep_mev->SetLogy();  // Set Y axis to logarithmic scale
    MeVHisto2D->Draw("COLZ"); // Fourth pad for 2D histogram (with color scale)
    canvas_edep_mev->Update();


    TCanvas *canvas_edepdis_gev = new TCanvas("canvas_edepdis_gev", "Histogram for edep per distance with gev momentum ", 1600, 1200);
    canvas_edepdis_gev->SetGrid();
    canvas_edepdis_gev->SetLogx();  // Set X axis to logarithmic scale
    canvas_edepdis_gev->SetLogy();  // Set Y axis to logarithmic scale
    dEdxHisto2D->Draw("COLZ"); // Fourth pad for 2D histogram (with color scale)
    canvas_edepdis_gev->Update();


    TCanvas *canvas_edepdis_mev = new TCanvas("canvas_edepdis_mev", "Histogram for edep per distance with mev momentum ", 1600, 1200);
    canvas_edepdis_mev->SetGrid();
    canvas_edepdis_mev->SetLogx();  // Set X axis to logarithmic scale
    canvas_edepdis_mev->SetLogy();  // Set Y axis to logarithmic scale
    MeVdEdxHisto2D->Draw("COLZ"); // Fourth pad for 2D histogram (with color scale)
    canvas_edepdis_mev->Update();


    TCanvas *canvas1D_Edep = new TCanvas("canvas1D_Edep", "1D Histogram - Energy Deposition", 800, 600);
    canvas1D_Edep->SetGrid();
    Histo_Edep->Draw();
    canvas1D_Edep->Update();


    TCanvas *canvas1D_dEdx = new TCanvas("canvas1D_dEdx", "1D Histogram - Energy Deposition per Distance", 800, 600);
    canvas1D_dEdx->SetGrid();
    Histo_dEdx->Draw();
    canvas1D_dEdx->Update();


    TCanvas *canvas1D_MOM = new TCanvas("canvas1D_MOM", "1D Histogram - Muon Momentum on GeV", 800, 600);
    canvas1D_MOM->SetGrid();
    Histo_MOM->Draw();
    canvas1D_MOM->Update();


    TCanvas *canvas1D_mom= new TCanvas("canvas1D_mom", "1D Histogram -  Muon Momentum on MeV", 800, 600);
    canvas1D_mom->SetGrid();
    Histo_mom->Draw();
    canvas1D_mom->Update();
}
