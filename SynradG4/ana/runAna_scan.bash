#!/bin/bash

for id in {0..4}
do
	echo ''
	echo ">>> ID = ${id}"
	echo ''

	#--------------------------------------------------#
	#---------------- INPUT PARAMETERS ----------------#
	mainInDir="${PWD}/../sim/output_${id}" # input directory
	treeName='tree'
	outputDir="${PWD}/output_${id}" # output directory
	buildDir="./build_${id}" # build directory
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

	com="./exe ${mainInDir} sim_output_all.root ${outputDir} sim_output_all.root ${treeName}"
	com="${com} &> ${outputDir}/logExe_ana.txt"
	echo "$com" >> runAll.sh
	chmod a+x runAll.sh
	echo "[INFO] Running ..."
	time ./runAll.sh

	cd -
done
