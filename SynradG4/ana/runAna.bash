#!/bin/bash

#--------------------------------------------------#
#---------------- INPUT PARAMETERS ----------------#
mainInDir="${PWD}/../sim/output" # input directory
treeName='tree'
outputDir="${PWD}/output" # output directory
buildDir="./build" # build directory
#--------------------------------------------------#
#--------------------------------------------------#

echo "[INFO] mainInDir = ${mainInDir}"
echo "[INFO] treeName = ${treeName}"
echo "[INFO] outputDir = ${outputDir}"
echo "[INFO] buildDir = ${buildDir}"

# output directory
mkdir -pv ${outputDir}

# build directory
mkdir -pv ${buildDir}
cd ${buildDir}

# config
make clean
cmake ../

# compile
make -j4

rm -rf ${mainInDir}/sim_output_all.root
hadd -f ${mainInDir}/sim_output_all.root ${mainInDir}/sim_output_*.root

com="./exe ${mainInDir} sim_output_all.root ${outputDir} ana_output_all.root ${treeName}"
com="${com} &> ${outputDir}/logExe_ana.txt"
echo "$com" >> runAll.sh
chmod a+x runAll.sh
echo "[INFO] Running ..."
time ./runAll.sh

cd -
