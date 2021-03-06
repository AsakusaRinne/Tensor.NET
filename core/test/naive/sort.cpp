#include "core/op/naive/ops.h"
#include "core/test/common/factory.h"
#include "core/test/common/utils.h"
#include "gtest/gtest.h"

using namespace nncore;
using namespace test;
using namespace opr;
using namespace opr::naive;

using F = NDArrayFactory;
using Param = param::sort;

TEST(Naive, Sort) {
  OpBase* oprs = OpNaiveImpl::get_instance();

  // Group 1
  Tensor inp1 = F::from_list(
      {31, 37, 18, 16, 6,  38, 43, 28, 36, 12, 16, 28, 10, 29, 5,  5,  42, 29,
       3,  40, 9,  22, 18, 29, 21, 3,  25, 15, 19, 39, 49, 34, 8,  34, 22, 9,
       27, 12, 4,  27, 40, 17, 10, 24, 6,  42, 21, 39, 18, 40, 40, 16, 10, 23,
       14, 25, 43, 48, 0,  17, 9,  0,  41, 0,  33, 47, 35, 42, 23, 38, 7,  22,
       11, 0,  19, 9,  7,  45, 23, 29, 2,  0,  38, 6,  41, 15, 8,  46, 34, 24,
       14, 28, 49, 19, 12, 47, 24, 5,  23, 12, 39, 40, 44, 46, 39, 34, 24, 5,
       28, 21, 36, 7,  14, 43, 11, 8,  38, 6,  7,  6,  12, 4,  9,  10, 42, 7,
       33, 9,  48, 36, 47, 25, 34, 35, 22, 7,  1,  1,  38, 8,  7,  44, 37, 19,
       28, 36, 8,  30, 49, 9,  47, 10, 39, 14, 27, 49, 6,  27, 28, 48, 8,  38,
       18, 16, 5,  4,  6,  48, 2,  11, 41, 24, 17, 37, 49, 45, 28, 41, 0,  4,
       2,  6,  45, 18, 10, 47, 31, 14, 45, 0,  13, 40, 24, 42, 25, 48, 3,  33,
       33, 17, 22, 31, 37, 3,  25, 5,  28, 37, 12, 20, 44, 8,  45, 36, 34, 42,
       22, 31, 26, 42, 11, 47, 45, 22, 39, 32, 28, 22, 26, 17, 28, 42, 3,  27,
       33, 4,  34, 6,  12, 23},
      {4, 3, 4, 5}, dtype::Int32());
  Tensor truth1 = F::from_list(
      {2,  0,  1,  0,  0,  3,  1,  5,  0,  5,  7,  8,  6,  3,  6,  7,  8,  10,
       14, 8,  2,  0,  3,  0,  4,  4,  6,  8,  2,  5,  8,  17, 9,  12, 11, 14,
       28, 10, 23, 11, 4,  6,  5,  3,  9,  5,  7,  9,  4,  12, 9,  22, 15, 16,
       12, 28, 31, 18, 23, 21, 5,  3,  6,  0,  6,  7,  4,  10, 18, 6,  13, 22,
       18, 19, 14, 36, 22, 22, 23, 17, 7,  8,  11, 6,  10, 9,  10, 14, 19, 12,
       32, 25, 18, 22, 17, 38, 33, 29, 27, 19, 8,  16, 12, 10, 20, 11, 21, 30,
       23, 22, 42, 34, 37, 29, 25, 44, 38, 39, 36, 27, 9,  6,  14, 7,  17, 12,
       7,  28, 24, 21, 16, 28, 33, 26, 28, 40, 31, 41, 34, 36, 9,  24, 24, 16,
       22, 15, 24, 37, 26, 27, 39, 28, 37, 34, 33, 47, 35, 44, 37, 39, 25, 24,
       27, 19, 24, 34, 25, 39, 33, 29, 47, 38, 41, 35, 33, 47, 40, 45, 45, 42,
       22, 27, 17, 12, 23, 36, 28, 38, 28, 38, 42, 34, 45, 36, 40, 45, 43, 45,
       46, 42, 31, 28, 31, 18, 25, 41, 40, 42, 29, 39, 47, 42, 46, 42, 40, 48,
       44, 48, 48, 48, 40, 37, 34, 28, 34, 47, 42, 45, 38, 39, 49, 43, 48, 43,
       41, 49, 47, 49, 49, 49},
      {4, 3, 4, 5}, dtype::Int32());
  Param p1(0, Param::Order::Increase);
  Param p2(2, Param::Order::Increase);
  Param p3(1, Param::Order::Increase);

  Tensor pred1;
  Tensor pred2;
  Tensor pred3;
  ASSERT_TRUE(oprs->sort(inp1, pred1, p1).is_ok());
  ASSERT_TRUE(oprs->sort(pred1, pred2, p2).is_ok());
  ASSERT_TRUE(oprs->sort(pred2, pred3, p3).is_ok());
  assert_same_data<nn_int32>(pred3, truth1, 0.0001f);
}