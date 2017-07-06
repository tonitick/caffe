#include "mpi.h"

#include "caffe/ps/paramserv.hpp"

namespace ps {

Server::Server(int wc, int ds) {
  worker_count = wc;
  data_size = ds;
  data = new double[data_size];
  diff = new double[data_size];
  sub_diff = new double[data_size];
}

Server::~Server() {
  if(data != NULL) {
    delete[] data;
  }
  if(diff != NULL) {
    delete[] diff;
  }
  if(sub_diff != NULL) {
    delete[] sub_diff;
  }
}

void Server::collectParam() {
  for(int i = 0; i < data_size; i++) {
    diff[i] = 0.0;
  }

  for(int worker_id = 1; worker_id <= worker_count; worker_id++) {
    MPI_Recv(sub_diff, data_size, MPI_DOUBLE, worker_id, 0,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    for(int i = 0; i < data_size; i++) {
      diff[i] += sub_diff[i];
    }
  }

  for(int i = 0; i < data_size; i++) {
    diff[i] /= worker_count;
  }
}

void Server::broadcast() {
  for(int worker_id = 1; worker_id <= worker_count; worker_id++) {
    MPI_Send(data, data_size, MPI_DOUBLE,
        worker_id, 0, MPI_COMM_WORLD);
  }
}

double Server::getDiff(int index) {
  return diff[index];
}

void Server::setData(int index, double val) {
  data[index] = val;
}

Worker::Worker(int ds) {
  data_size = ds;
  data = new double[data_size];
  diff = new double[data_size];
}

Worker::~Worker() {
  if(data != NULL) {
    delete[] data;
  }
  if(diff != NULL) {
    delete[] diff;
  } 
}

void Worker::push() {
  MPI_Send(diff, data_size, MPI_DOUBLE, 
      0, 0, MPI_COMM_WORLD);
}

void Worker::pull() {
  MPI_Recv(data, data_size, MPI_DOUBLE, 0, 0,
      MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

double Worker::getData(int index) {
  return data[index];
}

void Worker::setDiff(int index, double val) {
  diff[index] = val;
}

}
