#!/bin/bash
#./metropolis.out parameters.txt outputfile verboseTF NFil N iSite baseSepDist Force dimerForce

d=`date +%Y.%d.%m`
#d='2023.14.01'

#Edit these parameters:
for NumSeg in $(seq 218 218)
do
what='dimer' #'single' 'double'
NFil=2 #2
#NumSeg=${i} #single=300; double=200; dimer=122
if [ ${NFil} -eq 2 ]
then
	baseSepDist=16.667000
else
  baseSepDist=0
fi;
dimerForce=10 #0
iSite='-1'
force=0
#



#echo submit.${what}.N${NumSeg}.${d}.sh

cp testslurm.sub submit.${what}.N${NumSeg}.${d}.sub
sed -i "23c\ ./metropolis.out parameters.txt output_${what}.N${NumSeg}.iSite${iSite}.BSD${baseSepDist}.force${force}.kdimer${dimerForce}.txt 0 ${NFil} ${NumSeg} ${iSite} ${baseSepDist} ${force} ${dimerForce}
" "submit.${what}.N${NumSeg}.${d}.sub"
sed -i "3c\#SBATCH --job-name=dimer_${NumSeg}      ## Name of the job.
" "submit.${what}.N${NumSeg}.${d}.sub"
done

cd /pub/kbogue1/GitHub/Data/polymer-c_data
mkdir dimer.${d}

for NumSeg in $(seq 218 218)
do
cd /pub/kbogue1/GitHub/Data/polymer-c_data/dimer.${d}
mkdir run.${what}.N${NumSeg}_${d}
cd /pub/kbogue1/GitHub/polymer-c/src/PolymerCode
cp metropolis.out parameters.txt ISEED /pub/kbogue1/GitHub/Data/polymer-c_data/dimer.${d}/run.${what}.N${NumSeg}_${d}
cd /pub/kbogue1/GitHub/polymer-c/drivers
cp submit.${what}.N${NumSeg}.${d}.sub /pub/kbogue1/GitHub/Data/polymer-c_data/dimer.${d}/run.${what}.N${NumSeg}_${d}
cd /pub/kbogue1/GitHub/polymer-c/drivers
rm submit.${what}.N${NumSeg}.${d}.sub
done

for NumSeg in $(seq 218 218)
do
cd /pub/kbogue1/GitHub/Data/polymer-c_data/dimer.${d}/run.${what}.N${NumSeg}_${d}
sbatch submit.${what}.N${NumSeg}.${d}.sub
done
