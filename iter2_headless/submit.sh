#!/bin/sh
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=16
#SBATCH --time=00:30:00
#SBATCH --job-name=nbody_sim
#SBATCH --output=scaling_res_%j.txt

module load TeachEnv/2022a gcc openmpi
make clean
make

echo "number of threads,time" > table.csv

export OMP_NUM_THREADS=1
./nbody >> table.csv 2>&1 /dev/null

export OMP_NUM_THREADS=2
./nbody >> table.csv 2>&1 /dev/null

export OMP_NUM_THREADS=4
./nbody >> table.csv 2>&1 /dev/null

export OMP_NUM_THREADS=8
./nbody >> table.csv 2>&1 /dev/null

export OMP_NUM_THREADS=16
./nbody >> table.csv 2>&1 /dev/null

echo "done"
