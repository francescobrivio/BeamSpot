import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo") 							# dai il nome al processo

process.load("FWCore.MessageService.MessageLogger_cfi") 			# carichi librerie per messaggi di errori ecc..

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(20000) ) 	# es 1000 fa 1000 evts, se metto -1 gira su tutte

process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string("tracksFile.root"),		# nome del file da creare
                                   #fileName = cms.string("MC_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("TT_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("d0_tracksFile.root"),	# nome del file da creare
                                   fileName = cms.string("IPs_tracksFile2.root"),	# nome del file da creare
                                   #fileName = cms.string("event_tracksFile.root"),	# nome del file da creare
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
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/0C533DD1-F91E-E611-9277-02163E01457D.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/10010562-F91E-E611-B3ED-02163E014530.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/14EE9C93-D01E-E611-BEEF-02163E014594.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/502/00000/16F1FBDE-D01E-E611-BF62-02163E014736.root',
    )
)

process.demo = cms.EDAnalyzer('dxy_phi', # chiami funzione demo del processo e le dici che analyzer usare
			offlineVtx 	= cms.InputTag("offlinePrimaryVertices"),
			tracks 		= cms.InputTag("generalTracks"),
			beamSpot	= cms.InputTag("offlineBeamSpot"),
			#tracks		= cms.InputTag("ALCARECOTkAlMinBias"),
			)		

process.p = cms.Path(process.demo)			# metto in "p" (il vero processo che viene eseguito) l'analyzer giusto che ho definito sopra

