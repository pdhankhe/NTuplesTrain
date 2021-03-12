
Int_t AddGoodRuns(AliAnalysisAlien* plugin,TString lhcPeriod,TString mcprod="") {
  //
  // Adds good runs from the Monalisa Run Condition Table
  //
  if(mcprod=="") plugin->SetRunPrefix("000"); // DATA
  
  Int_t firstrun=0,lastrun=9999999;
  Int_t nruns=0,ngoodruns=0;
  
  
  if(lhcPeriod=="LHC15o_Gir") {
    if(mcprod=="") {
      nruns= 1;
      Int_t runlist[15] ={246766, 246945, 246928, 246846, 246845, 246844, 246810, 246809, 246808, 246807, 246805, 246804, 246765, 246760, 246759};
      for(Int_t k=0;k<nruns;k++){
	if(runlist[k]<firstrun || runlist[k]>lastrun) continue;
	plugin->AddRunNumber(runlist[k]);
	ngoodruns++;
      }
    }
    plugin->SetNrunsPerMaster(ngoodruns);
  }

  if(lhcPeriod=="LHC16r_wSDD") {
    if(mcprod=="") {
      nruns= 8;
      Int_t runlist[8] ={266318, 266317, 266316, 266208, 266197, 266196, 266187, 265744 };
      for(Int_t k=0;k<nruns;k++){
	if(runlist[k]<firstrun || runlist[k]>lastrun) continue;
	plugin->AddRunNumber(runlist[k]);
	ngoodruns++;
      }
    }
    plugin->SetNrunsPerMaster(ngoodruns);
  }
  
  
  
  if(lhcPeriod=="LHC16s_wSDD") {
    if(mcprod=="") {
      nruns= 15;
      Int_t runlist[15] ={267110, 267081, 267077, 267072, 267070, 266998, 266997, 266994,266993, 266944, 266886, 266885, 266883, 266882, 266437};
 for(Int_t k=0;k<nruns;k++){
   if(runlist[k]<firstrun || runlist[k]>lastrun) continue;
   plugin->AddRunNumber(runlist[k]);
   ngoodruns++;
      }
    }
    plugin->SetNrunsPerMaster(ngoodruns);
  }

 if(lhcPeriod=="LHC16s_wSDD") {
    if(mcprod=="LHC17i5a") {
      nruns= 23;
      Int_t runlist[23] ={265744, 266187, 266196, 266197, 266208, 266316, 266317, 266318, 266437, 266882, 266883, 266885, 266886, 266944, 266993, 266994, 266997, 266998, 267070, 267072, 267077, 267081, 267110
};
 for(Int_t k=0;k<nruns;k++){
   if(runlist[k]<firstrun || runlist[k]>lastrun) continue;
   plugin->AddRunNumber(runlist[k]);
   ngoodruns++;
      }
    }
    plugin->SetNrunsPerMaster(ngoodruns);
  }

return ngoodruns;
}
