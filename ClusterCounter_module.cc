////writing by A. Carolina  G.B. acarogb@unicamp.br gbcarolinaa@gmail.com
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
//


// LArSoft Module which runs in dunetpc v 09_12_00
// LArSoft under Apache License, Version 2.0
// based on: various Modules and dunetpc and the below
//
//Startin with ////////////////////////////////////////////////////////////////////
// Class:       ClusterCounter
// Module Type: analyzer
// File:        ClusterCounter_module.cc
//
// Just an empty module, outputs the event number.
// Robert Sulej
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art_root_io/TFileService.h"
#include "art_root_io/TFileDirectory.h"
#include "messagefacility/MessageLogger/MessageLogger.h"


// LArSoft includes
//
#include "larcore/CoreUtils/ServiceUtil.h"
#include "lardata/DetectorInfoServices/DetectorClocksService.h"
#include "lardataobj/RecoBase/OpHit.h"

// // ROOT includes
#include "TTree.h"


namespace tutorial {

class ClusterCounter : public art::EDAnalyzer {
public:
  explicit ClusterCounter(fhicl::ParameterSet const & p);

  // Plugins should not be copied or assigned.
  ClusterCounter(ClusterCounter const &) = delete;
  ClusterCounter(ClusterCounter &&) = delete;
  ClusterCounter & operator = (ClusterCounter const &) = delete;
  ClusterCounter & operator = (ClusterCounter &&) = delete;

  // Required functions.
  void analyze(art::Event const & e) override;
  void beginJob() override;
  void endJob() override;

private:
 std::map< int, int> CntLCa;

  size_t fEvNumber;
  TTree *fEventTree;
//Carolina ----->
  size_t ftotOPlc;

};

ClusterCounter::ClusterCounter(fhicl::ParameterSet const & p) : EDAnalyzer(p) {}

void ClusterCounter::analyze(art::Event const & e)
{
    std::cout << "ClusterCounter module on event #" << e.id().event() << std::endl;


//Carolina -----> from here
    std::cout << "Welcome to Module for L C a"<< std::endl;


art::Handle< std::vector< recob::OpHit >> datLCa; 
std::string fname="ophitInternal"; 
if(e.getByLabel(fname,datLCa)){


for(size_t i=0; i!=datLCa->size(); ++i)
  ++CntLCa[datLCa->at(i).OpChannel()];


  else{
   std::cout << "Ooouuppss DIDNT READ  "<<fname<<std::endl;
}


}


}

void ClusterCounter::beginJob()
{

 art::ServiceHandle<art::TFileService> tfs; // TTree's are created in the memory managed by ROOT (you don't delete them)

    fEventTree = tfs->make<TTree>("EventTree", "event by event info");
//Carolina -----> change this
    fEventTree->Branch("opLCa", &CntLCa, "ophotonChs");

}
//**************************************************
//************************************************************
void ClusterCounter::endJob()
{
    mf::LogVerbatim("ClusterCounter") << "ClusterCounter finished job";
    //fEventTree = tfs->make<TTree>("EventTree", "event by event info");
    std::cout<<"End Job structure "<<std::endl;

}


} 

DEFINE_ART_MODULE(tutorial::ClusterCounter)
