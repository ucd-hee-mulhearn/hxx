
export ROOTSYS=/share/apps/cms/cmssoft/cms/slc5_amd64_gcc462/cms/cmssw-patch/CMSSW_5_3_11_patch5/external/slc5_amd64_gcc462/
export PATH=/share/apps/cms/cmssoft/cms/slc5_amd64_gcc462/external/gcc/4.6.2/bin/:${ROOTSYS}/bin:${PATH}
export CMSSYS=/share/apps/cms/cmssoft/cms/slc5_amd64_gcc462/
export NEW_LIBS=./lib:${ROOTSYS}/lib:${CMSSYS}/cms/cmssw-patch/CMSSW_5_3_11_patch4/external/slc5_amd64_gcc462/lib/:${CMSSYS}/external/gcc/4.6.2/lib64/:${CMSSYS}/external/gcc/4.6.2/lib/:${CMSSYS}/cms/cmssw/CMSSW_5_3_11/lib/slc5_amd64_gcc462/
export LD_LIBRARY_PATH=${NEW_LIBS}:${LD_LIBRARY_PATH}




