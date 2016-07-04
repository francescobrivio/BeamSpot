import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo") 							# dai il nome al processo

process.load("FWCore.MessageService.MessageLogger_cfi") 			# carichi librerie per messaggi di errori ecc..
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = '80X_dataRun2_Prompt_v8'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) 	# es 1000 fa 1000 evts, se metto -1 gira su tutte

runNumber = str(int(274959))
process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string("tracksFile.root"),		# nome del file da creare
                                   #fileName = cms.string("MC_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("TT_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("d0_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("IPs_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string(runNumber+"_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string(runNumber+"_transient_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("event_tracksFile.root"),	# nome del file da creare
				   fileName = cms.string("runs_tracksFile.root"),
                                   closeFileFast = cms.untracked.bool(False)
                                   )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:myfile.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/150/00000/00639F04-D919-E611-889A-02163E014142.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/291/00000/0C26ADB0-221A-E611-9B38-02163E01262F.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/273/730/00000/6016578E-6D21-E611-917C-02163E01361C.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/344/00000/DA4B3435-992B-E611-81A3-02163E013468.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/982/00000/3ED2DD73-0A33-E611-BA28-02163E0128A9.root',
	)
)

process.demo = cms.EDAnalyzer('dxy_phi', # chiami funzione demo del processo e le dici che analyzer usare
			offlineVtx 	= cms.InputTag("offlinePrimaryVertices"),
			tracks 		= cms.InputTag("generalTracks"),
			beamSpot	= cms.InputTag("offlineBeamSpot"),
			#tracks		= cms.InputTag("ALCARECOTkAlMinBias"),
			)		

process.p = cms.Path(process.demo)			# metto in "p" (il vero processo che viene eseguito) l'analyzer giusto che ho definito sopra

