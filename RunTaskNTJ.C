{   const char* launch = "local"; //local or grid
    const char*  mode = "test"; // test or full
    Int_t cyclenumber = 1;
    Bool_t debug = kTRUE;
    const char* workDir = "NTuplesTest";
    const char* outputDir = "output";
    TString testfileslistWithPlugin = "./filesAOD.txt";
    Int_t ttl = 50000;
    Int_t noffiles = 7;
    //Int_t runcycle[] = {0,12,25};
    Int_t runcycle[] = {0,25};
    
    // load libraries
    LoadLibraries();
    
    TString mkl_filename = "";
    TString efp7_filename = "";
   
    
    if (!gSystem->AccessPathName("libmkl_core_so")) {
        // See https://software.intel.com/en-us/mkl-linux-developer-
        // guide-dynamic-libraries-in-the-lib-intel64-lin-directory
        mkl_filename = "libiomp5_so libmkl_avx2_so libmkl_avx_so "
            "libmkl_core_so libmkl_def_so libmkl_intel_lp64_so "
            "libmkl_intel_thread_so libmkl_vml_avx2_so "
            "libmkl_vml_avx_so libmkl_vml_def_so";
    }
    if (!gSystem->AccessPathName("efp7.cc")) {
        efp7_filename =
            "blasdrv.h efp7.cc einstein_sum.h fill_efp7.h";
    }
  
    
    
    gROOT->ProcessLine(".include $ROOTSYS/include");
    gROOT->ProcessLine(".include $ALICE_ROOT/include");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/include");
    
    AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
    
    alienHandler->SetAdditionalLibs("PWGGA_CF_config.yaml emcal_correction.yaml EMCALlocal2master.root geometry_2015.root libCDB.so libSTEER.so libGui.so libMinuit.so libXMLParser.so libRAWDatabase.so libRAWDatarec.so libSTEERBase.so "
                                    "special_function.h mc_truth.h cgal_4_9.h "
                                    "emcal_cell.h emcal.h isolation.h jet.h "
                                    "bad_channel.h "
                                    "eLut.cpp eLut.h half.cpp halfExport.h halfFunction.h "
                                    "half.h halfLimits.h toFloat.h "
                                    "keras_model.h keras_model.cc "
                                    "track_cuts.h "
                                    "photon_discr.model "
                                    "libpythia6.so libAliPythia6.so "
                                    "libfastjet.so libsiscone.so "
                                    "libsiscone_spherical.so libfastjetplugins.so "
                                    "libfastjetcontribfragile.so " +
                                    mkl_filename + " " + efp7_filename + " "
                                    );
    
    alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/STEER -I$ALICE_ROOT/STEER/STEER -I$ALICE_ROOT/EMCAL -I$ALICE_ROOT/ANALYSIS -I$ALICE_ROOT/STEER/STEERBase -I$ALICE_ROOT/STEER/ESD -I$ALICE_ROOT/STEER/AOD -I$ALICE_ROOT/ITS -I$ALICE_ROOT/TPC -IALICE_ROOT/PWG/EMCAL -I$ALICE_ROOT/macros -I$ALICE_ROOT/PYTHIA6 -I$ALICE_ROOT/FASTSIM -I$ALICE_ROOT/EVGEN -I$ALICE_ROOT/LHAPDF -I$ALICE_PHYSICS/PWGHF -I$ALICE_PHYSICS/PWGHF/hfe -I$ALICE_PHYSICS/OADB -I$ALICE_PHYSICS/PWGHF/base -I$ALICE_PHYSICS/include -I$ALICE_PHYSICS/PWGJE -I$ALICE_PHYSICS/JETAN -I$ALICE_PHYSICS/JETAN/FASTJETAN -I$FASTJET/include -g");
    
    alienHandler->SetAdditionalLibs("libCDB.so libSTEER.so libGui.so libMinuit.so libXMLParser.so libRAWDatabase.so libRAWDatarec.so libSTEERBase.so");
    

    //alienHandler->SetAnalysisSource("AliAnalysisTaskNTGJTest.cxx");
    alienHandler->SetRunMode(mode);
    alienHandler->SetUser("pdhankhe");
    alienHandler->SetAPIVersion("V1.1x");
    //alienHandler->SetROOTVersion("v5-34-30-alice10-79");
    //alienHandler->SetAliROOTVersion("v5-09-57b-1");
    alienHandler->SetAliPhysicsVersion("vAN-20210311-1");
    alienHandler->SetFileForTestMode(testfileslistWithPlugin.Data());
    alienHandler->SetNtestFiles(1); // if "test mode"
    
    
    
    //________________________Set data search pattern for DATA and MC
    //Method 1: To create automatically xml through plugin
    gROOT->LoadMacro("./AddGoodRuns.C");
    
    alienHandler->SetGridDataDir("/alice/data/2015/LHC15o"); // specify LHC period
    alienHandler->SetDataPattern("/pass1/AOD194/*/AliAOD.root"); // specify reco pass and AOD set
   Int_t totruns=0;
   totruns += AddGoodRuns(alienHandler,"LHC15o_Gir",""); // specify LHC period
  
    
    alienHandler->SetGridWorkingDir(workDir);
    alienHandler->SetGridOutputDir(outputDir);
    alienHandler->SetDefaultOutputs(kTRUE);
    //alienHandler->SetAnalysisMacro("GAMC.C");
    //alienHandler->SetSplitMaxInputFileNumber(noffiles);
    //alienHandler->SetExecutable("GAMC.sh");
    //alienHandler->SetExecutableCommand("aliroot -b -q");
    alienHandler->SetTTL(ttl); //10000
    alienHandler->SetInputFormat("xml-single");
    alienHandler->SetJDLName("GAMC.jdl");
    //alienHandler->SetPrice(1);
    alienHandler->SetSplitMode("se");
    alienHandler->SetMasterResubmitThreshold(10);
    alienHandler->SetMergeExcludes("EventStat_temp.root");
    alienHandler->SetOutputToRunNo(kTRUE);
    alienHandler->SetKeepLogs(kTRUE);
    alienHandler->SetMaxMergeStages(4);
    alienHandler->SetMergeViaJDL(kTRUE);
    
    if (!alienHandler) return;
    
    // Use AliRoot includes to compile our task
    gROOT->ProcessLine(".include $ALICE_ROOT/include");
    gROOT->ProcessLine(".include $ALICE_ROOT/EMCAL");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/PWGGA/");
    gROOT->ProcessLine(".include $ALICE_ROOT/ANALYSIS/");
    gROOT->ProcessLine(".include $PWD/.");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/PWGHF");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/PWGHF/hfe");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/JETAN");
    gROOT->ProcessLine(".include $FASTJET/include");
    
    
    
    alienHandler->SetAdditionalLibs("PWGGA_CF_config.yaml emcal_correction.yaml EMCALlocal2master.root geometry_2015.root libCDB.so libSTEER.so libGui.so libMinuit.so libXMLParser.so libRAWDatabase.so libRAWDatarec.so libSTEERBase.so "
                                    "special_function.h mc_truth.h cgal_4_9.h "
                                    "emcal_cell.h emcal.h isolation.h jet.h "
                                    "bad_channel.h "
                                    "eLut.cpp eLut.h half.cpp halfExport.h halfFunction.h "
                                    "half.h halfLimits.h toFloat.h "
                                    "keras_model.h keras_model.cc "
                                    "track_cuts.h "
                                    "photon_discr.model "
                                    "libpythia6.so libAliPythia6.so "
                                    "libfastjet.so libsiscone.so "
                                    "libsiscone_spherical.so libfastjetplugins.so "
                                    "libfastjetcontribfragile.so " +
                                    mkl_filename + " " + efp7_filename + " "
                                    );
    
    gSystem->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/STEER -I$ALICE_ROOT/STEER/STEER -I$ALICE_ROOT/EMCAL -I$ALICE_ROOT/ANALYSIS -I$ALICE_ROOT/STEER/STEERBase -I$ALICE_ROOT/STEER/ESD -I$ALICE_ROOT/STEER/AOD -I$ALICE_ROOT/ITS -I$ALICE_ROOT/TPC -IALICE_ROOT/PWG/EMCAL -I$ALICE_ROOT/macros -I$ALICE_ROOT/PYTHIA6 -I$ALICE_ROOT/FASTSIM -I$ALICE_ROOT/EVGEN -I$ALICE_ROOT/LHAPDF -I$ALICE_PHYSICS/PWGHF -I$ALICE_PHYSICS/PWGHF/hfe -I$ALICE_PHYSICS/OADB -I$ALICE_PHYSICS/PWGHF/base -I$ALICE_PHYSICS/include -I$ALICE_PHYSICS/PWGJE -I$ALICE_PHYSICS/JETAN -I$ALICE_PHYSICS/JETAN/FASTJETAN -I$ALICE_PHYSICS/PWGCF/Correlations/Base  -I$ALICE_PHYSICS/PWGCF/Correlations/DPhi -I$ALICE_PHYSICS/PWG/Tools -I$FASTJET/include -g");
    
    AliAnalysisManager *mgr = new AliAnalysisManager("ElectronEffiMC");
    mgr->SetGridHandler(alienHandler);
    
    AliAODInputHandler* aodH = new AliAODInputHandler();
    mgr->SetInputEventHandler(aodH);
    
  
    gROOT->LoadMacro("$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C");
    gROOT->LoadMacro("$ALICE_PHYSICS/PWG/EMCAL/macros/AddTaskEmcalCorrectionTask.C");
    //gROOT->LoadMacro("$ALICE_PHYSICS/OADB/macros/AddTaskPhysicsSelection.C");
    gROOT->LoadMacro("$ALICE_PHYSICS/PWGPP/PilotTrain/AddTaskCDBconnect.C");
    gROOT->LoadMacro("$ALICE_PHYSICS/PWGGA/NtuplizerTask/GJNtuples/macros/AddAliAnalysisTaskNTGJ.C");
    
    
    Bool_t isMC=false; // kTRUE in case of MC
    Bool_t is_embed=false; // kTRUE in case of MC
    
  //  AddTaskPhysicsSelection(isMC,true);
    
    AliTaskCDBconnect *taskCDB = AddTaskCDBconnect();
    taskCDB->SetFallBackToRaw(kTRUE);
    
    AliMultSelectionTask *mult_selection_task = AddTaskMultSelection(false);
    
