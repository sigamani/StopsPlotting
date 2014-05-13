#define MT_CUT 100 
#define MET_CUT 80
#define LEPTON_PT_CUT 26  
#define NJET_CUT 4
#define NBJET_CUT 1
#define NLEP_CUT 1


#include "Reader_final0210.h"
babyEvent myEvent;


// Control region definitions
// // ##################################


bool goesInPreselectionCR0() 
{

    if (myEvent.MET < MET_CUT) return false;
    if (myEvent.MT < MT_CUT) return false;
    if (myEvent.numberOfLepton != NLEP_CUT) return false;
    if (myEvent.nJets < NJET_CUT)  return false; 
    if (myEvent.nBTag < 1)  return false; 
    if ((!myEvent.isolatedTrackVeto) || (!myEvent.tauVeto)) return false;

    return true; 
}




bool goesIn0BtagCR1()
{

    if (myEvent.MET < MET_CUT) return false;
    if (myEvent.MT < MT_CUT) return false;
    if (myEvent.numberOfLepton != NLEP_CUT) return false;
    if (myEvent.nJets < NJET_CUT)  return false; 
    if (myEvent.nBTag != 0 )  return false; 
    if ((!myEvent.isolatedTrackVeto) || (!myEvent.tauVeto)) return false;

    return true; 
}



bool goesInMTPeakCR2()   // I guess CR2 was a logical name for it 
{

    if (myEvent.MET < MET_CUT) return false;
    if (myEvent.MT < 50) return false;
    if (myEvent.MT > 80) return false;
    if (myEvent.numberOfLepton != NLEP_CUT) return false;
    if (myEvent.nJets < NJET_CUT)  return false; 
    if (myEvent.nBTag < NBJET_CUT )  return false; 
    if ((!myEvent.isolatedTrackVeto) || (!myEvent.tauVeto)) return false;

    return true; 
}



bool goesInDileptonCR4() 
{

    // Apply double-lepton trigger requirement (for both MC and data)
    if ((!myEvent.triggerMuonElec) 
     && (!myEvent.triggerDoubleMuon)
     && (!myEvent.triggerDoubleElec)) return false;
    
    if (myEvent.MET < MET_CUT) return false;
    if (myEvent.MT < MT_CUT) return false;
    if (myEvent.numberOfLepton != 2) return false;
    if (myEvent.nJets < NJET_CUT)  return false;
    if (myEvent.nBTag < NBJET_CUT)  return false;

    return true; 
}



bool goesInDileptonCR5() 
{

    // Apply double-lepton trigger requirement (for both MC and data)
    if ((!myEvent.triggerMuonElec) 
     && (!myEvent.triggerDoubleMuon)
     && (!myEvent.triggerDoubleElec)) return false;
   
    if (myEvent.MET < MET_CUT) return false;
    if (myEvent.MT < MT_CUT) return false;
    if (myEvent.numberOfLepton != NLEP_CUT) return false;
    if (myEvent.nJets < NJET_CUT)  return false;
    if (myEvent.nBTag < NBJET_CUT)  return false;

    // Apply vetos
    if ( !((myEvent.isolatedTrackVeto == true ) || (myEvent.tauVeto == true))) return false; 


    return true; 
}



// Single-lepton channels definitions
// ##################################

bool goesInSingleElecChannel(babyEvent event, string sampleName, string sampleType) 
{
    // Keep only events with numberOfLepton == 1
    if (event.numberOfLepton != NLEP_CUT) return false;
    // For data, keep only events from SingleElec dataset
    if ((sampleType == "data") && (sampleName != "SingleElec")) return false;
    // Keep only events with an electron as leading lepton
    return (abs(event.leadingLeptonPDGId) == 11); 
}


bool goesInSingleMuonChannel(babyEvent event, string sampleName, string sampleType) 
{ 
    // Keep only events with numberOfLepton == 1
    if (event.numberOfLepton != 1) return false;
    // For data, keep only events from SingleMuon dataset
    if ((sampleType == "data") && (sampleName != "SingleMuon")) return false;
    // Keep only events with a muon as leading lepton
    return (abs(event.leadingLeptonPDGId) == 13); 
}


