import sys
import ROOT as rt

class inputFile():

    def __init__(self, fileName):
        self.HISTOGRAM = self.findHISTOGRAM(fileName)
        self.EXPECTED = self.findEXPECTED(fileName)
        self.OBSERVED = self.findOBSERVED(fileName)
        self.LUMI = self.findATTRIBUTE(fileName, "LUMI")
        self.ENERGY = self.findATTRIBUTE(fileName, "ENERGY")
        print self.ENERGY
      
        self.PRELIMINARY = self.findATTRIBUTE(fileName, "PRELIMINARY")

    def findATTRIBUTE(self, fileName, attribute):
        fileIN = open(fileName)        
        for line in fileIN:
            tmpLINE =  line[:-1].split(" ")
            if tmpLINE[0] != attribute: continue
            fileIN.close()
            return tmpLINE[1]

    def findHISTOGRAM(self, fileName):
        fileIN = open(fileName)        
        for line in fileIN:
            tmpLINE =  line[:-1].split(" ")
            if tmpLINE[0] != "HISTOGRAM": continue
            fileIN.close()
            rootFileIn = rt.TFile.Open(tmpLINE[1])
            return {'histogram': rootFileIn.Get(tmpLINE[2])}
    
    def findEXPECTED(self, fileName):
        fileIN = open(fileName)        
        for line in fileIN:
            tmpLINE =  line[:-1].split(" ")
            if tmpLINE[0] != "EXPECTED": continue
            fileIN.close()
            rootFileIn = rt.TFile.Open(tmpLINE[1])
            s = str(fileName) 
            if s.find("T2tt") == -1:
                return {'nominal': rootFileIn.Get(tmpLINE[2]),
                        'plus': rootFileIn.Get(tmpLINE[3]),
                        'minus': rootFileIn.Get(tmpLINE[4]),
                        'colorLine': tmpLINE[5],
                        'colorArea': tmpLINE[6]}  #,
                        #'Islandnominal': rootFileIn.Get(tmpLINE[7])} #just for the island on t2bw050 exp
            else:
                return {'nominal': rootFileIn.Get(tmpLINE[2]),
                        'plus': rootFileIn.Get(tmpLINE[3]),
                        'minus': rootFileIn.Get(tmpLINE[4]),
                        'OffShellnominal': rootFileIn.Get(tmpLINE[5]),
                        'OffShellplus': rootFileIn.Get(tmpLINE[6]),
                        'OffShellminus': rootFileIn.Get(tmpLINE[7]),
                        'colorLine': tmpLINE[8],
                        'colorArea': tmpLINE[9]}

    def findOBSERVED(self, fileName):
        fileIN = open(fileName)        
        for line in fileIN:
            tmpLINE =  line[:-1].split(" ")
            if tmpLINE[0] != "OBSERVED": continue
            fileIN.close()
            rootFileIn = rt.TFile.Open(tmpLINE[1])
            s = str(fileName) 
            if s.find("T2tt") == -1:
                return {'nominal': rootFileIn.Get(tmpLINE[2]),
                        'plus': rootFileIn.Get(tmpLINE[3]),
                        'minus': rootFileIn.Get(tmpLINE[4]),
                        'colorLine': tmpLINE[5],
                        'colorArea': tmpLINE[6]}
            else:
                return {'nominal': rootFileIn.Get(tmpLINE[2]),
                        'plus': rootFileIn.Get(tmpLINE[3]),
                        'minus': rootFileIn.Get(tmpLINE[4]),
                        'OffShellnominal': rootFileIn.Get(tmpLINE[5]),
                        'OffShellplus': rootFileIn.Get(tmpLINE[6]),
                        'OffShellminus': rootFileIn.Get(tmpLINE[7]),
                        'colorLine': tmpLINE[8],
                        'colorArea': tmpLINE[9]}
