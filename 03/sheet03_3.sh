#!/bin/bash

# Executes job in the queue "std.q" unless you have special requirements.
$ -q sheet03_3.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
$ -N sheet03_3

# Redirect output stream to this file.
$ -o output.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
$ -pe openmp 8

# Use gcc 8.2.0 as the default gcc
module load gcc/8.2.0

# Set up any environment variables
export ENVIRONMENT_VARIABLE=foobar

./usr/bin/time -v ./ex2_1