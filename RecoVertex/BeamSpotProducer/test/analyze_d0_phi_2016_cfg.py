import FWCore.ParameterSet.Config as cms

process = cms.Process("d0phi")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("RecoVertex.BeamSpotProducer.d0_phi_analyzer_cff")

#from list272798 import files
process.source = cms.Source("PoolSource",
                   fileNames = cms.untracked.vstring(
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/04F3D18E-4C14-E611-BA18-02163E011AA7.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/088F736D-4F14-E611-BE5B-02163E01421A.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/0ACABE6C-4F14-E611-9AE4-02163E0143F1.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/101D4867-4F14-E611-A373-02163E011CDC.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/14BD849D-4C14-E611-9C43-02163E01411F.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/1612A0B2-4C14-E611-887C-02163E014149.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/16141B4E-5214-E611-8FA1-02163E0140E2.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/164A6790-4C14-E611-A4F0-02163E011AB9.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/16AC3493-4C14-E611-B62F-02163E0138AB.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/16BC0552-5214-E611-8C2C-02163E014164.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/16E9C852-5214-E611-8FE7-02163E01236F.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/1A6553ED-5214-E611-ACC7-02163E012247.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/1CA3A2E7-5514-E611-8460-02163E01462B.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/20E0AB78-4D14-E611-BF3D-02163E01293F.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/2A773689-5214-E611-A5ED-02163E01431D.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/2CD48966-4F14-E611-B796-02163E01345F.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/2EDC9F4D-5214-E611-9AC9-02163E011C1C.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/36AAB163-4F14-E611-BFD6-02163E01433B.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/38D7B078-4D14-E611-A894-02163E01293F.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/3AD1F592-4C14-E611-9D6E-02163E0142CD.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/426E0BB5-4C14-E611-9D98-02163E0119B1.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/44A97A49-5214-E611-847E-02163E014651.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/547AA8AD-5214-E611-AF81-02163E0146D2.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/5809844E-5214-E611-A116-02163E0143B2.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/5A940C4D-5214-E611-A36E-02163E012228.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/5C85EC79-4D14-E611-AAB8-02163E0139C1.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/6282D469-4F14-E611-B35B-02163E0143E8.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/6ACAC626-5514-E611-BFE7-02163E014480.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/6AF4D45A-5214-E611-A701-02163E011E1B.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/7217C380-4F14-E611-B7F7-02163E01393D.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/72AAB476-4D14-E611-AEC4-02163E011D55.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/7800A96A-4F14-E611-95A5-02163E014208.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/7ABEE83A-5214-E611-AEF2-02163E0133D1.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/7EE92865-4F14-E611-864D-02163E0136B2.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/80D97C10-5414-E611-BC2D-02163E01456D.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/8667C850-5214-E611-A921-02163E01411E.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/8CB8A576-4D14-E611-BEA3-02163E011D55.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/9036A6E9-5214-E611-8C56-02163E014208.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/9866788A-5214-E611-9325-02163E012444.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/9A654373-4D14-E611-B767-02163E011AB9.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/9C538078-4D14-E611-AD51-02163E011D07.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/9ED27B6A-4D14-E611-96B5-02163E011AA7.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/A43BA96C-4F14-E611-8BC6-02163E0143F1.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/ACEE7631-5214-E611-BB9D-02163E011CDC.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/BCB1DE87-5214-E611-A59D-02163E0118C8.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/C06C8679-4F14-E611-A3B5-02163E013590.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/CC4C6E6D-5014-E611-B9B3-02163E0133C2.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/CE63D9EB-5214-E611-A841-02163E0145EB.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/CEBEBD69-4F14-E611-9495-02163E0134A7.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/D4051973-5214-E611-9F70-02163E012B6B.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/D88F9066-4F14-E611-9D3D-02163E0135B7.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/DE82FE79-4D14-E611-A615-02163E0139C1.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/DEE6B769-4F14-E611-8FAE-02163E0134A7.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/E0C94643-5214-E611-A067-02163E011E69.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/E0D1ED5F-4F14-E611-A2A7-02163E014111.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/E2EE9868-4F14-E611-8D48-02163E011CDC.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/F0FD2E65-4F14-E611-A272-02163E0136B2.root',
'/store/express/Run2016B/StreamExpress/ALCARECO/TkAlMinBias-Express-v1/000/272/785/00000/FEC97CEE-5214-E611-B770-02163E0138AF.root',
  )
)

