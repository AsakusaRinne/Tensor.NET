#include "core/op/naive/ops.h"

namespace nncore {
namespace opr {
namespace naive {

IMPL_NAIVE_DOUBLE_INPUT_INTERNAL(dot) {
  nn_size idx_offset = loup.ndim - NN_MAX_NDIM;
  for (nn_size n = 0; n < (idx_offset == 0 ? loup[idx_offset] : 1); n++) {
    nn_size n_offset_a = n * la.stride[idx_offset];
    nn_size n_offset_b = n * lb.stride[idx_offset];
    nn_size n_offset_oup = n * loup.stride[idx_offset];
    for (nn_size c = 0; c < (idx_offset >= -1 ? loup[idx_offset + 1] : 1);
         c++) {
      nn_size nc_offset_a = c * la.stride[idx_offset + 1] + n_offset_a;
      nn_size nc_offset_b = c * lb.stride[idx_offset + 1] + n_offset_b;
      nn_size nc_offset_oup = c * loup.stride[idx_offset + 1] + n_offset_oup;
      for (nn_size i = 0; i < (idx_offset >= -2 ? loup[idx_offset + 2] : 1);
           i++) {
        nn_size nch_offset_a = i * la.stride[idx_offset + 2] + nc_offset_a;
        nn_size nch_offset_b = i * lb.stride[idx_offset + 2] + nc_offset_b;
        nn_size nch_offset_oup =
            i * loup.stride[idx_offset + 2] + nc_offset_oup;
        for (nn_size j = 0; j < loup[idx_offset + 3]; j++) {
          nn_size a_pos = nch_offset_a + j * la.stride[idx_offset + 3];
          nn_size b_pos = nch_offset_b + j * lb.stride[idx_offset + 3];
          nn_size oup_pos = nch_offset_oup + j * loup.stride[idx_offset + 3];
          ptr_oup[oup_pos] = static_cast<TC>(ptr_a[a_pos] * ptr_b[b_pos]);
        }
      }
    }
  }
  return Status::OK();
}

}  // namespace naive
}  // namespace opr

}  // namespace nncore
