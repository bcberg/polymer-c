#!/bin/bash
#./metropolis.out parameters.txt outputfile verboseTF NFil N iSite baseSepDist Force dimerForce

#d=`date +%Y.%d.%m`
#d='2023.15.01'
d=$(date +%Y.%d.%m.%T)

# polymer number of segments to sweep over
NStart=350
NStop=350

# output directory
output_dir=/pub/kbogue1/GitHub/Data/polymer-c_data/



#Edit these parameters:
for NumSeg in $(seq $NStart $NStop); do
  what='double' #'single' 'double'
  NFil=2        #2
  #NumSeg=${i} #single=300; double=200; dimer=122
  if [ ${NFil} -eq 2 ]; then
    baseSepDist=16.667000
  else
    baseSepDist=0
  fi
  dimerForce=0 #10
  iSite='-1'
  force=0
  #

  #echo submit.${what}.N${NumSeg}.${d}.sh

  cp testslurm.sub submit.${what}.N${NumSeg}.${d}.sub
  sed -i "23c\ ./metropolis.out parameters.txt output_${what}.N${NumSeg}.iSite${iSite}.BSD${baseSepDist}.force${force}.kdimer${dimerForce}.txt 0 ${NFil} ${NumSeg} ${iSite} ${baseSepDist} ${force} ${dimerForce}
" "submit.${what}.N${NumSeg}.${d}.sub"
  sed -i "3c\#SBATCH --job-name=double_${NumSeg}      ## Name of the job.
" "submit.${what}.N${NumSeg}.${d}.sub"
done

cd $output_dir
mkdir double.${d}

for NumSeg in $(seq $NStart $NStop); do
  mkdir $output_dir/double.${d}/run.${what}.N${NumSeg}_${d}
  cp src/PolymerCode/metropolis.out src/PolymerCode/parameters.txt src/PolymerCode/ISEED $output_dir/double.${d}/run.${what}.N${NumSeg}_${d}
  cp drivers/submit.${what}.N${NumSeg}.${d}.sub $output_dir/double.${d}/run.${what}.N${NumSeg}_${d}
  rm drivers/submit.${what}.N${NumSeg}.${d}.sub
done

for NumSeg in $(seq $NStart $NStop); do
  cd $output_dir/double.${d}/run.${what}.N${NumSeg}_${d}
  sbatch submit.${what}.N${NumSeg}.${d}.sub
done
