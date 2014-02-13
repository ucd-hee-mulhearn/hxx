

setenv ROOTSYS /uscmst1/prod/sw/cms/slc5_amd64_gcc462/lcg/root/5.32.00-cms21

setenv PATH ${ROOTSYS}/bin:${PATH}
setenv PATH /uscmst1/prod/sw/cms/slc5_amd64_gcc462/external/gcc/4.6.2/bin/:$PATH

# Mainly looking for needed libs here:  /uscmst1/prod/sw/cms/slc5_amd64_gcc462/external

setenv NEW_LIBS ./lib:${ROOTSYS}/lib:/uscmst1/prod/sw/cms/slc5_amd64_gcc462/cms/cmssw-patch/CMSSW_5_3_11_patch4/external/slc5_amd64_gcc462/lib/:/uscmst1/prod/sw/cms/slc5_amd64_gcc462/external/gcc/4.6.2/lib64/:/uscmst1/prod/sw/cms/slc5_amd64_gcc462/external/gcc/4.6.2/lib/:/uscmst1/prod/sw/cms/slc5_amd64_gcc462/cms/cmssw/CMSSW_5_3_11/lib/slc5_amd64_gcc462/

setenv LD_LIBRARY_PATH ${NEW_LIBS}:${LD_LIBRARY_PATH}

