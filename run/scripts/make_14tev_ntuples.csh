source COMPILE

#setenv MAXEVENTA 1000000 
#setenv MAXEVENTB 100000

setenv MAXEVENTA 1000 
setenv MAXEVENTB 1000

rm data/analysis/14tev/*.root   ######  DELETING FILES HERE #####

# Using lumi in fb, xsec in fb^-1

./bin/MakeHxxTree --maxevent=$MAXEVENTB --sample=8 --lumi=300 --xsec=7951000    data/analysis/14tev/wjjj.root \
data/delphes/wjjj/run_*_14TeV/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTA --sample=1 --lumi=300 --xsec=552666    data/analysis/14tev/zjj.root \
data/delphes/zjj/run_14tev/tag_*_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=2 --lumi=300 --xsec=1587    data/analysis/14tev/zz_lljj.root \
data/delphes/zz_lljj/run_100K_14TeV/tag_*_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=2 --lumi=300 --xsec=2400     data/analysis/14tev/zw_lljj.root \
data/delphes/zw_lljj/run_100K_14TeV/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=3 --lumi=300 --xsec=2737     data/analysis/14tev/wwjj.root \
data/delphes/wwjj_lvlvjj/run_100K_14TeV/tag_*_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTA --sample=4 --lumi=300 --xsec=25847      data/analysis/14tev/tt.root \
data/delphes/tt/run_100K_14TeV/tag_*_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=5 --lumi=300 --xsec=80.15    data/analysis/14tev/h_zz_lljj.root \
data/delphes/h_lljj/run_14tev/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=6 --lumi=300 --xsec=0.2696  data/analysis/14tev/zh_vvlljj.root \
data/delphes/zh_lljjvv/run_14tev/tag_*_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=7 --lumi=300 --xsec=0.4346   data/analysis/14tev/wh_vllljj.root \
data/delphes/wh_jjllvv/run_14tev/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=20 --lumi=300 --xsec=149.8   data/analysis/14tev/hxx_lljjxx_mchi_1.root \
data/delphes/pass2_hxx_lljjxx/run_14tev_mchi1/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=21 --lumi=300 --xsec=149.8   data/analysis/14tev/hxx_lljjxx_mchi_10.root \
data/delphes/pass2_hxx_lljjxx/run_14tev_mchi10/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=22 --lumi=300 --xsec=149.8   data/analysis/14tev/hxx_lljjxx_mchi_100.root \
data/delphes/pass2_hxx_lljjxx/run_14tev_mchi100/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=23 --lumi=300 --xsec=149.8   data/analysis/14tev/hxx_lljjxx_mchi_500.root \
data/delphes/pass2_hxx_lljjxx/run_14tev_mchi500/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=24 --lumi=300 --xsec=149.8   data/analysis/14tev/hxx_lljjxx_mchi_1000.root \
data/delphes/pass2_hxx_lljjxx/run_14tev_mchi1000/tag_*_delphes_events.root

# hzp model:

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=30 --lumi=300 --xsec=149.8   data/analysis/14tev/hzp_mzp100_mchi1.root \
data/delphes/hzp/run_14tev_mzp100_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=31 --lumi=300 --xsec=149.8   data/analysis/14tev/hzp_mzp100_mchi10.root \
data/delphes/hzp/run_14tev_mzp100_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=32 --lumi=300 --xsec=149.8   data/analysis/14tev/hzp_mzp100_mchi100.root \
data/delphes/hzp/run_14tev_mzp100_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=33 --lumi=300 --xsec=149.8   data/analysis/14tev/hzp_mzp100_mchi500.root \
data/delphes/hzp/run_14tev_mzp100_mchi500/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=34 --lumi=300 --xsec=149.8   data/analysis/14tev/hzp_mzp100_mchi1000.root \
data/delphes/hzp/run_14tev_mzp100_mchi1000/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=35 --lumi=300 --xsec=149.8   data/analysis/14tev/hzp_mzp1000_mchi1.root \
data/delphes/hzp/run_14tev_mzp1000_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=36 --lumi=300 --xsec=149.8   data/analysis/14tev/hzp_mzp1000_mchi10.root \
data/delphes/hzp/run_14tev_mzp1000_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=37 --lumi=300 --xsec=149.8   data/analysis/14tev/hzp_mzp1000_mchi100.root \
data/delphes/hzp/run_14tev_mzp1000_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=38 --lumi=300 --xsec=149.8   data/analysis/14tev/hzp_mzp1000_mchi500.root \
data/delphes/hzp/run_14tev_mzp1000_mchi500/tag_1_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=39 --lumi=300 --xsec=149.8   data/analysis/14tev/hzp_mzp1000_mchi1000.root \
data/delphes/hzp/run_14tev_mzp1000_mchi1000/tag_1_delphes_events.root

# hzpzp model:

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=40 --lumi=300 --xsec=149.8   data/analysis/14tev/hzpzp_mzp100_mchi1.root \
data/delphes/hzpzp/run_14tev_mzp100_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=41 --lumi=300 --xsec=149.8   data/analysis/14tev/hzpzp_mzp100_mchi10.root \
data/delphes/hzpzp/run_14tev_mzp100_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=42 --lumi=300 --xsec=149.8   data/analysis/14tev/hzpzp_mzp100_mchi100.root \
data/delphes/hzpzp/run_14tev_mzp100_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=43 --lumi=300 --xsec=149.8   data/analysis/14tev/hzpzp_mzp100_mchi500.root \
data/delphes/hzpzp/run_14tev_mzp100_mchi500/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=44 --lumi=300 --xsec=149.8   data/analysis/14tev/hzpzp_mzp100_mchi1000.root \
data/delphes/hzpzp/run_14tev_mzp100_mchi1000/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=45 --lumi=300 --xsec=149.8   data/analysis/14tev/hzpzp_mzp1000_mchi1.root \
data/delphes/hzpzp/run_14tev_mzp1000_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=46 --lumi=300 --xsec=149.8   data/analysis/14tev/hzpzp_mzp1000_mchi10.root \
data/delphes/hzpzp/run_14tev_mzp1000_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=47 --lumi=300 --xsec=149.8   data/analysis/14tev/hzpzp_mzp1000_mchi100.root \
data/delphes/hzpzp/run_14tev_mzp1000_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=48 --lumi=300 --xsec=149.8   data/analysis/14tev/hzpzp_mzp1000_mchi500.root \
data/delphes/hzpzp/run_14tev_mzp1000_mchi500/tag_1_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=49 --lumi=300 --xsec=149.8   data/analysis/14tev/hzpzp_mzp1000_mchi1000.root \
data/delphes/hzpzp/run_14tev_mzp1000_mchi1000/tag_1_delphes_events.root


# hsc model:


./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=50 --lumi=300 --xsec=149.8   data/analysis/14tev/hsc_mzp100_mchi1.root \
data/delphes/hsc/run_14tev_mzp100_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=51 --lumi=300 --xsec=149.8   data/analysis/14tev/hsc_mzp100_mchi10.root \
data/delphes/hsc/run_14tev_mzp100_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=52 --lumi=300 --xsec=149.8   data/analysis/14tev/hsc_mzp100_mchi100.root \
data/delphes/hsc/run_14tev_mzp100_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=53 --lumi=300 --xsec=149.8   data/analysis/14tev/hsc_mzp100_mchi500.root \
data/delphes/hsc/run_14tev_mzp100_mchi500/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=54 --lumi=300 --xsec=149.8   data/analysis/14tev/hsc_mzp100_mchi1000.root \
data/delphes/hsc/run_14tev_mzp100_mchi1000/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=55 --lumi=300 --xsec=149.8   data/analysis/14tev/hsc_mzp1000_mchi1.root \
data/delphes/hsc/run_14tev_mzp1000_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=56 --lumi=300 --xsec=149.8   data/analysis/14tev/hsc_mzp1000_mchi10.root \
data/delphes/hsc/run_14tev_mzp1000_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=57 --lumi=300 --xsec=149.8   data/analysis/14tev/hsc_mzp1000_mchi100.root \
data/delphes/hsc/run_14tev_mzp1000_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=58 --lumi=300 --xsec=149.8   data/analysis/14tev/hsc_mzp1000_mchi500.root \
data/delphes/hsc/run_14tev_mzp1000_mchi500/tag_1_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=59 --lumi=300 --xsec=149.8   data/analysis/14tev/hsc_mzp1000_mchi1000.root \
data/delphes/hsc/run_14tev_mzp1000_mchi1000/tag_1_delphes_events.root


# hhxx_combined

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=60 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_combined_mchi1.root \
data/delphes/hhxx_combined/run_14tev_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=61 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_combined_mchi10.root \
data/delphes/hhxx_combined/run_14tev_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=62 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_combined_mchi100.root \
data/delphes/hhxx_combined/run_14tev_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=63 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_combined_mchi500.root \
data/delphes/hhxx_combined/run_14tev_mchi500/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=64 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_combined_mchi1000.root \
data/delphes/hhxx_combined/run_14tev_mchi1000/tag_1_delphes_events.root 

# hhxx_scalar

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=65 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_scalar_mchi1.root \
data/delphes/hhxx_scalar/run_14tev_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=66 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_scalar_mchi10.root \
data/delphes/hhxx_scalar/run_14tev_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=67 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_scalar_mchi100.root \
data/delphes/hhxx_scalar/run_14tev_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=68 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_scalar_mchi500.root \
data/delphes/hhxx_scalar/run_14tev_mchi500/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=69 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_scalar_mchi1000.root \
data/delphes/hhxx_scalar/run_14tev_mchi1000/tag_1_delphes_events.root 


# hhxx_scalar

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=65 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_scalar_mchi1.root \
data/delphes/hhxx_scalar/run_14tev_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=66 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_scalar_mchi10.root \
data/delphes/hhxx_scalar/run_14tev_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=67 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_scalar_mchi100.root \
data/delphes/hhxx_scalar/run_14tev_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=68 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_scalar_mchi500.root \
data/delphes/hhxx_scalar/run_14tev_mchi500/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=69 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxx_scalar_mchi1000.root \
data/delphes/hhxx_scalar/run_14tev_mchi1000/tag_1_delphes_events.root 


# hhxg5x

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=70 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxg5x_mchi1.root \
data/delphes/hhxg5x/run_14tev_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=71 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxg5x_mchi10.root \
data/delphes/hhxg5x/run_14tev_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=72 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxg5x_mchi100.root \
data/delphes/hhxg5x/run_14tev_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=73 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxg5x_mchi500.root \
data/delphes/hhxg5x/run_14tev_mchi500/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=74 --lumi=300 --xsec=149.8   data/analysis/14tev/hhxg5x_mchi1000.root \
data/delphes/hhxg5x/run_14tev_mchi1000/tag_1_delphes_events.root 


# xdx

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=75 --lumi=300 --xsec=149.8   data/analysis/14tev/xdx_mchi1.root \
data/delphes/xdx/run_14tev_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=76 --lumi=300 --xsec=149.8   data/analysis/14tev/xdx_mchi10.root \
data/delphes/xdx/run_14tev_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=77 --lumi=300 --xsec=149.8   data/analysis/14tev/xdx_mchi100.root \
data/delphes/xdx/run_14tev_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=78 --lumi=300 --xsec=149.8   data/analysis/14tev/xdx_mchi500.root \
data/delphes/xdx/run_14tev_mchi500/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=79 --lumi=300 --xsec=149.8   data/analysis/14tev/xdx_mchi1000.root \
data/delphes/xdx/run_14tev_mchi1000/tag_1_delphes_events.root 


# xgx

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=80 --lumi=300 --xsec=149.8   data/analysis/14tev/xgx_mchi1.root \
data/delphes/xgx/run_14tev_mchi1/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=81 --lumi=300 --xsec=149.8   data/analysis/14tev/xgx_mchi10.root \
data/delphes/xgx/run_14tev_mchi10/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=82 --lumi=300 --xsec=149.8   data/analysis/14tev/xgx_mchi100.root \
data/delphes/xgx/run_14tev_mchi100/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=83 --lumi=300 --xsec=149.8   data/analysis/14tev/xgx_mchi500.root \
data/delphes/xgx/run_14tev_mchi500/tag_1_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=84 --lumi=300 --xsec=149.8   data/analysis/14tev/xgx_mchi1000.root \
data/delphes/xgx/run_14tev_mchi1000/tag_1_delphes_events.root 








pushd data/analysis/14tev
if (-e all.root) rm all.root
hadd all.root *.root
popd
