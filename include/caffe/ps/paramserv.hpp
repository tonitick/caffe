#ifndef __PARAMSERV_H__
#define __PARAMSERV_H__

namespace ps {

class Server {
 public:
  Server(int wc, int ds);
  ~Server();

  void collectParam();
  void broadcast();
  double getDiff(int index);
  void setData(int index, double val);
  
 private:
  int worker_count;
  int data_size;
  double* data;
  double* diff;
  double* sub_diff;
};

class Worker {
 public:
  Worker(int ds);
  ~Worker();

  void push();
  void pull();
  double getData(int index);
  void setDiff(int index, double val);

 private:
  int data_size;
  double* data;
  double* diff;
};

}

#endif