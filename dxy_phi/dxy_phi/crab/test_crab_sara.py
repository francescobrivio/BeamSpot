
from CRABClient.UserUtilities import config
config = config()

config.General.requestName  = 'BcJpsiPiNtuples_2015B_MuonJsonv4_Dimuon16'
config.General.workArea     = '13TeV/'

config.JobType.pluginName   = 'Analysis'
config.JobType.psetName     = 'Bc2JpsiPi_2015B_dimuon16_cfg.py'
config.JobType.outputFiles  = ['dataGrid.root']

config.Data.inputDataset    = '/Charmonium/Run2015B-PromptReco-v1/AOD'
config.Data.inputDBS        = 'global'
config.Data.lumiMask        = 'Cert_246908-251883_13TeV_PromptReco_Collisions15_JSON_MuonPhys_v4.txt'
config.Data.splitting       = 'LumiBased'
config.Data.unitsPerJob     = 40
config.Data.outLFNDirBase   = '/store/user/fiorendi/BPH_data13TeV_ntuple/' # or '/store/group/<subdir>'

config.Site.storageSite     = 'T2_CH_CERN'
