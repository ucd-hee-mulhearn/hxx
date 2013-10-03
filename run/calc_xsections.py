#!/usr/bin/python

# Branching Ratios:  From PDG

# Assumes mH=120 GeV
BR_H_ZZ = 1.59E-02 
BR_H_WW = 1.41E-01

# Z->l+l-  : 3.37 * 2%  = 0.0674
BR_Z_LL = 0.0674

# Z->v v~  : 20.0%      = 0.200
BR_Z_VV = 0.200

# Z->j j   : 69.9%      = 0.699
BR_Z_JJ = 0.699

# W->l v   : 10.8 * 2%  = 0.216
BR_W_LV = 0.216

# W->j j   : 67.60%     = 0.676
BR_W_JJ = 0.6760

# Cross-sections:  From Madgraph
# Note:  for processes including decays, use only in ratios...
#
# Madgraph reports xsec in **pb**
PB_TO_FB = 1E3

MG_Z   = 4.819E4
MG_ZJJ = 5857
MG_ZBB = 860.7
MG_ZJJ_MLL_GT_80 = 194.8
MG_ZJJ_MLL_LT_80 = 4.792
MG_ZJJ_MLL_TOT   = MG_ZJJ_MLL_GT_80 + MG_ZJJ_MLL_LT_80

#
# K-Factors (Needed!)
#

K_Z   = 1

#
# Cross-sections derived from MG plus K-Factors:
#

SIGMA_ZJJ           = MG_ZJJ * K_Z * PB_TO_FB
SIGMA_ZJJ_MLL_LT_80 = SIGMA_ZJJ * MG_ZJJ_MLL_LT_80 / MG_ZJJ_MLL_TOT;
SIGMA_ZJJ_MLL_GT_80 = SIGMA_ZJJ * MG_ZJJ_MLL_GT_80 / MG_ZJJ_MLL_TOT;






# From Daniel, in pb
#
# Proc    8tev 14tev
# gg->H   20.9   53.5
# Wh       1.0   1.5
# Zh       0.1   0.9
# ttbar    135   554

SIGMA_H   =  53500
SIGMA_WH  =   1500
SIGMA_ZH  =    900
SIGMA_TT  = 554000

# NEEDS WORK:

# WWjj / WW
R_WWJJ_WW = 0.1


SIGMA_WZ  = 1E5
SIGMA_ZZ  = 1E5
SIGMA_WW  = 1E5


SIGMA_HXX = 1E4

#Missing Backgrounds:
#VBF Higgs,
#ttH,
#H->WW + jets,
#Fakes,

print "Sigma x BR in fb at at 14 TeV"
print ""
print "Backgrounds:  "
print ""
print "Zjj  -> lljj     ........................", SIGMA_ZJJ * BR_Z_LL
print "  mll < 80 GeV   ........................", SIGMA_ZJJ_MLL_LT_80 * BR_Z_LL
print "  mll > 80 GeV   ........................", SIGMA_ZJJ_MLL_GT_80 * BR_Z_LL
print ""
print "tt   -> lvlvbb ........................", SIGMA_TT * BR_W_LV *  BR_W_LV
print ""
print "ZW   -> lljj   ........................", SIGMA_WZ * BR_Z_LL * BR_W_JJ
print "ZZ   -> lljj   ........................", SIGMA_WZ * BR_Z_LL * BR_Z_JJ * 2
print "WWjj -> lvlvjj ........................", SIGMA_WW * R_WWJJ_WW * BR_W_LV * BR_W_LV
print ""
print "H -> ZZ -> lljj .......................", SIGMA_H * BR_H_ZZ * BR_Z_LL * BR_Z_JJ * 2
print ""
print "ZH, Z->VV, H -> ZZ -> lljj ............", SIGMA_ZH * BR_H_ZZ * BR_Z_VV * BR_Z_LL * BR_Z_JJ * 2
print ""
print "WH, W->LV, H -> ZZ -> lljj ............", SIGMA_WH * BR_H_ZZ * BR_W_LV * BR_Z_LL * BR_Z_JJ * 2
print ""
print "Signal:  "
print ""
print "Hxx            ........................", SIGMA_HXX 
print "Hxx, H->ZZ->lljj ......................", SIGMA_HXX * BR_H_ZZ * BR_Z_LL * BR_Z_JJ * 2
print ""
print "Missing Backgrounds:  "
print ""

