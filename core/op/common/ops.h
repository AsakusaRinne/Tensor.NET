#pragma once

#include <string>

#include "core/base/include/ndArray.h"
#include "core/macro.h"
#include "core/op/common/param.h"

namespace nncore {
namespace opr {

using namespace param;

#define NN_FOREACH_SINGLE_INPUT_OP(cb) cb(reshape) cb(transpose)

#define NN_FOREACH_DOUBLE_INPUT_OP(cb) cb(matmul) cb(dot)

#define NN_FOREACH_SINGLE_INPUT_OP_WITH_PARAM(cb, ...) \
  cb(reshape, __VA_ARGS__) cb(transpose, __VA_ARGS__)

#define NN_FOREACH_DOUBLE_INPUT_OP_WITH_PARAM(cb, ...) \
  cb(matmul, __VA_ARGS__) cb(dot, __VA_ARGS__)

#define DEF_OP_SINGLE_INPUT(_name)                     \
 public:                                               \
  virtual void _name(const NDArray& inp, NDArray& oup, \
                     const param::_name& param) = 0;   \
                                                       \
 protected:                                            \
  bool deduce_layout_##_name(Layout& inp, Layout& res, \
                             const param::_name param);

#define DEF_OP_DOUBLE_INPUT(_name)                                     \
 public:                                                               \
  virtual void _name(const NDArray& a, const NDArray& b, NDArray& oup, \
                     const param::_name& param) = 0;                   \
                                                                       \
 protected:                                                            \
  bool deduce_layout_##_name(Layout& a, Layout& b, Layout& res,        \
                             const param::_name param);

class OpBase {
  NN_FOREACH_SINGLE_INPUT_OP(DEF_OP_SINGLE_INPUT)

  NN_FOREACH_DOUBLE_INPUT_OP(DEF_OP_DOUBLE_INPUT)

  virtual ~OpBase() = default;
};

#undef DEF_OP_SINGLE_INPUT
#undef DEF_OP_DOUBLE_INPUT

#define IMPL_SINGLE_INPUT_LAYOUT_DEDUCE(_name)                 \
  bool OpBase::deduce_layout_##_name(Layout& inp, Layout& res, \
                                     const param::_name params)
#define IMPL_DOUBLE_INPUT_LAYOUT_DEDUCE(_name)                          \
  bool OpBase::deduce_layout_##_name(Layout& a, Layout& b, Layout& res, \
                                     const param::_name params)

#define TYPE_SELECT_SINGLE_INPUT(_type, _name)            \
  if (loup.dtype.is_ctype<_type>()) {                     \
    _name##_internal<_type>(inp, oup, linp, loup, param); \
    return;                                               \
  }
#define TYPE_SELECT_DOUBLE_INPUT(_type, _name)               \
  if (oup.layout.dtype.is_ctype<_type>()) {                  \
    _name##_internal<_type>(a, b, oup, la, lb, loup, param); \
    return;                                                  \
  }

#define IMPL_OP_SINGLE_INPUT(_name)                                            \
 public:                                                                       \
  void _name(const NDArray& inp, NDArray& oup, const param::_name& param) {    \
    Layout linp(inp.layout);                                                   \
    Layout loup;                                                               \
    nn_assert(deduce_layout_##_name(linp, loup, param), "Layout mismatched."); \
    oup.relayout(loup.auto_stride());                                          \
    NN_FOREACH_CTYPE_WITH_PARAM(TYPE_SELECT_SINGLE_INPUT, _name)               \
  }                                                                            \
                                                                               \
 private:                                                                      \
  template <typename T>                                                        \
  void _name##_internal(const NDArray& inp, const NDArray& oup,                \
                        const Layout& linp, const Layout& loup,                \
                        const param::_name& param);

#define IMPL_OP_DOUBLE_INPUT(_name)                              \
 public:                                                         \
  void _name(const NDArray& a, const NDArray& b, NDArray& oup,   \
             const param::_name& param) {                        \
    Layout la(a.layout);                                         \
    Layout lb(b.layout);                                         \
    Layout loup;                                                 \
    nn_assert(deduce_layout_##_name(la, lb, loup, param),        \
              "Layout mismatched.");                             \
    oup.relayout(loup.auto_stride());                            \
    NN_FOREACH_CTYPE_WITH_PARAM(TYPE_SELECT_DOUBLE_INPUT, _name) \
  }                                                              \
                                                                 \
 private:                                                        \
  template <typename T>                                          \
  void _name##_internal(const NDArray& a, const NDArray& b,      \
                        const NDArray& oup, const Layout& la,    \
                        const Layout& lb, const Layout& loup,    \
                        const param::_name& param);

#define SPECIFY_SINGLE_OUTPUT_OP_INTERNAL(_type, _class_name, _op_name) \
  template void _class_name::_op_name##_internal<_type>(                \
      const NDArray& inp, const NDArray& oup, const Layout& linp,       \
      const Layout& loup, const param::_op_name& param);

#define SPECIFY_DOUBLE_OUTPUT_OP_INTERNAL(_type, _class_name, _op_name) \
  template void _class_name::_op_name##_internal<_type>(                \
      const NDArray& a, const NDArray& b, const NDArray& oup,           \
      const Layout& la, const Layout& lb, const Layout& loup,           \
      const param::_op_name& param);

// #undef DEF_OP_METHOD_SINGLE_INPUT
// #undef DEF_OP_METHOD_DOUBLE_INPUT

}  // namespace opr

}  // namespace nncore
