STOPS plotting
============

To check-out: git clone git@github.com:sigamani/Stops-AN-14-067.git 


1) runPlots. In a ROOT session do: 
root [0] .L dataMC.C 
root [1] makeAllPlots()

Perhaps add 'gROOT->ProcessLine("setTDRStyle.C");' in your .rootlogon.C