bool goesInSingleLeptonChannel(babyEvent event, string sampleName, string sampleType) 
{ 
    // Single-lepton channel is the union of e-channel + µ-channel
    bool test = (goesInSingleElecChannel(event,sampleName,sampleType) 
              || goesInSingleMuonChannel(event,sampleName,sampleType));
    return test;
}



// Double-lepton channels definitions
// ##################################

bool goesInDoubleElecChannel(babyEvent event, string sampleName, string sampleType) 
{ 
    // Keep only events with numberOfLepton == 2
    if (event.numberOfLepton != 2) return false;
    // For data, keep only events from DoubleElec dataset
    if ((sampleType == "data") && (sampleName != "DoubleElec")) return false;
    // Keep only events with two electrons
    return ((abs(event.leadingLeptonPDGId) == 11) 
         && (abs(event.secondLeptonPDGId)  == 11)); 
}



bool goesInDoubleMuonChannel(babyEvent event, string sampleName, string sampleType) 
{ 
    // Keep only events with numberOfLepton == 2
    if (event.numberOfLepton != 2) return false;
    // For data, keep only events from DoubleMuon dataset
    if ((sampleType == "data") && (sampleName != "DoubleMuon")) return false;
    // Keep only events with two muons
    return ((abs(event.leadingLeptonPDGId) == 13) 
         && (abs(event.secondLeptonPDGId)  == 13)); 
}



bool goesInMuonElecChannel(babyEvent event, string sampleName, string sampleType) 
{ 
    // Keep only events with numberOfLepton == 2
    if (event.numberOfLepton != 2) return false;
    // For data, keep only events from SingleMuon channel
    if ((sampleType == "data") && (sampleName != "MuEl")) return false;
    // Keep only events with an electron and a muon
    return   (((abs(event.leadingLeptonPDGId) == 13) 
            && (abs(event.secondLeptonPDGId)  == 11))
       ||     ((abs(event.leadingLeptonPDGId) == 11) 
            && (abs(event.secondLeptonPDGId)  == 13)));
}



bool goesInDoubleLeptonChannel(babyEvent event, string sampleName, string sampleType) 
{ 
    // Double-lepton channel is the union of ee, mumu and emu channels
    bool test = (goesInDoubleElecChannel(event,sampleName,sampleType) 
              || goesInDoubleMuonChannel(event,sampleName,sampleType)
              ||   goesInMuonElecChannel(event,sampleName,sampleType)  ); 
    return test;
}



// Weighting information
// #####################

float getLumi(babyEvent event, string sampleName, string sampleType)
{
         if (goesInSingleElecChannel(event, sampleName, sampleType))  return 19154.0;
    else if (goesInSingleMuonChannel(event, sampleName, sampleType))  return 19096.0;
    else if (goesInMuonElecChannel(  event, sampleName, sampleType))  return 19347.0;
    else if (goesInDoubleMuonChannel(event, sampleName, sampleType))  return 14595.0;
    else if (goesInDoubleElecChannel(event, sampleName, sampleType))  return 19216.0;
    else                                                              return 0.0;
}

float getWeight(babyEvent event, string sampleName, string sampleType)
{
    float weight = 1.0;
    if (sampleType == "data") return weight;

    // Get the lumi
    float lumi = getLumi(event,sampleName,sampleType);

    // Normalize to cross section times lumi
    weight *= event.weightCrossSection * lumi;

    // Apply trigger efficiency weights for singleLepton channels
    // TODO : Add number for dilepton 
    if (event.numberOfLepton == 1)
        weight *= event.weightTriggerEfficiency;

    // Apply pile-up weight 
    // TODO : Do we confirm we'll use also this for signal ?
    weight *= event.weightPileUp;

    // For signal, apply ISR reweighting
    if (sampleType == "signal")  
        weight *= event.weightISRmodeling;

    // For ttbar only, apply topPt reweighting
    if (sampleName.find("ttbar") != string::npos) 
        weight *= event.weightTopPt;

    return weight;
}

