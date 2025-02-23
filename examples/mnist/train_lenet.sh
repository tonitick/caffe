#!/usr/bin/env sh
set -e

# ./build/tools/caffe train --solver=./examples/mnist/lenet_solver.prototxt $@
# mpirun -np 2 -machinefile /usr/cluster/machinefile /usr/cluster/caffe/build/tools/caffe train --solver=/usr/cluster/caffe/examples/mnist/lenet_solver.prototxt $@
mpirun -n 3 ./build/tools/caffe train --solver=examples/mnist/lenet_solver.prototxt $@

