#!/bin/bash
#PBS -l nodes=2:ppn=2
#PBS -l walltime=00:01:00
#PBS -N tsyren_lab2

cd $PBS_O_WORKDIR
set -e
if [ -z "$num" ]; then
	exit;
fi
num=$num
if [ $num -le 0 ]; then
	exit;
fi

echo "1) running mpi, my num = $num; PBS_O_WORKDIR = $PBS_O_WORKDIR ; jobId = ${PBS_JOBID}" >> output.txt
ml icc
ml openmpi
mrirun -output-filename "./output_j${PBS_JOBID}" ./hello

num=$(expr $num - 1) || true
a=$(expr $num / 2) || true
b=$(expr $a + $num % 2) || true

if [$a -gt 0]; then
	qsub -r n -v num=$a,task1=$task1 -W depend=beforeok:$task1 runtasks.pbs
fi

if [ $b -gt 0 ] then
	qsub -r n -v num=$b,task1=$task1 -W depend=beforeok:$task1 runtasks.pbs
fi
