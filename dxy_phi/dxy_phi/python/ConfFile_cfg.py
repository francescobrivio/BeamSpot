import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo") 							# dai il nome al processo

process.load("FWCore.MessageService.MessageLogger_cfi") 			# carichi librerie per messaggi di errori ecc..

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) 	# es 1000 fa 1000 evts, se metto -1 gira su tutte

process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string("tracksFile.root"),	# nome del file da creare
                                   fileName = cms.string("test3.root"),	# nome del file da creare
                                   closeFileFast = cms.untracked.bool(False)
                                   )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:myfile.root',
	#'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/00068562-EA26-E611-B903-02163E01389E.root',
	'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/000A8739-EA26-E611-82C7-02163E01443E.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/06677997-1B1F-E611-8ED0-02163E014391.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/36F95FA3-1B1F-E611-A7A2-02163E0135D6.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/3C1A8F99-3D1F-E611-A8B7-02163E014549.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/52443391-1B1F-E611-B34D-02163E014235.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/64770BBF-1B1F-E611-90C0-02163E012892.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/64B63AA1-1B1F-E611-9904-02163E012037.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/6E786FD2-1B1F-E611-983A-02163E014145.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/88A76FA3-3D1F-E611-92C4-02163E01376A.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/ACDB3890-1B1F-E611-A98C-02163E0133E9.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/C4DC829B-1B1F-E611-899C-02163E011FDC.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/CC46E5B2-1B1F-E611-935C-02163E0118AD.root',
	#'root://xrootd.unl.edu//store/data/Run2016B/ZeroBias/ALCARECO/TkAlMinBias-PromptReco-v2/000/273/502/00000/DA69DD93-1B1F-E611-A5F1-02163E01356C.root',
    )
)

process.demo = cms.EDAnalyzer('dxy_phi', # chiami funzione demo del processo e le dici che analyzer usare
			offlineVtx 	= cms.InputTag("offlinePrimaryVertices"),
			tracks		= cms.InputTag("ALCARECOTkAlMinBias"),
			)		

process.p = cms.Path(process.demo)			# metto in "p" (il vero processo che viene eseguito) l'analyzer giusto che ho definito sopra

