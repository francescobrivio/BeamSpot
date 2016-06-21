import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo") 							# dai il nome al processo

process.load("FWCore.MessageService.MessageLogger_cfi") 			# carichi librerie per messaggi di errori ecc..

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) 	# es 1000 fa 1000 evts, se metto -1 gira su tutte

runNumber = str(int(274971))
process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string("tracksFile.root"),		# nome del file da creare
                                   #fileName = cms.string("MC_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("TT_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("d0_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("IPs_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string(runNumber+"_tracksFile.root"),	# nome del file da creare
                                   fileName = cms.string(runNumber+"_dZ_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("event_tracksFile.root"),	# nome del file da creare
                                   closeFileFast = cms.untracked.bool(False)
                                   )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:myfile.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0030D672-D032-E611-AEAD-02163E0120EB.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/00339125-CE32-E611-BB6E-02163E012492.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0036A5F1-CC32-E611-8DFC-02163E01422B.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/00B490B4-CD32-E611-9EBC-02163E013516.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/023EDBBC-D032-E611-9215-02163E0143D6.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0400ED04-D132-E611-9CB0-02163E013411.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/040488BA-CC32-E611-9276-02163E011883.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0411DBFA-CC32-E611-86E6-02163E013616.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0625CF45-CD32-E611-AB05-02163E0143DC.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/065AA3F6-CC32-E611-B8D7-02163E011DB8.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/08C76CF0-B332-E611-AFDE-02163E0134D3.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/08D6398E-D032-E611-894B-02163E011D14.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0A2E8B40-CD32-E611-81F8-02163E012043.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0C20DD63-CD32-E611-8F9C-02163E013756.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0C4A35CC-CE32-E611-A6C0-02163E014151.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0CFABBAE-CE32-E611-BD87-02163E014536.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0E8FB55B-CD32-E611-95C6-02163E013786.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0EBB4E57-C632-E611-B7AE-02163E0123A7.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/0EE0D07A-D332-E611-ADC3-02163E0137E5.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/106E7B54-CE32-E611-9494-02163E012114.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/10BFD13A-D232-E611-B16D-02163E0142A2.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/123AF5C9-CF32-E611-B203-02163E013555.root',
	'/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/971/00000/14AFA4A0-CD32-E611-BD37-02163E011EE5.root',
	)
)

process.demo = cms.EDAnalyzer('dxy_phi', # chiami funzione demo del processo e le dici che analyzer usare
			offlineVtx 	= cms.InputTag("offlinePrimaryVertices"),
			tracks 		= cms.InputTag("generalTracks"),
			beamSpot	= cms.InputTag("offlineBeamSpot"),
			#tracks		= cms.InputTag("ALCARECOTkAlMinBias"),
			)		

process.p = cms.Path(process.demo)			# metto in "p" (il vero processo che viene eseguito) l'analyzer giusto che ho definito sopra

