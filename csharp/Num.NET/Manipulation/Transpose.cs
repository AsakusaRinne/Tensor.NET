using Numnet.Common;
using Numnet.Native;
using Numnet.Exceptions;
using Numnet.Native.Param;

namespace Numnet.Manipulation{
    public static class TransposeExtension{

        public static Tensor Transpose(this Tensor src, int dimA, int dimB)
        {
            Tensor res = new Tensor(DeduceLayout(src.TLayout, dimA, dimB));
            res.TLayout.InitContiguousLayout();
            TransposeInternal(src, res, dimA, dimB);
            return res;
        }
        private unsafe static void TransposeInternal(Tensor src, Tensor dst, int dimA, int dimB){
            TransposeParam param = new TransposeParam() { dimA = dimA, dimB = dimB };
            IntPtr status = Tensor.Execute(NativeApi.Transpose, src.TMemory, dst.TMemory, src.TLayout, dst.TLayout, new IntPtr(&param), Tensor.Provider);
            NativeStatus.AssertOK(status);
        }
        private static TensorLayout DeduceLayout(TensorLayout src, int dimA, int dimB){
            TensorLayout res = new TensorLayout();
            if (dimA >= src.NDim || dimB >= src.NDim) {
                throw new InvalidParamException("Invalid param for transpose.");
            }
            res.DType = src.DType;
            res.NDim = src.NDim;
            for (int i = 0; i < src.NDim; i++) {
                res.Shape[i] = src.Shape[i];
            }
            res.Shape[src.NDim - dimA - 1] = src.Shape[src.NDim - dimB - 1];
            res.Shape[src.NDim - dimB - 1] = src.Shape[src.NDim - dimA - 1];
            return res;
        }
    }
}