//// writing by A. Carolina  G.B. acarogb@unicamp.br gbcarolinaa@gmail.com  
//  ROOT constructor which runs with v 6.18/04
//  ROOT under lisence LGPL 2.1
//

/*
Developed By A. Carolina G.B. =    Carolina ----->
FAPESP Project

update 03.06.2021 
*/


#include <cmath>
#include <stdlib.h>

#include <TH1.h> //C:libreria de root, histos de 1D
#include <TH1F.h> //C:libreria de root, histos de 1D

using std::cout;
using std::endl;


void createHistosOut()
  {
TFile f("histogramsOut.root", "update");


// useful variables
Double_t numEvn=250000;  //change this according to the number of events simulated
Double_t numPhs;
Double_t valener;
TH1D* hevents = new TH1D("hevents","Op. Photons and Event ",numEvn,0,numEvn);
TH1D* hEnerevents = new TH1D("hEnerevents","Op. Photons and  Energy",numEvn,0,numEvn);


 TFile fp("OutPut.root");


//Carolina -----> comment and uncomment the following according to the desire histograms form the Detector or from the Source

//************ INFORMATION AT DETECTOR
 TTree *t1 = (TTree*)fp.Get("phAra");
 cout<<"reading file "<<endl;
 t1->SetBranchAddress("eveNumOPdet",&numPhs);
 TTree *tdos = (TTree*)fp.Get("phAra");
 tdos->SetBranchAddress("enerTotDet",&valener)
TH1F*  histo= new TH1F("hPhDet","Photons per Alpha,",300,0,3000);
TH1F*  histoEner= new TH1F("hEnDet","Alpha Spectrum,",100,-1.0,30);
//*************************+

//************ INFORMATION AT SOURCE
//  TH1F*  histo= new TH1F("hPhSou","Photon per Alpha close to the Source,",300,0,3000);
//  TH1F*  histoEner= new TH1F("hEnSou","Alpha Spectrum,",100,-1.0,30);
// TTree *t1 = (TTree*)fp.Get("phSou");
// cout<<"reading file "<<endl;
// t1->SetBranchAddress("eveNumOPsou",&numPhs);
// TTree *tdos = (TTree*)fp.Get("phSou");
// tdos->SetBranchAddress("enerTotSou",&valener)
//TH1F*  histo= new TH1F("hPhDet","Photons per Alpha,",300,0,3000);
//TH1F*  histoEner= new TH1F("hEnDet","Alpha Spectrum,",100,-1.0,30);

//*************************

// Reading the Output from the simulation
   Int_t nentries = (Int_t)t1->GetEntries();
   for (Int_t i=0; i<nentries; i++) {
      t1->GetEntry(i);   tdos->GetEntry(i);
      hevents->Fill(numPhs);   hEnerevents->Fill(numPhs,valener); 
   }
   fp.Close();

   cout<<" Histograms reading for "<< hevents->GetEntries()<<" events"<<endl;
   f.cd();
   Float_t val;

//Carolina -----> Filling the histograms
   for(Int_t i=0;i<numEvn;i++)
      {	
             // removing zeros
      val=hevents->GetBinContent(i);
          if(val != 0)
		   histo->Fill(val);

	      val=hEnerevents->GetBinContent(i);
        if(val != 0)
	   histoEner->Fill(val);
      }
cout<<" histograms saved with  "<< histo->GetEntries()<<" entries"<<endl;
//cout<<" and energy histogram with  "<< histoEner->GetEntries()<<" entries"<<endl;

 f.cd();
 histo->Write();
 histoEner->Write();
 f.Close();
 return;
}


//*****************************************************************************************************************************************************************   END
/*
Copyright 2021 A. Carolina G. B.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
