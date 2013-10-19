source COMPILE

# set to zero for all, non-zero to put cap on number output
setenv MAXEVENTA 100000 # not used yet ... for stat limited channels in final plost ...
setenv MAXEVENTB 100000

rm data/analysis/8tev/*.root   ######  DELETING FILES HERE #####

# Using lumi in fb, xsec in fb^-1

./bin/MakeHxxTree --maxevent=$MAXEVENTB --sample=8 --lumi=20 --xsec=2553000    data/analysis/8tev/wjjj.root \
data/delphes_3day/wjjj/run_*_8TeV/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=1 --lumi=20 --xsec=206176    data/analysis/8tev/zjj_mll_gt_80.root \
data/delphes/zjj/run_8tev/tag_*_delphes_events.root

#./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=1 --lumi=20 --xsec=145020    data/analysis/8tev/zjj_mll_gt_80.root \
#./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=1 --lumi=20 --xsec=2249     data/analysis/8tev/zjj_mll_lt_80.root \
#data/delphes_3day/zjj/run_100K_8TeV_MLL_LT_80/tag_*_delphes_events.root \

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=2 --lumi=20 --xsec=741.8    data/analysis/8tev/zz_lljj.root \
data/delphes_3day/zz_lljj/run_100K_8TeV/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=2 --lumi=20 --xsec=1055     data/analysis/8tev/zw_lljj.root \
data/delphes_3day/zw_lljj/run_100K_8TeV/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=3 --lumi=20 --xsec=744.5     data/analysis/8tev/wwjj.root \
data/delphes_3day/wwjj_lvlvjj/run_100K_8TeV/tag_1_delphes_events.root \
data/delphes_3day/wwjj_lvlvjj/run_100K_8TeV/tag_2_delphes_events.root \
data/delphes_3day/wwjj_lvlvjj/run_100K_8TeV/tag_3_delphes_events.root \
data/delphes_3day/wwjj_lvlvjj/run_100K_8TeV/tag_4_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=4 --lumi=20 --xsec=6298      data/analysis/8tev/tt.root \
data/delphes_3day/tt/run_100K_8TeV/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=5 --lumi=20 --xsec=31.31    data/analysis/8tev/h_zz_lljj.root \
data/delphes/h_lljj/run_8tev/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=6 --lumi=20 --xsec=0.02996  data/analysis/8tev/zh_lljjvv.root \
data/delphes/zh_lljjvv/run_8tev/tag_1_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=7 --lumi=20 --xsec=0.2897   data/analysis/8tev/wh_vllljj.root \
data/delphes/wh_jjllvv/run_8tev/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=20 --lumi=20 --xsec=149.8   data/analysis/8tev/hxx_lljjxx_mchi_1.root \
data/delphes/hxx_lljjxx/run_8tev_mchi1/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=21 --lumi=20 --xsec=149.8   data/analysis/8tev/hxx_lljjxx_mchi_10.root \
data/delphes/hxx_lljjxx/run_8tev_mchi10/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=22 --lumi=20 --xsec=149.8   data/analysis/8tev/hxx_lljjxx_mchi_100.root \
data/delphes/hxx_lljjxx/run_8tev_mchi100/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=23 --lumi=20 --xsec=149.8   data/analysis/8tev/hxx_lljjxx_mchi_500.root \
data/delphes/hxx_lljjxx/run_8tev_mchi500/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=24 --lumi=20 --xsec=149.8   data/analysis/8tev/hxx_lljjxx_mchi_1000.root \
data/delphes/hxx_lljjxx/run_8tev_mchi1000/tag_*_delphes_events.root

pushd data/analysis/8tev
if (-e all.root) rm all.root
hadd all.root *.root
popd