process.maxEvents = cms.untracked.PSet(
                                       input = cms.untracked.int32(-1) #1500
                                      )

process.options   = cms.untracked.PSet(
                                       wantSummary = cms.untracked.bool(False)
                                      )

# this is for filtering on L1 technical trigger bit
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')

process.hltLevel1GTSeed.L1TechTriggerSeeding     = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND ( 40 OR 41 )')

#### remove beam scraping events
process.noScraping = cms.EDFilter(
                                  "FilterOutScraping",
                      applyfilter = cms.untracked.bool(True) ,
                      debugOn     = cms.untracked.bool(False), ## Or 'True' to get some per-event info
                      numtrack    = cms.untracked.uint32(10) ,
                      thresh      = cms.untracked.double(0.20)
                                 )

#process.p = cms.Path(process.hltLevel1GTSeed + process.d0_phi_analyzer)
process.p = cms.Path(process.d0_phi_analyzer)
process.MessageLogger.debugModules = ['BeamSpotAnalyzer']

#######################

process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# run over STA muons
process.d0_phi_analyzer.BeamFitter.TrackCollection = cms.untracked.InputTag('ALCARECOTkAlMinBias') #,'UpdatedAtVtx')

process.d0_phi_analyzer.BeamFitter.WriteAscii                = True
process.d0_phi_analyzer.BeamFitter.AsciiFileName             = 'TkAlMinBias_Express_v1_ez3_dydz00002.txt'
process.d0_phi_analyzer.BeamFitter.Debug                     = cms.untracked.bool(True)
process.d0_phi_analyzer.BeamFitter.InputBeamWidth            = -1
process.d0_phi_analyzer.BeamFitter.MaximumImpactParameter    = 1.0  
process.d0_phi_analyzer.BeamFitter.MaximumNormChi2           = 10
process.d0_phi_analyzer.BeamFitter.MinimumInputTracks        = 50   
process.d0_phi_analyzer.BeamFitter.MinimumPt                 = 1.0
process.d0_phi_analyzer.BeamFitter.MinimumTotalLayers        = 6
process.d0_phi_analyzer.BeamFitter.MinimumPixelLayers        = -1

process.d0_phi_analyzer.BeamFitter.OutputFileName            = 'TkAlMinBias_Express_v1_ez3_dydz00002.root' #AtVtx10000.root'
process.d0_phi_analyzer.BeamFitter.TrackAlgorithm            = cms.untracked.vstring()
process.d0_phi_analyzer.BeamFitter.SaveFitResults            = True
process.d0_phi_analyzer.BeamFitter.SaveNtuple                = True
process.d0_phi_analyzer.BeamFitter.SavePVVertices            = True

process.d0_phi_analyzer.BeamFitter.MaximumZ                  = 60
process.d0_phi_analyzer.BeamFitter.FractionOfFittedTrks      = 0.9

# process.d0_phi_analyzer.BeamFitter.BunchCrossings            = cms.untracked.vdouble(1)


process.d0_phi_analyzer.PVFitter.Apply3DFit                  = True
process.d0_phi_analyzer.PVFitter.minNrVerticesForFit         = 10
process.d0_phi_analyzer.PVFitter.nSigmaCut                   = 50.0


# fit as function of lumi sections
process.d0_phi_analyzer.BSAnalyzerParameters.fitEveryNLumi   = 1
process.d0_phi_analyzer.BSAnalyzerParameters.resetEveryNLumi = 1
