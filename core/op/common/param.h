#pragma once

#include <memory.h>

#include "core/base/include/layout.h"

namespace nncore {
namespace param {

struct transpose {
  nn_size dimA;
  nn_size dimB;

  transpose(nn_size a, nn_size b) : dimA(a), dimB(b) {}
};

struct permute {
  nn_size *dims;

  permute(const std::vector<nn_size> &value) {
    dims = (nn_size *)malloc(sizeof(nn_size) * NN_MAX_NDIM);
    memcpy(dims, value.data(), value.size() * sizeof(nn_size));
  }

  ~permute() {
    free(dims);
    dims = nullptr;
  }

 private:
  permute(const permute &) {}
  void operator=(const permute &) {}
};

struct argmxx {
  int axis;
  bool is_max;

  argmxx(int axis, bool is_max) : axis(axis), is_max(is_max) {}
};

struct convert {
  DTypeEnum target_type;

  convert(DTypeEnum target_type) : target_type(target_type) {}
};

struct normal {
  double avg;
  double std;

  normal(double avg, double std) : avg(avg), std(std) {}
};

struct uniform {
  double min_value;
  double max_value;
  uniform(double min_value, double max_value)
      : min_value(min_value), max_value(max_value) {}
};

struct eye {
  int k;
  eye(int k) : k(k) {}
};

struct fill {
  double value;
  fill(double value) : value(value) {}
};

struct linspace {
  double start;
  double stop;
  int num;
  bool is_endpoint;

  linspace(double start, double stop, int num, bool is_endpoint)
      : start(start), stop(stop), num(num), is_endpoint(is_endpoint) {}
};

struct concat {
  int axis;

  concat(int axis) : axis(axis) {}
};

struct matmul {};

struct dot {};

struct boolindex {};
}  // namespace param

}  // namespace nncore