/*    if (is_embed) {
    AliAnalysisTaskEmcalEmbeddingHelper * embeddingHelper = AddTaskEmcalEmbeddingHelper();
    embeddingHelper->SetAOD();
    embeddingHelper->SetRandomFileAccess(kTRUE);
    embeddingHelper->SetRandomEventNumberAccess(kTRUE);
    embeddingHelper->Initialize();
}*/
    
    AliEmcalCorrectionTask * correctionTask = AddTaskEmcalCorrectionTask();
    correctionTask->SelectCollisionCandidates(AliVEvent::kAny);
    correctionTask->SetUserConfigurationFilename("PWGGA_CF_config.yaml");
    correctionTask->Initialize();
    
    
   // AddAliAnalysisTaskNTGJ("ntuples","emcal_correction.yaml",true,false,false,false,"geometry_2015.root","EMCALlocal2master.root",false,15.0,0,0,0,0,0,0,-2147483648,0,0,0,"lhc15o",false,false,"","");
    AddAliAnalysisTaskNTGJ("ntuples","PWGGA_CF_config.yaml",true,false,false,false,"geometry_2015.root","EMCALlocal2master.root",false,15.0,-1.7976931348623157e+308,-1.7976931348623157e+308,-1.7976931348623157e+308,-1.7976931348623157e+308,-1.7976931348623157e+308,-1.7976931348623157e+308,-2147483648,-1.7976931348623157e+308,-1.7976931348623157e+308,0,"lhc15o",false,false,"","");
    if (!mgr->InitAnalysis())
        return;
    
    mgr->PrintStatus();
    mgr->StartAnalysis(launch);
}

