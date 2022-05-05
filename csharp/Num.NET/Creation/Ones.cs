using Numnet.Common;
using Numnet.Manipulation;
using Numnet.Native.Param;
using Numnet.Native;

namespace Numnet{
    public static partial class Tensor{
        public static Tensor<T> Ones<T>(TensorShape shape) where T : struct, IConvertible, IEquatable<T>{
            Tensor<T> res = new Tensor<T>(new TensorLayout(shape, TensorTypeInfo.GetTypeInfo(typeof(T))._dtype));
            OnesInternal(res);
            return res;
        }
        private unsafe static void OnesInternal<T>(Tensor<T> src) where T : struct, IEquatable<T>, IConvertible{
            FillParam param = new FillParam() { value = 1.0 };
            IntPtr status = NativeExecutor.Execute(NativeApi.Fill, src.TMemory, src.TLayout, new IntPtr(&param), Tensor<T>.Provider);
            NativeStatus.AssertOK(status);
        }
    }
}