#!/bin/bash

#--------------------------------------------------#
#---------------- INPUT PARAMETERS ----------------#
mainInDir="${PWD}/../sim/output" # input directory
treeName='tree'
outputDir="${PWD}/output" # output directory
buildDir='./build' # build directory
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

com="./exe ${mainInDir} output_all.root ${outputDir} output_all ${treeName}"
com="${com} &> ${outputDir}/logExe_ana.txt"
echo "$com" >> runAll.sh
chmod a+x runAll.sh
echo "[INFO] Running ..."
time ./runAll.sh

cd -
