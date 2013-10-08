source COMPILE

setenv MAXEVENT 0

rm data/analysis/14tev/*.root   ######  DELETING FILES HERE #####

# Using lumi in fb, xsec in fb^-1

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=8 --lumi=300 --xsec=7951000    data/analysis/14tev/wjjj.root \
data/delphes_orig/wjjj/Events/run_*_14TeV/tag_*_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=1 --lumi=300 --xsec=385283    data/analysis/14tev/zjj_mll_gt_80.root \
data/delphes/zjj/run_100K_14TeV_MLL_GT_80/tag_1_delphes_events.root \
data/delphes/zjj/run_100K_14TeV_MLL_GT_80/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=1 --lumi=300 --xsec=9477     data/analysis/14tev/zjj_mll_lt_80.root \
data/delphes/zjj/run_100K_14TeV_MLL_LT_80/tag_1_delphes_events.root \
data/delphes/zjj/run_100K_14TeV_MLL_LT_80/tag_2_delphes_events.root 

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=2 --lumi=300 --xsec=777    data/analysis/14tev/zz_lljj.root \
data/delphes/zz_lljj/run_100K_14TeV/tag_1_delphes_events.root \
data/delphes/zz_lljj/run_100K_14TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=2 --lumi=300 --xsec=214    data/analysis/14tev/zz_llbb.root \
data/delphes/zz_llbb/run_100K_14TeV/tag_1_delphes_events.root \
data/delphes/zz_llbb/run_100K_14TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=2 --lumi=300 --xsec=1263     data/analysis/14tev/zw_lljj.root \
data/delphes/zw_lljj/run_100K_14TeV/tag_1_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=3 --lumi=300 --xsec=1388     data/analysis/14tev/wwjj.root \
data/delphes/wwjj_lvlvjj/run_100K_14TeV/tag_1_delphes_events.root \
data/delphes/wwjj_lvlvjj/run_100K_14TeV/tag_2_delphes_events.root \
data/delphes/wwjj_lvlvjj/run_100K_14TeV/tag_3_delphes_events.root \
data/delphes/wwjj_lvlvjj/run_100K_14TeV/tag_4_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=4 --lumi=300 --xsec=25847      data/analysis/14tev/tt.root \
data/delphes/tt/run_100K_14TeV/tag_*_delphes_events.root 

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=5 --lumi=300 --xsec=62.8    data/analysis/14tev/h_zz_lljj.root \
data/delphes/h_zz_lljj/run_100K_14TeV/tag_1_delphes_events.root \
data/delphes/h_zz_lljj/run_100K_14TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=5 --lumi=300 --xsec=17.3    data/analysis/14tev/h_zz_llbb.root \
data/delphes/h_zz_llbb/run_100K_14TeV/tag_1_delphes_events.root \
data/delphes/h_zz_llbb/run_100K_14TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=6 --lumi=300 --xsec=0.2113  data/analysis/14tev/zh_vvlljj.root \
data/delphes/zh_vvlljj/run_100K_14TeV/tag_1_delphes_events.root \
data/delphes/zh_vvlljj/run_100K_14TeV/tag_2_delphes_events.root

#./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=6 --lumi=300 --xsec=0.0583  data/analysis/14tev/zh_vvllbb.root \
#data/delphes/zh_vvllbb/run_100K_14TeV/tag_1_delphes_events.root \
#data/delphes/zh_vvllbb/run_100K_14TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=7 --lumi=300 --xsec=0.3804   data/analysis/14tev/wh_vllljj.root \
data/delphes/wh_vllljj/run_100K_14TeV/tag_2_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=7 --lumi=300 --xsec=0.104  data/analysis/14tev/wh_vlllbb.root \
data/delphes/wh_vlllbb/run_100K_14TeV/tag_1_delphes_events.root 


./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=20 --lumi=300 --xsec=117.4   data/analysis/14tev/hxx_lljjxx_mchi_1.root \
data/delphes/hxx_lljjxx/run_14tev_mchi1/tag_1_delphes_events.root
./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=20 --lumi=300 --xsec=32.40   data/analysis/14tev/hxx_llbbxx_mchi_1.root \
data/delphes/hxx_llbbxx/run_14tev_mchi1/tag_1_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=21 --lumi=300 --xsec=117.4   data/analysis/14tev/hxx_lljjxx_mchi_10.root \
data/delphes/hxx_lljjxx/run_14tev_mchi10/tag_1_delphes_events.root
./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=21 --lumi=300 --xsec=32.40   data/analysis/14tev/hxx_llbbxx_mchi_10.root \
data/delphes/hxx_llbbxx/run_14tev_mchi10/tag_1_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=22 --lumi=300 --xsec=117.4   data/analysis/14tev/hxx_lljjxx_mchi_100.root \
data/delphes/hxx_lljjxx/run_14tev_mchi100/tag_1_delphes_events.root
./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=22 --lumi=300 --xsec=32.40   data/analysis/14tev/hxx_llbbxx_mchi_100.root \
data/delphes/hxx_llbbxx/run_14tev_mchi100/tag_1_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=23 --lumi=300 --xsec=117.4   data/analysis/14tev/hxx_lljjxx_mchi_500.root \
data/delphes/hxx_lljjxx/run_14tev_mchi500/tag_1_delphes_events.root
./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=23 --lumi=300 --xsec=32.40   data/analysis/14tev/hxx_llbbxx_mchi_500.root \
data/delphes/hxx_llbbxx/run_14tev_mchi500/tag_1_delphes_events.root

./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=24 --lumi=300 --xsec=117.4   data/analysis/14tev/hxx_lljjxx_mchi_1000.root \
data/delphes/hxx_lljjxx/run_14tev_mchi500/tag_1_delphes_events.root
./bin/MakeHxxTree --maxevent=$MAXEVENT --sample=24 --lumi=300 --xsec=32.40   data/analysis/14tev/hxx_llbbxx_mchi_1000.root \
data/delphes/hxx_llbbxx/run_14tev_mchi1000/tag_1_delphes_events.root

pushd data/analysis/14tev
if (-e all.root) rm all.root
hadd all.root *.root
popd
