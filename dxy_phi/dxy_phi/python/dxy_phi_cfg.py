import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo") 							# dai il nome al processo

process.load("FWCore.MessageService.MessageLogger_cfi") 			# carichi librerie per messaggi di errori ecc..

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) 	# es 1000 fa 1000 evts, se metto -1 gira su tutte

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("tracksFile.root"),	# nome del file da creare
                                   #fileName = cms.string("test.root"),	# nome del file da creare
                                   closeFileFast = cms.untracked.bool(False)
                                   )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:myfile.root',  questi 10 presi da: /StreamExpress/Run2016B-TkAlMinBias-Express-v2/ALCARECO run=274241
	'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/00068562-EA26-E611-B903-02163E01389E.root',
	'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/000A8739-EA26-E611-82C7-02163E01443E.root',
	'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/0013E2D6-B626-E611-B215-02163E01361A.root',
	'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/004A45D8-B626-E611-93E5-02163E01345E.root',
	'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/0076E6C9-B626-E611-815B-02163E012A35.root',
	'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/00B7CEE1-B626-E611-80CD-02163E012211.root',
	'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/00C8A7CA-B626-E611-9F32-02163E01411D.root',
	'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/00F349E4-B626-E611-825D-02163E014536.root',
	'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/020DF5D1-B626-E611-AFB7-02163E0141DB.root',
	'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v2/000/274/241/00000/023C20D7-B626-E611-8A01-02163E0145C7.root',
    )
)

process.demo = cms.EDAnalyzer('dxy_phi', # chiami funzione demo del processo e le dici che analyzer usare
			offlineVtx 	= cms.InputTag("offlinePrimaryVertices"),
			tracks		= cms.InputTag("ALCARECOTkAlMinBias"),
			)		

process.p = cms.Path(process.demo)			# metto in "p" (il vero processo che viene eseguito) l'analyzer giusto che ho definito sopra

