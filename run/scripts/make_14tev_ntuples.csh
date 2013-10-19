source COMPILE

setenv MAXEVENTA 100000 # Not used yet... for stat limited channels in final pass...
setenv MAXEVENTB 100000

rm data/analysis/14tev/*.root   ######  DELETING FILES HERE #####

# Using lumi in fb, xsec in fb^-1

./bin/MakeHxxTree --maxevent=$MAXEVENTB --sample=8 --lumi=300 --xsec=7951000    data/analysis/14tev/wjjj.root \
data/delphes_3day/wjjj/run_*_14TeV/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=1 --lumi=300 --xsec=552666    data/analysis/14tev/zjj.root \
data/delphes/zjj/run_14tev/tag_*_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=2 --lumi=300 --xsec=1587    data/analysis/14tev/zz_lljj.root \
data/delphes_3day/zz_lljj/run_100K_14TeV/tag_*_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=2 --lumi=300 --xsec=2400     data/analysis/14tev/zw_lljj.root \
data/delphes_3day/zw_lljj/run_100K_14TeV/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=3 --lumi=300 --xsec=2737     data/analysis/14tev/wwjj.root \
data/delphes_3day/wwjj_lvlvjj/run_100K_14TeV/tag_*_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=4 --lumi=300 --xsec=25847      data/analysis/14tev/tt.root \
data/delphes_3day/tt/run_100K_14TeV/tag_*_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=5 --lumi=300 --xsec=80.15    data/analysis/14tev/h_zz_lljj.root \
data/delphes/h_zz_lljj/run_100K_14TeV/tag_*_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=6 --lumi=300 --xsec=0.2696  data/analysis/14tev/zh_vvlljj.root \
data/delphes/zh_vvlljj/run_100K_14TeV/tag_*_delphes_events.root 

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=7 --lumi=300 --xsec=0.4346   data/analysis/14tev/wh_vllljj.root \
data/delphes/wh_jjllvv/run_14tev/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=20 --lumi=300 --xsec=149.8   data/analysis/14tev/hxx_lljjxx_mchi_1.root \
data/delphes/hxx_lljjxx/run_14tev_mchi1/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=21 --lumi=300 --xsec=149.8   data/analysis/14tev/hxx_lljjxx_mchi_10.root \
data/delphes/hxx_lljjxx/run_14tev_mchi10/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=22 --lumi=300 --xsec=149.8   data/analysis/14tev/hxx_lljjxx_mchi_100.root \
data/delphes/hxx_lljjxx/run_14tev_mchi100/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=23 --lumi=300 --xsec=149.8   data/analysis/14tev/hxx_lljjxx_mchi_500.root \
data/delphes/hxx_lljjxx/run_14tev_mchi500/tag_*_delphes_events.root

./bin/MakeHxxTree --mllcut --maxevent=$MAXEVENTB --sample=24 --lumi=300 --xsec=149.8   data/analysis/14tev/hxx_lljjxx_mchi_1000.root \
data/delphes/hxx_lljjxx/run_14tev_mchi1000/tag_*_delphes_events.root

pushd data/analysis/14tev
if (-e all.root) rm all.root
hadd all.root *.root
popd
