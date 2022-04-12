using System.Runtime.InteropServices;

namespace Numnet.Native{
    internal static class NativeApi{
        [DllImport("/home/lyh/code/Num.NET/build/apis/libnumnet.so")]
        public static extern StatusCode GetErrorCode(IntPtr status);
        [DllImport("/home/lyh/code/Num.NET/build/apis/libnumnet.so")]
        public static extern IntPtr GetErrorMessage(IntPtr status);
        [DllImport("/home/lyh/code/Num.NET/build/apis/libnumnet.so")]
        public static extern void FreeStatusMemory(IntPtr status);


        [DllImport("/home/lyh/code/Num.NET/build/apis/libnumnet.so")]
        public static extern IntPtr Matmul(IntPtr a, IntPtr b, IntPtr oup, IntPtr param, NativeProvider provider);
        [DllImport("/home/lyh/code/Num.NET/build/apis/libnumnet.so")]
        public static extern IntPtr Permute(IntPtr inp, IntPtr oup, IntPtr param, NativeProvider provider);
        [DllImport("/home/lyh/code/Num.NET/build/apis/libnumnet.so")]
        public static extern IntPtr Transpose(IntPtr inp, IntPtr oup, IntPtr param, NativeProvider provider);
    }
}