void LoadLibraries()
{
    gSystem->Load("libCore");
    gSystem->Load("libTree");
    gSystem->Load("libGeom");
    gSystem->Load("libVMC");
    gSystem->Load("libXMLIO");
    gSystem->Load("libPhysics");
    gSystem->Load("libXMLParser");
    gSystem->Load("libProof");
    gSystem->Load("libMinuit");
    gSystem->Load("libSTEERBase");
    gSystem->Load("libSTEER");
    gSystem->Load("libCDB");
    gSystem->Load("libRAWDatabase");
    gSystem->Load("libRAWDatarec");
    gSystem->Load("libESD");
    gSystem->Load("libAOD");
    gSystem->Load("libOADB");
    gSystem->Load("libANALYSIS");
    gSystem->Load("libANALYSISalice");
    gSystem->Load("libGui");
    gSystem->Load("libEVGEN");
    gSystem->Load("libCDB");
    gSystem->Load("libRAWDatabase");
    gSystem->Load("libSTEER");
    gSystem->Load("libTPCbase");
    gSystem->Load("libTOFbase");
    gSystem->Load("libTOFrec");
    gSystem->Load("libTRDbase");
    gSystem->Load("libVZERObase");
    gSystem->Load("libVZEROrec");
    gSystem->Load("libT0base");
    gSystem->Load("libT0rec");
    gSystem->Load("libCORRFW");
    gSystem->Load("libTENDER");
    gSystem->Load("libTENDERSupplies");
    
    gSystem->Load("libEMCALbase.so");
    gSystem->Load("libEMCALUtils.so");
    gSystem->Load("libEMCALrec.so");
    gSystem->Load("libPWGCaloTrackCorrBase.so");
    gSystem->Load("libPWGCFCorrelationsDPhi.so");
    gSystem->Load("libPWGCFCorrelationsBase.so");
    gSystem->Load("libPWGTools.so");
    
    gSystem->Load("libfastjet");
    gSystem->Load("libsiscone");
    gSystem->Load("libsiscone_spherical");
    gSystem->Load("libfastjetplugins");
    gSystem->Load("libfastjetcontribfragile");
    
    gSystem->Load("libEMCALUtils");
    gSystem->Load("libPWGPPEMCAL");
}





