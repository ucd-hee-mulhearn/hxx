source COMPILE

# set to zero for all, non-zero to put cap on number output
setenv MAXEVENT 100000

rm data/analysis/8tev/*.root   ######  DELETING FILES HERE #####

# Using lumi in fb, xsec in fb^-1

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=1 --lumi=20 --xsec=145020    data/analysis/8tev/zjj_mll_gt_80.root \
data/delphes/zjj/run_100K_8TeV_MLL_GT_80/tag_1_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=1 --lumi=20 --xsec=2249     data/analysis/8tev/zjj_mll_lt_80.root \
data/delphes/zjj/run_100K_8TeV_MLL_LT_80/tag_1_delphes_events.root \
data/delphes/zjj/run_100K_8TeV_MLL_LT_80/tag_2_delphes_events.root 

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=2 --lumi=20 --xsec=363.3    data/analysis/8tev/zz_lljj.root \
data/delphes/zz_lljj/run_100K_8TeV/tag_1_delphes_events.root \
data/delphes/zz_lljj/run_100K_8TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=2 --lumi=20 --xsec=100.2    data/analysis/8tev/zz_llbb.root \
data/delphes/zz_llbb/run_100K_8TeV/tag_1_delphes_events.root \
data/delphes/zz_llbb/run_100K_8TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=2 --lumi=20 --xsec=586.3     data/analysis/8tev/zw_lljj.root \
data/delphes/zw_lljj/run_100K_8TeV/tag_1_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=3 --lumi=20 --xsec=437.9     data/analysis/8tev/wwjj.root \
data/delphes/wwjj_lvlvjj/run_100K_8TeV/tag_1_delphes_events.root \
data/delphes/wwjj_lvlvjj/run_100K_8TeV/tag_2_delphes_events.root \
data/delphes/wwjj_lvlvjj/run_100K_8TeV/tag_3_delphes_events.root \
data/delphes/wwjj_lvlvjj/run_100K_8TeV/tag_4_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=4 --lumi=20 --xsec=6298      data/analysis/8tev/tt.root \
data/delphes/tt/run_100K_8TeV/tag_*_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=5 --lumi=20 --xsec=24.53    data/analysis/8tev/h_zz_lljj.root \
data/delphes/h_zz_lljj/run_100K_8TeV/tag_1_delphes_events.root \
data/delphes/h_zz_lljj/run_100K_8TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=5 --lumi=20 --xsec=6.77    data/analysis/8tev/h_zz_llbb.root \
data/delphes/h_zz_llbb/run_100K_8TeV/tag_1_delphes_events.root \
data/delphes/h_zz_llbb/run_100K_8TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=6 --lumi=20 --xsec=0.02348  data/analysis/8tev/zh_vvlljj.root \
data/delphes/zh_vvlljj/run_100K_8TeV/tag_1_delphes_events.root \
data/delphes/zh_vvlljj/run_100K_8TeV/tag_2_delphes_events.root

#./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=6 --lumi=20 --xsec=0.00648  data/analysis/8tev/zh_vvllbb.root \
#data/delphes/zh_vvllbb/run_100K_8TeV/tag_1_delphes_events.root \
#data/delphes/zh_vvllbb/run_100K_8TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=7 --lumi=20 --xsec=0.2536   data/analysis/8tev/wh_vllljj.root \
data/delphes/wh_vllljj/run_100K_8TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=7 --lumi=20 --xsec=0.0700  data/analysis/8tev/wh_vlllbb.root \
data/delphes/wh_vlllbb/run_100K_8TeV/tag_1_delphes_events.root \
data/delphes/wh_vllljj/run_100K_8TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=20 --lumi=20 --xsec=117.4   data/analysis/8tev/hxx_lljjxx_mchi_1.root \
data/delphes/hxx_lljjxx/run_8tev_mchi1/tag_1_delphes_events.root
./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=20 --lumi=20 --xsec=32.40   data/analysis/8tev/hxx_llbbxx_mchi_1.root \
data/delphes/hxx_llbbxx/run_8tev_mchi1/tag_1_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=21 --lumi=20 --xsec=117.4   data/analysis/8tev/hxx_lljjxx_mchi_10.root \
data/delphes/hxx_lljjxx/run_8tev_mchi10/tag_1_delphes_events.root
./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=21 --lumi=20 --xsec=32.40   data/analysis/8tev/hxx_llbbxx_mchi_10.root \
data/delphes/hxx_llbbxx/run_8tev_mchi10/tag_1_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=22 --lumi=20 --xsec=117.4   data/analysis/8tev/hxx_lljjxx_mchi_100.root \
data/delphes/hxx_lljjxx/run_8tev_mchi100/tag_1_delphes_events.root
./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=22 --lumi=20 --xsec=32.40   data/analysis/8tev/hxx_llbbxx_mchi_100.root \
data/delphes/hxx_llbbxx/run_8tev_mchi100/tag_1_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=23 --lumi=20 --xsec=117.4   data/analysis/8tev/hxx_lljjxx_mchi_500.root \
data/delphes/hxx_lljjxx/run_8tev_mchi500/tag_1_delphes_events.root
./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=23 --lumi=20 --xsec=32.40   data/analysis/8tev/hxx_llbbxx_mchi_500.root \
data/delphes/hxx_llbbxx/run_8tev_mchi500/tag_1_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=24 --lumi=20 --xsec=117.4   data/analysis/8tev/hxx_lljjxx_mchi_1000.root \
data/delphes/hxx_lljjxx/run_8tev_mchi500/tag_1_delphes_events.root
./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=24 --lumi=20 --xsec=32.40   data/analysis/8tev/hxx_llbbxx_mchi_1000.root \
data/delphes/hxx_llbbxx/run_8tev_mchi1000/tag_1_delphes_events.root

pushd data/analysis/8tev
if (-e all.root) rm all.root
hadd all.root *.root
popd
