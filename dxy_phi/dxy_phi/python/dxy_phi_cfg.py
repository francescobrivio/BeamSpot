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
                                   fileName = cms.string(runNumber+"_transient_tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("event_tracksFile.root"),	# nome del file da creare
                                   closeFileFast = cms.untracked.bool(False)
                                   )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:myfile.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/007472D2-9B31-E611-842C-02163E014576.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/00D91429-9331-E611-A15C-02163E011E3B.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/028F41ED-9431-E611-8712-02163E013866.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/043D051E-9B31-E611-925F-02163E012037.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/04520405-9131-E611-9E2D-02163E0144E4.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/04BF38BC-AB31-E611-BC9F-02163E01385F.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/060FF599-AB31-E611-B4D2-02163E0135BD.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/087670FE-8031-E611-800E-02163E01357D.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/0E4E9E9E-8E31-E611-BFC3-02163E0143E3.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/0ED5774E-9731-E611-9436-02163E014295.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/101F4BE5-9531-E611-B530-02163E011920.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/10DF90BC-9031-E611-A21D-02163E014380.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/10ED24B3-9D31-E611-A576-02163E01350E.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/128C9F6B-7E31-E611-B33F-02163E01356C.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/140C8C7B-8231-E611-B4DD-02163E01447E.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/1420BC66-9931-E611-BC88-02163E0124CA.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/14290587-9531-E611-BD31-02163E012B9E.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/18188091-9A31-E611-AF3F-02163E0134A1.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/18C14BBC-9131-E611-A2D3-02163E0145A5.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/1AA0233B-9631-E611-95A1-02163E011D19.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/1AD9208C-9131-E611-97D1-02163E014605.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/1CC78C61-9231-E611-9A60-02163E01380A.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/208504DE-9531-E611-9370-02163E013892.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/22650138-9431-E611-B85C-02163E012A9F.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/22DF8DC6-9A31-E611-9B4A-02163E011EAC.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/243727DA-9831-E611-B5A3-02163E0128B3.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/24BA46BB-9731-E611-80BB-02163E01437E.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/2A04FE92-9031-E611-AC53-02163E0142E2.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/2A65F512-9531-E611-A276-02163E011E38.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/2A83CD09-9E31-E611-AB47-02163E014270.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/2AA81242-8831-E611-BEC1-02163E01435F.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/2ACE7DE9-8131-E611-BD3C-02163E0134F2.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/2CE4F8F7-9431-E611-8F0A-02163E011BE8.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/2CEC4A01-9631-E611-B8AC-02163E014601.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/2E88E69E-9131-E611-9857-02163E011A7D.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/2EAD462E-8731-E611-809D-02163E011866.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/30707D1F-9F31-E611-BE03-02163E01183D.root',
        '/store/data/Run2016B/ZeroBias/RECO/PromptReco-v2/000/274/959/00000/30744955-8031-E611-8C84-02163E014528.root',
	)
)

process.demo = cms.EDAnalyzer('dxy_phi', # chiami funzione demo del processo e le dici che analyzer usare
			offlineVtx 	= cms.InputTag("offlinePrimaryVertices"),
			tracks 		= cms.InputTag("generalTracks"),
			beamSpot	= cms.InputTag("offlineBeamSpot"),
			#tracks		= cms.InputTag("ALCARECOTkAlMinBias"),
			)		

process.p = cms.Path(process.demo)			# metto in "p" (il vero processo che viene eseguito) l'analyzer giusto che ho definito sopra

