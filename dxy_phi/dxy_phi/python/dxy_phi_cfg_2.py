import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo") 							# dai il nome al processo

process.load("FWCore.MessageService.MessageLogger_cfi") 			# carichi librerie per messaggi di errori ecc..

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) 	# es 1000 fa 1000 evts, se metto -1 gira su tutte

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("tracksFile2.root"),	# nome del file da creare
                                   #fileName = cms.string("TT_tracksFile2.root"),	# nome del file da creare
                                   #fileName = cms.string("test_fullCUT.root"),	# nome del file da creare
                                   closeFileFast = cms.untracked.bool(False)
                                   )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:myfile.root',  
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/004F7A31-F91E-E611-A9D5-02163E0146A8.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/02016E13-FC1E-E611-92FE-02163E014434.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/0218A0F0-F81E-E611-B156-02163E014768.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/02FC6749-F91E-E611-9C8D-02163E0133AC.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/04C03CFA-F81E-E611-83DB-02163E0143A2.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/0686AFF1-F81E-E611-A28A-02163E0144D7.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/06F3757D-F81E-E611-829C-02163E012B2D.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/08FE5535-F91E-E611-AD6B-02163E01388F.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/0A45557C-FB1E-E611-A3E2-02163E0121F3.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/0AB46FC3-F81E-E611-A142-02163E014293.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/0C367039-F91E-E611-95DD-02163E01399E.root',
        
	#
	#questi 10 presi da: /StreamExpress/Run2016B-TkAlMinBias-Express-v2/ALCARECO run=274241
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/00068562-EA26-E611-B903-02163E01389E.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/000A8739-EA26-E611-82C7-02163E01443E.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/0013E2D6-B626-E611-B215-02163E01361A.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/004A45D8-B626-E611-93E5-02163E01345E.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/0076E6C9-B626-E611-815B-02163E012A35.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/00B7CEE1-B626-E611-80CD-02163E012211.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/00C8A7CA-B626-E611-9F32-02163E01411D.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/00F349E4-B626-E611-825D-02163E014536.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/020DF5D1-B626-E611-AFB7-02163E0141DB.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/023C20D7-B626-E611-8A01-02163E0145C7.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/000763E3-FD26-E611-8C1C-02163E013759.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/008CAAE4-FD26-E611-9FBD-02163E01245C.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/00F1EEDB-FD26-E611-9AD8-02163E012352.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/020AEEF8-FD26-E611-B483-02163E011C6A.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/02482CDC-FD26-E611-9D40-02163E014712.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0278BAF0-FD26-E611-9CD6-02163E0143ED.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/028B7EE7-FD26-E611-AADA-02163E014556.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/02BB7D53-FE26-E611-97E3-02163E01427E.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/043F0ADD-FD26-E611-BD0F-02163E0146B3.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/048E9BD9-FD26-E611-A291-02163E013638.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/06007D2E-FE26-E611-81CE-02163E0144FB.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/069156E2-FD26-E611-9EB4-02163E01413E.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/06A06BDC-FD26-E611-A62D-02163E01389D.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/06FC14E6-FD26-E611-BC4D-02163E0134FA.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/08558FFC-FD26-E611-8151-02163E012032.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/08A6C8D6-FD26-E611-8907-02163E0141BA.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/08C11EED-FD26-E611-A81F-02163E0135D5.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0A2891E9-FD26-E611-8144-02163E012ADF.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0A3C070A-FE26-E611-A969-02163E0146AE.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0A4CD5D6-FD26-E611-A5C1-02163E013957.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0A852E0D-FE26-E611-8AE3-02163E011C1D.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0C3F2FDD-FD26-E611-91E5-02163E0146B3.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0CCC92EC-FD26-E611-9264-02163E0133A8.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0CE9D6D1-FD26-E611-BEB6-02163E012628.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0CEF40E4-FD26-E611-A200-02163E011EE2.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0E646FDF-FD26-E611-87B4-02163E01466F.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0E7808DD-FD26-E611-84C3-02163E01421C.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0E944EE7-FF26-E611-B796-02163E0145A5.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0EA69AEF-FD26-E611-8EA9-02163E0136B1.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0EDEF3F9-FD26-E611-B27B-02163E01372B.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/0EEF67D4-FD26-E611-9046-02163E013589.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/244/00000/102FADED-FD26-E611-9EFF-02163E011D19.root',
	#
	# questi contengono "generalTracks"
	#'/store/relval/CMSSW_8_0_3/RelValTTbar_13/GEN-SIM-RECO/PUpmx25ns_80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/02EEAAC8-3CF0-E511-A2F4-0CC47A78A2EC.root',
	#'/store/relval/CMSSW_8_0_3/RelValTTbar_13/GEN-SIM-RECO/PUpmx25ns_80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/20A0215E-38F0-E511-8AF3-0CC47A4C8E0E.root',
	#'/store/relval/CMSSW_8_0_3/RelValTTbar_13/GEN-SIM-RECO/PUpmx25ns_80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/986396DF-5BF0-E511-AAB2-0025905B8592.root',
	#'/store/relval/CMSSW_8_0_3/RelValTTbar_13/GEN-SIM-RECO/PUpmx25ns_80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/B43EB51C-3BF0-E511-A8E4-0025905A60B0.root',
	#'/store/relval/CMSSW_8_0_3/RelValTTbar_13/GEN-SIM-RECO/PUpmx25ns_80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/BECAE4C5-3AF0-E511-A93B-002618FDA26D.root',
	#'/store/relval/CMSSW_8_0_3/RelValTTbar_13/GEN-SIM-RECO/PUpmx25ns_80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/C0A95FC5-39F0-E511-BCBA-0CC47A4D767E.root',
	#'/store/relval/CMSSW_8_0_3/RelValTTbar_13/GEN-SIM-RECO/PUpmx25ns_80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/C4BED3D6-3BF0-E511-B0F6-0CC47A78A3E8.root',
	#'/store/relval/CMSSW_8_0_3/RelValTTbar_13/GEN-SIM-RECO/PUpmx25ns_80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/C6F254CD-5BF0-E511-8E99-0CC47A78A446.root',
	#'/store/relval/CMSSW_8_0_3/RelValTTbar_13/GEN-SIM-RECO/PUpmx25ns_80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/D251E0FF-3CF0-E511-AD33-0CC47A78A414.root',
	#'/store/relval/CMSSW_8_0_3/RelValTTbar_13/GEN-SIM-RECO/PUpmx25ns_80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/D6814B85-3BF0-E511-9BA2-0CC47A78A414.root',
    )
)

process.demo = cms.EDAnalyzer('dxy_phi', # chiami funzione demo del processo e le dici che analyzer usare
			offlineVtx 	= cms.InputTag("offlinePrimaryVertices"),
			tracks 		= cms.InputTag("generalTracks"),
			#tracks		= cms.InputTag("ALCARECOTkAlMinBias"),
			)		

process.p = cms.Path(process.demo)			# metto in "p" (il vero processo che viene eseguito) l'analyzer giusto che ho definito sopra

