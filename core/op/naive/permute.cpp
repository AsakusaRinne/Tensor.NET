#include <iostream>

#include "core/op/naive/ops.h"

namespace nncore {
namespace opr {
namespace naive {

IMPL_NAIVE_SINGLE_INPUT_INTERNAL(permute) {
  nn_size n = loup.total_elems();
  nn_size src_idx[NN_MAX_NDIM], dst_idx[NN_MAX_NDIM];
  for (nn_size i = 0; i < n; i++) {
    loup.offset_to_indices(i, dst_idx);
    for (int j = 0; j < loup.ndim; j++) {
      src_idx[param.dims[j]] = dst_idx[j];
    }
    nn_size src_pos = linp.indices_to_offset(src_idx);
    ptr_oup[i] = ptr_inp[src_pos];
  }
  return Status::OK();
}

}  // namespace naive
}  // namespace opr

}  // namespace nncore
